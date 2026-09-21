// ?positionAdditionalImages@@YAXPAVMapMetaData@@PAVGameWindow@@_N@Z
// partial score=0.9757207891 date=2026-09-21
// cl: /G5 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Oy /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1

typedef int Int;
typedef bool Bool;
typedef float Real;

struct Coord3DBase
{
	float x, y, z;
};

class Coord3D : public Coord3DBase
{
public:
	Coord3D();
	Coord3D(const Coord3D &that);
	~Coord3D();
};

struct Region3D
{
	Region3D();
	Region3D(const Region3D &that);
	~Region3D();

	Coord3D lo, hi;
};

struct ICoord2D
{
	Int x, y;
};

#include <list>

typedef std::list<ICoord2D> ICoord2DList;
typedef std::list<Coord3D> Coord3DList;

class TechAndSupplyImages
{
public:
	ICoord2DList m_techPosList;
	ICoord2DList m_supplyPosList;
};

extern TechAndSupplyImages TheSupplyAndTechImageLocations;

class GameWindow
{
public:
	Bool winIsHidden(void);
	Int winGetSize(Int *width, Int *height);
	Int winGetScreenPosition(Int *x, Int *y);
};

class MapMetaData
{
	public:
	char m_beforeExtent[8];
	Region3D m_extent;
	char m_betweenExtentAndLists[0x28];
	Coord3DList m_supplyPositions;
	Coord3DList m_techPositions;
};

void findDrawPositions(Int startX, Int startY, Int width, Int height,
	Region3D extent, ICoord2D *ul, ICoord2D *lr);

enum { SUPPLY_TECH_SIZE = 15 };

void positionAdditionalImages(MapMetaData *mmd, GameWindow *mapWindow, Bool force)
{
	TheSupplyAndTechImageLocations.m_supplyPosList.clear();
	TheSupplyAndTechImageLocations.m_techPosList.clear();

	if (!mmd || !mapWindow || mapWindow->winIsHidden())
		return;
	static MapMetaData *prevMMD = NULL;
	if (force)
		prevMMD = NULL;
	if (mmd == prevMMD)
		return;

	ICoord2D winMapSize;
	ICoord2D winMapPos;
	mapWindow->winGetSize(&winMapSize.x, &winMapSize.y);
	mapWindow->winGetScreenPosition(&winMapPos.x, &winMapPos.y);

	ICoord2D ul;
	ICoord2D lr;
	findDrawPositions(0, 0, winMapSize.x, winMapSize.y, mmd->m_extent, &ul, &lr);
	Int &smallWidth = winMapSize.x;
	smallWidth = lr.x - ul.x;
	Int &smallHeight = winMapSize.y;
	smallHeight = lr.y - ul.y;

	Coord3DList::iterator it = mmd->m_supplyPositions.begin();
	if (it != mmd->m_supplyPositions.end()) {
        const Real drawWidth = smallWidth;
        const Real originX = ul.x;
        const Real drawHeight = smallHeight;
        const Real originY = ul.y;
        do {
		ICoord2D markerPos;
		Real position = (it->x - mmd->m_extent.lo.x)
			/ (mmd->m_extent.hi.x - mmd->m_extent.lo.x);
		markerPos.x = position * drawWidth - SUPPLY_TECH_SIZE / 2 + originX;
		position = (it->y - mmd->m_extent.lo.y)
			/ (mmd->m_extent.hi.y - mmd->m_extent.lo.y);
		markerPos.y = (1 - position) * drawHeight
			- SUPPLY_TECH_SIZE / 2 + originY;
		TheSupplyAndTechImageLocations.m_supplyPosList.push_front(markerPos);
		it++;
        } while (it != mmd->m_supplyPositions.end());
	}

	it = mmd->m_techPositions.begin();
	if (it != mmd->m_techPositions.end()) {
        const Real drawWidth = smallWidth;
        const Real originX = ul.x;
        const Real drawHeight = smallHeight;
        const Real originY = ul.y;
        do {
		ICoord2D markerPos;
		Real position = (it->x - mmd->m_extent.lo.x)
			/ (mmd->m_extent.hi.x - mmd->m_extent.lo.x);
		markerPos.x = position * drawWidth - SUPPLY_TECH_SIZE / 2 + originX;
		position = (it->y - mmd->m_extent.lo.y)
			/ (mmd->m_extent.hi.y - mmd->m_extent.lo.y);
		markerPos.y = (1 - position) * drawHeight
			- SUPPLY_TECH_SIZE / 2 + originY;
		TheSupplyAndTechImageLocations.m_techPosList.push_front(markerPos);
		it++;
        } while (it != mmd->m_techPositions.end());
	}
}
