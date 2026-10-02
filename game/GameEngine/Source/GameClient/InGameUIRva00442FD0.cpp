// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// InGameUI lasso-aware drawable walk, retail 0x00442FD0 (380 B), reached only through ILT 0x00049F9E
// from the selection translator at VA 0x009B8AA0 with ECX = TheInGameUI; the spine is the Zero Hour
// W3DView::iterateDrawablesInRegion twin, so the method keeps an address-derived name.
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int Int;
typedef bool Bool;
typedef float Real;

#define NULL 0
#define TRUE true
#define FALSE false

struct ICoord2D
{
	Int x;
	Int y;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum PickType
{
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	unsigned char m_unmodelled_00[4];
	Overridable *m_nextOverride;
};

class Rva00132A20ThingMask
{
	unsigned int m_words[6];

public:
	bool rva00132a20(const Rva00132A20ThingMask &) const;
};

class ThingTemplate
{
	unsigned char m_unmodelled_00[0xc8];
	Rva00132A20ThingMask m_kindof;

public:
	Bool isAnyKindOf(const Rva00132A20ThingMask &anyKindOf) const { return m_kindof.rva00132a20(anyKindOf); }
};

struct Rva0087DC00Vec
{
	Real x;
	Real y;
	Real z;
};

class Rva0087DC00
{
public:
	void get(Rva0087DC00Vec *out);
};

class BfmeThingJA
{
public:
	int bfmeGoJA();
};

struct BfmeLinearCoord3D
{
	Real x;
	Real y;
	Real z;
};

class BFMERopeDrawableGetPositionShim
{
public:
	const BfmeLinearCoord3D *getPositionLinear() const;
};

class Drawable
{
public:
	const ThingTemplate *getTemplate() const
	{
		const Overridable *tmpl = m_template;
		if (tmpl && tmpl->m_nextOverride)
			tmpl = tmpl->m_nextOverride->getFinalOverride();
		return (const ThingTemplate *)tmpl;
	}
	Rva0087DC00 *getGeometryInfo() { return (Rva0087DC00 *)((BfmeThingJA *)this)->bfmeGoJA(); }
	const BfmeLinearCoord3D *getPosition() const { return ((const BFMERopeDrawableGetPositionShim *)this)->getPositionLinear(); }
	Drawable *getNextDrawable() const { return m_nextDrawable; }

private:
	unsigned char m_unmodelled_00[4];
	Overridable *m_template;
	unsigned char m_unmodelled_08[0x104 - 8];
	Drawable *m_nextDrawable;
};

class BfmeKindOfMask
{
public:
	unsigned int m_words[6];
};

// Names follow the landed PickDrawableStructConstructor.cpp; the walk skips m_reservedMask kinds.
struct PickDrawableStruct
{
	void *drawableListToFill;
	bool forceAttackMode;
	unsigned char m_reserved;
	unsigned char m_padding06[2];
	BfmeKindOfMask kindofsToMatch;
	BfmeKindOfMask m_reservedMask;
};

class ClientRoot4120
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual Drawable *firstDrawable() = 0;
};

#define VIEW_SLOT(n) virtual void viewSlot##n();
class View
{
public:
	VIEW_SLOT(0) VIEW_SLOT(1) VIEW_SLOT(2) VIEW_SLOT(3)
	VIEW_SLOT(4) VIEW_SLOT(5) VIEW_SLOT(6) VIEW_SLOT(7)
	VIEW_SLOT(8)
	virtual Drawable *pickDrawable(const ICoord2D *screen, Bool forceAttack, PickType pickType);	// slot 9
	VIEW_SLOT(10) VIEW_SLOT(11)
	VIEW_SLOT(12) VIEW_SLOT(13) VIEW_SLOT(14) VIEW_SLOT(15)
	VIEW_SLOT(16) VIEW_SLOT(17) VIEW_SLOT(18) VIEW_SLOT(19)
	VIEW_SLOT(20) VIEW_SLOT(21) VIEW_SLOT(22) VIEW_SLOT(23)
	VIEW_SLOT(24) VIEW_SLOT(25) VIEW_SLOT(26) VIEW_SLOT(27)
	VIEW_SLOT(28) VIEW_SLOT(29) VIEW_SLOT(30) VIEW_SLOT(31)
	VIEW_SLOT(32) VIEW_SLOT(33) VIEW_SLOT(34) VIEW_SLOT(35)
	VIEW_SLOT(36) VIEW_SLOT(37) VIEW_SLOT(38) VIEW_SLOT(39)
	VIEW_SLOT(40) VIEW_SLOT(41) VIEW_SLOT(42) VIEW_SLOT(43)
	VIEW_SLOT(44) VIEW_SLOT(45) VIEW_SLOT(46) VIEW_SLOT(47)
	VIEW_SLOT(48) VIEW_SLOT(49) VIEW_SLOT(50) VIEW_SLOT(51)
	VIEW_SLOT(52) VIEW_SLOT(53) VIEW_SLOT(54) VIEW_SLOT(55)
	VIEW_SLOT(56) VIEW_SLOT(57) VIEW_SLOT(58) VIEW_SLOT(59)
	VIEW_SLOT(60) VIEW_SLOT(61) VIEW_SLOT(62) VIEW_SLOT(63)
	VIEW_SLOT(64) VIEW_SLOT(65) VIEW_SLOT(66) VIEW_SLOT(67)
	VIEW_SLOT(68) VIEW_SLOT(69) VIEW_SLOT(70) VIEW_SLOT(71)
	VIEW_SLOT(72) VIEW_SLOT(73) VIEW_SLOT(74) VIEW_SLOT(75)
	VIEW_SLOT(76) VIEW_SLOT(77) VIEW_SLOT(78) VIEW_SLOT(79)
	VIEW_SLOT(80) VIEW_SLOT(81) VIEW_SLOT(82) VIEW_SLOT(83)
	VIEW_SLOT(84) VIEW_SLOT(85) VIEW_SLOT(86)
	virtual Int worldToScreenTriReturn(const Coord3D *world, ICoord2D *screen);	// slot 87
};
#undef VIEW_SLOT

// Retail 0x012F1464 is EA's GameClient *TheGameClient, defined once in
// game/GameEngine/Source/GameClient/GameClient.cpp.  ClientRoot4120 is a
// TU-local view of that object reached through the canonical global.
class GameClient;
extern GameClient *TheGameClient;
static inline ClientRoot4120 *theClientRoot4120( void )
{
	return (ClientRoot4120 *)TheGameClient;
}
extern View *TheTacticalView;
extern int Rva00459060(bool forceAttackMode);

struct Payload0044B800_1304 { unsigned int first, second; };

// Layout names follow the landed InGameUIConstructor.cpp view; 0x0043E260 is the lasso point test.
class InGameUI
{
public:
	Int rva00442fd0(Bool (*callback)(Drawable *draw, void *userData), void *userData);
	Bool rva0043e260(const ICoord2D *screen);
	Bool isInForceAttackMode() const { return m_field_12b1; }

private:
	unsigned char m_unmodelled_00[0x12b1];
	bool m_field_12b1; // +0x12b1
	unsigned char m_unmodelled_12b2[0x1304 - 0x12b2];
	_STL::list<Payload0044B800_1304> m_list_1304; // +0x1304
	Int m_field_1308; // +0x1308
	Int m_field_130c; // +0x130c
	Int m_field_1310; // +0x1310
	Int m_field_1314; // +0x1314
};

Int InGameUI::rva00442fd0(Bool (*callback)(Drawable *draw, void *userData), void *userData)
{
	Bool inside = FALSE;
	Int count = 0;
	Drawable *draw;
	Coord3D pos;
	ICoord2D screen;

	Bool regionIsPoint = FALSE;
	if (m_list_1304.size() < 3 || (m_field_1314 - m_field_130c == 0 && m_field_1310 - m_field_1308 == 0))
	{
		regionIsPoint = TRUE;
	}

	Drawable *onlyDrawableToTest = NULL;
	if (regionIsPoint)
	{
		onlyDrawableToTest = TheTacticalView->pickDrawable((const ICoord2D *)&m_field_1308, TRUE, (PickType)Rva00459060(isInForceAttackMode()));
		if (onlyDrawableToTest == NULL)
		{
			return 0;
		}
	}

	for (draw = theClientRoot4120()->firstDrawable(); draw; draw = draw->getNextDrawable())
	{
		if (onlyDrawableToTest)
		{
			draw = onlyDrawableToTest;
			inside = TRUE;
		}
		else
		{
			inside = FALSE;
			if (!draw->getTemplate()->isAnyKindOf(*(const Rva00132A20ThingMask *)&((PickDrawableStruct *)userData)->m_reservedMask))
			{
				draw->getGeometryInfo()->get((Rva0087DC00Vec *)&pos);
				const BfmeLinearCoord3D *drawPos = draw->getPosition();
				pos.x += drawPos->x;
				pos.y += drawPos->y;
				pos.z += drawPos->z;
				TheTacticalView->worldToScreenTriReturn(&pos, &screen);
				if (rva0043e260(&screen))
				{
					inside = TRUE;
				}
			}
		}

		if (inside)
		{
			if (callback(draw, userData))
			{
				++count;
			}
		}

		if (onlyDrawableToTest != NULL)
		{
			break;
		}
	}

	return count;
}
