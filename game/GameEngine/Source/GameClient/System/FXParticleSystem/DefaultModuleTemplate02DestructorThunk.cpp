// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DefaultModuleTemplate<3> empty dual-vtbl dtor (50B Sphere pattern).
// Retail vftables written by the dtor. Each declaration carries no C++ name:
// __identifier spells the retail symbol exactly, so the stores below reference
// the defining name (the same shape as
// game/GameEngineDevice/Source/W3DDevice/GameClient/WorldHeightMapRva0074ACB0Load.cpp).
extern "C" const void *__identifier("??_7Snapshot@@6B@")[];
extern "C" const void *__identifier("??_7?$CategoryModuleInfo@$02@FXParticleSystem@@6B@")[];
extern "C" const void *__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@")[];

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
	*(volatile unsigned int *)info = (unsigned int)__identifier("??_7Snapshot@@6B@");

	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)__identifier("??_7?$CategoryModuleInfo@$02@FXParticleSystem@@6B@");
	*(volatile unsigned int *)this = (unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@");
}

}
