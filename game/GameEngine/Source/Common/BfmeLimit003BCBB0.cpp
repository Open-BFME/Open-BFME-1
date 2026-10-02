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

// TU-local VIEW of the real GlobalData, kept only for its offsets.
class BfmeBaseDS003BCBB0
{
public:
	char m_bfmeHead[0xE70];					// +0x000
	int m_bfmeLow;						// +0xE70
	int m_bfmeHigh;						// +0xE74
};

// retail 0x012ED5C8 is EA's `GlobalData *TheWritableGlobalData`, defined once
// in Common/GlobalData.cpp.  In the linked build this TU must spell the global
// exactly that way or nothing defines it.
class GlobalData;
// retail 0x012F1024 is EA's `LivingWorldCampaignManager
// *TheLivingWorldCampaignManager`, defined once in
// GameLogic/LivingWorld/LivingWorldCampaignManager.cpp.  In the linked build
// this TU must spell the global exactly that way or nothing defines it; the
// view above is kept for its offsets only and the cast happens at the use.
class LivingWorldCampaignManager;
extern LivingWorldCampaignManager *TheLivingWorldCampaignManager;	// retail 0x012F1024
extern GlobalData *   TheWritableGlobalData;			// retail 0x012ED5C8

// retail 0x003BCBB0
int __cdecl bfmeLimit003BCBB0(void)
{
	BfmeSwitchDR *state = (BfmeSwitchDR *)TheLivingWorldCampaignManager;
	int high = state != 0 ? state->m_bfmeUseHigh : 0;
	if (state != 0 && high != 0)
		return ((BfmeBaseDS003BCBB0 *)TheWritableGlobalData)->m_bfmeHigh;
	return ((BfmeBaseDS003BCBB0 *)TheWritableGlobalData)->m_bfmeLow;
}
