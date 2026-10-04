// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CategoryModuleTemplate<5> empty dual-vtbl dtor.

// The retail vtables are named data symbols; declare them by their real name
// (recorded in targets/game/reverse/dir32_addresses.csv) instead of via a
// stand-in plus a linker alias.
extern "C" int __identifier("??_7?$CategoryModuleInfo@$04@FXParticleSystem@@6B@")[];
extern "C" int __identifier("??_7ModuleTemplate@FXParticleSystem@@6B@")[];

namespace FXParticleSystem
{

template <int Category>
class CategoryModuleTemplate
{
};

template <>
class __declspec(novtable) CategoryModuleTemplate<5>
{
public:
	virtual ~CategoryModuleTemplate();
};

// ??1?$CategoryModuleTemplate@$04@FXParticleSystem@@UAE@XZ
CategoryModuleTemplate<5>::~CategoryModuleTemplate()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)__identifier("??_7?$CategoryModuleInfo@$04@FXParticleSystem@@6B@");
	*(volatile unsigned int *)this = (unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@");
}

}
