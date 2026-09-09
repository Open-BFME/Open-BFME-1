// cl: /DNDEBUG /DWIN32 /MD /EHsc
// BFME W3D left HUD callback.  The retail callback uses the BFME variants of
// the subsystem vtables: videoBuffer is at InGameUI +0x13c, drawVideoBuffer is
// at Display +0xe0, and Radar::draw is at +0x1c.  Keep those ABI declarations
// local to this callback; the common headers describe the Zero Hour slots.

typedef int Int;
typedef bool Bool;

class VideoBuffer;
class WinInstanceData;

class GameWindow
{
public:
	Int winGetScreenPosition(Int *x, Int *y);
	Int winGetSize(Int *width, Int *height);
};

class Player
{
public:
	Bool hasRadar(void) const;
};

class Rva002EE330PlayerList
{
private:
	char m_padding00[0x0c];

public:
	Player *m_localPlayer;
};

extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

class InGameUI
{
public:
#define BFME_UI_SLOT(n) virtual void slot##n(void) = 0;
	BFME_UI_SLOT(00) BFME_UI_SLOT(01) BFME_UI_SLOT(02) BFME_UI_SLOT(03)
	BFME_UI_SLOT(04) BFME_UI_SLOT(05) BFME_UI_SLOT(06) BFME_UI_SLOT(07)
	BFME_UI_SLOT(08) BFME_UI_SLOT(09) BFME_UI_SLOT(10) BFME_UI_SLOT(11)
	BFME_UI_SLOT(12) BFME_UI_SLOT(13) BFME_UI_SLOT(14) BFME_UI_SLOT(15)
	BFME_UI_SLOT(16) BFME_UI_SLOT(17) BFME_UI_SLOT(18) BFME_UI_SLOT(19)
	BFME_UI_SLOT(20) BFME_UI_SLOT(21) BFME_UI_SLOT(22) BFME_UI_SLOT(23)
	BFME_UI_SLOT(24) BFME_UI_SLOT(25) BFME_UI_SLOT(26) BFME_UI_SLOT(27)
	BFME_UI_SLOT(28) BFME_UI_SLOT(29) BFME_UI_SLOT(30) BFME_UI_SLOT(31)
	BFME_UI_SLOT(32) BFME_UI_SLOT(33) BFME_UI_SLOT(34) BFME_UI_SLOT(35)
	BFME_UI_SLOT(36) BFME_UI_SLOT(37) BFME_UI_SLOT(38) BFME_UI_SLOT(39)
	BFME_UI_SLOT(40) BFME_UI_SLOT(41) BFME_UI_SLOT(42) BFME_UI_SLOT(43)
	BFME_UI_SLOT(44) BFME_UI_SLOT(45) BFME_UI_SLOT(46) BFME_UI_SLOT(47)
	BFME_UI_SLOT(48) BFME_UI_SLOT(49) BFME_UI_SLOT(50) BFME_UI_SLOT(51)
	BFME_UI_SLOT(52) BFME_UI_SLOT(53) BFME_UI_SLOT(54) BFME_UI_SLOT(55)
	BFME_UI_SLOT(56) BFME_UI_SLOT(57) BFME_UI_SLOT(58) BFME_UI_SLOT(59)
	BFME_UI_SLOT(60) BFME_UI_SLOT(61) BFME_UI_SLOT(62) BFME_UI_SLOT(63)
	BFME_UI_SLOT(64) BFME_UI_SLOT(65) BFME_UI_SLOT(66) BFME_UI_SLOT(67)
	BFME_UI_SLOT(68) BFME_UI_SLOT(69) BFME_UI_SLOT(70) BFME_UI_SLOT(71)
	BFME_UI_SLOT(72) BFME_UI_SLOT(73) BFME_UI_SLOT(74) BFME_UI_SLOT(75)
	BFME_UI_SLOT(76) BFME_UI_SLOT(77) BFME_UI_SLOT(78)
#undef BFME_UI_SLOT
	virtual VideoBuffer *videoBuffer(void) = 0;
};

extern InGameUI *TheInGameUI;

class Display
{
public:
#define BFME_DISPLAY_SLOT(n) virtual void slot##n(void) = 0;
	BFME_DISPLAY_SLOT(00) BFME_DISPLAY_SLOT(01) BFME_DISPLAY_SLOT(02) BFME_DISPLAY_SLOT(03)
	BFME_DISPLAY_SLOT(04) BFME_DISPLAY_SLOT(05) BFME_DISPLAY_SLOT(06) BFME_DISPLAY_SLOT(07)
	BFME_DISPLAY_SLOT(08) BFME_DISPLAY_SLOT(09) BFME_DISPLAY_SLOT(10) BFME_DISPLAY_SLOT(11)
	BFME_DISPLAY_SLOT(12) BFME_DISPLAY_SLOT(13) BFME_DISPLAY_SLOT(14) BFME_DISPLAY_SLOT(15)
	BFME_DISPLAY_SLOT(16) BFME_DISPLAY_SLOT(17) BFME_DISPLAY_SLOT(18) BFME_DISPLAY_SLOT(19)
	BFME_DISPLAY_SLOT(20) BFME_DISPLAY_SLOT(21) BFME_DISPLAY_SLOT(22) BFME_DISPLAY_SLOT(23)
	BFME_DISPLAY_SLOT(24) BFME_DISPLAY_SLOT(25) BFME_DISPLAY_SLOT(26) BFME_DISPLAY_SLOT(27)
	BFME_DISPLAY_SLOT(28) BFME_DISPLAY_SLOT(29) BFME_DISPLAY_SLOT(30) BFME_DISPLAY_SLOT(31)
	BFME_DISPLAY_SLOT(32) BFME_DISPLAY_SLOT(33) BFME_DISPLAY_SLOT(34) BFME_DISPLAY_SLOT(35)
	BFME_DISPLAY_SLOT(36) BFME_DISPLAY_SLOT(37) BFME_DISPLAY_SLOT(38) BFME_DISPLAY_SLOT(39)
	BFME_DISPLAY_SLOT(40) BFME_DISPLAY_SLOT(41) BFME_DISPLAY_SLOT(42) BFME_DISPLAY_SLOT(43)
	BFME_DISPLAY_SLOT(44) BFME_DISPLAY_SLOT(45) BFME_DISPLAY_SLOT(46) BFME_DISPLAY_SLOT(47)
	BFME_DISPLAY_SLOT(48) BFME_DISPLAY_SLOT(49) BFME_DISPLAY_SLOT(50) BFME_DISPLAY_SLOT(51)
	BFME_DISPLAY_SLOT(52) BFME_DISPLAY_SLOT(53) BFME_DISPLAY_SLOT(54) BFME_DISPLAY_SLOT(55)
#undef BFME_DISPLAY_SLOT
	virtual void drawVideoBuffer(VideoBuffer *buffer, float startX, float startY,
		float endX, float endY, Int color = -1) = 0;
};

extern Display *TheDisplay;

class Radar
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void draw(Int pixelX, Int pixelY, Int width, Int height, Int color = -1) = 0;

	Bool isRadarHidden(void) const
	{
		return *(const Bool *)((const char *)this + 0x0c);
	}

	Bool isRadarForced(void) const
	{
		return *(const Bool *)((const char *)this + 0x0d);
	}
};

extern Radar *TheRadar;

struct ICoord2D
{
	Int x;
	Int y;
};

// ?W3DLeftHUDDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
void __cdecl W3DLeftHUDDraw(GameWindow *window, WinInstanceData *instData)
{
	Player *player = Rva002EE330ThePlayers->m_localPlayer;
	VideoBuffer *video = TheInGameUI->videoBuffer();
	if (video)
	{
		ICoord2D pos, size;
		window->winGetScreenPosition(&pos.x, &pos.y);
		window->winGetSize(&size.x, &size.y);
		TheDisplay->drawVideoBuffer(video, pos.x, pos.y,
			pos.x + size.x, pos.y + size.y);
	}
	else if (TheRadar->isRadarForced() ||
		(!TheRadar->isRadarHidden() && player->hasRadar()))
	{
		ICoord2D pos, size;
		window->winGetScreenPosition(&pos.x, &pos.y);
		window->winGetSize(&size.x, &size.y);
		TheRadar->draw(pos.x + 1, pos.y + 1, size.x - 2, size.y - 2);
	}
}
