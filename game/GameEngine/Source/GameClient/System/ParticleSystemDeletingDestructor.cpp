// cl: /O2
// Open-BFME: ParticleSystem scalar-deleting destructor wrapper,
// retail 0x005CEAB0 (30 bytes).  The vtable at 0x0110FE48 routes through
// ILT 0x00427C14 to this wrapper; its destructor callee uses ILT 0x00407CBB.

class ParticleSystem
{
protected:
	__declspec(noinline) virtual ~ParticleSystem();
};

ParticleSystem::~ParticleSystem()
{
}
