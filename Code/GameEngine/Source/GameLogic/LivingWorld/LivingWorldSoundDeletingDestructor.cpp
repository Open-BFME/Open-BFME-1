// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: LivingWorldSound scalar-deleting destructor at retail RVA
// 0x0061BFC0 (30 bytes). Both exact constructors at 0x0061BF00 and 0x0061CA70
// install vtable 0x011173D4, whose slot zero routes through ILT 0x0001619E to
// this wrapper. The literal snapshot name corroborates identity; the complete
// destructor is called through ILT 0x0001F145.

class LivingWorldSound
{
public:
	virtual ~LivingWorldSound();
};

void forceLivingWorldSoundDeletingDestructor()
{
	LivingWorldSound value;
}
