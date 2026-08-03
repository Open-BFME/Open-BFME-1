// cl: /DNDEBUG /MD /EHsc

namespace FXParticleSystem
{

extern const char RENDEROBJECT_UPDATE_MODULE_KEY[1];
extern const char RENDEROBJECT_UPDATE_MODULE_NAME[1];

template <int Category, const char (&Key)[1], const char (&Name)[1], class Module, class ModuleTemplate, class ParticleModule, class ParticleModuleTemplate>
class ModuleTag
{
};

class RenderObjectUpdateModule
{
};

class RenderObjectUpdateModuleTemplate
{
};

class RenderObjectParticleUpdateModule
{
};

class RenderObjectParticleUpdateModuleTemplate
{
};

template <class Tag>
class ConcreteModuleTemplate
{
};

template <>
class ConcreteModuleTemplate<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule, RenderObjectParticleUpdateModuleTemplate> >
{
public:
    virtual RenderObjectUpdateModuleTemplate *clone() const;
};

__declspec(naked) RenderObjectUpdateModuleTemplate *ConcreteModuleTemplate<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule, RenderObjectParticleUpdateModuleTemplate> >::clone() const
{
    __asm {
        __emit 0x56
        __emit 0x68
        __emit 0xa0
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0xf1
        __emit 0xe8
        __emit 0xf3
        __emit 0x51
        __emit 0x2a
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x85
        __emit 0xc0
        __emit 0x74
        __emit 0x0a
        __emit 0x56
        __emit 0x8b
        __emit 0xc8
        __emit 0xe8
        __emit 0x03
        __emit 0x43
        __emit 0xa3
        __emit 0xff
        __emit 0x5e
        __emit 0xc3
        __emit 0x33
        __emit 0xc0
        __emit 0x5e
        __emit 0xc3
    }
}

}
