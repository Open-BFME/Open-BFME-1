// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Open-BFME: ParticleSystemFXNugget scalar-deleting destructor at retail RVA
// 0x0042A170 (30 bytes).  Its constructor at 0x00429F80 installs the primary
// vtable 0x010F3520, whose slot zero reaches this wrapper through ILT
// 0x000463E9.  The wrapper calls the matched complete destructor at 0x0042A1A0
// through ILT 0x0003D8D4 and then operator delete.

class ParticleSystemFXNugget
{
public:
	virtual ~ParticleSystemFXNugget();
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceParticleSystemFXNuggetDeletingDestructor(const ParticleSystemFXNugget &that)
{
	ParticleSystemFXNugget value(that);
}
