// ?bfmeAccept@Gen_0016C730@@AAEXPAVBfmeSeedTarget@@@Z

typedef unsigned char Bool;

struct BfmeSeedPair
{
	unsigned char first;
	unsigned char second;
};

class BfmeSeedTarget
{
public:
	virtual void slot00(void) = 0;
	virtual Bool slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual Bool bfmeSkip(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void bfmeSeed(BfmeSeedPair *pair) = 0;
	virtual void slot0b(void) = 0;
	virtual void slot0c(void) = 0;
	virtual void slot0d(void) = 0;
	virtual void slot0e(void) = 0;
	virtual void slot0f(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void bfmeTakeAt50(void *item) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot1a(void) = 0;
	virtual void bfmeTakeAt6C(void *item) = 0;
	virtual void slot1c(void) = 0;
	virtual void bfmeTakeAt74(void *item) = 0;
	virtual void bfmeTakeAt78(void *item) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual void slot23(void) = 0;
	virtual void bfmeTakeAt8C(void *item) = 0;
};

class TerrainLogic
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot0a(void) = 0;
	virtual void slot0b(void) = 0;
	virtual void slot0c(void) = 0;
	virtual void slot0d(void) = 0;
	virtual void slot0e(void) = 0;
	virtual void slot0f(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot1a(void) = 0;
	virtual void slot1b(void) = 0;
	virtual void slot1c(void) = 0;
	virtual void slot1d(void) = 0;
	virtual void slot1e(void) = 0;
	virtual void slot1f(void) = 0;
	virtual void *bfmeTerrainGet(int value) = 0;
};

#define TheTerrainLogic (*(TerrainLogic **)0x012EF4CC)

class Gen_0016B250;

class Gen_0016C730
{
private:
	void bfmeAccept(BfmeSeedTarget *target);

	char m_padding00[0x50];
	char m_item50;
	char m_padding51[0x07];
	char m_item58;
	char m_padding59[0x03];
	char m_item5c;
	void *m_item60;
	void *m_item64;
	char m_item68;
};

class Gen_0016B250
{
private:
	friend class Gen_0016C730;
	void bfmeAccept(BfmeSeedTarget *target);
};

void Gen_0016C730::bfmeAccept(BfmeSeedTarget *target)
{
	BfmeSeedPair pair;
	pair.first = 1;
	pair.second = 1;
	target->bfmeSeed(&pair);
	((Gen_0016B250 *)this)->bfmeAccept(target);

	if (target->bfmeSkip())
		return;

	target->bfmeTakeAt50(&m_item50);
	target->bfmeTakeAt6C(&m_item58);
	target->bfmeTakeAt78(&m_item5c);

	int value = 0x7fffffff;
	if (m_item60)
		value = *(int *)((char *)m_item60 + 4);
	target->bfmeTakeAt74(&value);
	if (target->slot01())
		m_item60 = TheTerrainLogic->bfmeTerrainGet(value);

	value = 0x7fffffff;
	if (m_item64)
		value = *(int *)((char *)m_item64 + 4);
	target->bfmeTakeAt74(&value);
	if (target->slot01())
		m_item64 = TheTerrainLogic->bfmeTerrainGet(value);

	target->bfmeTakeAt8C(&m_item68);
}
