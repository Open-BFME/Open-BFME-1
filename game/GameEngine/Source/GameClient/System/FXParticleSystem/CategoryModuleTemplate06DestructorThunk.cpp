// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CategoryModuleTemplate (ledger $05 / N=6) empty dual-vtbl dtor.

namespace FXParticleSystem
{

template <int Category>
class CategoryModuleTemplate
{
};

template <>
class __declspec(novtable) CategoryModuleTemplate<6>
{
public:
	virtual ~CategoryModuleTemplate();
};

// ??1?$CategoryModuleTemplate@$05@FXParticleSystem@@UAE@XZ
CategoryModuleTemplate<6>::~CategoryModuleTemplate()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = 0x0110F97C;
	*(volatile unsigned int *)this = 0x01073758;
}

}
