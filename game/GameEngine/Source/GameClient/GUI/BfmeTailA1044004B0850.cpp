// cl: 
// Button menu screen-position update with an address-qualified identity.
// Evidence: targets/game/reverse/identity_evidence/004b0850-screen-position.md

#include <stdlib.h>
#pragma intrinsic(abs)

#include "../../../../Libraries/Include/Lib/Coord3D.h"

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

#define BFME_HAVE_COORD3D
#define OBJECT_TU_MEMBERS bool getWorldspaceBestContactPoint(Coord3D *, const Coord3D *, const char *, int, int, bool) const;
#include "../../GameLogic/Object/object.h"
#undef OBJECT_TU_MEMBERS

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

extern GameLogic *TheGameLogic;
extern View *TheTacticalView;

extern void j_00034e91(void);

typedef bool (Object::*WorldspaceBestContactPointCall)(Coord3D *pointOut,
	const Coord3D *callerPos, const char *label, int preference, int seed,
	bool skipCollideTest) const;

// ?bfmeAbs1044@@YAHH@Z absent-from-retail
static __forceinline int bfmeAbs1044(int value)
{
	return abs(value);
}

// ?bfmeHeight1044@@YAM_NPDMPBVObject@@@Z absent-from-retail
static __forceinline float bfmeHeight1044(bool hasContactPoint,
	const volatile float *positionZ, const Object *object)
{
	if (hasContactPoint)
		return *positionZ;
	return reinterpret_cast<const GeometryInfo *>(
		reinterpret_cast<const char *>(object) + 0xAC)->getMaxHeightAbovePosition()
		* 0.5f;
}

class BfmeB1044
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	void bfmeTailA1044004B0850(void);

	char m_bfmePad[4];
	unsigned char m_bfmeFlag;
	char m_bfmePadAfterFlag[0x18 - 9];
	int m_bfme18;
	int m_bfme1c;
	int m_bfme20;
	int m_bfme24;
};

// ?bfmeTailA1044004B0850@BfmeB1044@@QAEXXZ
void BfmeB1044::bfmeTailA1044004B0850(void)
{
	Object *object = TheGameLogic->findObjectByID(m_bfme18);
	ICoord2D screen;

	if (object != 0)
	{
		struct Frame
		{
			Coord3D point;
			Coord3D position;
		} frame;

		Drawable *drawable = object->getDrawable();
		if (drawable != 0)
		{
			frame.point = *drawable->getPosition();
		}
		else
		{
			const Coord3D sourcePosition = *reinterpret_cast<const Coord3D *>(
				reinterpret_cast<const char *>(object) + 0x38);
			frame.point = sourcePosition;
		}

		frame.position.x = 0.0f;
		frame.position.y = 0.0f;
		frame.position.z = 0.0f;
		union
		{
			void *asVoid;
			WorldspaceBestContactPointCall asMember;
		} contactPointCast;
		contactPointCast.asVoid = (void *)j_00034e91;
		bool hasContactPoint = (object->*contactPointCast.asMember)(
			&frame.position, &frame.position, "Menu", 0, 0, false);
		if (hasContactPoint)
		{
			frame.position.x -= reinterpret_cast<const Coord3D *>(
				reinterpret_cast<const char *>(object) + 0x38)->x;
			frame.position.y -= reinterpret_cast<const Coord3D *>(
				reinterpret_cast<const char *>(object) + 0x38)->y;
			frame.position.z -= reinterpret_cast<const Coord3D *>(
				reinterpret_cast<const char *>(object) + 0x38)->z;
			volatile float *positionX = &frame.position.x;
			frame.point.x += *positionX;
			frame.point.y += frame.position.y;
		}
		frame.point.z += bfmeHeight1044(hasContactPoint, &frame.position.z, object);

		if (TheTacticalView->worldToScreen(&frame.point, &screen))
		{
			screen.x = -999;
			screen.y = -999;
		}

		const ICoord2D *center = reinterpret_cast<const ICoord2D *>(&m_bfme20);
		int delta = bfmeAbs1044(center->y - screen.y);
		delta += bfmeAbs1044(center->x - screen.x);
		if (delta > 2)
		{
			m_bfme20 = screen.x;
			m_bfme24 = screen.y;
			m_bfmeFlag = 1;
		}
	}
	else
	{
		screen.x = -999;
		screen.y = -999;
		slot04();
	}
}
