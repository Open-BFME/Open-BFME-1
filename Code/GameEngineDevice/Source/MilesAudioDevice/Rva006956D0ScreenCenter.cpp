// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Screen-center to world for the Miles audio owner that already has
// Rva00696040Checker at +0x604 mode. Address-derived name.

struct ICoord2D
{
	int x;
	int y;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Display
{
public:
	virtual void v00() = 0;
	virtual void v04() = 0;
	virtual void v08() = 0;
	virtual void v0C() = 0;
	virtual void v10() = 0;
	virtual void v14() = 0;
	virtual void v18() = 0;
	virtual void v1C() = 0;
	virtual void v20() = 0;
	virtual void v24() = 0;
	virtual void v28() = 0;
	virtual unsigned int getWidth() = 0;
	virtual unsigned int getHeight() = 0;
};

class Glo012F7048Shim
{
public:
	virtual void v00() = 0;
	virtual void v04() = 0;
	virtual void v08() = 0;
	virtual void v0C() = 0;
	virtual void v10() = 0;
	virtual void v14() = 0;
	virtual void v18() = 0;
	virtual void v1C() = 0;
	virtual void mapScreenToWorld(const ICoord2D *screen, Coord3D *world) = 0;
};

class TacticalViewFadeShim
{
public:
#define BFME_VIEW_SLOT(n) virtual void slot##n() = 0;
	BFME_VIEW_SLOT(00) BFME_VIEW_SLOT(01) BFME_VIEW_SLOT(02) BFME_VIEW_SLOT(03)
	BFME_VIEW_SLOT(04) BFME_VIEW_SLOT(05) BFME_VIEW_SLOT(06) BFME_VIEW_SLOT(07)
	BFME_VIEW_SLOT(08) BFME_VIEW_SLOT(09) BFME_VIEW_SLOT(10) BFME_VIEW_SLOT(11)
	BFME_VIEW_SLOT(12) BFME_VIEW_SLOT(13) BFME_VIEW_SLOT(14)
#undef BFME_VIEW_SLOT
	virtual int getWidth() = 0;
	virtual void slot16() = 0;
	virtual int getHeight() = 0;
#define BFME_VIEW_SLOT(n) virtual void slot##n() = 0;
	BFME_VIEW_SLOT(18) BFME_VIEW_SLOT(19)
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
	virtual bool screenToTerrain(const ICoord2D *pixel, Coord3D *world, bool terrainOnly) = 0;
};

extern Display *TheDisplay;
extern Glo012F7048Shim *g_bfmeStateDF;
extern TacticalViewFadeShim *TheTacticalViewFadeShim;

class Rva006956D0Owner
{
	char m_pad604[0x604];
	int m_mode;

public:
	bool getScreenCenterWorld(Coord3D *out);
};

bool Rva006956D0Owner::getScreenCenterWorld(Coord3D *out)
{
	ICoord2D center;
	switch (m_mode)
	{
	case 1:
		if (g_bfmeStateDF)
		{
			if (TheDisplay)
			{
				center.x = (int)(TheDisplay->getWidth() / 2);
				center.y = (int)(TheDisplay->getHeight() / 2);
				g_bfmeStateDF->mapScreenToWorld(&center, out);
				return true;
			}
		}
		break;
	case 0:
		if (TheTacticalViewFadeShim)
		{
			center.x = TheTacticalViewFadeShim->getWidth() / 2;
			center.y = TheTacticalViewFadeShim->getHeight() / 2;
			return TheTacticalViewFadeShim->screenToTerrain(&center, out, false);
		}
		break;
	}
	out->x = 0.0f;
	out->y = 0.0f;
	out->z = 0.0f;
	return false;
}
