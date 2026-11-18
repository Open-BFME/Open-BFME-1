// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

// class-gate: allow Coord3D BFME's user copy constructor and destructor, absent from the canonical header, give retail's 0x10 frame and saved argument address for 0x0060BAA0
struct Coord3D
{
public:
	Coord3D() {}
	Coord3D(const Coord3D &that) : x(that.x), y(that.y), z(that.z) {}
	~Coord3D(void) {}
	float x, y, z;
};

class ParticleSystem;
// The null-system accessor (ILT 0x00001B18 -> 0x005CFF50) is defined only as
// ?bfmeNullSystemZA@@YAPAVParticleSystemZA@@XZ; its real name is unproven.
class ParticleSystemZA;
ParticleSystemZA *bfmeNullSystemZA();
#include "../../../Include/Common/ScalarTypes.h"

class ParticleSystemHandle
{
public:
	~ParticleSystemHandle() throw();

	operator Bool() const
	{
		return m_system != 0;
	}

	ParticleSystem *operator->() const
	{
		if( !m_system )
			return (ParticleSystem *)bfmeNullSystemZA();
		return m_system;
	}

	ParticleSystem *m_system;
	ParticleSystemHandle *m_previous;
	ParticleSystemHandle *m_next;
};

class ParticleSystem
{
public:
	void start();
	void stop();
	ParticleSystemHandle getSlave();
	void setPosition(const Coord3D *position);
};

void j_00010069();

// Address-qualified owner: constructor 0x0060BEB0 installs vtable 0x01115E90.
// Slots 8/9 reach 0x0060C140/0x0060C160, which call these methods without
// adjusting ECX. No constructor, RTTI, literal or named caller establishes
// the former LivingWorldEyeTowerSecondaryState label. This view is limited
// to the particle handle at +0x14; the constructor keeps its own ABI view.

class Rva0060BEB0Object
{
public:
	virtual void rva0060BAA0(Coord3D position);
	void startParticleSystems();
	void stopParticleSystems();

private:
	// Base-class slot 7 through ILT 0x00010069. MSVC 7.1 single-inheritance
	// member pointers are one code address with the receiver in ECX.
	void baseSlot7(Coord3D position)
	{
		union { void (*entry)(); void (Rva0060BEB0Object::*method)(Coord3D); } fn;
		fn.entry = &j_00010069;
		(this->*fn.method)(position);
	}

	unsigned char m_unmodelled04[ 0x10 ];
	ParticleSystemHandle m_particleSystem;
	unsigned char m_unmodelled20[ 0xA0 - 0x20 ];
	float m_fieldA0;
	float m_fieldA4;
	float m_fieldA8;
};

// Retail 0x0060BAA0, 142 bytes (ret 0xC): slot 7 of vtable 0x01115E90 through
// ILT 0x0000B785. It calls the base table's slot 7 (ILT 0x00010069, as the
// Rva0060BBD0 sibling at 0x0060B9C0 does) with the by-value position, then
// places the particle system at that position plus the offset at +0xA0 that
// the constructor clears. Method name is address-derived.
void Rva0060BEB0Object::rva0060BAA0(Coord3D position)
{
	baseSlot7(position);
	if( m_particleSystem )
	{
		Coord3D offset;
		offset.x = position.x + m_fieldA0;
		offset.y = position.y + m_fieldA4;
		offset.z = position.z + m_fieldA8;
		m_particleSystem->setPosition(&offset);
	}
}

// ?startParticleSystems@Rva0060BEB0Object@@QAEXXZ
void Rva0060BEB0Object::startParticleSystems()
{
	if( m_particleSystem )
	{
		m_particleSystem->start();
		if( m_particleSystem->getSlave() )
			m_particleSystem->getSlave()->start();
	}
}

// ?stopParticleSystems@Rva0060BEB0Object@@QAEXXZ
void Rva0060BEB0Object::stopParticleSystems()
{
	if( m_particleSystem )
	{
		if( m_particleSystem->getSlave() )
			m_particleSystem->getSlave()->stop();
		m_particleSystem->stop();
	}
}
