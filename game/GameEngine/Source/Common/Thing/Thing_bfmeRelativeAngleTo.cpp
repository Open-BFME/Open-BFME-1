// cl: /DNDEBUG /MD /EHsc

#include <math.h>

typedef float Real;

extern Real ACos(Real);

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Thing
{
public:
	const Coord3D *getUnitDirectionVector2D() const;
	Real bfmeRelativeAngleTo(const Coord3D *point) const;

private:
	unsigned char m_pad000[0x38];
	Coord3D m_cachedPos;
};

#define BFME_ZERO_RANGE (*(const Real *)0x01075350)
#define BFME_DEFAULT_BU (*(const Real *)0x01075334)
#define BFME_MINUS_ONE (*(const double *)0x01095f18)
#define BFME_ONE (*(const double *)0x0107c640)

// ?bfmeRelativeAngleTo@Thing@@QBEMPBUCoord3D@@@Z
Real Thing::bfmeRelativeAngleTo(const Coord3D *point) const
{
	Coord3D delta;
	delta.x = point->x - m_cachedPos.x;
	delta.y = point->y - m_cachedPos.y;
	Real distance = (Real)sqrt(delta.x * delta.x + delta.y * delta.y);
	if (distance == BFME_ZERO_RANGE)
		return BFME_ZERO_RANGE;

	Real scale = BFME_DEFAULT_BU / distance;
	delta.x *= scale;
	delta.y *= scale;
	const Coord3D *direction = getUnitDirectionVector2D();
	Real cosine = delta.x * direction->x + delta.y * direction->y;
	if (cosine < BFME_MINUS_ONE)
		cosine = -1.0f;
	else if (cosine > BFME_ONE)
		cosine = 1.0f;

	Real angle = ACos(cosine);
	if (direction->x * delta.y - direction->y * delta.x < BFME_ZERO_RANGE)
		angle = -angle;
	return angle;
}
