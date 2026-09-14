// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Open-BFME: Mouse scalar-deleting destructor at retail RVA 0x005A5EB0
// (30 bytes). The wrapper calls Mouse's exact complete destructor at
// 0x005A5500 through ILT 0x000437F2; the recovered BFME layout and the
// established Mouse input hierarchy identify this deleting slot.

class Mouse
{
public:
	virtual ~Mouse();
};

void forceMouseDeletingDestructor()
{
	Mouse value;
}
