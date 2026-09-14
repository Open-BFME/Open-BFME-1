// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: DirectInputMouse scalar-deleting destructor at retail RVA
// 0x006BBCF0 (30 bytes). The matched constructor at 0x006BB7F0 and complete
// destructor at 0x006BB820 both install vtable 0x0111CE08. Win32DIMouse.cpp
// also fixes the DirectInputMouse layout with its Mouse tail and owned
// interfaces at +0x4E14/+0x4E18, establishing the named class identity.

class DirectInputMouse
{
public:
	virtual ~DirectInputMouse();
};

void forceDirectInputMouseDeletingDestructor()
{
	DirectInputMouse value;
}
