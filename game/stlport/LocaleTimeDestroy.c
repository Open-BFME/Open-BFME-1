// STLport 4.5.3 Win32 _Locale_time_destroy.

__declspec(dllimport) void __cdecl free(void *memory);

typedef struct _Locale_time
{
	char header[0x0C];
	char *abbrev_month[12];
	char *full_month[12];
	char *abbrev_day[7];
	char *full_day[7];
} _Locale_time;

void _Locale_time_destroy(void *l)
{
	_Locale_time *time;
	int i;

	if (!l)
		return;

	time = (_Locale_time *)l;
	for (i = 0; i < 12; ++i) {
		if (time->abbrev_month[i])
			free(time->abbrev_month[i]);
		if (time->full_month[i])
			free(time->full_month[i]);
	}
	for (i = 0; i < 7; ++i) {
		if (time->abbrev_day[i])
			free(time->abbrev_day[i]);
		if (time->full_day[i])
			free(time->full_day[i]);
	}
	free(l);
}
