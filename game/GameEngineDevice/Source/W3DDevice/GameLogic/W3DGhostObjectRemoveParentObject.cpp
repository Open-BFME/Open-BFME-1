// Open-BFME5 host-object parent sweep.
//
// The body is the BFME rebuild of W3DGhostObject::removeParentObject (the
// symbols.csv pin ?removeParentObject@W3DGhostObject@@IAEXXZ at 0x006BC750,
// reached from the matched setLocalPlayerIndex caller). BFME replaced the
// Drawable graph with its own A/B/M handle chain, so the offsets are the
// BFME ones this file declares, not the W3DGhostObject layout.
//
// Byte note -- the loop head sits at +0x29, which is 9 mod 16. MSVC 7.1's
// loop-head aligner pads a head whose misalignment is 1..7 bytes (mod16
// 9..15) and leaves one needing 8..15 bytes alone, so the plain `while` form
// picks up a 7-byte `lea esp,[esp]` and lands 79 bytes wide. Re-testing the
// element pointer inside the body gives the optimizer a reason to redo the
// loop's shape after the aligner has run, and the head stays at +0x29 with no
// pad -- 72 bytes, matching retail instruction for instruction.

class BfmeBBP;
class BfmeUBM;
class BfmeItemBP;

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

class BfmeItemBP
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
	virtual BfmeUBM *bfmeGetBP();
};

class BfmeBBP
{
public:
	void bfmeSetBP(int mode);
	BfmeItemBP **bfmeListBP();
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
	virtual BfmeBBP *bfmeMakeBP();
};

class W3DGhostObject
{
protected:
	void removeParentObject();

	unsigned char m_bfmeHeadBM[0xc];	// 0x000
	BfmeABM *m_bfmeABM;		// 0x00c
};

void W3DGhostObject::removeParentObject()
{
	if (m_bfmeABM == 0)
		return;

	BfmeBBP *b = m_bfmeABM->bfmeMakeBP();

	b->bfmeSetBP(1);

	BfmeItemBP **p = b->bfmeListBP();

	while (*p != 0)
	{
		BfmeItemBP *item = *p;

		if (item != 0)
		{
			BfmeUBM *u = item->bfmeGetBP();

			if (u != 0)
				u->bfmeStopBM();
		}

		p++;
	}
}
