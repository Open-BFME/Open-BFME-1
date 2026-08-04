// cl: /DNDEBUG /MD /EHsc
// Lift the ApplyRandomForceNugget::create __emit thunk to clean C++.
//
// BFME-only nugget, so there is no Zero Hour body to port; the shape comes from
// the already-matched callee. calcRandomForce is pinned as
// ?calcRandomForce@@YAXMMMMPAUCoord3D@@@Z -- four floats and a Coord3D out --
// which identifies this+0x04..0x10 as the four float parameters, and the push
// order gives their argument positions. The physics behavior sits at
// Object+0x208.
//
// Note the declared Object * return is never actually produced: retail has no
// value-returning path, so each exit just leaves whatever eax happens to hold
// (null when the object test failed, the object itself when the physics test
// did). The source therefore has no return statement, which is what reproduces
// those two epilogues.

// MSVC 7.1 raises C4716 for the missing return; retail genuinely has no
// value-returning path, so the diagnostic is the point rather than a defect.
#pragma warning(disable : 4716)

struct Coord3D
{
	float x;
	float y;
	float z;
};

class PhysicsBehavior
{
public:
	void applyMotiveForce(const Coord3D *force);		///< ILT thunk at 0x0002A284
};

class Object
{
public:
	PhysicsBehavior *getPhysics(void) const { return m_physics; }

private:
	unsigned char m_unreconstructed_00[0x208];
	PhysicsBehavior *m_physics;							///< retail this+0x208
};

void calcRandomForce(float minForce, float maxForce, float minAngle, float maxAngle,
					 Coord3D *force);					///< matched at 0x001D6510

class ApplyRandomForceNugget
{
public:
	virtual Object *create(const Object *, const Object *, unsigned int) const;

private:
	float m_minForce;									///< retail this+0x04
	float m_maxForce;									///< retail this+0x08
	float m_minSpinRate;								///< retail this+0x0C
	float m_maxSpinRate;								///< retail this+0x10
};

// ?create@ApplyRandomForceNugget@@UBEPAVObject@@PBV2@0I@Z
Object *ApplyRandomForceNugget::create(const Object *primary, const Object *, unsigned int) const
{
	if (primary)
	{
		PhysicsBehavior *physics = primary->getPhysics();
		if (physics)
		{
			Coord3D force;
			calcRandomForce(m_minForce, m_maxForce, m_minSpinRate, m_maxSpinRate, &force);
			physics->applyMotiveForce(&force);
		}
	}
}
