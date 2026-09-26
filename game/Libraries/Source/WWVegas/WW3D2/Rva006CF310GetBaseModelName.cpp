// ?getBaseModelName@Rva006CF310RenderObjClass@@UBEPBDXZ
// The RenderObjClass vtable places this null default immediately after
// Get_Name and Set_Name at 0x006CF2F0 and 0x006CF300.

// cl: /O2 /DNDEBUG /MD /EHsc
class Rva006CF310RenderObjClass
{
public:
	virtual const char *getBaseModelName() const
	;
};

const char *Rva006CF310RenderObjClass::getBaseModelName() const
{
	return 0;
}
