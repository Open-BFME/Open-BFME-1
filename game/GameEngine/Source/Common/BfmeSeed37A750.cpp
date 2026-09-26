// cl: /DNDEBUG /MD /EHs-c-

struct BfmeVersionBlock
{
	unsigned char m_bfmeKind;
	unsigned char m_bfmeVersion;
};

class BfmeSeedTarget
{
public:
	virtual void bfmeSlot0(void);
	virtual void bfmeSlot1(void);
	virtual void bfmeSlot2(void);
	virtual void bfmeSlot3(void);
	virtual bool bfmeAskAt10(void);
	virtual void bfmeSlot5(void);
	virtual void bfmeSlot6(void);
	virtual void bfmeSlot7(void);
	virtual void bfmeSlot8(void);
	virtual void bfmeSlot9(void);
	virtual BfmeSeedTarget *bfmeSeed(BfmeVersionBlock *version);
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
	virtual BfmeSeedTarget *bfmeTakeAt6C(void *item);
	virtual void bfmeSlot28(void);
	virtual void bfmeSlot29(void);
	virtual void bfmeSlot30(void);
	virtual void bfmeSlot31(void);
	virtual void bfmeSlot32(void);
	virtual void bfmeSlot33(void);
	virtual void bfmeSlot34(void);
	virtual BfmeSeedTarget *bfmeTakeAt8C(void *item);
};

class Gen_0037A750
{
public:
	void bfmeSeed(BfmeSeedTarget *target);

private:
	char m_pad00[4];
	int m_item04;
	int m_item08;
	int m_item0C;
};

void Gen_0037A750::bfmeSeed(BfmeSeedTarget *target)
{
	if (target->bfmeAskAt10())
		return;
	BfmeVersionBlock version;
	version.m_bfmeKind = 1;
	version.m_bfmeVersion = 1;
	target = target->bfmeSeed(&version);
	target = target->bfmeTakeAt6C(&m_item04);
	target = target->bfmeTakeAt6C(&m_item08);
	target->bfmeTakeAt8C(&m_item0C);
}
