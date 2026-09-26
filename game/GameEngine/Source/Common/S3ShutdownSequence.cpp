// Retail 0x00510B50, 80 bytes, split by the ledger before its final delete --
// the same eleven-byte expansion that 0x00510B20 and 0x005F3140 also end with,
// and the same global they delete.
//
// Three releases in a row, each guarded by its own sentinel and each writing
// that sentinel back afterwards. The first two sentinels differ in what
// "empty" means: a null pointer for the first, -1 for the second, which is why
// the second is reset to -1 rather than zeroed.
//
// The first release goes through vtable slot 10 of one global with the value
// as its argument; the second through a named member of another; the third is
// a plain delete, whose null test and slot 0 call with an argument of 1 are
// generated rather than written.

class Glo00EF19E8
{
public:
	void h0046B2B0(int handle);					// ILT 0x00033857
};

class BfmeReleaseSink
{
public:
	virtual void bfmeSlot00(void) = 0;
	virtual void bfmeSlot04(void) = 0;
	virtual void bfmeSlot08(void) = 0;
	virtual void bfmeSlot0C(void) = 0;
	virtual void bfmeSlot10(void) = 0;
	virtual void bfmeSlot14(void) = 0;
	virtual void bfmeSlot18(void) = 0;
	virtual void bfmeSlot1C(void) = 0;
	virtual void bfmeSlot20(void) = 0;
	virtual void bfmeSlot24(void) = 0;
	virtual void bfmeRelease(void *resource) = 0;			// +0x28
};

class BfmeDeletable
{
public:
	virtual ~BfmeDeletable();
};

extern void *TheBfmeHeldResource;					// 0x012F4974
extern BfmeReleaseSink *TheBfmeReleaseSink;				// 0x012F12CC
extern int TheBfmeHeldHandle;						// 0x012B7430
extern Glo00EF19E8 *TheBfmeHandleOwner;					// 0x012F19E8
extern BfmeDeletable *TheBfmeCampaignManager;				// 0x012F49D0

// ?Gen_00510b50@@YAXXZ
void Gen_00510b50(void)
{
	if (TheBfmeHeldResource)
	{
		TheBfmeReleaseSink->bfmeRelease(TheBfmeHeldResource);

		TheBfmeHeldResource = 0;
	}

	if (TheBfmeHeldHandle != -1)
	{
		TheBfmeHandleOwner->h0046B2B0(TheBfmeHeldHandle);

		TheBfmeHeldHandle = -1;
	}

	delete TheBfmeCampaignManager;
}
