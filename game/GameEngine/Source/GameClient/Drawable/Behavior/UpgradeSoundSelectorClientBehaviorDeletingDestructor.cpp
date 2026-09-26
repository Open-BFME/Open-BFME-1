// cl: /DNDEBUG /MD /EHsc

// Open-BFME: UpgradeSoundSelectorClientBehavior scalar-deleting destructor
// at retail RVA 0x00124BC0 (30 bytes). The dedicated constructor at
// 0x00121F60 and friend_newModuleInstance factory at 0x00124B30 establish
// the class; constructor/factory carry vtable 0x0108AD18, whose slot zero
// routes through ILT 0x0001189C. The wrapper calls complete destructor
// through ILT 0x000369B7 to 0x00124BF0.
//
// The complete tail body is the existing 11-byte
// Rva00124BF0TailDtor row; its address-derived source remains untouched.
class UpgradeSoundSelectorClientBehavior
{
public:
	virtual ~UpgradeSoundSelectorClientBehavior();
};

void forceUpgradeSoundSelectorClientBehaviorDeletingDestructor()
{
	UpgradeSoundSelectorClientBehavior value;
}
