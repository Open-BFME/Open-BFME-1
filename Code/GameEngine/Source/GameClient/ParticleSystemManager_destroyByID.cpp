// cl: /DNDEBUG /MD /EHsc
// readable body of ?destroyParticleSystemByID@ParticleSystemManager@@QAEXW4ParticleSystemID@@@Z: Code/GameEngine/Source/GameClient/System/ParticleSys.cpp
// Open-BFME: ParticleSystemManager::destroyParticleSystemByID, retail
// 0x005C3C10, 84 bytes.
//
// The reference's two lines, but the lookup hands back a value rather than a
// bare pointer: the call takes a hidden return slot, the system is read out of
// its first word, and whatever it is gets released on the way out -- an unwind
// frame is set up for exactly that. So it is modelled as a small handle, which
// is all the body says about it.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum ParticleSystemID { INVALID_PARTICLE_SYSTEM_ID = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ParticleSys.h
class ParticleSystem
{
public:
	void destroy(void);					// ILT 0x0000E525
};

// Returned by value and released here; nothing beyond its first word is
// touched, so nothing more is claimed about it.
class BfmeParticleSystemHandle
{
public:
	BfmeParticleSystemHandle(const BfmeParticleSystemHandle &that);
	~BfmeParticleSystemHandle() throw();				// ILT 0x00013994

	ParticleSystem *m_system;				// this+0x00

private:
	char m_bfme_tail[8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ParticleSys.h
class ParticleSystemManager
{
public:
	void destroyParticleSystemByID(ParticleSystemID id);

private:
	BfmeParticleSystemHandle findParticleSystemByID(ParticleSystemID id);	// ILT 0x0002A216
};

void ParticleSystemManager::destroyParticleSystemByID( ParticleSystemID id )
{
	BfmeParticleSystemHandle sys = findParticleSystemByID(id);

	if (sys.m_system)
		sys.m_system->destroy();
}
