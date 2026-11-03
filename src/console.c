/*
 *	console.c (2026): the console reads and writes UTF-8 (names like α).
 *	Apart from sync.c because windows.h defines names of its own (BOOLEAN).
 */

#include <stdio.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#include <shlobj.h>		/* SHGetFolderPath */
#include <io.h>			/* _open_osfhandle */
#else
#include <unistd.h>		/* readlink */
#endif

void console_utf8 (void)
{
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
#endif
}

/* the Windows profile folder (C:\Users\<user>) from Windows itself, also
   where USERPROFILE is not passed on (the MSYS2 login shell); NULL elsewhere */
const char * windows_home (void)
{
#ifdef _WIN32
	static char path[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_PROFILE, NULL, 0, path))) return path;
#endif
	return 0;
}

/* the folder of the running program (the library may be next to it), or
   NULL if it is not known */
const char * program_dir (void)
{
	static char path[4096];
	char * slash;
#ifdef _WIN32
	DWORD n = GetModuleFileNameA(NULL, path, sizeof path);
	char * back;
	if (n == 0 || n >= sizeof path) return 0;
	slash = strrchr(path, '/');
	back = strrchr(path, '\\');
	if (back > slash) slash = back;
#else
	ssize_t n = readlink("/proc/self/exe", path, sizeof path - 1);
	if (n <= 0) return 0;
	path[n] = 0;
	slash = strrchr(path, '/');
#endif
	if (! slash) return 0;
	* slash = 0;
	return path;
}

/* a program prog with the arguments args that reads what is written to the
   returned file (gnuplot for plot); quiet: its output is discarded, else it
   writes into rewrite's output. *proc: for child_close. On Windows it gets
   only these handles: a gnuplot window that stays after rewrite must not
   keep a pipe open into which rewrite or its caller writes (rewrite f.rw |
   less, RewriteCAS.jl); Windows would pass on all inheritable handles. */
FILE * child_open (const char * prog, const char * args, int quiet, void ** proc)
{
	char cmd[1200];
#ifdef _WIN32
	SECURITY_ATTRIBUTES sa = { sizeof sa, NULL, TRUE };
	STARTUPINFOEXA si;
	PROCESS_INFORMATION pi;
	HANDLE rd, wr, out = NULL, err = NULL, self = GetCurrentProcess(), list[3];
	SIZE_T size = 0;
	int n = 0, ok, fd;
	if (! CreatePipe(& rd, & wr, & sa, 0)) return NULL;
	SetHandleInformation(wr, HANDLE_FLAG_INHERIT, 0);
	if (quiet)
		out = err = CreateFileA("NUL", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, & sa, OPEN_EXISTING, 0, NULL);
	else
		{
		DuplicateHandle(self, GetStdHandle(STD_OUTPUT_HANDLE), self, & out, 0, TRUE, DUPLICATE_SAME_ACCESS);
		DuplicateHandle(self, GetStdHandle(STD_ERROR_HANDLE), self, & err, 0, TRUE, DUPLICATE_SAME_ACCESS);
		}
	list[n++] = rd;
	if (out && out != INVALID_HANDLE_VALUE) list[n++] = out;
	if (err && err != INVALID_HANDLE_VALUE && err != out) list[n++] = err;
	ZeroMemory(& si, sizeof si);
	si.StartupInfo.cb = sizeof si;
	si.StartupInfo.dwFlags = STARTF_USESTDHANDLES;
	si.StartupInfo.hStdInput = rd;
	si.StartupInfo.hStdOutput = out;
	si.StartupInfo.hStdError = err;
	InitializeProcThreadAttributeList(NULL, 1, 0, & size);
	si.lpAttributeList = (LPPROC_THREAD_ATTRIBUTE_LIST) HeapAlloc(GetProcessHeap(), 0, size);
	ok = si.lpAttributeList && InitializeProcThreadAttributeList(si.lpAttributeList, 1, 0, & size)
	     && UpdateProcThreadAttribute(si.lpAttributeList, 0, PROC_THREAD_ATTRIBUTE_HANDLE_LIST,
	                                  list, n * sizeof(HANDLE), NULL, NULL);
	snprintf(cmd, sizeof cmd, "\"%s\" %s", prog, args);
	ok = ok && CreateProcessA(NULL, cmd, NULL, NULL, TRUE, EXTENDED_STARTUPINFO_PRESENT,
	                          NULL, NULL, & si.StartupInfo, & pi);
	if (si.lpAttributeList)
		{
		DeleteProcThreadAttributeList(si.lpAttributeList);
		HeapFree(GetProcessHeap(), 0, si.lpAttributeList);
		}
	CloseHandle(rd);
	if (out && out != INVALID_HANDLE_VALUE) CloseHandle(out);
	if (err && err != INVALID_HANDLE_VALUE && err != out) CloseHandle(err);
	if (! ok) { CloseHandle(wr); return NULL; }
	CloseHandle(pi.hThread);
	* proc = pi.hProcess;
	fd = _open_osfhandle((intptr_t) wr, 0);
	return fd < 0 ? NULL : fdopen(fd, "w");
#else
	snprintf(cmd, sizeof cmd, "\"%s\" %s%s", prog, args, quiet ? " >/dev/null 2>&1" : "");
	* proc = NULL;
	return popen(cmd, "w");
#endif
}

/* closes the input of the program and waits for it: its exit status */
int child_close (FILE * fp, void * proc)
{
#ifdef _WIN32
	DWORD code = 1;
	fclose(fp);
	WaitForSingleObject((HANDLE) proc, INFINITE);
	GetExitCodeProcess((HANDLE) proc, & code);
	CloseHandle((HANDLE) proc);
	return (int) code;
#else
	return pclose(fp);
#endif
}
