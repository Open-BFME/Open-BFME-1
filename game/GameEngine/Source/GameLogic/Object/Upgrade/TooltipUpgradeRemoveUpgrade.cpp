// TooltipUpgrade::removeUpgrade at retail 0x002D9570: slot 7 of the UpgradeMux table 0x010CE1A0, reached
// only through ILT 0x00036750 (its VA appears once in the image). TooltipUpgrade's registered
// constructor 0x002D93E0 stores that table. Slot 7 is
// EA's removeUpgrade (BFME2/RotWK WorldBuilder labels, matching slot), which undoes
// slot 9 (upgradeImplementation). Evidence:
// targets/game/reverse/identity_evidence/upgrademux-slot7-removeupgrade.md and
// targets/game/reverse/identity_evidence/upgrademux-slot7-owner-names.md

// Open-BFME5 conversions.

struct BfmeStateUYA
{
	char m_bfmePad[0x24];
	char m_bfmeDirty;
};

class ControlBar;

extern ControlBar *TheControlBar;

// The record's +0x2D4/+0x2D8 members are narrow strings: retail's body calls
// StringBase<char>::releaseBuffer (0x00887940) on each, which is what
// StringBase<char>::clear() is, so the placeholder bfmeClearUYA is spelled as
// the real StringBase<char>, viewed through a local POD because StringBase's
// default constructor is private.
#include "../../../../../Libraries/Source/WWVegas/WWLib/string_base.h"

struct BfmeStrUYA
{
	void *m_bfmePad;
};

class BfmeRecUYA
{
public:
	char m_bfmePad[0x2d4];
	BfmeStrUYA m_bfmeA;
	BfmeStrUYA m_bfmeB;
};

class BfmeOwnerUYA
{
public:
	virtual void bfmeV0UYA() = 0;
	virtual void bfmeV1UYA() = 0;
	virtual void bfmeV2UYA() = 0;
	virtual void bfmeV3UYA() = 0;
	virtual void bfmeV4UYA() = 0;
	virtual void bfmeV5UYA() = 0;
	virtual void bfmeV6UYA() = 0;
	virtual void bfmeV7UYA() = 0;
	virtual void bfmeV8UYA() = 0;
	virtual void bfmeV9UYA() = 0;
	virtual BfmeRecUYA *bfmeFindUYA() = 0;
};

class TooltipUpgrade
{
public:
	virtual char bfmeCheckUYA() = 0;
	virtual void bfmeW1UYA() = 0;
	virtual void bfmeW2UYA() = 0;
	virtual void bfmeW3UYA() = 0;
	virtual void bfmeW4UYA() = 0;
	virtual void bfmeW5UYA() = 0;
	virtual void bfmeW6UYA() = 0;
	virtual void bfmeW7UYA() = 0;
	virtual void bfmeFinishUYA(int f) = 0;
public:
	virtual void removeUpgrade();
};

void TooltipUpgrade::removeUpgrade()
{
	if (!bfmeCheckUYA())
		return;
	BfmeRecUYA *r = (*(BfmeOwnerUYA **)((char *)this - 8))->bfmeFindUYA();
	if (r) {
		((StringBase<char> *)&r->m_bfmeA)->clear();
		((StringBase<char> *)&r->m_bfmeB)->clear();
		((BfmeStateUYA *)TheControlBar)->m_bfmeDirty = 1;
	}
	bfmeFinishUYA(0);
}
