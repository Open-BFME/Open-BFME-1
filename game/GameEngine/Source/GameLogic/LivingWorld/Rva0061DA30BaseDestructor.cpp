// Destructor of the address-derived LivingWorld owner whose constructor is
// Rva0061DA30BaseConstructor.cpp (0x0061DA30). Both install vtable
// 0x01117624, the only two .text bodies that carry it. The constructor's
// volatile-int view cannot hold members with destructors without changing its
// own code, so this file views the members the destructor tears down, with
// the vtable as a real one so its store comes before the unwind state. The
// view is named after that vtable (its ??_7 then names the address it
// stores); it is the same object as Rva0061DA30Base.
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"

extern const char g_Rva0107301CEmptyString[];

// The reference-counted objects at +0x08..+0x10: slot 0 deletes, the count
// sits at +0x04, and the first two are detached through slot 0x40 first.
class Rva0061E3E0RefObject
{
public:
	virtual void deleteThis();
	virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18();
	virtual void slot1C(); virtual void slot20(); virtual void slot24();
	virtual void slot28(); virtual void slot2C(); virtual void slot30();
	virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void detach();
	int m_numRefs;

	void release()
	{
		if (--m_numRefs == 0)
			deleteThis();
	}
};

// The particle-system handle at +0x14, as Rva0077B3F0.cpp declares it.
struct Rva0077B3F0Particle;
class Rva0077B3F0HandleBase
{
public:
	void rva005C2240() throw();
	Rva0077B3F0Particle *p00;
	Rva0077B3F0HandleBase *p04, *p08;
};
class Rva0077B3F0Handle : public Rva0077B3F0HandleBase
{
public:
	~Rva0077B3F0Handle() throw(); // ILT 00013994 -> 001DA440
};

#include "../../../Include/Common/Enums/ParticleSystemID.h"
class ParticleSystemManager
{
public:
	void destroyParticleSystemByID(ParticleSystemID id);
};
extern ParticleSystemManager *TheParticleSystemManager;

class Rva01117624Owner
{
public:
	~Rva01117624Owner();
	// Vtable 0x01117624; pure so MSVC does not emit its own copy.
	virtual void slot00() = 0;
	AsciiString m_name;
	Rva0061E3E0RefObject *m_object08;
	Rva0061E3E0RefObject *m_object0c;
	Rva0061E3E0RefObject *m_object10;
	Rva0077B3F0Handle m_particleSystem;
	ParticleSystemID m_particleSystemID;
};

// ??1Rva01117624Owner@@QAE@XZ
// Retail 0x0061E3E0, 221 bytes; BfmeSinkAMDrop.cpp and BfmeConv2126.cpp call
// it and then operator delete.
Rva01117624Owner::~Rva01117624Owner()
{
	m_name.StringBase<char>::set(g_Rva0107301CEmptyString, 0);

	if (m_object08)
	{
		m_object08->detach();
		if (m_object08)
		{
			m_object08->release();
			m_object08 = 0;
		}
	}
	if (m_object0c)
	{
		m_object0c->detach();
		if (m_object0c)
		{
			m_object0c->release();
			m_object0c = 0;
		}
	}
	if (m_object10)
	{
		m_object10->release();
		m_object10 = 0;
	}

	if (m_particleSystem.p00)
	{
		TheParticleSystemManager->destroyParticleSystemByID(m_particleSystemID);
		m_particleSystem.rva005C2240();
		m_particleSystemID = INVALID_PARTICLE_SYSTEM_ID;
	}
}
