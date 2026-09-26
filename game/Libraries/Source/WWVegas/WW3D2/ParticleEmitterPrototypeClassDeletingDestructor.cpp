// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: ParticleEmitterPrototypeClass scalar-deleting destructor at retail
// RVA 0x0014ABD0 (30 bytes). The exact constructor at 0x00149F90 installs
// vtable 0x01095704, whose slot zero routes through ILT 0x00036197 to this
// wrapper. The particle loader's concrete allocation corroborates identity;
// the complete destructor is called through ILT 0x0001BBCB.

class ParticleEmitterPrototypeClass
{
public:
	virtual ~ParticleEmitterPrototypeClass();
};

void forceParticleEmitterPrototypeClassDeletingDestructor()
{
	ParticleEmitterPrototypeClass value;
}
