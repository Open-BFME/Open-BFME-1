// cl: /DNDEBUG /DWIN32 /MD /Iinputs/reference/shims/stringinline
// Open-BFME: ScriptActions::doCameraMotionBlurJump, retail 0x002F41C0, 165 bytes.

#include "StringInline.h"

typedef bool Bool;
typedef float Real;

enum FilterTypes
{
	FT_NULL_FILTER = 0,
	FT_VIEW_BW_FILTER,
	FT_VIEW_MOTION_BLUR_FILTER
};

enum FilterModes
{
	FM_NULL_MODE = 0,
	FM_VIEW_BW_BLACK_AND_WHITE,
	FM_VIEW_BW_RED_AND_WHITE,
	FM_VIEW_BW_GREEN_AND_WHITE,
	FM_VIEW_BW_BLUE_AND_WHITE,
	FM_VIEW_BW_IN_AND_OUT,
	FM_VIEW_BW_FADE_AND_RETURN,
	FM_VIEW_MB_IN_AND_OUT_ALPHA,
	FM_VIEW_MB_IN_AND_OUT_SATURATE
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Waypoint
{
public:
	unsigned char m_beforeLocation[0x0c];
	Coord3D m_location;
};

class TerrainLogic
{
public:
	virtual void slot00(void) = 0; virtual void slot01(void) = 0;
	virtual void slot02(void) = 0; virtual void slot03(void) = 0;
	virtual void slot04(void) = 0; virtual void slot05(void) = 0;
	virtual void slot06(void) = 0; virtual void slot07(void) = 0;
	virtual void slot08(void) = 0; virtual void slot09(void) = 0;
	virtual void slot10(void) = 0; virtual void slot11(void) = 0;
	virtual void slot12(void) = 0; virtual void slot13(void) = 0;
	virtual void slot14(void) = 0; virtual void slot15(void) = 0;
	virtual void slot16(void) = 0; virtual void slot17(void) = 0;
	virtual void slot18(void) = 0; virtual void slot19(void) = 0;
	virtual void slot20(void) = 0; virtual void slot21(void) = 0;
	virtual void slot22(void) = 0; virtual void slot23(void) = 0;
	virtual void slot24(void) = 0; virtual void slot25(void) = 0;
	virtual void slot26(void) = 0; virtual void slot27(void) = 0;
	virtual void slot28(void) = 0; virtual void slot29(void) = 0;
	virtual void slot30(void) = 0;
	virtual Waypoint *getWaypointByName(AsciiString name) = 0; // slot 31, +0x7c
};

class View
{
public:
#define BFME_VIEW_SLOT(offset) virtual void slot##offset(void) = 0;
	BFME_VIEW_SLOT(000) BFME_VIEW_SLOT(004) BFME_VIEW_SLOT(008) BFME_VIEW_SLOT(00C)
	BFME_VIEW_SLOT(010) BFME_VIEW_SLOT(014) BFME_VIEW_SLOT(018) BFME_VIEW_SLOT(01C)
	BFME_VIEW_SLOT(020) BFME_VIEW_SLOT(024) BFME_VIEW_SLOT(028) BFME_VIEW_SLOT(02C)
	BFME_VIEW_SLOT(030) BFME_VIEW_SLOT(034) BFME_VIEW_SLOT(038) BFME_VIEW_SLOT(03C)
	BFME_VIEW_SLOT(040) BFME_VIEW_SLOT(044) BFME_VIEW_SLOT(048) BFME_VIEW_SLOT(04C)
	BFME_VIEW_SLOT(050)
	virtual void lookAt(const Coord3D *position) = 0; // slot 21, +0x54
	BFME_VIEW_SLOT(058) BFME_VIEW_SLOT(05C) BFME_VIEW_SLOT(060) BFME_VIEW_SLOT(064)
	BFME_VIEW_SLOT(068) BFME_VIEW_SLOT(06C) BFME_VIEW_SLOT(070) BFME_VIEW_SLOT(074)
	BFME_VIEW_SLOT(078) BFME_VIEW_SLOT(07C) BFME_VIEW_SLOT(080) BFME_VIEW_SLOT(084)
	BFME_VIEW_SLOT(088) BFME_VIEW_SLOT(08C) BFME_VIEW_SLOT(090) BFME_VIEW_SLOT(094)
	BFME_VIEW_SLOT(098) BFME_VIEW_SLOT(09C) BFME_VIEW_SLOT(0A0) BFME_VIEW_SLOT(0A4)
	BFME_VIEW_SLOT(0A8) BFME_VIEW_SLOT(0AC)
	virtual Bool setViewFilterMode(FilterModes mode) = 0; // slot 44, +0xb0
	// BFME's slot takes an added flag (the retail target is an empty `ret 8`);
	// the Zero Hour predecessor took only the position pointer.
	virtual void setViewFilterPos(const Coord3D *position,
		Bool immediate = false) = 0; // slot 45, +0xb4
	virtual Bool setViewFilter(FilterTypes filter) = 0; // slot 46, +0xb8
#undef BFME_VIEW_SLOT
};

extern TerrainLogic *TheTerrainLogic;
extern View *TheTacticalView;

class ScriptActions
{
protected:
	void doCameraMotionBlurJump(const AsciiString &waypointName, Bool saturate);
};

// ?doCameraMotionBlurJump@ScriptActions@@IAEXABVAsciiString@@_N@Z
void ScriptActions::doCameraMotionBlurJump(
	const AsciiString &waypointName, Bool saturate)
{
	Waypoint *way = TheTerrainLogic->getWaypointByName(waypointName);
	if (!way)
		return;

	Bool passed = false;
	Coord3D pos;
	pos.x = way->m_location.x;
	pos.y = way->m_location.y;
	pos.z = way->m_location.z;
	if (TheTacticalView->setViewFilter(FT_VIEW_MOTION_BLUR_FILTER))
	{
		passed = true;
		if (saturate)
		{
			if (!TheTacticalView->setViewFilterMode(FM_VIEW_MB_IN_AND_OUT_SATURATE))
			{
				TheTacticalView->setViewFilter(FT_NULL_FILTER);
				passed = false;
			}
		}
		else
		{
			if (!TheTacticalView->setViewFilterMode(FM_VIEW_MB_IN_AND_OUT_ALPHA))
			{
				TheTacticalView->setViewFilter(FT_NULL_FILTER);
				passed = false;
			}
		}
		if (passed)
			TheTacticalView->setViewFilterPos(&pos);
	}
	if (!passed)
		TheTacticalView->lookAt(&pos);
}
