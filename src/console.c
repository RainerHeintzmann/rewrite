/*
 *	console.c (2026): the console reads and writes UTF-8 (names like α).
 *	Apart from sync.c because windows.h defines names of its own (BOOLEAN).
 */

#ifdef _WIN32
#include <windows.h>
#include <shlobj.h>		/* SHGetFolderPath */
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
