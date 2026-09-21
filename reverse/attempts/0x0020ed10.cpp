// ?createParticleSystems@ActiveBody@@IAEXABVAsciiString@@PBVParticleSystemTemplate@@H@Z
// partial score=0.57 date=2026-09-21
// ZH twin reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Body/ActiveBody.cpp:976-1077
// Real Coord3D (Code/Libraries/Source/WWVegas/WWMath/coord3d.h) has a non-trivial
// ctor/dtor, so the local bonePositions[16] array needs the compiler-generated
// eh-vector-constructor-iterator (??_L) -- that call was missing from the
// earlier hand-rolled Coord3D stand-in, which is why that attempt came up 64B
// short. Including the real header restores it. memset() zero-fill for
// usedBoneIndices beats the {false} aggregate initializer (244 vs 275
// non-reloc diffs) but neither reproduces retail's clean 4x dword zero-store;
// frame is still 0xEC vs retail 0xE8 -- /FAsc showed both ours and retail
// spill `this` to the stack (not the culprit); the extra slot is still open.
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath

#include <string.h>

typedef bool Bool;
typedef int Int;
typedef unsigned int size_t;

enum ParticleSystemID
{
	INVALID_PARTICLE_SYSTEM_ID = 0
};

#include "coord3d.h"

class Matrix3D;

class AsciiString
{
	public:
	void *m_data;

	const char *str() const
	{
		return m_data ? reinterpret_cast<const char *>(m_data) + 8 :
			reinterpret_cast<const char *>(0x0107388b);
	}
};

class Object
{
public:
	Int getMultiLogicalBonePosition(const char *boneNamePrefix, Int maxBones,
		Coord3D *positions, Matrix3D *transforms, Bool convertToWorld,
		Int extra = 0) const;
};

class ParticleSystemTemplate;

class BfmeParticleSystemHandle;

class ParticleSystem
{
public:
	void setPosition(const Coord3D *pos);
	void attachToObject(const Object *obj);

	ParticleSystemID getSystemID() const
	{
		return *reinterpret_cast<const ParticleSystemID *>(
			reinterpret_cast<const char *>(this) + 0xac);
	}
};

extern ParticleSystem *Make00001B18();

class BfmeParticleSystemHandle
{
public:
	~BfmeParticleSystemHandle() throw()
	{
		m_previous = 0;
		m_next = 0;
	}

	operator Bool() const
	{
		return m_system != 0;
	}

	ParticleSystem *operator->() const
	{
		if (!m_system)
			return Make00001B18();
		return m_system;
	}

	ParticleSystem *m_system;
	BfmeParticleSystemHandle *m_previous;
	BfmeParticleSystemHandle *m_next;
};

class ParticleSystemManager
{
public:
	BfmeParticleSystemHandle createParticleSystem(
		const ParticleSystemTemplate *sysTemplate, Bool createSlaves = true) throw();
};

extern ParticleSystemManager *TheParticleSystemManager;

class BodyParticleSystem
{
protected:
	virtual ~BodyParticleSystem();

private:
	virtual void *getObjectMemoryPool();

public:
	enum BodyParticleSystemMagicEnum
	{
		BodyParticleSystem_GLUE_NOT_IMPLEMENTED = 0
	};

	static void *operator new(size_t s, BodyParticleSystemMagicEnum,
		const char *)
	{
		extern void *operator new(size_t);
		return ::operator new(s);
	}

	ParticleSystemID m_particleSystemID;
	BodyParticleSystem *m_next;
};

class ActiveBody
{
protected:
	void createParticleSystems(const AsciiString &boneBaseName,
		const ParticleSystemTemplate *systemTemplate, Int maxSystems);

private:
	unsigned char m_bodyFields[0xa8];
	BodyParticleSystem *m_particleSystems;

public:
	Object *getObject() const
	{
		return *reinterpret_cast<Object * const *>(
			reinterpret_cast<const char *>(this) + 8);
	}
};

extern Int GetGameClientRandomValue(int lo, int hi, char *file, int line);
#define GameClientRandomValue(lo, hi) \
	GetGameClientRandomValue((lo), (hi), __FILE__, __LINE__)

#define newInstance(ARGCLASS) \
	new(ARGCLASS::ARGCLASS##_GLUE_NOT_IMPLEMENTED, __FILE__) ARGCLASS

void ActiveBody::createParticleSystems(const AsciiString &boneBaseName,
	const ParticleSystemTemplate *systemTemplate, Int maxSystems)
{
	Object *us = getObject();

	if (systemTemplate == 0)
		return;

	enum { MAX_BONES = 16 };
	Coord3D bonePositions[MAX_BONES];
	Int numBones = us->getMultiLogicalBonePosition(boneBaseName.str(),
		MAX_BONES, bonePositions, 0, false);

	if (numBones == 0)
		return;

	if (numBones < maxSystems)
		maxSystems = numBones;

	Bool usedBoneIndices[MAX_BONES];
	memset(usedBoneIndices, 0, sizeof(usedBoneIndices));

	const Coord3D *pos;
	for (Int i = 0; i < maxSystems; ++i)
	{
		// Keep the retail source location used by GameClientRandomValue.
#line 1391 "Code/GameEngine/Source/GameLogic/Object/Body/ActiveBody.cpp"
		Int boneIndex = GameClientRandomValue(0, maxSystems - i - 1);
#line 110

		Int count = 0;
		for (Int j = 0; j < numBones; j++)
		{
			if (usedBoneIndices[j] == true)
				continue;

			if (count == boneIndex)
			{
				pos = &bonePositions[j];
				usedBoneIndices[j] = true;
				break;
			}
			else
			{
				++count;
			}
		}

		BfmeParticleSystemHandle particleSystem =
			TheParticleSystemManager->createParticleSystem(systemTemplate);
		if (particleSystem)
		{
			particleSystem->setPosition(pos);
			particleSystem->attachToObject(us);

			BodyParticleSystem *newEntry = newInstance(BodyParticleSystem);
			newEntry->m_particleSystemID = particleSystem->getSystemID();
			newEntry->m_next = m_particleSystems;
			m_particleSystems = newEntry;
		}
	}
}
