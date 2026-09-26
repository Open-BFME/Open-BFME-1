// ?bfmeShutBM@BfmeHostBM@@QAEXXZ (identity unknown)
// partial score=0.96 date=2026-09-07
// 79/72. Every instruction and operand matches. The ONLY difference is a
// 7-byte `lea esp,[esp]` alignment pad MSVC inserts at the loop head (0x6BC779
// -> 0x6BC780) that retail does not have. /G5 /G6 /G7 /Op all keep it; the
// while form instead of the for form keeps it too.
// There is a real fork here and BOTH halves are individually reachable, just
// not together:
//   * guard on the MEMBER (`if (m_bfmeABM == 0) return;` then use the member)
//     gives retail's head exactly -- mov eax,[ecx+0xc] / test eax,eax / je /
//     mov ecx,eax -- but MSVC then pads the loop: 79 bytes.
//   * guard on a NAMED LOCAL (`BfmeABM *a = m_bfmeABM; if (a == 0)`) removes
//     the pad but loads straight into ecx (mov ecx,[ecx+0xc]), losing the
//     2-byte `mov ecx,eax`: 70 bytes.
// Naming the local AFTER the member guard collapses back to the 70-byte form.
// See [[local-picks-ecx-receiver]] -- this is that lever seen from both sides.
// /Os and /O1 DO remove the pad (79 -> 67) but rewrite the head into
// `cmp dword ptr [ecx+0xc],0` plus a reload, so they are not the answer either.
// Data point from the sibling 0x006BC7B0, which lands EXACT at 90: its loop
// head sits 8 bytes below a 16-boundary and MSVC does not pad. Here the head
// sits 7 bytes below one and it does. So the threshold is <= 7, and the pad is
// decided by the head's ADDRESS -- meaning the only way out is an earlier
// byte-length change, not a loop-level rewrite.
class BfmeBBM;
class BfmeUBM;
class BfmeItemBM;

class BfmeUBM
{
public:
	virtual void bfmeSlot00U();
	virtual void bfmeSlot01U();
	virtual void bfmeSlot02U();
	virtual void bfmeSlot03U();
	virtual void bfmeSlot04U();
	virtual void bfmeSlot05U();
	virtual void bfmeSlot06U();
	virtual void bfmeSlot07U();
	virtual void bfmeSlot08U();
	virtual void bfmeSlot09U();
	virtual void bfmeSlot10U();
	virtual void bfmeSlot11U();
	virtual void bfmeSlot12U();
	virtual void bfmeSlot13U();
	virtual void bfmeSlot14U();
	virtual void bfmeSlot15U();
	virtual void bfmeStopBM();
};

class BfmeItemBM
{
public:
	virtual void bfmeSlot00I();
	virtual void bfmeSlot01I();
	virtual void bfmeSlot02I();
	virtual void bfmeSlot03I();
	virtual void bfmeSlot04I();
	virtual void bfmeSlot05I();
	virtual void bfmeSlot06I();
	virtual void bfmeSlot07I();
	virtual void bfmeSlot08I();
	virtual void bfmeSlot09I();
	virtual void bfmeSlot10I();
	virtual void bfmeSlot11I();
	virtual void bfmeSlot12I();
	virtual void bfmeSlot13I();
	virtual void bfmeSlot14I();
	virtual void bfmeSlot15I();
	virtual void bfmeSlot16I();
	virtual void bfmeSlot17I();
	virtual void bfmeSlot18I();
	virtual void bfmeSlot19I();
	virtual void bfmeSlot20I();
	virtual void bfmeSlot21I();
	virtual void bfmeSlot22I();
	virtual void bfmeSlot23I();
	virtual void bfmeSlot24I();
	virtual void bfmeSlot25I();
	virtual void bfmeSlot26I();
	virtual void bfmeSlot27I();
	virtual void bfmeSlot28I();
	virtual void bfmeSlot29I();
	virtual void bfmeSlot30I();
	virtual void bfmeSlot31I();
	virtual void bfmeSlot32I();
	virtual void bfmeSlot33I();
	virtual void bfmeSlot34I();
	virtual void bfmeSlot35I();
	virtual void bfmeSlot36I();
	virtual void bfmeSlot37I();
	virtual void bfmeSlot38I();
	virtual void bfmeSlot39I();
	virtual void bfmeSlot40I();
	virtual void bfmeSlot41I();
	virtual void bfmeSlot42I();
	virtual void bfmeSlot43I();
	virtual void bfmeSlot44I();
	virtual void bfmeSlot45I();
	virtual BfmeUBM *bfmeGetBM();
};

class BfmeBBM
{
public:
	void bfmeSetBM(int mode);
	BfmeItemBM **bfmeListBM();
};

class BfmeABM
{
public:
	virtual void bfmeSlot00A();
	virtual void bfmeSlot01A();
	virtual void bfmeSlot02A();
	virtual void bfmeSlot03A();
	virtual void bfmeSlot04A();
	virtual void bfmeSlot05A();
	virtual void bfmeSlot06A();
	virtual void bfmeSlot07A();
	virtual void bfmeSlot08A();
	virtual void bfmeSlot09A();
	virtual BfmeBBM *bfmeMakeBM();
};

class BfmeHostBM
{
public:
	void bfmeShutBM();

	unsigned char m_bfmeHeadBM[0xc];
	BfmeABM *m_bfmeABM;
};

void BfmeHostBM::bfmeShutBM()
{
	if (m_bfmeABM == 0)
		return;

	BfmeBBM *b = m_bfmeABM->bfmeMakeBM();

	b->bfmeSetBM(1);

	BfmeItemBM **p = b->bfmeListBM();

	while (*p != 0)
	{
		BfmeUBM *u = (*p)->bfmeGetBM();

		if (u != 0)
			u->bfmeStopBM();

		p++;
	}
}
