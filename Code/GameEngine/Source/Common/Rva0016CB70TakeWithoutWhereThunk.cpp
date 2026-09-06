// cl: /DNDEBUG /MD /EHsc
// Open-BFME: fuzzy-twin of BfmeThingKU::bfmeTakeKU / BfmeThingKX::bfmeTakeKX
// (retail 0x0016CB30 / near-twin dump base 0x0016DC00, both in
// Code/GameEngine/Source/Common/BfmeTwoHundredTwentyFour.cpp). Same "mark,
// ask whether it wants the held piece, make one if none yet, hand it over"
// shape and the same identical class layout/vtable slots, but retail's
// disassembly for this address never calls a fourth virtual (the twin's
// trailing `item->bfmeWhereKU(m_bfmeRest);`): the early-out branch
// (`item->bfmeIsKU() != 0` => return) jumps straight to the final
// pop/pop/pop/ret, and the taken path falls through to that same exit after
// the `bfmeHandKU` call -- there is no code for a fifth call or for the
// `m_bfmeRest` field at all. 120 retail bytes vs. the twin's 131 is exactly
// the size of that missing call (push m_bfmeRest; mov ecx; call [eax+addr]).
// Real ZH name unproven; lands under an address-derived name in the same
// class-home file as its twin, following the twin's own BfmeThingKU/KX
// naming.

struct BfmePairRva0016CB70
{
	unsigned char m_bfmeFirst;		// 0x0
	unsigned char m_bfmeSecond;		// 0x1
};

class BfmeItemRva0016CB70
{
public:
	virtual void bfmeSpare000(void) = 0;
	virtual void bfmeSpare001(void) = 0;
	virtual void bfmeSpare002(void) = 0;
	virtual void bfmeSpare003(void) = 0;
	virtual unsigned char bfmeIsRva0016CB70(void) = 0;
	virtual void bfmeSpare005(void) = 0;
	virtual void bfmeSpare006(void) = 0;
	virtual void bfmeSpare007(void) = 0;
	virtual void bfmeSpare008(void) = 0;
	virtual void bfmeSpare009(void) = 0;
	virtual void bfmeMarkRva0016CB70(BfmePairRva0016CB70 *both) = 0;
	virtual void bfmeSpare011(void) = 0;
	virtual void bfmeHandRva0016CB70(void *what) = 0;
	virtual void bfmeSpare013(void) = 0;
	virtual void bfmeSpare014(void) = 0;
	virtual void bfmeSpare015(void) = 0;
	virtual void bfmeSpare016(void) = 0;
	virtual void bfmeSpare017(void) = 0;
	virtual void bfmeSpare018(void) = 0;
	virtual void bfmeSpare019(void) = 0;
	virtual void bfmeSpare020(void) = 0;
	virtual void bfmeSpare021(void) = 0;
	virtual void bfmeSpare022(void) = 0;
	virtual void bfmeSpare023(void) = 0;
	virtual void bfmeSpare024(void) = 0;
	virtual void bfmeSpare025(void) = 0;
	virtual void bfmeSpare026(void) = 0;
	virtual void bfmeSpare027(void) = 0;
	virtual void bfmeSpare028(void) = 0;
	virtual void bfmeSpare029(void) = 0;
	virtual void bfmeSpare030(void) = 0;
	virtual void bfmeSpare031(void) = 0;
	virtual void bfmeSpare032(void) = 0;
	virtual void bfmeSpare033(void) = 0;
	virtual void bfmeSpare034(void) = 0;
	virtual void bfmeWantRva0016CB70(unsigned char *yes) = 0;
};

class BfmeMakerRva0016CB70
{
public:
	virtual void bfmeSpare000(void) = 0;
	virtual void bfmeSpare001(void) = 0;
	virtual void bfmeSpare002(void) = 0;
	virtual void bfmeSpare003(void) = 0;
	virtual void bfmeSpare004(void) = 0;
	virtual void bfmeSpare005(void) = 0;
	virtual void bfmeSpare006(void) = 0;
	virtual void bfmeSpare007(void) = 0;
	virtual void bfmeSpare008(void) = 0;
	virtual void *bfmeMakeRva0016CB70(void) = 0;
};

class BfmeThingRva0016CB70
{
public:
	void bfmeTakeRva0016CB70(BfmeItemRva0016CB70 *item);

private:
	unsigned char m_bfmeHead[0x1c];		// 0x00
	BfmeMakerRva0016CB70 *m_bfmeMaker;		// 0x1c
	unsigned char m_bfmeGap[4];		// 0x20
	void *m_bfmeHeld;			// 0x24
};

void BfmeThingRva0016CB70::bfmeTakeRva0016CB70(BfmeItemRva0016CB70 *item)
{
	if (item->bfmeIsRva0016CB70() != 0)
		return;

	BfmePairRva0016CB70 both;

	both.m_bfmeFirst = 1;
	both.m_bfmeSecond = 1;

	item->bfmeMarkRva0016CB70(&both);

	unsigned char yes = (unsigned char)(m_bfmeHeld != 0);

	item->bfmeWantRva0016CB70(&yes);

	if (yes != 0)
	{
		if (m_bfmeHeld == 0)
			m_bfmeHeld = m_bfmeMaker->bfmeMakeRva0016CB70();

		if (yes != 0)
			item->bfmeHandRva0016CB70(m_bfmeHeld);
	}
}
