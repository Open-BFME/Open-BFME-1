// ?positionStartSpots@@YAXVAsciiString@@QAPAVGameWindow@@PAV2@2@Z
// partial score=1.0 date=2026-09-29
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: the four-argument positionStartSpots that positions the eight
// start-spot buttons for one map (retail 0x00455F60, 1069 bytes).  The Zero
// Hour twin in SkirmishGameOptionsMenu.cpp is the three-argument form; BFME
// added the fourth argument, the APT "APT:MapTitle" commit, and the
// "MissingMap" image name (Zero Hour says "UnknownMap").
//
// The matched GameInfo overload at 0x004564A0 forwards its own fourth argument
// straight through to this body through ILT 0x0003D901, and the five other call
// sites of that ILT thunk (LanMapSelectMenuSystem 0x004D0D10 and 0x004D0E16,
// WOLPositionStartSpots 0x004F1B44, and the two in 0x00504600) push four words
// too, so the arity is four.
//
// The fourth parameter is a GameWindow*, not the Bool that the symbols.csv pin
// at 0x0003D901 and the callers' declarations spell it as.  Retail tests it
// with `mov ebx,[esp+0x13c]; cmp ebx,edi` -- a full dword against zero -- while
// a `Bool` parameter makes MSVC 7.1 emit `mov bl,byte ptr [..]; test bl,bl`
// (measured: that spelling compiles to 1087 bytes against retail's 1069), and
// it then hands the same word to GadgetListBoxReset (0x004B7880) before
// anything else and to GadgetListBoxAddEntryText (0x004BB4B0) at the end of
// the map-found path: a list box.  Every mapped call site passes zero, so both
// list-box calls are dead in the shipped game.  See
// targets/game/reverse/identity_evidence/00455f60-positionstartspots.md.

#include <list>
#include <map>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

// Retail's toLower is the public StringBase<char> member
// ?toLower@?$StringBase@D@@QAEXXZ (0x00887DA0, matched,
// game/Libraries/Source/string/StringBaseCaseOps.cpp), so it is declared public
// here: the access specifier is in the mangled name and the call site has to
// encode the one retail does.
template <typename T>
class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &src);
	StringBase(const T *text);
	void releaseBuffer();

	struct Header
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		T m_text[1];
	};

	Header *m_data;

public:
	void toLower();
};

// Retail's AsciiString is StringBase<char> and every one of its bodies is out of
// line: the copy constructor 0x00887B60, the C-string constructor 0x00888BC0,
// the destructor (releaseBuffer) 0x00887940 and toLower 0x00887DA0.  The copy
// constructor is the one exception in spelling: it has to be an inline forwarder
// so that the call site encodes StringBase<char>'s body, because that is the
// name retail's own calls carry; the rest are declared only, which leaves the
// call site with a relocation the pins resolve.
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString();

	void toLower() { StringBase<char>::toLower(); }
	void __cdecl format(AsciiString fmt, ...);

	bool operator<(const AsciiString &other) const;
};

// The wide string bodies retail calls are 0x00888DE0 (the literal constructor)
// and 0x008881D0 (releaseBuffer).
class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString(const unsigned short *text) : StringBase<unsigned short>(text) {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString();
};

class Image
{
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MapUtil.h
class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

class WindowManager
{
public:
	void bfme_setAptText(const AsciiString &name, const UnicodeString &text);
};

class GameWindow
{
public:
	// upstream signatures:
	// inputs/reference/.../GameEngine/Include/GameClient/GameWindow.h:256,262
	UnsignedInt winClearStatus(UnsignedInt status);
	void winSetUserData(void *data);
	UnsignedInt winSetStatus(UnsignedInt status);
	void winSetEnabledImage(Int index, const Image *image);
	Int winHide(Bool hide);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWMath/Coord3D.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

class WaypointMap : public std::map<AsciiString, Coord3D>
{
};

typedef std::list<Coord3D> Coord3DList;

// Retail's MapMetaData, as the matched copy constructor (0x000C1240) and
// destructor (0x00078540) witness it: the two strings, six extent floats,
// m_numPlayers at +0x20, the three flag bytes, the two size words, the
// timestamp pair, the waypoint tree at +0x38, the two supply/tech lists and the
// filename at +0x50, the eight player records at +0x54 and the two cached
// strings at +0xF4.  The waypoint tree decides the frame size, so the tail
// padding that follows the player records is load-bearing here.
class MapMetaData
{
public:
	MapMetaData(const MapMetaData &other);
	~MapMetaData();

	UnicodeString getDescription();
	UnicodeString bfme_getDisplayName();

	UnicodeString m_displayName;
	UnicodeString m_descriptionLabel;
	float m_extentLoX;
	float m_extentLoY;
	float m_extentLoZ;
	float m_extentHiX;
	float m_extentHiY;
	float m_extentHiZ;
	Int m_numPlayers;
	Bool m_isMultiplayer;
	Bool m_isScenarioMP;
	Bool m_isOfficial;
	UnsignedInt m_filesize;
	UnsignedInt m_CRC;
	UnsignedInt m_timestampLo;
	UnsignedInt m_timestampHi;
	WaypointMap m_waypoints;
	Coord3DList m_supplyPositions;
	Coord3DList m_techPositions;
	AsciiString m_fileName;
	unsigned char m_unmodelled54[0xA0];
	UnicodeString m_cachedDisplayName;
	UnicodeString m_cachedDescription;
	unsigned int m_unmodelledFC;
};

class MapCache : public std::map<AsciiString, MapMetaData>
{
public:
	const MapMetaData *findMap(AsciiString mapName);
};

// One node of the cache's name-keyed tree: the 0x14 bytes of links every
// STLport tree node carries, then the value.
struct MapCacheNode
{
	unsigned char m_treeLinks[0x14];
	MapMetaData second;
};

extern MapCache *TheMapCache;
extern ImageCollection *TheMappedImageCollection;
extern WindowManager *g_theWindowManager;

// The two function-local statics of the Zero Hour source, one per branch: they
// cache the "MissingMap" image of the map-not-found path and of the
// preview-image-missing path.  Named for the retail addresses they hold.
extern const Image *g_Rva012F15EC;
extern const Image *g_Rva012F15E8;

Image *getMapPreviewImage(AsciiString mapName);
void positionAdditionalImages(MapMetaData *mmd, GameWindow *mapWindow, Bool force);
void positionStartSpotControls(GameWindow *win, GameWindow *mapWindow, Coord3D *pos,
	MapMetaData *mmd, GameWindow *buttonMapStartPositions[]);
void GadgetListBoxReset(GameWindow *listbox);
Int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text, Int color,
	Int row, Int column, Bool overwrite);

enum { MAX_SLOTS = 8 };

// ?positionStartSpots@@YAXVAsciiString@@QAPAVGameWindow@@PAV2@PAVGameWindow@@Z
void positionStartSpots(AsciiString mapName, GameWindow *buttonMapStartPositions[],
	GameWindow *mapWindow, GameWindow *errorListBox)
{
	if (errorListBox)
		GadgetListBoxReset(errorListBox);

	AsciiString lowerMap = mapName;
	lowerMap.toLower();
	MapCache *cache = TheMapCache;
	std::map<AsciiString, MapMetaData>::iterator it = cache->find(lowerMap);
	if (it == cache->end())
	{
		mapWindow->winSetUserData(NULL);

		if (!g_Rva012F15EC)
			g_Rva012F15EC = TheMappedImageCollection->findImageByName("MissingMap");
		if (g_Rva012F15EC)
		{
			mapWindow->winSetStatus(0x80);
			mapWindow->winSetEnabledImage(0, g_Rva012F15EC);
		}
		else
		{
			mapWindow->winClearStatus(0x80);
		}

		positionAdditionalImages(NULL, mapWindow, true);
		for (Int i = 0; i < MAX_SLOTS; ++i)
		{
			if (buttonMapStartPositions[i] != NULL)
			{
				buttonMapStartPositions[i]->winHide(true);
			}
		}

		g_theWindowManager->bfme_setAptText(AsciiString("APT:MapTitle"),
			UnicodeString(L" "));
	}
	else
	{
		MapMetaData mmd = it->second;

		Image *image = getMapPreviewImage(mapName);
		if (mapWindow != NULL) {
			mapWindow->winSetUserData((void *)TheMapCache->findMap(mapName));
			if (image)
			{
				mapWindow->winSetStatus(0x80);
				mapWindow->winSetEnabledImage(0, image);
			}
			else
			{
				if (!g_Rva012F15E8)
					g_Rva012F15E8 = TheMappedImageCollection->findImageByName("MissingMap");
				if (g_Rva012F15E8)
				{
					mapWindow->winSetStatus(0x80);
					mapWindow->winSetEnabledImage(0, g_Rva012F15E8);
				}
				else
				{
					mapWindow->winClearStatus(0x80);
				}
			}
		}

		positionAdditionalImages(&mmd, mapWindow, true);

		AsciiString waypointName;
		for (Int i = 0; i < mmd.m_numPlayers && mmd.m_isMultiplayer; ++i)
		{
			waypointName.format("Player_%d_Start", i + 1);
			WaypointMap::iterator wmIt = mmd.m_waypoints.find(waypointName);
			if (wmIt != mmd.m_waypoints.end())
			{
				Coord3D *pos = &wmIt->second;
				positionStartSpotControls(buttonMapStartPositions[i], mapWindow, pos,
					&mmd, buttonMapStartPositions);
				if (buttonMapStartPositions[i] != NULL)
				{
					buttonMapStartPositions[i]->winHide(false);
				}
			}
		}
		// hide the rest
		for (; i < MAX_SLOTS; ++i)
		{
			if (buttonMapStartPositions[i] != NULL)
			{
				buttonMapStartPositions[i]->winHide(true);
			}
		}

		{
			// The matched sibling at 0x00520920 (AptMapPreviewSetMapTitle.cpp)
			// builds the key into a local before the display-name call, and
			// retail releases both at the end of the enclosing block.
			AsciiString key("APT:MapTitle");
			g_theWindowManager->bfme_setAptText(key, mmd.bfme_getDisplayName());
		}

		if (errorListBox)
			GadgetListBoxAddEntryText(errorListBox, mmd.getDescription(),
				-1, -1, -1, true);
	}
}
