// cl: /G5 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Oy /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// positionAdditionalImages: ZH twin SkirmishGameOptionsMenu.cpp; retail 0x00452AD0..0x00452D62 (659 bytes)

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

	if( !mmd || !mapWindow || mapWindow->winIsHidden())
		return;
	static MapMetaData *prevMMD = NULL;
	if(force)
		prevMMD = NULL;
	if(mmd == prevMMD)
		return;
	ICoord2D winMapSize, winMapPos;
	mapWindow->winGetSize(&winMapSize.x, &winMapSize.y);
	mapWindow->winGetScreenPosition(&winMapPos.x, &winMapPos.y);

	ICoord2D ul;
	Int smallWidth, smallHeight;
	{
		ICoord2D lr;
		findDrawPositions(0,0, winMapSize.x, winMapSize.y,mmd->m_extent, &ul, &lr);
		smallWidth = lr.x - ul.x;
		smallHeight= lr.y - ul.y;
	}

	Coord3DList::iterator it = mmd->m_supplyPositions.begin();
	Int ulX = ul.x;
	Int ulY = ul.y;
	while( it != mmd->m_supplyPositions.end())
	{
		ICoord2D markerPos;
		Real position;
		position = (it->x - mmd->m_extent.lo.x) / (mmd->m_extent.hi.x - mmd->m_extent.lo.x);
		markerPos.x = (position * smallWidth) - SUPPLY_TECH_SIZE /2 + ulX;
		position = (it->y - mmd->m_extent.lo.y) / (mmd->m_extent.hi.y - mmd->m_extent.lo.y);
		markerPos.y = ((1- position) * smallHeight) - SUPPLY_TECH_SIZE /2 + ulY;
		TheSupplyAndTechImageLocations.m_supplyPosList.push_front(markerPos);
		it++;
	}

	it = mmd->m_techPositions.begin();
	ulX = ul.x;
	ulY = ul.y;
	while( it != mmd->m_techPositions.end())
	{
		ICoord2D markerPos;
		Real position;
		position = (it->x - mmd->m_extent.lo.x) / (mmd->m_extent.hi.x - mmd->m_extent.lo.x);
		markerPos.x = (position * smallWidth) - SUPPLY_TECH_SIZE /2 + ulX;
		position = (it->y - mmd->m_extent.lo.y) / (mmd->m_extent.hi.y - mmd->m_extent.lo.y);
		markerPos.y = ((1- position) * smallHeight) - SUPPLY_TECH_SIZE /2 + ulY;
		TheSupplyAndTechImageLocations.m_techPosList.push_front(markerPos);
		it++;
	}
}
