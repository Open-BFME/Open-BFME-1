// cl: /DNDEBUG /MD /EHsc

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
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f9e8;
    *(volatile unsigned int *)this = 0x01073758;
}

}
