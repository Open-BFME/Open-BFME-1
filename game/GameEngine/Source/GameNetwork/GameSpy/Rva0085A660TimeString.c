/* 0x0085A660 (160 B): formats the current local time as "mm.dd.yy hh:mm.ss"
   into a static buffer, or "00.00.00 00:00.00" when localtime fails. It sits
   in the GameSpy SDK block (after sb_server.c's SBServerGetTeamIntValueA,
   before chat's ciBufferInit) and has no remaining references, so its name
   keeps the address. */
typedef long time_t;
struct tm { int tm_sec, tm_min, tm_hour, tm_mday, tm_mon, tm_year, tm_wday, tm_yday, tm_isdst; };
__declspec(dllimport) time_t __cdecl time(time_t *);
__declspec(dllimport) struct tm *__cdecl localtime(const time_t *);
__declspec(dllimport) int __cdecl sprintf(char *, const char *, ...);
char *__cdecl strcpy(char *, const char *);
#pragma intrinsic(strcpy)

static char Rva0085A660TimeBuffer[20];

char *Rva0085A660TimeString(void)
{
	time_t now;
	struct tm *local;

	now = time(0);
	local = localtime(&now);
	if (local)
	{
		if (local->tm_year > 99)
			local->tm_year -= 100;
		sprintf(Rva0085A660TimeBuffer, "%02d.%02d.%02d %02d:%02d.%02d",
			local->tm_mon + 1, local->tm_mday, local->tm_year,
			local->tm_hour, local->tm_min, local->tm_sec);
		return Rva0085A660TimeBuffer;
	}
	strcpy(Rva0085A660TimeBuffer, "00.00.00 00:00.00");
	return Rva0085A660TimeBuffer;
}
