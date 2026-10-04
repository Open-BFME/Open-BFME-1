// cl: /O2
// Retail RVA 0x005DB900. Destructor ILT 0x0003B8DB routes directly to the
// matched SphericalEmissionVelocity specialization destructor at 0x005DB850.
// The three vftable DATA symbols this destructor stores are named by their
// defining mangled names; __identifier (MSVC's verbatim-name extension)
// declares a reference to them without declaring the classes whose vftables
// they are, so no linker alias stand-in is needed. Same technique as
// game/GameEngine/Source/GameClient/Drawable/Behavior/RandomSoundSelectorClientBehaviorModuleDataDestructor.cpp
extern "C" int __identifier("??_7BfmeBaseVUQ@@6B@")[];
extern "C" int __identifier("??_7?$CategoryModuleInfo@$03@FXParticleSystem@@6B@")[];
extern "C" int __identifier("??_7ModuleTemplate@FXParticleSystem@@6B@")[];

namespace FXParticleSystem
{
extern const char SPHERICAL_EMISSION_VELOCITY_MODULE_KEY[1];
extern const char SPHERICAL_EMISSION_VELOCITY_MODULE_NAME[1];
class SphericalEmissionVelocityModule;
class SphericalEmissionVelocityModuleTemplate;
class SphericalEmissionVelocityInfo;
template<int Category> class DefaultParticleModule;
template<int Category> class DefaultParticleModuleTemplate;
template<int Category, const char (&Key)[1], const char (&Name)[1], class Module,
    class ModuleTemplate, class DefaultModule, class DefaultModuleTemplate>
class ModuleTag;
template<class Tag>
class __declspec(novtable) ConcreteModuleTemplate
{
public:
    virtual ~ConcreteModuleTemplate();
private:
    unsigned char m_data[0x14];
};
// 0x005DB850: SphericalEmissionVelocity ConcreteModuleTemplate specialization
// empty triple-vtbl dtor. Retail 50B: this+8 / this+4 / this vtbl stores
// (DIR32-masked). Destructor ILT 0x0003B8DB routes directly to 0x005DB850;
// scalar deleting dtor at 0x005DB900 and vector deleting dtor at 0x005DB930
// call through the same ILT; landed neighbours (ctor 0x005DB820, copy ctor
// 0x005DB890, operator= 0x005DB8C0) sit either side in the same TU family.
ConcreteModuleTemplate<ModuleTag<4,
    SPHERICAL_EMISSION_VELOCITY_MODULE_KEY,
    SPHERICAL_EMISSION_VELOCITY_MODULE_NAME,
    SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate,
    DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::~ConcreteModuleTemplate()
{
	unsigned char *info = this ? (unsigned char *)this + 8 : 0;
	*(volatile unsigned int *)info = (unsigned int)__identifier("??_7BfmeBaseVUQ@@6B@");

	unsigned char *base = this ? (unsigned char *)this + 4 : 0;
	*(volatile unsigned int *)base = (unsigned int)__identifier("??_7?$CategoryModuleInfo@$03@FXParticleSystem@@6B@");
	*(volatile unsigned int *)this = (unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@");
}
}
