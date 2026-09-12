// cl: /DNDEBUG /MD /EHsc
// readable body of ?placeBuildAvailable@InGameUI@@UAEXPBVThingTemplate@@PAVDrawable@@@Z: Code/GameEngine/Source/GameClient/InGameUI.cpp
// readable body of ?recreateControlBar@InGameUI@@UAEXXZ: Code/GameEngine/Source/GameClient/InGameUI.cpp
//
// Six InGameUI members that each arrived one to a file:
//
//   destroyPlacementIcons  0x0043AF00   71 B  IAE (protected)
//   placeBuildAvailable    0x0043AF60  363 B  UAE (public virtual)
//   handleRadiusCursor     0x0043B2D0   -- B  IAE (protected)
//   getIdleWorkerCount     0x004422C0   41 B  EAE (private virtual)
//   recreateControlBar     0x00442300  279 B  UAE (public virtual)
//   setInputEnabled           retail    -- B  UAE (public virtual)
//   setMouseCursor            retail    -- B  QAE (public)
//   selectMatchingAcrossScreen 0x0043EF70 -- B UAE (public virtual)
//
// Four files, four InGameUIs, each measured from its own field: 0x53c to the
// placement icons, 0x824 to the mouse mode, 0x131c to the idle-worker lists,
// 0x139c to the idle-worker window. Nothing contradicted anything, and one of
// the joins is worth stating on its own -- the thirty-two idle-worker list
// heads run from +0x131c to +0x139c and the idle-worker window is the very
// next field. Two files measured to opposite ends of the same array without
// either being able to say so.
//
// The vtable is the placement file's, which is the only one of the four with
// pinned slots in it: placeBuildAvailable at 48, setPlacementStart at 51,
// setRadiusCursorNone at 71. The other two virtuals are virtual by their
// mangled names and nothing more -- no body here calls them through the table
// -- so they are declared past the pinned run rather than given a number.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct ICoord2D { Int x, y; };
struct Coord3D { float x, y, z; };
class Object;
class Drawable;
class ThingTemplate;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	unsigned char m_unreconstructed_000[0x24];
	Int m_playerIndex;					// +0x024
	unsigned char m_unreconstructed_028[0x1C4 - 0x28];
	UnsignedInt m_playerColor;				// +0x1c4
	UnsignedInt m_playerNightColor;				// +0x1c8

	Bool hasRadar() const;
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
		SCROLL = 3,
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

	unsigned char m_unreconstructed_004[0x4D10 - 4];
	ICoord2D m_pos;						// +0x4d10
};

extern Mouse *TheMouse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	char m_padding00[0x0c];
	Player *m_localPlayer;					// +0x0c
};

extern PlayerList *ThePlayerList;

// Retail's AsciiString is a one-pointer StringBase<char> view.  Keeping the
// constructors and release operation out of line leaves the calls at the
// already matched retail string bodies (0x00888BC0 and 0x00887940).
template <typename T> class StringBase
{
private:
	StringBase( const T *text );
	StringBase( const StringBase<T> &that );
	void releaseBuffer();
	friend class AsciiString;
	friend class UnicodeString;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString( const char *text )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase( text );
	}

	AsciiString( const AsciiString &that )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that );
	}

	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

	const char *str() const
	{
		return m_text ? m_text + 8 : (const char *)0x0107388B;
	}

private:
	char *m_text;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	UnicodeString( const UnicodeString &that )
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
			*(const StringBase<unsigned short> *)&that );
	}

	~UnicodeString()
	{
		((StringBase<unsigned short> *)this)->releaseBuffer();
	}

private:
	void *m_data;
};

// Retail's 0x0043251f ILT is Thing::isKindOf.  Keep this TU-local facade
// honest about the call shape while preserving the BFME ILT target.
class BFMEActionThing
{
public:
	Bool isKindOf(Int kind) const;
};


struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

class GameTextInterface
{
public:
	virtual void vfn00( void ); virtual void vfn01( void ); virtual void vfn02( void );
	virtual void vfn03( void ); virtual void vfn04( void ); virtual void vfn05( void );
	virtual void vfn06( void ); virtual void vfn07( void ); virtual void vfn08( void );
	virtual void vfn09( void );
	virtual UnicodeString fetch( const char *label, Bool *exists = 0 );	// slot 10, vtable+0x28
};

// The BFME selection state the across-screen pass refuses to run inside: two
// flag BYTES at +0x2c and +0x2d, which is what the `mov cl,[eax+0x2c]` pair in
// the body reads -- pointers there compile to dword loads and miss.
class BfmeStateDO
{
private:
	char m_padding[0x2C];

public:
	unsigned char m_bfmeFirst;				// +0x2c
	unsigned char m_bfmeSecond;				// +0x2d
};

extern GameTextInterface *TheGameText;
extern class InGameUI *TheInGameUI;
extern BfmeStateDO *g_bfmeStateDO;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	virtual void deleteInstance( UnsignedInt flags );
};

class WindowLayoutInfo;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
	virtual void slot000(); virtual void slot004(); virtual void slot008();
	virtual void slot00C(); virtual void slot010(); virtual void slot014();
	virtual void slot018(); virtual void slot01C(); virtual void slot020();
	virtual void slot024(); virtual void slot028(); virtual void slot02C();
	virtual void slot030(); virtual void slot034(); virtual void slot038();
	virtual void slot03C(); virtual void slot040(); virtual void slot044();
	virtual void slot048(); virtual void slot04C(); virtual void slot050();
	virtual void slot054(); virtual void slot058(); virtual void slot05C();
	virtual void slot060(); virtual void slot064();
	virtual GameWindow *winCreateFromScript( AsciiString file,
		WindowLayoutInfo *info, void *extra );		// slot 26, vtable+0x68
	virtual void slot06C(); virtual void slot070(); virtual void slot074();
	virtual void slot078(); virtual void slot07C(); virtual void slot080();
	virtual void slot084(); virtual void slot088(); virtual void slot08C();
	virtual void slot090(); virtual void slot094(); virtual void slot098();
	virtual void slot09C(); virtual void slot0A0(); virtual void slot0A4();
	virtual void slot0A8(); virtual void slot0AC();
	virtual void slot0B0(); virtual void slot0B4(); virtual void slot0B8();
	virtual void slot0BC(); virtual void slot0C0(); virtual void slot0C4();
	virtual void slot0C8(); virtual void slot0CC(); virtual void slot0D0();
	virtual void slot0D4(); virtual void slot0D8();
	virtual GameWindow *winGetWindowFromId( GameWindow *window, Int id );	// slot 55, vtable+0xdc
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	Int nameToKey( const char *name );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	ControlBar();
	virtual ~ControlBar();
	virtual void init();

private:
	char m_unreconstructed[0x2F4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/TerrainVisual.h
class TerrainVisual
{
public:
	virtual void reserved00(); virtual void reserved01(); virtual void reserved02();
	virtual void reserved03(); virtual void reserved04(); virtual void reserved05();
	virtual void reserved06(); virtual void reserved07(); virtual void reserved08();
	virtual void reserved09(); virtual void reserved10(); virtual void reserved11();
	virtual void reserved12(); virtual void reserved13(); virtual void reserved14();
	virtual void reserved15(); virtual void reserved16(); virtual void reserved17();
	virtual void reserved18(); virtual void reserved19(); virtual void reserved20();
	virtual void reserved21(); virtual void reserved22(); virtual void reserved23();
	virtual void reserved24(); virtual void reserved25();
	virtual void removeFactionBibDrawable(Drawable *drawable);	// slot 26, vtable+0x68
	virtual void removeAllBibs();					// slot 27, vtable+0x6c
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameClient.h
class GameClient
{
public:
	virtual void reserved00(); virtual void reserved01(); virtual void reserved02();
	virtual void reserved03(); virtual void reserved04(); virtual void reserved05();
	virtual void reserved06(); virtual void reserved07(); virtual void reserved08();
	virtual void reserved09(); virtual void reserved10(); virtual void reserved11();
	virtual void reserved12(); virtual void reserved13(); virtual void reserved14();
	virtual void reserved15(); virtual void reserved16(); virtual void reserved17();
	virtual void reserved18(); virtual void reserved19(); virtual void reserved20();
	virtual void reserved21(); virtual void reserved22(); virtual void reserved23();
	virtual void destroyDrawable(Drawable *drawable);		// slot 24, vtable+0x60
};

// The idle-worker lists are STLport list heads: one sentinel pointer each, and
// the count is the walk back round to it.
struct BfmeIdleWorkerNode
{
	BfmeIdleWorkerNode *m_next;
	BfmeIdleWorkerNode *m_prev;
	void *m_object;
};

struct BfmeIdleWorkerList
{
	BfmeIdleWorkerNode *m_head;

	Int size() const
	{
		BfmeIdleWorkerNode *node = m_head->m_next;
		Int count = 0;
		while (node != m_head)
		{
			node = node->m_next;
			++count;
		}
		return count;
	}
};

extern GameWindowManager *TheWindowManager;
extern NameKeyGenerator *TheNameKeyGenerator;
extern ControlBar *TheControlBar;
extern TerrainVisual *TheTerrainVisual;
extern GameClient *TheGameClient;

void HideControlBar( bool immediate );

class BfmeSelectionTranslator
{
public:
	void setDragSelecting();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Radar.h
class Radar
{
	unsigned char m_pad00[0x0C];
public:
	Bool m_hidden;						// +0x0c
	Bool m_radarForceOn;						// +0x0d
	Bool screenPixelToWorld(const ICoord2D *pixel, Coord3D *world);
};

// The retail call is TacticalView's vtable slot +0x164. Dummy declarations
// keep this reconstruction independent of the Zero Hour class layout.
class TacticalViewFadeShim
{
public:
#define BFME_VIEW_SLOT(n) virtual void slot##n() = 0;
	BFME_VIEW_SLOT(00) BFME_VIEW_SLOT(01) BFME_VIEW_SLOT(02) BFME_VIEW_SLOT(03)
	BFME_VIEW_SLOT(04) BFME_VIEW_SLOT(05) BFME_VIEW_SLOT(06) BFME_VIEW_SLOT(07)
	BFME_VIEW_SLOT(08) BFME_VIEW_SLOT(09) BFME_VIEW_SLOT(10) BFME_VIEW_SLOT(11)
	BFME_VIEW_SLOT(12) BFME_VIEW_SLOT(13)
	virtual void setWidth( Int width );			// slot 14, vtable+0x38
	virtual Int getWidth( void );				// slot 15, vtable+0x3c
	virtual void setHeight( Int height );			// slot 16, vtable+0x40
	virtual Int getHeight( void );				// slot 17, vtable+0x44
	virtual void setOrigin( Int x, Int y );			// slot 18, vtable+0x48
	virtual void getOrigin( Int *x, Int *y );		// slot 19, vtable+0x4c
	BFME_VIEW_SLOT(20) BFME_VIEW_SLOT(21) BFME_VIEW_SLOT(22) BFME_VIEW_SLOT(23)
	BFME_VIEW_SLOT(24) BFME_VIEW_SLOT(25) BFME_VIEW_SLOT(26) BFME_VIEW_SLOT(27)
	BFME_VIEW_SLOT(28) BFME_VIEW_SLOT(29) BFME_VIEW_SLOT(30) BFME_VIEW_SLOT(31)
	BFME_VIEW_SLOT(32) BFME_VIEW_SLOT(33) BFME_VIEW_SLOT(34) BFME_VIEW_SLOT(35)
	BFME_VIEW_SLOT(36) BFME_VIEW_SLOT(37) BFME_VIEW_SLOT(38) BFME_VIEW_SLOT(39)
	BFME_VIEW_SLOT(40) BFME_VIEW_SLOT(41) BFME_VIEW_SLOT(42) BFME_VIEW_SLOT(43)
	BFME_VIEW_SLOT(44) BFME_VIEW_SLOT(45) BFME_VIEW_SLOT(46) BFME_VIEW_SLOT(47)
	BFME_VIEW_SLOT(48) BFME_VIEW_SLOT(49) BFME_VIEW_SLOT(50) BFME_VIEW_SLOT(51)
	BFME_VIEW_SLOT(52) BFME_VIEW_SLOT(53) BFME_VIEW_SLOT(54) BFME_VIEW_SLOT(55)
	BFME_VIEW_SLOT(56) BFME_VIEW_SLOT(57) BFME_VIEW_SLOT(58) BFME_VIEW_SLOT(59)
	BFME_VIEW_SLOT(60) BFME_VIEW_SLOT(61) BFME_VIEW_SLOT(62) BFME_VIEW_SLOT(63)
	BFME_VIEW_SLOT(64) BFME_VIEW_SLOT(65) BFME_VIEW_SLOT(66) BFME_VIEW_SLOT(67)
	BFME_VIEW_SLOT(68) BFME_VIEW_SLOT(69) BFME_VIEW_SLOT(70) BFME_VIEW_SLOT(71)
	BFME_VIEW_SLOT(72) BFME_VIEW_SLOT(73) BFME_VIEW_SLOT(74) BFME_VIEW_SLOT(75)
	BFME_VIEW_SLOT(76) BFME_VIEW_SLOT(77) BFME_VIEW_SLOT(78) BFME_VIEW_SLOT(79)
	BFME_VIEW_SLOT(80) BFME_VIEW_SLOT(81) BFME_VIEW_SLOT(82) BFME_VIEW_SLOT(83)
	BFME_VIEW_SLOT(84) BFME_VIEW_SLOT(85) BFME_VIEW_SLOT(86) BFME_VIEW_SLOT(87)
	BFME_VIEW_SLOT(88)
#undef BFME_VIEW_SLOT
	virtual void screenToTerrain(const ICoord2D *pixel, Coord3D *world, Bool clamp) = 0;
};

enum CellShroudStatus { SHROUD_CLEAR = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionManager
{
public:
	CellShroudStatus getShroudStatusForPlayer(Int playerIndex, const Coord3D *pos) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/RadiusDecal.h
class RadiusDecal
{
	unsigned char m_pad00[8];
public:
	Bool m_empty;						// +0x08
	void setPosition(const Coord3D &pos);
	void update();
};

extern BfmeSelectionTranslator *TheSelectionTranslator;
extern Radar *TheRadar;
extern TacticalViewFadeShim *TheTacticalViewFadeShim;
extern PartitionManager *TheShroudManager;

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
	virtual void message( UnicodeString format, ... );	// slot 13, vtable+0x34
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
	virtual void clearMode68(Bool enabled);			// slot 26, vtable+0x68
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
	virtual void setSelecting(Bool selecting);		// slot 42, vtable+0xa8
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
	virtual Drawable *getFirstSelectedDrawable(void);		// slot 65, vtable+0x104
	virtual void slot42(void);
	virtual void slot43(void);
	virtual void slot44(void);
	virtual void slot45(void);
	virtual void slot46(void);
	virtual void setRadiusCursorNone(void);			// slot 71, vtable+0x11c
	virtual void setInputEnabled(Bool enable);		// slot 72, vtable+0x120
	virtual void slot49(void); virtual void slot4A(void); virtual void slot4B(void);
	virtual void slot4C(void); virtual void slot4D(void); virtual void slot4E(void);
	virtual void slot4F(void); virtual void slot50(void); virtual void slot51(void);
	virtual void slot52(void); virtual void slot53(void); virtual void slot54(void);
	virtual void slot55(void); virtual void slot56(void); virtual void slot57(void);
	virtual int selectMatchingAcrossScreen( void );		// slot 88, retail thunk13F6B->43EF70
	virtual int rva00448700( void );		// slot 89, retail thunk2A5E5->448700
	virtual int selectMatchingAcrossRegion( IRegion2D *region );	// slot 90
	virtual void buildRegion( const ICoord2D *anchor, const ICoord2D *dest,
		IRegion2D *region );					// slot 91

	// Virtual by their mangled names -- recreateControlBar is UAE and
	// getIdleWorkerCount EAE -- but no body here calls either through the
	// table, so nothing pins their slot numbers. They sit past the last
	// pinned entry rather than claiming one.
	virtual void recreateControlBar();

	void createControlBar()
	{
		TheWindowManager->winCreateFromScript(
			AsciiString( "ControlBar.wnd" ), 0, 0 );
		HideControlBar( true );
	}

	void setMouseCursor(Mouse::MouseCursor cursor);

protected:
	void destroyPlacementIcons(void);
	void handleRadiusCursor(void);

private:
	virtual Int getIdleWorkerCount();

	unsigned char m_unreconstructed_004[0x530];
	const ThingTemplate *m_pendingPlaceType;		// +0x534
	UnsignedInt m_pendingPlaceSourceObjectID;		// +0x538
	Drawable **m_placeIcon;					// +0x53c
	unsigned char m_unreconstructed_540[0x820 - 0x540];
	Bool m_isScrolling;					// +0x820
	Bool m_isSelecting;					// +0x821
	unsigned char m_alignMouseMode[2];
	Int m_mouseMode;					// +0x824
	Int m_mouseModeCursor;					// +0x828
	unsigned char m_unreconstructed_82c[0x838 - 0x82C];
	Bool m_inputEnabled;					// +0x838
	unsigned char m_unreconstructed_839[0x1284 - 0x839];
	RadiusDecal m_curRadiusCursor;				// +0x1284
	unsigned char m_unreconstructed_128d[0x12B0 - 0x128D];
	Bool m_modes[12];					// +0x12b0
	unsigned char m_unreconstructed_12bc[0x131C - 0x12BC];
	BfmeIdleWorkerList m_idleWorkers[32];			// +0x131c
	GameWindow *m_idleWorkerWin;				// +0x139c
};

// ?destroyPlacementIcons@InGameUI@@IAEXXZ
// Retail 0x0043AF00, 71 bytes.
void InGameUI::destroyPlacementIcons()
{
	Drawable *icon = m_placeIcon[0];

	if (icon != 0) {
		TheTerrainVisual->removeFactionBibDrawable(icon);
		TheGameClient->destroyDrawable(m_placeIcon[0]);
	}

	m_placeIcon[0] = 0;
	TheTerrainVisual->removeAllBibs();
}

// ?placeBuildAvailable@InGameUI@@UAEXPBVThingTemplate@@PAVDrawable@@@Z
// Retail 0x0043AF60, 363 bytes.
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

// ?getIdleWorkerCount@InGameUI@@EAEHXZ
// Retail 0x004422C0, 41 bytes.
Int InGameUI::getIdleWorkerCount()
{
	Int index = ThePlayerList->m_localPlayer->m_playerIndex;
	return m_idleWorkers[index].size();
}

// ?recreateControlBar@InGameUI@@UAEXXZ
// Retail 0x00442300, 279 bytes.
void InGameUI::recreateControlBar()
{
	GameWindow *window = TheWindowManager->winGetWindowFromId(
		0, TheNameKeyGenerator->nameToKey(
			AsciiString( "ControlBar.wnd" ).str() ) );
	if (window)
		window->deleteInstance( 1 );

	m_idleWorkerWin = 0;
	createControlBar();

	if (TheControlBar)
	{
		delete TheControlBar;
		TheControlBar = new ControlBar;
		TheControlBar->init();
	}
}

// ?handleRadiusCursor@InGameUI@@IAEXXZ
// The radius decal follows the mouse: through the radar's own pixel-to-world
// when the radar is up, otherwise through the tactical view, and a second
// time clamped if the first landed in shroud.
void InGameUI::handleRadiusCursor()
{
	if (m_curRadiusCursor.m_empty)
		return;

	const ICoord2D *mousePos = &TheMouse->m_pos;
	Coord3D pos;
	Bool radarOn = TheRadar->m_radarForceOn ||
		(!TheRadar->m_hidden && ThePlayerList->m_localPlayer &&
		 ThePlayerList->m_localPlayer->hasRadar());

	if (!radarOn || !TheRadar->screenPixelToWorld(mousePos, &pos))
	{
		TheTacticalViewFadeShim->screenToTerrain(mousePos, &pos, false);

		if (TheShroudManager && ThePlayerList)
		{
			Int playerIndex = ThePlayerList->m_localPlayer->m_playerIndex;
			if (TheShroudManager->getShroudStatusForPlayer(playerIndex, &pos) != SHROUD_CLEAR)
				TheTacticalViewFadeShim->screenToTerrain(mousePos, &pos, true);
		}
	}

	m_curRadiusCursor.setPosition(pos);
	m_curRadiusCursor.update();
}

// ?setInputEnabled@InGameUI@@UAEX_N@Z
// Re-enabling input resets every mode: the drag-select translator, the three
// vtable mode clears -- slot 71 is the one the input file called clearMode11C
// and the placement file calls setRadiusCursorNone -- and the twelve flags at
// +0x12b0, written out one at a time in retail's own order.
void InGameUI::setInputEnabled(Bool enable)
{
	Bool wasEnabled = m_inputEnabled;
	m_inputEnabled = enable;

	if (!wasEnabled && enable)
	{
		if (TheSelectionTranslator)
			TheSelectionTranslator->setDragSelecting();
		setSelecting(false);
		clearMode68(false);
		setRadiusCursorNone();
		m_modes[1] = false;
		m_modes[2] = false;
		m_modes[0] = false;
		m_modes[3] = false;
		m_modes[4] = false;
		m_modes[5] = false;
		m_modes[6] = false;
		m_modes[7] = false;
		m_modes[8] = false;
		m_modes[9] = false;
		m_modes[10] = false;
		m_modes[11] = false;
	}
}

// ?setMouseCursor@InGameUI@@QAEXW4MouseCursor@Mouse@@@Z
// BFME suppresses cursor changes while selection or RMB scrolling is active.
void InGameUI::setMouseCursor(Mouse::MouseCursor cursor)
{
	if (m_isSelecting || m_isScrolling)
		return;

	if (TheMouse == 0)
		return;

	TheMouse->setCursor(cursor);

	if (m_mouseMode == 2 && cursor != Mouse::ARROW && cursor != Mouse::SCROLL)
		m_mouseModeCursor = cursor;
}

// ?selectMatchingAcrossScreen@InGameUI@@UAEHXZ
// Retail 0x0043EF70. The whole screen becomes a region and the region pass
// does the work; the two message texts are the only thing this body adds.
int InGameUI::selectMatchingAcrossScreen( void )
{
	BfmeStateDO *state = g_bfmeStateDO;
	if (state != 0 && state->m_bfmeFirst != 0 && state->m_bfmeSecond != 0)
		return 0;

	ICoord2D origin;
	ICoord2D size;
	IRegion2D region;
	TheTacticalViewFadeShim->getOrigin(&origin.x, &origin.y);
	size.x = TheTacticalViewFadeShim->getWidth();
	size.y = TheTacticalViewFadeShim->getHeight();
	buildRegion(&origin, &size, &region);
	Int numSelected = selectMatchingAcrossRegion(&region);
	if (numSelected == -1)
	{
		UnicodeString message = TheGameText->fetch("GUI:NothingSelected");
		TheInGameUI->message(message);
	}
	else if (numSelected != 0)
	{
		UnicodeString message = TheGameText->fetch("GUI:SelectedAcrossScreen");
		TheInGameUI->message(message);
	}
	return numSelected;
}

// ?rva00448700@InGameUI@@UAEHXZ
// InGameUI ctor44B834 installs table10F5B38; W3D ctor6FBE18 installs
// table1120590. Both route slot89 here. Original method name is unproven.
// Retail 0x00448700, 339 bytes.  The older 0x00448729/298-byte row began
// after the shared SEH and BFME state-readiness prologue; the full retail
// function includes those 41 bytes.
int InGameUI::rva00448700( void )
{
	BfmeStateDO *state = g_bfmeStateDO;
	if (state != 0 && state->m_bfmeFirst != 0 && state->m_bfmeSecond != 0)
		return 0;

	Int numSelected = selectMatchingAcrossRegion( 0 );
	if (numSelected == -1)
	{
		UnicodeString message = TheGameText->fetch("GUI:NothingSelected");
		TheInGameUI->message(message);
	}
	else if (numSelected == 0)
	{
		Drawable *draw = TheInGameUI->getFirstSelectedDrawable();
		if (draw == 0 || draw->m_object == 0 ||
			!reinterpret_cast<const BFMEActionThing *>(draw->m_object)->isKindOf(7))
		{
			UnicodeString message = TheGameText->fetch("GUI:SelectedAcrossMap");
			TheInGameUI->message(message);
		}
	}
	else
	{
		UnicodeString message = TheGameText->fetch("GUI:SelectedAcrossMap");
		TheInGameUI->message(message);
	}
	return numSelected;
}
