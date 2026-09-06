// cl: /DNDEBUG /MD /EHs-c-

// Address-derived near-twin of ?bfmeSeed@Gen_002BEC60@@QAEXPAVBfmeSeedTarget@@@Z
// (Code/GameEngine/Source/Common/S3VersionBlocks.cpp). Same versioned
// hand-over shape, but the first hand-over goes through the free function
// bfmeCalcTGC(target, item) instead of target->bfmeTakeAt8C(item), and the
// two sub-object offsets swap (item0 at +0x28, item1 at +0x24 via TakeAt74
// instead of TakeAt78).

struct BfmeVersionBlock_14F220
{
	unsigned char m_bfmeKind;
	unsigned char m_bfmeVersion;
};

class BfmeSeedTarget_14F220
{
public:
	virtual void bfmeSlot0(void);
	virtual void bfmeSlot1(void);
	virtual void bfmeSlot2(void);
	virtual void bfmeSlot3(void);
	virtual bool bfmeAskAt10(void);		// slot 4, vtable+0x10
	virtual void bfmeSlot5(void);
	virtual void bfmeSlot6(void);
	virtual void bfmeSlot7(void);
	virtual void bfmeSlot8(void);
	virtual void bfmeTakeAt24(void *item, int size);		// slot 9, vtable+0x24
	virtual void bfmeSeed(BfmeVersionBlock_14F220 *version);		// slot 10, vtable+0x28
	virtual void bfmeSlot11(void);
	virtual void bfmeTakeAt30(void *held);		// slot 12, vtable+0x30
	virtual void bfmeSlot13(void);
	virtual void bfmeSlot14(void);
	virtual void bfmeSlot15(void);
	virtual void bfmeSlot16(void);
	virtual void bfmeSlot17(void);
	virtual void bfmeSlot18(void);
	virtual void bfmeTakeAt4C(void *item);		// slot 19, vtable+0x4C
	virtual void bfmeSlot20(void);
	virtual void bfmeSlot21(void);
	virtual void bfmeSlot22(void);
	virtual void bfmeSlot23(void);
	virtual void bfmeTakeAt60(void *item);		// slot 24, vtable+0x60
	virtual void bfmeSlot25(void);
	virtual void bfmeSlot26(void);
	virtual void bfmeTakeAt6C(void *item);		// slot 27, vtable+0x6C
	virtual void bfmeSlot28(void);
	virtual void bfmeTakeAt74(void *item);		// slot 29, vtable+0x74
};

void __cdecl bfmeCalcTGC(void *target, int *item);

class Gen_0014F220
{
public:
	void bfmeSeed(BfmeSeedTarget_14F220 *target);

private:
	char m_bfmePad0[0x24];
	char m_bfmeItem1;				// +0x24 (bfmeTakeAt74)
	char m_bfmePad1[0x3];
	char m_bfmeItem0;				// +0x28 (bfmeCalcTGC)
};

void Gen_0014F220::bfmeSeed(BfmeSeedTarget_14F220 *target)
{
	BfmeVersionBlock_14F220 version;

	version.m_bfmeKind = 1;
	version.m_bfmeVersion = 2;

	target->bfmeSeed(&version);
	bfmeCalcTGC(target, (int *)&m_bfmeItem0);
	if (version.m_bfmeVersion >= 2)
	{
		target->bfmeTakeAt74(&m_bfmeItem1);
	}
}
