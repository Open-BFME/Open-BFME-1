// ?bfmeRefreshAAK@@YAXXZ
// partial score=0.8 date=2026-09-08
struct Rva005A00B0AudioClient
{
	unsigned char m_bfmeHeadAAK[0xb8];
	unsigned char m_bfmeSlotsAAK[0x54c];
};

extern Rva005A00B0AudioClient *volatile TheAudioClientUpdate;

void __stdcall refreshPair(int a, int b);

void bfmeRefreshAAK();

void bfmeRefreshAAK()
{
	if (TheAudioClientUpdate == 0)
		return;

	for (int off = 0; off < 0x54c; off += 0x1c4)
	{
		unsigned char *volatile slot = TheAudioClientUpdate->m_bfmeSlotsAAK + off;

		for (int j = 0; j < 6; ++j)
			for (int k = 0; k < 2; ++k)
				refreshPair(j, k);
	}
}
