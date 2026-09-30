// cl: /DNDEBUG /MD /EHsc

extern "C" const void *bfmeVftSnapshot[];
#pragma comment(linker, "/alternatename:_bfmeVftSnapshot=??_7Snapshot@@6B@")
extern "C" const void *bfmeVftCategoryModuleInfo2[];
#pragma comment(linker, "/alternatename:_bfmeVftCategoryModuleInfo2=??_7?$CategoryModuleInfo@$01@FXParticleSystem@@6B@")
extern "C" const void *bfmeVftModuleTemplate[];
#pragma comment(linker, "/alternatename:_bfmeVftModuleTemplate=??_7ModuleTemplate@FXParticleSystem@@6B@")

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
    *(volatile unsigned int *)info = (unsigned int)bfmeVftSnapshot;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = (unsigned int)bfmeVftCategoryModuleInfo2;
    *(volatile unsigned int *)this = (unsigned int)bfmeVftModuleTemplate;
}

}
