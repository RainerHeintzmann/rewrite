/*
 *	console.c (2026): the console reads and writes UTF-8 (names like α).
 *	Apart from sync.c because windows.h defines names of its own (BOOLEAN).
 */

#include <string.h>
#ifdef _WIN32
#include <windows.h>
#include <shlobj.h>		/* SHGetFolderPath */
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
