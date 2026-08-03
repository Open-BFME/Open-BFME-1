// cl: /DNDEBUG /MD /EHsc

void __cdecl operator delete(void *block) throw();

namespace FXParticleSystem
{

class __declspec(novtable) RenderObjectUpdateModuleTemplate
{
public:
    virtual ~RenderObjectUpdateModuleTemplate();
    __declspec(noinline) void destroyComplete();
    void *destroyAndMaybeDelete(unsigned int flags);
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

// Complete destructor body shared with the scalar deleting wrapper.
void RenderObjectUpdateModuleTemplate::destroyComplete()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f9e8;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??_GRenderObjectUpdateModuleTemplate@FXParticleSystem@@UAEPAXI@Z
void *RenderObjectUpdateModuleTemplate::destroyAndMaybeDelete(unsigned int flags)
{
    destroyComplete();
    if (flags & 1)
        ::operator delete(this);
    return this;
}

}
