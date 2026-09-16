// ?placeSystem@BfmeAnimationHolder@@QAEXUCoord3D@@@Z
// partial score=0.6 date=2026-09-16
// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x0060BAA0. The receiver reaching applyPayloadOverrides at ILT
// 0x00010069 is this body's own, which places it on BfmeAnimationHolder. The
// other two calls are the matched ParticleSystem::setPosition and the null
// system accessor.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class ParticleSystemZA;

class ParticleSystem
{
public:
	void setPosition(const Coord3D *position);
};

ParticleSystemZA *bfmeNullSystemZA(void);

class BfmeAnimationHolder
{
public:
	void placeSystem(Coord3D offset);
	void applyPayloadOverrides(Coord3D offset);

	unsigned char m_bfmePad000[0x14];
	ParticleSystem *m_bfmeSystem;
	unsigned char m_bfmePad018[0xA0 - 0x18];
	float m_bfmeOffsetX;
	float m_bfmeOffsetY;
	float m_bfmeOffsetZ;
};

// The payload helper is matched with three integer parameters in its own
// translation unit, so it is reached through its retail thunk to keep the
// twelve-byte argument block retail builds here.
extern void j_00010069();

typedef void (BfmeAnimationHolder::*BfmeApplyPayloadCall)(Coord3D offset);

union BfmeApplyPayloadCast
{
	void *asVoid;
	BfmeApplyPayloadCall asCall;
};

void BfmeAnimationHolder::placeSystem(Coord3D offset)
{
	BfmeApplyPayloadCast apply;
	apply.asVoid = (void *)j_00010069;
	(this->*apply.asCall)(offset);

	ParticleSystem *system = m_bfmeSystem;
	if (system == 0)
		return;

	Coord3D world;
	world.x = offset.x + m_bfmeOffsetX;
	world.y = offset.y + m_bfmeOffsetY;
	world.z = offset.z + m_bfmeOffsetZ;

	if (system == 0)
		system = (ParticleSystem *)bfmeNullSystemZA();

	system->setPosition(&world);
}
