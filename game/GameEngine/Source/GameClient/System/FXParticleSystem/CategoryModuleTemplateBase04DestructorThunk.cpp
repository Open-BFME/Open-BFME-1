// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CategoryModuleTemplateBase (ledger $04 / N=5) empty dual-vtbl dtor.

namespace FXParticleSystem
{

template <int Category>
class CategoryModuleTemplateBase
{
};

template <>
class __declspec(novtable) CategoryModuleTemplateBase<5>
{
public:
	virtual ~CategoryModuleTemplateBase();
};

// ??1?$CategoryModuleTemplateBase@$04@FXParticleSystem@@UAE@XZ
CategoryModuleTemplateBase<5>::~CategoryModuleTemplateBase()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = 0x0110F9AC;
	*(volatile unsigned int *)this = 0x01073758;
}

}
