// ?rva005B5590@BfmeOwnVVD@@QAEXXZ
// partial score=0.9978 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc
extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
// Retail 0x005B5590 (1791 bytes): the per-frame scroll/camera update of the
// class whose constructor is 0x005B5470 (BfmeOwnVVD; singleton 0x012F4C84,
// vftable 0x0110DE48), called once per client frame from the matched
// ClientUpdate004329D0::update. The body is Zero Hour's LookAtTranslator
// MSG_FRAME_TICK case (LookAtXlat.cpp) moved into its own member: the
// forced-stop test, the RMB / key / screen-edge scroll switch on m_148, the
// setScrollAmount + scrollBy pair, and the MSG_SET_REPLAY_CAMERA (0x446)
// ViewLocation message; BFME adds an edge-scroll ramp (m_14c, GlobalData
// +0xB6C/+0xB70), a scroll hook at 0x012F7048, anchor resets from scrollBy's
// edge flags, rotate keys (m_154..m_157) and key-release polling. No symbol
// names the member, so it keeps the address token.

// Non-POD as in retail: setScrollAmount receives it by value with a saved
// argument address; the constructors and destructor are inline here.
class Coord2D
{
public:
	Coord2D() {}
	Coord2D(const Coord2D &that) { x = that.x; y = that.y; }
	~Coord2D() {}
	void normalize();
	float x, y;
};
struct Coord3D { float x, y, z; };
struct ICoord2D { int x, y; };

// ViewLocation (0x20 bytes; the constructor's BfmeElemVVD[8] at +0x48).
struct ViewLocation
{
	unsigned char m_valid;
	Coord3D m_pos;
	float m_angle, m_pitch, m_zoom, m_fov;
	ViewLocation()
	{
		m_valid = 0;
		m_pos.x = 0; m_pos.y = 0; m_pos.z = 0;
		m_angle = m_pitch = m_zoom = m_fov = 0.0f;
	}
};

struct GlobalData
{
	unsigned char m_pad000[0xb64];
	float m_horizontalScrollSpeedFactor;	// +0xB64
	float m_verticalScrollSpeedFactor;	// +0xB68
	float m_b6c;				// +0xB6C edge-scroll factor
	int m_b70;				// +0xB70 edge-scroll ramp time
	unsigned char m_pad074[0xbbc - 0xb74];
	float m_keyboardScrollFactor;		// +0xBBC
	unsigned char m_padbc0[0xc0c - 0xbc0];
	unsigned char m_c0c;			// +0xC0C replay-camera switch
	unsigned char m_padc0d[0xcc8 - 0xc0d];
	float m_keyboardCameraRotateSpeed;	// +0xCC8
};
extern GlobalData *TheWritableGlobalData;

class GameMessage
{
public:
	void appendIntegerArgument(int arg);
	void appendRealArgument(float arg);
	void appendLocationArgument(const Coord3D &arg);
	void appendPixelArgument(const ICoord2D &arg);
};

class GameLogic
{
public:
	bool isInSinglePlayerGame();
	unsigned char m_pad000[0x10c];
	int m_gameMode;			// +0x10C
};
extern GameLogic *TheGameLogic;

struct GameEngine { unsigned char m_pad00[0x30]; int m_30; };
extern GameEngine *TheGameEngine;

struct Rva005A4600Slot { int x, y; };
class Rva005A4600Arr { public: Rva005A4600Slot *slot(); };
struct Mouse { unsigned char m_pad0000[0x4da8]; int m_currentCursor; };
extern Mouse *TheMouse;

// 0x005A31C0 (ILT 0x00040DD1): key-state bit test; callers use it as a bool.
class Rva005A31C0Object { public: bool test(unsigned char key); };
class Keyboard;
extern Keyboard *TheKeyboard;

class BfmeW1095 { public: void bfmeGo1095B(); };	// 0x005B52B0, Zero Hour's stopScrolling
class InGameUI
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
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5C() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual void slot68() = 0;
	virtual void slot6C() = 0;
	virtual void slot70() = 0;
	virtual void slot74() = 0;
	virtual void slot78() = 0;
	virtual void slot7C() = 0;
	virtual void slot80() = 0;
	virtual void slot84() = 0;
	virtual void slot88() = 0;
	virtual void slot8C() = 0;
	virtual void slot90() = 0;
	virtual void slot94() = 0;
	virtual void slot98() = 0;
	virtual void slot9C() = 0;
	virtual void slotA0() = 0;
	virtual bool isScrolling() = 0;
	virtual void slotA8() = 0;
	virtual void slotAC() = 0;
	virtual void setScrollAmount(Coord2D amt) = 0;
	unsigned char m_pad004[0xd - 4];
	unsigned char m_0d;
	unsigned char m_0e;
	unsigned char m_pad00f[0x12bd - 0xf];
	unsigned char m_moveRMBScrollAnchor;
};
class View
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
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual int scrollBy(Coord2D *delta) = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual void slot68() = 0;
	virtual void slot6C() = 0;
	virtual void slot70() = 0;
	virtual void slot74() = 0;
	virtual void slot78() = 0;
	virtual void slot7C() = 0;
	virtual void slot80() = 0;
	virtual void slot84() = 0;
	virtual void slot88() = 0;
	virtual void slot8C() = 0;
	virtual void slot90() = 0;
	virtual void slot94() = 0;
	virtual void slot98() = 0;
	virtual void slot9C() = 0;
	virtual void slotA0() = 0;
	virtual void slotA4() = 0;
	virtual void slotA8() = 0;
	virtual void slotAC() = 0;
	virtual void slotB0() = 0;
	virtual void slotB4() = 0;
	virtual void slotB8() = 0;
	virtual void slotBC() = 0;
	virtual void slotC0() = 0;
	virtual void slotC4() = 0;
	virtual void slotC8() = 0;
	virtual void slotCC() = 0;
	virtual void slotD0() = 0;
	virtual void slotD4() = 0;
	virtual void slotD8() = 0;
	virtual void slotDC() = 0;
	virtual void slotE0() = 0;
	virtual void slotE4() = 0;
	virtual void slotE8() = 0;
	virtual void slotEC() = 0;
	virtual void slotF0() = 0;
	virtual void slotF4() = 0;
	virtual void setAngle(float angle) = 0;
	virtual float getAngle() = 0;
	virtual void slot100() = 0;
	virtual void slot104() = 0;
	virtual void slot108() = 0;
	virtual void slot10C() = 0;
	virtual void slot110() = 0;
	virtual void slot114() = 0;
	virtual void slot118() = 0;
	virtual void slot11C() = 0;
	virtual void slot120() = 0;
	virtual void slot124() = 0;
	virtual void slot128() = 0;
	virtual void slot12C() = 0;
	virtual void slot130() = 0;
	virtual void slot134() = 0;
	virtual void slot138() = 0;
	virtual void slot13C() = 0;
	virtual void slot140() = 0;
	virtual void slot144() = 0;
	virtual void slot148() = 0;
	virtual void slot14C() = 0;
	virtual void slot150() = 0;
	virtual void slot154() = 0;
	virtual void slot158() = 0;
	virtual void slot15C() = 0;
	virtual void slot160() = 0;
	virtual void slot164() = 0;
	virtual void slot168() = 0;
	virtual void getLocation(ViewLocation *location) = 0;
};
class Display
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
	virtual unsigned int getWidth() = 0;
	virtual unsigned int getHeight() = 0;
};
class MessageStream
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
	virtual GameMessage *appendMessage(int type) = 0;
};
class BfmeHostESM
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14(Coord2D *delta, int flags) = 0;
	unsigned char m_pad004[4];
	unsigned char m_08;
};

extern InGameUI *TheInGameUI;
extern View *TheTacticalView;
extern Display *TheDisplay;
extern MessageStream *TheMessageStream;
extern BfmeHostESM *g_bfmeStateDF;
extern int (*g_bfmeNowVNH)();

static bool scrollDir[4];

inline float sqr(float x) { return x * x; }

class BfmeElemVVD
{
public:
	char m_bfmePad00[0x20];
};

class BfmeOwnVVD
{
public:
	virtual void bfmeSlot0VVD();
	void rva005B5590();

	int m_anchorX;				// +0x04
	int m_anchorY;				// +0x08
	unsigned int m_0c;			// +0x0c
	unsigned int m_10;			// +0x10
	ICoord2D m_currentPos;			// +0x14
	unsigned char m_1c;
	unsigned char m_pad1d[3];
	unsigned int m_20, m_24, m_28, m_2c, m_30, m_34;
	unsigned char m_isScrolling;		// +0x38
	unsigned char m_39, m_3a, m_3b, m_3c;
	unsigned char m_pad3d[3];
	unsigned int m_40, m_44;
	BfmeElemVVD m_bfme48[8];		// +0x48
	int m_scrollType;			// +0x148
	int m_scrollStart;			// +0x14c
	unsigned int m_150;
	unsigned char m_154, m_155, m_156, m_157;
};

// ?rva005B5590@BfmeOwnVVD@@QAEXXZ
void BfmeOwnVVD::rva005B5590()
{
	Coord2D offset;
	offset.x = 0;
	offset.y = 0;

	if (m_isScrolling && !TheInGameUI->isScrolling())
	{
		TheInGameUI->setScrollAmount(offset);
		((BfmeW1095 *)this)->bfmeGo1095B();
	}
	else if (m_isScrolling)
	{
		switch (m_scrollType)
		{
		case 1:
			{
				{
				ICoord2D mouse = *(ICoord2D *)((Rva005A4600Arr *)TheMouse)->slot();
				int dy = m_currentPos.y - mouse.y;
				if (TheInGameUI->m_moveRMBScrollAnchor)
				{
					int maxX = TheDisplay->getWidth() / 2;
					int maxY = TheDisplay->getHeight() / 2;
					if (m_currentPos.x + maxX < m_anchorX)
						m_anchorX = m_currentPos.x + maxX;
					else if (m_currentPos.x - maxX > m_anchorX)
						m_anchorX = m_currentPos.x - maxX;
					if (m_currentPos.y + maxY < m_anchorY)
						m_anchorY = m_currentPos.y + maxY;
					else if (dy - maxY > m_anchorY)
						m_anchorY = m_currentPos.y - maxY;
				}
				}
				GlobalData *gd = TheWritableGlobalData;
				offset.x = gd->m_horizontalScrollSpeedFactor * (m_currentPos.x - m_anchorX);
				offset.y = gd->m_verticalScrollSpeedFactor * (m_currentPos.y - m_anchorY);
				{
				Coord2D vec;
				vec.x = offset.x;
				vec.y = offset.y;
				vec.normalize();
				offset.x += gd->m_horizontalScrollSpeedFactor * vec.x * sqr(gd->m_keyboardScrollFactor);
				offset.y += gd->m_verticalScrollSpeedFactor * (vec.y * sqr(gd->m_keyboardScrollFactor));
			}
				}
			break;
		case 2:
			{
				if (scrollDir[0])
					offset.y -= TheWritableGlobalData->m_keyboardScrollFactor * TheWritableGlobalData->m_verticalScrollSpeedFactor * 100.0f;
				if (scrollDir[1])
					offset.y += TheWritableGlobalData->m_keyboardScrollFactor * TheWritableGlobalData->m_verticalScrollSpeedFactor * 100.0f;
				if (scrollDir[2])
					offset.x -= TheWritableGlobalData->m_keyboardScrollFactor * TheWritableGlobalData->m_horizontalScrollSpeedFactor * 100.0f;
				if (scrollDir[3])
					offset.x += TheWritableGlobalData->m_keyboardScrollFactor * TheWritableGlobalData->m_horizontalScrollSpeedFactor * 100.0f;
			}
			break;
		case 3:
			{
				int amount;
				int elapsed = g_bfmeNowVNH() - m_scrollStart;
				if (elapsed > TheWritableGlobalData->m_b70)
					amount = 100;
				else
					amount = elapsed * 100 / TheWritableGlobalData->m_b70;
				unsigned int height = TheDisplay->getHeight();
				unsigned int width = TheDisplay->getWidth();
				GlobalData *gd = TheWritableGlobalData;
				if (m_currentPos.y < 3)
					offset.y -= gd->m_keyboardScrollFactor * gd->m_b6c * gd->m_verticalScrollSpeedFactor * amount;
				if (m_currentPos.y >= height - 3)
					offset.y += gd->m_keyboardScrollFactor * gd->m_b6c * gd->m_verticalScrollSpeedFactor * amount;
				if (m_currentPos.x < 3)
					offset.x -= gd->m_keyboardScrollFactor * gd->m_b6c * gd->m_horizontalScrollSpeedFactor * amount;
				if (m_currentPos.x >= width - 3)
					offset.x += gd->m_keyboardScrollFactor * gd->m_b6c * gd->m_horizontalScrollSpeedFactor * amount;
			}
			break;
		}

		if (g_bfmeStateDF && g_bfmeStateDF->m_08)
		{
			g_bfmeStateDF->slot14(&offset, 0);
		}
		else
		{
			TheInGameUI->setScrollAmount(offset);
			int edges = TheTacticalView->scrollBy(&offset);
			if (edges && m_scrollType == 1)
			{
				float angle = (float)fabs(TheTacticalView->getAngle());
				bool turned = false;
				if (angle > 0.78539819f && angle < 2.3561945f)
					turned = true;
				if (edges & 3)
				{
					if (turned)
						m_anchorY = m_currentPos.y;
					else
						m_anchorX = m_currentPos.x;
				}
				if (edges & 0xc)
				{
					if (turned)
						m_anchorX = m_currentPos.x;
					else
						m_anchorY = m_currentPos.y;
				}
			}
		}
	}
	else
		TheInGameUI->setScrollAmount(offset);

	if (TheInGameUI->m_0d && TheInGameUI->m_0e)
	{
		if (m_154)
			TheTacticalView->setAngle(TheTacticalView->getAngle() - TheWritableGlobalData->m_keyboardCameraRotateSpeed);
		if (m_155)
			TheTacticalView->setAngle(TheTacticalView->getAngle() + TheWritableGlobalData->m_keyboardCameraRotateSpeed);
		if (m_156)
			TheTacticalView->slot130();
		if (m_157)
			TheTacticalView->slot134();
	}

	if (TheWritableGlobalData->m_c0c && TheGameEngine->m_30 == 1 &&
		(TheGameLogic->isInSinglePlayerGame() || TheGameLogic->m_gameMode == 2 ||
		 TheGameLogic->m_gameMode == 1 || TheGameLogic->m_gameMode == 5))
	{
		ViewLocation currentView;
		TheTacticalView->getLocation(&currentView);
		GameMessage *msg = TheMessageStream->appendMessage(0x446);
		msg->appendLocationArgument(currentView.m_pos);
		msg->appendRealArgument(currentView.m_angle);
		msg->appendRealArgument(currentView.m_pitch);
		msg->appendRealArgument(currentView.m_zoom);
		msg->appendRealArgument(currentView.m_fov);
		msg->appendIntegerArgument(TheMouse->m_currentCursor);
		msg->appendPixelArgument(m_currentPos);
	}

	if (m_isScrolling)
	{
		Rva005A31C0Object *keys = (Rva005A31C0Object *)TheKeyboard;
		if (!((Rva005A31C0Object *)TheKeyboard)->test(0xc8)) scrollDir[0] = false;
		if (!((Rva005A31C0Object *)TheKeyboard)->test(0xd0)) scrollDir[1] = false;
		if (!((Rva005A31C0Object *)TheKeyboard)->test(0xcb)) scrollDir[2] = false;
		if (!((Rva005A31C0Object *)TheKeyboard)->test(0xcd)) scrollDir[3] = false;
		if (!scrollDir[0] && !scrollDir[1] && !scrollDir[2] && !scrollDir[3] && m_scrollType == 2)
			((BfmeW1095 *)this)->bfmeGo1095B();
	}
	if (m_154 && !((Rva005A31C0Object *)TheKeyboard)->test(0x4b)) m_154 = false;
	if (m_155 && !((Rva005A31C0Object *)TheKeyboard)->test(0x4d)) m_155 = false;
	if (m_156 && !((Rva005A31C0Object *)TheKeyboard)->test(0x48)) m_156 = false;
	if (m_157 && !((Rva005A31C0Object *)TheKeyboard)->test(0x50)) m_157 = false;
}
