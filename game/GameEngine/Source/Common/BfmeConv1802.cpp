class BfmeStateVT
{
public:
	unsigned char m_bfmeHeadVT[0x5e];
	char m_bfmeFlagVT;
};

class BfmeUnitVT
{
public:
	unsigned char m_bfmeHeadVT[0x208];
	BfmeStateVT *m_bfmeStateVT;
};

// Retail routes this call through the five-byte incremental-link thunk at
// 0x000030B2, whose ledger name is ?j_000030b2@@YAXXZ
// (game/gen_small/thunks_001.cpp, target FUN_00608a50).
void j_000030b2(void);

class BfmeOwnerVT
{
public:
	int bfmeTouchVT(void);

	unsigned char m_bfmeHeadVT[0x2c];
	unsigned char m_bfmeMaskVT;
	unsigned char m_bfmeGapVT[3];
	char m_bfmeDirtyVT;
};

int BfmeOwnerVT::bfmeTouchVT(void)
{
	BfmeUnitVT *unit = *(BfmeUnitVT **)((char *)this - 8);

	if (unit->m_bfmeStateVT->m_bfmeFlagVT)
		m_bfmeDirtyVT = 1;

	if (m_bfmeMaskVT & 1)
		j_000030b2();

	return 1;
}
