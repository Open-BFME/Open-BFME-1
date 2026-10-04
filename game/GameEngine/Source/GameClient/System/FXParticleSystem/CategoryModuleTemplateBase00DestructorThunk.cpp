// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CategoryModuleTemplateBase<1> empty dual-vtbl dtor.

// The two vftables this dtor parks are named by their compiler-emitted
// symbols.  __identifier spells them directly, so no linker alias is needed;
// the array type keeps the decay-to-pointer that `mov dword ptr [reg], imm32`
// needs (a plain int declaration would load the vftable's first slot instead).
extern "C" const char __identifier("??_7V3Vt0110F978@@6B@")[];
extern "C" const char __identifier("??_7ModuleTemplate@FXParticleSystem@@6B@")[];

namespace FXParticleSystem
{

template <int Category>
class CategoryModuleTemplateBase
{
};

template <>
class __declspec(novtable) CategoryModuleTemplateBase<1>
{
public:
	virtual ~CategoryModuleTemplateBase();
};

// ??1?$CategoryModuleTemplateBase@$00@FXParticleSystem@@UAE@XZ
CategoryModuleTemplateBase<1>::~CategoryModuleTemplateBase()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)__identifier("??_7V3Vt0110F978@@6B@");
	*(volatile unsigned int *)this = (unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@");
}

}
