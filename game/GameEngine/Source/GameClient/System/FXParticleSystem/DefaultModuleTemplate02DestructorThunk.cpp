// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DefaultModuleTemplate<3> empty dual-vtbl dtor (50B Sphere pattern).

namespace FXParticleSystem
{

template <int Category>
class DefaultModuleTemplate
{
};

template <>
class __declspec(novtable) DefaultModuleTemplate<3>
{
public:
	virtual ~DefaultModuleTemplate();
};

DefaultModuleTemplate<3>::~DefaultModuleTemplate()
{
	unsigned char *info = this ? (unsigned char *)this + 8 : 0;
	*(volatile unsigned int *)info = 0x01073744;

	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = 0x0110F9E4;
	*(volatile unsigned int *)this = 0x01073758;
}

}
