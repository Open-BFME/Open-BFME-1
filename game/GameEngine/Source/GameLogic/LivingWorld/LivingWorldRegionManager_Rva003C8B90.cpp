// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/shims/stringbaseunicode /Igame/Libraries/Source/WWVegas/WWLib
//
// Retail 0x003C8B90.  The owner is established independently by the
// 0x003C8880 constructor's 0x010EE010 vtable and its 0x003C88D0
// "LivingWorldRegionManager" name slot.  This body's +0x08 selected-region
// and +0x10 enable fields also agree with the matched setter at 0x003C8340.
// The original method name is unavailable, so the exported name stays
// address-derived.  The two typed member declarations below resolve through
// their retail ILT thunks; their bodies are 0x003C8160 and 0x003C8340.

#include <wchar.h>
#include "Common/UnicodeString.h"

struct RGBColor;

struct ICoord2D
{
	int x;
	int y;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Mouse
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void setCursor(int cursor) = 0;

	void setCursorTooltip(UnicodeString tooltip, int delay,
		const RGBColor *color, float width);
};

extern Mouse *TheMouse;

class CampaignObject
{
public:
	char m_unmodelled00[0x1C];
	bool m_regionInputEnabled;
	char m_pad1D[3];
	ICoord2D m_regionInput;
};

extern CampaignObject *TheLivingWorldLogic;

class Gen_00609320
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void screenToTerrain(const ICoord2D *screen, Coord3D *world) = 0;
};

extern Gen_00609320 *g_bfmeStateDF;

class LivingWorldRegion
{
};

class LivingWorldRegionManager
{
public:
	void rva003C8B90();
	LivingWorldRegion *rva003C8160(Coord3D *position);
	void rva003C8340(LivingWorldRegion *region);

private:
	void *m_vtable;
	void *m_regions;
	LivingWorldRegion *m_selectedRegion;
	int m_unmodelled0C;
	bool m_enabled;
};

void LivingWorldRegionManager::rva003C8B90()
{
	if (m_selectedRegion != 0)
		TheMouse->setCursor(5);
	else
		TheMouse->setCursor(1);

	ICoord2D screen = TheLivingWorldLogic->m_regionInput;
	if (!m_enabled)
	{
		TheMouse->setCursorTooltip(UnicodeString::TheEmptyString, -1, 0, 1.0f);
		m_selectedRegion = 0;
		return;
	}

	if (TheLivingWorldLogic->m_regionInputEnabled)
	{
		Coord3D world;
		g_bfmeStateDF->screenToTerrain(&screen, &world);
		rva003C8340(rva003C8160(&world));
	}
}
