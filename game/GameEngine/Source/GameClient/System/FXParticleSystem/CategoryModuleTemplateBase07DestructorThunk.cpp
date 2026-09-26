// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CategoryModuleTemplateBase (ledger $07 / N=8) empty dual-vtbl dtor.

namespace FXParticleSystem
{

template <int Category>
class CategoryModuleTemplateBase
{
};

template <>
class __declspec(novtable) CategoryModuleTemplateBase<8>
{
public:
	virtual ~CategoryModuleTemplateBase();
};

// ??1?$CategoryModuleTemplateBase@$07@FXParticleSystem@@UAE@XZ
CategoryModuleTemplateBase<8>::~CategoryModuleTemplateBase()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = 0x0107375C;
	*(volatile unsigned int *)this = 0x01073758;
}

}
