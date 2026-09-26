// cl: /G5 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Oy /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// MapSelectorTooltip: ZH twin SkirmishGameOptionsMenu.cpp. Retail 0x004F1760
// (267 bytes). Its ILT 0x00037EF2 is passed to GameWindow::winSetTooltipFunc by
// the matched InitLanGameGadgets (push at 0x004CBF89, as the ZH twin does) and
// by the body at 0x004F2C00 (push at 0x004F30BF). The string literals "Cash" and
// "TOOLTIP:SupplyDock" are the ZH twin's supply-dock branch; BFME has no
// tech-building branch here.

#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

struct ICoord2D
{
	Int x, y;
};

#include <list>

typedef std::list<ICoord2D> ICoord2DList;

class TechAndSupplyImages
{
public:
	ICoord2DList m_techPosList;
	ICoord2DList m_supplyPosList;
};

extern TechAndSupplyImages TheSupplyAndTechImageLocations;

#define LOLONGTOSHORT(a)  ((a) & 0x0000FFFF)
#define HILONGTOSHORT(b)  (((b) & 0xFFFF0000) >> 16)

class WinInstanceData;

class GameWindow
{
public:
	Int winGetScreenPosition(Int *x, Int *y);
};

class Image;

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;

class GameTextInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual UnicodeString fetch(const char *label, bool *exists = 0);
	virtual UnicodeString fetch(AsciiString label, bool *exists = 0);
};

extern GameTextInterface *TheGameText;

struct RGBColor;

class Mouse
{
public:
	void setCursorTooltip(UnicodeString tooltip, Int tooltipDelay = -1,
		const RGBColor *color = 0, Real width = 1.0f);
};

extern Mouse *TheMouse;

enum { SUPPLY_TECH_SIZE = 15 };

void MapSelectorTooltip(GameWindow *window,
						WinInstanceData *instData,
						UnsignedInt mouse)
{
	Int x, y;
	x = LOLONGTOSHORT(mouse);
	y = HILONGTOSHORT(mouse);

	Int pixelX, pixelY;
	window->winGetScreenPosition(&pixelX, &pixelY);

	const Image *image2 = TheMappedImageCollection->findImageByName("Cash");

	ICoord2DList::iterator it2 = TheSupplyAndTechImageLocations.m_supplyPosList.begin();

	if (image2)
	{
		// Check to see if we mouse over a supply dock
		while (it2 != TheSupplyAndTechImageLocations.m_supplyPosList.end())
		{
			if ((x > (pixelX + it2->x) && x < (pixelX + it2->x + SUPPLY_TECH_SIZE))
					 && ( y > (pixelY + it2->y) && y < (pixelY + it2->y + SUPPLY_TECH_SIZE)))
			{
				TheMouse->setCursorTooltip( TheGameText->fetch("TOOLTIP:SupplyDock"), -1, 0);
				break;
			}
			it2++;
		}
	}
}
