// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CategoryModuleTemplate<3> empty dual-vtbl dtor.

// The declarations carry no C++ name: __identifier spells the retail symbol
// exactly, so the stores below reference the defining name.
extern "C" int __identifier("??_7?$CategoryModuleInfo@$02@FXParticleSystem@@6B@");
extern "C" int __identifier("??_7ModuleTemplate@FXParticleSystem@@6B@");

namespace FXParticleSystem
{

template <int Category>
class CategoryModuleTemplate
{
};

template <>
class __declspec(novtable) CategoryModuleTemplate<3>
{
public:
	virtual ~CategoryModuleTemplate();
};

// ??1?$CategoryModuleTemplate@$02@FXParticleSystem@@UAE@XZ
CategoryModuleTemplate<3>::~CategoryModuleTemplate()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base =
		(unsigned int)&__identifier("??_7?$CategoryModuleInfo@$02@FXParticleSystem@@6B@");
	*(volatile unsigned int *)this =
		(unsigned int)&__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@");
}

}
