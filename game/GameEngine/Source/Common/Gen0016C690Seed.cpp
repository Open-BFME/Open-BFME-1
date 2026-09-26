// Seeder body at retail RVA 0x0016C690.

struct BfmeSeedPair
{
	unsigned char m_bfmeFirst;
	unsigned char m_bfmeSecond;
};

class BfmeSeedTarget
{
public:
	virtual void bfmeSlot0(void);
	virtual bool bfmeSlot1(void);
	virtual void bfmeSlot2(void);
	virtual void bfmeSlot3(void);
	virtual bool bfmeSlot4(void);
	virtual void bfmeSlot5(void);
	virtual void bfmeSlot6(void);
	virtual void bfmeSlot7(void);
	virtual void bfmeSlot8(void);
	virtual void bfmeSlot9(void);
	virtual void bfmeSeed(BfmeSeedPair *pair);
	virtual void bfmeSlot11(void);
	virtual void bfmeSlot12(void);
	virtual void bfmeSlot13(void);
	virtual void bfmeSlot14(void);
	virtual void bfmeSlot15(void);
	virtual void bfmeSlot16(void);
	virtual void bfmeSlot17(void);
	virtual void bfmeSlot18(void);
	virtual void bfmeSlot19(void);
	virtual void bfmeSlot20(void);
	virtual void bfmeSlot21(void);
	virtual void bfmeSlot22(void);
	virtual void bfmeSlot23(void);
	virtual void bfmeSlot24(void);
	virtual void bfmeSlot25(void);
	virtual void bfmeSlot26(void);
	virtual void bfmeSlot27(void);
	virtual void bfmeSlot28(void);
	virtual void bfmeTakeAt74(void *item);
	virtual void bfmeSlot30(void);
	virtual void bfmeSlot31(void);
	virtual void bfmeSlot32(void);
	virtual void bfmeSlot33(void);
	virtual void bfmeSlot34(void);
	virtual void bfmeSlot35(void);
};

class TerrainLogic
{
public:
	virtual void bfmeTerrainSlot0(void);
	virtual void bfmeTerrainSlot1(void);
	virtual void bfmeTerrainSlot2(void);
	virtual void bfmeTerrainSlot3(void);
	virtual void bfmeTerrainSlot4(void);
	virtual void bfmeTerrainSlot5(void);
	virtual void bfmeTerrainSlot6(void);
	virtual void bfmeTerrainSlot7(void);
	virtual void bfmeTerrainSlot8(void);
	virtual void bfmeTerrainSlot9(void);
	virtual void bfmeTerrainSlot10(void);
	virtual void bfmeTerrainSlot11(void);
	virtual void bfmeTerrainSlot12(void);
	virtual void bfmeTerrainSlot13(void);
	virtual void bfmeTerrainSlot14(void);
	virtual void bfmeTerrainSlot15(void);
	virtual void bfmeTerrainSlot16(void);
	virtual void bfmeTerrainSlot17(void);
	virtual void bfmeTerrainSlot18(void);
	virtual void bfmeTerrainSlot19(void);
	virtual void bfmeTerrainSlot20(void);
	virtual void bfmeTerrainSlot21(void);
	virtual void bfmeTerrainSlot22(void);
	virtual void bfmeTerrainSlot23(void);
	virtual void bfmeTerrainSlot24(void);
	virtual void bfmeTerrainSlot25(void);
	virtual void bfmeTerrainSlot26(void);
	virtual void bfmeTerrainSlot27(void);
	virtual void bfmeTerrainSlot28(void);
	virtual void bfmeTerrainSlot29(void);
	virtual void bfmeTerrainSlot30(void);
	virtual void bfmeTerrainSlot31(void);
	virtual void *bfmeTerrainGet(int value);
};

extern TerrainLogic *TheTerrainLogic;

class Gen_0016C690;

class Gen_0016B250
{
	friend class Gen_0016C690;

	private:
	void bfmeAccept(BfmeSeedTarget *target);
};

class Gen_0016C690
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0x50];
	void *m_bfmeItem0;
};

// ?bfmeSeed@Gen_0016C690@@QAEXPAVBfmeSeedTarget@@@Z
void Gen_0016C690::bfmeSeed(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;

	pair.m_bfmeFirst = 1;
	pair.m_bfmeSecond = 1;

	target->bfmeSeed(&pair);
	((Gen_0016B250 *)this)->bfmeAccept(target);

	if ( !target->bfmeSlot4() )
	{
		int value = 0x7fffffff;
		if (m_bfmeItem0)
			value = *(int *)((char *)m_bfmeItem0 + 4);
		target->bfmeTakeAt74(&value);
		if (target->bfmeSlot1())
			m_bfmeItem0 = TheTerrainLogic->bfmeTerrainGet(value);
	}
}
