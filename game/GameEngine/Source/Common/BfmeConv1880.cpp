extern "C" char g_bfmeSingleZM[];
extern "C" char g_bfmeExtendedZM[];
extern "C" char g_bfmeFlagZM;

void __cdecl bfmeCopyZM(void *unused, char *dest, char flag)
{
	if (dest == 0 || flag != 0)
		return;

	const char *src = g_bfmeFlagZM ? g_bfmeSingleZM : g_bfmeExtendedZM;
	char *out = dest;

	for (;;)
	{
		char c = *src++;

		*out++ = c;

		if (c == 0)
			break;
	}
}
