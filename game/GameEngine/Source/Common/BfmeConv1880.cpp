extern const char g_rva01080FC0[2];
// One-byte flag in zero-filled .bss at VA 0x012F1B23 (dir32_addresses.csv);
// Rva0046EF50SetFlag sets it. Defined once here.
extern "C" char g_bfmeFlagZM;
char g_bfmeFlagZM;

void __cdecl bfmeCopyZM(void *unused, char *dest, char flag)
{
	if (dest == 0 || flag != 0)
		return;

	const char *src = g_bfmeFlagZM ? g_rva01080FC0 : "0";
	char *out = dest;

	for (;;)
	{
		char c = *src++;

		*out++ = c;

		if (c == 0)
			break;
	}
}
