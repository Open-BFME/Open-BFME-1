// cl: /DNDEBUG /MD /EHsc
// readable body of ?placeBuildAvailable@InGameUI@@UAEXPBVThingTemplate@@PAVDrawable@@@Z: Code/GameEngine/Source/GameClient/InGameUI.cpp

// Open-BFME5: clean C++ reconstruction of InGameUI::placeBuildAvailable.
// The declarations below retain the BFME retail offsets and virtual slots;
// they are intentionally local so this conversion does not perturb shared
// headers or unrelated translation units.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct ICoord2D;
class Object;
class Drawable;
class ThingTemplate;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
private:
	unsigned char m_unreconstructed_000[0x1C4];

public:
	UnsignedInt m_playerColor;
	UnsignedInt m_playerNightColor;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
private:
	unsigned char m_unreconstructed_000[0x74];

public:
	UnsignedInt m_id;
	Player *getControllingPlayer(void) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	void setOrientation(float angle);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable : public Thing
{
private:
	unsigned char m_unreconstructed_004[0xAF];

public:
	float m_opacity;
	unsigned char m_unreconstructed_0B4[0x48];
	Object *m_object;

	void setIndicatorColor(UnsignedInt color);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
private:
	unsigned char m_unreconstructed_000[0x3B0];

public:
	float m_placementViewAngle;
};

enum DrawableStatus
{
	DRAWABLE_STATUS_NO_STATE_PARTICLES = 8
};

class BFMEThingFactory
{
public:
	Drawable *newDrawable(const ThingTemplate *thing, DrawableStatus status,
		Int unknown);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
private:
	unsigned char m_unreconstructed_000[0x218];

public:
	Int m_timeOfDay;
};

class Mouse
{
public:
	enum MouseCursor
	{
		ARROW = 2,
		CROSS = 4
	};

	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0C(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1C(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2C(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual void setCursor(MouseCursor cursor);
	virtual void capture(void);
	virtual void releaseCapture(void);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot0A(void);
	virtual void slot0B(void);
	virtual void slot0C(void);
	virtual void slot0D(void);
	virtual void slot0E(void);
	virtual void slot0F(void);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void slot12(void);
	virtual void slot13(void);
	virtual void slot14(void);
	virtual void slot15(void);
	virtual void slot16(void);
	virtual void slot17(void);
	virtual void slot18(void);
	virtual void slot19(void);
	virtual void slot1A(void);
	virtual void slot1B(void);
	virtual void slot1C(void);
	virtual void slot1D(void);
	virtual void slot1E(void);
	virtual void slot1F(void);
	virtual void slot20(void);
	virtual void slot21(void);
	virtual void slot22(void);
	virtual void slot23(void);
	virtual void slot24(void);
	virtual void slot25(void);
	virtual void slot26(void);
	virtual void slot27(void);
	virtual void slot28(void);
	virtual void slot29(void);
	virtual void slot2A(void);
	virtual void slot2B(void);
	virtual void slot2C(void);
	virtual void slot2D(void);
	virtual void slot2E(void);
	virtual void slot2F(void);
	virtual void placeBuildAvailable(const ThingTemplate *build,
		Drawable *buildDrawable);
	virtual void slot31(void);
	virtual void slot32(void);
	virtual void setPlacementStart(const ICoord2D *start);
	virtual void slot34(void);
	virtual void slot35(void);
	virtual void slot36(void);
	virtual void slot37(void);
	virtual void slot38(void);
	virtual void slot39(void);
	virtual void slot3A(void);
	virtual void slot3B(void);
	virtual void slot3C(void);
	virtual void slot3D(void);
	virtual void slot3E(void);
	virtual void slot3F(void);
	virtual void slot40(void);
	virtual void slot41(void);
	virtual void slot42(void);
	virtual void slot43(void);
	virtual void slot44(void);
	virtual void slot45(void);
	virtual void slot46(void);
	virtual void setRadiusCursorNone(void);
	void destroyPlacementIcons(void);

private:
	unsigned char m_unreconstructed_004[0x530];
	const ThingTemplate *m_pendingPlaceType;
	UnsignedInt m_pendingPlaceSourceObjectID;
	Drawable **m_placeIcon;
	unsigned char m_unreconstructed_540[0x2E4];
	Int m_mouseMode;
	Int m_mouseModeCursor;
};

void InGameUI::placeBuildAvailable(const ThingTemplate *build,
	Drawable *buildDrawable)
{
	if (build != 0)
		setRadiusCursorNone();

	if (m_pendingPlaceType != 0 && build != 0)
		placeBuildAvailable(0, 0);

	Object *sourceObject = 0;
	m_pendingPlaceType = build;
	m_pendingPlaceSourceObjectID = 0;
	if (buildDrawable != 0)
		sourceObject = buildDrawable->m_object;
	if (sourceObject != 0)
		m_pendingPlaceSourceObjectID = sourceObject->m_id;

	Mouse *mouse = *(Mouse **)0x012F4C5C;
	if (mouse == 0)
		return;

	if (build != 0)
	{
		m_mouseMode = 1;
		m_mouseModeCursor = Mouse::CROSS;
		(*(Mouse **)0x012F4C5C)->capture();

		mouse = *(Mouse **)0x012F4C5C;
		if (mouse != 0)
		{
			mouse->setCursor(Mouse::CROSS);
			if (m_mouseMode == 2)
				m_mouseModeCursor = Mouse::CROSS;
		}

		Drawable *draw = (*(BFMEThingFactory **)0x012EF1D8)->newDrawable(
			build, DRAWABLE_STATUS_NO_STATE_PARTICLES, -1);
		if (sourceObject != 0)
		{
			if ((*(GlobalData **)0x012ED5C8)->m_timeOfDay == 4)
				draw->setIndicatorColor(
					sourceObject->getControllingPlayer()->m_playerNightColor);
			else
				draw->setIndicatorColor(
					sourceObject->getControllingPlayer()->m_playerColor);
		}
		draw->setOrientation(build->m_placementViewAngle);
		draw->m_opacity = 0.45f;
		m_placeIcon[0] = draw;
	}
	else
	{
		if (m_mouseMode == 1)
		{
			m_mouseMode = 0;
			m_mouseModeCursor = Mouse::ARROW;
			mouse = *(Mouse **)0x012F4C5C;
		}
		mouse->releaseCapture();

		mouse = *(Mouse **)0x012F4C5C;
		if (mouse != 0)
			mouse->setCursor(Mouse::ARROW);

		setPlacementStart(0);
		destroyPlacementIcons();
	}
}
