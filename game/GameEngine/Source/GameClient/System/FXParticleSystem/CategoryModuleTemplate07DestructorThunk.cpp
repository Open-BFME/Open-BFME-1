// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CategoryModuleTemplate<8> empty dual-vtbl dtor.

namespace FXParticleSystem
{

template <int Category>
class CategoryModuleTemplate
{
};

template <>
class __declspec(novtable) CategoryModuleTemplate<8>
{
public:
	virtual ~CategoryModuleTemplate();
};

// ??1?$CategoryModuleTemplate@$07@FXParticleSystem@@UAE@XZ
CategoryModuleTemplate<8>::~CategoryModuleTemplate()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = 0x0107375C;
	*(volatile unsigned int *)this = 0x01073758;
}

}
