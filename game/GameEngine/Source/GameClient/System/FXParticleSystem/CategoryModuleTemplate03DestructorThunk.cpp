// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CategoryModuleTemplate<4> empty dual-vtbl dtor.

namespace FXParticleSystem
{

template <int Category>
class CategoryModuleTemplate
{
};

template <>
class __declspec(novtable) CategoryModuleTemplate<4>
{
public:
	virtual ~CategoryModuleTemplate();
};

// ??1?$CategoryModuleTemplate@$03@FXParticleSystem@@UAE@XZ
CategoryModuleTemplate<4>::~CategoryModuleTemplate()
{
	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = 0x0110F9CC;
	*(volatile unsigned int *)this = 0x01073758;
}

}
