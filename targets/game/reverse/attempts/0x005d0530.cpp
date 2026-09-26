// ?createParticle@BfmeParticleEmissionHelper@@QAEPAVParticle@@HH@Z
// partial score=0.65 date=2026-09-20
// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// The retail helper at 0x005D0530 is reached by the actual ParticleSystem
//::DoXfer call at 0x005D0D70 through ILT 0x00019F6A.  The target allocates a
// 0x68-byte object and installs the FXParticleInfo vtable at 0x0110FE78.
// This file keeps that small BFME view local; the retail ParticleInfo header
// describes a larger ZH keyframe object and is not its layout.

#include <new>

typedef float Real;

class Particle;

class GameClientRandomVariable
{
public:
	Real getValue() const;
};

// These are the three existing ILT labels used by the retail body.  Their
// concrete implementation names are not recovered, so the call sites use
// address-derived aliases and explicit ABI views below.
extern void j_0001cfc6();
extern void j_0000c2bb();
extern void j_00043e91();

extern Real g_bfmeDefaultBU;
extern const Real BfmeZeroRange;

#define Rva005D0530ClampLimit (*(const Real *)0x0107FAA8)

struct Rva005D0530Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Rva005C36C0Owner
{
public:
	Rva005D0530Coord3D *sample(
		Rva005D0530Coord3D *, int, int);
};

class Rva005C3630Owner
{
public:
	Rva005D0530Coord3D *sample(
		Rva005D0530Coord3D *, Rva005D0530Coord3D *);
};

struct BfmeOutAC;

class BfmeNextAC
{
public:
	void bfmeSendAC(BfmeOutAC *);
};

class Rva005D0530LinkTail
{
public:
	virtual unsigned int getValue();
};

class Rva005D0530Link
{
public:
	unsigned char m_head[0x14];
	Rva005D0530LinkTail m_tail;
};

static Rva005D0530Coord3D *sampleEmissionPosition(
	void *system, Rva005D0530Coord3D *out, int count, int number)
{
	return reinterpret_cast<Rva005C36C0Owner *>(system)->sample(
		out, count, number);
}

static Rva005D0530Coord3D *sampleEmissionDirection(
	void *system, Rva005D0530Coord3D *out,
	Rva005D0530Coord3D *position)
{
	return reinterpret_cast<Rva005C3630Owner *>(system)->sample(out, position);
}

static __forceinline void copyCoord3D(
	Rva005D0530Coord3D *source, Rva005D0530Coord3D *destination)
{
	struct Raw {
		unsigned int x;
		unsigned int y;
		unsigned int z;
	};
	*(Raw *)destination = *(const Raw *)source;
}

static void attachEmissionInfo(void *tail, Particle *info)
{
	reinterpret_cast<BfmeNextAC *>(tail)->bfmeSendAC(
		reinterpret_cast<BfmeOutAC *>(info));
}

class Rva005D0530ParticleInfo
{
public:
	__forceinline Rva005D0530ParticleInfo()
	{
		unsigned int zero = 0;
		*(unsigned int *)(m_bytes + 0x04) = zero;
		*(unsigned int *)(m_bytes + 0x08) = zero;
		*(unsigned int *)(m_bytes + 0x0c) = zero;
		*(unsigned int *)(m_bytes + 0x28) = zero;
		*(unsigned int *)(m_bytes + 0x2c) = zero;
		*(unsigned int *)(m_bytes + 0x30) = zero;
		*(unsigned int *)(m_bytes + 0x1c) = zero;
		*(unsigned int *)(m_bytes + 0x20) = zero;
		*(unsigned int *)(m_bytes + 0x24) = zero;
		*(unsigned int *)(m_bytes + 0x10) = zero;
		*(unsigned int *)(m_bytes + 0x14) = zero;
		*(unsigned int *)(m_bytes + 0x18) = zero;
		*(unsigned int *)(m_bytes + 0x34) = zero;
		*(unsigned char *)(m_bytes + 0x38) = 0;
		*(unsigned int *)m_bytes = 0x0110FE78;
		*(unsigned int *)(m_bytes + 0x3c) = zero;
		*(unsigned int *)(m_bytes + 0x40) = zero;
		*(unsigned int *)(m_bytes + 0x44) = zero;
		*(unsigned int *)(m_bytes + 0x48) = zero;
		*(unsigned int *)(m_bytes + 0x54) = zero;
		*(unsigned int *)(m_bytes + 0x58) = zero;
		*(unsigned int *)(m_bytes + 0x5c) = zero;
		*(unsigned int *)(m_bytes + 0x60) = zero;
	}

	unsigned char m_bytes[0x68];
};

class BfmeParticleEmissionHelper
{
public:
	Particle *createParticle(int particleCount, int particleNumber);
};

// ?createParticle@BfmeParticleEmissionHelper@@QAEPAVParticle@@HH@Z
Particle *BfmeParticleEmissionHelper::createParticle(
	int particleCount, int particleNumber)
{
	Rva005D0530ParticleInfo *particleInfo = new Rva005D0530ParticleInfo;
	unsigned char *info = (unsigned char *)particleInfo;
	unsigned int zero = 0;

	if ((unsigned int)particleNumber != zero)
	{
		Rva005D0530Coord3D scratch;
		Rva005D0530Coord3D *positionResult = sampleEmissionPosition(
			this, &scratch, particleCount, particleNumber);
		Rva005D0530Coord3D *storedPosition =
			(Rva005D0530Coord3D *)(info + 0x1c);
		*storedPosition = *positionResult;
		Rva005D0530Coord3D *directionResult = sampleEmissionDirection(
			this, &scratch, storedPosition);
		Rva005D0530Coord3D *storedDirection =
			(Rva005D0530Coord3D *)(info + 0x10);
		*storedDirection = *directionResult;
		Real *f0 = (Real *)((unsigned char *)this + 0xf0);
		Real *f1 = (Real *)((unsigned char *)this + 0x100);
		Real *f2 = (Real *)((unsigned char *)this + 0x110);

		if (*(unsigned char *)((unsigned char *)this + 0x1a5) ==
			(unsigned char)zero)
		{
			if (*(unsigned char *)((unsigned char *)this + 0x1a9) !=
				(unsigned char)zero)
			{
			Rva005D0530Coord3D *current =
				(Rva005D0530Coord3D *)((unsigned char *)this + 0x148);
			Rva005D0530Coord3D *previous =
				(Rva005D0530Coord3D *)((unsigned char *)this + 0x154);
			copyCoord3D(current, previous);
				*(unsigned char *)((unsigned char *)this + 0x1a9) = 0;
			}

			Real originalZ = *(Real *)(info + 0x18);
			Real originalY = *(Real *)(info + 0x14);
			Real ratio = (Real)particleCount / (Real)particleNumber;
			Real blend = g_bfmeDefaultBU - ratio;
			Rva005D0530Coord3D *current =
				(Rva005D0530Coord3D *)((unsigned char *)this + 0x148);
			Rva005D0530Coord3D *previous =
				(Rva005D0530Coord3D *)((unsigned char *)this + 0x154);
			Rva005D0530Coord3D delta;
			delta.x = (current->x - previous->x) * blend;
			delta.y = (current->y - previous->y) * blend;
			delta.z = (current->z - previous->z) * blend;

			Real x = *(Real *)(info + 0x1c);
			Real y = *(Real *)(info + 0x20);
			Real z = *(Real *)(info + 0x24);
			Real transformedX = z * f0[2] + y * f0[1] + x * f0[0] + f0[3];
			Real transformedY = z * f1[2] + y * f1[1] + x * f1[0] + f1[3];
			Real transformedZ = z * f2[2] + y * f2[1] + x * f2[0] + f2[3];

			*(Real *)(info + 0x1c) = transformedX - delta.x;
			*(Real *)(info + 0x20) = transformedY - delta.y;
			*(Real *)(info + 0x24) = transformedZ - delta.z;

			Real dx = *(Real *)(info + 0x10);
			Real dy = originalY;
			Real dz = originalZ;
		*(Real *)(info + 0x10) =
				dz * f0[2] + dy * f0[1] + dx * f0[0];
			*(Real *)(info + 0x14) =
				dz * f1[2] + dy * f1[1] + dx * f1[0];
			*(Real *)(info + 0x18) =
				dz * f2[2] + dy * f2[1] + dx * f2[0];
		}

		GameClientRandomVariable *lifetime =
			(GameClientRandomVariable *)((unsigned char *)this + 0x14);
		*(unsigned int *)(info + 0x34) = (unsigned int)lifetime->getValue();

		Rva005D0530Link *link = *(Rva005D0530Link **)(
			(unsigned char *)this + 0x1b0);
		if (link != 0)
		{
			Rva005D0530LinkTail *tail =
				(Rva005D0530LinkTail *)((unsigned char *)link + 0x14);
			*(unsigned int *)(info + 0x3c) = tail->getValue();
		}
		else
		{
			*(unsigned int *)(info + 0x3c) = zero;
		}
		attachEmissionInfo((unsigned char *)this + 0x1b4, (Particle *)info);

		GameClientRandomVariable *damping =
			(GameClientRandomVariable *)((unsigned char *)this + 0x34);
		Real dampingValue = damping->getValue();
		*(Real *)((unsigned char *)this + 0x184) += dampingValue;
		if (*(Real *)((unsigned char *)this + 0x184) != BfmeZeroRange)
		{
			Real *value = (Real *)((unsigned char *)this + 0x184);
			if (*value > Rva005D0530ClampLimit)
				*value = 48.0f;
		}

		Real *out = (Real *)(info + 0x28);
		out[0] = (f0[2] + f0[1] + f0[0]) * BfmeZeroRange + f0[3];
		out[1] = (f1[2] + f1[1] + f1[0]) * BfmeZeroRange + f1[3];
		out[2] = (f2[2] + f2[1] + f2[0]) * BfmeZeroRange + f2[3];
		*(unsigned char *)(info + 0x38) =
			*(unsigned char *)((unsigned char *)this + 0x82);
	}

	return (Particle *)info;
}
