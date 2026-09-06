// Four more: a limit picked by a global switch, a search through a two-level
// Open-BFME7: retail 0x003BCBB0 (42 bytes) is the twin of bfmeLimit (Bfme5FortyNine.cpp,
// 0x003BCB70) reading the low/high pair 0x48 bytes earlier in the same base object
// (+0xE70/+0xE74 instead of +0xEB8/+0xEBC); same switch global.

class BfmeSwitchDR
{
public:
	int m_bfmeHead[7];					// +0x00
	bool m_bfmeUseHigh;					// +0x1C
};

class BfmeBaseDS003BCBB0
{
public:
	char m_bfmeHead[0xE70];					// +0x000
	int m_bfmeLow;						// +0xE70
	int m_bfmeHigh;						// +0xE74
};

extern BfmeSwitchDR *g_bfmeSwitchDR;				// retail 0x012F1024
extern BfmeBaseDS003BCBB0 *g_bfmeBaseDS003BCBB0;		// retail 0x012ED5C8

// retail 0x003BCBB0
int __cdecl bfmeLimit003BCBB0(void)
{
	BfmeSwitchDR *state = g_bfmeSwitchDR;
	int high = state != 0 ? state->m_bfmeUseHigh : 0;
	if (state != 0 && high != 0)
		return g_bfmeBaseDS003BCBB0->m_bfmeHigh;
	return g_bfmeBaseDS003BCBB0->m_bfmeLow;
}
