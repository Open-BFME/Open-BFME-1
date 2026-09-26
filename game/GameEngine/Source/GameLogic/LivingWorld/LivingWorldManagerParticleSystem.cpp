// cl: /O2 /Ob2 /GR- /MD /DNDEBUG /DWIN32 /D_WINDOWS /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// The LivingWorldManager particle record creates one particle system at the
// manager position and retains its handle and system id in a 16-byte vector.

#include <vector>

typedef bool Bool;

enum { FALSE = 0, TRUE = 1 };

struct Coord3D
{
	float x;
	float y;
	float z;
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

	char *m_data;

private:
	void releaseBuffer();
};

class ParticleSystemTemplate;

#include "ascii_string.h"

class ParticleSystem
{
public:
	void setPosition(const Coord3D *position);
	void setField94(void *value);
	void start();
	void stop();
	void destroy();

	unsigned char m_pad[0xAC];
	int m_systemId;
};

ParticleSystem *Make00001B18(void);

class U1CachedHolder;

class W3DAnimationInfo;

namespace _STL
{
class W3DAnimationInfoCopyShim
{
public:
	static W3DAnimationInfo *copy(W3DAnimationInfo *first,
		W3DAnimationInfo *last, W3DAnimationInfo *result,
		const random_access_iterator_tag &, int *n);
};
}

class W3DAnimationInfo
{
public:
	ParticleSystem *m_system;
	W3DAnimationInfo *m_previous;
	W3DAnimationInfo *m_next;
	int m_systemId;

	~W3DAnimationInfo() throw();
};

class U1Sub
{
public:
	U1Sub &apply(U1CachedHolder *that) throw();

	ParticleSystem *m_system;
	U1Sub *m_previous;
	U1Sub *m_next;
};

class BfmeParticleSystemHandle : public U1Sub
{
public:
	BfmeParticleSystemHandle()
	{
		m_system = 0;
		m_previous = 0;
		m_next = 0;
	}

	BfmeParticleSystemHandle &operator=(const BfmeParticleSystemHandle &that)
		throw()
	{
		apply((U1CachedHolder *)&that);
		return *this;
	}

	operator Bool() const
	{
		return m_system != 0;
	}

	ParticleSystem *operator->() const
	{
		return m_system ? m_system : Make00001B18();
	}

	~BfmeParticleSystemHandle() throw();
};

class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findTemplate(const AsciiString &name) const;
	BfmeParticleSystemHandle createParticleSystem(
		const ParticleSystemTemplate *sysTemplate, Bool createSlaves) throw();
};

extern ParticleSystemManager *TheParticleSystemManager;

struct Gen_t_00617d60_p16cd
{
	BfmeParticleSystemHandle m_handle;
	int m_systemId;
};

typedef _STL::vector<Gen_t_00617d60_p16cd> Rva00617D60Vector;

struct Rva00617D60RawVector
{
	Gen_t_00617d60_p16cd *m_start;
	Gen_t_00617d60_p16cd *m_finish;
	Gen_t_00617d60_p16cd *m_endOfStorage;
};

class Gen_00609320
{
public:
	unsigned char m_pad[8];
	volatile unsigned char m_enabled;
};

extern Gen_00609320 *g_bfmeStateDF;

class BfmeLivingWorldManager
{
public:
	void rva00617c60();
	void rva00617e30();
	void j_0003b1e2();
	void rva00610090();

private:
	unsigned char m_pad00[0x20];
	Coord3D m_position;
	BFMERetailAsciiString m_particleSystemName;
	unsigned char m_pad30[0x240];
	Rva00617D60Vector m_particleSystems;
};

void BfmeLivingWorldManager::rva00617c60()
{
	for (unsigned int i = 0; i < m_particleSystems.size(); ++i)
	{
		if (m_particleSystems[i].m_handle)
		{
			m_particleSystems[i].m_handle->stop();
			m_particleSystems[i].m_handle->destroy();
		}
	}
	Rva00617D60RawVector *particleSystems =
		(Rva00617D60RawVector *)&m_particleSystems;
	Gen_t_00617d60_p16cd *start = particleSystems->m_start;
	Gen_t_00617d60_p16cd *finish = particleSystems->m_finish;
	_STL::random_access_iterator_tag tag;
	W3DAnimationInfo *destination = _STL::W3DAnimationInfoCopyShim::copy(
		(W3DAnimationInfo *)finish, (W3DAnimationInfo *)finish,
		(W3DAnimationInfo *)start, tag, (int *)0);
	Gen_t_00617d60_p16cd *oldFinish = particleSystems->m_finish;
	for (W3DAnimationInfo *current = destination;
		current != (W3DAnimationInfo *)oldFinish; ++current)
	{
		current->~W3DAnimationInfo();
	}
	particleSystems->m_finish = (Gen_t_00617d60_p16cd *)destination;
	rva00610090();
}

void BfmeLivingWorldManager::rva00617e30()
{
	register unsigned char enabled = g_bfmeStateDF->m_enabled;
	if (enabled != FALSE)
	{
		const ParticleSystemTemplate *sysTemplate;
		{
			const char *name = m_particleSystemName.m_data
				? m_particleSystemName.m_data + 8
				: "";
			BFMERetailAsciiString particleSystemName(name);
			sysTemplate = TheParticleSystemManager->findTemplate(
				*(const AsciiString *)&particleSystemName);
		}
		if (sysTemplate)
		{
			Gen_t_00617d60_p16cd particleSystem;
			particleSystem.m_handle = TheParticleSystemManager->createParticleSystem(
				sysTemplate, TRUE);
			if (particleSystem.m_handle)
			{
				particleSystem.m_systemId = particleSystem.m_handle->m_systemId;
				particleSystem.m_handle->setPosition(&m_position);
				particleSystem.m_handle->setField94((void *)1);
				particleSystem.m_handle->start();
			}
			m_particleSystems.push_back(particleSystem);
		}
		j_0003b1e2();
	}
}
