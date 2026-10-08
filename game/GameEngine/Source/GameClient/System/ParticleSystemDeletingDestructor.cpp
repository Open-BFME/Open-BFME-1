// cl: /O2
// Open-BFME: ParticleSystem scalar-deleting destructor wrapper,
// retail 0x005CEAB0 (30 bytes).  The vtable at 0x0110FE48 routes through
// ILT 0x00427C14 to this wrapper; its destructor callee uses ILT 0x00407CBB.
// The destructor itself is matched in ParticleSystemDestructor.cpp.

class ParticleSystem
{
protected:
	virtual ~ParticleSystem();

private:
	// Forcer-only constructor: emits the vftable (and so this ??_G) here
	// without a second copy of the destructor.
	explicit ParticleSystem(int) {}
	friend void forceParticleSystemDeletingDestructor();
};

void forceParticleSystemDeletingDestructor()
{
	ParticleSystem value(0);
}
