// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas
// readable body of ??0Locomotor@@IAE@PBVLocomotorTemplate@@@Z: game/GameEngine/Source/GameLogic/Object/Locomotor.cpp
//
// BFME Locomotor constructor at RVA 0x001B60E0 (539 bytes, ret 4 at +0x218).
// Identity: LocomotorStore::newLocomotor (LocomotorStore_newLocomotor.cpp)
// allocates the object and calls this body; it installs Locomotor's vtable
// 0x0109DEF0 and its unwind funclet runs ~Snapshot, so BFME's Locomotor has a
// single Snapshot base (one vptr) and keeps the OVERRIDE template at +0x04.
// Zero Hour's body (Locomotor.cpp), with BFME's extra zeroed state, the
// identity Matrix3D at +0x64 and both setFlag calls after the wander offset.
// The layout is the one the matched copy assignment (LocomotorCopyAssignment.cpp)
// and LocomotorTemplate constructor (LocomotorTemplateConstructor.cpp) witness;
// the Zero Hour GameLogic/Locomotor.h layout (two vptrs) cannot hold this body.
// The random draws report retail's own __FILE__/__LINE__ (631, 632, 644).

#include "Lib/BaseType.h"
#include "WWMath/matrix3d.h"

#define BIGNUM 99999.0f

Real GetGameLogicRandomValueReal(Real lo, Real hi, char *file, Int line);
Int GetGameLogicRandomValue(Int lo, Int hi, char *file, Int line);

class Xfer;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot();
protected:
	virtual void crc(Xfer *xfer) = 0;
	virtual void xfer(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}
protected:
	virtual ~Overridable();
private:
	Overridable *m_nextOverride;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Override.h
template <class T> class OVERRIDE
{
public:
	OVERRIDE(const T *overridable = NULL) : m_overridable(overridable) {}
	OVERRIDE &operator=(const T *overridable) { m_overridable = overridable; return *this; }
	const T *operator->() const
	{
		if (!m_overridable)
			return NULL;
		return (const T *)m_overridable->getFinalOverride();
	}
private:
	const T *m_overridable;
};

class LocomotorTemplate : public Overridable
{
public:
	char m_unmodelled008[0x54 - 0x08];
	Real m_preferredHeight;			// +0x54
	Real m_field58;					// +0x58
	Real m_preferredHeightDamping;	// +0x5c
	char m_unmodelled060[0xc0 - 0x60];
	Real m_closeEnoughDist;			// +0xc0
	Bool m_isCloseEnoughDist3D;		// +0xc4
	char m_unmodelled0c5[0xf0 - 0xc5];
	Real m_wanderLengthFactor;		// +0xf0
};

enum LocoFlag
{
	IS_CLOSE_ENOUGH_DIST_3D = 10,
	OFFSET_INCREASING = 11
};

class Locomotor : public Snapshot
{
protected:
	Locomotor(const LocomotorTemplate *tmpl);
	virtual ~Locomotor();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

	void setFlag(LocoFlag f, Bool b) { if (b) m_flags |= (1 << f); else m_flags &= ~(1 << f); }

	OVERRIDE<LocomotorTemplate> m_template;	// +0x04
	Coord3D m_maintainPos;					// +0x08
	Coord3D m_position;						// +0x14
	Real m_brakingFactor;					// +0x20
	Real m_maxLift;							// +0x24
	Real m_maxSpeed;						// +0x28
	Real m_maxAccel;						// +0x2c
	Real m_maxBraking;						// +0x30
	Real m_maxTurnRate;						// +0x34
	Real m_closeEnoughDist;					// +0x38
	Int m_field3c;							// +0x3c
	UnsignedInt m_flags;					// +0x40
	Real m_preferredHeight;					// +0x44
	Real m_field48;							// +0x48
	Real m_preferredHeightDamping;			// +0x4c
	Real m_angleOffset;						// +0x50
	Real m_offsetIncrement;					// +0x54
	Int m_field58;							// +0x58
	Int m_field5c;							// +0x5c
	Int m_field60;							// +0x60
	Matrix3D m_transform;					// +0x64
	Bool m_field94;							// +0x94
	Bool m_field95;							// +0x95
	Bool m_field96;							// +0x96
	Int m_field98;							// +0x98
	Int m_field9c;							// +0x9c
	Int m_fielda0;							// +0xa0
	Int m_fielda4;							// +0xa4
};

// ??0Locomotor@@IAE@PBVLocomotorTemplate@@@Z
Locomotor::Locomotor(const LocomotorTemplate *tmpl) : m_transform(true), m_field96(false)
{
	m_template = tmpl;
	m_maintainPos.zero();
	m_position.zero();
	m_brakingFactor = 1.0f;
	m_maxLift = BIGNUM;
	m_maxSpeed = BIGNUM;
	m_maxAccel = BIGNUM;
	m_maxBraking = BIGNUM;
	m_maxTurnRate = BIGNUM;
	m_closeEnoughDist = m_template->m_closeEnoughDist;
	m_field3c = 0;
	m_flags = 0;
	m_preferredHeight = m_template->m_preferredHeight;
	m_field48 = m_template->m_field58;
	m_preferredHeightDamping = m_template->m_preferredHeightDamping;

#line 631 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Locomotor.cpp"
	m_angleOffset = GetGameLogicRandomValueReal(-PI/6, PI/6, __FILE__, __LINE__);
	m_offsetIncrement = (PI/40) * (GetGameLogicRandomValueReal(0.8f, 1.2f, __FILE__, __LINE__)/m_template->m_wanderLengthFactor);
	m_field58 = 0;
	m_field5c = 0;
	m_field60 = 0;
	m_field94 = false;
	m_field95 = false;
	m_field98 = 0;
	m_field9c = 0;
	m_fielda0 = 0;
	m_fielda4 = 0;

	setFlag(IS_CLOSE_ENOUGH_DIST_3D, m_template->m_isCloseEnoughDist3D);
	setFlag(OFFSET_INCREASING, GetGameLogicRandomValue(0, 1, __FILE__, __LINE__));
}
