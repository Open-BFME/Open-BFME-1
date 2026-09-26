// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CategoryModuleTemplateBase (ledger $03 / N=4) empty dual-vtbl dtor.

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
	*(volatile unsigned int *)base = 0x0110F9CC;
	*(volatile unsigned int *)this = 0x01073758;
}

}
