// ?calcFlightPath@BezierProjectileBehavior@@QAE_N_N@Z
// cl: /DNDEBUG /DWIN32 /MD /O2 /Ob2 /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// BezierProjectileBehavior::calcFlightPath, retail 0x001EF5E0, 902 bytes; ILT 0x00021BD9 is called by projectileFireAtObjectOrPosition.
// Zero Hour twin DumbProjectileBehavior::calcFlightPath; BFME adds the alternate curve set (this+0x78) and range-scaled heights.

#define __PLACEMENT_VEC_NEW_INLINE
#include <math.h>
#include "vector3.h"
#include <vector>

typedef float Real;
typedef bool Bool;
typedef int Int;

extern const Real g_bfmeZeroCY;

struct Coord3D
{
	Coord3D();
	~Coord3D();

	Real x;
	Real y;
	Real z;
};

typedef std::vector<Coord3D> FlightPathVec;

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

// Reference-returning max; the retail selects operand addresses and returns the second operand on ties.
template <class T>
inline const T &refMax001EF5E0(const T &x, const T &y)
{
	return (x > y) ? x : y;
}

Bool BezierProjectileBehavior::calcFlightPath(Bool recalcNumSegments)
{
	const BezierProjectileBehaviorModuleData *d = m_moduleData;
	Real firstPct;
	Real secondPct;
	if (!m_altCurve)
		firstPct = d->m_firstPercentA;
	else
		firstPct = d->m_firstPercentB;
	if (!m_altCurve)
		secondPct = d->m_secondPercentA;
	else
		secondPct = d->m_secondPercentB;
	m_heightScale = 1.0f;

	Coord3D controlPoints[4];
	controlPoints[0] = m_flightPathStart;
	controlPoints[3] = m_flightPathEnd;
	controlPoints[1].x = firstPct * (controlPoints[3].x - controlPoints[0].x) + controlPoints[0].x;
	controlPoints[1].y = firstPct * (controlPoints[3].y - controlPoints[0].y) + controlPoints[0].y;
	controlPoints[2].x = (controlPoints[3].x - controlPoints[0].x) * secondPct + controlPoints[0].x;
	controlPoints[2].y = (controlPoints[3].y - controlPoints[0].y) * secondPct + controlPoints[0].y;

	if (d->m_useSimpleZ)
	{
		controlPoints[1].z = (controlPoints[3].z - controlPoints[0].z) * d->m_firstPercentIndent + controlPoints[0].z;
		controlPoints[2].z = (controlPoints[3].z - controlPoints[0].z) * d->m_secondPercentIndent + controlPoints[0].z;
	}
	else
	{
		Real highestInterveningTerrain = TheTerrainLogic->getHighestAlongLine(&controlPoints[0], &controlPoints[3]);
		Real firstHeight;
		Real secondHeight;
		if (!m_altCurve)
			firstHeight = d->m_firstHeightA;
		else
			firstHeight = d->m_firstHeightB;
		if (!m_altCurve)
			secondHeight = d->m_secondHeightA;
		else
			secondHeight = d->m_secondHeightB;

		if (d->m_heightRange > g_bfmeZeroCY)
		{
			Real thresh = d->m_heightRange * 0.5f;
			Vector3 targetVector;
			targetVector.X = controlPoints[3].x - controlPoints[0].x;
			targetVector.Y = controlPoints[3].y - controlPoints[0].y;
			targetVector.Z = controlPoints[3].z - controlPoints[0].z;
			Real targetDistance = targetVector.Length();
			if (targetDistance < thresh)
				m_heightScale = 0.0f;
			else if (targetDistance < d->m_heightRange)
				m_heightScale = (targetDistance - thresh) / thresh;

			controlPoints[1].z = firstPct * (controlPoints[3].z - controlPoints[0].z) + controlPoints[0].z;
			Real z2 = (controlPoints[3].z - controlPoints[0].z) * secondPct + controlPoints[0].z;
			if (controlPoints[1].z < highestInterveningTerrain)
				controlPoints[1].z = highestInterveningTerrain;
			controlPoints[1].z = firstHeight * m_heightScale + controlPoints[1].z;
			if (z2 < highestInterveningTerrain)
				z2 = highestInterveningTerrain;
			controlPoints[2].z = secondHeight * m_heightScale + z2;
		}
		else
		{
			highestInterveningTerrain = refMax001EF5E0(highestInterveningTerrain, controlPoints[0].z);
			highestInterveningTerrain = refMax001EF5E0(highestInterveningTerrain, controlPoints[3].z);
			controlPoints[1].z = highestInterveningTerrain + firstHeight;
			controlPoints[2].z = highestInterveningTerrain + secondHeight;
		}
	}

	BezierSegment flightCurve(controlPoints);
	if (recalcNumSegments)
	{
		Real speed;
		if (!m_altCurve)
			speed = m_flightPathSpeed;
		else
			speed = m_flightPathSpeed * 0.5f;
		Real flightDistance = flightCurve.getApproximateLength(1.0f);
		m_flightPathSegments = (Int)ceil(flightDistance / speed);
	}
	if (m_flightPathSegments < 2)
		m_flightPathSegments = 2;
	flightCurve.getSegmentPoints(m_flightPathSegments, &m_flightPath);
	return true;
}
