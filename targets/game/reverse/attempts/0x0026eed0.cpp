// ?blockedSpeed@Rva0026EED0AIUpdate@@QBEMPAVObject@@@Z
// partial score=0.72 date=2026-09-26
// cl: /DNDEBUG /MD /EHsc
// This is the AI collision-speed calculation analogous to the Zero Hour
// blocked-speed formula, with BFME's locomotor-height term replacing the
// upstream physics-velocity walk.
typedef float Real;
extern const Real BfmeZeroRange;
extern Real g_bfmeDefaultBU;
extern "C" double __cdecl sqrt(double value);
#pragma intrinsic(sqrt)

struct Coord3D { Real x, y, z; };
struct Rva0026EED0Direction2D { Real x, y; };
class Thing
{
public:
	const Coord3D *getUnitDirectionVector2D() const;
	char m_pad00[0x38];
	Coord3D m_position;
	char m_pad44[0x31c - 0x44];
	int m_formation;
};
class Object : public Thing
{
public:
	Real bfmeGetNonnegativePreferredLocomotorHeight() const;
};
class Rva0026EED0AIUpdate
{
public:
	Real blockedSpeed(Object *other) const;
	char m_pad00[8];
	Object *m_object;
	char m_pad0c[0x170 - 0x0c];
	Real m_curMaxBlockedSpeed;
};
Real Rva0026EED0AIUpdate::blockedSpeed(Object *other) const
{
	const Coord3D *direction = m_object->getUnitDirectionVector2D();
	Rva0026EED0Direction2D ourDir = { direction->x, direction->y };
	const Coord3D *otherDirection = other->getUnitDirectionVector2D();
	Rva0026EED0Direction2D otherDir = { otherDirection->x, otherDirection->y };
	Real dx = other->m_position.x - m_object->m_position.x;
	Real dy = other->m_position.y - m_object->m_position.y;
	Real length = (Real)sqrt(dx * dx + dy * dy);
	if (length != BfmeZeroRange)
	{
		Real reciprocal = g_bfmeDefaultBU / length;
		dx *= reciprocal;
		dy *= reciprocal;
	}
	Real speedFactor = dx * otherDir.x + dy * otherDir.y;
	if (speedFactor < BfmeZeroRange)
		return BfmeZeroRange;
	Real awaySpeed = other->bfmeGetNonnegativePreferredLocomotorHeight() * speedFactor;
	Real dot = dx * ourDir.x + dy * ourDir.y;
	if (dot <= BfmeZeroRange)
		return m_curMaxBlockedSpeed;
	Real maxSpeed = awaySpeed / dot;
	if (other->m_formation != 0 && m_object->m_formation == other->m_formation)
		maxSpeed *= 0.55f;
	if (maxSpeed > m_curMaxBlockedSpeed)
		return m_curMaxBlockedSpeed;
	return maxSpeed;
}
