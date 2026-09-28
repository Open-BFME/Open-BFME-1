// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System
// readable body of ?generateParticleInfo@ParticleSystem@@: game/GameEngine/Source/GameClient/System/ParticleSys.cpp
//
// ParticleSystem::generateParticleInfo, retail 0x005D0530 (844 bytes, ret 8).
//
// Identity: the matched ParticleSystem::DoXfer (0x005D0D70) calls this body
// through ILT 0x00019F6A as (0, 1) on its own system, and the body is Zero
// Hour's generateParticleInfo statement for statement: the particleCount
// guard, computeParticlePosition then computeParticleVelocity(&info.m_pos),
// the m_isIdentity / m_isFirstPos inter-frame emission adjustment
// (1 - num/count) * (m_pos - m_lastPos), the transform of position and
// velocity, the lifetime draw, the accumulated size bonus clamped to
// MAX_SIZE_BONUS (50.0f), the emitter position m_transform * (0,0,0) and
// m_isParticleUpTowardsEmitter.
//
// BFME differences, read from the retail body: the info is a new 0x68-byte
// ParticleInfo (vtable 0x0110FE78, whose ctor is the out-of-line 0x005CEFC0
// inlined here; DoXfer releases it), position and velocity come back by value,
// the per-particle keyframe/size/angle draws moved elsewhere, and the module at
// +0x1B0 and the chain at +0x1B4 (0x005CF250) stamp their values into it.
// Member names follow the Zero Hour statements they occupy.
//
// Shape notes, each measured against the retail bytes: the size-bonus clamp
// is a reference-returning min, and the standard Matrix3D mulVector3 /
// Rotate_Vector produce retail's z-first x87 order on their own.
#include "matrix3d.h"

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

#define INT_TO_REAL(x) ((Real)(x))
#define MAX_SIZE_BONUS 50

template <typename NUM> inline const NUM &bfmeMin(const NUM &x, const NUM &y) { return ((x) < (y) ? (x) : (y)); }

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

#include "game_client_random_variable.h"

class ParticleInfoData
{
public:
	ParticleInfoData()
	{
		m_value04.x = 0;
		m_value04.y = 0;
		m_value04.z = 0;
		m_emitterPos.x = 0;
		m_emitterPos.y = 0;
		m_emitterPos.z = 0;
		m_pos.x = 0;
		m_pos.y = 0;
		m_pos.z = 0;
		m_vel.x = 0;
		m_vel.y = 0;
		m_vel.z = 0;
		m_lifetime = 0;
		m_particleUpTowardsEmitter = false;
	}

	Coord3D m_value04;
	Coord3D m_vel;
	Coord3D m_pos;
	Coord3D m_emitterPos;
	UnsignedInt m_lifetime;
	Bool m_particleUpTowardsEmitter;
};

class ParticleInfo : public ParticleInfoData
{
public:
	ParticleInfo()
	{
		m_value3c = 0;
		m_value40 = 0;
		m_value44 = 0;
		m_value48 = 0;
		m_value54 = 0;
		m_value58 = 0;
		m_value5c = 0;
		m_value60 = 0;
	}
	virtual ~ParticleInfo();

	UnsignedInt m_value3c;
	UnsignedInt m_value40;
	UnsignedInt m_value44;
	UnsignedInt m_value48;
	UnsignedInt m_value4c;
	UnsignedInt m_value50;
	UnsignedInt m_value54;
	UnsignedInt m_value58;
	UnsignedInt m_value5c;
	UnsignedInt m_value60;
	UnsignedInt m_value64;
};

class Rva005D0530ModuleValue
{
public:
	virtual UnsignedInt getValue();
};

class Rva005D0530Module
{
public:
	unsigned char m_head[0x14];
	Rva005D0530ModuleValue m_value;
};

struct BfmeOutAC;

// The +0x1B4 module chain; 0x005CF250 stamps its modules' values into the info.
class BfmeNextAC
{
public:
	void bfmeSendAC(BfmeOutAC *info);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ParticleSys.h
class ParticleSystem
{
protected:
	ParticleInfo *generateParticleInfo(Int particleNum, Int particleCount);
	Coord3D computeParticlePosition(Int particleNum, Int particleCount);	///< 0x005C36C0
	Coord3D computeParticleVelocity(const Coord3D *pos);				///< 0x005C3630

public:

	unsigned char m_head[0x14];
	GameClientRandomVariable m_lifetime;				///< +0x14
	unsigned char m_pad20[0x14];
	GameClientRandomVariable m_startSizeRate;			///< +0x34
	unsigned char m_pad40[0x42];
	Bool m_isParticleUpTowardsEmitter;					///< +0x82
	unsigned char m_pad83[0x6d];
	Matrix3D m_transform;								///< +0xF0
	unsigned char m_pad120[0x28];
	Coord3D m_pos;										///< +0x148
	Coord3D m_lastPos;									///< +0x154
	unsigned char m_pad160[0x24];
	Real m_accumulatedSizeBonus;						///< +0x184
	unsigned char m_pad188[0x1d];
	Bool m_isIdentity;									///< +0x1A5
	unsigned char m_pad1a6[3];
	Bool m_isFirstPos;									///< +0x1A9
	unsigned char m_pad1aa[6];
	Rva005D0530Module *m_module1b0;						///< +0x1B0
	BfmeNextAC m_modules1b4;							///< +0x1B4
};

// ?generateParticleInfo@ParticleSystem@@IAEPAVParticleInfo@@HH@Z
ParticleInfo *ParticleSystem::generateParticleInfo(Int particleNum, Int particleCount)
{
	ParticleInfo *info = new ParticleInfo;
	if (particleCount == 0)
		return info;

	// NOTE: position MUST be computed before velocity, in case OUTWARD velocity is
	// specified, which must know where the particle is in space.
	info->m_pos = computeParticlePosition(particleNum, particleCount);
	info->m_vel = computeParticleVelocity(&info->m_pos);

	// transform the position and velocity, if necessary
	if (m_isIdentity == false)
	{
		// transform particle position to world coordinates
		Vector3 p, pr;

		Coord3D emissionAdjustment;	// this is the adjustment for inter-frame emission
		if (m_isFirstPos) {
			m_lastPos = m_pos;
			m_isFirstPos = false;
		}

		emissionAdjustment.x = (1 - (INT_TO_REAL(particleNum) / particleCount)) * (m_pos.x - m_lastPos.x);
		emissionAdjustment.y = (1 - (INT_TO_REAL(particleNum) / particleCount)) * (m_pos.y - m_lastPos.y);
		emissionAdjustment.z = (1 - (INT_TO_REAL(particleNum) / particleCount)) * (m_pos.z - m_lastPos.z);

		p.X = info->m_pos.x;
		p.Y = info->m_pos.y;
		p.Z = info->m_pos.z;

		m_transform.mulVector3(p, pr);

		info->m_pos.x = pr.X - emissionAdjustment.x;
		info->m_pos.y = pr.Y - emissionAdjustment.y;
		info->m_pos.z = pr.Z - emissionAdjustment.z;

		// transform particle velocity to world coordinates
		Vector3 v, vr;

		v.X = info->m_vel.x;
		v.Y = info->m_vel.y;
		v.Z = info->m_vel.z;

		Matrix3D::Rotate_Vector(m_transform, v, &vr);

		info->m_vel.x = vr.X;
		info->m_vel.y = vr.Y;
		info->m_vel.z = vr.Z;
	}

	info->m_lifetime = (UnsignedInt)m_lifetime.getValue();

	if (m_module1b0)
		info->m_value3c = m_module1b0->m_value.getValue();
	else
		info->m_value3c = 0;
	m_modules1b4.bfmeSendAC((BfmeOutAC *)info);

	// Keeping a running tally makes each successive particle spawned start a bit bigger (or smaller).
	m_accumulatedSizeBonus += m_startSizeRate.getValue();
	if( m_accumulatedSizeBonus )
		m_accumulatedSizeBonus = bfmeMin( m_accumulatedSizeBonus, (float)MAX_SIZE_BONUS );

	Vector3 pos;
	m_transform.mulVector3(Vector3(0, 0, 0), pos);
	info->m_emitterPos.x = pos.X;
	info->m_emitterPos.y = pos.Y;
	info->m_emitterPos.z = pos.Z;
	info->m_particleUpTowardsEmitter = m_isParticleUpTowardsEmitter;

	return info;
}
