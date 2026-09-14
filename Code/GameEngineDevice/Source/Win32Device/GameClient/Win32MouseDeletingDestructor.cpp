// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: Win32Mouse scalar-deleting destructor at retail RVA 0x006BC300
// (30 bytes). W3DMouse's matched construction and teardown call the Win32Mouse
// constructor and virtual destructor, while the recovered Win32 event, cursor,
// and input methods corroborate the class. The wrapper calls the complete
// destructor through ILT 0x0002BC1A before conditionally invoking delete.

class Win32Mouse
{
public:
	virtual ~Win32Mouse();
};

void forceWin32MouseDeletingDestructor()
{
	Win32Mouse value;
}
