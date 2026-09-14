// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: Shell scalar-deleting destructor at retail RVA 0x0057FF00
// (30 bytes). The matched constructor at 0x0057F650 and complete destructor
// at 0x0057F7A0 both install vtable 0x0110B558. The wrapper calls that
// destructor through ILT 0x0002464A before conditionally invoking scalar
// operator delete.

class Shell
{
public:
	virtual ~Shell();
};

void forceShellDeletingDestructor()
{
	Shell value;
}
