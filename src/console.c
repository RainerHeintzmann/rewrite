/*
 *	console.c (2026): the console reads and writes UTF-8 (names like α).
 *	Apart from sync.c because windows.h defines names of its own (BOOLEAN).
 */

#ifdef _WIN32
#include <windows.h>
#endif

void console_utf8 (void)
{
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
#endif
}
