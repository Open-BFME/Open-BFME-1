// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CategoryModuleTemplateBase (ledger $03 / N=4) empty dual-vtbl dtor.

// Retail stores these two vftable addresses as immediates: ModuleTemplate's
// at VA 0x01073758 (targets/game/reverse/symbols.csv) and
// CategoryModuleInfo<3>'s at VA 0x00D0F9CC (exports.csv). Both are
// compiler-emitted vftable special names, so they are declared by their own
// decorated name and referenced directly -- no linker alias.
extern "C" const void *__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@")[];
extern "C" const void *__identifier("??_7?$CategoryModuleInfo@$03@FXParticleSystem@@6B@")[];

namespace FXParticleSystem
{

template <int Category>
class CategoryModuleTemplateBase
{
};

// MSVC mangles CategoryModuleTemplateBase<4> as @$03
template <>
class __declspec(novtable) CategoryModuleTemplateBase<4>
{
public:
	virtual ~CategoryModuleTemplateBase();
};

// ??1?$CategoryModuleTemplateBase@$03@FXParticleSystem@@UAE@XZ
CategoryModuleTemplateBase<4>::~CategoryModuleTemplateBase()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)__identifier("??_7?$CategoryModuleInfo@$03@FXParticleSystem@@6B@");
	*(volatile unsigned int *)this = (unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@");
}

}
