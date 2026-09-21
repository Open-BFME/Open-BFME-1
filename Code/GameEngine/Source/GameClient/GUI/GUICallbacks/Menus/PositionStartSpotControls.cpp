// ?positionStartSpotControls@@YAXPAVGameWindow@@0PAUCoord3D@@PAVMapMetaData@@QAPAV1@@Z
// Retail 0x0044F960, 427 bytes. Coordinate-calculation locals end before
// the overlap loop so VC7.1 reuses their stack slots as retail does.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /FAsc /Fabuild/rva0044f960.cod /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport
typedef int Int;
typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct Region3D
{
	Region3D(const Region3D &that);
	~Region3D();

	Coord3D lo;
	Coord3D hi;
};

struct ICoord2D
{
	Int x;
	Int y;
};

class GameWindow
{
public:
	Int winGetSize(Int *width, Int *height);
	Int winGetScreenPosition(Int *x, Int *y);
	Int winSetPosition(Int x, Int y);
};

class MapMetaData
{
	public:
	char m_beforeExtent[8];
	Region3D m_extent;
};

void findDrawPositions(Int startX, Int startY, Int width, Int height,
	Region3D extent, ICoord2D *ul, ICoord2D *lr);

enum { MAX_SLOTS = 8 };

// ZH twin: GeneralsMD/Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/SkirmishGameOptionsMenu.cpp
void positionStartSpotControls(GameWindow *win, GameWindow *mapWindow,
	Coord3D *pos, MapMetaData *mmd, GameWindow *buttonMapStartPositions[])
{
	if (!win || !mmd || !mapWindow || !buttonMapStartPositions)
		return;

	ICoord2D winMapSize, winMapPos, gadgetPos;
	Int gadgetSize[2];
	mapWindow->winGetSize(&winMapSize.x, &winMapSize.y);
	mapWindow->winGetScreenPosition(&winMapPos.x, &winMapPos.y);
	win->winGetSize(&gadgetSize[0], &gadgetSize[1]);
	{
		Int ul[2];
		ICoord2D *ulAddress = (ICoord2D *)ul;
		Int smallWidth, smallHeight;
		ICoord2D lr;
		findDrawPositions(0, 0, winMapSize.x, winMapSize.y,
			mmd->m_extent, ulAddress, &lr);
		smallWidth = lr.x - ul[0];
		smallHeight = lr.y - ul[1];

		Real position;
		position = (pos->x - mmd->m_extent.lo.x) /
			(mmd->m_extent.hi.x - mmd->m_extent.lo.x);
		gadgetPos.x = (position * smallWidth) - gadgetSize[0] / 2 + ul[0];

		position = (pos->y - mmd->m_extent.lo.y) /
			(mmd->m_extent.hi.y - mmd->m_extent.lo.y);
		gadgetPos.y = ((1 - position) * smallHeight) - gadgetSize[1] / 2 + ul[1];
	}

	for (Int i = 0; i < MAX_SLOTS; ++i)
	{
		if (buttonMapStartPositions[i] == win)
			break;
		ICoord2D tempPos;
		buttonMapStartPositions[i]->winGetScreenPosition(&tempPos.x, &tempPos.y);
		if (gadgetPos.x > tempPos.x &&
			gadgetPos.x < tempPos.x + gadgetSize[0] &&
			gadgetPos.y > tempPos.y &&
			gadgetPos.y < tempPos.y + gadgetSize[1])
		{
			Int closerRight = tempPos.x + gadgetSize[0] - gadgetPos.x;
			Int closerBottom = tempPos.y + gadgetSize[1] - gadgetPos.y;
			if (closerRight < closerBottom)
				gadgetPos.x = tempPos.x + gadgetSize[0] + 1;
			else if (closerBottom < closerRight)
				gadgetPos.y = tempPos.y + gadgetSize[1] + 1;
			else
			{
				gadgetPos.x = tempPos.x + gadgetSize[0] + 1;
				gadgetPos.y = tempPos.y + gadgetSize[1] + 1;
			}
		}
	}
	win->winSetPosition(gadgetPos.x, gadgetPos.y);
}
