// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

typedef int Int;
typedef bool Bool;

struct ICoord2D { Int x, y; };
struct Coord3D { float x, y, z; };

class Player
{
	unsigned char m_pad00[0x24];
public:
	Int m_playerIndex;
	Bool hasRadar() const;
};

class PlayerList
{
	unsigned char m_pad00[0x0C];
public:
	Player *m_localPlayer;
};

class Mouse
{
	unsigned char m_pad00[0x4D10];
public:
	ICoord2D m_pos;
};

class Radar
{
	unsigned char m_pad00[0x0C];
public:
	Bool m_hidden;
	Bool m_forced;
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
	BFME_VIEW_SLOT(12) BFME_VIEW_SLOT(13) BFME_VIEW_SLOT(14) BFME_VIEW_SLOT(15)
	BFME_VIEW_SLOT(16) BFME_VIEW_SLOT(17) BFME_VIEW_SLOT(18) BFME_VIEW_SLOT(19)
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
class PartitionManager
{
public:
	CellShroudStatus getShroudStatusForPlayer(Int playerIndex, const Coord3D *pos) const;
};

class RadiusDecal
{
	unsigned char m_pad00[8];
public:
	Bool m_empty;
	void setPosition(const Coord3D &pos);
	void update();
};

extern Radar *TheRadar;
extern Mouse *TheMouse;
extern PlayerList *ThePlayerList;
extern TacticalViewFadeShim *TheTacticalViewFadeShim;
extern PartitionManager *TheShroudManager;

class InGameUI
{
protected:
	unsigned char m_pad00[0x1284];
	RadiusDecal m_curRadiusCursor;
	void handleRadiusCursor();
};

void InGameUI::handleRadiusCursor()
{
	if (m_curRadiusCursor.m_empty)
		return;

	const ICoord2D *mousePos = &TheMouse->m_pos;
	Coord3D pos;
	Bool radarOn = TheRadar->m_forced ||
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
