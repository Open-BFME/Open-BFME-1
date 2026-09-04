// ?calcFlightPath@BezierProjectileBehavior@@QAE_N_N@Z
// partial score=0.62 date=2026-09-04
// cl: /DNDEBUG /DWIN32 /MD /O2 /Ob2 /EHsc
// stlport
// BezierProjectileBehavior::calcFlightPath, retail 0x001EF5E0 size 902.
// Identity: ILT 0x00021BD9 -> this body, named by projectileFireAtObjectOrPosition.
// ZH twin is DumbProjectileBehavior::calcFlightPath; BFME adds dual INI curve
// sets (this+0x78), a TerrainLogic vslot+0x40 height query, and a range-scaled
// height (module+0x34). Always returns true. Local Coord3D[4] + BezierSegment
// drive the eh vector ctor/dtor iterators (element ??0/??1Coord3D).

#include <math.h>

typedef float Real;
typedef bool Bool;
typedef int Int;

extern const Real g_bfmeZeroCY;
extern const Real g_bfmeADL;

struct Coord3D
{
	Coord3D();
	~Coord3D();

	Real x;
	Real y;
	Real z;
};

struct FlightPathVec
{
	char m_pad[12];
};

class BezierSegment
{
public:
	BezierSegment(Coord3D cp[4]);

	Real getApproximateLength(Real withinTolerance) const;
	void getSegmentPoints(Int numSegments, FlightPathVec *outResult) const;

private:
	Coord3D m_controlPoints[4];
};

class TerrainLogic
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual Real getHighestAlongLine(const Coord3D *start, const Coord3D *end);
};

extern TerrainLogic *TheTerrainLogic;

class BezierProjectileBehaviorModuleData
{
public:
	char m_pad00[0x08];
	Real m_firstHeightA;
	Real m_secondHeightA;
	Real m_firstPercentA;
	Real m_secondPercentA;
	char m_pad18[0x24 - 0x18];
	Real m_firstHeightB;
	Real m_secondHeightB;
	Real m_firstPercentB;
	Real m_secondPercentB;
	Real m_heightRange;
	char m_pad38[0x88 - 0x38];
	unsigned char m_useSimpleZ;
	char m_pad89[0x8C - 0x89];
	Real m_firstPercentIndent;
	Real m_secondPercentIndent;
};

class BezierProjectileBehavior
{
public:
	Bool calcFlightPath(Bool recalcNumSegments);

	void *m_vtable;
	const BezierProjectileBehaviorModuleData *m_moduleData;
	char m_pad08[0x44 - 0x08];
	FlightPathVec m_flightPath;
	Coord3D m_flightPathStart;
	Coord3D m_flightPathEnd;
	Real m_flightPathSpeed;
	Int m_flightPathSegments;
	char m_pad70[0x78 - 0x70];
	Int m_altCurve;
	char m_pad7C[0x84 - 0x7C];
	Real m_heightScale;
};

struct CalcFlightLocals
{
	Real terrainZ;
	Real firstPct;
	Real secondPct;
	Real dist;
	Real thresh;
	Real firstHeight;
	Real secondHeight;
	Real distSq;
};

// ?calcFlightPath@BezierProjectileBehavior@@QAE_N_N@Z present-unmatched
Bool BezierProjectileBehavior::calcFlightPath(Bool recalcNumSegments)
{
	Int alt = m_altCurve;
	const BezierProjectileBehaviorModuleData *d = m_moduleData;
	CalcFlightLocals L;
	if (!alt)
		L.firstPct = d->m_firstPercentA;
	else
		L.firstPct = d->m_firstPercentB;
	alt = m_altCurve;
	if (!alt)
		L.secondPct = d->m_secondPercentA;
	else
		L.secondPct = d->m_secondPercentB;
	m_heightScale = 1.0f;
	Coord3D controlPoints[4];

	controlPoints[0] = m_flightPathStart;
	controlPoints[3] = m_flightPathEnd;
	Real dx = controlPoints[3].x - controlPoints[0].x;
	controlPoints[1].x = L.firstPct * dx + controlPoints[0].x;
	Real dy = controlPoints[3].y - controlPoints[0].y;
	controlPoints[1].y = L.firstPct * dy + controlPoints[0].y;
	controlPoints[2].x = L.secondPct * dx + controlPoints[0].x;
	controlPoints[2].y = L.secondPct * dy + controlPoints[0].y;

	if (d->m_useSimpleZ)
	{
		Real dz = controlPoints[3].z - controlPoints[0].z;
		controlPoints[1].z = dz * d->m_firstPercentIndent + controlPoints[0].z;
		controlPoints[2].z = dz * d->m_secondPercentIndent + controlPoints[0].z;
	}
	else
	{
		L.terrainZ = TheTerrainLogic->getHighestAlongLine(&controlPoints[0], &controlPoints[3]);
		Int altH = m_altCurve;
		if (!altH)
			L.firstHeight = d->m_firstHeightA;
		else
			L.firstHeight = d->m_firstHeightB;
		altH = m_altCurve;
		if (!altH)
			L.secondHeight = d->m_secondHeightA;
		else
			L.secondHeight = d->m_secondHeightB;

		if (d->m_heightRange > g_bfmeZeroCY)
		{
			Real range = d->m_heightRange;
			L.thresh = range * g_bfmeADL;
			Real distX = controlPoints[3].x - controlPoints[0].x;
			Real distY = controlPoints[3].y - controlPoints[0].y;
			Real distZ = controlPoints[3].z - controlPoints[0].z;
			L.distSq = distX * distX + distY * distY + distZ * distZ;
			L.dist = (Real)sqrt(L.distSq);
			if (L.dist < L.thresh)
				m_heightScale = 0.0f;
			else if (L.dist < d->m_heightRange)
				m_heightScale = (L.dist - L.thresh) / L.thresh;

			Real zDelta = controlPoints[3].z - controlPoints[0].z;
			controlPoints[1].z = L.firstPct * zDelta + controlPoints[0].z;
			Real z2 = L.secondPct * zDelta + controlPoints[0].z;
			if (controlPoints[1].z < L.terrainZ)
				controlPoints[1].z = L.terrainZ;
			controlPoints[1].z = L.firstHeight * m_heightScale + controlPoints[1].z;
			if (z2 < L.terrainZ)
				z2 = L.terrainZ;
			controlPoints[2].z = z2 + L.secondHeight * m_heightScale;
		}
		else
		{
			Real hi = (L.terrainZ > controlPoints[0].z) ? L.terrainZ : controlPoints[0].z;
			hi = (hi > controlPoints[3].z) ? hi : controlPoints[3].z;
			controlPoints[1].z = hi + L.firstHeight;
			controlPoints[2].z = hi + L.secondHeight;
		}
	}

	BezierSegment flightCurve(controlPoints);
	if (recalcNumSegments)
	{
		if (!m_altCurve)
			L.secondHeight = m_flightPathSpeed;
		else
			L.secondHeight = m_flightPathSpeed * g_bfmeADL;
		m_flightPathSegments = (Int)ceil((double)(flightCurve.getApproximateLength(1.0f) / L.secondHeight));
	}
	if (m_flightPathSegments < 2)
		m_flightPathSegments = 2;
	flightCurve.getSegmentPoints(m_flightPathSegments, &m_flightPath);
	return true;
}
