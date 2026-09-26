// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DefaultModuleTemplate<6> empty dual-vtbl dtor (50B Sphere pattern).

namespace FXParticleSystem
{

template <int Category>
class DefaultModuleTemplate
{
};

template <>
class __declspec(novtable) DefaultModuleTemplate<6>
{
public:
	virtual ~DefaultModuleTemplate();
};

DefaultModuleTemplate<6>::~DefaultModuleTemplate()
{
	unsigned char *info = this ? (unsigned char *)this + 8 : 0;
	*(volatile unsigned int *)info = 0x01073744;

	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = 0x0110F97C;
	*(volatile unsigned int *)this = 0x01073758;
}

}
