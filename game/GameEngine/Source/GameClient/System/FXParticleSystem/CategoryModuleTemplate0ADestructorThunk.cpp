// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CategoryModuleTemplate<0> empty dual-vtbl dtor.

namespace FXParticleSystem
{

template <int Category>
class CategoryModuleTemplate
{
};

template <>
class __declspec(novtable) CategoryModuleTemplate<0>
{
public:
	virtual ~CategoryModuleTemplate();
};

// ??1?$CategoryModuleTemplate@$0A@@FXParticleSystem@@UAE@XZ
CategoryModuleTemplate<0>::~CategoryModuleTemplate()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = 0x01073760;
	*(volatile unsigned int *)this = 0x01073758;
}

}
