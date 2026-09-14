// cl: /DNDEBUG /MD /EHsc

// Open-BFME: HotKeyManager scalar-deleting destructor at retail RVA
// 0x005B3AA0 (30 bytes). The exact constructor at 0x005B39E0 installs the
// 0x0110DE08 vtable, whose slot-zero ILT 0x00046F1A routes here. The class
// header, existing HotKeyManager methods, and the complete destructor body at
// 0x005B37C0 corroborate the identity: it restores that vtable, destroys the
// two map members at +0x08 and +0x14, and then destroys SubsystemInterface.

class HotKeyManager
{
public:
	virtual ~HotKeyManager();
};

void forceHotKeyManagerDeletingDestructor()
{
	HotKeyManager value;
}
