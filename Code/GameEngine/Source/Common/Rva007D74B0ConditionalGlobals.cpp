// Open-BFME: conditional global reads reconstructed from retail RVA 0x007D74B0.

extern volatile int g_Rva012F9D04;
extern volatile int g_Rva012F9D0C;

int Rva007D74B0ReadGlobals(void)
{
	if (g_Rva012F9D04 != 0)
		(void)g_Rva012F9D0C;
	return 0;
}
