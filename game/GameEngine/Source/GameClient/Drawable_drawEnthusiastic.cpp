// cl: /DNDEBUG /MD /EHsc
// stlport
//
// Drawable::drawEnthusiastic, retail RVA 0x0041A780, 511 bytes (two plain
// `ret` exits). The matched Drawable::drawIconUI (0x00420AC0) calls it in its
// icon group 1, and tools/ilt_oracle.py CONFIRMS ?drawEnthusiastic@Drawable@@AAEXXZ
// at its ILT 0x0003D514: BFME takes no health-bar region argument and reads
// the drawable's own region at +0x3C4, as drawBombed and drawHealing do.
// Otherwise the body is Zero Hour's (GameClient/Drawable.cpp, including its
// `testWeaponBonusCondition(...) == TRUE` tests): weapon-bonus bit 8 picks
// icon 11, or icon 12 when bit 15 is also set (Zero Hour's ENTHUSIASTIC and
// SUBLIMINAL pair; BFME's numbering differs, so the bits stay numeric); the
// icon is sized by KindOf 7 (structure) or 13 (1.0), 9 (0.75) or 0.5; otherwise
// both icons are killed. BFME draws at the region's hi.y.

#include "../../Include/Common/ScalarTypes.h"


class Anim2DTemplate;
class Anim2DCollection;

class Anim2D
{
public:
	Anim2D(Anim2DTemplate *iconTemplate, Anim2DCollection *collection);
	virtual ~Anim2D();
	UnsignedInt getCurrentFrameWidth() const;
	UnsignedInt getCurrentFrameHeight() const;
	void draw(int x, int y, int width, int height);

	void deleteInstance() { delete this; }

private:
	unsigned char m_unmodelled[0x30];
};

class DrawableIconInfo
{
public:
	virtual ~DrawableIconInfo();
	Anim2D *m_icon[14];
	UnsignedInt m_keepTillFrame[14];

	void killIcon(int t)
	{
		if (m_icon[t])
		{
			m_icon[t]->deleteInstance();
			m_icon[t] = 0;
			m_keepTillFrame[t] = 0;
		}
	}
};

extern Anim2DCollection *TheAnim2DCollection;

#include "../../Include/Common/Enums/KindOfType.h"




class Thing
{
public:
	bool isKindOf(KindOfType t) const;
};

class Drawable : public Thing
{
private:
	static Anim2DTemplate **s_animationTemplates;
	void drawEnthusiastic();
};

// Retail ILT 0x000102A8 reaches the matched 0x00410F10 lazy allocation body.
class Rva00410F10Allocation;
class Rva00410F10Owner
{
public:
	Rva00410F10Allocation *ensure();
};

static inline DrawableIconInfo *getIconInfo(Drawable *drawable)
{
	return reinterpret_cast<DrawableIconInfo *>(
		reinterpret_cast<Rva00410F10Owner *>(drawable)->ensure());
}

#include "../../../Libraries/Include/Lib/ICoord2D.h"

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

struct BfmeDrawableEnthusiasticFields
{
	unsigned char m_unmodelled_000[0xFC];
	void *m_object;
	unsigned char m_unmodelled_100[0x1E0];
	DrawableIconInfo *m_iconInfo;				// +0x2E0
	unsigned char m_unmodelled_2E4[0xE0];
	IRegion2D m_healthBarRegion;				// +0x3C4
};

struct BfmeDrawableEnthusiasticObjectFields
{
	unsigned char m_unmodelled_000[0x2A0];
	UnsignedInt m_weaponBonusCondition;		// +0x2A0
	bool testWeaponBonusCondition(int c) const { return (m_weaponBonusCondition & (1 << c)) != 0; }
};

void Drawable::drawEnthusiastic()
{
	BfmeDrawableEnthusiasticFields *self = (BfmeDrawableEnthusiasticFields *)this;
	const BfmeDrawableEnthusiasticObjectFields *obj =
		(const BfmeDrawableEnthusiasticObjectFields *)self->m_object;

	if (obj->testWeaponBonusCondition(8) == true)
	{
		int iconIndex = 11;
		if (obj->testWeaponBonusCondition(15) == true)
			iconIndex = 12;

		if (getIconInfo(this)->m_icon[iconIndex] == 0)
			getIconInfo(this)->m_icon[iconIndex] = new Anim2D(
				s_animationTemplates[iconIndex], TheAnim2DCollection);

		if (getIconInfo(this)->m_icon[iconIndex] != 0)
		{
			const IRegion2D *healthBarRegion = &self->m_healthBarRegion;
			int barWidth = healthBarRegion->hi.x - healthBarRegion->lo.x;

			Real scale;
			if (isKindOf(KINDOF_STRUCTURE) || isKindOf((KindOfType)13))
				scale = 1.00f;
			else if (isKindOf((KindOfType)9))
				scale = 0.75f;
			else
				scale = 0.5f;

			int frameWidth = getIconInfo(this)->m_icon[iconIndex]->getCurrentFrameWidth() * scale;
			int frameHeight = getIconInfo(this)->m_icon[iconIndex]->getCurrentFrameHeight() * scale;

			ICoord2D screen;
			screen.x = (int)(healthBarRegion->lo.x + (barWidth * 0.25f) - (frameWidth * 0.5f));
			screen.y = healthBarRegion->hi.y;
			getIconInfo(this)->m_icon[iconIndex]->draw(screen.x, screen.y, frameWidth, frameHeight);
		}
	}
	else
	{
		if (self->m_iconInfo)
			self->m_iconInfo->killIcon(11);
		if (self->m_iconInfo)
			self->m_iconInfo->killIcon(12);
	}
}
