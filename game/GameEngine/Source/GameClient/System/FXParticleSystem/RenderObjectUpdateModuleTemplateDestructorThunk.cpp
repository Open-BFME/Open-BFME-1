// cl: /DNDEBUG /MD /EHsc

// Retail stores three vftable addresses here. The declarations carry no C++
// name: __identifier spells the retail symbol exactly (the pattern used by
// WorldHeightMapRva0074ACB0Load.cpp), so the stores below reference the
// defining vftable names instead of a linker alias.
extern "C" int __identifier("??_7Snapshot@@6B@")[];
extern "C" int __identifier("??_7?$CategoryModuleInfo@$01@FXParticleSystem@@6B@")[];
extern "C" int __identifier("??_7ModuleTemplate@FXParticleSystem@@6B@")[];

namespace FXParticleSystem
{

class __declspec(novtable) RenderObjectUpdateModuleTemplate
{
public:
    virtual ~RenderObjectUpdateModuleTemplate();
};

// ??1RenderObjectUpdateModuleTemplate@FXParticleSystem@@UAE@XZ
RenderObjectUpdateModuleTemplate::~RenderObjectUpdateModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = (unsigned int)__identifier("??_7Snapshot@@6B@");

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = (unsigned int)__identifier("??_7?$CategoryModuleInfo@$01@FXParticleSystem@@6B@");
    *(volatile unsigned int *)this = (unsigned int)__identifier("??_7ModuleTemplate@FXParticleSystem@@6B@");
}

}
