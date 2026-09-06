// cl: /O2 /Ob2 /GR- /MD /DNDEBUG /DWIN32 /D_WINDOWS /EHsc /D_STLP_USE_STATIC_LIB
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

class AsciiString
{
public:
	char *m_data;
};

class ParticleSystem
{
public:
	void setPosition(const Coord3D *position);
	void setField94(void *value);
	void start();

	unsigned char m_pad[0xAC];
	int m_systemId;
};

ParticleSystem *Make00001B18(void);

class U1CachedHolder;

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
	void rva00617e30();
	void j_0003b1e2();

private:
	unsigned char m_pad00[0x20];
	Coord3D m_position;
	BFMERetailAsciiString m_particleSystemName;
	unsigned char m_pad30[0x240];
	Rva00617D60Vector m_particleSystems;
};

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
