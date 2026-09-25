// ?d_006c0fa0@@YAXXZ
// partial score=0.4 date=2026-09-25
// ?method@Rva006C0FA0W3DRadar@@QAEXHHHHH@Z
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef float Real;
typedef int Int;

struct ICoord2D
{
	Int x;
	Int y;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct Rva006C0FA0Locals
{
	unsigned int leading[2];
	ICoord2D origin;
	Coord3D world;
};

class Coord2D
{
public:
	Coord2D();
	~Coord2D();

	Real x;
	Real y;
};

class View
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
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void getOrigin(Int *, Int *) = 0;
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
	virtual void slot63() = 0;
	virtual void slot64() = 0;
	virtual void slot65() = 0;
	virtual void slot66() = 0;
	virtual void slot67() = 0;
	virtual void slot68() = 0;
	virtual void slot69() = 0;
	virtual void slot70() = 0;
	virtual void slot71() = 0;
	virtual void slot72() = 0;
	virtual void slot73() = 0;
	virtual void slot74() = 0;
	virtual void slot75() = 0;
	virtual void slot76() = 0;
	virtual void slot77() = 0;
	virtual void slot78() = 0;
	virtual void slot79() = 0;
	virtual void slot80() = 0;
	virtual void slot81() = 0;
	virtual void slot82() = 0;
	virtual void slot83() = 0;
	virtual void slot84() = 0;
	virtual void slot85() = 0;
	virtual void slot86() = 0;
	virtual void slot87() = 0;
	virtual void slot88() = 0;
	virtual void slot89() = 0;
	virtual void screenToWorldAtZ(const ICoord2D *, Coord3D *, Real) = 0;
};

struct RvaMapExtent
{
	Coord3D lo;
	Coord3D hi;
};

struct Rva00592E10Pair
{
	unsigned int first;
	unsigned int second;
};

class Rva00592E10Owner
{
public:
	void copy(const Rva00592E10Pair *source);
};

class Rva006C0FA0W3DRadar
{
private:
	unsigned char m_pad0000[0x18];
	Real m_terrainAverageZ;
	unsigned char m_pad001c[0x143c - 0x1c];
	RvaMapExtent m_mapExtent;
	unsigned char m_pad1454[0x14e8 - 0x1454];
	Coord2D m_viewBox[4];

public:
	void method(Int, Int, Int, Int, Int);
};

#define TheTacticalView (*(View **)0x012f1600)
#define RvaRadarCellScale (*(const Real *)0x010888f4)
#define RvaRadarCellOrigin (*(const Real *)0x0111d780)
#define Glo012F4B98 (*(Rva00592E10Owner **)0x012f4b98)

void Rva006C0FA0W3DRadar::method(Int pixelX, Int pixelY, Int width, Int height, Int unused)
{
	Rva006C0FA0Locals locals;
	Real terrainZ;

	TheTacticalView->getOrigin(&locals.origin.x, &locals.origin.y);
	terrainZ = m_terrainAverageZ;
	TheTacticalView->screenToWorldAtZ(&locals.origin, &locals.world, terrainZ);

	Real x;
	Real y;
	x = locals.world.x /
		((m_mapExtent.hi.x - m_mapExtent.lo.x) * RvaRadarCellScale);
	y = locals.world.y /
		((m_mapExtent.hi.y - m_mapExtent.lo.y) * RvaRadarCellScale);
	locals.world.x = pixelX + (width * x) * RvaRadarCellScale;
	locals.world.y = pixelY + ((RvaRadarCellOrigin - y) * height) * RvaRadarCellScale;

	{
	Coord2D points[4];

	points[0].x = locals.world.x;
	points[0].y = locals.world.y;
	x += m_viewBox[1].x;
	y += m_viewBox[1].y;
	points[1].x = pixelX + (width * x) * RvaRadarCellScale;
	points[1].y = pixelY + ((RvaRadarCellOrigin - y) * height) * RvaRadarCellScale;
	x += m_viewBox[2].x;
	y += m_viewBox[2].y;
	points[2].x = pixelX + (width * x) * RvaRadarCellScale;
	points[2].y = pixelY + ((RvaRadarCellOrigin - y) * height) * RvaRadarCellScale;
	x += m_viewBox[3].x;
	y += m_viewBox[3].y;
	points[3].x = pixelX + (width * x) * RvaRadarCellScale;
	points[3].y = pixelY + ((RvaRadarCellOrigin - y) * height) * RvaRadarCellScale;

	if (Glo012F4B98)
		Glo012F4B98->copy((const Rva00592E10Pair *)points);
	}
}
