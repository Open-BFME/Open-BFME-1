// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: RandomSoundSelectorClientBehaviorModuleData scalar-deleting
// destructor at retail RVA 0x0012BDA0 (30 bytes). The matched constructor at
// 0x0012BCC0, factory at 0x0012BE60, and matched complete destructor at
// 0x0012BDD0 establish the class. This wrapper calls the destructor through
// ILT 0x0002D84E before operator delete.

class RandomSoundSelectorClientBehaviorModuleData
{
public:
	virtual ~RandomSoundSelectorClientBehaviorModuleData();
};

void forceRandomSoundSelectorClientBehaviorModuleDataDeletingDestructor()
{
	RandomSoundSelectorClientBehaviorModuleData value;
}
