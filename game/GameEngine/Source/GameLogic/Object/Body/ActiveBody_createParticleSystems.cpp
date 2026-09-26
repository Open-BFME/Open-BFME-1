// ActiveBody::createParticleSystems, retail 0x0020ED10 (virtual slot +0x40, ILT 0x0004237A).
// ZH twin: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Body/ActiveBody.cpp
// cl: /DNDEBUG /MD /EHsc

#include <string.h>

typedef bool Bool;
typedef int Int;
typedef unsigned int size_t;

enum ParticleSystemID
{
	INVALID_PARTICLE_SYSTEM_ID = 0
};

// Struct tag as the retail callees mangle it; the out-of-line empty ctor/dtor
// (coord3d.cpp) make the local array use the EH vector iterators.
struct Coord3D
{
	float x, y, z;

	Coord3D();
	~Coord3D();
};

class Matrix3D;

class AsciiString
{
public:
	void *m_data;

	const char *str() const
	{
		return m_data ? reinterpret_cast<const char *>(m_data) + 8 : "";
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
		return m_systemID;
	}

	unsigned char m_pad[0x98];
	BfmeParticleSystemHandle *m_firstHandle;
	BfmeParticleSystemHandle *m_lastHandle;
	unsigned char m_pad0A0[0xAC - 0xA0];
	ParticleSystemID m_systemID;
};

extern ParticleSystem *Make00001B18();

class BfmeParticleSystemHandle
{
public:
	~BfmeParticleSystemHandle() throw()
	{
		if (m_system)
		{
			if (m_previous)
				m_previous->m_next = m_next;
			else
				m_system->m_firstHandle = m_next;
			if (m_next)
				m_next->m_previous = m_previous;
			else
				m_system->m_lastHandle = m_previous;
			m_previous = 0;
			m_next = 0;
		}
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
	virtual void createParticleSystems(const AsciiString &boneBaseName,
		const ParticleSystemTemplate *systemTemplate, Int maxSystems);

private:
	unsigned char m_bodyFields[0xa4];
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

// Places up to maxSystems systems on distinct random bones, probing forward from
// a random start index until a free bone is found.
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

	for (Int i = 0; i < maxSystems; ++i)
	{
#line 1391 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Body\\ActiveBody.cpp"
		Int boneIndex = GameClientRandomValue(0, numBones - 1);

		for (Int j = 0; j < numBones; j++)
		{
			if (usedBoneIndices[boneIndex] != true)
			{
				const Coord3D *pos = &bonePositions[boneIndex];
				usedBoneIndices[boneIndex] = true;
				if (pos)
				{
					BfmeParticleSystemHandle particleSystem =
						TheParticleSystemManager->createParticleSystem(systemTemplate, true);
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
				break;
			}
			boneIndex = (boneIndex + 1) % numBones;
		}
	}
}
