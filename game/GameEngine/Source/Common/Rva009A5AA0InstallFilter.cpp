// ?Rva009A5AA0InstallFilter@@YAXPAX00H@Z
// Retail RVA 0x009A5AA0, 193 bytes.  Rva009A4D00Init (0x009A4D00) calls it
// directly as cdecl with three table pointers (all its 64-entry int table
// 0x0134C6D8) and the tier constant 7.  The body builds the saturating clamp
// table read by the loop filters, publishes the three table pointers, copies
// the 64-entry source table, picks the tier's pair of tables and runs the CPU
// dispatch installer.

// Retail passes the tier on the stack although the installer's landed body
// (0x009B0D60) never reads an argument, so the call goes through a typed cast
// of its ledger name.
extern void __cdecl bfmeInstallCpuDispatchTable(void);
typedef void (__cdecl *Rva009A5AA0TierInstaller)(int);

extern const unsigned char g_bfmeClampTable[];	// retail 0x01356FE0 (zero point)
extern const unsigned int *g_rva01356AA0;
extern const unsigned int *g_rva01356A98;
extern const void *g_rva01356A88;
extern int g_rva01356940[64];
extern unsigned short *Rva009C0D10Src;			// retail 0x01356A7C
extern int *g_rva01356A9C;

extern unsigned short g_rva012D7C58[128];
extern unsigned short g_rva012D7D58[128];
extern unsigned short g_rva012D7E58[128];
extern int g_rva012D7858[64];
extern int g_rva012D7958[64];
extern int g_rva012D7A58[64];

void __cdecl Rva009A5AA0InstallFilter(void *firstTable, void *secondTable, void *sourceTable, int tier)
{
	unsigned char *clamp = (unsigned char *)g_bfmeClampTable;
	int i;
	for (i = -256; i < 512; ++i)
	{
		int value;
		if (i < 0)
			value = 0;
		else
		{
			value = i;
			if (value > 255)
				value = 255;
		}
		clamp[i] = (unsigned char)value;
	}

	g_rva01356AA0 = (const unsigned int *)firstTable;
	g_rva01356A98 = (const unsigned int *)secondTable;
	g_rva01356A88 = sourceTable;
	for (i = 0; i < 64; ++i)
		g_rva01356940[i] = ((const int *)sourceTable)[i];

	if ((unsigned)tier >= 6)
	{
		Rva009C0D10Src = g_rva012D7E58;
		g_rva01356A9C = g_rva012D7A58;
	}
	else if ((unsigned)tier >= 5)
	{
		Rva009C0D10Src = g_rva012D7D58;
		g_rva01356A9C = g_rva012D7958;
	}
	else
	{
		Rva009C0D10Src = g_rva012D7C58;
		g_rva01356A9C = g_rva012D7858;
	}
	((Rva009A5AA0TierInstaller)bfmeInstallCpuDispatchTable)(tier);
}
