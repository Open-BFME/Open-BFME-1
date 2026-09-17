// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME 1.03 RVA 0x006C0C00, 574 bytes.
//
// The generated row's call-free label is not an identity.  The body is the
// W3DRadar::reconstructViewBox operation: the adjacent W3DRadar code uses the
// same terrain-average-Z field, map extent, view-box cache, and camera calls.
// The retail BFME layout is wider than the published Zero Hour W3DRadar
// declaration, so this TU gives the recovered body its actual BFME offsets.

typedef float Real;

// These are the WWMath classes used by retail.  Their empty constructor and
// destructor are existing canonical functions; declaring them here makes the
// compiler emit the same EH vector construction/cleanup calls as retail.
class Coord3D
{
public:
	Coord3D();
	~Coord3D();
	Real x, y, z;
};

class Coord2D
{
public:
	Coord2D();
	~Coord2D();
	Real x, y;
};

struct RvaPoint3D
{
	Real x, y, z;
};

class Rva006C0C00TacticalView
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void getScreenCornerWorldPointsAtZ(Coord3D *, Coord3D *, Coord3D *, Coord3D *, Real) = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual Real getAngle() = 0;
	virtual void slot64() = 0;
	virtual void slot65() = 0;
	virtual void slot66() = 0;
	virtual void slot67() = 0;
	virtual void slot68() = 0;
	virtual void getPosition(RvaPoint3D *) = 0;
	virtual void slot70() = 0;
	virtual void slot71() = 0;
	virtual Real getZoom() = 0;
};

struct RvaMapExtent
{
	RvaPoint3D lo, hi;

	Real width() const { return hi.x - lo.x; }
	Real height() const { return hi.y - lo.y; }
};

struct RvaRadarPoint
{
	Real x, y;
};

class Rva006C0C00W3DRadar
{
private:
	unsigned char m_pad0000[0x18];
	Real m_terrainAverageZ; // 0x0018
	unsigned char m_pad001c[0x143c - 0x001c];
	RvaMapExtent m_mapExtent; // 0x143c
	unsigned char m_pad1454[0x14dc - 0x1454];
	unsigned char m_reconstructViewBox; // 0x14dc
	Real m_viewAngle; // 0x14e0
	Real m_viewZoom; // 0x14e4
	Coord2D m_viewBox[4]; // 0x14e8

public:
	Real getTerrainAverageZ() const { return m_terrainAverageZ; }
	void reconstructViewBox();
};

#define TheTacticalView (*(Rva006C0C00TacticalView **)0x012f1600)
#define RvaRadarCellScale (*(const Real *)0x010888f4)

void Rva006C0C00W3DRadar::reconstructViewBox()
{
	Coord3D world[4];
	Coord2D radar[4];
	int i;

	TheTacticalView->getScreenCornerWorldPointsAtZ(
		&world[0], &world[1], &world[2], &world[3], getTerrainAverageZ());

	for (i = 0; i < 4; ++i)
	{
		radar[i].x = world[i].x / (m_mapExtent.width() * RvaRadarCellScale);
		Real radarHeight = m_mapExtent.height();

		if (i == 0)
		{
			m_viewBox[i].x = 0.0f;
			m_viewBox[i].y = 0.0f;
		}

		radar[i].y = world[i].y / (radarHeight * RvaRadarCellScale);

		if (i != 0)
		{
			m_viewBox[i].x = radar[i].x - radar[i - 1].x;
			m_viewBox[i].y = radar[i].y - radar[i - 1].y;
		}
	}

	m_viewAngle = TheTacticalView->getAngle();
	RvaPoint3D pos;
	TheTacticalView->getPosition(&pos);
	m_viewZoom = TheTacticalView->getZoom();
	m_reconstructViewBox = 0;
}
