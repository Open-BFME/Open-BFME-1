// TU-local VIEW of the real GlobalData, kept only for its offsets.
class BfmeGlobalCBE
{
public:
	unsigned char m_bfmeHead[0x68];
	void *m_bfmeCur;
};

// retail 0x012ED5C8 is EA's `GlobalData *TheWritableGlobalData`, defined once
// in Common/GlobalData.cpp.  In the linked build this TU must spell the global
// exactly that way or nothing defines it.
class GlobalData;
extern GlobalData *TheWritableGlobalData;

void *bfmeNowCBE();
void bfmeSetCBE(void *what, int value);

void __stdcall bfmeGoCBE(void *spare)
{
	if (TheWritableGlobalData != 0)
	{
		void *cur = ((BfmeGlobalCBE *)TheWritableGlobalData)->m_bfmeCur;
		if (bfmeNowCBE() != cur)
			bfmeSetCBE(cur, 6);
	}
}
