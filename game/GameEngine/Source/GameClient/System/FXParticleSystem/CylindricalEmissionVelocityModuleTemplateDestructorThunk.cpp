// cl: /DNDEBUG /MD /EHsc
// CylindricalEmissionVelocityModuleTemplate empty triple-vtbl dtor at 0x005D78F0.
// Retail 50B: this+8 / this+4 / this vtbl stores (DIR32-masked). The scalar
// destructor ILT 0x0004099E routes directly to 0x005D78F0 and the vector
// deleting destructor at 0x005D7A10 calls through the same ILT; landed
// neighbours (ctor 0x005D7860, copy ctor 0x005D7930, operator= 0x005D7980)
// sit either side in the same TU family.

// The three class tables this dtor plants are named by their retail decorated
// symbols directly (the vftable symbol of the class itself), the same
// __identifier() spelling the vtable users elsewhere in the tree use, so no
// linker stand-in symbol name is needed.
extern "C" const void *__identifier("??_7Snapshot@@6B@")[];
extern "C" const void *__identifier("??_7?$CategoryModuleInfo@$03@FXParticleSystem@@6B@")[];
extern "C" const void *__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@")[];

namespace FXParticleSystem
{

class __declspec(novtable) CylindricalEmissionVelocityModuleTemplate
{
public:
	virtual ~CylindricalEmissionVelocityModuleTemplate();
};

// ??1CylindricalEmissionVelocityModuleTemplate@FXParticleSystem@@UAE@XZ
CylindricalEmissionVelocityModuleTemplate::~CylindricalEmissionVelocityModuleTemplate()
{
	unsigned char *info = this ? (unsigned char *)this + 8 : 0;
	*(volatile unsigned int *)info = (unsigned int)__identifier("??_7Snapshot@@6B@");

	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)__identifier("??_7?$CategoryModuleInfo@$03@FXParticleSystem@@6B@");
	*(volatile unsigned int *)this = (unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@");
}

}
