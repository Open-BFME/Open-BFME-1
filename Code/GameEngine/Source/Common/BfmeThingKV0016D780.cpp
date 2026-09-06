// cl: /DNDEBUG /MD /EHsc
// Fuzzy-twin (r0.940) of ?bfmeTakeKU@BfmeThingKU@@QAEXPAVBfmeItemKU@@@Z in
// Code/GameEngine/Source/Common/BfmeTwoHundredTwentyFour.cpp: same item
// interface (bfmeIsKU@0x10, bfmeMarkKU@0x28, bfmeWantKU@0x8c,
// bfmeHandKU@0x30) and same BfmeThingKU field layout (m_bfmeMaker@0x1c,
// m_bfmeHeld@0x24), but two proven differences from the disassembly:
//   1. the maker interface's make call is at vtable slot 0x28, one slot
//      later than the twin's 0x24 -- one extra spare virtual before it.
//   2. this variant does not call item->bfmeWhereKU(m_bfmeRest) at the end
//      (twin's trailing add/push/call block at +0x72..+0x7c is absent; the
//      target is 120B vs the twin's 131B, an 11-byte/one-call difference).
// IDENTITY IS NOT RECOVERED: class/method names are address-derived.

struct BfmePairKV
{
	unsigned char m_bfmeFirst;		// 0x0
	unsigned char m_bfmeSecond;		// 0x1
};

class BfmeItemKV
{
public:
	virtual void bfmeSpare000KV(void) = 0;
	virtual void bfmeSpare001KV(void) = 0;
	virtual void bfmeSpare002KV(void) = 0;
	virtual void bfmeSpare003KV(void) = 0;
	virtual unsigned char bfmeIsKV(void) = 0;
	virtual void bfmeSpare005KV(void) = 0;
	virtual void bfmeSpare006KV(void) = 0;
	virtual void bfmeSpare007KV(void) = 0;
	virtual void bfmeSpare008KV(void) = 0;
	virtual void bfmeSpare009KV(void) = 0;
	virtual void bfmeMarkKV(BfmePairKV *both) = 0;
	virtual void bfmeSpare011KV(void) = 0;
	virtual void bfmeHandKV(void *what) = 0;
	virtual void bfmeSpare013KV(void) = 0;
	virtual void bfmeSpare014KV(void) = 0;
	virtual void bfmeSpare015KV(void) = 0;
	virtual void bfmeSpare016KV(void) = 0;
	virtual void bfmeSpare017KV(void) = 0;
	virtual void bfmeSpare018KV(void) = 0;
	virtual void bfmeSpare019KV(void) = 0;
	virtual void bfmeSpare020KV(void) = 0;
	virtual void bfmeSpare021KV(void) = 0;
	virtual void bfmeSpare022KV(void) = 0;
	virtual void bfmeSpare023KV(void) = 0;
	virtual void bfmeSpare024KV(void) = 0;
	virtual void bfmeSpare025KV(void) = 0;
	virtual void bfmeSpare026KV(void) = 0;
	virtual void bfmeSpare027KV(void) = 0;
	virtual void bfmeSpare028KV(void) = 0;
	virtual void bfmeSpare029KV(void) = 0;
	virtual void bfmeSpare030KV(void) = 0;
	virtual void bfmeSpare031KV(void) = 0;
	virtual void bfmeSpare032KV(void) = 0;
	virtual void bfmeSpare033KV(void) = 0;
	virtual void bfmeSpare034KV(void) = 0;
	virtual void bfmeWantKV(unsigned char *yes) = 0;
};

// one extra spare vs BfmeMakerKU: bfmeMakeKV lands at vtable slot 0x28.
class BfmeMakerKV
{
public:
	virtual void bfmeSpare000KV(void) = 0;
	virtual void bfmeSpare001KV(void) = 0;
	virtual void bfmeSpare002KV(void) = 0;
	virtual void bfmeSpare003KV(void) = 0;
	virtual void bfmeSpare004KV(void) = 0;
	virtual void bfmeSpare005KV(void) = 0;
	virtual void bfmeSpare006KV(void) = 0;
	virtual void bfmeSpare007KV(void) = 0;
	virtual void bfmeSpare008KV(void) = 0;
	virtual void bfmeSpare009KV(void) = 0;
	virtual void *bfmeMakeKV(void) = 0;
};

class BfmeThingKV0016D780
{
public:
	void bfmeTakeKV0016D780(BfmeItemKV *item);

private:
	unsigned char m_bfmeHead[0x1c];		// 0x00
	BfmeMakerKV *m_bfmeMaker;		// 0x1c
	unsigned char m_bfmeGap[4];		// 0x20
	void *m_bfmeHeld;			// 0x24
	unsigned char m_bfmeRest[4];		// 0x28
};

// ?d_0016d780@@YAXXZ
void BfmeThingKV0016D780::bfmeTakeKV0016D780(BfmeItemKV *item)
{
	if (item->bfmeIsKV() != 0)
		return;

	BfmePairKV both;

	both.m_bfmeFirst = 1;
	both.m_bfmeSecond = 1;

	item->bfmeMarkKV(&both);

	unsigned char yes = (unsigned char)(m_bfmeHeld != 0);

	item->bfmeWantKV(&yes);

	if (yes != 0)
	{
		if (m_bfmeHeld == 0)
			m_bfmeHeld = m_bfmeMaker->bfmeMakeKV();

		if (yes != 0)
			item->bfmeHandKV(m_bfmeHeld);
	}
}
