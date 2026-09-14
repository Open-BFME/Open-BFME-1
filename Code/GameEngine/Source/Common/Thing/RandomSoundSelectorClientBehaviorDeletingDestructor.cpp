// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: RandomSoundSelectorClientBehavior scalar-deleting destructor at
// retail RVA 0x00607BA0 (30 bytes). The exact constructor at 0x00607A30
// installs primary vtable 0x01115918, whose slot zero routes through ILT
// 0x000380F0 to this wrapper. The named module factory at 0x00122040
// corroborates identity; the complete destructor is called through 0x0004374D.

class RandomSoundSelectorClientBehavior
{
public:
	virtual ~RandomSoundSelectorClientBehavior();
};

void forceRandomSoundSelectorClientBehaviorDeletingDestructor()
{
	RandomSoundSelectorClientBehavior value;
}
