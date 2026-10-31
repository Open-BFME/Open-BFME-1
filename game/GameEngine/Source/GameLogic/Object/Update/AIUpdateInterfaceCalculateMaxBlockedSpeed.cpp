// ?calculateMaxBlockedSpeed@AIUpdateInterface@@IBEMPAVObject@@@Z
// cl: /DNDEBUG /MD /EHsc
// AIUpdateInterface::calculateMaxBlockedSpeed, retail 0x0026EED0, 289 B (ret 4).
// ilt_oracle CONFIRMS ?calculateMaxBlockedSpeed@AIUpdateInterface@@IBEMPAVObject@@@Z.
// Zero Hour AIUpdate.cpp:1258 twin; BFME replaces the physics velocity with
// Object::bfmeGetNonnegativePreferredLocomotorHeight (ILT 0x47C8).
// Reading getObject() inside a member helper (not passing it in) gives retail's
// EAX; reading ourDir through volatile lvalues in the second dot makes retail
// load ourDir and multiply by vectorToOther. See attempt_support handoff.
typedef float Real;
typedef int Int;
extern "C" double __cdecl sqrt(double value);
#pragma intrinsic(sqrt)
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
// class-gate: allow Coord2D ZH's inline length()/normalize() (absent from the canonical header) are inlined into this body
struct Coord2D
{
	Real x, y;
	Real length() const { return (Real)sqrt(x * x + y * y); }
	void normalize()
	{
		Real len = length();
		if (len != 0.0f)
		{
			Real inv = 1.0f / len;
			x *= inv;
			y *= inv;
		}
	}
};
class Thing
{
public:
	const Coord3D *getUnitDirectionVector2D() const;
	const Coord3D *getPosition() const { return &m_cachedPos; }
	char m_pad00[0x38];
	Coord3D m_cachedPos;
	char m_pad44[0x31c - 0x44];
	Int m_formationID;
};
class Object : public Thing
{
public:
	Real bfmeGetNonnegativePreferredLocomotorHeight() const;
	Int getFormationID() const { return m_formationID; }
};
class AIUpdateInterface
{
protected:
	Real calculateMaxBlockedSpeed(Object *other) const;
	Object *getObject() const { return m_object; }
	__forceinline Real projectTowards(Coord2D &v, const Object *to, Real oy, Real ox) const
	{
		v.x = to->getPosition()->x - getObject()->getPosition()->x;
		v.y = to->getPosition()->y - getObject()->getPosition()->y;
		v.normalize();
		return v.x*ox + v.y*oy;
	}
	char m_pad00[8];
	Object *m_object;
	char m_pad0c[0x170 - 0x0c];
	Real m_curMaxBlockedSpeed;
};
Real AIUpdateInterface::calculateMaxBlockedSpeed(Object *other) const
{
	const Coord3D *dir = getObject()->getUnitDirectionVector2D();
	Coord3D ourDir; ourDir.x = dir->x; ourDir.y = dir->y;
	Coord2D vectorToOther;
	const Coord3D *odir = other->getUnitDirectionVector2D();
	Real dotProduct = projectTowards(vectorToOther, other, odir->y, odir->x);
	if (dotProduct<0) return 0; // They are running into us.

	Real speedFactor = dotProduct;
	Real awaySpeed = other->bfmeGetNonnegativePreferredLocomotorHeight() * speedFactor;

	// Now calculate the amount we are moving relative to towards them...
	dotProduct = *(const volatile Real *)&ourDir.x*vectorToOther.x + *(const volatile Real *)&ourDir.y*vectorToOther.y;
	if (dotProduct<=0) {
		return m_curMaxBlockedSpeed;
	}
	Real maxSpeed = awaySpeed / dotProduct;
	if (other->getFormationID()!=0 && getObject()->getFormationID()==other->getFormationID()) {
		maxSpeed *= 0.55f;
	}
	if (maxSpeed>m_curMaxBlockedSpeed) return m_curMaxBlockedSpeed;
	return maxSpeed;
}
