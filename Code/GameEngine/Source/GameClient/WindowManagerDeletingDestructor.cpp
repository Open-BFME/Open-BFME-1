// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: WindowManager scalar-deleting destructor at retail RVA
// 0x0046E820 (30 bytes). The matched constructor at 0x0046E5E0 and matched
// complete destructor at 0x0046D8E0 both use vtable 0x010F72A8. The wrapper
// calls that destructor through ILT 0x00026175 before conditionally invoking
// scalar operator delete.

class WindowManager
{
public:
	virtual ~WindowManager();
};

void forceWindowManagerDeletingDestructor()
{
	WindowManager value;
}
