// ?bfmeTailA1044@BfmeB1044@@QAEXXZ
// partial score=0.8 date=2026-09-08
// Identity evidence: the 0x00006E83 thunk jumps to retail 0x004B0850,
// and BfmeB1044::bfmeGo1044B at 0x004B17E0 selects that thunk for nonzero IDs.

#include <stdlib.h>
#pragma intrinsic(abs)

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct ICoord2D
{
	int x;
	int y;
};

class Drawable
{
public:
	const Coord3D *getPosition(void) const;
};

class GeometryInfo
{
public:
	float getMaxHeightAbovePosition(void) const;
};

class Object
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
	virtual Drawable *getDrawable(void) const = 0;
	bool getWorldspaceBestContactPoint(Coord3D *pointOut,
		const Coord3D *callerPos, const char *label, int preference,
		int seed, bool skipCollideTest) const;
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

class View
{
public:
#define BFME_VIEW_SLOT(n) virtual void slot##n(void) = 0;
	BFME_VIEW_SLOT(00) BFME_VIEW_SLOT(01) BFME_VIEW_SLOT(02)
	BFME_VIEW_SLOT(03) BFME_VIEW_SLOT(04) BFME_VIEW_SLOT(05)
	BFME_VIEW_SLOT(06) BFME_VIEW_SLOT(07) BFME_VIEW_SLOT(08)
	BFME_VIEW_SLOT(09) BFME_VIEW_SLOT(10) BFME_VIEW_SLOT(11)
	BFME_VIEW_SLOT(12) BFME_VIEW_SLOT(13) BFME_VIEW_SLOT(14)
	BFME_VIEW_SLOT(15) BFME_VIEW_SLOT(16) BFME_VIEW_SLOT(17)
	BFME_VIEW_SLOT(18) BFME_VIEW_SLOT(19) BFME_VIEW_SLOT(20)
	BFME_VIEW_SLOT(21) BFME_VIEW_SLOT(22) BFME_VIEW_SLOT(23)
	BFME_VIEW_SLOT(24) BFME_VIEW_SLOT(25) BFME_VIEW_SLOT(26)
	BFME_VIEW_SLOT(27) BFME_VIEW_SLOT(28) BFME_VIEW_SLOT(29)
	BFME_VIEW_SLOT(30) BFME_VIEW_SLOT(31) BFME_VIEW_SLOT(32)
	BFME_VIEW_SLOT(33) BFME_VIEW_SLOT(34) BFME_VIEW_SLOT(35)
	BFME_VIEW_SLOT(36) BFME_VIEW_SLOT(37) BFME_VIEW_SLOT(38)
	BFME_VIEW_SLOT(39) BFME_VIEW_SLOT(40) BFME_VIEW_SLOT(41)
	BFME_VIEW_SLOT(42) BFME_VIEW_SLOT(43) BFME_VIEW_SLOT(44)
	BFME_VIEW_SLOT(45) BFME_VIEW_SLOT(46) BFME_VIEW_SLOT(47)
	BFME_VIEW_SLOT(48) BFME_VIEW_SLOT(49) BFME_VIEW_SLOT(50)
	BFME_VIEW_SLOT(51) BFME_VIEW_SLOT(52) BFME_VIEW_SLOT(53)
	BFME_VIEW_SLOT(54) BFME_VIEW_SLOT(55) BFME_VIEW_SLOT(56)
	BFME_VIEW_SLOT(57) BFME_VIEW_SLOT(58) BFME_VIEW_SLOT(59)
	BFME_VIEW_SLOT(60) BFME_VIEW_SLOT(61) BFME_VIEW_SLOT(62)
	BFME_VIEW_SLOT(63) BFME_VIEW_SLOT(64) BFME_VIEW_SLOT(65)
	BFME_VIEW_SLOT(66) BFME_VIEW_SLOT(67) BFME_VIEW_SLOT(68)
	BFME_VIEW_SLOT(69) BFME_VIEW_SLOT(70) BFME_VIEW_SLOT(71)
	BFME_VIEW_SLOT(72) BFME_VIEW_SLOT(73) BFME_VIEW_SLOT(74)
	BFME_VIEW_SLOT(75) BFME_VIEW_SLOT(76) BFME_VIEW_SLOT(77)
	BFME_VIEW_SLOT(78) BFME_VIEW_SLOT(79) BFME_VIEW_SLOT(80)
	BFME_VIEW_SLOT(81) BFME_VIEW_SLOT(82) BFME_VIEW_SLOT(83)
	BFME_VIEW_SLOT(84) BFME_VIEW_SLOT(85) BFME_VIEW_SLOT(86)
#undef BFME_VIEW_SLOT
	virtual int worldToScreen(const Coord3D *world, ICoord2D *screen) = 0;
};

#define TheGameLogic (*(GameLogic **)0x012F0898)
#define TheTacticalView (*(View **)0x012F1600)

extern void j_00034e91(void);

typedef bool (Object::*WorldspaceBestContactPointCall)(Coord3D *pointOut,
	const Coord3D *callerPos, const char *label, int preference, int seed,
	bool skipCollideTest) const;

__forceinline int bfmeAbs1044(int value)
{
	return abs(value);
}

__forceinline float bfmeHeight1044(bool hasContactPoint,
	const float *positionZ, const Object *object)
{
	if (hasContactPoint)
		return *positionZ;
	return reinterpret_cast<const GeometryInfo *>(
		reinterpret_cast<const char *>(object) + 0xAC)->getMaxHeightAbovePosition()
		* (*(const float *)0x0107533C);
}

class BfmeB1044
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	void bfmeTailA1044(void);

	char m_bfmePad[4];
	unsigned char m_bfmeFlag;
	char m_bfmePadAfterFlag[0x18 - 9];
	int m_bfme18;
	int m_bfme1c;
	int m_bfme20;
	int m_bfme24;
};

void BfmeB1044::bfmeTailA1044(void)
{
	Object *object = TheGameLogic->findObjectByID(m_bfme18);
	struct Locals
	{
		ICoord2D screen;
		Coord3D point;
		Coord3D position;
	} locals;

	if (object != 0)
	{
		Coord3D *const point = &locals.point;
		Coord3D *const position = &locals.position;
		float *positionZ = &position->z;
		Drawable *drawable = object->getDrawable();
		if (drawable != 0)
		{
			*point = *drawable->getPosition();
		}
		else
		{
			const Coord3D sourcePosition = *reinterpret_cast<const Coord3D *>(
				reinterpret_cast<const char *>(object) + 0x38);
			*point = sourcePosition;
		}

		position->x = 0.0f;
		position->y = 0.0f;
		position->z = 0.0f;
		union
		{
			void *asVoid;
			WorldspaceBestContactPointCall asMember;
		} contactPointCast;
		contactPointCast.asVoid = (void *)j_00034e91;
		bool hasContactPoint = (object->*contactPointCast.asMember)(
			position, position, reinterpret_cast<const char *>(0x010FD1D0), 0, 0, false);
		if (hasContactPoint)
		{
			position->x -= reinterpret_cast<const Coord3D *>(
				reinterpret_cast<const char *>(object) + 0x38)->x;
			position->y -= reinterpret_cast<const Coord3D *>(
				reinterpret_cast<const char *>(object) + 0x38)->y;
			*positionZ -= reinterpret_cast<const Coord3D *>(
				reinterpret_cast<const char *>(object) + 0x38)->z;
			volatile float *positionX = &position->x;
			point->x += *positionX;
			point->y += position->y;
		}
		point->z += bfmeHeight1044(hasContactPoint, positionZ, object);

		if (TheTacticalView->worldToScreen(point, &locals.screen))
		{
			locals.screen.x = -999;
			locals.screen.y = -999;
		}

		int delta = bfmeAbs1044(m_bfme24 - locals.screen.y);
		delta += bfmeAbs1044(m_bfme20 - locals.screen.x);
		if (delta > 2)
		{
			m_bfme20 = locals.screen.x;
			m_bfme24 = locals.screen.y;
			m_bfmeFlag = 1;
		}
	}
	else
	{
		locals.screen.x = -999;
		locals.screen.y = -999;
		slot04();
	}
}
