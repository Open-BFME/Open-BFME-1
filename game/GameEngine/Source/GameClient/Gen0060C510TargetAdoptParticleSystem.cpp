// ?adoptParticleSystem@Gen0060C510Target@@QAEXPAVBfmeParticleSystemHandle@@@Z
// The Living World manager passes the newly created BFME particle handle to
// this target method at retail 0x00610D60. The target keeps its handle at
// +0x14 and caches the adopted system ID at +0x20.

typedef unsigned int ParticleSystemID;

class ParticleSystem
{
public:
	unsigned char m_beforeSystemID[0xac];
	ParticleSystemID m_systemID;

};

// The null-system accessor (ILT 0x00001B18 -> 0x005CFF50) is defined only as
// ?bfmeNullSystemZA@@YAPAVParticleSystemZA@@XZ; its real name is unproven.
class ParticleSystemZA;
ParticleSystemZA *bfmeNullSystemZA();

extern "C" void __cdecl __identifier("?apply@U1Sub@@QAEAAV1@PAVU1CachedHolder@@@Z")();
class ParticleSystemHandle
{
public:
	operator bool() const
	{
		return m_system != 0;
	}

	// 0x005C21D0 is ledgered as ?apply@U1Sub@@QAEAAV1@PAVU1CachedHolder@@@Z; call it by that defined name.
	ParticleSystemHandle &operator=(const ParticleSystemHandle &that) throw()
	{
		union { void (__cdecl *symbol)(); ParticleSystemHandle &(ParticleSystemHandle::*member)(const ParticleSystemHandle &); } c;
		c.symbol = &__identifier("?apply@U1Sub@@QAEAAV1@PAVU1CachedHolder@@@Z");
		return (this->*c.member)(that);
	}

	ParticleSystem *operator->() const
	{
		if (m_system == 0)
			return (ParticleSystem *)bfmeNullSystemZA();
		return m_system;
	}

	ParticleSystem *m_system;
	ParticleSystemHandle *m_previous;
	ParticleSystemHandle *m_next;
};

class BfmeParticleSystemHandle : public ParticleSystemHandle
{
};

class Gen0060C510Target
{
public:
	void adoptParticleSystem(BfmeParticleSystemHandle *handle);

private:
	unsigned char m_beforeParticleSystem[0x14];
	ParticleSystemHandle m_particleSystem;
	ParticleSystemID m_particleSystemID;
};

void Gen0060C510Target::adoptParticleSystem(BfmeParticleSystemHandle *handle)
{
	if (*handle)
	{
		m_particleSystem = *handle;
		m_particleSystemID = m_particleSystem->m_systemID;
	}
}
