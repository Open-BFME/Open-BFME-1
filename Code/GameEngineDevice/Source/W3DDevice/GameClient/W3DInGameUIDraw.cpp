// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

// Open-BFME5: W3DInGameUI::draw, retail 0x006FBFF0. The upstream control
// flow is preserved; these TU-local facades expose only the BFME slots and
// fields proven by this body.

class View {};

#define DECLARE_TEN(prefix) \
	virtual void prefix##0(); virtual void prefix##1(); \
	virtual void prefix##2(); virtual void prefix##3(); \
	virtual void prefix##4(); virtual void prefix##5(); \
	virtual void prefix##6(); virtual void prefix##7(); \
	virtual void prefix##8(); virtual void prefix##9();

class DisplaySlots
{
public:
	DECLARE_TEN(displayA)
	DECLARE_TEN(displayB)
	virtual void displayC0(); virtual void displayC1();
	virtual void displayC2(); virtual void displayC3();
	virtual void displayC4(); virtual void displayC5();
	virtual void displayC6(); virtual void displayC7();
	virtual void displayC8();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Display.h
class Display : public DisplaySlots
{
public:
	virtual View *getFirstView();             // +0x74
	virtual View *getNextView(View *view);    // +0x78
};

class WindowManagerSlots
{
public:
	DECLARE_TEN(windowA)
	DECLARE_TEN(windowB)
	DECLARE_TEN(windowC)
	virtual void windowD0(); virtual void windowD1();
	virtual void windowD2(); virtual void windowD3();
	virtual void windowD4(); virtual void windowD5();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager : public WindowManagerSlots
{
public:
	virtual void winRepaintWindows();         // +0x90

private:
	unsigned char m_unmodelled_04[0x34];

public:
	int m_drawState;                          // +0x38
};

class W3DInGameUISlots
{
public:
	virtual void draw();                      // slot zero, overridden below
	DECLARE_TEN(inGameA)                      // slots 1..10
	DECLARE_TEN(inGameB)                      // slots 11..20
	DECLARE_TEN(inGameC)                      // slots 21..30
	DECLARE_TEN(inGameD)                      // slots 31..40
	DECLARE_TEN(inGameE)                      // slots 41..50
	DECLARE_TEN(inGameF)                      // slots 51..60
	DECLARE_TEN(inGameG)                      // slots 61..70
	virtual void inGameH1(); virtual void inGameH2();
	virtual void inGameH3();                  // slots 71..73
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DInGameUI.h
#include "ascii_string.h"

extern const char g_bfmeEmptyAscii[];

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#define NULL 0

class View;

class Matrix3D
{
	Real Row[3][4];
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class HAnimClass
{
public:
	virtual void Delete_This();
	void Release_Ref()
	{
		NumRefs--;
		if (NumRefs == 0)
			Delete_This();
	}

private:
	Int NumRefs;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/rendobj.h
class RenderObjClass
{
public:
	enum AnimMode { ANIM_MODE_MANUAL = 0, ANIM_MODE_LOOP, ANIM_MODE_ONCE };

	DECLARE_TEN(slotA)                        // 0..9
	DECLARE_TEN(slotB)                        // 10..19
	virtual void slotC0();                    // 20
	virtual void Set_Transform(const Matrix3D &m);            // 21, +0x54
	virtual void slotC2(); virtual void slotC3();
	virtual void slotC4(); virtual void slotC5();
	virtual void slotC6(); virtual void slotC7();
	virtual void slotC8(); virtual void slotC9();
	DECLARE_TEN(slotD)                        // 30..39
	virtual void slotE0(); virtual void slotE1();
	virtual void slotE2(); virtual void slotE3();
	virtual void Set_Animation(HAnimClass *anim, Real frame, Int mode); // 44, +0xb0
	virtual void slotE5(); virtual void slotE6();
	virtual void slotE7(); virtual void slotE8(); virtual void slotE9();
	DECLARE_TEN(slotF)                        // 50..59
	DECLARE_TEN(slotG)                        // 60..69
	DECLARE_TEN(slotH)                        // 70..79
	DECLARE_TEN(slotI)                        // 80..89
	virtual void slotJ0(); virtual void slotJ1();
	virtual void slotJ2(); virtual void slotJ3();
	virtual void slotJ4(); virtual void slotJ5();
	virtual void slotJ6(); virtual void slotJ7();
	virtual void slotJ8();                    // 90..98
	virtual Int Is_Hidden() const;            // 99, +0x18c
	virtual void Set_Hidden(Int onoff);       // 100, +0x190
};

// W3DDisplay::m_3DScene (0x012F8058); slots +0x08 / +0x0c
class RTS3DScene
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void Add_Render_Object(RenderObjClass *obj);
	virtual void Remove_Render_Object(RenderObjClass *obj);
};

class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;
};

class GameClient
{
public:
	DECLARE_TEN(slotA)                        // 0..9
	DECLARE_TEN(slotB)                        // 10..19
	virtual void slotC0(); virtual void slotC1();
	virtual void slotC2(); virtual void slotC3();
	virtual void slotC4(); virtual void slotC5();
	virtual UnsignedInt getFrame();           // 26, +0x68
};

class TerrainLogic
{
public:
	DECLARE_TEN(slotA)                        // 0..9
	virtual void slotB0(); virtual void slotB1();
	virtual void slotB2(); virtual void slotB3();
	virtual void slotB4(); virtual void slotB5();
	virtual void slotB6(); virtual void slotB7();
	virtual PathfindLayerEnum alignOnTerrain(Real angle, const Coord3D &pos, Bool stickToGround, Matrix3D &mtx); // 18, +0x48
	virtual Bool isUnderwater(Real x, Real y, Real *waterZ = NULL, Real *terrainZ = NULL); // 19, +0x4c
};

class GlobalData
{
public:
	unsigned char m_unmodelled_00[0x0c];
	AsciiString m_moveHintName;               // +0x0c
};


extern GameClient *TheGameClient;
extern GlobalData *TheWritableGlobalData;
extern TerrainLogic *TheTerrainLogic;

extern RenderObjClass *Create_Render_Obj(const char *name);
extern HAnimClass *Get_HAnim(const char *name);
extern void makeAlignToNormalMatrix(Real angle, const Coord3D &pos, const Coord3D &normal, Matrix3D &mtx);

// Retail inlines AsciiString::str(): the text follows an 8-byte header and an
// empty string reads the shared 0x0107388B literal.
inline const char *asciiText(const AsciiString &s)
{
	const char *const &data = *(const char *const *)&s;
	return data ? data + 8 : g_bfmeEmptyAscii;
}

#define REF_PTR_RELEASE(x) { if (x) { (x)->Release_Ref(); (x) = NULL; } }

enum { MAX_MOVE_HINTS = 25 };

struct MoveHintStruct
{
	Coord3D pos;
	UnsignedInt frame;
	Bool byte_10;
};


class W3DInGameUI : public W3DInGameUISlots
{
public:
	virtual void draw();
	virtual void preDraw();                   // +0x128, slot 74
	virtual void postDraw();                  // +0x12c, slot 75
	DECLARE_TEN(inGameTailA)                  // slots 76..85
	DECLARE_TEN(inGameTailB)                  // slots 86..95
	DECLARE_TEN(inGameTailC)                  // slots 96..105
	virtual void inGameTailD0(); virtual void inGameTailD1();
	virtual void inGameTailD2(); virtual void inGameTailD3();
	virtual void drawSelectionRegion();       // +0x1b8, slot 110
	virtual void rva006FC5A0Slot(View *view);   // +0x1bc, slot 111; routes to drawMoveHints
	virtual void drawAttackHints(View *view);  // +0x1c0, slot 112
	virtual void drawPlaceAngle(View *view);   // +0x1c4, slot 113

private:
	unsigned char m_unmodelled_04[0x1c];
	bool m_isDragSelecting;                   // +0x20
    unsigned char m_unmodelled_21[0x38 - 0x21];
    MoveHintStruct m_moveHint[MAX_MOVE_HINTS];                // +0x38
    unsigned char m_unmodelled_22c[0x13ac - 0x22c];
    RenderObjClass *m_moveHintRenderObj[MAX_MOVE_HINTS];     // +0x13ac
    HAnimClass *m_moveHintAnim[MAX_MOVE_HINTS];              // +0x1410
};

#undef DECLARE_TEN

extern Display *TheDisplay;
extern GameWindowManager *TheWindowManager;

void W3DInGameUI::draw()
{
	int drawState = TheWindowManager->m_drawState;
	switch (drawState)
	{
		case -1:
		case 1:
			break;
		case 0:
			TheWindowManager->winRepaintWindows();
			return;
		default:
			return;
	}

	preDraw();
	if (m_isDragSelecting)
		drawSelectionRegion();

	if (TheDisplay)
	{
		for (View *view = TheDisplay->getFirstView(); view;
			 view = TheDisplay->getNextView(view))
		{
			rva006FC5A0Slot(view);
			drawAttackHints(view);
			drawPlaceAngle(view);
		}
	}

	postDraw();
	TheWindowManager->winRepaintWindows();
}
