// cl: /DNDEBUG /MD /EHsc
#include <math.h>

typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

inline Real bfmeSqr(Real value)
{
	return value * value;
}

class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition(void) const;
	Real getMaxHeightBelowPosition(void) const;
	void calcPitches(const Coord3D &thisPos, const GeometryInfo &that,
		const Coord3D &thatPos, Real &minPitch, Real &maxPitch) const;

private:
	void getCenterPosition(const Coord3D &position, Coord3D &center) const
	{
		center = m_centerOffset;
		center.x += position.x;
		center.y += position.y;
		center.z += position.z;
	}

	unsigned char m_unmodelled000[0x18];
	Coord3D m_centerOffset;
};

// ?calcPitches@GeometryInfo@@QBEXABUCoord3D@@ABV1@0AAM2@Z
void GeometryInfo::calcPitches(const Coord3D &thisPos, const GeometryInfo &that,
	const Coord3D &thatPos, Real &minPitch, Real &maxPitch) const
{
	Coord3D thisCenter;
	getCenterPosition(thisPos, thisCenter);

	Real dxy = sqrt(bfmeSqr(thatPos.x - thisCenter.x) +
		bfmeSqr(thatPos.y - thisCenter.y));

	Real dz = (thatPos.z + that.getMaxHeightAbovePosition()) - thisCenter.z;
	maxPitch = atan2(dz, dxy);

	Real below = that.getMaxHeightBelowPosition();
	dz = (thatPos.z - below) - thisCenter.z;
	minPitch = atan2(dz, dxy);
}
