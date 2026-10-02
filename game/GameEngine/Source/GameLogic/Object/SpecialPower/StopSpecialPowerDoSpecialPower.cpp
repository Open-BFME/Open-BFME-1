// cl: /DNDEBUG /MD /EHsc
// StopSpecialPower::doSpecialPower at retail 0x0026B3C0 (35 B): slot 11 of the
// SpecialPowerModuleInterface table 0x010B8180, which the registered
// StopSpecialPower constructor 0x0026B340 stores at +0x10. It is reached only
// through ILT 0x00035413, whose VA appears once in the image.
// Object::doSpecialPower (0x001C3790) calls slot 11 (+0x2C); the body ends `ret 4`.
// Evidence: targets/game/reverse/identity_evidence/specialpower-slot11-12-dospecialpower.md
//
// Moved from BfmeTwoHundredOne.cpp with its private views. The guard calls
// interface slot 1 (Zero Hour's isReady); the names below stay as they were.

typedef unsigned int UnsignedInt;

class BfmeOtherGJ
{
public:
	virtual void bfmeSpare000GJ(void) = 0;
	virtual void bfmeSpare001GJ(void) = 0;
	virtual void bfmeSpare002GJ(void) = 0;
	virtual void bfmeSpare003GJ(void) = 0;
	virtual void bfmeSpare004GJ(void) = 0;
	virtual void bfmeSpare005GJ(void) = 0;
	virtual void bfmeSpare006GJ(void) = 0;
	virtual void bfmeSpare007GJ(void) = 0;
	virtual void bfmeSpare008GJ(void) = 0;
	virtual void bfmeSpare009GJ(void) = 0;
	virtual void bfmeSpare010GJ(void) = 0;
	virtual void bfmeSpare011GJ(void) = 0;
	virtual void bfmeSpare012GJ(void) = 0;
	virtual void bfmeSpare013GJ(void) = 0;
	virtual void bfmeSpare014GJ(void) = 0;
	virtual void bfmeSpare015GJ(void) = 0;
	virtual void bfmeSpare016GJ(void) = 0;
	virtual void bfmeSpare017GJ(void) = 0;
	virtual void bfmeSpare018GJ(void) = 0;
	virtual void bfmeSpare019GJ(void) = 0;
	virtual void bfmeSpare020GJ(void) = 0;
	virtual void bfmeDoGJ(void) = 0;
};

class BfmeSubGJ
{
public:
	virtual void bfmeSpare000GK(void);
	virtual void bfmeSpare001GK(void);
	virtual void bfmeSpare002GK(void);
	virtual void bfmeSpare003GK(void);
	virtual void bfmeSpare004GK(void);
	virtual void bfmeSpare005GK(void);
	virtual void bfmeSpare006GK(void);
	virtual BfmeOtherGJ *bfmeMakeGJ(void);
};

struct BfmeItemGJ
{
	unsigned char m_bfmeHead[0xc];		// 0x0
	BfmeSubGJ m_bfmeSub;			// 0xc
};

class StopSpecialPower
{
public:
	virtual void bfmeSpare000GJ(void) = 0;
	virtual unsigned char bfmeAskGJ(void) = 0;

	virtual void doSpecialPower(UnsignedInt commandOptions);

private:
	unsigned char m_bfmeHead[0x18];		// 0x04
	BfmeItemGJ *m_bfmeItem;			// 0x1c
};

void StopSpecialPower::doSpecialPower(UnsignedInt)
{
	if (bfmeAskGJ() == 0)
		return;

	BfmeOtherGJ *other = m_bfmeItem->m_bfmeSub.bfmeMakeGJ();

	other->bfmeDoGJ();
}
