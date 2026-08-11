// cl: /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include/Common /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib
#include "fx_particle_system.h"
#include <memory.h>

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

// GameClientRandomVariable xfer helper (version + distribution/min/max); lives in
// another translation unit — resolved via reverse/symbols.csv.
void xferRandomVariable(Xfer &xfer, GameClientRandomVariable &v);
void xferInteger(Xfer &xfer, int &value);

namespace FXParticleSystem {

void writeDrawTemplateBase(const void *self, File &file, const unsigned int *flags);
void writeDrawInfo(File &file, const unsigned int *flags);

class LifeEventAsciiStringAssignShim {
public:
    void assign(const void *source);
};

class LightningDrawTemplateAssignShim {
public:
    void assign(const void *source);
};

class RenderObjectDrawTemplateAssignShim {
public:
    void assign(const void *source);
};

class RenderObjectUpdateTemplateAssignShim {
public:
    void assign(const void *source);
};

class ParticleSystemTemplateInfoAssignShim {
public:
    void assign(const void *source);
};

class ParticleSystemTemplateTailAssignShim {
public:
    void assign(const void *source);
};

class TerrainCollisionEventFXLookupShim {
public:
    const FXList *lookup(const char *name) const;
};

struct TerrainCollisionFXNameShim {
    const char *m_text;
};

struct TerrainCollisionInfoView {
    unsigned char padding[0x18];
    const FXList *cached;
};

struct LifeEventInfoView {
    unsigned char padding[0x14];
    const FXList *cached;
};

extern "C" TerrainCollisionEventFXLookupShim *g_terrainCollisionEventFXListStore;

class PointEmissionVolumeTemplateCopyCtorShim {
public:
    void construct(const void *source);
};

class PointEmissionVolumeModuleCtorShim {
public:
    void construct(TrackingPtr<ParticleSystem> &sys, const void *source);
};

__forceinline void initializePointEmissionVolumeModule(void *module)
{
    *(unsigned int *)module = 0x011122e0;
    *(unsigned int *)((unsigned char *)module + 0x14) = 0x011122dc;
    *(unsigned int *)((unsigned char *)module + 0x18) = 0x011122d8;
    *(unsigned int *)((unsigned char *)module + 0x1c) = 0x011122c4;
}

class DefaultModuleTemplate0CtorShim {
public:
    void construct();
};

class DefaultModuleTemplate0CopyCtorShim {
public:
    void construct(const void *source);
};

class DefaultModuleTemplate0AssignShim {
public:
    void assign(const void *source);
};

class DefaultModuleTemplate1CtorShim {
public:
    void construct();
};

class DefaultModuleTemplate1CopyCtorShim {
public:
    void construct(const void *source);
};

class DefaultModuleTemplate1AssignShim {
public:
    void assign(const void *source);
};

class DefaultModuleTemplate2CtorShim {
public:
    void construct();
};

class DefaultModuleTemplate2CopyCtorShim {
public:
    void construct(const void *source);
};

class DefaultModuleTemplate2AssignShim {
public:
    void assign(const void *source);
};

class DefaultModuleTemplate3CtorShim {
public:
    void construct();
};

class DefaultModuleTemplate3CopyCtorShim {
public:
    void construct(const void *source);
};

class DefaultModuleTemplate6CtorShim {
public:
    void construct();
};

class DefaultModuleTemplate6CopyCtorShim {
public:
    void construct(const void *source);
};

class DefaultModuleTemplate7CtorShim {
public:
    void construct();
};

class DefaultModuleTemplate7CopyCtorShim {
public:
    void construct(const void *source);
};

class DefaultModuleTemplate7AssignShim {
public:
    void assign(const void *source);
};

class CylindricalEmissionVelocityTemplateCtorShim {
public:
    void construct();
};

class CylindricalEmissionVelocityTemplateCopyCtorShim {
public:
    void construct(const void *source);
};

class CylinderEmissionVolumeTemplateCopyCtorShim {
public:
    void construct(const void *source);
};

class CylinderEmissionVolumeModuleCtorShim {
public:
    void construct(TrackingPtr<ParticleSystem> &sys, const void *source);
};

__forceinline void initializeCylinderEmissionVolumeModule(void *module)
{
    *(unsigned int *)module = 0x011123e0;
    *(unsigned int *)((unsigned char *)module + 0x14) = 0x011123dc;
    *(unsigned int *)((unsigned char *)module + 0x18) = 0x011123d8;
    *(unsigned int *)((unsigned char *)module + 0x1c) = 0x011123c4;
}

class OutwardEmissionVelocityTemplateCopyCtorShim {
public:
    void construct(const void *source);
};

class OutwardEmissionVelocityTemplateCtorShim {
public:
    void construct();
};

class OutwardEmissionVelocityModuleCtorShim {
public:
    void construct(TrackingPtr<ParticleSystem> &sys, const void *source);
};

__forceinline void initializeOutwardEmissionVelocityModule(void *module)
{
    *(unsigned int *)module = 0x011122ac;
    *(unsigned int *)((unsigned char *)module + 0x14) = 0x011122a8;
    *(unsigned int *)((unsigned char *)module + 0x18) = 0x01112294;
}

class CylindricalEmissionVelocityModuleCtorShim {
public:
    void construct(TrackingPtr<ParticleSystem> &sys, const void *source);
};

__forceinline void initializeCylindricalEmissionVelocityModule(void *module)
{
    *(unsigned int *)module = 0x0111227c;
    *(unsigned int *)((unsigned char *)module + 0x14) = 0x01112278;
    *(unsigned int *)((unsigned char *)module + 0x18) = 0x01112264;
}

class SphericalEmissionVelocityModuleCtorShim {
public:
    void construct(TrackingPtr<ParticleSystem> &sys, const void *source);
};

__forceinline void initializeSphericalEmissionVelocityModule(void *module)
{
    *(unsigned int *)module = 0x0111221c;
    *(unsigned int *)((unsigned char *)module + 0x14) = 0x01112218;
    *(unsigned int *)((unsigned char *)module + 0x18) = 0x01112204;
}

class HemisphericalEmissionVelocityModuleCtorShim {
public:
    void construct(TrackingPtr<ParticleSystem> &sys, const void *source);
};

__forceinline void initializeHemisphericalEmissionVelocityModule(void *module)
{
    *(unsigned int *)module = 0x0111224c;
    *(unsigned int *)((unsigned char *)module + 0x14) = 0x01112248;
    *(unsigned int *)((unsigned char *)module + 0x18) = 0x01112234;
}

class HemisphericalEmissionVelocityTemplateCopyCtorShim {
public:
    void construct(const void *source);
};

class HemisphericalEmissionVelocityTemplateCtorShim {
public:
    void construct();
};

class BoxEmissionVolumeModuleCtorShim {
public:
    void construct(TrackingPtr<ParticleSystem> &sys, const void *source);
};

__forceinline void initializeBoxEmissionVolumeModule(void *module)
{
    *(unsigned int *)module = 0x01112360;
    *(unsigned int *)((unsigned char *)module + 0x14) = 0x0111235c;
    *(unsigned int *)((unsigned char *)module + 0x18) = 0x01112358;
    *(unsigned int *)((unsigned char *)module + 0x1c) = 0x01112344;
}

class LineEmissionVolumeModuleCtorShim {
public:
    void construct(TrackingPtr<ParticleSystem> &sys, const void *source);
};

__forceinline void initializeLineEmissionVolumeModule(void *module)
{
    *(unsigned int *)module = 0x01112320;
    *(unsigned int *)((unsigned char *)module + 0x14) = 0x0111231c;
    *(unsigned int *)((unsigned char *)module + 0x18) = 0x01112318;
    *(unsigned int *)((unsigned char *)module + 0x1c) = 0x01112304;
}

class BoxEmissionVolumeTemplateCopyCtorShim {
public:
    void construct(const void *source);
};

class SphereEmissionVolumeTemplateCopyCtorShim {
public:
    void construct(const void *source);
};

class SphereEmissionVolumeModuleCtorShim {
public:
    void construct(TrackingPtr<ParticleSystem> &sys, const void *source);
};

__forceinline void initializeSphereEmissionVolumeModule(void *module)
{
    *(unsigned int *)module = 0x011123a0;
    *(unsigned int *)((unsigned char *)module + 0x14) = 0x0111239c;
    *(unsigned int *)((unsigned char *)module + 0x18) = 0x01112398;
    *(unsigned int *)((unsigned char *)module + 0x1c) = 0x01112384;
}

class LineEmissionVolumeTemplateCopyCtorShim {
public:
    void construct(const void *source);
};

class SphericalEmissionVelocityTemplateCopyCtorShim {
public:
    void construct(const void *source);
};

class SphericalEmissionVelocityTemplateCtorShim {
public:
    void construct();
};

class LightningEmissionTemplateCtorShim {
public:
    void construct();
};

class ButterflyDrawTemplateCtorShim {
public:
    void construct();
};

class ButterflyDrawTemplateCopyCtorShim {
public:
    void construct(const void *source);
};

class LightningDrawTemplateCtorShim {
public:
    void construct();
};

class LightningDrawTemplateCopyCtorShim {
public:
    void construct(const void *source);
};

class QuadDrawTemplateCtorShim {
public:
    void construct();
};

class QuadDrawTemplateFactoryShim {
public:
    QuadDrawTemplateFactoryShim()
    {
        ((QuadDrawTemplateCtorShim *)this)->construct();
        *(volatile unsigned int *)this = 0x01110e64;
        *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01110e60;
        *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01110e4c;
    }

private:
    unsigned char m_storage[0x0c];
};

class QuadDrawTemplateCopyCtorShim {
public:
    void construct(const void *source);
};

class RenderObjectDrawTemplateCtorShim {
public:
    void construct();
};

class RenderObjectDrawTemplateFactoryShim {
public:
    RenderObjectDrawTemplateFactoryShim()
    {
        ((RenderObjectDrawTemplateCtorShim *)this)->construct();
        *(volatile unsigned int *)this = 0x01111398;
        *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01111394;
        *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01111380;
    }

private:
    unsigned char m_storage[0x48];
};

class RenderObjectDrawTemplateCopyCtorShim {
public:
    void construct(const void *source);
};

class StreakDrawTemplateCtorShim {
public:
    void construct();
};

class StreakDrawTemplateFactoryShim {
public:
    StreakDrawTemplateFactoryShim()
    {
        ((StreakDrawTemplateCtorShim *)this)->construct();
        *(volatile unsigned int *)this = 0x01110e38;
        *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01110e34;
        *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01110e20;
    }

private:
    unsigned char m_storage[12];
};

class StreakDrawTemplateCopyCtorShim {
public:
    void construct(const void *source);
};

class LifeEventTemplateCtorShim {
public:
    void construct();
};

class LifeEventTemplateCopyCtorShim {
public:
    void construct(const void *source);
};

class TerrainCollisionTemplateCtorShim {
public:
    void construct();
};

class TerrainCollisionTemplateCopyCtorShim {
public:
    void construct(const void *source);
};

class OrthoEmissionVelocityTemplateCtorShim {
public:
    void construct();
};

class RenderObjectUpdateTemplateCtorShim {
public:
    void construct();
};

class RenderObjectUpdateTemplateFactoryShim {
public:
    RenderObjectUpdateTemplateFactoryShim()
    {
        ((RenderObjectUpdateTemplateCtorShim *)this)->construct();
        *(volatile unsigned int *)this = 0x01111074;
        *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01111070;
        *(volatile unsigned int *)((unsigned char *)this + 8) = 0x0111105c;
    }

private:
    unsigned char m_storage[0xa0];
};

class RenderObjectUpdateTemplateCopyCtorShim {
public:
    void construct(const void *source);
};

class OrthoEmissionVelocityTemplateCopyCtorShim {
public:
    void construct(const void *source);
};

class OrthoEmissionVelocityModuleCtorShim {
public:
    void construct(TrackingPtr<ParticleSystem> &sys, const void *source);
};

__forceinline void initializeOrthoEmissionVelocityModule(void *module)
{
    *(unsigned int *)module = 0x011121ec;
    *(unsigned int *)((unsigned char *)module + 0x14) = 0x011121e8;
    *(unsigned int *)((unsigned char *)module + 0x18) = 0x011121d4;
}

extern const char BOX_EMISSION_VOLUME_MODULE_TEMPLATE_PARSE_TABLE[];
extern const char BUTTERFLY_DRAW_MODULE_TEMPLATE_PARSE_TABLE[];
extern const char CYLINDER_EMISSION_VOLUME_MODULE_TEMPLATE_PARSE_TABLE[];
extern const char CYLINDRICAL_EMISSION_VELOCITY_MODULE_TEMPLATE_PARSE_TABLE[];
extern const char LIFE_EVENT_MODULE_TEMPLATE_PARSE_TABLE[];
extern const char LIGHTNING_DRAW_MODULE_TEMPLATE_PARSE_TABLE[];
extern const char LIGHTNING_EMISSION_MODULE_TEMPLATE_PARSE_TABLE[];
extern const char LINE_EMISSION_VOLUME_MODULE_TEMPLATE_PARSE_TABLE[];
extern const char ORTHO_EMISSION_VELOCITY_MODULE_TEMPLATE_PARSE_TABLE[];
extern const char OUTWARD_EMISSION_VELOCITY_MODULE_TEMPLATE_PARSE_TABLE[];
extern const char POINT_EMISSION_VOLUME_MODULE_TEMPLATE_PARSE_TABLE[];
extern const char QUAD_DRAW_MODULE_TEMPLATE_PARSE_TABLE[];
extern const char RENDER_OBJECT_DRAW_MODULE_TEMPLATE_PARSE_TABLE[];
extern const char RENDER_OBJECT_UPDATE_MODULE_TEMPLATE_PARSE_TABLE[];
extern const char SPHERE_EMISSION_VOLUME_MODULE_TEMPLATE_PARSE_TABLE[];
extern const char SPHERICAL_EMISSION_VELOCITY_MODULE_TEMPLATE_PARSE_TABLE[];
extern const char STREAK_DRAW_MODULE_TEMPLATE_PARSE_TABLE[];
extern const char TERRAIN_COLLISION_MODULE_TEMPLATE_PARSE_TABLE[];
extern const void *CATEGORY_MODULE_CLASS_0_VTABLE;

// ??0?$ConcreteModuleClass@V?$DefaultModuleTag@$0A@@FXParticleSystem@@@FXParticleSystem@@AAE@XZ
ConcreteModuleClass<DefaultModuleTag<0> >::ConcreteModuleClass()
{
    const void *first = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6ce4));
    void **self = reinterpret_cast<void **>(this);
    const void *second = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6ce0));
    *reinterpret_cast<void **>(0x012f64c4) = this;
    self[0] = (void *)0x01110844;
    self[1] = (void *)second;
    self[2] = (void *)first;
    self[3] = *reinterpret_cast<void **>(0x012f64e8);
    *reinterpret_cast<void **>(0x012f64e8) = this;
    self[0] = (void *)0x011113b8;
}

ConcreteModuleClass<DefaultModuleTag<0> >::~ConcreteModuleClass()
{
    *(const void **)this = &CATEGORY_MODULE_CLASS_0_VTABLE;
}

// ?getClass@?$ConcreteModuleTemplate@V?$DefaultModuleTag@$0A@@FXParticleSystem@@@FXParticleSystem@@UBEABV?$ConcreteModuleClass@V?$DefaultModuleTag@$0A@@FXParticleSystem@@@2@XZ
const ConcreteModuleClass<DefaultModuleTag<0> > &ConcreteModuleTemplate<DefaultModuleTag<0> >::getClass() const
{
    return ConcreteModuleClass<DefaultModuleTag<0> >::getInstance();
}

// ?getInstance@?$ConcreteModuleClass@V?$DefaultModuleTag@$0A@@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ
__declspec(naked) const ConcreteModuleClass<DefaultModuleTag<0> > &ConcreteModuleClass<DefaultModuleTag<0> >::getInstance()
{
    __asm {
        __emit 0x8a
        __emit 0x0d
        __emit 0x60
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xb8
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x84
        __emit 0xc8
        __emit 0x75
        __emit 0x5a
        __emit 0x8b
        __emit 0x15
        __emit 0x60
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x0d
        __emit 0xe0
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x09
        __emit 0x0b
        __emit 0xd0
        __emit 0xa1
        __emit 0xe4
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x00
        __emit 0x89
        __emit 0x15
        __emit 0x60
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xba
        __emit 0x4c
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0x54
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xa1
        __emit 0xe8
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0x68
        __emit 0x90
        __emit 0x06
        __emit 0x07
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0xc4
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0x89
        __emit 0x0d
        __emit 0x50
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0x58
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0xe8
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0x4c
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xb8
        __emit 0x13
        __emit 0x11
        __emit 0x01
        __emit 0xe8
        __emit 0xe0
        __emit 0x6d
        __emit 0x41
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xb8
        __emit 0x4c
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xc3
    }
}

// ??0?$ConcreteModuleClass@V?$DefaultModuleTag@$00@FXParticleSystem@@@FXParticleSystem@@AAE@XZ
ConcreteModuleClass<DefaultModuleTag<1> >::ConcreteModuleClass()
{
    const void *first = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6cd4));
    void **self = reinterpret_cast<void **>(this);
    const void *second = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6cd0));
    *reinterpret_cast<void **>(0x012f64c8) = this;
    self[0] = (void *)0x01110838;
    self[1] = (void *)second;
    self[2] = (void *)first;
    self[3] = *reinterpret_cast<void **>(0x012f64ec);
    *reinterpret_cast<void **>(0x012f64ec) = this;
    self[0] = (void *)0x011113ac;
}

// ??1?$ConcreteModuleClass@V?$DefaultModuleTag@$00@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleClass<DefaultModuleTag<1> >::~ConcreteModuleClass()
{
    *(const void **)this = (const void *)0x01110838;
}

// ?getClass@?$ConcreteModuleTemplate@V?$DefaultModuleTag@$00@FXParticleSystem@@@FXParticleSystem@@UBEABV?$ConcreteModuleClass@V?$DefaultModuleTag@$00@FXParticleSystem@@@2@XZ
const ConcreteModuleClass<DefaultModuleTag<1> > &ConcreteModuleTemplate<DefaultModuleTag<1> >::getClass() const
{
    return ConcreteModuleClass<DefaultModuleTag<1> >::getInstance();
}

// ?getInstance@?$ConcreteModuleClass@V?$DefaultModuleTag@$00@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ
__declspec(naked) const ConcreteModuleClass<DefaultModuleTag<1> > &ConcreteModuleClass<DefaultModuleTag<1> >::getInstance()
{
    __asm {
        __emit 0x8a
        __emit 0x0d
        __emit 0x30
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xb8
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x84
        __emit 0xc8
        __emit 0x75
        __emit 0x5a
        __emit 0x8b
        __emit 0x15
        __emit 0x30
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x0d
        __emit 0xd0
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x09
        __emit 0x0b
        __emit 0xd0
        __emit 0xa1
        __emit 0xd4
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x00
        __emit 0x89
        __emit 0x15
        __emit 0x30
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xba
        __emit 0x1c
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0x24
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xa1
        __emit 0xec
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0x68
        __emit 0xc0
        __emit 0x06
        __emit 0x07
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0xc8
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0x89
        __emit 0x0d
        __emit 0x20
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0x28
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0xec
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0x1c
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xac
        __emit 0x13
        __emit 0x11
        __emit 0x01
        __emit 0xe8
        __emit 0x70
        __emit 0x70
        __emit 0x41
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xb8
        __emit 0x1c
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xc3
    }
}

// ??0?$ConcreteModuleClass@V?$DefaultModuleTag@$01@FXParticleSystem@@@FXParticleSystem@@AAE@XZ
ConcreteModuleClass<DefaultModuleTag<2> >::ConcreteModuleClass()
{
    const void *first = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6d04));
    void **self = reinterpret_cast<void **>(this);
    const void *second = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6d00));
    *reinterpret_cast<void **>(0x012f64cc) = this;
    self[0] = (void *)0x0111085c;
    self[1] = (void *)second;
    self[2] = (void *)first;
    self[3] = *reinterpret_cast<void **>(0x012f64f0);
    *reinterpret_cast<void **>(0x012f64f0) = this;
    self[0] = (void *)0x011113d0;
}

// ??1?$ConcreteModuleClass@V?$DefaultModuleTag@$01@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleClass<DefaultModuleTag<2> >::~ConcreteModuleClass()
{
    *(const void **)this = (const void *)0x0111085c;
}

// ?getClass@?$ConcreteModuleTemplate@V?$DefaultModuleTag@$01@FXParticleSystem@@@FXParticleSystem@@UBEABV?$ConcreteModuleClass@V?$DefaultModuleTag@$01@FXParticleSystem@@@2@XZ
const ConcreteModuleClass<DefaultModuleTag<2> > &ConcreteModuleTemplate<DefaultModuleTag<2> >::getClass() const
{
    return ConcreteModuleClass<DefaultModuleTag<2> >::getInstance();
}

// ?getInstance@?$ConcreteModuleClass@V?$DefaultModuleTag@$01@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ
__declspec(naked) const ConcreteModuleClass<DefaultModuleTag<2> > &ConcreteModuleClass<DefaultModuleTag<2> >::getInstance()
{
    __asm {
        __emit 0x8a
        __emit 0x0d
        __emit 0xc0
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xb8
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x84
        __emit 0xc8
        __emit 0x75
        __emit 0x5a
        __emit 0x8b
        __emit 0x15
        __emit 0xc0
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x0d
        __emit 0x00
        __emit 0x6d
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x09
        __emit 0x0b
        __emit 0xd0
        __emit 0xa1
        __emit 0x04
        __emit 0x6d
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x00
        __emit 0x89
        __emit 0x15
        __emit 0xc0
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xba
        __emit 0xac
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0xb4
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xa1
        __emit 0xf0
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0x68
        __emit 0x30
        __emit 0x06
        __emit 0x07
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0xcc
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0x89
        __emit 0x0d
        __emit 0xb0
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0xb8
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0xf0
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0xac
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xd0
        __emit 0x13
        __emit 0x11
        __emit 0x01
        __emit 0xe8
        __emit 0xc0
        __emit 0x68
        __emit 0x41
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xb8
        __emit 0xac
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xc3
    }
}

// ??0?$ConcreteModuleClass@V?$DefaultModuleTag@$02@FXParticleSystem@@@FXParticleSystem@@AAE@XZ
ConcreteModuleClass<DefaultModuleTag<3> >::ConcreteModuleClass()
{
    const void *first = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6cf4));
    void **self = reinterpret_cast<void **>(this);
    const void *second = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6cf0));
    *reinterpret_cast<void **>(0x012f64d0) = this;
    self[0] = (void *)0x01110850;
    self[1] = (void *)second;
    self[2] = (void *)first;
    self[3] = *reinterpret_cast<void **>(0x012f64f4);
    *reinterpret_cast<void **>(0x012f64f4) = this;
    self[0] = (void *)0x011113c4;
}

// ??1?$ConcreteModuleClass@V?$DefaultModuleTag@$02@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleClass<DefaultModuleTag<3> >::~ConcreteModuleClass()
{
    *(const void **)this = (const void *)0x01110850;
}

// ?getClass@?$ConcreteModuleTemplate@V?$DefaultModuleTag@$02@FXParticleSystem@@@FXParticleSystem@@UBEABV?$ConcreteModuleClass@V?$DefaultModuleTag@$02@FXParticleSystem@@@2@XZ
const ConcreteModuleClass<DefaultModuleTag<3> > &ConcreteModuleTemplate<DefaultModuleTag<3> >::getClass() const
{
    return ConcreteModuleClass<DefaultModuleTag<3> >::getInstance();
}

// ?getInstance@?$ConcreteModuleClass@V?$DefaultModuleTag@$02@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ
__declspec(naked) const ConcreteModuleClass<DefaultModuleTag<3> > &ConcreteModuleClass<DefaultModuleTag<3> >::getInstance()
{
    __asm {
        __emit 0x8a
        __emit 0x0d
        __emit 0x90
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xb8
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x84
        __emit 0xc8
        __emit 0x75
        __emit 0x5a
        __emit 0x8b
        __emit 0x15
        __emit 0x90
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x0d
        __emit 0xf0
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x09
        __emit 0x0b
        __emit 0xd0
        __emit 0xa1
        __emit 0xf4
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x00
        __emit 0x89
        __emit 0x15
        __emit 0x90
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xba
        __emit 0x7c
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0x84
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xa1
        __emit 0xf4
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0x68
        __emit 0x60
        __emit 0x06
        __emit 0x07
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0xd0
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0x89
        __emit 0x0d
        __emit 0x80
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0x88
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0xf4
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0x7c
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xc4
        __emit 0x13
        __emit 0x11
        __emit 0x01
        __emit 0xe8
        __emit 0x50
        __emit 0x6b
        __emit 0x41
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xb8
        __emit 0x7c
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xc3
    }
}

// ??0?$ConcreteModuleClass@V?$DefaultModuleTag@$05@FXParticleSystem@@@FXParticleSystem@@AAE@XZ
ConcreteModuleClass<DefaultModuleTag<6> >::ConcreteModuleClass()
{
    const void *first = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6c9c));
    void **self = reinterpret_cast<void **>(this);
    const void *second = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6c98));
    *reinterpret_cast<void **>(0x012f64dc) = this;
    self[0] = (void *)0x01110820;
    self[1] = (void *)second;
    self[2] = (void *)first;
    self[3] = *reinterpret_cast<void **>(0x012f6500);
    *reinterpret_cast<void **>(0x012f6500) = this;
    self[0] = (void *)0x01111338;
}

// ??1?$ConcreteModuleClass@V?$DefaultModuleTag@$05@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleClass<DefaultModuleTag<6> >::~ConcreteModuleClass()
{
    *(const void **)this = (const void *)0x01110820;
}

// ?getClass@?$ConcreteModuleTemplate@V?$DefaultModuleTag@$05@FXParticleSystem@@@FXParticleSystem@@UBEABV?$ConcreteModuleClass@V?$DefaultModuleTag@$05@FXParticleSystem@@@2@XZ
const ConcreteModuleClass<DefaultModuleTag<6> > &ConcreteModuleTemplate<DefaultModuleTag<6> >::getClass() const
{
    return ConcreteModuleClass<DefaultModuleTag<6> >::getInstance();
}

// ?getInstance@?$ConcreteModuleClass@V?$DefaultModuleTag@$05@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ
__declspec(naked) const ConcreteModuleClass<DefaultModuleTag<6> > &ConcreteModuleClass<DefaultModuleTag<6> >::getInstance()
{
    __asm {
        __emit 0x8a
        __emit 0x0d
        __emit 0x88
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xb8
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x84
        __emit 0xc8
        __emit 0x75
        __emit 0x5a
        __emit 0x8b
        __emit 0x15
        __emit 0x88
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x0d
        __emit 0x98
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x09
        __emit 0x0b
        __emit 0xd0
        __emit 0xa1
        __emit 0x9c
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x00
        __emit 0x89
        __emit 0x15
        __emit 0x88
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xba
        __emit 0x74
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0x7c
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xa1
        __emit 0x00
        __emit 0x65
        __emit 0x2f
        __emit 0x01
        __emit 0x68
        __emit 0xf0
        __emit 0x04
        __emit 0x07
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0xdc
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0x89
        __emit 0x0d
        __emit 0x78
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0x80
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0x00
        __emit 0x65
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0x74
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0x38
        __emit 0x13
        __emit 0x11
        __emit 0x01
        __emit 0xe8
        __emit 0xe0
        __emit 0x7e
        __emit 0x41
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xb8
        __emit 0x74
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xc3
    }
}

// ??0?$ConcreteModuleClass@V?$DefaultModuleTag@$06@FXParticleSystem@@@FXParticleSystem@@AAE@XZ
ConcreteModuleClass<DefaultModuleTag<7> >::ConcreteModuleClass()
{
    const void *first = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6d14));
    void **self = reinterpret_cast<void **>(this);
    const void *second = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6d10));
    *reinterpret_cast<void **>(0x012f64e0) = this;
    self[0] = (void *)0x01110868;
    self[1] = (void *)second;
    self[2] = (void *)first;
    self[3] = *reinterpret_cast<void **>(0x012f6504);
    *reinterpret_cast<void **>(0x012f6504) = this;
    self[0] = (void *)0x011113dc;
}

// ??1?$ConcreteModuleClass@V?$DefaultModuleTag@$06@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleClass<DefaultModuleTag<7> >::~ConcreteModuleClass()
{
    *(const void **)this = (const void *)0x01110868;
}

// ?getClass@?$ConcreteModuleTemplate@V?$DefaultModuleTag@$06@FXParticleSystem@@@FXParticleSystem@@UBEABV?$ConcreteModuleClass@V?$DefaultModuleTag@$06@FXParticleSystem@@@2@XZ
const ConcreteModuleClass<DefaultModuleTag<7> > &ConcreteModuleTemplate<DefaultModuleTag<7> >::getClass() const
{
    return ConcreteModuleClass<DefaultModuleTag<7> >::getInstance();
}

// ?getInstance@?$ConcreteModuleClass@V?$DefaultModuleTag@$06@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ
__declspec(naked) const ConcreteModuleClass<DefaultModuleTag<7> > &ConcreteModuleClass<DefaultModuleTag<7> >::getInstance()
{
    __asm {
        __emit 0x8a
        __emit 0x0d
        __emit 0xf0
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xb8
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x84
        __emit 0xc8
        __emit 0x75
        __emit 0x5a
        __emit 0x8b
        __emit 0x15
        __emit 0xf0
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x0d
        __emit 0x10
        __emit 0x6d
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x09
        __emit 0x0b
        __emit 0xd0
        __emit 0xa1
        __emit 0x14
        __emit 0x6d
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x00
        __emit 0x89
        __emit 0x15
        __emit 0xf0
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xba
        __emit 0xdc
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0xe4
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xa1
        __emit 0x04
        __emit 0x65
        __emit 0x2f
        __emit 0x01
        __emit 0x68
        __emit 0x00
        __emit 0x06
        __emit 0x07
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0xe0
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0x89
        __emit 0x0d
        __emit 0xe0
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0xe8
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0x04
        __emit 0x65
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0xdc
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xdc
        __emit 0x13
        __emit 0x11
        __emit 0x01
        __emit 0xe8
        __emit 0x30
        __emit 0x66
        __emit 0x41
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xb8
        __emit 0xdc
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xc3
    }
}

// ??0?$ConcreteModuleClass@V?$ModuleTag@$01$E?RENDEROBJECT_UPDATE_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_UPDATE_MODULE_NAME@2@3QBDBVRenderObjectUpdateModule@2@VRenderObjectUpdateModuleTemplate@2@VRenderObjectParticleUpdateModule@2@VRenderObjectParticleUpdateModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@AAE@XZ
ConcreteModuleClass<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule, RenderObjectParticleUpdateModuleTemplate> >::ConcreteModuleClass()
{
    const void *first = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6d24));
    void **slots = reinterpret_cast<void **>(this);
    const void *second = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6d20));
    slots[0] = (void *)0x0111085c;
    slots[1] = (void *)second;
    slots[2] = (void *)first;
    slots[3] = *reinterpret_cast<void **>(0x012f64f0);
    *reinterpret_cast<void **>(0x012f64f0) = this;
    slots[0] = (void *)0x01110ed0;
}

// ??1?$ConcreteModuleClass@V?$ModuleTag@$01$E?RENDEROBJECT_UPDATE_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_UPDATE_MODULE_NAME@2@3QBDBVRenderObjectUpdateModule@2@VRenderObjectUpdateModuleTemplate@2@VRenderObjectParticleUpdateModule@2@VRenderObjectParticleUpdateModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleClass<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule, RenderObjectParticleUpdateModuleTemplate> >::~ConcreteModuleClass()
{
    *(const void **)this = (const void *)0x0111085c;
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$01$E?RENDEROBJECT_UPDATE_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_UPDATE_MODULE_NAME@2@3QBDBVRenderObjectUpdateModule@2@VRenderObjectUpdateModuleTemplate@2@VRenderObjectParticleUpdateModule@2@VRenderObjectParticleUpdateModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVRenderObjectUpdateModuleTemplate@2@PAVINI@@@Z
__declspec(naked) RenderObjectUpdateModuleTemplate *ConcreteModuleClass<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule, RenderObjectParticleUpdateModuleTemplate> >::createTemplate(INI *ini) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xa3
        __emit 0xb2
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x68
        __emit 0xa0
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0xcf
        __emit 0x15
        __emit 0x2a
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x85
        __emit 0xf6
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1d
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x13
        __emit 0x4b
        __emit 0xa5
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0x74
        __emit 0x10
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x70
        __emit 0x10
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x08
        __emit 0x5c
        __emit 0x10
        __emit 0x11
        __emit 0x01
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xf6
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0x8f
        __emit 0x24
        __emit 0xa2
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$01$E?RENDEROBJECT_UPDATE_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_UPDATE_MODULE_NAME@2@3QBDBVRenderObjectUpdateModule@2@VRenderObjectUpdateModuleTemplate@2@VRenderObjectParticleUpdateModule@2@VRenderObjectParticleUpdateModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVRenderObjectUpdateModuleTemplate@2@XZ
RenderObjectUpdateModuleTemplate *ConcreteModuleClass<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule, RenderObjectParticleUpdateModuleTemplate> >::createTemplate() const
{
    return (RenderObjectUpdateModuleTemplate *)new RenderObjectUpdateTemplateFactoryShim;
}

// ?getClass@?$ConcreteModuleTemplate@V?$ModuleTag@$01$E?RENDEROBJECT_UPDATE_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_UPDATE_MODULE_NAME@2@3QBDBVRenderObjectUpdateModule@2@VRenderObjectUpdateModuleTemplate@2@VRenderObjectParticleUpdateModule@2@VRenderObjectParticleUpdateModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@UBEABV?$ConcreteModuleClass@V?$ModuleTag@$01$E?RENDEROBJECT_UPDATE_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_UPDATE_MODULE_NAME@2@3QBDBVRenderObjectUpdateModule@2@VRenderObjectUpdateModuleTemplate@2@VRenderObjectParticleUpdateModule@2@VRenderObjectParticleUpdateModuleTemplate@2@@FXParticleSystem@@@2@XZ
const ConcreteModuleClass<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule, RenderObjectParticleUpdateModuleTemplate> > &ConcreteModuleTemplate<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule, RenderObjectParticleUpdateModuleTemplate> >::getClass() const
{
    return ConcreteModuleClass<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule, RenderObjectParticleUpdateModuleTemplate> >::getInstance();
}

// ?getInstance@?$ConcreteModuleClass@V?$ModuleTag@$01$E?RENDEROBJECT_UPDATE_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_UPDATE_MODULE_NAME@2@3QBDBVRenderObjectUpdateModule@2@VRenderObjectUpdateModuleTemplate@2@VRenderObjectParticleUpdateModule@2@VRenderObjectParticleUpdateModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ
__declspec(naked) const ConcreteModuleClass<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule, RenderObjectParticleUpdateModuleTemplate> > &ConcreteModuleClass<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule, RenderObjectParticleUpdateModuleTemplate> >::getInstance()
{
    __asm {
        __emit 0x8a
        __emit 0x0d
        __emit 0x20
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xb8
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x84
        __emit 0xc8
        __emit 0x75
        __emit 0x53
        __emit 0x8b
        __emit 0x15
        __emit 0x20
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x0d
        __emit 0x20
        __emit 0x6d
        __emit 0x2f
        __emit 0x01
        __emit 0x0b
        __emit 0xd0
        __emit 0xa1
        __emit 0x24
        __emit 0x6d
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x00
        __emit 0x89
        __emit 0x15
        __emit 0x20
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x11
        __emit 0xa3
        __emit 0x14
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xa1
        __emit 0xf0
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0x68
        __emit 0xe0
        __emit 0x05
        __emit 0x07
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0x10
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0x18
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0xf0
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0x0c
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0x0c
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xd0
        __emit 0x0e
        __emit 0x11
        __emit 0x01
        __emit 0xe8
        __emit 0x17
        __emit 0x65
        __emit 0x41
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xb8
        __emit 0x0c
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xc3
    }
}

// ??0?$ConcreteModuleClass@V?$ModuleTag@$03$E?CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVCylindricalEmissionVelocityModule@2@VCylindricalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@AAE@XZ
ConcreteModuleClass<ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::ConcreteModuleClass()
{
    const void *first = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6d4c));
    void **slots = reinterpret_cast<void **>(this);
    const void *second = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6d48));
    slots[0] = (void *)0x01110880;
    slots[1] = (void *)second;
    slots[2] = (void *)first;
    slots[3] = *reinterpret_cast<void **>(0x012f64f8);
    *reinterpret_cast<void **>(0x012f64f8) = this;
    slots[0] = (void *)0x01110f00;
}

// ??1?$ConcreteModuleClass@V?$ModuleTag@$03$E?CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVCylindricalEmissionVelocityModule@2@VCylindricalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleClass<ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::~ConcreteModuleClass()
{
    *(const void **)this = (const void *)0x01110880;
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$03$E?CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVCylindricalEmissionVelocityModule@2@VCylindricalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVCylindricalEmissionVelocityModuleTemplate@2@PAVINI@@@Z
__declspec(naked) CylindricalEmissionVelocityModuleTemplate *ConcreteModuleClass<ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::createTemplate(INI *ini) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xe3
        __emit 0xb3
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x6a
        __emit 0x24
        __emit 0xe8
        __emit 0x72
        __emit 0x0e
        __emit 0x2a
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x85
        __emit 0xf6
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1d
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0xdd
        __emit 0x9d
        __emit 0xa6
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0x24
        __emit 0x11
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x20
        __emit 0x11
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x08
        __emit 0x0c
        __emit 0x11
        __emit 0x11
        __emit 0x01
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xf6
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0x70
        __emit 0xcd
        __emit 0xa4
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$03$E?CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVCylindricalEmissionVelocityModule@2@VCylindricalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVCylindricalEmissionVelocityModuleTemplate@2@XZ
__declspec(naked) CylindricalEmissionVelocityModuleTemplate *ConcreteModuleClass<ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::createTemplate() const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x0b
        __emit 0xb4
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x6a
        __emit 0x24
        __emit 0xe8
        __emit 0xd2
        __emit 0x0d
        __emit 0x2a
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x33
        __emit 0xc0
        __emit 0x3b
        __emit 0xf0
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x74
        __emit 0x1d
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x3f
        __emit 0x9d
        __emit 0xa6
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0x24
        __emit 0x11
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x20
        __emit 0x11
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x08
        __emit 0x0c
        __emit 0x11
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xc6
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc3
    }
}

// ?getClass@?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVCylindricalEmissionVelocityModule@2@VCylindricalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@UBEABV?$ConcreteModuleClass@V?$ModuleTag@$03$E?CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVCylindricalEmissionVelocityModule@2@VCylindricalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@2@XZ
const ConcreteModuleClass<ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &ConcreteModuleTemplate<ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::getClass() const
{
    return ConcreteModuleClass<ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::getInstance();
}

// ?getInstance@?$ConcreteModuleClass@V?$ModuleTag@$03$E?CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVCylindricalEmissionVelocityModule@2@VCylindricalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ
__declspec(naked) const ConcreteModuleClass<ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &ConcreteModuleClass<ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::getInstance()
{
    __asm {
        __emit 0x8a
        __emit 0x0d
        __emit 0x98
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xb8
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x84
        __emit 0xc8
        __emit 0x75
        __emit 0x53
        __emit 0x8b
        __emit 0x15
        __emit 0x98
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x0d
        __emit 0x48
        __emit 0x6d
        __emit 0x2f
        __emit 0x01
        __emit 0x0b
        __emit 0xd0
        __emit 0xa1
        __emit 0x4c
        __emit 0x6d
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x00
        __emit 0x89
        __emit 0x15
        __emit 0x98
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x11
        __emit 0xa3
        __emit 0x8c
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xa1
        __emit 0xf8
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0x68
        __emit 0x90
        __emit 0x05
        __emit 0x07
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0x88
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0x90
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0xf8
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0x84
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0x84
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0x00
        __emit 0x0f
        __emit 0x11
        __emit 0x01
        __emit 0xe8
        __emit 0xb7
        __emit 0x5d
        __emit 0x41
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xb8
        __emit 0x84
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xc3
    }
}

// ??0?$ConcreteModuleClass@V?$ModuleTag@$03$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVHemisphericalEmissionVelocityModule@2@VHemisphericalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@AAE@XZ
ConcreteModuleClass<ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::ConcreteModuleClass()
{
    const void *first = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6d44));
    void **slots = reinterpret_cast<void **>(this);
    const void *second = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6d40));
    slots[0] = (void *)0x01110880;
    slots[1] = (void *)second;
    slots[2] = (void *)first;
    slots[3] = *reinterpret_cast<void **>(0x012f64f8);
    *reinterpret_cast<void **>(0x012f64f8) = this;
    slots[0] = (void *)0x01110ef4;
}

// ??1?$ConcreteModuleClass@V?$ModuleTag@$03$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVHemisphericalEmissionVelocityModule@2@VHemisphericalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleClass<ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::~ConcreteModuleClass()
{
    *(const void **)this = (const void *)0x01110880;
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$03$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVHemisphericalEmissionVelocityModule@2@VHemisphericalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVHemisphericalEmissionVelocityModuleTemplate@2@PAVINI@@@Z
__declspec(naked) HemisphericalEmissionVelocityModuleTemplate *ConcreteModuleClass<ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::createTemplate(INI *ini) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x93
        __emit 0xb3
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x6a
        __emit 0x18
        __emit 0xe8
        __emit 0x22
        __emit 0x10
        __emit 0x2a
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x85
        __emit 0xf6
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1d
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x5c
        __emit 0xb0
        __emit 0xa3
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0xf8
        __emit 0x10
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0xf4
        __emit 0x10
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x08
        __emit 0xe0
        __emit 0x10
        __emit 0x11
        __emit 0x01
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xf6
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0x21
        __emit 0x24
        __emit 0xa4
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$03$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVHemisphericalEmissionVelocityModule@2@VHemisphericalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVHemisphericalEmissionVelocityModuleTemplate@2@XZ
__declspec(naked) HemisphericalEmissionVelocityModuleTemplate *ConcreteModuleClass<ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::createTemplate() const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xbb
        __emit 0xb3
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x6a
        __emit 0x18
        __emit 0xe8
        __emit 0x82
        __emit 0x0f
        __emit 0x2a
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x33
        __emit 0xc0
        __emit 0x3b
        __emit 0xf0
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x74
        __emit 0x1d
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0xbe
        __emit 0xaf
        __emit 0xa3
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0xf8
        __emit 0x10
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0xf4
        __emit 0x10
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x08
        __emit 0xe0
        __emit 0x10
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xc6
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc3
    }
}

// ?getClass@?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVHemisphericalEmissionVelocityModule@2@VHemisphericalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@UBEABV?$ConcreteModuleClass@V?$ModuleTag@$03$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVHemisphericalEmissionVelocityModule@2@VHemisphericalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@2@XZ
const ConcreteModuleClass<ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &ConcreteModuleTemplate<ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::getClass() const
{
    return ConcreteModuleClass<ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::getInstance();
}

// ?getInstance@?$ConcreteModuleClass@V?$ModuleTag@$03$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVHemisphericalEmissionVelocityModule@2@VHemisphericalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ
__declspec(naked) const ConcreteModuleClass<ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &ConcreteModuleClass<ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::getInstance()
{
    __asm {
        __emit 0x8a
        __emit 0x0d
        __emit 0x80
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xb8
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x84
        __emit 0xc8
        __emit 0x75
        __emit 0x53
        __emit 0x8b
        __emit 0x15
        __emit 0x80
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x0d
        __emit 0x40
        __emit 0x6d
        __emit 0x2f
        __emit 0x01
        __emit 0x0b
        __emit 0xd0
        __emit 0xa1
        __emit 0x44
        __emit 0x6d
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x00
        __emit 0x89
        __emit 0x15
        __emit 0x80
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x11
        __emit 0xa3
        __emit 0x74
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xa1
        __emit 0xf8
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0x68
        __emit 0xa0
        __emit 0x05
        __emit 0x07
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0x70
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0x78
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0xf8
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0x6c
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0x6c
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xf4
        __emit 0x0e
        __emit 0x11
        __emit 0x01
        __emit 0xe8
        __emit 0x67
        __emit 0x5f
        __emit 0x41
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xb8
        __emit 0x6c
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xc3
    }
}

// ??0?$ConcreteModuleClass@V?$ModuleTag@$03$E?OUTWARD_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?OUTWARD_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVOutwardEmissionVelocityModule@2@VOutwardEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@AAE@XZ
ConcreteModuleClass<ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::ConcreteModuleClass()
{
    const void *first = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6d54));
    void **slots = reinterpret_cast<void **>(this);
    const void *second = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6d50));
    slots[0] = (void *)0x01110880;
    slots[1] = (void *)second;
    slots[2] = (void *)first;
    slots[3] = *reinterpret_cast<void **>(0x012f64f8);
    *reinterpret_cast<void **>(0x012f64f8) = this;
    slots[0] = (void *)0x01110f0c;
}

// ??1?$ConcreteModuleClass@V?$ModuleTag@$03$E?OUTWARD_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?OUTWARD_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVOutwardEmissionVelocityModule@2@VOutwardEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleClass<ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::~ConcreteModuleClass()
{
    *(const void **)this = (const void *)0x01110880;
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$03$E?OUTWARD_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?OUTWARD_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVOutwardEmissionVelocityModule@2@VOutwardEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVOutwardEmissionVelocityModuleTemplate@2@PAVINI@@@Z
__declspec(naked) OutwardEmissionVelocityModuleTemplate *ConcreteModuleClass<ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::createTemplate(INI *ini) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x33
        __emit 0xb4
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x6a
        __emit 0x24
        __emit 0xe8
        __emit 0xc2
        __emit 0x0c
        __emit 0x2a
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x85
        __emit 0xf6
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1d
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x26
        __emit 0x7b
        __emit 0xa6
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0x50
        __emit 0x11
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x4c
        __emit 0x11
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x08
        __emit 0x38
        __emit 0x11
        __emit 0x11
        __emit 0x01
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xf6
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0x29
        __emit 0xe1
        __emit 0xa3
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$03$E?OUTWARD_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?OUTWARD_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVOutwardEmissionVelocityModule@2@VOutwardEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVOutwardEmissionVelocityModuleTemplate@2@XZ
__declspec(naked) OutwardEmissionVelocityModuleTemplate *ConcreteModuleClass<ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::createTemplate() const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x5b
        __emit 0xb4
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x6a
        __emit 0x24
        __emit 0xe8
        __emit 0x22
        __emit 0x0c
        __emit 0x2a
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x33
        __emit 0xc0
        __emit 0x3b
        __emit 0xf0
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x74
        __emit 0x1d
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x88
        __emit 0x7a
        __emit 0xa6
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0x50
        __emit 0x11
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x4c
        __emit 0x11
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x08
        __emit 0x38
        __emit 0x11
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xc6
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc3
    }
}

// ?getClass@?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?OUTWARD_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?OUTWARD_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVOutwardEmissionVelocityModule@2@VOutwardEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@UBEABV?$ConcreteModuleClass@V?$ModuleTag@$03$E?OUTWARD_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?OUTWARD_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVOutwardEmissionVelocityModule@2@VOutwardEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@2@XZ
const ConcreteModuleClass<ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &ConcreteModuleTemplate<ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::getClass() const
{
    return ConcreteModuleClass<ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::getInstance();
}

// ?getInstance@?$ConcreteModuleClass@V?$ModuleTag@$03$E?OUTWARD_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?OUTWARD_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVOutwardEmissionVelocityModule@2@VOutwardEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ
__declspec(naked) const ConcreteModuleClass<ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &ConcreteModuleClass<ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::getInstance()
{
    __asm {
        __emit 0x8a
        __emit 0x0d
        __emit 0xb0
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xb8
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x84
        __emit 0xc8
        __emit 0x75
        __emit 0x53
        __emit 0x8b
        __emit 0x15
        __emit 0xb0
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x0d
        __emit 0x50
        __emit 0x6d
        __emit 0x2f
        __emit 0x01
        __emit 0x0b
        __emit 0xd0
        __emit 0xa1
        __emit 0x54
        __emit 0x6d
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x00
        __emit 0x89
        __emit 0x15
        __emit 0xb0
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x11
        __emit 0xa3
        __emit 0xa4
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xa1
        __emit 0xf8
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0x68
        __emit 0x80
        __emit 0x05
        __emit 0x07
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0xa0
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0xa8
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0xf8
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0x9c
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0x9c
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0x0c
        __emit 0x0f
        __emit 0x11
        __emit 0x01
        __emit 0xe8
        __emit 0x07
        __emit 0x5c
        __emit 0x41
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xb8
        __emit 0x9c
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xc3
    }
}

// ??0?$ConcreteModuleClass@V?$ModuleTag@$03$E?SPHERICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?SPHERICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVSphericalEmissionVelocityModule@2@VSphericalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@AAE@XZ
ConcreteModuleClass<ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::ConcreteModuleClass()
{
    const void *first = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6d3c));
    void **slots = reinterpret_cast<void **>(this);
    const void *second = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6d38));
    slots[0] = (void *)0x01110880;
    slots[1] = (void *)second;
    slots[2] = (void *)first;
    slots[3] = *reinterpret_cast<void **>(0x012f64f8);
    *reinterpret_cast<void **>(0x012f64f8) = this;
    slots[0] = (void *)0x01110ee8;
}

// ??1?$ConcreteModuleClass@V?$ModuleTag@$03$E?SPHERICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?SPHERICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVSphericalEmissionVelocityModule@2@VSphericalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleClass<ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::~ConcreteModuleClass()
{
    *(const void **)this = (const void *)0x01110880;
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$03$E?SPHERICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?SPHERICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVSphericalEmissionVelocityModule@2@VSphericalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVSphericalEmissionVelocityModuleTemplate@2@PAVINI@@@Z
__declspec(naked) SphericalEmissionVelocityModuleTemplate *ConcreteModuleClass<ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::createTemplate(INI *ini) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x43
        __emit 0xb3
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x6a
        __emit 0x18
        __emit 0xe8
        __emit 0xd2
        __emit 0x11
        __emit 0x2a
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x85
        __emit 0xf6
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1d
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x0c
        __emit 0xb2
        __emit 0xa3
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0xcc
        __emit 0x10
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0xc8
        __emit 0x10
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x08
        __emit 0xb4
        __emit 0x10
        __emit 0x11
        __emit 0x01
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xf6
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0xd1
        __emit 0x25
        __emit 0xa4
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$03$E?SPHERICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?SPHERICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVSphericalEmissionVelocityModule@2@VSphericalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVSphericalEmissionVelocityModuleTemplate@2@XZ
__declspec(naked) SphericalEmissionVelocityModuleTemplate *ConcreteModuleClass<ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::createTemplate() const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x6b
        __emit 0xb3
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x6a
        __emit 0x18
        __emit 0xe8
        __emit 0x32
        __emit 0x11
        __emit 0x2a
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x33
        __emit 0xc0
        __emit 0x3b
        __emit 0xf0
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x74
        __emit 0x1d
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x6e
        __emit 0xb1
        __emit 0xa3
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0xcc
        __emit 0x10
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0xc8
        __emit 0x10
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x08
        __emit 0xb4
        __emit 0x10
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xc6
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc3
    }
}

// ?getClass@?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?SPHERICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?SPHERICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVSphericalEmissionVelocityModule@2@VSphericalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@UBEABV?$ConcreteModuleClass@V?$ModuleTag@$03$E?SPHERICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?SPHERICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVSphericalEmissionVelocityModule@2@VSphericalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@2@XZ
const ConcreteModuleClass<ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &ConcreteModuleTemplate<ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::getClass() const
{
    return ConcreteModuleClass<ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::getInstance();
}

// ?getInstance@?$ConcreteModuleClass@V?$ModuleTag@$03$E?SPHERICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?SPHERICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVSphericalEmissionVelocityModule@2@VSphericalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ
__declspec(naked) const ConcreteModuleClass<ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &ConcreteModuleClass<ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::getInstance()
{
    __asm {
        __emit 0x8a
        __emit 0x0d
        __emit 0x68
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xb8
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x84
        __emit 0xc8
        __emit 0x75
        __emit 0x53
        __emit 0x8b
        __emit 0x15
        __emit 0x68
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x0d
        __emit 0x38
        __emit 0x6d
        __emit 0x2f
        __emit 0x01
        __emit 0x0b
        __emit 0xd0
        __emit 0xa1
        __emit 0x3c
        __emit 0x6d
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x00
        __emit 0x89
        __emit 0x15
        __emit 0x68
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x11
        __emit 0xa3
        __emit 0x5c
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xa1
        __emit 0xf8
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0x68
        __emit 0xb0
        __emit 0x05
        __emit 0x07
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0x58
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0x60
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0xf8
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0x54
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0x54
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xe8
        __emit 0x0e
        __emit 0x11
        __emit 0x01
        __emit 0xe8
        __emit 0x17
        __emit 0x61
        __emit 0x41
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xb8
        __emit 0x54
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xc3
    }
}

// ??0?$ConcreteModuleClass@V?$ModuleTag@$04$E?BOX_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?BOX_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVBoxEmissionVolumeModule@2@VBoxEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@AAE@XZ
ConcreteModuleClass<ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::ConcreteModuleClass()
{
    const void *first = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6d6c));
    void **slots = reinterpret_cast<void **>(this);
    const void *second = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6d68));
    slots[0] = (void *)0x0111088c;
    slots[1] = (void *)second;
    slots[2] = (void *)first;
    slots[3] = *reinterpret_cast<void **>(0x012f64fc);
    *reinterpret_cast<void **>(0x012f64fc) = this;
    slots[0] = (void *)0x01110f24;
}

// ??1?$ConcreteModuleClass@V?$ModuleTag@$04$E?BOX_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?BOX_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVBoxEmissionVolumeModule@2@VBoxEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleClass<ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::~ConcreteModuleClass()
{
    *(const void **)this = (const void *)0x0111088c;
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$04$E?BOX_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?BOX_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVBoxEmissionVolumeModule@2@VBoxEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVBoxEmissionVolumeModuleTemplate@2@PAVINI@@@Z
__declspec(naked) BoxEmissionVolumeModuleTemplate *ConcreteModuleClass<ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::createTemplate(INI *ini) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xb8
        __emit 0xb4
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x6a
        __emit 0x1c
        __emit 0xe8
        __emit 0xf2
        __emit 0x07
        __emit 0x2a
        __emit 0x00
        __emit 0x33
        __emit 0xc9
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x3b
        __emit 0xc1
        __emit 0x74
        __emit 0x32
        __emit 0xc7
        __emit 0x40
        __emit 0x04
        __emit 0xac
        __emit 0xf9
        __emit 0x10
        __emit 0x01
        __emit 0x88
        __emit 0x48
        __emit 0x0c
        __emit 0xc7
        __emit 0x40
        __emit 0x08
        __emit 0xcc
        __emit 0x09
        __emit 0x11
        __emit 0x01
        __emit 0x89
        __emit 0x48
        __emit 0x10
        __emit 0x89
        __emit 0x48
        __emit 0x14
        __emit 0x89
        __emit 0x48
        __emit 0x18
        __emit 0xc7
        __emit 0x00
        __emit 0xd4
        __emit 0x11
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x40
        __emit 0x04
        __emit 0xd0
        __emit 0x11
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x40
        __emit 0x08
        __emit 0xbc
        __emit 0x11
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xf0
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xf6
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x89
        __emit 0x4c
        __emit 0x24
        __emit 0x10
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x0a
        __emit 0x62
        __emit 0xa4
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$04$E?BOX_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?BOX_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVBoxEmissionVolumeModule@2@VBoxEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVBoxEmissionVolumeModuleTemplate@2@XZ
BoxEmissionVolumeModuleTemplate *ConcreteModuleClass<ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::createTemplate() const
{
    BoxEmissionVolumeModuleTemplate *result =
        (BoxEmissionVolumeModuleTemplate *)::operator new(0x1c);
    if (result != 0) {
        *(volatile unsigned int *)((unsigned char *)result + 4) = 0x0110f9ac;
        *((volatile unsigned char *)result + 0x0c) = 0;
        *(volatile unsigned int *)((unsigned char *)result + 8) = 0x011109cc;
        *(volatile unsigned int *)((unsigned char *)result + 0x10) = 0;
        *(volatile unsigned int *)((unsigned char *)result + 0x14) = 0;
        *(volatile unsigned int *)((unsigned char *)result + 0x18) = 0;
        *(volatile unsigned int *)result = 0x011111d4;
        *(volatile unsigned int *)((unsigned char *)result + 4) = 0x011111d0;
        *(volatile unsigned int *)((unsigned char *)result + 8) = 0x011111bc;
        return result;
    }
    return 0;
}

// ?getClass@?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?BOX_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?BOX_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVBoxEmissionVolumeModule@2@VBoxEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@UBEABV?$ConcreteModuleClass@V?$ModuleTag@$04$E?BOX_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?BOX_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVBoxEmissionVolumeModule@2@VBoxEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@2@XZ
const ConcreteModuleClass<ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &ConcreteModuleTemplate<ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::getClass() const
{
    return ConcreteModuleClass<ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::getInstance();
}

// ?getInstance@?$ConcreteModuleClass@V?$ModuleTag@$04$E?BOX_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?BOX_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVBoxEmissionVolumeModule@2@VBoxEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ
__declspec(naked) const ConcreteModuleClass<ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &ConcreteModuleClass<ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::getInstance()
{
    __asm {
        __emit 0x8a
        __emit 0x0d
        __emit 0xf8
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xb8
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x84
        __emit 0xc8
        __emit 0x75
        __emit 0x53
        __emit 0x8b
        __emit 0x15
        __emit 0xf8
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x0d
        __emit 0x68
        __emit 0x6d
        __emit 0x2f
        __emit 0x01
        __emit 0x0b
        __emit 0xd0
        __emit 0xa1
        __emit 0x6c
        __emit 0x6d
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x00
        __emit 0x89
        __emit 0x15
        __emit 0xf8
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x11
        __emit 0xa3
        __emit 0xec
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xa1
        __emit 0xfc
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0x68
        __emit 0x50
        __emit 0x05
        __emit 0x07
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0xe8
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0xf0
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0xfc
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0xe4
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0xe4
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0x24
        __emit 0x0f
        __emit 0x11
        __emit 0x01
        __emit 0xe8
        __emit 0x37
        __emit 0x57
        __emit 0x41
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xb8
        __emit 0xe4
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xc3
    }
}

// ??0?$ConcreteModuleClass@V?$ModuleTag@$04$E?CYLINDER_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?CYLINDER_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVCylinderEmissionVolumeModule@2@VCylinderEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@AAE@XZ
ConcreteModuleClass<ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME, CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::ConcreteModuleClass()
{
    const void *first = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6d7c));
    void **self = reinterpret_cast<void **>(this);
    const void *second = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6d78));
    self[0] = (void *)0x0111088c;
    self[1] = (void *)second;
    self[2] = (void *)first;
    self[3] = *reinterpret_cast<void **>(0x012f64fc);
    *reinterpret_cast<void **>(0x012f64fc) = this;
    self[0] = (void *)0x01110f3c;
}

// ??1?$ConcreteModuleClass@V?$ModuleTag@$04$E?CYLINDER_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?CYLINDER_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVCylinderEmissionVolumeModule@2@VCylinderEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleClass<ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME, CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::~ConcreteModuleClass()
{
    *(const void **)this = (const void *)0x0111088c;
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$04$E?CYLINDER_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?CYLINDER_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVCylinderEmissionVolumeModule@2@VCylinderEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVCylinderEmissionVolumeModuleTemplate@2@PAVINI@@@Z
__declspec(naked) CylinderEmissionVolumeModuleTemplate *ConcreteModuleClass<ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME, CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::createTemplate(INI *ini) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xf8
        __emit 0xb4
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x6a
        __emit 0x24
        __emit 0xe8
        __emit 0xd2
        __emit 0x04
        __emit 0x2a
        __emit 0x00
        __emit 0x33
        __emit 0xc9
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x3b
        __emit 0xc1
        __emit 0x74
        __emit 0x38
        __emit 0xc7
        __emit 0x40
        __emit 0x04
        __emit 0xac
        __emit 0xf9
        __emit 0x10
        __emit 0x01
        __emit 0x88
        __emit 0x48
        __emit 0x0c
        __emit 0xc7
        __emit 0x40
        __emit 0x08
        __emit 0x4c
        __emit 0x0a
        __emit 0x11
        __emit 0x01
        __emit 0x89
        __emit 0x48
        __emit 0x10
        __emit 0x89
        __emit 0x48
        __emit 0x14
        __emit 0x89
        __emit 0x48
        __emit 0x18
        __emit 0x89
        __emit 0x48
        __emit 0x1c
        __emit 0x89
        __emit 0x48
        __emit 0x20
        __emit 0xc7
        __emit 0x00
        __emit 0x2c
        __emit 0x12
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x40
        __emit 0x04
        __emit 0x28
        __emit 0x12
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x40
        __emit 0x08
        __emit 0x14
        __emit 0x12
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xf0
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xf6
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x89
        __emit 0x4c
        __emit 0x24
        __emit 0x10
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x80
        __emit 0x30
        __emit 0xa5
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$04$E?CYLINDER_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?CYLINDER_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVCylinderEmissionVolumeModule@2@VCylinderEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVCylinderEmissionVolumeModuleTemplate@2@XZ
CylinderEmissionVolumeModuleTemplate *ConcreteModuleClass<ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME, CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::createTemplate() const
{
    CylinderEmissionVolumeModuleTemplate *result =
        (CylinderEmissionVolumeModuleTemplate *)::operator new(0x24);
    if (result != 0) {
        *(volatile unsigned int *)((unsigned char *)result + 4) = 0x0110f9ac;
        *((volatile unsigned char *)result + 0x0c) = 0;
        *(volatile unsigned int *)((unsigned char *)result + 8) = 0x01110a4c;
        *(volatile unsigned int *)((unsigned char *)result + 0x10) = 0;
        *(volatile unsigned int *)((unsigned char *)result + 0x14) = 0;
        *(volatile unsigned int *)((unsigned char *)result + 0x18) = 0;
        *(volatile unsigned int *)((unsigned char *)result + 0x1c) = 0;
        *(volatile unsigned int *)((unsigned char *)result + 0x20) = 0;
        *(volatile unsigned int *)result = 0x0111122c;
        *(volatile unsigned int *)((unsigned char *)result + 4) = 0x01111228;
        *(volatile unsigned int *)((unsigned char *)result + 8) = 0x01111214;
        return result;
    }
    return 0;
}

// ?getClass@?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?CYLINDER_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?CYLINDER_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVCylinderEmissionVolumeModule@2@VCylinderEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@UBEABV?$ConcreteModuleClass@V?$ModuleTag@$04$E?CYLINDER_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?CYLINDER_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVCylinderEmissionVolumeModule@2@VCylinderEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@2@XZ
const ConcreteModuleClass<ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME, CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &ConcreteModuleTemplate<ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME, CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::getClass() const
{
    return ConcreteModuleClass<ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME, CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::getInstance();
}

// ?getInstance@?$ConcreteModuleClass@V?$ModuleTag@$04$E?CYLINDER_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?CYLINDER_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVCylinderEmissionVolumeModule@2@VCylinderEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ
__declspec(naked) const ConcreteModuleClass<ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME, CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &ConcreteModuleClass<ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME, CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::getInstance()
{
    __asm {
        __emit 0x8a
        __emit 0x0d
        __emit 0x28
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0xb8
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x84
        __emit 0xc8
        __emit 0x75
        __emit 0x53
        __emit 0x8b
        __emit 0x15
        __emit 0x28
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x0d
        __emit 0x78
        __emit 0x6d
        __emit 0x2f
        __emit 0x01
        __emit 0x0b
        __emit 0xd0
        __emit 0xa1
        __emit 0x7c
        __emit 0x6d
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x00
        __emit 0x89
        __emit 0x15
        __emit 0x28
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x11
        __emit 0xa3
        __emit 0x1c
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0xa1
        __emit 0xfc
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0x68
        __emit 0x30
        __emit 0x05
        __emit 0x07
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0x18
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0x20
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0xfc
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0x14
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0x14
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0x3c
        __emit 0x0f
        __emit 0x11
        __emit 0x01
        __emit 0xe8
        __emit 0x17
        __emit 0x54
        __emit 0x41
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xb8
        __emit 0x14
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0xc3
    }
}

// ??0?$ConcreteModuleClass@V?$ModuleTag@$04$E?LIGHTNING_EMISSION_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIGHTNING_EMISSION_MODULE_NAME@2@3QBDBVLightningEmissionModule@2@VLightningEmissionModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@AAE@XZ
ConcreteModuleClass<ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::ConcreteModuleClass()
{
    const void *first = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6d84));
    void **slots = reinterpret_cast<void **>(this);
    const void *second = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6d80));
    slots[0] = (void *)0x0111088c;
    slots[1] = (void *)second;
    slots[2] = (void *)first;
    slots[3] = *reinterpret_cast<void **>(0x012f64fc);
    *reinterpret_cast<void **>(0x012f64fc) = this;
    slots[0] = (void *)0x01110f48;
}

// ??1?$ConcreteModuleClass@V?$ModuleTag@$04$E?LIGHTNING_EMISSION_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIGHTNING_EMISSION_MODULE_NAME@2@3QBDBVLightningEmissionModule@2@VLightningEmissionModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleClass<ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::~ConcreteModuleClass()
{
    *(const void **)this = (const void *)0x0111088c;
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$04$E?LIGHTNING_EMISSION_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIGHTNING_EMISSION_MODULE_NAME@2@3QBDBVLightningEmissionModule@2@VLightningEmissionModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVLightningEmissionModuleTemplate@2@PAVINI@@@Z
__declspec(naked) LightningEmissionModuleTemplate *ConcreteModuleClass<ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::createTemplate(INI *ini) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x23
        __emit 0xb5
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x68
        __emit 0x94
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0x2f
        __emit 0x03
        __emit 0x2a
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x85
        __emit 0xf6
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1d
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x1c
        __emit 0xb0
        __emit 0xa2
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0x58
        __emit 0x12
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x54
        __emit 0x12
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x08
        __emit 0x40
        __emit 0x12
        __emit 0x11
        __emit 0x01
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xf6
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0xb9
        __emit 0x43
        __emit 0xa6
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$04$E?LIGHTNING_EMISSION_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIGHTNING_EMISSION_MODULE_NAME@2@3QBDBVLightningEmissionModule@2@VLightningEmissionModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVLightningEmissionModuleTemplate@2@XZ
__declspec(naked) LightningEmissionModuleTemplate *ConcreteModuleClass<ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::createTemplate() const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x4b
        __emit 0xb5
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x68
        __emit 0x94
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0x7f
        __emit 0x02
        __emit 0x2a
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x33
        __emit 0xc0
        __emit 0x3b
        __emit 0xf0
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x74
        __emit 0x1d
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x6e
        __emit 0xaf
        __emit 0xa2
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0x58
        __emit 0x12
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x54
        __emit 0x12
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x08
        __emit 0x40
        __emit 0x12
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xc6
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc3
    }
}

// ?getClass@?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?LIGHTNING_EMISSION_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIGHTNING_EMISSION_MODULE_NAME@2@3QBDBVLightningEmissionModule@2@VLightningEmissionModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@UBEABV?$ConcreteModuleClass@V?$ModuleTag@$04$E?LIGHTNING_EMISSION_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIGHTNING_EMISSION_MODULE_NAME@2@3QBDBVLightningEmissionModule@2@VLightningEmissionModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@2@XZ
const ConcreteModuleClass<ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &ConcreteModuleTemplate<ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::getClass() const
{
    return ConcreteModuleClass<ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::getInstance();
}

// ?getInstance@?$ConcreteModuleClass@V?$ModuleTag@$04$E?LIGHTNING_EMISSION_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIGHTNING_EMISSION_MODULE_NAME@2@3QBDBVLightningEmissionModule@2@VLightningEmissionModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ
__declspec(naked) const ConcreteModuleClass<ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &ConcreteModuleClass<ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::getInstance()
{
    __asm {
        __emit 0x8a
        __emit 0x0d
        __emit 0x40
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0xb8
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x84
        __emit 0xc8
        __emit 0x75
        __emit 0x53
        __emit 0x8b
        __emit 0x15
        __emit 0x40
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x0d
        __emit 0x80
        __emit 0x6d
        __emit 0x2f
        __emit 0x01
        __emit 0x0b
        __emit 0xd0
        __emit 0xa1
        __emit 0x84
        __emit 0x6d
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x00
        __emit 0x89
        __emit 0x15
        __emit 0x40
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x11
        __emit 0xa3
        __emit 0x34
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0xa1
        __emit 0xfc
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0x68
        __emit 0x20
        __emit 0x05
        __emit 0x07
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0x30
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0x38
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0xfc
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0x2c
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0x2c
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0x48
        __emit 0x0f
        __emit 0x11
        __emit 0x01
        __emit 0xe8
        __emit 0x77
        __emit 0x52
        __emit 0x41
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xb8
        __emit 0x2c
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0xc3
    }
}

// ??0?$ConcreteModuleClass@V?$ModuleTag@$04$E?LINE_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?LINE_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVLineEmissionVolumeModule@2@VLineEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@AAE@XZ
ConcreteModuleClass<ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::ConcreteModuleClass()
{
    const void *first = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6d64));
    void **slots = reinterpret_cast<void **>(this);
    const void *second = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6d60));
    slots[0] = (void *)0x0111088c;
    slots[1] = (void *)second;
    slots[2] = (void *)first;
    slots[3] = *reinterpret_cast<void **>(0x012f64fc);
    *reinterpret_cast<void **>(0x012f64fc) = this;
    slots[0] = (void *)0x01110f18;
}

// ??1?$ConcreteModuleClass@V?$ModuleTag@$04$E?LINE_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?LINE_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVLineEmissionVolumeModule@2@VLineEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleClass<ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::~ConcreteModuleClass()
{
    *(const void **)this = (const void *)0x0111088c;
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$04$E?LINE_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?LINE_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVLineEmissionVolumeModule@2@VLineEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVLineEmissionVolumeModuleTemplate@2@PAVINI@@@Z
__declspec(naked) LineEmissionVolumeModuleTemplate *ConcreteModuleClass<ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::createTemplate(INI *ini) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x98
        __emit 0xb4
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x6a
        __emit 0x28
        __emit 0xe8
        __emit 0x92
        __emit 0x09
        __emit 0x2a
        __emit 0x00
        __emit 0x33
        __emit 0xc9
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x3b
        __emit 0xc1
        __emit 0x74
        __emit 0x3b
        __emit 0xc7
        __emit 0x40
        __emit 0x04
        __emit 0xac
        __emit 0xf9
        __emit 0x10
        __emit 0x01
        __emit 0x88
        __emit 0x48
        __emit 0x0c
        __emit 0xc7
        __emit 0x40
        __emit 0x08
        __emit 0x8c
        __emit 0x09
        __emit 0x11
        __emit 0x01
        __emit 0x89
        __emit 0x48
        __emit 0x10
        __emit 0x89
        __emit 0x48
        __emit 0x14
        __emit 0x89
        __emit 0x48
        __emit 0x18
        __emit 0x89
        __emit 0x48
        __emit 0x1c
        __emit 0x89
        __emit 0x48
        __emit 0x20
        __emit 0x89
        __emit 0x48
        __emit 0x24
        __emit 0xc7
        __emit 0x00
        __emit 0xa8
        __emit 0x11
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x40
        __emit 0x04
        __emit 0xa4
        __emit 0x11
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x40
        __emit 0x08
        __emit 0x90
        __emit 0x11
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xf0
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xf6
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x89
        __emit 0x4c
        __emit 0x24
        __emit 0x10
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x0f
        __emit 0x22
        __emit 0xa5
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$04$E?LINE_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?LINE_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVLineEmissionVolumeModule@2@VLineEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVLineEmissionVolumeModuleTemplate@2@XZ
LineEmissionVolumeModuleTemplate *ConcreteModuleClass<ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::createTemplate() const
{
    LineEmissionVolumeModuleTemplate *result =
        (LineEmissionVolumeModuleTemplate *)::operator new(0x28);
    if (result != 0) {
        *(volatile unsigned int *)((unsigned char *)result + 4) = 0x0110f9ac;
        *((volatile unsigned char *)result + 0x0c) = 0;
        *(volatile unsigned int *)((unsigned char *)result + 8) = 0x0111098c;
        *(volatile unsigned int *)((unsigned char *)result + 0x10) = 0;
        *(volatile unsigned int *)((unsigned char *)result + 0x14) = 0;
        *(volatile unsigned int *)((unsigned char *)result + 0x18) = 0;
        *(volatile unsigned int *)((unsigned char *)result + 0x1c) = 0;
        *(volatile unsigned int *)((unsigned char *)result + 0x20) = 0;
        *(volatile unsigned int *)((unsigned char *)result + 0x24) = 0;
        *(volatile unsigned int *)result = 0x011111a8;
        *(volatile unsigned int *)((unsigned char *)result + 4) = 0x011111a4;
        *(volatile unsigned int *)((unsigned char *)result + 8) = 0x01111190;
        return result;
    }
    return 0;
}

// ?getClass@?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?LINE_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?LINE_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVLineEmissionVolumeModule@2@VLineEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@UBEABV?$ConcreteModuleClass@V?$ModuleTag@$04$E?LINE_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?LINE_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVLineEmissionVolumeModule@2@VLineEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@2@XZ
const ConcreteModuleClass<ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &ConcreteModuleTemplate<ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::getClass() const
{
    return ConcreteModuleClass<ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::getInstance();
}

// ?getInstance@?$ConcreteModuleClass@V?$ModuleTag@$04$E?LINE_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?LINE_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVLineEmissionVolumeModule@2@VLineEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ
__declspec(naked) const ConcreteModuleClass<ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &ConcreteModuleClass<ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::getInstance()
{
    __asm {
        __emit 0x8a
        __emit 0x0d
        __emit 0xe0
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xb8
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x84
        __emit 0xc8
        __emit 0x75
        __emit 0x53
        __emit 0x8b
        __emit 0x15
        __emit 0xe0
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x0d
        __emit 0x60
        __emit 0x6d
        __emit 0x2f
        __emit 0x01
        __emit 0x0b
        __emit 0xd0
        __emit 0xa1
        __emit 0x64
        __emit 0x6d
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x00
        __emit 0x89
        __emit 0x15
        __emit 0xe0
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x11
        __emit 0xa3
        __emit 0xd4
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xa1
        __emit 0xfc
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0x68
        __emit 0x60
        __emit 0x05
        __emit 0x07
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0xd0
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0xd8
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0xfc
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0xcc
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0xcc
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0x18
        __emit 0x0f
        __emit 0x11
        __emit 0x01
        __emit 0xe8
        __emit 0xd7
        __emit 0x58
        __emit 0x41
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xb8
        __emit 0xcc
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xc3
    }
}

// ??0?$ConcreteModuleClass@V?$ModuleTag@$04$E?SPHERE_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?SPHERE_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVSphereEmissionVolumeModule@2@VSphereEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@AAE@XZ
ConcreteModuleClass<ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY, SPHERE_EMISSION_VOLUME_MODULE_NAME, SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::ConcreteModuleClass()
{
    const void *first = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6d74));
    void **self = reinterpret_cast<void **>(this);
    const void *second = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6d70));
    self[0] = (void *)0x0111088c;
    self[1] = (void *)second;
    self[2] = (void *)first;
    self[3] = *reinterpret_cast<void **>(0x012f64fc);
    *reinterpret_cast<void **>(0x012f64fc) = this;
    self[0] = (void *)0x01110f30;
}

// ??1?$ConcreteModuleClass@V?$ModuleTag@$04$E?SPHERE_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?SPHERE_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVSphereEmissionVolumeModule@2@VSphereEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleClass<ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY, SPHERE_EMISSION_VOLUME_MODULE_NAME, SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::~ConcreteModuleClass()
{
    *(const void **)this = (const void *)0x0111088c;
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$04$E?SPHERE_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?SPHERE_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVSphereEmissionVolumeModule@2@VSphereEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVSphereEmissionVolumeModuleTemplate@2@PAVINI@@@Z
__declspec(naked) SphereEmissionVolumeModuleTemplate *ConcreteModuleClass<ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY, SPHERE_EMISSION_VOLUME_MODULE_NAME, SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::createTemplate(INI *ini) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xd8
        __emit 0xb4
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x6a
        __emit 0x14
        __emit 0xe8
        __emit 0x52
        __emit 0x06
        __emit 0x2a
        __emit 0x00
        __emit 0x33
        __emit 0xc9
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x3b
        __emit 0xc1
        __emit 0x74
        __emit 0x2c
        __emit 0xc7
        __emit 0x40
        __emit 0x04
        __emit 0xac
        __emit 0xf9
        __emit 0x10
        __emit 0x01
        __emit 0x88
        __emit 0x48
        __emit 0x0c
        __emit 0xc7
        __emit 0x40
        __emit 0x08
        __emit 0x0c
        __emit 0x0a
        __emit 0x11
        __emit 0x01
        __emit 0x89
        __emit 0x48
        __emit 0x10
        __emit 0xc7
        __emit 0x00
        __emit 0x00
        __emit 0x12
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x40
        __emit 0x04
        __emit 0xfc
        __emit 0x11
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x40
        __emit 0x08
        __emit 0xe8
        __emit 0x11
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xf0
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xf6
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x89
        __emit 0x4c
        __emit 0x24
        __emit 0x10
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x1e
        __emit 0x2f
        __emit 0xa5
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$04$E?SPHERE_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?SPHERE_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVSphereEmissionVolumeModule@2@VSphereEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVSphereEmissionVolumeModuleTemplate@2@XZ
SphereEmissionVolumeModuleTemplate *ConcreteModuleClass<ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY, SPHERE_EMISSION_VOLUME_MODULE_NAME, SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::createTemplate() const
{
    SphereEmissionVolumeModuleTemplate *result =
        (SphereEmissionVolumeModuleTemplate *)::operator new(0x14);
    if (result != 0) {
        *(volatile unsigned int *)((unsigned char *)result + 4) = 0x0110f9ac;
        *((volatile unsigned char *)result + 0x0c) = 0;
        *(volatile unsigned int *)((unsigned char *)result + 8) = 0x01110a0c;
        *(volatile unsigned int *)((unsigned char *)result + 0x10) = 0;
        *(volatile unsigned int *)result = 0x01111200;
        *(volatile unsigned int *)((unsigned char *)result + 4) = 0x011111fc;
        *(volatile unsigned int *)((unsigned char *)result + 8) = 0x011111e8;
        return result;
    }
    return 0;
}

// ?getClass@?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?SPHERE_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?SPHERE_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVSphereEmissionVolumeModule@2@VSphereEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@UBEABV?$ConcreteModuleClass@V?$ModuleTag@$04$E?SPHERE_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?SPHERE_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVSphereEmissionVolumeModule@2@VSphereEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@2@XZ
const ConcreteModuleClass<ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY, SPHERE_EMISSION_VOLUME_MODULE_NAME, SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &ConcreteModuleTemplate<ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY, SPHERE_EMISSION_VOLUME_MODULE_NAME, SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::getClass() const
{
    return ConcreteModuleClass<ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY, SPHERE_EMISSION_VOLUME_MODULE_NAME, SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::getInstance();
}

// ?getInstance@?$ConcreteModuleClass@V?$ModuleTag@$04$E?SPHERE_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?SPHERE_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVSphereEmissionVolumeModule@2@VSphereEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ
__declspec(naked) const ConcreteModuleClass<ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY, SPHERE_EMISSION_VOLUME_MODULE_NAME, SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &ConcreteModuleClass<ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY, SPHERE_EMISSION_VOLUME_MODULE_NAME, SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::getInstance()
{
    __asm {
        __emit 0x8a
        __emit 0x0d
        __emit 0x10
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0xb8
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x84
        __emit 0xc8
        __emit 0x75
        __emit 0x53
        __emit 0x8b
        __emit 0x15
        __emit 0x10
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x0d
        __emit 0x70
        __emit 0x6d
        __emit 0x2f
        __emit 0x01
        __emit 0x0b
        __emit 0xd0
        __emit 0xa1
        __emit 0x74
        __emit 0x6d
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x00
        __emit 0x89
        __emit 0x15
        __emit 0x10
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x11
        __emit 0xa3
        __emit 0x04
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0xa1
        __emit 0xfc
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0x68
        __emit 0x40
        __emit 0x05
        __emit 0x07
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0x00
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0x08
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0xfc
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0xfc
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0xfc
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0x30
        __emit 0x0f
        __emit 0x11
        __emit 0x01
        __emit 0xe8
        __emit 0x97
        __emit 0x55
        __emit 0x41
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xb8
        __emit 0xfc
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xc3
    }
}

// ??0?$ConcreteModuleClass@V?$ModuleTag@$05$E?BUTTERFLY_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?BUTTERFLY_DRAW_MODULE_NAME@2@3QBDBVButterflyDrawModule@2@VButterflyDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@AAE@XZ
ConcreteModuleClass<ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME, ButterflyDrawModule, ButterflyDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::ConcreteModuleClass()
{
    const void *first = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6cb4));
    void **slots = reinterpret_cast<void **>(this);
    const void *second = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6cb0));
    slots[0] = (void *)0x01110820;
    slots[1] = (void *)second;
    slots[2] = (void *)first;
    slots[3] = *reinterpret_cast<void **>(0x012f6500);
    *reinterpret_cast<void **>(0x012f6500) = this;
    slots[0] = (void *)0x01110dd0;
}

// ??1?$ConcreteModuleClass@V?$ModuleTag@$05$E?BUTTERFLY_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?BUTTERFLY_DRAW_MODULE_NAME@2@3QBDBVButterflyDrawModule@2@VButterflyDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleClass<ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME, ButterflyDrawModule, ButterflyDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::~ConcreteModuleClass()
{
    *(const void **)this = (const void *)0x01110820;
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$05$E?BUTTERFLY_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?BUTTERFLY_DRAW_MODULE_NAME@2@3QBDBVButterflyDrawModule@2@VButterflyDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVButterflyDrawModuleTemplate@2@PAVINI@@@Z
__declspec(naked) ButterflyDrawModuleTemplate *ConcreteModuleClass<ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME, ButterflyDrawModule, ButterflyDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::createTemplate(INI *ini) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xa3
        __emit 0xb0
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x6a
        __emit 0x0c
        __emit 0xe8
        __emit 0xb2
        __emit 0x2b
        __emit 0x2a
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x85
        __emit 0xf6
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1d
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x57
        __emit 0xf5
        __emit 0xa5
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0x90
        __emit 0x0e
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x8c
        __emit 0x0e
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x08
        __emit 0x78
        __emit 0x0e
        __emit 0x11
        __emit 0x01
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xf6
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0x54
        __emit 0x45
        __emit 0xa6
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$05$E?BUTTERFLY_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?BUTTERFLY_DRAW_MODULE_NAME@2@3QBDBVButterflyDrawModule@2@VButterflyDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVButterflyDrawModuleTemplate@2@XZ
__declspec(naked) ButterflyDrawModuleTemplate *ConcreteModuleClass<ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME, ButterflyDrawModule, ButterflyDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::createTemplate() const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xcb
        __emit 0xb0
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x6a
        __emit 0x0c
        __emit 0xe8
        __emit 0x12
        __emit 0x2b
        __emit 0x2a
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x33
        __emit 0xc0
        __emit 0x3b
        __emit 0xf0
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x74
        __emit 0x1d
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0xb9
        __emit 0xf4
        __emit 0xa5
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0x90
        __emit 0x0e
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x8c
        __emit 0x0e
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x08
        __emit 0x78
        __emit 0x0e
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xc6
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc3
    }
}

// ?getClass@?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?BUTTERFLY_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?BUTTERFLY_DRAW_MODULE_NAME@2@3QBDBVButterflyDrawModule@2@VButterflyDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@UBEABV?$ConcreteModuleClass@V?$ModuleTag@$05$E?BUTTERFLY_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?BUTTERFLY_DRAW_MODULE_NAME@2@3QBDBVButterflyDrawModule@2@VButterflyDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@2@XZ
const ConcreteModuleClass<ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME, ButterflyDrawModule, ButterflyDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &ConcreteModuleTemplate<ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME, ButterflyDrawModule, ButterflyDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::getClass() const
{
    return ConcreteModuleClass<ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME, ButterflyDrawModule, ButterflyDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::getInstance();
}

// ?getInstance@?$ConcreteModuleClass@V?$ModuleTag@$05$E?BUTTERFLY_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?BUTTERFLY_DRAW_MODULE_NAME@2@3QBDBVButterflyDrawModule@2@VButterflyDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ
__declspec(naked) const ConcreteModuleClass<ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME, ButterflyDrawModule, ButterflyDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &ConcreteModuleClass<ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME, ButterflyDrawModule, ButterflyDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::getInstance()
{
    __asm {
        __emit 0x8a
        __emit 0x0d
        __emit 0xd0
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xb8
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x84
        __emit 0xc8
        __emit 0x75
        __emit 0x53
        __emit 0x8b
        __emit 0x15
        __emit 0xd0
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x0d
        __emit 0xb0
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0x0b
        __emit 0xd0
        __emit 0xa1
        __emit 0xb4
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x00
        __emit 0x89
        __emit 0x15
        __emit 0xd0
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x11
        __emit 0xa3
        __emit 0xc4
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xa1
        __emit 0x00
        __emit 0x65
        __emit 0x2f
        __emit 0x01
        __emit 0x68
        __emit 0xc0
        __emit 0x04
        __emit 0x07
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0xc0
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0xc8
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0x00
        __emit 0x65
        __emit 0x2f
        __emit 0x01
        __emit 0xbc
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0xbc
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xd0
        __emit 0x0d
        __emit 0x11
        __emit 0x01
        __emit 0xe8
        __emit 0xf7
        __emit 0x7a
        __emit 0x41
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xb8
        __emit 0xbc
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xc3
    }
}

// ??0?$ConcreteModuleClass@V?$ModuleTag@$05$E?LIGHTNING_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIGHTNING_DRAW_MODULE_NAME@2@3QBDBVLightningDrawModule@2@VLightningDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@AAE@XZ
ConcreteModuleClass<ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule, LightningDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::ConcreteModuleClass()
{
    const void *first = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6cc4));
    void **self = reinterpret_cast<void **>(this);
    const void *second = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6cc0));
    self[0] = (void *)0x01110820;
    self[1] = (void *)second;
    self[2] = (void *)first;
    self[3] = *reinterpret_cast<void **>(0x012f6500);
    *reinterpret_cast<void **>(0x012f6500) = this;
    self[0] = (void *)0x01110de8;
}

// ??1?$ConcreteModuleClass@V?$ModuleTag@$05$E?LIGHTNING_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIGHTNING_DRAW_MODULE_NAME@2@3QBDBVLightningDrawModule@2@VLightningDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleClass<ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule, LightningDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::~ConcreteModuleClass()
{
    *(const void **)this = (const void *)0x01110820;
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$05$E?LIGHTNING_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIGHTNING_DRAW_MODULE_NAME@2@3QBDBVLightningDrawModule@2@VLightningDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVLightningDrawModuleTemplate@2@PAVINI@@@Z
__declspec(naked) LightningDrawModuleTemplate *ConcreteModuleClass<ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule, LightningDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::createTemplate(INI *ini) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xf3
        __emit 0xb0
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x6a
        __emit 0x38
        __emit 0xe8
        __emit 0x72
        __emit 0x29
        __emit 0x2a
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x85
        __emit 0xf6
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1d
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0xd0
        __emit 0xbc
        __emit 0xa5
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0xbc
        __emit 0x0e
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0xb8
        __emit 0x0e
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x08
        __emit 0xa4
        __emit 0x0e
        __emit 0x11
        __emit 0x01
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xf6
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0xb9
        __emit 0xd5
        __emit 0xa5
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$05$E?LIGHTNING_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIGHTNING_DRAW_MODULE_NAME@2@3QBDBVLightningDrawModule@2@VLightningDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVLightningDrawModuleTemplate@2@XZ
__declspec(naked) LightningDrawModuleTemplate *ConcreteModuleClass<ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule, LightningDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::createTemplate() const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x1b
        __emit 0xb1
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x6a
        __emit 0x38
        __emit 0xe8
        __emit 0xd2
        __emit 0x28
        __emit 0x2a
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x33
        __emit 0xc0
        __emit 0x3b
        __emit 0xf0
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x74
        __emit 0x1d
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x32
        __emit 0xbc
        __emit 0xa5
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0xbc
        __emit 0x0e
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0xb8
        __emit 0x0e
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x08
        __emit 0xa4
        __emit 0x0e
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xc6
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc3
    }
}

// ?getClass@?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?LIGHTNING_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIGHTNING_DRAW_MODULE_NAME@2@3QBDBVLightningDrawModule@2@VLightningDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@UBEABV?$ConcreteModuleClass@V?$ModuleTag@$05$E?LIGHTNING_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIGHTNING_DRAW_MODULE_NAME@2@3QBDBVLightningDrawModule@2@VLightningDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@2@XZ
const ConcreteModuleClass<ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule, LightningDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &ConcreteModuleTemplate<ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule, LightningDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::getClass() const
{
    return ConcreteModuleClass<ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule, LightningDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::getInstance();
}

// ?getInstance@?$ConcreteModuleClass@V?$ModuleTag@$05$E?LIGHTNING_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIGHTNING_DRAW_MODULE_NAME@2@3QBDBVLightningDrawModule@2@VLightningDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ
__declspec(naked) const ConcreteModuleClass<ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule, LightningDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &ConcreteModuleClass<ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule, LightningDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::getInstance()
{
    __asm {
        __emit 0x8a
        __emit 0x0d
        __emit 0x00
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xb8
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x84
        __emit 0xc8
        __emit 0x75
        __emit 0x53
        __emit 0x8b
        __emit 0x15
        __emit 0x00
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x0d
        __emit 0xc0
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0x0b
        __emit 0xd0
        __emit 0xa1
        __emit 0xc4
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x00
        __emit 0x89
        __emit 0x15
        __emit 0x00
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x11
        __emit 0xa3
        __emit 0xf4
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xa1
        __emit 0x00
        __emit 0x65
        __emit 0x2f
        __emit 0x01
        __emit 0x68
        __emit 0xa0
        __emit 0x04
        __emit 0x07
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0xf0
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0xf8
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0x00
        __emit 0x65
        __emit 0x2f
        __emit 0x01
        __emit 0xec
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0xec
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xe8
        __emit 0x0d
        __emit 0x11
        __emit 0x01
        __emit 0xe8
        __emit 0xb7
        __emit 0x78
        __emit 0x41
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xb8
        __emit 0xec
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xc3
    }
}

// ??0?$ConcreteModuleClass@V?$ModuleTag@$05$E?QUAD_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?QUAD_DRAW_MODULE_NAME@2@3QBDBVQuadDrawModule@2@VQuadDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@AAE@XZ
ConcreteModuleClass<ModuleTag<6, QUAD_DRAW_MODULE_KEY, QUAD_DRAW_MODULE_NAME, QuadDrawModule, QuadDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::ConcreteModuleClass()
{
    const void *first = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6cac));
    void **slots = reinterpret_cast<void **>(this);
    const void *second = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6ca8));
    slots[0] = (void *)0x01110820;
    slots[1] = (void *)second;
    slots[2] = (void *)first;
    slots[3] = *reinterpret_cast<void **>(0x012f6500);
    *reinterpret_cast<void **>(0x012f6500) = this;
    slots[0] = (void *)0x01110dc4;
}

// ??1?$ConcreteModuleClass@V?$ModuleTag@$05$E?QUAD_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?QUAD_DRAW_MODULE_NAME@2@3QBDBVQuadDrawModule@2@VQuadDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleClass<ModuleTag<6, QUAD_DRAW_MODULE_KEY, QUAD_DRAW_MODULE_NAME, QuadDrawModule, QuadDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::~ConcreteModuleClass()
{
    *(const void **)this = (const void *)0x01110820;
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$05$E?QUAD_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?QUAD_DRAW_MODULE_NAME@2@3QBDBVQuadDrawModule@2@VQuadDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVQuadDrawModuleTemplate@2@PAVINI@@@Z
__declspec(naked) QuadDrawModuleTemplate *ConcreteModuleClass<ModuleTag<6, QUAD_DRAW_MODULE_KEY, QUAD_DRAW_MODULE_NAME, QuadDrawModule, QuadDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::createTemplate(INI *ini) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x53
        __emit 0xb0
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x6a
        __emit 0x0c
        __emit 0xe8
        __emit 0x62
        __emit 0x2d
        __emit 0x2a
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x85
        __emit 0xf6
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1d
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x8e
        __emit 0xe0
        __emit 0xa3
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0x64
        __emit 0x0e
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x60
        __emit 0x0e
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x08
        __emit 0x4c
        __emit 0x0e
        __emit 0x11
        __emit 0x01
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xf6
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0xde
        __emit 0x49
        __emit 0xa6
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$05$E?QUAD_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?QUAD_DRAW_MODULE_NAME@2@3QBDBVQuadDrawModule@2@VQuadDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVQuadDrawModuleTemplate@2@XZ
QuadDrawModuleTemplate *ConcreteModuleClass<ModuleTag<6, QUAD_DRAW_MODULE_KEY, QUAD_DRAW_MODULE_NAME, QuadDrawModule, QuadDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::createTemplate() const
{
    return (QuadDrawModuleTemplate *)new QuadDrawTemplateFactoryShim;
}

// ?getClass@?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?QUAD_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?QUAD_DRAW_MODULE_NAME@2@3QBDBVQuadDrawModule@2@VQuadDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@UBEABV?$ConcreteModuleClass@V?$ModuleTag@$05$E?QUAD_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?QUAD_DRAW_MODULE_NAME@2@3QBDBVQuadDrawModule@2@VQuadDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@2@XZ
const ConcreteModuleClass<ModuleTag<6, QUAD_DRAW_MODULE_KEY, QUAD_DRAW_MODULE_NAME, QuadDrawModule, QuadDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &ConcreteModuleTemplate<ModuleTag<6, QUAD_DRAW_MODULE_KEY, QUAD_DRAW_MODULE_NAME, QuadDrawModule, QuadDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::getClass() const
{
    return ConcreteModuleClass<ModuleTag<6, QUAD_DRAW_MODULE_KEY, QUAD_DRAW_MODULE_NAME, QuadDrawModule, QuadDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::getInstance();
}

// ?getInstance@?$ConcreteModuleClass@V?$ModuleTag@$05$E?QUAD_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?QUAD_DRAW_MODULE_NAME@2@3QBDBVQuadDrawModule@2@VQuadDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ
__declspec(naked) const ConcreteModuleClass<ModuleTag<6, QUAD_DRAW_MODULE_KEY, QUAD_DRAW_MODULE_NAME, QuadDrawModule, QuadDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &ConcreteModuleClass<ModuleTag<6, QUAD_DRAW_MODULE_KEY, QUAD_DRAW_MODULE_NAME, QuadDrawModule, QuadDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::getInstance()
{
    __asm {
        __emit 0x8a
        __emit 0x0d
        __emit 0xb8
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xb8
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x84
        __emit 0xc8
        __emit 0x75
        __emit 0x53
        __emit 0x8b
        __emit 0x15
        __emit 0xb8
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x0d
        __emit 0xa8
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0x0b
        __emit 0xd0
        __emit 0xa1
        __emit 0xac
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x00
        __emit 0x89
        __emit 0x15
        __emit 0xb8
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x11
        __emit 0xa3
        __emit 0xac
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xa1
        __emit 0x00
        __emit 0x65
        __emit 0x2f
        __emit 0x01
        __emit 0x68
        __emit 0xd0
        __emit 0x04
        __emit 0x07
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0xa8
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0xb0
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0x00
        __emit 0x65
        __emit 0x2f
        __emit 0x01
        __emit 0xa4
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0xa4
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xc4
        __emit 0x0d
        __emit 0x11
        __emit 0x01
        __emit 0xe8
        __emit 0xa7
        __emit 0x7c
        __emit 0x41
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xb8
        __emit 0xa4
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xc3
    }
}

// ??0?$ConcreteModuleClass@V?$ModuleTag@$05$E?RENDEROBJECT_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_DRAW_MODULE_NAME@2@3QBDBVRenderObjectDrawModule@2@VRenderObjectDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@AAE@XZ
ConcreteModuleClass<ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY, RENDEROBJECT_DRAW_MODULE_NAME, RenderObjectDrawModule, RenderObjectDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::ConcreteModuleClass()
{
    const void *first = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6cbc));
    void **self = reinterpret_cast<void **>(this);
    const void *second = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6cb8));
    self[0] = (void *)0x01110820;
    self[1] = (void *)second;
    self[2] = (void *)first;
    self[3] = *reinterpret_cast<void **>(0x012f6500);
    *reinterpret_cast<void **>(0x012f6500) = this;
    self[0] = (void *)0x01110ddc;
}

// ??1?$ConcreteModuleClass@V?$ModuleTag@$05$E?RENDEROBJECT_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_DRAW_MODULE_NAME@2@3QBDBVRenderObjectDrawModule@2@VRenderObjectDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleClass<ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY, RENDEROBJECT_DRAW_MODULE_NAME, RenderObjectDrawModule, RenderObjectDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::~ConcreteModuleClass()
{
    *(const void **)this = (const void *)0x01110820;
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$05$E?RENDEROBJECT_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_DRAW_MODULE_NAME@2@3QBDBVRenderObjectDrawModule@2@VRenderObjectDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVRenderObjectDrawModuleTemplate@2@PAVINI@@@Z
__declspec(naked) RenderObjectDrawModuleTemplate *ConcreteModuleClass<ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY, RENDEROBJECT_DRAW_MODULE_NAME, RenderObjectDrawModule, RenderObjectDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::createTemplate(INI *ini) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x63
        __emit 0xb6
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x6a
        __emit 0x48
        __emit 0xe8
        __emit 0x62
        __emit 0xe0
        __emit 0x29
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x85
        __emit 0xf6
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1d
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x2c
        __emit 0xf9
        __emit 0xa4
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0x98
        __emit 0x13
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x94
        __emit 0x13
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x08
        __emit 0x80
        __emit 0x13
        __emit 0x11
        __emit 0x01
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xf6
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0xf9
        __emit 0x37
        __emit 0xa5
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$05$E?RENDEROBJECT_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_DRAW_MODULE_NAME@2@3QBDBVRenderObjectDrawModule@2@VRenderObjectDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVRenderObjectDrawModuleTemplate@2@XZ
RenderObjectDrawModuleTemplate *ConcreteModuleClass<ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY, RENDEROBJECT_DRAW_MODULE_NAME, RenderObjectDrawModule, RenderObjectDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::createTemplate() const
{
    return (RenderObjectDrawModuleTemplate *)new RenderObjectDrawTemplateFactoryShim;
}

// ?getClass@?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?RENDEROBJECT_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_DRAW_MODULE_NAME@2@3QBDBVRenderObjectDrawModule@2@VRenderObjectDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@UBEABV?$ConcreteModuleClass@V?$ModuleTag@$05$E?RENDEROBJECT_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_DRAW_MODULE_NAME@2@3QBDBVRenderObjectDrawModule@2@VRenderObjectDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@2@XZ
const ConcreteModuleClass<ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY, RENDEROBJECT_DRAW_MODULE_NAME, RenderObjectDrawModule, RenderObjectDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &ConcreteModuleTemplate<ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY, RENDEROBJECT_DRAW_MODULE_NAME, RenderObjectDrawModule, RenderObjectDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::getClass() const
{
    return ConcreteModuleClass<ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY, RENDEROBJECT_DRAW_MODULE_NAME, RenderObjectDrawModule, RenderObjectDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::getInstance();
}

// ?getInstance@?$ConcreteModuleClass@V?$ModuleTag@$05$E?RENDEROBJECT_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_DRAW_MODULE_NAME@2@3QBDBVRenderObjectDrawModule@2@VRenderObjectDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ
__declspec(naked) const ConcreteModuleClass<ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY, RENDEROBJECT_DRAW_MODULE_NAME, RenderObjectDrawModule, RenderObjectDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &ConcreteModuleClass<ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY, RENDEROBJECT_DRAW_MODULE_NAME, RenderObjectDrawModule, RenderObjectDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::getInstance()
{
    __asm {
        __emit 0x8a
        __emit 0x0d
        __emit 0xe8
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xb8
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x84
        __emit 0xc8
        __emit 0x75
        __emit 0x53
        __emit 0x8b
        __emit 0x15
        __emit 0xe8
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x0d
        __emit 0xb8
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0x0b
        __emit 0xd0
        __emit 0xa1
        __emit 0xbc
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x00
        __emit 0x89
        __emit 0x15
        __emit 0xe8
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x11
        __emit 0xa3
        __emit 0xdc
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xa1
        __emit 0x00
        __emit 0x65
        __emit 0x2f
        __emit 0x01
        __emit 0x68
        __emit 0xb0
        __emit 0x04
        __emit 0x07
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0xd8
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0xe0
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0x00
        __emit 0x65
        __emit 0x2f
        __emit 0x01
        __emit 0xd4
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0xd4
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xdc
        __emit 0x0d
        __emit 0x11
        __emit 0x01
        __emit 0xe8
        __emit 0x47
        __emit 0x79
        __emit 0x41
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xb8
        __emit 0xd4
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xc3
    }
}

// ??0?$ConcreteModuleClass@V?$ModuleTag@$05$E?STREAK_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?STREAK_DRAW_MODULE_NAME@2@3QBDBVStreakDrawModule@2@VStreakDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@AAE@XZ
ConcreteModuleClass<ModuleTag<6, STREAK_DRAW_MODULE_KEY, STREAK_DRAW_MODULE_NAME, StreakDrawModule, StreakDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::ConcreteModuleClass()
{
    const void *first = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6ca4));
    void **slots = reinterpret_cast<void **>(this);
    const void *second = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6ca0));
    slots[0] = (void *)0x01110820;
    slots[1] = (void *)second;
    slots[2] = (void *)first;
    slots[3] = *reinterpret_cast<void **>(0x012f6500);
    *reinterpret_cast<void **>(0x012f6500) = this;
    slots[0] = (void *)0x01110db8;
}

// ??1?$ConcreteModuleClass@V?$ModuleTag@$05$E?STREAK_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?STREAK_DRAW_MODULE_NAME@2@3QBDBVStreakDrawModule@2@VStreakDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleClass<ModuleTag<6, STREAK_DRAW_MODULE_KEY, STREAK_DRAW_MODULE_NAME, StreakDrawModule, StreakDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::~ConcreteModuleClass()
{
    *(const void **)this = (const void *)0x01110820;
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$05$E?STREAK_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?STREAK_DRAW_MODULE_NAME@2@3QBDBVStreakDrawModule@2@VStreakDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVStreakDrawModuleTemplate@2@PAVINI@@@Z
__declspec(naked) StreakDrawModuleTemplate *ConcreteModuleClass<ModuleTag<6, STREAK_DRAW_MODULE_KEY, STREAK_DRAW_MODULE_NAME, StreakDrawModule, StreakDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::createTemplate(INI *ini) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x03
        __emit 0xb0
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x6a
        __emit 0x0c
        __emit 0xe8
        __emit 0x12
        __emit 0x2f
        __emit 0x2a
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x85
        __emit 0xf6
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1d
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x84
        __emit 0x7f
        __emit 0xa2
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0x38
        __emit 0x0e
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x34
        __emit 0x0e
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x08
        __emit 0x20
        __emit 0x0e
        __emit 0x11
        __emit 0x01
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xf6
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0x50
        __emit 0xcc
        __emit 0xa4
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$05$E?STREAK_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?STREAK_DRAW_MODULE_NAME@2@3QBDBVStreakDrawModule@2@VStreakDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVStreakDrawModuleTemplate@2@XZ
StreakDrawModuleTemplate *ConcreteModuleClass<ModuleTag<6, STREAK_DRAW_MODULE_KEY, STREAK_DRAW_MODULE_NAME, StreakDrawModule, StreakDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::createTemplate() const
{
    return (StreakDrawModuleTemplate *)new StreakDrawTemplateFactoryShim;
}

// ?getClass@?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?STREAK_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?STREAK_DRAW_MODULE_NAME@2@3QBDBVStreakDrawModule@2@VStreakDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@UBEABV?$ConcreteModuleClass@V?$ModuleTag@$05$E?STREAK_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?STREAK_DRAW_MODULE_NAME@2@3QBDBVStreakDrawModule@2@VStreakDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@2@XZ
const ConcreteModuleClass<ModuleTag<6, STREAK_DRAW_MODULE_KEY, STREAK_DRAW_MODULE_NAME, StreakDrawModule, StreakDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &ConcreteModuleTemplate<ModuleTag<6, STREAK_DRAW_MODULE_KEY, STREAK_DRAW_MODULE_NAME, StreakDrawModule, StreakDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::getClass() const
{
    return ConcreteModuleClass<ModuleTag<6, STREAK_DRAW_MODULE_KEY, STREAK_DRAW_MODULE_NAME, StreakDrawModule, StreakDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::getInstance();
}

// ?getInstance@?$ConcreteModuleClass@V?$ModuleTag@$05$E?STREAK_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?STREAK_DRAW_MODULE_NAME@2@3QBDBVStreakDrawModule@2@VStreakDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ
__declspec(naked) const ConcreteModuleClass<ModuleTag<6, STREAK_DRAW_MODULE_KEY, STREAK_DRAW_MODULE_NAME, StreakDrawModule, StreakDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &ConcreteModuleClass<ModuleTag<6, STREAK_DRAW_MODULE_KEY, STREAK_DRAW_MODULE_NAME, StreakDrawModule, StreakDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::getInstance()
{
    __asm {
        __emit 0x8a
        __emit 0x0d
        __emit 0xa0
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xb8
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x84
        __emit 0xc8
        __emit 0x75
        __emit 0x53
        __emit 0x8b
        __emit 0x15
        __emit 0xa0
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x0d
        __emit 0xa0
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0x0b
        __emit 0xd0
        __emit 0xa1
        __emit 0xa4
        __emit 0x6c
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x00
        __emit 0x89
        __emit 0x15
        __emit 0xa0
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x11
        __emit 0xa3
        __emit 0x94
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xa1
        __emit 0x00
        __emit 0x65
        __emit 0x2f
        __emit 0x01
        __emit 0x68
        __emit 0xe0
        __emit 0x04
        __emit 0x07
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0x90
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0x98
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0x00
        __emit 0x65
        __emit 0x2f
        __emit 0x01
        __emit 0x8c
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0x8c
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xb8
        __emit 0x0d
        __emit 0x11
        __emit 0x01
        __emit 0xe8
        __emit 0x57
        __emit 0x7e
        __emit 0x41
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xb8
        __emit 0x8c
        __emit 0x69
        __emit 0x2f
        __emit 0x01
        __emit 0xc3
    }
}

// ??0?$ConcreteModuleClass@V?$ModuleTag@$07$E?LIFE_EVENT_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIFE_EVENT_MODULE_NAME@2@3QBDBVLifeEventModule@2@VLifeEventModuleTemplate@2@VParticleLifeEventModule@2@VParticleLifeEventModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@AAE@XZ
ConcreteModuleClass<ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule, ParticleLifeEventModuleTemplate> >::ConcreteModuleClass()
{
    const void *first = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6d1c));
    void **slots = reinterpret_cast<void **>(this);
    const void *second = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6d18));
    slots[0] = (void *)0x01110874;
    slots[1] = (void *)second;
    slots[2] = (void *)first;
    slots[3] = *reinterpret_cast<void **>(0x012f6508);
    *reinterpret_cast<void **>(0x012f6508) = this;
    slots[0] = (void *)0x011113e8;
}

// ??1?$ConcreteModuleClass@V?$ModuleTag@$07$E?LIFE_EVENT_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIFE_EVENT_MODULE_NAME@2@3QBDBVLifeEventModule@2@VLifeEventModuleTemplate@2@VParticleLifeEventModule@2@VParticleLifeEventModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleClass<ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule, ParticleLifeEventModuleTemplate> >::~ConcreteModuleClass()
{
    *(const void **)this = (const void *)0x01110874;
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$07$E?LIFE_EVENT_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIFE_EVENT_MODULE_NAME@2@3QBDBVLifeEventModule@2@VLifeEventModuleTemplate@2@VParticleLifeEventModule@2@VParticleLifeEventModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVLifeEventModuleTemplate@2@PAVINI@@@Z
__declspec(naked) LifeEventModuleTemplate *ConcreteModuleClass<ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule, ParticleLifeEventModuleTemplate> >::createTemplate(INI *ini) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x43
        __emit 0xb8
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x6a
        __emit 0x24
        __emit 0xe8
        __emit 0x52
        __emit 0xd8
        __emit 0x29
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x85
        __emit 0xf6
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1d
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x2a
        __emit 0x69
        __emit 0xa6
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0x24
        __emit 0x14
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x20
        __emit 0x14
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x0c
        __emit 0x0c
        __emit 0x14
        __emit 0x11
        __emit 0x01
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xf6
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0x29
        __emit 0xae
        __emit 0xa5
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$07$E?LIFE_EVENT_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIFE_EVENT_MODULE_NAME@2@3QBDBVLifeEventModule@2@VLifeEventModuleTemplate@2@VParticleLifeEventModule@2@VParticleLifeEventModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVLifeEventModuleTemplate@2@XZ
__declspec(naked) LifeEventModuleTemplate *ConcreteModuleClass<ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule, ParticleLifeEventModuleTemplate> >::createTemplate() const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x6b
        __emit 0xb8
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x6a
        __emit 0x24
        __emit 0xe8
        __emit 0xb2
        __emit 0xd7
        __emit 0x29
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x33
        __emit 0xc0
        __emit 0x3b
        __emit 0xf0
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x74
        __emit 0x1d
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x8c
        __emit 0x68
        __emit 0xa6
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0x24
        __emit 0x14
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x20
        __emit 0x14
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x0c
        __emit 0x0c
        __emit 0x14
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xc6
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc3
    }
}

// ?getClass@?$ConcreteModuleTemplate@V?$ModuleTag@$07$E?LIFE_EVENT_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIFE_EVENT_MODULE_NAME@2@3QBDBVLifeEventModule@2@VLifeEventModuleTemplate@2@VParticleLifeEventModule@2@VParticleLifeEventModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@UBEABV?$ConcreteModuleClass@V?$ModuleTag@$07$E?LIFE_EVENT_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIFE_EVENT_MODULE_NAME@2@3QBDBVLifeEventModule@2@VLifeEventModuleTemplate@2@VParticleLifeEventModule@2@VParticleLifeEventModuleTemplate@2@@FXParticleSystem@@@2@XZ
const ConcreteModuleClass<ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule, ParticleLifeEventModuleTemplate> > &ConcreteModuleTemplate<ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule, ParticleLifeEventModuleTemplate> >::getClass() const
{
    return ConcreteModuleClass<ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule, ParticleLifeEventModuleTemplate> >::getInstance();
}

// ?getInstance@?$ConcreteModuleClass@V?$ModuleTag@$07$E?LIFE_EVENT_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIFE_EVENT_MODULE_NAME@2@3QBDBVLifeEventModule@2@VLifeEventModuleTemplate@2@VParticleLifeEventModule@2@VParticleLifeEventModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ
__declspec(naked) const ConcreteModuleClass<ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule, ParticleLifeEventModuleTemplate> > &ConcreteModuleClass<ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule, ParticleLifeEventModuleTemplate> >::getInstance()
{
    __asm {
        __emit 0x8a
        __emit 0x0d
        __emit 0x08
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xb8
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x84
        __emit 0xc8
        __emit 0x75
        __emit 0x53
        __emit 0x8b
        __emit 0x15
        __emit 0x08
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x0d
        __emit 0x18
        __emit 0x6d
        __emit 0x2f
        __emit 0x01
        __emit 0x0b
        __emit 0xd0
        __emit 0xa1
        __emit 0x1c
        __emit 0x6d
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x00
        __emit 0x89
        __emit 0x15
        __emit 0x08
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x11
        __emit 0xa3
        __emit 0xfc
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xa1
        __emit 0x08
        __emit 0x65
        __emit 0x2f
        __emit 0x01
        __emit 0x68
        __emit 0xf0
        __emit 0x05
        __emit 0x07
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0xf8
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0x00
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0x08
        __emit 0x65
        __emit 0x2f
        __emit 0x01
        __emit 0xf4
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0xf4
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xe8
        __emit 0x13
        __emit 0x11
        __emit 0x01
        __emit 0xe8
        __emit 0xa7
        __emit 0x65
        __emit 0x41
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xb8
        __emit 0xf4
        __emit 0x6a
        __emit 0x2f
        __emit 0x01
        __emit 0xc3
    }
}

// ??0?$ConcreteModuleClass@V?$ModuleTag@$07$E?TERRAIN_COLLISION_MODULE_KEY@FXParticleSystem@@3QBDB$E?TERRAIN_COLLISION_MODULE_NAME@2@3QBDBVTerrainCollisionModule@2@VTerrainCollisionModuleTemplate@2@VParticleTerrainCollisionModule@2@VParticleTerrainCollisionModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@AAE@XZ
ConcreteModuleClass<ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME, TerrainCollisionModule, TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule, ParticleTerrainCollisionModuleTemplate> >::ConcreteModuleClass()
{
    const void *first = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6d2c));
    void **slots = reinterpret_cast<void **>(this);
    const void *second = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6d28));
    slots[0] = (void *)0x01110874;
    slots[1] = (void *)second;
    slots[2] = (void *)first;
    slots[3] = *reinterpret_cast<void **>(0x012f6508);
    *reinterpret_cast<void **>(0x012f6508) = this;
    slots[0] = (void *)0x01110edc;
}

// ??1?$ConcreteModuleClass@V?$ModuleTag@$07$E?TERRAIN_COLLISION_MODULE_KEY@FXParticleSystem@@3QBDB$E?TERRAIN_COLLISION_MODULE_NAME@2@3QBDBVTerrainCollisionModule@2@VTerrainCollisionModuleTemplate@2@VParticleTerrainCollisionModule@2@VParticleTerrainCollisionModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleClass<ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME, TerrainCollisionModule, TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule, ParticleTerrainCollisionModuleTemplate> >::~ConcreteModuleClass()
{
    *(const void **)this = (const void *)0x01110874;
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$07$E?TERRAIN_COLLISION_MODULE_KEY@FXParticleSystem@@3QBDB$E?TERRAIN_COLLISION_MODULE_NAME@2@3QBDBVTerrainCollisionModule@2@VTerrainCollisionModuleTemplate@2@VParticleTerrainCollisionModule@2@VParticleTerrainCollisionModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVTerrainCollisionModuleTemplate@2@PAVINI@@@Z
__declspec(naked) TerrainCollisionModuleTemplate *ConcreteModuleClass<ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME, TerrainCollisionModule, TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule, ParticleTerrainCollisionModuleTemplate> >::createTemplate(INI *ini) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x93
        __emit 0xb8
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x6a
        __emit 0x28
        __emit 0xe8
        __emit 0x32
        __emit 0xd7
        __emit 0x29
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x85
        __emit 0xf6
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1d
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0xe8
        __emit 0xdd
        __emit 0xa2
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0x50
        __emit 0x14
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x4c
        __emit 0x14
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x0c
        __emit 0x38
        __emit 0x14
        __emit 0x11
        __emit 0x01
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xf6
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0x16
        __emit 0xa2
        __emit 0xa3
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ?createTemplate@?$ConcreteModuleClass@V?$ModuleTag@$07$E?TERRAIN_COLLISION_MODULE_KEY@FXParticleSystem@@3QBDB$E?TERRAIN_COLLISION_MODULE_NAME@2@3QBDBVTerrainCollisionModule@2@VTerrainCollisionModuleTemplate@2@VParticleTerrainCollisionModule@2@VParticleTerrainCollisionModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVTerrainCollisionModuleTemplate@2@XZ
__declspec(naked) TerrainCollisionModuleTemplate *ConcreteModuleClass<ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME, TerrainCollisionModule, TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule, ParticleTerrainCollisionModuleTemplate> >::createTemplate() const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xbb
        __emit 0xb8
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x6a
        __emit 0x28
        __emit 0xe8
        __emit 0x92
        __emit 0xd6
        __emit 0x29
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x33
        __emit 0xc0
        __emit 0x3b
        __emit 0xf0
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x74
        __emit 0x1d
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x4a
        __emit 0xdd
        __emit 0xa2
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0x50
        __emit 0x14
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x4c
        __emit 0x14
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x0c
        __emit 0x38
        __emit 0x14
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xc6
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc3
    }
}

// ?getClass@?$ConcreteModuleTemplate@V?$ModuleTag@$07$E?TERRAIN_COLLISION_MODULE_KEY@FXParticleSystem@@3QBDB$E?TERRAIN_COLLISION_MODULE_NAME@2@3QBDBVTerrainCollisionModule@2@VTerrainCollisionModuleTemplate@2@VParticleTerrainCollisionModule@2@VParticleTerrainCollisionModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@UBEABV?$ConcreteModuleClass@V?$ModuleTag@$07$E?TERRAIN_COLLISION_MODULE_KEY@FXParticleSystem@@3QBDB$E?TERRAIN_COLLISION_MODULE_NAME@2@3QBDBVTerrainCollisionModule@2@VTerrainCollisionModuleTemplate@2@VParticleTerrainCollisionModule@2@VParticleTerrainCollisionModuleTemplate@2@@FXParticleSystem@@@2@XZ
const ConcreteModuleClass<ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME, TerrainCollisionModule, TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule, ParticleTerrainCollisionModuleTemplate> > &ConcreteModuleTemplate<ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME, TerrainCollisionModule, TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule, ParticleTerrainCollisionModuleTemplate> >::getClass() const
{
    return ConcreteModuleClass<ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME, TerrainCollisionModule, TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule, ParticleTerrainCollisionModuleTemplate> >::getInstance();
}

// ?getInstance@?$ConcreteModuleClass@V?$ModuleTag@$07$E?TERRAIN_COLLISION_MODULE_KEY@FXParticleSystem@@3QBDB$E?TERRAIN_COLLISION_MODULE_NAME@2@3QBDBVTerrainCollisionModule@2@VTerrainCollisionModuleTemplate@2@VParticleTerrainCollisionModule@2@VParticleTerrainCollisionModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ
__declspec(naked) const ConcreteModuleClass<ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME, TerrainCollisionModule, TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule, ParticleTerrainCollisionModuleTemplate> > &ConcreteModuleClass<ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME, TerrainCollisionModule, TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule, ParticleTerrainCollisionModuleTemplate> >::getInstance()
{
    __asm {
        __emit 0x8a
        __emit 0x0d
        __emit 0x38
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xb8
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x84
        __emit 0xc8
        __emit 0x75
        __emit 0x53
        __emit 0x8b
        __emit 0x15
        __emit 0x38
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x0d
        __emit 0x28
        __emit 0x6d
        __emit 0x2f
        __emit 0x01
        __emit 0x0b
        __emit 0xd0
        __emit 0xa1
        __emit 0x2c
        __emit 0x6d
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x00
        __emit 0x89
        __emit 0x15
        __emit 0x38
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x11
        __emit 0xa3
        __emit 0x2c
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xa1
        __emit 0x08
        __emit 0x65
        __emit 0x2f
        __emit 0x01
        __emit 0x68
        __emit 0xd0
        __emit 0x05
        __emit 0x07
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0x28
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0x30
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0x08
        __emit 0x65
        __emit 0x2f
        __emit 0x01
        __emit 0x24
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0x24
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xdc
        __emit 0x0e
        __emit 0x11
        __emit 0x01
        __emit 0xe8
        __emit 0x57
        __emit 0x63
        __emit 0x41
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xb8
        __emit 0x24
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xc3
    }
}

// ??0?$ConcreteModuleClass@UOrthoEmissionVelocityModuleTag@FXParticleSystem@@@FXParticleSystem@@AAE@XZ
ConcreteModuleClass<OrthoEmissionVelocityModuleTag>::ConcreteModuleClass()
{
    const void *first = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6d34));
    void **self = reinterpret_cast<void **>(this);
    const void *second = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6d30));
    *reinterpret_cast<void **>(0x012f64d4) = this;
    self[0] = (void *)0x01110880;
    self[1] = (void *)second;
    self[2] = (void *)first;
    self[3] = *reinterpret_cast<void **>(0x012f64f8);
    *reinterpret_cast<void **>(0x012f64f8) = this;
    self[0] = (void *)0x011113f4;
}

// ??1?$ConcreteModuleClass@UOrthoEmissionVelocityModuleTag@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleClass<OrthoEmissionVelocityModuleTag>::~ConcreteModuleClass()
{
    *(const void **)this = (const void *)0x01110880;
}

// ?createTemplate@?$ConcreteModuleClass@UOrthoEmissionVelocityModuleTag@FXParticleSystem@@@FXParticleSystem@@UBEPAVOrthoEmissionVelocityModuleTemplate@2@PAVINI@@@Z
__declspec(naked) OrthoEmissionVelocityModuleTemplate *ConcreteModuleClass<OrthoEmissionVelocityModuleTag>::createTemplate(INI *ini) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xf3
        __emit 0xb2
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x6a
        __emit 0x30
        __emit 0xe8
        __emit 0x82
        __emit 0x13
        __emit 0x2a
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x85
        __emit 0xf6
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1d
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x09
        __emit 0xef
        __emit 0xa2
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0xa0
        __emit 0x10
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x9c
        __emit 0x10
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x08
        __emit 0x88
        __emit 0x10
        __emit 0x11
        __emit 0x01
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xf6
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0xf1
        __emit 0xf2
        __emit 0xa4
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ?createTemplate@?$ConcreteModuleClass@UOrthoEmissionVelocityModuleTag@FXParticleSystem@@@FXParticleSystem@@UBEPAVOrthoEmissionVelocityModuleTemplate@2@XZ
__declspec(naked) OrthoEmissionVelocityModuleTemplate *ConcreteModuleClass<OrthoEmissionVelocityModuleTag>::createTemplate() const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x1b
        __emit 0xb3
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x6a
        __emit 0x30
        __emit 0xe8
        __emit 0xe2
        __emit 0x12
        __emit 0x2a
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x33
        __emit 0xc0
        __emit 0x3b
        __emit 0xf0
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x74
        __emit 0x1d
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x6b
        __emit 0xee
        __emit 0xa2
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0xa0
        __emit 0x10
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x9c
        __emit 0x10
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x08
        __emit 0x88
        __emit 0x10
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xc6
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc3
    }
}

// ?getClass@?$ConcreteModuleTemplate@UOrthoEmissionVelocityModuleTag@FXParticleSystem@@@FXParticleSystem@@UBEABV?$ConcreteModuleClass@UOrthoEmissionVelocityModuleTag@FXParticleSystem@@@2@XZ
const ConcreteModuleClass<OrthoEmissionVelocityModuleTag> &ConcreteModuleTemplate<OrthoEmissionVelocityModuleTag>::getClass() const
{
    return ConcreteModuleClass<OrthoEmissionVelocityModuleTag>::getInstance();
}

// ?getInstance@?$ConcreteModuleClass@UOrthoEmissionVelocityModuleTag@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ
__declspec(naked) const ConcreteModuleClass<OrthoEmissionVelocityModuleTag> &ConcreteModuleClass<OrthoEmissionVelocityModuleTag>::getInstance()
{
    __asm {
        __emit 0x8a
        __emit 0x0d
        __emit 0x50
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xb8
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x84
        __emit 0xc8
        __emit 0x75
        __emit 0x5a
        __emit 0x8b
        __emit 0x15
        __emit 0x50
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x0d
        __emit 0x30
        __emit 0x6d
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x09
        __emit 0x0b
        __emit 0xd0
        __emit 0xa1
        __emit 0x34
        __emit 0x6d
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x00
        __emit 0x89
        __emit 0x15
        __emit 0x50
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xba
        __emit 0x3c
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0x44
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xa1
        __emit 0xf8
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0x68
        __emit 0xc0
        __emit 0x05
        __emit 0x07
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0xd4
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0x89
        __emit 0x0d
        __emit 0x40
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0x48
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0xf8
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0x3c
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xf4
        __emit 0x13
        __emit 0x11
        __emit 0x01
        __emit 0xe8
        __emit 0xc0
        __emit 0x62
        __emit 0x41
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xb8
        __emit 0x3c
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xc3
    }
}

// ??0?$ConcreteModuleClass@UPointEmissionVolumeModuleTag@FXParticleSystem@@@FXParticleSystem@@AAE@XZ
ConcreteModuleClass<PointEmissionVolumeModuleTag>::ConcreteModuleClass()
{
    const void *first = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6d5c));
    void **self = reinterpret_cast<void **>(this);
    const void *second = *reinterpret_cast<void **>(*reinterpret_cast<void **>(0x012f6d58));
    *reinterpret_cast<void **>(0x012f64d8) = this;
    self[0] = (void *)0x0111088c;
    self[1] = (void *)second;
    self[2] = (void *)first;
    self[3] = *reinterpret_cast<void **>(0x012f64fc);
    *reinterpret_cast<void **>(0x012f64fc) = this;
    self[0] = (void *)0x01111400;
}

// ??1?$ConcreteModuleClass@UPointEmissionVolumeModuleTag@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleClass<PointEmissionVolumeModuleTag>::~ConcreteModuleClass()
{
    *(const void **)this = (const void *)0x0111088c;
}

// ?createTemplate@?$ConcreteModuleClass@UPointEmissionVolumeModuleTag@FXParticleSystem@@@FXParticleSystem@@UBEPAVPointEmissionVolumeModuleTemplate@2@PAVINI@@@Z
__declspec(naked) PointEmissionVolumeModuleTemplate *ConcreteModuleClass<PointEmissionVolumeModuleTag>::createTemplate(INI *ini) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x78
        __emit 0xb4
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x6a
        __emit 0x10
        __emit 0xe8
        __emit 0x12
        __emit 0x0b
        __emit 0x2a
        __emit 0x00
        __emit 0x33
        __emit 0xc9
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x3b
        __emit 0xc1
        __emit 0x74
        __emit 0x29
        __emit 0xc7
        __emit 0x40
        __emit 0x04
        __emit 0xac
        __emit 0xf9
        __emit 0x10
        __emit 0x01
        __emit 0xc7
        __emit 0x40
        __emit 0x08
        __emit 0x80
        __emit 0xf9
        __emit 0x10
        __emit 0x01
        __emit 0x88
        __emit 0x48
        __emit 0x0c
        __emit 0xc7
        __emit 0x00
        __emit 0x7c
        __emit 0x11
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x40
        __emit 0x04
        __emit 0x78
        __emit 0x11
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x40
        __emit 0x08
        __emit 0x64
        __emit 0x11
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xf0
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xf6
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x89
        __emit 0x4c
        __emit 0x24
        __emit 0x10
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0xcb
        __emit 0x02
        __emit 0xa6
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ?createTemplate@?$ConcreteModuleClass@UPointEmissionVolumeModuleTag@FXParticleSystem@@@FXParticleSystem@@UBEPAVPointEmissionVolumeModuleTemplate@2@XZ
PointEmissionVolumeModuleTemplate *ConcreteModuleClass<PointEmissionVolumeModuleTag>::createTemplate() const
{
    PointEmissionVolumeModuleTemplate *result =
        (PointEmissionVolumeModuleTemplate *)::operator new(0x10);
    if (result != 0) {
        *(volatile unsigned int *)((unsigned char *)result + 4) = 0x0110f9ac;
        *(volatile unsigned int *)((unsigned char *)result + 8) = 0x0110f980;
        *((volatile unsigned char *)result + 0x0c) = 0;
        *(volatile unsigned int *)result = 0x0111117c;
        *(volatile unsigned int *)((unsigned char *)result + 4) = 0x01111178;
        *(volatile unsigned int *)((unsigned char *)result + 8) = 0x01111164;
        return result;
    }
    return 0;
}

// ?getClass@?$ConcreteModuleTemplate@UPointEmissionVolumeModuleTag@FXParticleSystem@@@FXParticleSystem@@UBEABV?$ConcreteModuleClass@UPointEmissionVolumeModuleTag@FXParticleSystem@@@2@XZ
const ConcreteModuleClass<PointEmissionVolumeModuleTag> &ConcreteModuleTemplate<PointEmissionVolumeModuleTag>::getClass() const
{
    return ConcreteModuleClass<PointEmissionVolumeModuleTag>::getInstance();
}

// ?getInstance@?$ConcreteModuleClass@UPointEmissionVolumeModuleTag@FXParticleSystem@@@FXParticleSystem@@SAABV12@XZ
__declspec(naked) const ConcreteModuleClass<PointEmissionVolumeModuleTag> &ConcreteModuleClass<PointEmissionVolumeModuleTag>::getInstance()
{
    __asm {
        __emit 0x8a
        __emit 0x0d
        __emit 0xc8
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xb8
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x84
        __emit 0xc8
        __emit 0x75
        __emit 0x5a
        __emit 0x8b
        __emit 0x15
        __emit 0xc8
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x0d
        __emit 0x58
        __emit 0x6d
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x09
        __emit 0x0b
        __emit 0xd0
        __emit 0xa1
        __emit 0x5c
        __emit 0x6d
        __emit 0x2f
        __emit 0x01
        __emit 0x8b
        __emit 0x00
        __emit 0x89
        __emit 0x15
        __emit 0xc8
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xba
        __emit 0xb4
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0xbc
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xa1
        __emit 0xfc
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0x68
        __emit 0x70
        __emit 0x05
        __emit 0x07
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0xd8
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0x89
        __emit 0x0d
        __emit 0xb8
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xa3
        __emit 0xc0
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0x89
        __emit 0x15
        __emit 0xfc
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0xc7
        __emit 0x05
        __emit 0xb4
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0x00
        __emit 0x14
        __emit 0x11
        __emit 0x01
        __emit 0xe8
        __emit 0x50
        __emit 0x5a
        __emit 0x41
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xb8
        __emit 0xb4
        __emit 0x6b
        __emit 0x2f
        __emit 0x01
        __emit 0xc3
    }
}

// ??0?$ConcreteModuleTemplate@V?$DefaultModuleTag@$0A@@FXParticleSystem@@@FXParticleSystem@@QAE@ABV01@@Z
ConcreteModuleTemplate<DefaultModuleTag<0> >::ConcreteModuleTemplate(const ConcreteModuleTemplate<DefaultModuleTag<0> > &that)
{
    ((DefaultModuleTemplate0CopyCtorShim *)this)->construct(&that);
    *(volatile unsigned int *)this = 0x01110f98;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01110f94;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01110f80;
}

// ??0?$ConcreteModuleTemplate@V?$DefaultModuleTag@$0A@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleTemplate<DefaultModuleTag<0> >::ConcreteModuleTemplate()
{
    ((DefaultModuleTemplate0CtorShim *)this)->construct();
    *(volatile unsigned int *)this = 0x01110f98;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01110f94;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01110f80;
}

// ??1?$ConcreteModuleTemplate@V?$DefaultModuleTag@$0A@@FXParticleSystem@@@FXParticleSystem@@UAE@XZ
ConcreteModuleTemplate<DefaultModuleTag<0> >::~ConcreteModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x01073760;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??4?$ConcreteModuleTemplate@V?$DefaultModuleTag@$0A@@FXParticleSystem@@@FXParticleSystem@@QAEAAV01@ABV01@@Z
ConcreteModuleTemplate<DefaultModuleTag<0> > &ConcreteModuleTemplate<DefaultModuleTag<0> >::operator=(const ConcreteModuleTemplate<DefaultModuleTag<0> > &that)
{
    const void *source = &that;
    const unsigned char *info = source ? (const unsigned char *)source + 8 : 0;
    ((DefaultModuleTemplate0AssignShim *)((unsigned char *)this + 8))->assign(info);
    return *this;
}

// ?createModule@?$ConcreteModuleTemplate@V?$DefaultModuleTag@$0A@@FXParticleSystem@@@FXParticleSystem@@UAEPAV?$DefaultModule@$0A@@2@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@@@Z
__declspec(naked) DefaultModule<0> *ConcreteModuleTemplate<DefaultModuleTag<0> >::createModule(TrackingPtr<ParticleSystem> &sys)
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x9b
        __emit 0xbb
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x57
        __emit 0x68
        __emit 0xac
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0xf9
        __emit 0xe8
        __emit 0x2c
        __emit 0x94
        __emit 0x29
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0x33
        __emit 0xc0
        __emit 0x3b
        __emit 0xf0
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x74
        __emit 0x2a
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x1c
        __emit 0x57
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x2c
        __emit 0xaa
        __emit 0xa4
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0xcc
        __emit 0x1f
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x14
        __emit 0xc8
        __emit 0x1f
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x18
        __emit 0xc4
        __emit 0x1f
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x1c
        __emit 0xb0
        __emit 0x1f
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xc6
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x5f
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ??0?$ConcreteModuleTemplate@V?$DefaultModuleTag@$00@FXParticleSystem@@@FXParticleSystem@@QAE@ABV01@@Z
ConcreteModuleTemplate<DefaultModuleTag<1> >::ConcreteModuleTemplate(const ConcreteModuleTemplate<DefaultModuleTag<1> > &that)
{
    ((DefaultModuleTemplate1CopyCtorShim *)this)->construct(&that);
    *(volatile unsigned int *)this = 0x01110f6c;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01110f68;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01110f54;
}

// ??0?$ConcreteModuleTemplate@V?$DefaultModuleTag@$00@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleTemplate<DefaultModuleTag<1> >::ConcreteModuleTemplate()
{
    ((DefaultModuleTemplate1CtorShim *)this)->construct();
    *(volatile unsigned int *)this = 0x01110f6c;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01110f68;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01110f54;
}

// ??1?$ConcreteModuleTemplate@V?$DefaultModuleTag@$00@FXParticleSystem@@@FXParticleSystem@@UAE@XZ
ConcreteModuleTemplate<DefaultModuleTag<1> >::~ConcreteModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f978;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??4?$ConcreteModuleTemplate@V?$DefaultModuleTag@$00@FXParticleSystem@@@FXParticleSystem@@QAEAAV01@ABV01@@Z
ConcreteModuleTemplate<DefaultModuleTag<1> > &ConcreteModuleTemplate<DefaultModuleTag<1> >::operator=(const ConcreteModuleTemplate<DefaultModuleTag<1> > &that)
{
    const void *source = &that;
    const unsigned char *info = source ? (const unsigned char *)source + 8 : 0;
    ((DefaultModuleTemplate1AssignShim *)((unsigned char *)this + 8))->assign(info);
    return *this;
}

// ?createModule@?$ConcreteModuleTemplate@V?$DefaultModuleTag@$00@FXParticleSystem@@@FXParticleSystem@@UAEPAV?$DefaultModule@$00@2@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@@@Z
__declspec(naked) DefaultModule<1> *ConcreteModuleTemplate<DefaultModuleTag<1> >::createModule(TrackingPtr<ParticleSystem> &sys)
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x3b
        __emit 0xbd
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x57
        __emit 0x68
        __emit 0xa0
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0xf9
        __emit 0xe8
        __emit 0xfc
        __emit 0x5f
        __emit 0x29
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0x33
        __emit 0xc0
        __emit 0x3b
        __emit 0xf0
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x74
        __emit 0x2a
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x1c
        __emit 0x57
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0xc0
        __emit 0x42
        __emit 0xa5
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0xec
        __emit 0x2d
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x14
        __emit 0xe8
        __emit 0x2d
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x18
        __emit 0xe4
        __emit 0x2d
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x1c
        __emit 0xd0
        __emit 0x2d
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xc6
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x5f
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ??0?$ConcreteModuleTemplate@V?$DefaultModuleTag@$01@FXParticleSystem@@@FXParticleSystem@@QAE@ABV01@@Z
ConcreteModuleTemplate<DefaultModuleTag<2> >::ConcreteModuleTemplate(const ConcreteModuleTemplate<DefaultModuleTag<2> > &that)
{
    ((DefaultModuleTemplate2CopyCtorShim *)this)->construct(&that);
    *(volatile unsigned int *)this = 0x01110ff0;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01110fec;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01110fd8;
}

// ??0?$ConcreteModuleTemplate@V?$DefaultModuleTag@$01@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleTemplate<DefaultModuleTag<2> >::ConcreteModuleTemplate()
{
    ((DefaultModuleTemplate2CtorShim *)this)->construct();
    *(volatile unsigned int *)this = 0x01110ff0;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01110fec;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01110fd8;
}

// ??1?$ConcreteModuleTemplate@V?$DefaultModuleTag@$01@FXParticleSystem@@@FXParticleSystem@@UAE@XZ
ConcreteModuleTemplate<DefaultModuleTag<2> >::~ConcreteModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f9e8;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??4?$ConcreteModuleTemplate@V?$DefaultModuleTag@$01@FXParticleSystem@@@FXParticleSystem@@QAEAAV01@ABV01@@Z
ConcreteModuleTemplate<DefaultModuleTag<2> > &ConcreteModuleTemplate<DefaultModuleTag<2> >::operator=(const ConcreteModuleTemplate<DefaultModuleTag<2> > &that)
{
    const void *source = &that;
    const unsigned char *info = source ? (const unsigned char *)source + 8 : 0;
    ((DefaultModuleTemplate2AssignShim *)((unsigned char *)this + 8))->assign(info);
    return *this;
}

// ?createModule@?$ConcreteModuleTemplate@V?$DefaultModuleTag@$01@FXParticleSystem@@@FXParticleSystem@@UAEPAV?$DefaultModule@$01@2@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@@@Z
__declspec(naked) DefaultModule<2> *ConcreteModuleTemplate<DefaultModuleTag<2> >::createModule(TrackingPtr<ParticleSystem> &sys)
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x5b
        __emit 0xbd
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x57
        __emit 0x6a
        __emit 0x60
        __emit 0x8b
        __emit 0xf9
        __emit 0xe8
        __emit 0x5f
        __emit 0x5f
        __emit 0x29
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0x33
        __emit 0xc0
        __emit 0x3b
        __emit 0xf0
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x74
        __emit 0x2a
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x1c
        __emit 0x57
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x2a
        __emit 0x73
        __emit 0xa4
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0x1c
        __emit 0x2e
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x14
        __emit 0x18
        __emit 0x2e
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x18
        __emit 0x14
        __emit 0x2e
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x1c
        __emit 0x00
        __emit 0x2e
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xc6
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x5f
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ??0?$ConcreteModuleTemplate@V?$DefaultModuleTag@$02@FXParticleSystem@@@FXParticleSystem@@QAE@ABV01@@Z
ConcreteModuleTemplate<DefaultModuleTag<3> >::ConcreteModuleTemplate(const ConcreteModuleTemplate<DefaultModuleTag<3> > &that)
{
    ((DefaultModuleTemplate3CopyCtorShim *)this)->construct(&that);
    *(volatile unsigned int *)this = 0x01110fc4;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01110fc0;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01110fac;
}

// ??0?$ConcreteModuleTemplate@V?$DefaultModuleTag@$02@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleTemplate<DefaultModuleTag<3> >::ConcreteModuleTemplate()
{
    ((DefaultModuleTemplate3CtorShim *)this)->construct();
    *(volatile unsigned int *)this = 0x01110fc4;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01110fc0;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01110fac;
}

// ??1?$ConcreteModuleTemplate@V?$DefaultModuleTag@$02@FXParticleSystem@@@FXParticleSystem@@UAE@XZ
ConcreteModuleTemplate<DefaultModuleTag<3> >::~ConcreteModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f9e4;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??4?$ConcreteModuleTemplate@V?$DefaultModuleTag@$02@FXParticleSystem@@@FXParticleSystem@@QAEAAV01@ABV01@@Z
ConcreteModuleTemplate<DefaultModuleTag<3> > &ConcreteModuleTemplate<DefaultModuleTag<3> >::operator=(const ConcreteModuleTemplate<DefaultModuleTag<3> > &that)
{
	struct VariableBlock {
		unsigned int value0;
		unsigned int value1;
		unsigned int value2;
	};

	const void *src = &that;
	const unsigned char *base = src ? (const unsigned char *)src + 8 : 0;
	memcpy((unsigned char *)this + 0x0c, base + 4, 12);
	*((unsigned int *)((unsigned char *)this + 0x18)) = *(const unsigned int *)(base + 0x10);
	base += 0x14;
	*(VariableBlock *)((unsigned char *)this + 0x1c) = *(const VariableBlock *)base;
	return *this;
}

// ?createModule@?$ConcreteModuleTemplate@V?$DefaultModuleTag@$02@FXParticleSystem@@@FXParticleSystem@@UAEPAV?$DefaultModule@$02@2@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@@@Z
__declspec(naked) DefaultModule<3> *ConcreteModuleTemplate<DefaultModuleTag<3> >::createModule(TrackingPtr<ParticleSystem> &sys)
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xbb
        __emit 0xbb
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x57
        __emit 0x6a
        __emit 0x3c
        __emit 0x8b
        __emit 0xf9
        __emit 0xe8
        __emit 0x8f
        __emit 0x93
        __emit 0x29
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0x33
        __emit 0xc0
        __emit 0x3b
        __emit 0xf0
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x74
        __emit 0x2a
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x1c
        __emit 0x57
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x3b
        __emit 0x9f
        __emit 0xa3
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0x50
        __emit 0x20
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x14
        __emit 0x4c
        __emit 0x20
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x18
        __emit 0x48
        __emit 0x20
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x1c
        __emit 0x34
        __emit 0x20
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xc6
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x5f
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ??0?$ConcreteModuleTemplate@V?$DefaultModuleTag@$05@FXParticleSystem@@@FXParticleSystem@@QAE@ABV01@@Z
ConcreteModuleTemplate<DefaultModuleTag<6> >::ConcreteModuleTemplate(const ConcreteModuleTemplate<DefaultModuleTag<6> > &that)
{
    ((DefaultModuleTemplate6CopyCtorShim *)this)->construct(&that);
    *(volatile unsigned int *)this = 0x01110e0c;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01110e08;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01110df4;
}

// ??0?$ConcreteModuleTemplate@V?$DefaultModuleTag@$05@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleTemplate<DefaultModuleTag<6> >::ConcreteModuleTemplate()
{
    ((DefaultModuleTemplate6CtorShim *)this)->construct();
    *(volatile unsigned int *)this = 0x01110e0c;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01110e08;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01110df4;
}

// ??1?$ConcreteModuleTemplate@V?$DefaultModuleTag@$05@FXParticleSystem@@@FXParticleSystem@@UAE@XZ
ConcreteModuleTemplate<DefaultModuleTag<6> >::~ConcreteModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f97c;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??4?$ConcreteModuleTemplate@V?$DefaultModuleTag@$05@FXParticleSystem@@@FXParticleSystem@@QAEAAV01@ABV01@@Z
ConcreteModuleTemplate<DefaultModuleTag<6> > &ConcreteModuleTemplate<DefaultModuleTag<6> >::operator=(const ConcreteModuleTemplate<DefaultModuleTag<6> > &that)
{
    return *this;
}

// ?createModule@?$ConcreteModuleTemplate@V?$DefaultModuleTag@$05@FXParticleSystem@@@FXParticleSystem@@UAEPAV?$DefaultModule@$05@2@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@@@Z
__declspec(naked) DefaultModule<6> *ConcreteModuleTemplate<DefaultModuleTag<6> >::createModule(TrackingPtr<ParticleSystem> &sys)
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xdb
        __emit 0xba
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x57
        __emit 0x6a
        __emit 0x1c
        __emit 0x8b
        __emit 0xf9
        __emit 0xe8
        __emit 0x8f
        __emit 0x97
        __emit 0x29
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0x33
        __emit 0xc0
        __emit 0x3b
        __emit 0xf0
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x74
        __emit 0x23
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x1c
        __emit 0x57
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x32
        __emit 0x0a
        __emit 0xa5
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0xb4
        __emit 0x1d
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x14
        __emit 0xb0
        __emit 0x1d
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x18
        __emit 0x9c
        __emit 0x1d
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xc6
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x5f
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ??0?$ConcreteModuleTemplate@V?$DefaultModuleTag@$06@FXParticleSystem@@@FXParticleSystem@@QAE@ABV01@@Z
ConcreteModuleTemplate<DefaultModuleTag<7> >::ConcreteModuleTemplate(const ConcreteModuleTemplate<DefaultModuleTag<7> > &that)
{
    ((DefaultModuleTemplate7CopyCtorShim *)this)->construct(&that);
    *(volatile unsigned int *)this = 0x01111048;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01111044;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01111030;
}

// ??0?$ConcreteModuleTemplate@V?$DefaultModuleTag@$06@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleTemplate<DefaultModuleTag<7> >::ConcreteModuleTemplate()
{
    ((DefaultModuleTemplate7CtorShim *)this)->construct();
    *(volatile unsigned int *)this = 0x01111048;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01111044;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01111030;
}

// ??1?$ConcreteModuleTemplate@V?$DefaultModuleTag@$06@FXParticleSystem@@@FXParticleSystem@@UAE@XZ
ConcreteModuleTemplate<DefaultModuleTag<7> >::~ConcreteModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110fa14;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??4?$ConcreteModuleTemplate@V?$DefaultModuleTag@$06@FXParticleSystem@@@FXParticleSystem@@QAEAAV01@ABV01@@Z
ConcreteModuleTemplate<DefaultModuleTag<7> > &ConcreteModuleTemplate<DefaultModuleTag<7> >::operator=(const ConcreteModuleTemplate<DefaultModuleTag<7> > &that)
{
    const void *source = &that;
    const unsigned char *info = source ? (const unsigned char *)source + 8 : 0;
    ((DefaultModuleTemplate7AssignShim *)((unsigned char *)this + 8))->assign(info);
    return *this;
}

// ?createModule@?$ConcreteModuleTemplate@V?$DefaultModuleTag@$06@FXParticleSystem@@@FXParticleSystem@@UAEPAV?$DefaultModule@$06@2@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@@@Z
__declspec(naked) DefaultModule<7> *ConcreteModuleTemplate<DefaultModuleTag<7> >::createModule(TrackingPtr<ParticleSystem> &sys)
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xdb
        __emit 0xbb
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x57
        __emit 0x6a
        __emit 0x64
        __emit 0x8b
        __emit 0xf9
        __emit 0xe8
        __emit 0xff
        __emit 0x92
        __emit 0x29
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0x33
        __emit 0xc0
        __emit 0x3b
        __emit 0xf0
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x74
        __emit 0x2a
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x1c
        __emit 0x57
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0xad
        __emit 0xab
        __emit 0xa3
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0xcc
        __emit 0x20
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x14
        __emit 0xc8
        __emit 0x20
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x18
        __emit 0xc4
        __emit 0x20
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x1c
        __emit 0xb0
        __emit 0x20
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xc6
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x5f
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$01$E?RENDEROBJECT_UPDATE_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_UPDATE_MODULE_NAME@2@3QBDBVRenderObjectUpdateModule@2@VRenderObjectUpdateModuleTemplate@2@VRenderObjectParticleUpdateModule@2@VRenderObjectParticleUpdateModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@QAE@ABV01@@Z
ConcreteModuleTemplate<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule, RenderObjectParticleUpdateModuleTemplate> >::ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule, RenderObjectParticleUpdateModuleTemplate> > &that)
{
    ((RenderObjectUpdateTemplateCopyCtorShim *)this)->construct(&that);
    *(volatile unsigned int *)this = 0x01111074;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01111070;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x0111105c;
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$01$E?RENDEROBJECT_UPDATE_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_UPDATE_MODULE_NAME@2@3QBDBVRenderObjectUpdateModule@2@VRenderObjectUpdateModuleTemplate@2@VRenderObjectParticleUpdateModule@2@VRenderObjectParticleUpdateModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleTemplate<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule, RenderObjectParticleUpdateModuleTemplate> >::ConcreteModuleTemplate()
{
    ((RenderObjectUpdateTemplateCtorShim *)this)->construct();
    *(volatile unsigned int *)this = 0x01111074;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01111070;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x0111105c;
}

// ??1?$ConcreteModuleTemplate@V?$ModuleTag@$01$E?RENDEROBJECT_UPDATE_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_UPDATE_MODULE_NAME@2@3QBDBVRenderObjectUpdateModule@2@VRenderObjectUpdateModuleTemplate@2@VRenderObjectParticleUpdateModule@2@VRenderObjectParticleUpdateModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@UAE@XZ
ConcreteModuleTemplate<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule, RenderObjectParticleUpdateModuleTemplate> >::~ConcreteModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f9e8;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??4?$ConcreteModuleTemplate@V?$ModuleTag@$01$E?RENDEROBJECT_UPDATE_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_UPDATE_MODULE_NAME@2@3QBDBVRenderObjectUpdateModule@2@VRenderObjectUpdateModuleTemplate@2@VRenderObjectParticleUpdateModule@2@VRenderObjectParticleUpdateModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@QAEAAV01@ABV01@@Z
ConcreteModuleTemplate<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule, RenderObjectParticleUpdateModuleTemplate> > &ConcreteModuleTemplate<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule, RenderObjectParticleUpdateModuleTemplate> >::operator=(const ConcreteModuleTemplate<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule, RenderObjectParticleUpdateModuleTemplate> > &that)
{
    const void *source = &that;
    const unsigned char *info = source ? (const unsigned char *)source + 8 : 0;
    ((RenderObjectUpdateTemplateAssignShim *)((unsigned char *)this + 8))->assign(info);
    return *this;
}

// ?clone@?$ConcreteModuleTemplate@V?$ModuleTag@$01$E?RENDEROBJECT_UPDATE_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_UPDATE_MODULE_NAME@2@3QBDBVRenderObjectUpdateModule@2@VRenderObjectUpdateModuleTemplate@2@VRenderObjectParticleUpdateModule@2@VRenderObjectParticleUpdateModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVRenderObjectUpdateModuleTemplate@2@XZ
// Converted to RenderObjectUpdateConcreteModuleTemplateCloneThunk.cpp.

// ?createModule@?$ConcreteModuleTemplate@V?$ModuleTag@$01$E?RENDEROBJECT_UPDATE_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_UPDATE_MODULE_NAME@2@3QBDBVRenderObjectUpdateModule@2@VRenderObjectUpdateModuleTemplate@2@VRenderObjectParticleUpdateModule@2@VRenderObjectParticleUpdateModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@UAEPAVRenderObjectUpdateModule@2@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@@@Z
__declspec(naked) RenderObjectUpdateModule *ConcreteModuleTemplate<ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule, RenderObjectParticleUpdateModuleTemplate> >::createModule(TrackingPtr<ParticleSystem> &sys)
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x7b
        __emit 0xbd
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x57
        __emit 0x68
        __emit 0xb4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0xf9
        __emit 0xe8
        __emit 0xcc
        __emit 0x5e
        __emit 0x29
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0x33
        __emit 0xc0
        __emit 0x3b
        __emit 0xf0
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x74
        __emit 0x2a
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x1c
        __emit 0x57
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0xcc
        __emit 0x3a
        __emit 0xa2
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0x4c
        __emit 0x2e
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x14
        __emit 0x48
        __emit 0x2e
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x18
        __emit 0x44
        __emit 0x2e
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x1c
        __emit 0x30
        __emit 0x2e
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xc6
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x5f
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVCylindricalEmissionVelocityModule@2@VCylindricalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@QAE@ABV01@@Z
ConcreteModuleTemplate<ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &that)
{
    ((CylindricalEmissionVelocityTemplateCopyCtorShim *)this)->construct(&that);
    *(volatile unsigned int *)this = 0x01111124;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01111120;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x0111110c;
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVCylindricalEmissionVelocityModule@2@VCylindricalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleTemplate<ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::ConcreteModuleTemplate()
{
    ((CylindricalEmissionVelocityTemplateCtorShim *)this)->construct();
    *(volatile unsigned int *)this = 0x01111124;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01111120;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x0111110c;
}

// ??1?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVCylindricalEmissionVelocityModule@2@VCylindricalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@UAE@XZ
ConcreteModuleTemplate<ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::~ConcreteModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f9cc;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??4?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVCylindricalEmissionVelocityModule@2@VCylindricalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@QAEAAV01@ABV01@@Z
ConcreteModuleTemplate<ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &ConcreteModuleTemplate<ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::operator=(const ConcreteModuleTemplate<ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &that)
{
	const void *src = &that;
	const unsigned char *base = src ? (const unsigned char *)src + 8 : 0;
	memcpy((unsigned char *)this + 0x0c, base + 4, 12);
	memcpy((unsigned char *)this + 0x18, base + 0x10, 12);
	return *this;
}

// ?clone@?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVCylindricalEmissionVelocityModule@2@VCylindricalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVCylindricalEmissionVelocityModuleTemplate@2@XZ
CylindricalEmissionVelocityModuleTemplate *ConcreteModuleTemplate<ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::clone() const
{
    return (CylindricalEmissionVelocityModuleTemplate *)new ConcreteModuleTemplate<ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >(*this);
}

// ?createModule@?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVCylindricalEmissionVelocityModule@2@VCylindricalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@UAEPAVCylindricalEmissionVelocityModule@2@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@@@Z
CylindricalEmissionVelocityModule *ConcreteModuleTemplate<ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::createModule(TrackingPtr<ParticleSystem> &sys)
{
    CylindricalEmissionVelocityModule *module =
        (CylindricalEmissionVelocityModule *)::operator new(0x34);
    if (module) {
        const void *source = this;
        ((CylindricalEmissionVelocityModuleCtorShim *)module)->construct(sys, source);
        initializeCylindricalEmissionVelocityModule(module);
        return module;
    }
    return 0;
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVHemisphericalEmissionVelocityModule@2@VHemisphericalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@QAE@ABV01@@Z
ConcreteModuleTemplate<ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &that)
{
    ((HemisphericalEmissionVelocityTemplateCopyCtorShim *)this)->construct(&that);
    *(volatile unsigned int *)this = 0x011110f8;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x011110f4;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x011110e0;
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVHemisphericalEmissionVelocityModule@2@VHemisphericalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleTemplate<ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::ConcreteModuleTemplate()
{
    ((HemisphericalEmissionVelocityTemplateCtorShim *)this)->construct();
    *(volatile unsigned int *)this = 0x011110f8;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x011110f4;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x011110e0;
}

// ??1?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVHemisphericalEmissionVelocityModule@2@VHemisphericalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@UAE@XZ
ConcreteModuleTemplate<ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::~ConcreteModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f9cc;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??4?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVHemisphericalEmissionVelocityModule@2@VHemisphericalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@QAEAAV01@ABV01@@Z
ConcreteModuleTemplate<ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &ConcreteModuleTemplate<ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::operator=(const ConcreteModuleTemplate<ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &that)
{
	const void *src = &that;
	const unsigned char *base = src ? (const unsigned char *)src + 8 : 0;
	base += 4;
	memcpy((unsigned char *)this + 0x0c, base, 12);
	return *this;
}

// ?clone@?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVHemisphericalEmissionVelocityModule@2@VHemisphericalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVHemisphericalEmissionVelocityModuleTemplate@2@XZ
HemisphericalEmissionVelocityModuleTemplate *ConcreteModuleTemplate<ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::clone() const
{
    return (HemisphericalEmissionVelocityModuleTemplate *)new ConcreteModuleTemplate<ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >(*this);
}

// ?createModule@?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVHemisphericalEmissionVelocityModule@2@VHemisphericalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@UAEPAVHemisphericalEmissionVelocityModule@2@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@@@Z
HemisphericalEmissionVelocityModule *ConcreteModuleTemplate<ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::createModule(TrackingPtr<ParticleSystem> &sys)
{
    HemisphericalEmissionVelocityModule *module =
        (HemisphericalEmissionVelocityModule *)::operator new(0x28);
    if (module) {
        const void *source = this;
        ((HemisphericalEmissionVelocityModuleCtorShim *)module)->construct(sys, source);
        initializeHemisphericalEmissionVelocityModule(module);
        return module;
    }
    return 0;
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?OUTWARD_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?OUTWARD_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVOutwardEmissionVelocityModule@2@VOutwardEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@QAE@ABV01@@Z
ConcreteModuleTemplate<ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &that)
{
    ((OutwardEmissionVelocityTemplateCopyCtorShim *)this)->construct(&that);
    *(volatile unsigned int *)this = 0x01111150;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x0111114c;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01111138;
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?OUTWARD_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?OUTWARD_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVOutwardEmissionVelocityModule@2@VOutwardEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleTemplate<ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::ConcreteModuleTemplate()
{
    ((OutwardEmissionVelocityTemplateCtorShim *)this)->construct();
    *(volatile unsigned int *)this = 0x01111150;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x0111114c;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01111138;
}

// ??1?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?OUTWARD_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?OUTWARD_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVOutwardEmissionVelocityModule@2@VOutwardEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@UAE@XZ
ConcreteModuleTemplate<ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::~ConcreteModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f9cc;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??4?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?OUTWARD_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?OUTWARD_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVOutwardEmissionVelocityModule@2@VOutwardEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@QAEAAV01@ABV01@@Z
ConcreteModuleTemplate<ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &ConcreteModuleTemplate<ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::operator=(const ConcreteModuleTemplate<ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &that)
{
	const void *src = &that;
	const unsigned char *base = src ? (const unsigned char *)src + 8 : 0;
	memcpy((unsigned char *)this + 0x0c, base + 4, 12);
	memcpy((unsigned char *)this + 0x18, base + 0x10, 12);
	return *this;
}

// ?clone@?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?OUTWARD_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?OUTWARD_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVOutwardEmissionVelocityModule@2@VOutwardEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVOutwardEmissionVelocityModuleTemplate@2@XZ
OutwardEmissionVelocityModuleTemplate *ConcreteModuleTemplate<ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::clone() const
{
    return (OutwardEmissionVelocityModuleTemplate *)new ConcreteModuleTemplate<ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >(*this);
}

// ?createModule@?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?OUTWARD_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?OUTWARD_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVOutwardEmissionVelocityModule@2@VOutwardEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@UAEPAVOutwardEmissionVelocityModule@2@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@@@Z
OutwardEmissionVelocityModule *ConcreteModuleTemplate<ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::createModule(TrackingPtr<ParticleSystem> &sys)
{
    OutwardEmissionVelocityModule *module =
        (OutwardEmissionVelocityModule *)::operator new(0x34);
    if (module) {
        const void *source = this;
        ((OutwardEmissionVelocityModuleCtorShim *)module)->construct(sys, source);
        initializeOutwardEmissionVelocityModule(module);
        return module;
    }
    return 0;
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?SPHERICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?SPHERICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVSphericalEmissionVelocityModule@2@VSphericalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@QAE@ABV01@@Z
ConcreteModuleTemplate<ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &that)
{
    ((SphericalEmissionVelocityTemplateCopyCtorShim *)this)->construct(&that);
    *(volatile unsigned int *)this = 0x011110cc;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x011110c8;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x011110b4;
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?SPHERICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?SPHERICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVSphericalEmissionVelocityModule@2@VSphericalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleTemplate<ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::ConcreteModuleTemplate()
{
    ((SphericalEmissionVelocityTemplateCtorShim *)this)->construct();
    *(volatile unsigned int *)this = 0x011110cc;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x011110c8;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x011110b4;
}

// ??1?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?SPHERICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?SPHERICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVSphericalEmissionVelocityModule@2@VSphericalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@UAE@XZ
ConcreteModuleTemplate<ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::~ConcreteModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f9cc;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??4?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?SPHERICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?SPHERICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVSphericalEmissionVelocityModule@2@VSphericalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@QAEAAV01@ABV01@@Z
ConcreteModuleTemplate<ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &ConcreteModuleTemplate<ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::operator=(const ConcreteModuleTemplate<ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > &that)
{
	const void *src = &that;
	const unsigned char *base = src ? (const unsigned char *)src + 8 : 0;
	base += 4;
	memcpy((unsigned char *)this + 0x0c, base, 12);
	return *this;
}

// ?clone@?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?SPHERICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?SPHERICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVSphericalEmissionVelocityModule@2@VSphericalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVSphericalEmissionVelocityModuleTemplate@2@XZ
SphericalEmissionVelocityModuleTemplate *ConcreteModuleTemplate<ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::clone() const
{
    return (SphericalEmissionVelocityModuleTemplate *)new ConcreteModuleTemplate<ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >(*this);
}

// ?createModule@?$ConcreteModuleTemplate@V?$ModuleTag@$03$E?SPHERICAL_EMISSION_VELOCITY_MODULE_KEY@FXParticleSystem@@3QBDB$E?SPHERICAL_EMISSION_VELOCITY_MODULE_NAME@2@3QBDBVSphericalEmissionVelocityModule@2@VSphericalEmissionVelocityModuleTemplate@2@V?$DefaultParticleModule@$03@2@V?$DefaultParticleModuleTemplate@$03@2@@FXParticleSystem@@@FXParticleSystem@@UAEPAVSphericalEmissionVelocityModule@2@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@@@Z
SphericalEmissionVelocityModule *ConcreteModuleTemplate<ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > >::createModule(TrackingPtr<ParticleSystem> &sys)
{
    SphericalEmissionVelocityModule *module =
        (SphericalEmissionVelocityModule *)::operator new(0x28);
    if (module) {
        const void *source = this;
        ((SphericalEmissionVelocityModuleCtorShim *)module)->construct(sys, source);
        initializeSphericalEmissionVelocityModule(module);
        return module;
    }
    return 0;
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?BOX_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?BOX_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVBoxEmissionVolumeModule@2@VBoxEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@QAE@ABV01@@Z
ConcreteModuleTemplate<ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &that)
{
    ((BoxEmissionVolumeTemplateCopyCtorShim *)this)->construct(&that);
    *(volatile unsigned int *)this = 0x011111d4;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x011111d0;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x011111bc;
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?BOX_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?BOX_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVBoxEmissionVolumeModule@2@VBoxEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleTemplate<ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::ConcreteModuleTemplate()
{
    volatile unsigned int *slots = (unsigned int *)this;
    slots[1] = 0x0110f9ac;
    _ReadWriteBarrier();
    *((volatile unsigned char *)this + 0x0c) = 0;
    slots[2] = 0x011109cc;
    slots[4] = 0;
    slots[5] = 0;
    slots[6] = 0;
    slots[0] = 0x011111d4;
    slots[1] = 0x011111d0;
    slots[2] = 0x011111bc;
}

// ??1?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?BOX_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?BOX_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVBoxEmissionVolumeModule@2@VBoxEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@UAE@XZ
ConcreteModuleTemplate<ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::~ConcreteModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f9ac;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??4?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?BOX_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?BOX_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVBoxEmissionVolumeModule@2@VBoxEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@QAEAAV01@ABV01@@Z
ConcreteModuleTemplate<ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &ConcreteModuleTemplate<ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::operator=(const ConcreteModuleTemplate<ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &that)
{
	const void *src = &that;
	const unsigned char *base = src ? (const unsigned char *)src + 8 : 0;
	*((unsigned char *)this + 0x0c) = base[4];
	base += 8;
	memcpy((unsigned char *)this + 0x10, base, 12);
	return *this;
}

// ?clone@?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?BOX_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?BOX_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVBoxEmissionVolumeModule@2@VBoxEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVBoxEmissionVolumeModuleTemplate@2@XZ
BoxEmissionVolumeModuleTemplate *ConcreteModuleTemplate<ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::clone() const
{
    return (BoxEmissionVolumeModuleTemplate *)new ConcreteModuleTemplate<ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >(*this);
}

// ?createModule@?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?BOX_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?BOX_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVBoxEmissionVolumeModule@2@VBoxEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@UAEPAVBoxEmissionVolumeModule@2@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@@@Z
BoxEmissionVolumeModule *ConcreteModuleTemplate<ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::createModule(TrackingPtr<ParticleSystem> &sys)
{
    BoxEmissionVolumeModule *module =
        (BoxEmissionVolumeModule *)::operator new(0x30);
    if (module) {
        const void *source = this;
        ((BoxEmissionVolumeModuleCtorShim *)module)->construct(sys, source);
        initializeBoxEmissionVolumeModule(module);
        return module;
    }
    return 0;
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?CYLINDER_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?CYLINDER_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVCylinderEmissionVolumeModule@2@VCylinderEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@QAE@ABV01@@Z
ConcreteModuleTemplate<ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME, CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME, CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &that)
{
    ((CylinderEmissionVolumeTemplateCopyCtorShim *)this)->construct(&that);
    *(volatile unsigned int *)this = 0x0111122c;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01111228;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01111214;
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?CYLINDER_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?CYLINDER_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVCylinderEmissionVolumeModule@2@VCylinderEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleTemplate<ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME, CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::ConcreteModuleTemplate()
{
    volatile unsigned int *slots = (unsigned int *)this;
    slots[1] = 0x0110f9ac;
    _ReadWriteBarrier();
    *((volatile unsigned char *)this + 0x0c) = 0;
    slots[2] = 0x01110a4c;
    slots[4] = 0;
    slots[5] = 0;
    slots[6] = 0;
    slots[7] = 0;
    slots[8] = 0;
    slots[0] = 0x0111122c;
    slots[1] = 0x01111228;
    slots[2] = 0x01111214;
}

// ??1?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?CYLINDER_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?CYLINDER_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVCylinderEmissionVolumeModule@2@VCylinderEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@UAE@XZ
ConcreteModuleTemplate<ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME, CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::~ConcreteModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f9ac;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??4?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?CYLINDER_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?CYLINDER_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVCylinderEmissionVolumeModule@2@VCylinderEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@QAEAAV01@ABV01@@Z
ConcreteModuleTemplate<ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME, CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &ConcreteModuleTemplate<ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME, CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::operator=(const ConcreteModuleTemplate<ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME, CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &that)
{
	const void *src = &that;
	const unsigned char *base = src ? (const unsigned char *)src + 8 : 0;
	*((unsigned char *)this + 0x0c) = base[4];
	*((unsigned int *)((unsigned char *)this + 0x10)) = *(const unsigned int *)(base + 8);
	*((unsigned int *)((unsigned char *)this + 0x14)) = *(const unsigned int *)(base + 0x0c);
	base += 0x10;
	memcpy((unsigned char *)this + 0x18, base, 12);
	return *this;
}

// ?clone@?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?CYLINDER_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?CYLINDER_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVCylinderEmissionVolumeModule@2@VCylinderEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVCylinderEmissionVolumeModuleTemplate@2@XZ
CylinderEmissionVolumeModuleTemplate *ConcreteModuleTemplate<ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME, CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::clone() const
{
    return (CylinderEmissionVolumeModuleTemplate *)new ConcreteModuleTemplate<ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME, CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >(*this);
}

// ?createModule@?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?CYLINDER_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?CYLINDER_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVCylinderEmissionVolumeModule@2@VCylinderEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@UAEPAVCylinderEmissionVolumeModule@2@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@@@Z
CylinderEmissionVolumeModule *ConcreteModuleTemplate<ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME, CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::createModule(TrackingPtr<ParticleSystem> &sys)
{
    CylinderEmissionVolumeModule *module =
        (CylinderEmissionVolumeModule *)::operator new(0x38);
    if (module) {
        const void *source = this;
        ((CylinderEmissionVolumeModuleCtorShim *)module)->construct(sys, source);
        initializeCylinderEmissionVolumeModule(module);
        return module;
    }
    return 0;
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?LIGHTNING_EMISSION_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIGHTNING_EMISSION_MODULE_NAME@2@3QBDBVLightningEmissionModule@2@VLightningEmissionModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@QAE@ABV01@@Z
__declspec(naked) ConcreteModuleTemplate<ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &that)
{
    __asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x04
        __emit 0x85
        __emit 0xc0
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0xac
        __emit 0xf9
        __emit 0x10
        __emit 0x01
        __emit 0x57
        __emit 0xc7
        __emit 0x06
        __emit 0x20
        __emit 0xfc
        __emit 0x10
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x1c
        __emit 0xfc
        __emit 0x10
        __emit 0x01
        __emit 0x74
        __emit 0x05
        __emit 0x83
        __emit 0xc0
        __emit 0x08
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xc0
        __emit 0x8d
        __emit 0x7e
        __emit 0x08
        __emit 0x50
        __emit 0x8b
        __emit 0xcf
        __emit 0xe8
        __emit 0x1c
        __emit 0x1c
        __emit 0xa6
        __emit 0xff
        __emit 0xc7
        __emit 0x07
        __emit 0x40
        __emit 0x12
        __emit 0x11
        __emit 0x01
        __emit 0x5f
        __emit 0xc7
        __emit 0x06
        __emit 0x58
        __emit 0x12
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x54
        __emit 0x12
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?LIGHTNING_EMISSION_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIGHTNING_EMISSION_MODULE_NAME@2@3QBDBVLightningEmissionModule@2@VLightningEmissionModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleTemplate<ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::ConcreteModuleTemplate()
{
    ((LightningEmissionTemplateCtorShim *)this)->construct();
    *(volatile unsigned int *)this = 0x01111258;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01111254;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01111240;
}

ConcreteModuleTemplate<ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::~ConcreteModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f9ac;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??4?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?LIGHTNING_EMISSION_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIGHTNING_EMISSION_MODULE_NAME@2@3QBDBVLightningEmissionModule@2@VLightningEmissionModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@QAEAAV01@ABV01@@Z
ConcreteModuleTemplate<ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &ConcreteModuleTemplate<ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::operator=(const ConcreteModuleTemplate<ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &that)
{
	const void *src = &that;
	const LightningEmissionInfo *info = src ? (const LightningEmissionInfo *)((const unsigned char *)src + 8) : 0;
	LightningEmissionInfo *dest = (LightningEmissionInfo *)((unsigned char *)this + 8);
	dest->operator=(*info);
	return *this;
}

// ?clone@?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?LIGHTNING_EMISSION_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIGHTNING_EMISSION_MODULE_NAME@2@3QBDBVLightningEmissionModule@2@VLightningEmissionModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVLightningEmissionModuleTemplate@2@XZ
LightningEmissionModuleTemplate *ConcreteModuleTemplate<ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::clone() const
{
    return (LightningEmissionModuleTemplate *)new ConcreteModuleTemplate<ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >(*this);
}

// ?createModule@?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?LIGHTNING_EMISSION_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIGHTNING_EMISSION_MODULE_NAME@2@3QBDBVLightningEmissionModule@2@VLightningEmissionModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@UAEPAVLightningEmissionModule@2@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@@@Z
__declspec(naked) LightningEmissionModule *ConcreteModuleTemplate<ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::createModule(TrackingPtr<ParticleSystem> &sys)
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x3b
        __emit 0xbc
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x57
        __emit 0x68
        __emit 0xa8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0xf9
        __emit 0xe8
        __emit 0x8c
        __emit 0x8d
        __emit 0x29
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0x33
        __emit 0xc0
        __emit 0x3b
        __emit 0xf0
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x74
        __emit 0x2a
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x1c
        __emit 0x57
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0xcb
        __emit 0xba
        __emit 0xa3
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0x20
        __emit 0x24
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x14
        __emit 0x1c
        __emit 0x24
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x18
        __emit 0x18
        __emit 0x24
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x1c
        __emit 0x04
        __emit 0x24
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xc6
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x5f
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?LINE_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?LINE_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVLineEmissionVolumeModule@2@VLineEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@QAE@ABV01@@Z
ConcreteModuleTemplate<ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &that)
{
    ((LineEmissionVolumeTemplateCopyCtorShim *)this)->construct(&that);
    *(volatile unsigned int *)this = 0x011111a8;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x011111a4;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01111190;
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?LINE_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?LINE_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVLineEmissionVolumeModule@2@VLineEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleTemplate<ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::ConcreteModuleTemplate()
{
    volatile unsigned int *slots = (unsigned int *)this;
    slots[1] = 0x0110f9ac;
    _ReadWriteBarrier();
    *((volatile unsigned char *)this + 0x0c) = 0;
    slots[2] = 0x0111098c;
    slots[4] = 0;
    slots[5] = 0;
    slots[6] = 0;
    slots[7] = 0;
    slots[8] = 0;
    slots[9] = 0;
    slots[0] = 0x011111a8;
    slots[1] = 0x011111a4;
    slots[2] = 0x01111190;
}

// ??1?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?LINE_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?LINE_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVLineEmissionVolumeModule@2@VLineEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@UAE@XZ
ConcreteModuleTemplate<ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::~ConcreteModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f9ac;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??4?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?LINE_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?LINE_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVLineEmissionVolumeModule@2@VLineEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@QAEAAV01@ABV01@@Z
ConcreteModuleTemplate<ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &ConcreteModuleTemplate<ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::operator=(const ConcreteModuleTemplate<ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &that)
{
	const void *src = &that;
	const unsigned char *base = src ? (const unsigned char *)src + 8 : 0;
	*((unsigned char *)this + 0x0c) = base[4];
	memcpy((unsigned char *)this + 0x10, base + 8, 12);
	memcpy((unsigned char *)this + 0x1c, base + 0x14, 12);
	return *this;
}

// ?clone@?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?LINE_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?LINE_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVLineEmissionVolumeModule@2@VLineEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVLineEmissionVolumeModuleTemplate@2@XZ
LineEmissionVolumeModuleTemplate *ConcreteModuleTemplate<ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::clone() const
{
    return (LineEmissionVolumeModuleTemplate *)new ConcreteModuleTemplate<ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >(*this);
}

// ?createModule@?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?LINE_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?LINE_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVLineEmissionVolumeModule@2@VLineEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@UAEPAVLineEmissionVolumeModule@2@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@@@Z
LineEmissionVolumeModule *ConcreteModuleTemplate<ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::createModule(TrackingPtr<ParticleSystem> &sys)
{
    LineEmissionVolumeModule *module =
        (LineEmissionVolumeModule *)::operator new(0x3c);
    if (module) {
        const void *source = this;
        ((LineEmissionVolumeModuleCtorShim *)module)->construct(sys, source);
        initializeLineEmissionVolumeModule(module);
        return module;
    }
    return 0;
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?SPHERE_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?SPHERE_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVSphereEmissionVolumeModule@2@VSphereEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@QAE@ABV01@@Z
ConcreteModuleTemplate<ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY, SPHERE_EMISSION_VOLUME_MODULE_NAME, SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY, SPHERE_EMISSION_VOLUME_MODULE_NAME, SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &that)
{
    ((SphereEmissionVolumeTemplateCopyCtorShim *)this)->construct(&that);
    *(volatile unsigned int *)this = 0x01111200;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x011111fc;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x011111e8;
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?SPHERE_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?SPHERE_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVSphereEmissionVolumeModule@2@VSphereEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleTemplate<ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY, SPHERE_EMISSION_VOLUME_MODULE_NAME, SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::ConcreteModuleTemplate()
{
    volatile unsigned int *slots = (unsigned int *)this;
    slots[1] = 0x0110f9ac;
    _ReadWriteBarrier();
    *((volatile unsigned char *)this + 0x0c) = 0;
    slots[2] = 0x01110a0c;
    slots[4] = 0;
    slots[0] = 0x01111200;
    slots[1] = 0x011111fc;
    slots[2] = 0x011111e8;
}

// ??1?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?SPHERE_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?SPHERE_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVSphereEmissionVolumeModule@2@VSphereEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@UAE@XZ
ConcreteModuleTemplate<ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY, SPHERE_EMISSION_VOLUME_MODULE_NAME, SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::~ConcreteModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f9ac;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??4?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?SPHERE_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?SPHERE_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVSphereEmissionVolumeModule@2@VSphereEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@QAEAAV01@ABV01@@Z
// Naked→C++: copy +0x0c byte and +0x10 dword via (that? that+8 : 0) intermediates.
ConcreteModuleTemplate<ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY, SPHERE_EMISSION_VOLUME_MODULE_NAME, SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &ConcreteModuleTemplate<ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY, SPHERE_EMISSION_VOLUME_MODULE_NAME, SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::operator=(const ConcreteModuleTemplate<ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY, SPHERE_EMISSION_VOLUME_MODULE_NAME, SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > &that)
{
	const void *src = &that;
	unsigned char *base = src ? (unsigned char *)src + 8 : 0;
	*((unsigned char *)this + 0x0c) = base[4];
	*((unsigned int *)((unsigned char *)this + 0x10)) = *(unsigned int *)(base + 8);
	return *this;
}

// ?clone@?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?SPHERE_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?SPHERE_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVSphereEmissionVolumeModule@2@VSphereEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVSphereEmissionVolumeModuleTemplate@2@XZ
SphereEmissionVolumeModuleTemplate *ConcreteModuleTemplate<ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY, SPHERE_EMISSION_VOLUME_MODULE_NAME, SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::clone() const
{
    return (SphereEmissionVolumeModuleTemplate *)new ConcreteModuleTemplate<ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY, SPHERE_EMISSION_VOLUME_MODULE_NAME, SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >(*this);
}

// ?createModule@?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?SPHERE_EMISSION_VOLUME_MODULE_KEY@FXParticleSystem@@3QBDB$E?SPHERE_EMISSION_VOLUME_MODULE_NAME@2@3QBDBVSphereEmissionVolumeModule@2@VSphereEmissionVolumeModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@UAEPAVSphereEmissionVolumeModule@2@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@@@Z
SphereEmissionVolumeModule *ConcreteModuleTemplate<ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY, SPHERE_EMISSION_VOLUME_MODULE_NAME, SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > >::createModule(TrackingPtr<ParticleSystem> &sys)
{
    SphereEmissionVolumeModule *module =
        (SphereEmissionVolumeModule *)::operator new(0x28);
    if (module) {
        const void *source = this;
        ((SphereEmissionVolumeModuleCtorShim *)module)->construct(sys, source);
        initializeSphereEmissionVolumeModule(module);
        return module;
    }
    return 0;
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?BUTTERFLY_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?BUTTERFLY_DRAW_MODULE_NAME@2@3QBDBVButterflyDrawModule@2@VButterflyDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@QAE@ABV01@@Z
ConcreteModuleTemplate<ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME, ButterflyDrawModule, ButterflyDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME, ButterflyDrawModule, ButterflyDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &that)
{
    ((ButterflyDrawTemplateCopyCtorShim *)this)->construct(&that);
    *(volatile unsigned int *)this = 0x01110e90;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01110e8c;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01110e78;
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?BUTTERFLY_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?BUTTERFLY_DRAW_MODULE_NAME@2@3QBDBVButterflyDrawModule@2@VButterflyDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleTemplate<ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME, ButterflyDrawModule, ButterflyDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::ConcreteModuleTemplate()
{
    ((ButterflyDrawTemplateCtorShim *)this)->construct();
    *(volatile unsigned int *)this = 0x01110e90;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01110e8c;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01110e78;
}

// ??1?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?BUTTERFLY_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?BUTTERFLY_DRAW_MODULE_NAME@2@3QBDBVButterflyDrawModule@2@VButterflyDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@UAE@XZ
ConcreteModuleTemplate<ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME, ButterflyDrawModule, ButterflyDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::~ConcreteModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f97c;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??4?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?BUTTERFLY_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?BUTTERFLY_DRAW_MODULE_NAME@2@3QBDBVButterflyDrawModule@2@VButterflyDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@QAEAAV01@ABV01@@Z
ConcreteModuleTemplate<ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME, ButterflyDrawModule, ButterflyDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &ConcreteModuleTemplate<ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME, ButterflyDrawModule, ButterflyDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::operator=(const ConcreteModuleTemplate<ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME, ButterflyDrawModule, ButterflyDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &that)
{
    return *this;
}

// ?clone@?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?BUTTERFLY_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?BUTTERFLY_DRAW_MODULE_NAME@2@3QBDBVButterflyDrawModule@2@VButterflyDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVButterflyDrawModuleTemplate@2@XZ
ButterflyDrawModuleTemplate *ConcreteModuleTemplate<ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME, ButterflyDrawModule, ButterflyDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::clone() const
{
    return (ButterflyDrawModuleTemplate *)new ConcreteModuleTemplate<ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME, ButterflyDrawModule, ButterflyDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >(*this);
}

// ?createModule@?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?BUTTERFLY_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?BUTTERFLY_DRAW_MODULE_NAME@2@3QBDBVButterflyDrawModule@2@VButterflyDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@UAEPAVButterflyDrawModule@2@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@@@Z
__declspec(naked) ButterflyDrawModule *ConcreteModuleTemplate<ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME, ButterflyDrawModule, ButterflyDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::createModule(TrackingPtr<ParticleSystem> &sys)
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x3b
        __emit 0xbb
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x57
        __emit 0x6a
        __emit 0x1c
        __emit 0x8b
        __emit 0xf9
        __emit 0xe8
        __emit 0xdf
        __emit 0x95
        __emit 0x29
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0x33
        __emit 0xc0
        __emit 0x3b
        __emit 0xf0
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x74
        __emit 0x23
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x1c
        __emit 0x57
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0xae
        __emit 0x25
        __emit 0xa2
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0x68
        __emit 0x1e
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x14
        __emit 0x64
        __emit 0x1e
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x18
        __emit 0x50
        __emit 0x1e
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xc6
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x5f
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?LIGHTNING_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIGHTNING_DRAW_MODULE_NAME@2@3QBDBVLightningDrawModule@2@VLightningDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@QAE@ABV01@@Z
ConcreteModuleTemplate<ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule, LightningDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule, LightningDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &that)
{
    ((LightningDrawTemplateCopyCtorShim *)this)->construct(&that);
    *(volatile unsigned int *)this = 0x01110ebc;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01110eb8;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01110ea4;
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?LIGHTNING_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIGHTNING_DRAW_MODULE_NAME@2@3QBDBVLightningDrawModule@2@VLightningDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleTemplate<ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule, LightningDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::ConcreteModuleTemplate()
{
    ((LightningDrawTemplateCtorShim *)this)->construct();
    *(volatile unsigned int *)this = 0x01110ebc;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01110eb8;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01110ea4;
}

ConcreteModuleTemplate<ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule, LightningDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::~ConcreteModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f97c;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??4?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?LIGHTNING_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIGHTNING_DRAW_MODULE_NAME@2@3QBDBVLightningDrawModule@2@VLightningDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@QAEAAV01@ABV01@@Z
ConcreteModuleTemplate<ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule, LightningDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &ConcreteModuleTemplate<ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule, LightningDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::operator=(const ConcreteModuleTemplate<ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule, LightningDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &that)
{
    const void *source = &that;
    const unsigned char *info = source ? (const unsigned char *)source + 8 : 0;
    ((LightningDrawTemplateAssignShim *)((unsigned char *)this + 8))->assign(info);
    return *this;
}

// ?clone@?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?LIGHTNING_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIGHTNING_DRAW_MODULE_NAME@2@3QBDBVLightningDrawModule@2@VLightningDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVLightningDrawModuleTemplate@2@XZ
LightningDrawModuleTemplate *ConcreteModuleTemplate<ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule, LightningDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::clone() const
{
    return (LightningDrawModuleTemplate *)new ConcreteModuleTemplate<ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule, LightningDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >(*this);
}

// ?createModule@?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?LIGHTNING_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIGHTNING_DRAW_MODULE_NAME@2@3QBDBVLightningDrawModule@2@VLightningDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@UAEPAVLightningDrawModule@2@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@@@Z
__declspec(naked) LightningDrawModule *ConcreteModuleTemplate<ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule, LightningDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::createModule(TrackingPtr<ParticleSystem> &sys)
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x7b
        __emit 0xbb
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x57
        __emit 0x68
        __emit 0xe4
        __emit 0x08
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0xf9
        __emit 0xe8
        __emit 0xbc
        __emit 0x94
        __emit 0x29
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0x33
        __emit 0xc0
        __emit 0x3b
        __emit 0xf0
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x74
        __emit 0x23
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x1c
        __emit 0x57
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0xd7
        __emit 0x1c
        __emit 0xa4
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0xe0
        __emit 0x1e
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x14
        __emit 0xdc
        __emit 0x1e
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x18
        __emit 0xc8
        __emit 0x1e
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xc6
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x5f
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?QUAD_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?QUAD_DRAW_MODULE_NAME@2@3QBDBVQuadDrawModule@2@VQuadDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@QAE@ABV01@@Z
ConcreteModuleTemplate<ModuleTag<6, QUAD_DRAW_MODULE_KEY, QUAD_DRAW_MODULE_NAME, QuadDrawModule, QuadDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<6, QUAD_DRAW_MODULE_KEY, QUAD_DRAW_MODULE_NAME, QuadDrawModule, QuadDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &that)
{
    ((QuadDrawTemplateCopyCtorShim *)this)->construct(&that);
    *(volatile unsigned int *)this = 0x01110e64;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01110e60;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01110e4c;
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?QUAD_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?QUAD_DRAW_MODULE_NAME@2@3QBDBVQuadDrawModule@2@VQuadDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleTemplate<ModuleTag<6, QUAD_DRAW_MODULE_KEY, QUAD_DRAW_MODULE_NAME, QuadDrawModule, QuadDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::ConcreteModuleTemplate()
{
    ((QuadDrawTemplateCtorShim *)this)->construct();
    *(volatile unsigned int *)this = 0x01110e64;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01110e60;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01110e4c;
}

// ??1?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?QUAD_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?QUAD_DRAW_MODULE_NAME@2@3QBDBVQuadDrawModule@2@VQuadDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@UAE@XZ
ConcreteModuleTemplate<ModuleTag<6, QUAD_DRAW_MODULE_KEY, QUAD_DRAW_MODULE_NAME, QuadDrawModule, QuadDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::~ConcreteModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f97c;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??4?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?QUAD_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?QUAD_DRAW_MODULE_NAME@2@3QBDBVQuadDrawModule@2@VQuadDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@QAEAAV01@ABV01@@Z
ConcreteModuleTemplate<ModuleTag<6, QUAD_DRAW_MODULE_KEY, QUAD_DRAW_MODULE_NAME, QuadDrawModule, QuadDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &ConcreteModuleTemplate<ModuleTag<6, QUAD_DRAW_MODULE_KEY, QUAD_DRAW_MODULE_NAME, QuadDrawModule, QuadDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::operator=(const ConcreteModuleTemplate<ModuleTag<6, QUAD_DRAW_MODULE_KEY, QUAD_DRAW_MODULE_NAME, QuadDrawModule, QuadDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &that)
{
    return *this;
}

// ?clone@?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?QUAD_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?QUAD_DRAW_MODULE_NAME@2@3QBDBVQuadDrawModule@2@VQuadDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVQuadDrawModuleTemplate@2@XZ
QuadDrawModuleTemplate *ConcreteModuleTemplate<ModuleTag<6, QUAD_DRAW_MODULE_KEY, QUAD_DRAW_MODULE_NAME, QuadDrawModule, QuadDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::clone() const
{
    return (QuadDrawModuleTemplate *)new ConcreteModuleTemplate<ModuleTag<6, QUAD_DRAW_MODULE_KEY, QUAD_DRAW_MODULE_NAME, QuadDrawModule, QuadDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >(*this);
}

// ?createModule@?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?QUAD_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?QUAD_DRAW_MODULE_NAME@2@3QBDBVQuadDrawModule@2@VQuadDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@UAEPAVQuadDrawModule@2@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@@@Z
__declspec(naked) QuadDrawModule *ConcreteModuleTemplate<ModuleTag<6, QUAD_DRAW_MODULE_KEY, QUAD_DRAW_MODULE_NAME, QuadDrawModule, QuadDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::createModule(TrackingPtr<ParticleSystem> &sys)
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x1b
        __emit 0xbb
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x57
        __emit 0x6a
        __emit 0x1c
        __emit 0x8b
        __emit 0xf9
        __emit 0xe8
        __emit 0x6f
        __emit 0x96
        __emit 0x29
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0x33
        __emit 0xc0
        __emit 0x3b
        __emit 0xf0
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x74
        __emit 0x23
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x1c
        __emit 0x57
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0xce
        __emit 0xf1
        __emit 0xa5
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0x2c
        __emit 0x1e
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x14
        __emit 0x28
        __emit 0x1e
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x18
        __emit 0x14
        __emit 0x1e
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xc6
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x5f
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?RENDEROBJECT_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_DRAW_MODULE_NAME@2@3QBDBVRenderObjectDrawModule@2@VRenderObjectDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@QAE@ABV01@@Z
ConcreteModuleTemplate<ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY, RENDEROBJECT_DRAW_MODULE_NAME, RenderObjectDrawModule, RenderObjectDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY, RENDEROBJECT_DRAW_MODULE_NAME, RenderObjectDrawModule, RenderObjectDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &that)
{
    ((RenderObjectDrawTemplateCopyCtorShim *)this)->construct(&that);
    *(volatile unsigned int *)this = 0x01111398;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01111394;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01111380;
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?RENDEROBJECT_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_DRAW_MODULE_NAME@2@3QBDBVRenderObjectDrawModule@2@VRenderObjectDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleTemplate<ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY, RENDEROBJECT_DRAW_MODULE_NAME, RenderObjectDrawModule, RenderObjectDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::ConcreteModuleTemplate()
{
    ((RenderObjectDrawTemplateCtorShim *)this)->construct();
    *(volatile unsigned int *)this = 0x01111398;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01111394;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01111380;
}

// ??1?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?RENDEROBJECT_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_DRAW_MODULE_NAME@2@3QBDBVRenderObjectDrawModule@2@VRenderObjectDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@UAE@XZ
ConcreteModuleTemplate<ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY, RENDEROBJECT_DRAW_MODULE_NAME, RenderObjectDrawModule, RenderObjectDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::~ConcreteModuleTemplate()
{
}

// ??4?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?RENDEROBJECT_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_DRAW_MODULE_NAME@2@3QBDBVRenderObjectDrawModule@2@VRenderObjectDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@QAEAAV01@ABV01@@Z
ConcreteModuleTemplate<ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY, RENDEROBJECT_DRAW_MODULE_NAME, RenderObjectDrawModule, RenderObjectDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &ConcreteModuleTemplate<ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY, RENDEROBJECT_DRAW_MODULE_NAME, RenderObjectDrawModule, RenderObjectDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::operator=(const ConcreteModuleTemplate<ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY, RENDEROBJECT_DRAW_MODULE_NAME, RenderObjectDrawModule, RenderObjectDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &that)
{
    const void *source = &that;
    const unsigned char *info = source ? (const unsigned char *)source + 8 : 0;
    ((RenderObjectDrawTemplateAssignShim *)((unsigned char *)this + 8))->assign(info);
    return *this;
}

// ?clone@?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?RENDEROBJECT_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_DRAW_MODULE_NAME@2@3QBDBVRenderObjectDrawModule@2@VRenderObjectDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVRenderObjectDrawModuleTemplate@2@XZ
RenderObjectDrawModuleTemplate *ConcreteModuleTemplate<ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY, RENDEROBJECT_DRAW_MODULE_NAME, RenderObjectDrawModule, RenderObjectDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::clone() const
{
    return (RenderObjectDrawModuleTemplate *)new ConcreteModuleTemplate<ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY, RENDEROBJECT_DRAW_MODULE_NAME, RenderObjectDrawModule, RenderObjectDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >(*this);
}

// ?createModule@?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?RENDEROBJECT_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_DRAW_MODULE_NAME@2@3QBDBVRenderObjectDrawModule@2@VRenderObjectDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@UAEPAVRenderObjectDrawModule@2@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@@@Z
__declspec(naked) RenderObjectDrawModule *ConcreteModuleTemplate<ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY, RENDEROBJECT_DRAW_MODULE_NAME, RenderObjectDrawModule, RenderObjectDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::createModule(TrackingPtr<ParticleSystem> &sys)
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x5b
        __emit 0xbb
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x57
        __emit 0x6a
        __emit 0x5c
        __emit 0x8b
        __emit 0xf9
        __emit 0xe8
        __emit 0x4f
        __emit 0x95
        __emit 0x29
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0x33
        __emit 0xc0
        __emit 0x3b
        __emit 0xf0
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x74
        __emit 0x23
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x1c
        __emit 0x57
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x20
        __emit 0x36
        __emit 0xa3
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0xa4
        __emit 0x1e
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x14
        __emit 0xa0
        __emit 0x1e
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x18
        __emit 0x8c
        __emit 0x1e
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xc6
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x5f
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?STREAK_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?STREAK_DRAW_MODULE_NAME@2@3QBDBVStreakDrawModule@2@VStreakDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@QAE@ABV01@@Z
ConcreteModuleTemplate<ModuleTag<6, STREAK_DRAW_MODULE_KEY, STREAK_DRAW_MODULE_NAME, StreakDrawModule, StreakDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<6, STREAK_DRAW_MODULE_KEY, STREAK_DRAW_MODULE_NAME, StreakDrawModule, StreakDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &that)
{
    ((StreakDrawTemplateCopyCtorShim *)this)->construct(&that);
    *(volatile unsigned int *)this = 0x01110e38;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01110e34;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01110e20;
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?STREAK_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?STREAK_DRAW_MODULE_NAME@2@3QBDBVStreakDrawModule@2@VStreakDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleTemplate<ModuleTag<6, STREAK_DRAW_MODULE_KEY, STREAK_DRAW_MODULE_NAME, StreakDrawModule, StreakDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::ConcreteModuleTemplate()
{
    ((StreakDrawTemplateCtorShim *)this)->construct();
    *(volatile unsigned int *)this = 0x01110e38;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01110e34;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01110e20;
}

// ??1?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?STREAK_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?STREAK_DRAW_MODULE_NAME@2@3QBDBVStreakDrawModule@2@VStreakDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@UAE@XZ
ConcreteModuleTemplate<ModuleTag<6, STREAK_DRAW_MODULE_KEY, STREAK_DRAW_MODULE_NAME, StreakDrawModule, StreakDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::~ConcreteModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f97c;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??4?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?STREAK_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?STREAK_DRAW_MODULE_NAME@2@3QBDBVStreakDrawModule@2@VStreakDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@QAEAAV01@ABV01@@Z
ConcreteModuleTemplate<ModuleTag<6, STREAK_DRAW_MODULE_KEY, STREAK_DRAW_MODULE_NAME, StreakDrawModule, StreakDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &ConcreteModuleTemplate<ModuleTag<6, STREAK_DRAW_MODULE_KEY, STREAK_DRAW_MODULE_NAME, StreakDrawModule, StreakDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::operator=(const ConcreteModuleTemplate<ModuleTag<6, STREAK_DRAW_MODULE_KEY, STREAK_DRAW_MODULE_NAME, StreakDrawModule, StreakDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > > &that)
{
    return *this;
}

// ?clone@?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?STREAK_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?STREAK_DRAW_MODULE_NAME@2@3QBDBVStreakDrawModule@2@VStreakDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVStreakDrawModuleTemplate@2@XZ
StreakDrawModuleTemplate *ConcreteModuleTemplate<ModuleTag<6, STREAK_DRAW_MODULE_KEY, STREAK_DRAW_MODULE_NAME, StreakDrawModule, StreakDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::clone() const
{
    return (StreakDrawModuleTemplate *)new ConcreteModuleTemplate<ModuleTag<6, STREAK_DRAW_MODULE_KEY, STREAK_DRAW_MODULE_NAME, StreakDrawModule, StreakDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >(*this);
}

// ?createModule@?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?STREAK_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?STREAK_DRAW_MODULE_NAME@2@3QBDBVStreakDrawModule@2@VStreakDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@V?$DefaultParticleModuleTemplate@$05@2@@FXParticleSystem@@@FXParticleSystem@@UAEPAVStreakDrawModule@2@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@@@Z
__declspec(naked) StreakDrawModule *ConcreteModuleTemplate<ModuleTag<6, STREAK_DRAW_MODULE_KEY, STREAK_DRAW_MODULE_NAME, StreakDrawModule, StreakDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > >::createModule(TrackingPtr<ParticleSystem> &sys)
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xfb
        __emit 0xba
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x57
        __emit 0x6a
        __emit 0x1c
        __emit 0x8b
        __emit 0xf9
        __emit 0xe8
        __emit 0xff
        __emit 0x96
        __emit 0x29
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0x33
        __emit 0xc0
        __emit 0x3b
        __emit 0xf0
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x74
        __emit 0x23
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x1c
        __emit 0x57
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0xd1
        __emit 0xe3
        __emit 0xa5
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0xf0
        __emit 0x1d
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x14
        __emit 0xec
        __emit 0x1d
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x18
        __emit 0xd8
        __emit 0x1d
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xc6
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x5f
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$07$E?LIFE_EVENT_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIFE_EVENT_MODULE_NAME@2@3QBDBVLifeEventModule@2@VLifeEventModuleTemplate@2@VParticleLifeEventModule@2@VParticleLifeEventModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@QAE@ABV01@@Z
ConcreteModuleTemplate<ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule, ParticleLifeEventModuleTemplate> >::ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule, ParticleLifeEventModuleTemplate> > &that)
{
    ((LifeEventTemplateCopyCtorShim *)this)->construct(&that);
    *(volatile unsigned int *)this = 0x01111424;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01111420;
    *(volatile unsigned int *)((unsigned char *)this + 12) = 0x0111140c;
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$07$E?LIFE_EVENT_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIFE_EVENT_MODULE_NAME@2@3QBDBVLifeEventModule@2@VLifeEventModuleTemplate@2@VParticleLifeEventModule@2@VParticleLifeEventModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleTemplate<ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule, ParticleLifeEventModuleTemplate> >::ConcreteModuleTemplate()
{
    ((LifeEventTemplateCtorShim *)this)->construct();
    *(volatile unsigned int *)this = 0x01111424;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01111420;
    *(volatile unsigned int *)((unsigned char *)this + 12) = 0x0111140c;
}

// ??1?$ConcreteModuleTemplate@V?$ModuleTag@$07$E?LIFE_EVENT_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIFE_EVENT_MODULE_NAME@2@3QBDBVLifeEventModule@2@VLifeEventModuleTemplate@2@VParticleLifeEventModule@2@VParticleLifeEventModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@UAE@XZ
ConcreteModuleTemplate<ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule, ParticleLifeEventModuleTemplate> >::~ConcreteModuleTemplate()
{
}

// ?clone@?$ConcreteModuleTemplate@V?$ModuleTag@$07$E?LIFE_EVENT_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIFE_EVENT_MODULE_NAME@2@3QBDBVLifeEventModule@2@VLifeEventModuleTemplate@2@VParticleLifeEventModule@2@VParticleLifeEventModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVLifeEventModuleTemplate@2@XZ
LifeEventModuleTemplate *ConcreteModuleTemplate<ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule, ParticleLifeEventModuleTemplate> >::clone() const
{
    return (LifeEventModuleTemplate *)new ConcreteModuleTemplate<ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule, ParticleLifeEventModuleTemplate> >(*this);
}

// ?createModule@?$ConcreteModuleTemplate@V?$ModuleTag@$07$E?LIFE_EVENT_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIFE_EVENT_MODULE_NAME@2@3QBDBVLifeEventModule@2@VLifeEventModuleTemplate@2@VParticleLifeEventModule@2@VParticleLifeEventModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@UAEPAVLifeEventModule@2@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@@@Z
__declspec(naked) LifeEventModule *ConcreteModuleTemplate<ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule, ParticleLifeEventModuleTemplate> >::createModule(TrackingPtr<ParticleSystem> &sys)
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xfb
        __emit 0xbb
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x57
        __emit 0x6a
        __emit 0x40
        __emit 0x8b
        __emit 0xf9
        __emit 0xe8
        __emit 0x6f
        __emit 0x92
        __emit 0x29
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0x33
        __emit 0xc0
        __emit 0x3b
        __emit 0xf0
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x74
        __emit 0x2a
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x1c
        __emit 0x57
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0x76
        __emit 0xbf
        __emit 0xa4
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0x90
        __emit 0x21
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x14
        __emit 0x8c
        __emit 0x21
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x18
        __emit 0x88
        __emit 0x21
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x20
        __emit 0x74
        __emit 0x21
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xc6
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x5f
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$07$E?TERRAIN_COLLISION_MODULE_KEY@FXParticleSystem@@3QBDB$E?TERRAIN_COLLISION_MODULE_NAME@2@3QBDBVTerrainCollisionModule@2@VTerrainCollisionModuleTemplate@2@VParticleTerrainCollisionModule@2@VParticleTerrainCollisionModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@QAE@ABV01@@Z
ConcreteModuleTemplate<ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME, TerrainCollisionModule, TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule, ParticleTerrainCollisionModuleTemplate> >::ConcreteModuleTemplate(const ConcreteModuleTemplate<ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME, TerrainCollisionModule, TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule, ParticleTerrainCollisionModuleTemplate> > &that)
{
    ((TerrainCollisionTemplateCopyCtorShim *)this)->construct(&that);
    *(volatile unsigned int *)this = 0x01111450;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x0111144c;
    *(volatile unsigned int *)((unsigned char *)this + 12) = 0x01111438;
}

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$07$E?TERRAIN_COLLISION_MODULE_KEY@FXParticleSystem@@3QBDB$E?TERRAIN_COLLISION_MODULE_NAME@2@3QBDBVTerrainCollisionModule@2@VTerrainCollisionModuleTemplate@2@VParticleTerrainCollisionModule@2@VParticleTerrainCollisionModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleTemplate<ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME, TerrainCollisionModule, TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule, ParticleTerrainCollisionModuleTemplate> >::ConcreteModuleTemplate()
{
    ((TerrainCollisionTemplateCtorShim *)this)->construct();
    *(volatile unsigned int *)this = 0x01111450;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x0111144c;
    *(volatile unsigned int *)((unsigned char *)this + 12) = 0x01111438;
}

// ??1?$ConcreteModuleTemplate@V?$ModuleTag@$07$E?TERRAIN_COLLISION_MODULE_KEY@FXParticleSystem@@3QBDB$E?TERRAIN_COLLISION_MODULE_NAME@2@3QBDBVTerrainCollisionModule@2@VTerrainCollisionModuleTemplate@2@VParticleTerrainCollisionModule@2@VParticleTerrainCollisionModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@UAE@XZ
ConcreteModuleTemplate<ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME, TerrainCollisionModule, TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule, ParticleTerrainCollisionModuleTemplate> >::~ConcreteModuleTemplate()
{
}

// ?clone@?$ConcreteModuleTemplate@V?$ModuleTag@$07$E?TERRAIN_COLLISION_MODULE_KEY@FXParticleSystem@@3QBDB$E?TERRAIN_COLLISION_MODULE_NAME@2@3QBDBVTerrainCollisionModule@2@VTerrainCollisionModuleTemplate@2@VParticleTerrainCollisionModule@2@VParticleTerrainCollisionModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@UBEPAVTerrainCollisionModuleTemplate@2@XZ
TerrainCollisionModuleTemplate *ConcreteModuleTemplate<ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME, TerrainCollisionModule, TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule, ParticleTerrainCollisionModuleTemplate> >::clone() const
{
    return (TerrainCollisionModuleTemplate *)new ConcreteModuleTemplate<ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME, TerrainCollisionModule, TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule, ParticleTerrainCollisionModuleTemplate> >(*this);
}

// ?createModule@?$ConcreteModuleTemplate@V?$ModuleTag@$07$E?TERRAIN_COLLISION_MODULE_KEY@FXParticleSystem@@3QBDB$E?TERRAIN_COLLISION_MODULE_NAME@2@3QBDBVTerrainCollisionModule@2@VTerrainCollisionModuleTemplate@2@VParticleTerrainCollisionModule@2@VParticleTerrainCollisionModuleTemplate@2@@FXParticleSystem@@@FXParticleSystem@@UAEPAVTerrainCollisionModule@2@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@@@Z
__declspec(naked) TerrainCollisionModule *ConcreteModuleTemplate<ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME, TerrainCollisionModule, TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule, ParticleTerrainCollisionModuleTemplate> >::createModule(TrackingPtr<ParticleSystem> &sys)
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x1b
        __emit 0xbc
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x57
        __emit 0x6a
        __emit 0x44
        __emit 0x8b
        __emit 0xf9
        __emit 0xe8
        __emit 0xdf
        __emit 0x91
        __emit 0x29
        __emit 0x00
        __emit 0x8b
        __emit 0xf0
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0x33
        __emit 0xc0
        __emit 0x3b
        __emit 0xf0
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x74
        __emit 0x2a
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x1c
        __emit 0x57
        __emit 0x50
        __emit 0x8b
        __emit 0xce
        __emit 0xe8
        __emit 0xdc
        __emit 0x00
        __emit 0xa4
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0xc0
        __emit 0x21
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x14
        __emit 0xbc
        __emit 0x21
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x18
        __emit 0xb8
        __emit 0x21
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x20
        __emit 0xa4
        __emit 0x21
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0xc6
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x5f
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ??0?$ConcreteModuleTemplate@UOrthoEmissionVelocityModuleTag@FXParticleSystem@@@FXParticleSystem@@QAE@ABV01@@Z
ConcreteModuleTemplate<OrthoEmissionVelocityModuleTag>::ConcreteModuleTemplate(const ConcreteModuleTemplate<OrthoEmissionVelocityModuleTag> &that)
{
    ((OrthoEmissionVelocityTemplateCopyCtorShim *)this)->construct(&that);
    *(volatile unsigned int *)this = 0x011110a0;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x0111109c;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01111088;
}

// ??0?$ConcreteModuleTemplate@UOrthoEmissionVelocityModuleTag@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleTemplate<OrthoEmissionVelocityModuleTag>::ConcreteModuleTemplate()
{
    ((OrthoEmissionVelocityTemplateCtorShim *)this)->construct();
    *(volatile unsigned int *)this = 0x011110a0;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x0111109c;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01111088;
}

ConcreteModuleTemplate<OrthoEmissionVelocityModuleTag>::~ConcreteModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f9cc;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??4?$ConcreteModuleTemplate@UOrthoEmissionVelocityModuleTag@FXParticleSystem@@@FXParticleSystem@@QAEAAV01@ABV01@@Z
// Naked→C++: retail only calls OrthoEmissionVelocityModuleTemplate::operator= then returns *this.
ConcreteModuleTemplate<OrthoEmissionVelocityModuleTag> &ConcreteModuleTemplate<OrthoEmissionVelocityModuleTag>::operator=(const ConcreteModuleTemplate<OrthoEmissionVelocityModuleTag> &that)
{
	((OrthoEmissionVelocityModuleTemplate *)this)->operator=(*(const OrthoEmissionVelocityModuleTemplate *)&that);
	return *this;
}

// ?clone@?$ConcreteModuleTemplate@UOrthoEmissionVelocityModuleTag@FXParticleSystem@@@FXParticleSystem@@UBEPAVOrthoEmissionVelocityModuleTemplate@2@XZ
OrthoEmissionVelocityModuleTemplate *ConcreteModuleTemplate<OrthoEmissionVelocityModuleTag>::clone() const
{
    return (OrthoEmissionVelocityModuleTemplate *)new ConcreteModuleTemplate<OrthoEmissionVelocityModuleTag>(*this);
}

// ?createModule@?$ConcreteModuleTemplate@UOrthoEmissionVelocityModuleTag@FXParticleSystem@@@FXParticleSystem@@UAEPAVOrthoEmissionVelocityModule@2@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@@@Z
OrthoEmissionVelocityModule *ConcreteModuleTemplate<OrthoEmissionVelocityModuleTag>::createModule(TrackingPtr<ParticleSystem> &sys)
{
    OrthoEmissionVelocityModule *module =
        (OrthoEmissionVelocityModule *)::operator new(0x40);
    if (module) {
        const void *source = this;
        ((OrthoEmissionVelocityModuleCtorShim *)module)->construct(sys, source);
        initializeOrthoEmissionVelocityModule(module);
        return module;
    }
    return 0;
}

// ??0?$ConcreteModuleTemplate@UPointEmissionVolumeModuleTag@FXParticleSystem@@@FXParticleSystem@@QAE@ABV01@@Z
ConcreteModuleTemplate<PointEmissionVolumeModuleTag>::ConcreteModuleTemplate(const ConcreteModuleTemplate<PointEmissionVolumeModuleTag> &that)
{
    ((PointEmissionVolumeTemplateCopyCtorShim *)this)->construct(&that);
    *(volatile unsigned int *)this = 0x0111117c;
    *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01111178;
    *(volatile unsigned int *)((unsigned char *)this + 8) = 0x01111164;
}

// ??0?$ConcreteModuleTemplate@UPointEmissionVolumeModuleTag@FXParticleSystem@@@FXParticleSystem@@QAE@XZ
ConcreteModuleTemplate<PointEmissionVolumeModuleTag>::ConcreteModuleTemplate()
{
	volatile unsigned int *vtableSlots = (unsigned int *)this;
	vtableSlots[1] = 0x0110f9ac;
	vtableSlots[2] = 0x0110f980;
	*((volatile unsigned char *)this + 0x0c) = 0;
	vtableSlots[0] = 0x0111117c;
	vtableSlots[1] = 0x01111178;
	vtableSlots[2] = 0x01111164;
}

ConcreteModuleTemplate<PointEmissionVolumeModuleTag>::~ConcreteModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f9ac;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??4?$ConcreteModuleTemplate@UPointEmissionVolumeModuleTag@FXParticleSystem@@@FXParticleSystem@@QAEAAV01@ABV01@@Z
// Naked→C++: copy byte at +0x0c via (that? that+8 : 0)[4] (MSVC 7.1 shape).
ConcreteModuleTemplate<PointEmissionVolumeModuleTag> &ConcreteModuleTemplate<PointEmissionVolumeModuleTag>::operator=(const ConcreteModuleTemplate<PointEmissionVolumeModuleTag> &that)
{
	const ConcreteModuleTemplate<PointEmissionVolumeModuleTag> *src = &that;
	unsigned char *base = src ? (unsigned char *)src + 8 : 0;
	*((unsigned char *)this + 0x0c) = base[4];
	return *this;
}

// ?clone@?$ConcreteModuleTemplate@UPointEmissionVolumeModuleTag@FXParticleSystem@@@FXParticleSystem@@UBEPAVPointEmissionVolumeModuleTemplate@2@XZ
PointEmissionVolumeModuleTemplate *ConcreteModuleTemplate<PointEmissionVolumeModuleTag>::clone() const
{
    return (PointEmissionVolumeModuleTemplate *)new ConcreteModuleTemplate<PointEmissionVolumeModuleTag>(*this);
}

// ?createModule@?$ConcreteModuleTemplate@UPointEmissionVolumeModuleTag@FXParticleSystem@@@FXParticleSystem@@UAEPAVPointEmissionVolumeModule@2@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@@@Z
PointEmissionVolumeModule *ConcreteModuleTemplate<PointEmissionVolumeModuleTag>::createModule(TrackingPtr<ParticleSystem> &sys)
{
    PointEmissionVolumeModule *module =
        (PointEmissionVolumeModule *)::operator new(0x24);
    if (module) {
        const void *source = this;
        ((PointEmissionVolumeModuleCtorShim *)module)->construct(sys, source);
        initializePointEmissionVolumeModule(module);
        return module;
    }
    return 0;
}

// ??0BoxEmissionVolumeModuleTemplate@FXParticleSystem@@QAE@XZ
BoxEmissionVolumeModuleTemplate::BoxEmissionVolumeModuleTemplate()
    : CategoryModuleTemplate<5>(), BoxEmissionVolumeInfo()
{}


// ??0ButterflyDrawModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
ButterflyDrawModuleTemplate::ButterflyDrawModuleTemplate(const ButterflyDrawModuleTemplate &that)
    : CategoryModuleTemplate<6>(that), ButterflyDrawModuleInfo(that)
{}

// ??0ButterflyDrawModuleTemplate@FXParticleSystem@@QAE@XZ
ButterflyDrawModuleTemplate::ButterflyDrawModuleTemplate() {}

// ??0CylinderEmissionVolumeModuleTemplate@FXParticleSystem@@QAE@XZ
CylinderEmissionVolumeModuleTemplate::CylinderEmissionVolumeModuleTemplate()
    : CategoryModuleTemplate<5>(), CylinderEmissionVolumeInfo()
{}


// ??0EmissionVelocityInfo@FXParticleSystem@@QAE@ABV01@@Z
EmissionVelocityInfo::EmissionVelocityInfo(const EmissionVelocityInfo &that)
{
}

// ??0CylindricalEmissionVelocityInfo@FXParticleSystem@@QAE@XZ
CylindricalEmissionVelocityInfo::CylindricalEmissionVelocityInfo()
    : EmissionVelocityInfo()
    , m_var0()
    , m_var1()
{
    m_var0.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
    m_var1.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
}

// ??0CylindricalEmissionVelocityModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
CylindricalEmissionVelocityModuleTemplate::CylindricalEmissionVelocityModuleTemplate(const CylindricalEmissionVelocityModuleTemplate &that)
    : CategoryModuleTemplate<4>(that), CylindricalEmissionVelocityInfo(that)
{}

// ??0CylindricalEmissionVelocityModuleTemplate@FXParticleSystem@@QAE@XZ
CylindricalEmissionVelocityModuleTemplate::CylindricalEmissionVelocityModuleTemplate()
    : CategoryModuleTemplate<4>(), CylindricalEmissionVelocityInfo()
{}


// ??0DefaultAlphaModuleInfo@FXParticleSystem@@QAE@ABV01@@Z
// compiler-generated: set vtable, rep movsd m_alphaKey[8]

// ??0DefaultAlphaModuleInfo@FXParticleSystem@@QAE@XZ
// Body in DefaultAlphaModuleInfoCtorThunk.cpp (SEH array-ctor; exact retail bytes).
// Keep RandomAlphaKeyframe default-ctor COMDAT in this TU (was only referenced
// by the old C++ DefaultAlphaModuleInfo default ctor).
void _force_RandomAlphaKeyframe_ctor(RandomAlphaKeyframe *p)
{
    RandomAlphaKeyframe tmp;
    *p = tmp;
}

// ??0DefaultColorModuleInfo@FXParticleSystem@@QAE@ABV01@@Z
// compiler-generated: set vtable, rep movsd m_colorKey[8], copy m_colorScale fields

// ??0DefaultColorModuleInfo@FXParticleSystem@@QAE@XZ
DefaultColorModuleInfo::DefaultColorModuleInfo()
{
}

// These functions force compiler-generated copy ctor COMDATs into this .obj.
// Non-static so MSVC cannot dead-code-eliminate them.
void _DefaultAlphaModuleInfo_copy(DefaultAlphaModuleInfo *dst, const DefaultAlphaModuleInfo &src) { DefaultAlphaModuleInfo copy(src); *dst = copy; }
void _DefaultColorModuleInfo_copy(DefaultColorModuleInfo *dst, const DefaultColorModuleInfo &src) { DefaultColorModuleInfo copy(src); *dst = copy; }

// ??0DefaultPhysicsModuleInfo@FXParticleSystem@@QAE@ABV01@@Z
DefaultPhysicsModuleInfo::DefaultPhysicsModuleInfo(const DefaultPhysicsModuleInfo &that)
    : m_field0(that.m_field0)
    , m_field1(that.m_field1)
    , m_field2(that.m_field2)
    , m_field3(that.m_field3)
    , m_var1(that.m_var1)
{
}

// ??0DefaultPhysicsModuleInfo@FXParticleSystem@@QAE@XZ
// Body in DefaultPhysicsModuleInfoCtorThunk.cpp (exact retail SEH bytes).

// ??0DefaultUpdateModuleInfo@FXParticleSystem@@QAE@ABV01@@Z
DefaultUpdateModuleInfo::DefaultUpdateModuleInfo(const DefaultUpdateModuleInfo &that)
    : m_var0(that.m_var0)
    , m_var1(that.m_var1)
    , m_var2(that.m_var2)
    , m_var3(that.m_var3)
    , m_var4(that.m_var4)
    , m_extra(that.m_extra)
{
}

// ??0DefaultUpdateModuleInfo@FXParticleSystem@@QAE@XZ
// Body in DefaultUpdateModuleInfoCtorThunk.cpp (exact retail SEH bytes).

// ??0LifeEventModuleInfo@FXParticleSystem@@QAE@ABV01@@Z
__declspec(naked) LifeEventModuleInfo::LifeEventModuleInfo(const LifeEventModuleInfo &that)
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xb8
        __emit 0xad
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x57
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x7c
        __emit 0x24
        __emit 0x1c
        __emit 0x8d
        __emit 0x47
        __emit 0x04
        __emit 0x50
        __emit 0x8d
        __emit 0x4e
        __emit 0x04
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x06
        __emit 0x78
        __emit 0x12
        __emit 0x11
        __emit 0x01
        __emit 0xe8
        __emit 0x04
        __emit 0x9d
        __emit 0x2a
        __emit 0x00
        __emit 0x8d
        __emit 0x4f
        __emit 0x08
        __emit 0x8b
        __emit 0x01
        __emit 0x8d
        __emit 0x56
        __emit 0x08
        __emit 0x89
        __emit 0x02
        __emit 0x8b
        __emit 0x41
        __emit 0x04
        __emit 0x89
        __emit 0x42
        __emit 0x04
        __emit 0x8b
        __emit 0x49
        __emit 0x08
        __emit 0x89
        __emit 0x4a
        __emit 0x08
        __emit 0x8b
        __emit 0x57
        __emit 0x14
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x89
        __emit 0x56
        __emit 0x14
        __emit 0x5f
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ??0LifeEventModuleInfo@FXParticleSystem@@QAE@XZ
__declspec(naked) LifeEventModuleInfo::LifeEventModuleInfo()
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xe3
        __emit 0xc8
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x33
        __emit 0xc0
        __emit 0xc7
        __emit 0x06
        __emit 0x78
        __emit 0x12
        __emit 0x11
        __emit 0x01
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x89
        __emit 0x46
        __emit 0x04
        __emit 0x6a
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x08
        __emit 0x50
        __emit 0x89
        __emit 0x01
        __emit 0x89
        __emit 0x41
        __emit 0x04
        __emit 0x89
        __emit 0x41
        __emit 0x08
        __emit 0x50
        __emit 0xc6
        __emit 0x44
        __emit 0x24
        __emit 0x1c
        __emit 0x01
        __emit 0x89
        __emit 0x46
        __emit 0x14
        __emit 0xe8
        __emit 0x00
        __emit 0xa5
        __emit 0xa0
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc3
    }
}

// ??0LifeEventModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
__declspec(naked) LifeEventModuleTemplate::LifeEventModuleTemplate(const LifeEventModuleTemplate &that)
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x18
        __emit 0xae
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x85
        __emit 0xc0
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x5c
        __emit 0x37
        __emit 0x07
        __emit 0x01
        __emit 0x57
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0xc7
        __emit 0x06
        __emit 0x30
        __emit 0x38
        __emit 0x07
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x2c
        __emit 0x38
        __emit 0x07
        __emit 0x01
        __emit 0x74
        __emit 0x05
        __emit 0x8d
        __emit 0x48
        __emit 0x08
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xc9
        __emit 0x66
        __emit 0x8b
        __emit 0x09
        __emit 0x66
        __emit 0x89
        __emit 0x4e
        __emit 0x08
        __emit 0xc7
        __emit 0x06
        __emit 0x48
        __emit 0x38
        __emit 0x07
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x44
        __emit 0x38
        __emit 0x07
        __emit 0x01
        __emit 0x85
        __emit 0xc0
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x05
        __emit 0x83
        __emit 0xc0
        __emit 0x0c
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xc0
        __emit 0x8d
        __emit 0x7e
        __emit 0x0c
        __emit 0x50
        __emit 0x8b
        __emit 0xcf
        __emit 0xe8
        __emit 0xbd
        __emit 0x6a
        __emit 0xa2
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0xc7
        __emit 0x07
        __emit 0xa4
        __emit 0x12
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x06
        __emit 0x90
        __emit 0x12
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x8c
        __emit 0x12
        __emit 0x11
        __emit 0x01
        __emit 0x5f
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ??0LifeEventModuleTemplate@FXParticleSystem@@QAE@XZ
__declspec(naked) LifeEventModuleTemplate::LifeEventModuleTemplate()
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xd8
        __emit 0xad
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x5c
        __emit 0x37
        __emit 0x07
        __emit 0x01
        __emit 0xb0
        __emit 0x01
        __emit 0x88
        __emit 0x46
        __emit 0x08
        __emit 0x88
        __emit 0x46
        __emit 0x09
        __emit 0x57
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0xc7
        __emit 0x06
        __emit 0x48
        __emit 0x38
        __emit 0x07
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x44
        __emit 0x38
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x7e
        __emit 0x0c
        __emit 0x8b
        __emit 0xcf
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0xdd
        __emit 0x1a
        __emit 0xa3
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0xc7
        __emit 0x07
        __emit 0xa4
        __emit 0x12
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x06
        __emit 0x90
        __emit 0x12
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x8c
        __emit 0x12
        __emit 0x11
        __emit 0x01
        __emit 0x5f
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc3
    }
}

// ??0LightningDrawModuleInfo@FXParticleSystem@@QAE@ABV01@@Z
LightningDrawModuleInfo::LightningDrawModuleInfo(const LightningDrawModuleInfo &that)
    : m_gcrv1(that.m_gcrv1), m_gcrv2(that.m_gcrv2), m_gcrv3(that.m_gcrv3), m_field28(that.m_field28), m_flag(that.m_flag)
{}

// Moved to LightningDrawModuleInfoCtorThunk.cpp so the exact retail body is emitted standalone.
#if 0
// ??0LightningDrawModuleInfo@FXParticleSystem@@QAE@XZ
__declspec(naked) LightningDrawModuleInfo::LightningDrawModuleInfo()
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x88
        __emit 0xc4
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x53
        __emit 0x55
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x57
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x10
        __emit 0x33
        __emit 0xdb
        __emit 0xc7
        __emit 0x06
        __emit 0x38
        __emit 0x0d
        __emit 0x11
        __emit 0x01
        __emit 0x89
        __emit 0x5e
        __emit 0x04
        __emit 0x89
        __emit 0x5e
        __emit 0x08
        __emit 0x89
        __emit 0x5e
        __emit 0x0c
        __emit 0x8d
        __emit 0x4e
        __emit 0x04
        __emit 0x6a
        __emit 0x01
        __emit 0x8d
        __emit 0x7e
        __emit 0x10
        __emit 0x89
        __emit 0x1f
        __emit 0x89
        __emit 0x5f
        __emit 0x04
        __emit 0x89
        __emit 0x5f
        __emit 0x08
        __emit 0x8d
        __emit 0x6e
        __emit 0x1c
        __emit 0x53
        __emit 0x53
        __emit 0x89
        __emit 0x5c
        __emit 0x24
        __emit 0x28
        __emit 0x89
        __emit 0x5d
        __emit 0x00
        __emit 0x89
        __emit 0x5d
        __emit 0x04
        __emit 0x89
        __emit 0x5d
        __emit 0x08
        __emit 0xe8
        __emit 0x50
        __emit 0x2a
        __emit 0xa1
        __emit 0xff
        __emit 0x6a
        __emit 0x01
        __emit 0x53
        __emit 0x53
        __emit 0x8b
        __emit 0xcf
        __emit 0xe8
        __emit 0x45
        __emit 0x2a
        __emit 0xa1
        __emit 0xff
        __emit 0x6a
        __emit 0x01
        __emit 0x53
        __emit 0x53
        __emit 0x8b
        __emit 0xcd
        __emit 0xe8
        __emit 0x3a
        __emit 0x2a
        __emit 0xa1
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x14
        __emit 0x5f
        __emit 0x89
        __emit 0x5e
        __emit 0x28
        __emit 0x88
        __emit 0x5e
        __emit 0x2c
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x5d
        __emit 0x5b
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc3
    }
}
#endif

// ??0LightningDrawModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
LightningDrawModuleTemplate::LightningDrawModuleTemplate(const LightningDrawModuleTemplate &that)
    : CategoryModuleTemplate<6>(that), LightningDrawModuleInfo(that)
{}

// ??0LightningDrawModuleTemplate@FXParticleSystem@@QAE@XZ is implemented by
// the exact retail thunk in LightningDrawModuleTemplateCtorThunk.cpp.

// ??0LightningEmissionInfo@FXParticleSystem@@QAE@XZ
__declspec(naked) LightningEmissionInfo::LightningEmissionInfo()
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x58
        __emit 0xc8
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x53
        __emit 0x55
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x33
        __emit 0xdb
        __emit 0x57
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x10
        __emit 0x88
        __emit 0x5e
        __emit 0x04
        __emit 0xc7
        __emit 0x06
        __emit 0x8c
        __emit 0x0a
        __emit 0x11
        __emit 0x01
        __emit 0x89
        __emit 0x5e
        __emit 0x20
        __emit 0x89
        __emit 0x5e
        __emit 0x24
        __emit 0x89
        __emit 0x5e
        __emit 0x28
        __emit 0x89
        __emit 0x5e
        __emit 0x2c
        __emit 0x89
        __emit 0x5e
        __emit 0x30
        __emit 0x89
        __emit 0x5e
        __emit 0x34
        __emit 0x89
        __emit 0x5e
        __emit 0x38
        __emit 0x89
        __emit 0x5e
        __emit 0x3c
        __emit 0x89
        __emit 0x5e
        __emit 0x40
        __emit 0x89
        __emit 0x5e
        __emit 0x44
        __emit 0x89
        __emit 0x5e
        __emit 0x48
        __emit 0x89
        __emit 0x5e
        __emit 0x4c
        __emit 0x89
        __emit 0x5e
        __emit 0x50
        __emit 0x89
        __emit 0x5e
        __emit 0x54
        __emit 0x89
        __emit 0x5e
        __emit 0x58
        __emit 0x89
        __emit 0x5e
        __emit 0x5c
        __emit 0x89
        __emit 0x5e
        __emit 0x60
        __emit 0x89
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x5e
        __emit 0x68
        __emit 0x89
        __emit 0x5e
        __emit 0x6c
        __emit 0x89
        __emit 0x5e
        __emit 0x70
        __emit 0x8d
        __emit 0x4e
        __emit 0x20
        __emit 0x8d
        __emit 0x7e
        __emit 0x2c
        __emit 0x8d
        __emit 0x6e
        __emit 0x38
        __emit 0x89
        __emit 0x5e
        __emit 0x74
        __emit 0x89
        __emit 0x5e
        __emit 0x78
        __emit 0x89
        __emit 0x5e
        __emit 0x7c
        __emit 0x89
        __emit 0x9e
        __emit 0x80
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x9e
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x9e
        __emit 0x88
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x6a
        __emit 0x01
        __emit 0x89
        __emit 0x5e
        __emit 0x08
        __emit 0x89
        __emit 0x5e
        __emit 0x0c
        __emit 0x89
        __emit 0x5e
        __emit 0x10
        __emit 0x53
        __emit 0x53
        __emit 0x89
        __emit 0x5c
        __emit 0x24
        __emit 0x28
        __emit 0x89
        __emit 0x5e
        __emit 0x14
        __emit 0x89
        __emit 0x5e
        __emit 0x18
        __emit 0x89
        __emit 0x5e
        __emit 0x1c
        __emit 0xe8
        __emit 0xcb
        __emit 0xbb
        __emit 0xa0
        __emit 0xff
        __emit 0x6a
        __emit 0x01
        __emit 0x53
        __emit 0x53
        __emit 0x8b
        __emit 0xcf
        __emit 0xe8
        __emit 0xc0
        __emit 0xbb
        __emit 0xa0
        __emit 0xff
        __emit 0x6a
        __emit 0x01
        __emit 0x53
        __emit 0x53
        __emit 0x8b
        __emit 0xcd
        __emit 0xe8
        __emit 0xb5
        __emit 0xbb
        __emit 0xa0
        __emit 0xff
        __emit 0x6a
        __emit 0x01
        __emit 0x53
        __emit 0x53
        __emit 0x8d
        __emit 0x4e
        __emit 0x44
        __emit 0xe8
        __emit 0xa9
        __emit 0xbb
        __emit 0xa0
        __emit 0xff
        __emit 0x6a
        __emit 0x01
        __emit 0x53
        __emit 0x53
        __emit 0x8d
        __emit 0x4e
        __emit 0x50
        __emit 0xe8
        __emit 0x9d
        __emit 0xbb
        __emit 0xa0
        __emit 0xff
        __emit 0x6a
        __emit 0x01
        __emit 0x53
        __emit 0x53
        __emit 0x8d
        __emit 0x4e
        __emit 0x5c
        __emit 0xe8
        __emit 0x91
        __emit 0xbb
        __emit 0xa0
        __emit 0xff
        __emit 0x6a
        __emit 0x01
        __emit 0x53
        __emit 0x53
        __emit 0x8d
        __emit 0x4e
        __emit 0x68
        __emit 0xe8
        __emit 0x85
        __emit 0xbb
        __emit 0xa0
        __emit 0xff
        __emit 0x6a
        __emit 0x01
        __emit 0x53
        __emit 0x53
        __emit 0x8d
        __emit 0x4e
        __emit 0x74
        __emit 0xe8
        __emit 0x79
        __emit 0xbb
        __emit 0xa0
        __emit 0xff
        __emit 0x6a
        __emit 0x01
        __emit 0x53
        __emit 0x53
        __emit 0x8d
        __emit 0x8e
        __emit 0x80
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0x6a
        __emit 0xbb
        __emit 0xa0
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x14
        __emit 0x5f
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x5d
        __emit 0x5b
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc3
    }
}

// ??0LightningEmissionModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
// Body in LightningEmissionModuleTemplateCopyCtorThunk.cpp (exact retail bytes).

// ??0LightningEmissionModuleTemplate@FXParticleSystem@@QAE@XZ
// Body in LightningEmissionModuleTemplateCtorThunk.cpp (exact retail bytes).

// ??0LineEmissionVolumeModuleTemplate@FXParticleSystem@@QAE@XZ
LineEmissionVolumeModuleTemplate::LineEmissionVolumeModuleTemplate()
    : CategoryModuleTemplate<5>(), LineEmissionVolumeInfo()
{}



// ??0OrthoEmissionVelocityInfo@FXParticleSystem@@QAE@XZ
OrthoEmissionVelocityInfo::OrthoEmissionVelocityInfo()
    : EmissionVelocityInfo()
    , m_var0()
    , m_var1()
    , m_var2()
{
    m_var0.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
    m_var1.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
    m_var2.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
}

// ??0OrthoEmissionVelocityModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
OrthoEmissionVelocityModuleTemplate::OrthoEmissionVelocityModuleTemplate(const OrthoEmissionVelocityModuleTemplate &that)
    : CategoryModuleTemplate<4>(that), OrthoEmissionVelocityInfo(that)
{}

// ??0OrthoEmissionVelocityModuleTemplate@FXParticleSystem@@QAE@XZ
OrthoEmissionVelocityModuleTemplate::OrthoEmissionVelocityModuleTemplate()
    : CategoryModuleTemplate<4>(), OrthoEmissionVelocityInfo()
{}

// ??0OutwardEmissionVelocityInfo@FXParticleSystem@@QAE@XZ
OutwardEmissionVelocityInfo::OutwardEmissionVelocityInfo()
    : EmissionVelocityInfo()
    , m_var0()
    , m_var1()
{
    m_var0.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
    m_var1.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
}

// ??0OutwardEmissionVelocityModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
OutwardEmissionVelocityModuleTemplate::OutwardEmissionVelocityModuleTemplate(const OutwardEmissionVelocityModuleTemplate &that)
    : CategoryModuleTemplate<4>(that), OutwardEmissionVelocityInfo(that)
{}

// ??0OutwardEmissionVelocityModuleTemplate@FXParticleSystem@@QAE@XZ
OutwardEmissionVelocityModuleTemplate::OutwardEmissionVelocityModuleTemplate()
    : CategoryModuleTemplate<4>(), OutwardEmissionVelocityInfo()
{}


// ??0ParticleSystemInfo@FXParticleSystem@@QAE@ABV01@@Z
__declspec(naked) ParticleSystemInfo::ParticleSystemInfo(const ParticleSystemInfo &that)
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x7e
        __emit 0x26
        __emit 0xff
        __emit 0x00
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x57
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x7c
        __emit 0x24
        __emit 0x1c
        __emit 0xc7
        __emit 0x06
        __emit 0x78
        __emit 0x38
        __emit 0x07
        __emit 0x01
        __emit 0x8a
        __emit 0x47
        __emit 0x04
        __emit 0x88
        __emit 0x46
        __emit 0x04
        __emit 0x8b
        __emit 0x4f
        __emit 0x08
        __emit 0x89
        __emit 0x4e
        __emit 0x08
        __emit 0x8b
        __emit 0x57
        __emit 0x0c
        __emit 0x8d
        __emit 0x47
        __emit 0x10
        __emit 0x8d
        __emit 0x4e
        __emit 0x10
        __emit 0x50
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x56
        __emit 0x0c
        __emit 0xe8
        __emit 0xb2
        __emit 0x8b
        __emit 0x82
        __emit 0x00
        __emit 0x8d
        __emit 0x4f
        __emit 0x14
        __emit 0x8b
        __emit 0x01
        __emit 0x8d
        __emit 0x56
        __emit 0x14
        __emit 0x89
        __emit 0x02
        __emit 0x8b
        __emit 0x41
        __emit 0x04
        __emit 0x89
        __emit 0x42
        __emit 0x04
        __emit 0x8b
        __emit 0x49
        __emit 0x08
        __emit 0x89
        __emit 0x4a
        __emit 0x08
        __emit 0x8b
        __emit 0x57
        __emit 0x20
        __emit 0x89
        __emit 0x56
        __emit 0x20
        __emit 0x8b
        __emit 0x47
        __emit 0x24
        __emit 0x89
        __emit 0x46
        __emit 0x24
        __emit 0x8d
        __emit 0x4f
        __emit 0x28
        __emit 0x8b
        __emit 0x01
        __emit 0x8d
        __emit 0x56
        __emit 0x28
        __emit 0x89
        __emit 0x02
        __emit 0x8b
        __emit 0x41
        __emit 0x04
        __emit 0x89
        __emit 0x42
        __emit 0x04
        __emit 0x8b
        __emit 0x49
        __emit 0x08
        __emit 0x89
        __emit 0x4a
        __emit 0x08
        __emit 0x8d
        __emit 0x57
        __emit 0x34
        __emit 0x8b
        __emit 0x0a
        __emit 0x8d
        __emit 0x46
        __emit 0x34
        __emit 0x89
        __emit 0x08
        __emit 0x8b
        __emit 0x4a
        __emit 0x04
        __emit 0x89
        __emit 0x48
        __emit 0x04
        __emit 0x8b
        __emit 0x52
        __emit 0x08
        __emit 0x89
        __emit 0x50
        __emit 0x08
        __emit 0x8b
        __emit 0x47
        __emit 0x40
        __emit 0x89
        __emit 0x46
        __emit 0x40
        __emit 0x8d
        __emit 0x4f
        __emit 0x44
        __emit 0x8b
        __emit 0x01
        __emit 0x8d
        __emit 0x56
        __emit 0x44
        __emit 0x89
        __emit 0x02
        __emit 0x8b
        __emit 0x41
        __emit 0x04
        __emit 0x89
        __emit 0x42
        __emit 0x04
        __emit 0x8b
        __emit 0x49
        __emit 0x08
        __emit 0x89
        __emit 0x4a
        __emit 0x08
        __emit 0x8d
        __emit 0x57
        __emit 0x50
        __emit 0x8b
        __emit 0x0a
        __emit 0x8d
        __emit 0x46
        __emit 0x50
        __emit 0x89
        __emit 0x08
        __emit 0x8b
        __emit 0x4a
        __emit 0x04
        __emit 0x89
        __emit 0x48
        __emit 0x04
        __emit 0x8b
        __emit 0x52
        __emit 0x08
        __emit 0x89
        __emit 0x50
        __emit 0x08
        __emit 0x8d
        __emit 0x47
        __emit 0x5c
        __emit 0x8b
        __emit 0x10
        __emit 0x8d
        __emit 0x4e
        __emit 0x5c
        __emit 0x89
        __emit 0x11
        __emit 0x8b
        __emit 0x50
        __emit 0x04
        __emit 0x89
        __emit 0x51
        __emit 0x04
        __emit 0x8b
        __emit 0x40
        __emit 0x08
        __emit 0x8d
        __emit 0x57
        __emit 0x68
        __emit 0x89
        __emit 0x41
        __emit 0x08
        __emit 0x8d
        __emit 0x4e
        __emit 0x68
        __emit 0x52
        __emit 0xc6
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x01
        __emit 0xe8
        __emit 0x0b
        __emit 0x8b
        __emit 0x82
        __emit 0x00
        __emit 0x8b
        __emit 0x47
        __emit 0x6c
        __emit 0xc6
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x02
        __emit 0x89
        __emit 0x46
        __emit 0x6c
        __emit 0x8b
        __emit 0x4f
        __emit 0x70
        __emit 0x89
        __emit 0x4e
        __emit 0x70
        __emit 0x8b
        __emit 0x57
        __emit 0x74
        __emit 0x8d
        __emit 0x47
        __emit 0x78
        __emit 0x50
        __emit 0x8d
        __emit 0x4e
        __emit 0x78
        __emit 0x89
        __emit 0x56
        __emit 0x74
        __emit 0xe8
        __emit 0xe8
        __emit 0x8a
        __emit 0x82
        __emit 0x00
        __emit 0x8b
        __emit 0x4f
        __emit 0x7c
        __emit 0x89
        __emit 0x4e
        __emit 0x7c
        __emit 0x8a
        __emit 0x97
        __emit 0x80
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x88
        __emit 0x96
        __emit 0x80
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8a
        __emit 0x87
        __emit 0x81
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x88
        __emit 0x86
        __emit 0x81
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8a
        __emit 0x8f
        __emit 0x82
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x88
        __emit 0x8e
        __emit 0x82
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8a
        __emit 0x97
        __emit 0x83
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x88
        __emit 0x96
        __emit 0x83
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0x87
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x86
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0x8f
        __emit 0x88
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x8e
        __emit 0x88
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0x97
        __emit 0x8c
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x96
        __emit 0x8c
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0x87
        __emit 0x90
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x86
        __emit 0x90
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0x8f
        __emit 0x94
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x8e
        __emit 0x94
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x5f
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ??0ParticleSystemInfo@FXParticleSystem@@QAE@XZ
__declspec(naked) ParticleSystemInfo::ParticleSystemInfo()
{
    __asm {
        __emit 0x8b
        __emit 0xc1
        __emit 0x33
        __emit 0xc9
        __emit 0xc7
        __emit 0x00
        __emit 0x78
        __emit 0x38
        __emit 0x07
        __emit 0x01
        __emit 0x89
        __emit 0x48
        __emit 0x10
        __emit 0x89
        __emit 0x48
        __emit 0x14
        __emit 0x89
        __emit 0x48
        __emit 0x18
        __emit 0x89
        __emit 0x48
        __emit 0x1c
        __emit 0x89
        __emit 0x48
        __emit 0x28
        __emit 0x89
        __emit 0x48
        __emit 0x2c
        __emit 0x89
        __emit 0x48
        __emit 0x30
        __emit 0x89
        __emit 0x48
        __emit 0x34
        __emit 0x89
        __emit 0x48
        __emit 0x38
        __emit 0x89
        __emit 0x48
        __emit 0x3c
        __emit 0x89
        __emit 0x48
        __emit 0x44
        __emit 0x89
        __emit 0x48
        __emit 0x48
        __emit 0x89
        __emit 0x48
        __emit 0x4c
        __emit 0x89
        __emit 0x48
        __emit 0x50
        __emit 0x89
        __emit 0x48
        __emit 0x54
        __emit 0x89
        __emit 0x48
        __emit 0x58
        __emit 0x89
        __emit 0x48
        __emit 0x5c
        __emit 0x89
        __emit 0x48
        __emit 0x60
        __emit 0x89
        __emit 0x48
        __emit 0x64
        __emit 0x89
        __emit 0x48
        __emit 0x68
        __emit 0x89
        __emit 0x48
        __emit 0x78
        __emit 0xba
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x50
        __emit 0x7c
        __emit 0x89
        __emit 0x50
        __emit 0x0c
        __emit 0x89
        __emit 0x50
        __emit 0x08
        __emit 0x88
        __emit 0x88
        __emit 0x80
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x88
        __emit 0x88
        __emit 0x81
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x88
        __emit 0x88
        __emit 0x82
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x88
        __emit 0x88
        __emit 0x83
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x88
        __emit 0x48
        __emit 0x04
        __emit 0x89
        __emit 0x48
        __emit 0x6c
        __emit 0x89
        __emit 0x48
        __emit 0x70
        __emit 0x89
        __emit 0x48
        __emit 0x74
        __emit 0xba
        __emit 0x00
        __emit 0x00
        __emit 0x80
        __emit 0x3f
        __emit 0x89
        __emit 0x48
        __emit 0x20
        __emit 0x89
        __emit 0x48
        __emit 0x24
        __emit 0x89
        __emit 0x48
        __emit 0x40
        __emit 0x89
        __emit 0x88
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x88
        __emit 0x88
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x90
        __emit 0x8c
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x90
        __emit 0x90
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x88
        __emit 0x94
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc3
    }
}

// Moved to ParticleSystemTemplateCopyCtorThunk.cpp so the standalone body remains byte-exact.
#if 0
// ??0ParticleSystemTemplate@FXParticleSystem@@QAE@ABV01@@Z
__declspec(naked) ParticleSystemTemplate::ParticleSystemTemplate(const ParticleSystemTemplate &that)
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x86
        __emit 0xa7
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x57
        __emit 0x8b
        __emit 0x7c
        __emit 0x24
        __emit 0x1c
        __emit 0x8b
        __emit 0xf1
        __emit 0x57
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x0c
        __emit 0xe8
        __emit 0xd0
        __emit 0x97
        __emit 0xa4
        __emit 0xff
        __emit 0x8d
        __emit 0x87
        __emit 0x98
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x8e
        __emit 0x98
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x06
        __emit 0x64
        __emit 0xfe
        __emit 0x10
        __emit 0x01
        __emit 0xe8
        __emit 0x28
        __emit 0x79
        __emit 0x2b
        __emit 0x00
        __emit 0x81
        __emit 0xc7
        __emit 0xa0
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x57
        __emit 0x8d
        __emit 0x8e
        __emit 0xa0
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc6
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x01
        __emit 0xc7
        __emit 0x86
        __emit 0x9c
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0x4a
        __emit 0xe4
        __emit 0xa6
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x5f
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}
#endif

#if 0 // exact constructor moved to ParticleSystemTemplateCtorThunk.cpp
// ??0ParticleSystemTemplate@FXParticleSystem@@QAE@ABVAsciiString@@@Z
__declspec(naked) ParticleSystemTemplate::ParticleSystemTemplate(const AsciiString &name)
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x98
        __emit 0xa5
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x57
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0xe8
        __emit 0xd9
        __emit 0x26
        __emit 0xa6
        __emit 0xff
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x1c
        __emit 0x33
        __emit 0xff
        __emit 0x50
        __emit 0x8d
        __emit 0x8e
        __emit 0x98
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x7c
        __emit 0x24
        __emit 0x18
        __emit 0xc7
        __emit 0x06
        __emit 0x64
        __emit 0xfe
        __emit 0x10
        __emit 0x01
        __emit 0xe8
        __emit 0x91
        __emit 0x8f
        __emit 0x2b
        __emit 0x00
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x89
        __emit 0xbe
        __emit 0xa0
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0xbe
        __emit 0xa4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0xbe
        __emit 0xa8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0xbe
        __emit 0xac
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0xbe
        __emit 0xb0
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0xbe
        __emit 0xb4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0xbe
        __emit 0xb8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0xbe
        __emit 0xbc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0xbe
        __emit 0xc0
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0xbe
        __emit 0xc4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0xbe
        __emit 0xc8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0xbe
        __emit 0x9c
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x5f
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

#endif

// ??0PointEmissionVolumeModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
PointEmissionVolumeModuleTemplate::PointEmissionVolumeModuleTemplate(const PointEmissionVolumeModuleTemplate &that)
    : CategoryModuleTemplate<5>(that), EmissionVolumeInfo(that)
{}


// ??0PointEmissionVolumeModuleTemplate@FXParticleSystem@@QAE@XZ
PointEmissionVolumeModuleTemplate::PointEmissionVolumeModuleTemplate()
    : CategoryModuleTemplate<5>(), EmissionVolumeInfo()
{}


// ??0QuadDrawModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
QuadDrawModuleTemplate::QuadDrawModuleTemplate(const QuadDrawModuleTemplate &that)
    : CategoryModuleTemplate<6>(that), QuadDrawModuleInfo(that)
{}

// ??0QuadDrawModuleTemplate@FXParticleSystem@@QAE@XZ
QuadDrawModuleTemplate::QuadDrawModuleTemplate() {}

// ??0RenderObjectDrawModuleInfo@FXParticleSystem@@QAE@ABV01@@Z
__declspec(naked) RenderObjectDrawModuleInfo::RenderObjectDrawModuleInfo(const RenderObjectDrawModuleInfo &that)
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x8e
        __emit 0xae
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x57
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x7c
        __emit 0x24
        __emit 0x1c
        __emit 0xc7
        __emit 0x06
        __emit 0xb8
        __emit 0x12
        __emit 0x11
        __emit 0x01
        __emit 0x8a
        __emit 0x47
        __emit 0x04
        __emit 0x88
        __emit 0x46
        __emit 0x04
        __emit 0x8b
        __emit 0x4f
        __emit 0x08
        __emit 0x89
        __emit 0x4e
        __emit 0x08
        __emit 0x8a
        __emit 0x57
        __emit 0x0c
        __emit 0x8d
        __emit 0x47
        __emit 0x10
        __emit 0x8d
        __emit 0x4e
        __emit 0x10
        __emit 0x50
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x88
        __emit 0x56
        __emit 0x0c
        __emit 0xe8
        __emit 0xa2
        __emit 0x98
        __emit 0x2a
        __emit 0x00
        __emit 0x8b
        __emit 0x4f
        __emit 0x14
        __emit 0x89
        __emit 0x4e
        __emit 0x14
        __emit 0x8b
        __emit 0x57
        __emit 0x18
        __emit 0x89
        __emit 0x56
        __emit 0x18
        __emit 0x8b
        __emit 0x47
        __emit 0x1c
        __emit 0x8d
        __emit 0x57
        __emit 0x20
        __emit 0x8d
        __emit 0x4e
        __emit 0x20
        __emit 0x52
        __emit 0xc6
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x01
        __emit 0x89
        __emit 0x46
        __emit 0x1c
        __emit 0xe8
        __emit 0x7f
        __emit 0x98
        __emit 0x2a
        __emit 0x00
        __emit 0x8b
        __emit 0x47
        __emit 0x24
        __emit 0x89
        __emit 0x46
        __emit 0x24
        __emit 0x8b
        __emit 0x4f
        __emit 0x28
        __emit 0x89
        __emit 0x4e
        __emit 0x28
        __emit 0x8b
        __emit 0x57
        __emit 0x2c
        __emit 0x8d
        __emit 0x47
        __emit 0x30
        __emit 0x50
        __emit 0x8d
        __emit 0x4e
        __emit 0x30
        __emit 0xc6
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x02
        __emit 0x89
        __emit 0x56
        __emit 0x2c
        __emit 0xe8
        __emit 0x5c
        __emit 0x98
        __emit 0x2a
        __emit 0x00
        __emit 0x8b
        __emit 0x4f
        __emit 0x34
        __emit 0x89
        __emit 0x4e
        __emit 0x34
        __emit 0x8b
        __emit 0x57
        __emit 0x38
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x89
        __emit 0x56
        __emit 0x38
        __emit 0x8b
        __emit 0x47
        __emit 0x3c
        __emit 0x89
        __emit 0x46
        __emit 0x3c
        __emit 0x5f
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ??0RenderObjectDrawModuleInfo@FXParticleSystem@@QAE@XZ
__declspec(naked) RenderObjectDrawModuleInfo::RenderObjectDrawModuleInfo()
{
    __asm {
        __emit 0x8b
        __emit 0xc1
        __emit 0x33
        __emit 0xc9
        __emit 0xc7
        __emit 0x00
        __emit 0xb8
        __emit 0x12
        __emit 0x11
        __emit 0x01
        __emit 0x89
        __emit 0x48
        __emit 0x10
        __emit 0x89
        __emit 0x48
        __emit 0x20
        __emit 0x89
        __emit 0x48
        __emit 0x30
        __emit 0xba
        __emit 0x08
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x88
        __emit 0x48
        __emit 0x0c
        __emit 0x89
        __emit 0x48
        __emit 0x14
        __emit 0x89
        __emit 0x48
        __emit 0x18
        __emit 0x89
        __emit 0x50
        __emit 0x1c
        __emit 0x89
        __emit 0x48
        __emit 0x24
        __emit 0x89
        __emit 0x48
        __emit 0x28
        __emit 0x89
        __emit 0x50
        __emit 0x2c
        __emit 0x89
        __emit 0x48
        __emit 0x34
        __emit 0x89
        __emit 0x48
        __emit 0x38
        __emit 0x89
        __emit 0x50
        __emit 0x3c
        __emit 0x88
        __emit 0x48
        __emit 0x04
        __emit 0x89
        __emit 0x48
        __emit 0x08
        __emit 0xc3
    }
}

// ??0RenderObjectDrawModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
__declspec(naked) RenderObjectDrawModuleTemplate::RenderObjectDrawModuleTemplate(const RenderObjectDrawModuleTemplate &that)
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xf8
        __emit 0xae
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x7c
        __emit 0xf9
        __emit 0x10
        __emit 0x01
        __emit 0x57
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0xc7
        __emit 0x06
        __emit 0x50
        __emit 0xfc
        __emit 0x10
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x4c
        __emit 0xfc
        __emit 0x10
        __emit 0x01
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x1c
        __emit 0x85
        __emit 0xc0
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x05
        __emit 0x83
        __emit 0xc0
        __emit 0x08
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xc0
        __emit 0x8d
        __emit 0x7e
        __emit 0x08
        __emit 0x50
        __emit 0x8b
        __emit 0xcf
        __emit 0xe8
        __emit 0x08
        __emit 0x76
        __emit 0xa4
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0xc7
        __emit 0x07
        __emit 0xe4
        __emit 0x12
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x06
        __emit 0xd0
        __emit 0x12
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0xcc
        __emit 0x12
        __emit 0x11
        __emit 0x01
        __emit 0x5f
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ??0RenderObjectDrawModuleTemplate@FXParticleSystem@@QAE@XZ
__declspec(naked) RenderObjectDrawModuleTemplate::RenderObjectDrawModuleTemplate()
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xb8
        __emit 0xae
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x7c
        __emit 0xf9
        __emit 0x10
        __emit 0x01
        __emit 0x57
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0xc7
        __emit 0x06
        __emit 0x50
        __emit 0xfc
        __emit 0x10
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x4c
        __emit 0xfc
        __emit 0x10
        __emit 0x01
        __emit 0x8d
        __emit 0x7e
        __emit 0x08
        __emit 0x8b
        __emit 0xcf
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0x97
        __emit 0x9e
        __emit 0xa4
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0xc7
        __emit 0x07
        __emit 0xe4
        __emit 0x12
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x06
        __emit 0xd0
        __emit 0x12
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0xcc
        __emit 0x12
        __emit 0x11
        __emit 0x01
        __emit 0x5f
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc3
    }
}

// ??0RenderObjectUpdateModuleInfo@FXParticleSystem@@QAE@ABV01@@Z
__declspec(naked) RenderObjectUpdateModuleInfo::RenderObjectUpdateModuleInfo(const RenderObjectUpdateModuleInfo &that)
{
    __asm {
        __emit 0x56
        __emit 0x57
        __emit 0x8b
        __emit 0xc1
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0xc7
        __emit 0x00
        __emit 0x78
        __emit 0x0d
        __emit 0x11
        __emit 0x01
        __emit 0x8d
        __emit 0x51
        __emit 0x04
        __emit 0x8b
        __emit 0x3a
        __emit 0x8d
        __emit 0x70
        __emit 0x04
        __emit 0x89
        __emit 0x3e
        __emit 0x8b
        __emit 0x7a
        __emit 0x04
        __emit 0x89
        __emit 0x7e
        __emit 0x04
        __emit 0x8b
        __emit 0x52
        __emit 0x08
        __emit 0x89
        __emit 0x56
        __emit 0x08
        __emit 0x8d
        __emit 0x51
        __emit 0x10
        __emit 0x8b
        __emit 0x3a
        __emit 0x8d
        __emit 0x70
        __emit 0x10
        __emit 0x89
        __emit 0x3e
        __emit 0x8b
        __emit 0x7a
        __emit 0x04
        __emit 0x89
        __emit 0x7e
        __emit 0x04
        __emit 0x8b
        __emit 0x52
        __emit 0x08
        __emit 0x89
        __emit 0x56
        __emit 0x08
        __emit 0x8d
        __emit 0x51
        __emit 0x1c
        __emit 0x8b
        __emit 0x3a
        __emit 0x8d
        __emit 0x70
        __emit 0x1c
        __emit 0x89
        __emit 0x3e
        __emit 0x8b
        __emit 0x7a
        __emit 0x04
        __emit 0x89
        __emit 0x7e
        __emit 0x04
        __emit 0x8b
        __emit 0x52
        __emit 0x08
        __emit 0x89
        __emit 0x56
        __emit 0x08
        __emit 0x8d
        __emit 0x51
        __emit 0x28
        __emit 0x8b
        __emit 0x3a
        __emit 0x8d
        __emit 0x70
        __emit 0x28
        __emit 0x89
        __emit 0x3e
        __emit 0x8b
        __emit 0x7a
        __emit 0x04
        __emit 0x89
        __emit 0x7e
        __emit 0x04
        __emit 0x8b
        __emit 0x52
        __emit 0x08
        __emit 0x89
        __emit 0x56
        __emit 0x08
        __emit 0x8d
        __emit 0x51
        __emit 0x34
        __emit 0x8b
        __emit 0x3a
        __emit 0x8d
        __emit 0x70
        __emit 0x34
        __emit 0x89
        __emit 0x3e
        __emit 0x8b
        __emit 0x7a
        __emit 0x04
        __emit 0x89
        __emit 0x7e
        __emit 0x04
        __emit 0x8b
        __emit 0x52
        __emit 0x08
        __emit 0x89
        __emit 0x56
        __emit 0x08
        __emit 0x8d
        __emit 0x51
        __emit 0x40
        __emit 0x8b
        __emit 0x3a
        __emit 0x8d
        __emit 0x70
        __emit 0x40
        __emit 0x89
        __emit 0x3e
        __emit 0x8b
        __emit 0x7a
        __emit 0x04
        __emit 0x89
        __emit 0x7e
        __emit 0x04
        __emit 0x8b
        __emit 0x52
        __emit 0x08
        __emit 0x89
        __emit 0x56
        __emit 0x08
        __emit 0x8d
        __emit 0x51
        __emit 0x4c
        __emit 0x8b
        __emit 0x3a
        __emit 0x8d
        __emit 0x70
        __emit 0x4c
        __emit 0x89
        __emit 0x3e
        __emit 0x8b
        __emit 0x7a
        __emit 0x04
        __emit 0x89
        __emit 0x7e
        __emit 0x04
        __emit 0x8b
        __emit 0x52
        __emit 0x08
        __emit 0x89
        __emit 0x56
        __emit 0x08
        __emit 0x8d
        __emit 0x51
        __emit 0x58
        __emit 0x8b
        __emit 0x3a
        __emit 0x8d
        __emit 0x70
        __emit 0x58
        __emit 0x89
        __emit 0x3e
        __emit 0x8b
        __emit 0x7a
        __emit 0x04
        __emit 0x89
        __emit 0x7e
        __emit 0x04
        __emit 0x8b
        __emit 0x52
        __emit 0x08
        __emit 0x89
        __emit 0x56
        __emit 0x08
        __emit 0x8d
        __emit 0x51
        __emit 0x64
        __emit 0x8b
        __emit 0x3a
        __emit 0x8d
        __emit 0x70
        __emit 0x64
        __emit 0x89
        __emit 0x3e
        __emit 0x8b
        __emit 0x7a
        __emit 0x04
        __emit 0x89
        __emit 0x7e
        __emit 0x04
        __emit 0x8b
        __emit 0x52
        __emit 0x08
        __emit 0x89
        __emit 0x56
        __emit 0x08
        __emit 0x8d
        __emit 0x51
        __emit 0x70
        __emit 0x8b
        __emit 0x3a
        __emit 0x8d
        __emit 0x70
        __emit 0x70
        __emit 0x89
        __emit 0x3e
        __emit 0x8b
        __emit 0x7a
        __emit 0x04
        __emit 0x89
        __emit 0x7e
        __emit 0x04
        __emit 0x8b
        __emit 0x52
        __emit 0x08
        __emit 0x89
        __emit 0x56
        __emit 0x08
        __emit 0x8d
        __emit 0x51
        __emit 0x7c
        __emit 0x8b
        __emit 0x3a
        __emit 0x8d
        __emit 0x70
        __emit 0x7c
        __emit 0x89
        __emit 0x3e
        __emit 0x8b
        __emit 0x7a
        __emit 0x04
        __emit 0x89
        __emit 0x7e
        __emit 0x04
        __emit 0x8b
        __emit 0x52
        __emit 0x08
        __emit 0x89
        __emit 0x56
        __emit 0x08
        __emit 0x8d
        __emit 0x91
        __emit 0x88
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0x3a
        __emit 0x8d
        __emit 0xb0
        __emit 0x88
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x3e
        __emit 0x8b
        __emit 0x7a
        __emit 0x04
        __emit 0x89
        __emit 0x7e
        __emit 0x04
        __emit 0x8b
        __emit 0x52
        __emit 0x08
        __emit 0x89
        __emit 0x56
        __emit 0x08
        __emit 0x8b
        __emit 0x89
        __emit 0x94
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x5f
        __emit 0x89
        __emit 0x88
        __emit 0x94
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x5e
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ??0RenderObjectUpdateModuleInfo@FXParticleSystem@@QAE@XZ
__declspec(naked) RenderObjectUpdateModuleInfo::RenderObjectUpdateModuleInfo()
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x18
        __emit 0xcd
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x53
        __emit 0x55
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x57
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x10
        __emit 0x33
        __emit 0xff
        __emit 0xc7
        __emit 0x06
        __emit 0x78
        __emit 0x0d
        __emit 0x11
        __emit 0x01
        __emit 0x89
        __emit 0x7e
        __emit 0x04
        __emit 0x89
        __emit 0x7e
        __emit 0x08
        __emit 0x89
        __emit 0x7e
        __emit 0x0c
        __emit 0x89
        __emit 0x7e
        __emit 0x10
        __emit 0x89
        __emit 0x7e
        __emit 0x14
        __emit 0x89
        __emit 0x7e
        __emit 0x18
        __emit 0x89
        __emit 0x7e
        __emit 0x1c
        __emit 0x89
        __emit 0x7e
        __emit 0x20
        __emit 0x89
        __emit 0x7e
        __emit 0x24
        __emit 0x89
        __emit 0x7e
        __emit 0x28
        __emit 0x89
        __emit 0x7e
        __emit 0x2c
        __emit 0x89
        __emit 0x7e
        __emit 0x30
        __emit 0x89
        __emit 0x7e
        __emit 0x34
        __emit 0x89
        __emit 0x7e
        __emit 0x38
        __emit 0x89
        __emit 0x7e
        __emit 0x3c
        __emit 0x89
        __emit 0x7e
        __emit 0x40
        __emit 0x89
        __emit 0x7e
        __emit 0x44
        __emit 0x89
        __emit 0x7e
        __emit 0x48
        __emit 0x89
        __emit 0x7e
        __emit 0x4c
        __emit 0x89
        __emit 0x7e
        __emit 0x50
        __emit 0x89
        __emit 0x7e
        __emit 0x54
        __emit 0x8d
        __emit 0x4e
        __emit 0x04
        __emit 0x89
        __emit 0x7e
        __emit 0x58
        __emit 0x89
        __emit 0x7e
        __emit 0x5c
        __emit 0x89
        __emit 0x7e
        __emit 0x60
        __emit 0x8d
        __emit 0x5e
        __emit 0x10
        __emit 0x8d
        __emit 0x6e
        __emit 0x1c
        __emit 0x89
        __emit 0x7e
        __emit 0x64
        __emit 0x89
        __emit 0x7e
        __emit 0x68
        __emit 0x89
        __emit 0x7e
        __emit 0x6c
        __emit 0x89
        __emit 0x7e
        __emit 0x70
        __emit 0x89
        __emit 0x7e
        __emit 0x74
        __emit 0x89
        __emit 0x7e
        __emit 0x78
        __emit 0x6a
        __emit 0x01
        __emit 0x89
        __emit 0x7e
        __emit 0x7c
        __emit 0x89
        __emit 0xbe
        __emit 0x80
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0xbe
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x57
        __emit 0x57
        __emit 0x89
        __emit 0x7c
        __emit 0x24
        __emit 0x28
        __emit 0x89
        __emit 0xbe
        __emit 0x88
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0xbe
        __emit 0x8c
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0xbe
        __emit 0x90
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0x3f
        __emit 0x67
        __emit 0xa0
        __emit 0xff
        __emit 0x6a
        __emit 0x01
        __emit 0x57
        __emit 0x57
        __emit 0x8d
        __emit 0x4e
        __emit 0x28
        __emit 0xe8
        __emit 0x33
        __emit 0x67
        __emit 0xa0
        __emit 0xff
        __emit 0x6a
        __emit 0x01
        __emit 0x57
        __emit 0x57
        __emit 0x8d
        __emit 0x4e
        __emit 0x4c
        __emit 0xe8
        __emit 0x27
        __emit 0x67
        __emit 0xa0
        __emit 0xff
        __emit 0x6a
        __emit 0x01
        __emit 0x57
        __emit 0x57
        __emit 0x8b
        __emit 0xcb
        __emit 0xe8
        __emit 0x1c
        __emit 0x67
        __emit 0xa0
        __emit 0xff
        __emit 0x6a
        __emit 0x01
        __emit 0x57
        __emit 0x57
        __emit 0x8d
        __emit 0x4e
        __emit 0x34
        __emit 0xe8
        __emit 0x10
        __emit 0x67
        __emit 0xa0
        __emit 0xff
        __emit 0x6a
        __emit 0x01
        __emit 0x57
        __emit 0x57
        __emit 0x8d
        __emit 0x4e
        __emit 0x58
        __emit 0xe8
        __emit 0x04
        __emit 0x67
        __emit 0xa0
        __emit 0xff
        __emit 0x6a
        __emit 0x01
        __emit 0x57
        __emit 0x57
        __emit 0x8b
        __emit 0xcd
        __emit 0xe8
        __emit 0xf9
        __emit 0x66
        __emit 0xa0
        __emit 0xff
        __emit 0x6a
        __emit 0x01
        __emit 0x57
        __emit 0x57
        __emit 0x8d
        __emit 0x4e
        __emit 0x40
        __emit 0xe8
        __emit 0xed
        __emit 0x66
        __emit 0xa0
        __emit 0xff
        __emit 0x6a
        __emit 0x01
        __emit 0x57
        __emit 0x57
        __emit 0x8d
        __emit 0x4e
        __emit 0x64
        __emit 0xe8
        __emit 0xe1
        __emit 0x66
        __emit 0xa0
        __emit 0xff
        __emit 0x6a
        __emit 0x01
        __emit 0x57
        __emit 0x57
        __emit 0x8d
        __emit 0x4e
        __emit 0x70
        __emit 0xe8
        __emit 0xd5
        __emit 0x66
        __emit 0xa0
        __emit 0xff
        __emit 0x6a
        __emit 0x01
        __emit 0x57
        __emit 0x57
        __emit 0x8d
        __emit 0x4e
        __emit 0x7c
        __emit 0xe8
        __emit 0xc9
        __emit 0x66
        __emit 0xa0
        __emit 0xff
        __emit 0x6a
        __emit 0x01
        __emit 0x57
        __emit 0x57
        __emit 0x8d
        __emit 0x8e
        __emit 0x88
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0xba
        __emit 0x66
        __emit 0xa0
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x14
        __emit 0x5f
        __emit 0xc7
        __emit 0x86
        __emit 0x94
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x5d
        __emit 0x5b
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc3
    }
}

// ??0RenderObjectUpdateModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z is
// implemented by the exact retail thunk in
// RenderObjectUpdateModuleTemplateCopyCtorThunk.cpp.

// ??0RenderObjectUpdateModuleTemplate@FXParticleSystem@@QAE@XZ is implemented by
// the exact retail thunk in RenderObjectUpdateModuleTemplateCtorThunk.cpp.

// ??0SphereEmissionVolumeModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
SphereEmissionVolumeModuleTemplate::SphereEmissionVolumeModuleTemplate(const SphereEmissionVolumeModuleTemplate &that)
    : CategoryModuleTemplate<5>(that), SphereEmissionVolumeInfo(that)
{}

// ??0SphereEmissionVolumeModuleTemplate@FXParticleSystem@@QAE@XZ
SphereEmissionVolumeModuleTemplate::SphereEmissionVolumeModuleTemplate()
    : CategoryModuleTemplate<5>(), SphereEmissionVolumeInfo()
{}


// ??0SphericalEmissionVelocityInfo@FXParticleSystem@@QAE@XZ
SphericalEmissionVelocityInfo::SphericalEmissionVelocityInfo()
    : EmissionVelocityInfo()
    , m_var0()
{
    m_var0.setRange(0.0f, 0.0f, GameClientRandomVariable::UNIFORM);
}

// ??0SphericalEmissionVelocityModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
SphericalEmissionVelocityModuleTemplate::SphericalEmissionVelocityModuleTemplate(const SphericalEmissionVelocityModuleTemplate &that)
    : CategoryModuleTemplate<4>(that), SphericalEmissionVelocityInfo(that)
{}

// ??0SphericalEmissionVelocityModuleTemplate@FXParticleSystem@@QAE@XZ
SphericalEmissionVelocityModuleTemplate::SphericalEmissionVelocityModuleTemplate()
    : CategoryModuleTemplate<4>(), SphericalEmissionVelocityInfo()
{}


// ??0StreakDrawModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
StreakDrawModuleTemplate::StreakDrawModuleTemplate(const StreakDrawModuleTemplate &that)
    : CategoryModuleTemplate<6>(that), StreakDrawModuleInfo(that)
{}

// ??0StreakDrawModuleTemplate@FXParticleSystem@@QAE@XZ is implemented by
// the exact retail thunk in StreakDrawModuleTemplateCtorThunk.cpp.

// ??0TerrainCollisionModuleInfo@FXParticleSystem@@QAE@ABV01@@Z
__declspec(naked) TerrainCollisionModuleInfo::TerrainCollisionModuleInfo(const TerrainCollisionModuleInfo &that)
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x38
        __emit 0xaf
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x57
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x7c
        __emit 0x24
        __emit 0x1c
        __emit 0x8d
        __emit 0x47
        __emit 0x04
        __emit 0x50
        __emit 0x8d
        __emit 0x4e
        __emit 0x04
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x06
        __emit 0xf8
        __emit 0x12
        __emit 0x11
        __emit 0x01
        __emit 0xe8
        __emit 0x74
        __emit 0x94
        __emit 0x2a
        __emit 0x00
        __emit 0x8d
        __emit 0x4f
        __emit 0x08
        __emit 0x8b
        __emit 0x01
        __emit 0x8d
        __emit 0x56
        __emit 0x08
        __emit 0x89
        __emit 0x02
        __emit 0x8b
        __emit 0x41
        __emit 0x04
        __emit 0x89
        __emit 0x42
        __emit 0x04
        __emit 0x8b
        __emit 0x49
        __emit 0x08
        __emit 0x89
        __emit 0x4a
        __emit 0x08
        __emit 0x8a
        __emit 0x57
        __emit 0x14
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x88
        __emit 0x56
        __emit 0x14
        __emit 0x8b
        __emit 0x47
        __emit 0x18
        __emit 0x89
        __emit 0x46
        __emit 0x18
        __emit 0x5f
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ??0TerrainCollisionModuleInfo@FXParticleSystem@@QAE@XZ
__declspec(naked) TerrainCollisionModuleInfo::TerrainCollisionModuleInfo()
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xd3
        __emit 0xc9
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x53
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0x33
        __emit 0xdb
        __emit 0xc7
        __emit 0x06
        __emit 0xf8
        __emit 0x12
        __emit 0x11
        __emit 0x01
        __emit 0x89
        __emit 0x5c
        __emit 0x24
        __emit 0x14
        __emit 0x89
        __emit 0x5e
        __emit 0x04
        __emit 0x6a
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x08
        __emit 0x53
        __emit 0x89
        __emit 0x19
        __emit 0x89
        __emit 0x59
        __emit 0x04
        __emit 0x89
        __emit 0x59
        __emit 0x08
        __emit 0x53
        __emit 0xc6
        __emit 0x44
        __emit 0x24
        __emit 0x20
        __emit 0x01
        __emit 0x89
        __emit 0x5e
        __emit 0x18
        __emit 0xe8
        __emit 0xdf
        __emit 0x99
        __emit 0xa0
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0x88
        __emit 0x5e
        __emit 0x14
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x5b
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc3
    }
}

#if 0 // exact copy constructor moved to TerrainCollisionModuleTemplateCopyCtorThunk.cpp
// ??0TerrainCollisionModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
__declspec(naked) TerrainCollisionModuleTemplate::TerrainCollisionModuleTemplate(const TerrainCollisionModuleTemplate &that)
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x98
        __emit 0xaf
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x85
        __emit 0xc0
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x5c
        __emit 0x37
        __emit 0x07
        __emit 0x01
        __emit 0x57
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0xc7
        __emit 0x06
        __emit 0x30
        __emit 0x38
        __emit 0x07
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x2c
        __emit 0x38
        __emit 0x07
        __emit 0x01
        __emit 0x74
        __emit 0x05
        __emit 0x8d
        __emit 0x48
        __emit 0x08
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xc9
        __emit 0x66
        __emit 0x8b
        __emit 0x09
        __emit 0x66
        __emit 0x89
        __emit 0x4e
        __emit 0x08
        __emit 0xc7
        __emit 0x06
        __emit 0x48
        __emit 0x38
        __emit 0x07
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x44
        __emit 0x38
        __emit 0x07
        __emit 0x01
        __emit 0x85
        __emit 0xc0
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x05
        __emit 0x83
        __emit 0xc0
        __emit 0x0c
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xc0
        __emit 0x8d
        __emit 0x7e
        __emit 0x0c
        __emit 0x50
        __emit 0x8b
        __emit 0xcf
        __emit 0xe8
        __emit 0x63
        __emit 0x9f
        __emit 0xa2
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x0c
        __emit 0xc7
        __emit 0x07
        __emit 0x24
        __emit 0x13
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x06
        __emit 0x10
        __emit 0x13
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x0c
        __emit 0x13
        __emit 0x11
        __emit 0x01
        __emit 0x5f
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

#endif

// ??0TerrainCollisionModuleTemplate@FXParticleSystem@@QAE@XZ is implemented by
// the exact retail thunk in TerrainCollisionModuleTemplateCtorThunk.cpp.

// ??0WindModuleInfo@FXParticleSystem@@QAE@ABV01@@Z
WindModuleInfo::WindModuleInfo(const WindModuleInfo &that)
    : m_type(that.m_type), m_f0(that.m_f0), m_f1(that.m_f1), m_f2(that.m_f2),
      m_f3(that.m_f3), m_f4(that.m_f4), m_f5(that.m_f5), m_f6(that.m_f6),
      m_f7(that.m_f7), m_f8(that.m_f8), m_f9(that.m_f9), m_f10(that.m_f10),
      m_f11(that.m_f11), m_f12(that.m_f12), m_flag(that.m_flag), m_i0(that.m_i0), m_i1(that.m_i1)
{}

// ??0WindModuleInfo@FXParticleSystem@@QAE@XZ is implemented by the exact
// retail thunk in WindModuleInfoCtorThunk.cpp.

// ??1BoxEmissionVolumeModuleTemplate@FXParticleSystem@@UAE@XZ
BoxEmissionVolumeModuleTemplate::~BoxEmissionVolumeModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f9ac;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??1ButterflyDrawModuleTemplate@FXParticleSystem@@UAE@XZ
// Body in ButterflyDrawModuleTemplate_dtor.asm (50B; ICF twin of Quad dtor).

// ??1CylinderEmissionVolumeModuleTemplate@FXParticleSystem@@UAE@XZ
CylinderEmissionVolumeModuleTemplate::~CylinderEmissionVolumeModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f9ac;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??1CylindricalEmissionVelocityModuleTemplate@FXParticleSystem@@UAE@XZ
CylindricalEmissionVelocityModuleTemplate::~CylindricalEmissionVelocityModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f9cc;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??1HemisphericalEmissionVelocityModuleTemplate@FXParticleSystem@@UAE@XZ
HemisphericalEmissionVelocityModuleTemplate::~HemisphericalEmissionVelocityModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f9cc;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??1LifeEventModuleInfo@FXParticleSystem@@UAE@XZ
__declspec(naked) LifeEventModuleInfo::~LifeEventModuleInfo()
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x98
        __emit 0xad
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x8d
        __emit 0x4e
        __emit 0x04
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0x53
        __emit 0x9b
        __emit 0x2a
        __emit 0x00
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0xc7
        __emit 0x06
        __emit 0x44
        __emit 0x37
        __emit 0x07
        __emit 0x01
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc3
    }
}

// ??1LifeEventModuleTemplate@FXParticleSystem@@UAE@XZ
__declspec(naked) LifeEventModuleTemplate::~LifeEventModuleTemplate()
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x00
        __emit 0xae
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xec
        __emit 0x08
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x57
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x0c
        __emit 0x85
        __emit 0xf6
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x05
        __emit 0x8d
        __emit 0x7e
        __emit 0x0c
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xff
        __emit 0x89
        __emit 0x7c
        __emit 0x24
        __emit 0x08
        __emit 0x8d
        __emit 0x4f
        __emit 0x04
        __emit 0xc6
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x01
        __emit 0xe8
        __emit 0x1c
        __emit 0x99
        __emit 0x2a
        __emit 0x00
        __emit 0x85
        __emit 0xf6
        __emit 0xc7
        __emit 0x07
        __emit 0x44
        __emit 0x37
        __emit 0x07
        __emit 0x01
        __emit 0x74
        __emit 0x09
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x5c
        __emit 0x37
        __emit 0x07
        __emit 0x01
        __emit 0xeb
        __emit 0x08
        __emit 0x33
        __emit 0xc0
        __emit 0xc7
        __emit 0x00
        __emit 0x5c
        __emit 0x37
        __emit 0x07
        __emit 0x01
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x10
        __emit 0xc7
        __emit 0x06
        __emit 0x58
        __emit 0x37
        __emit 0x07
        __emit 0x01
        __emit 0x5f
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x14
        __emit 0xc3
    }
}

// ??1LightningDrawModuleTemplate@FXParticleSystem@@UAE@XZ
LightningDrawModuleTemplate::~LightningDrawModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f97c;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??1LightningEmissionModuleTemplate@FXParticleSystem@@UAE@XZ
LightningEmissionModuleTemplate::~LightningEmissionModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f9ac;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??1LineEmissionVolumeModuleTemplate@FXParticleSystem@@UAE@XZ
LineEmissionVolumeModuleTemplate::~LineEmissionVolumeModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f9ac;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??1OrthoEmissionVelocityModuleTemplate@FXParticleSystem@@UAE@XZ
OrthoEmissionVelocityModuleTemplate::~OrthoEmissionVelocityModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f9cc;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??1OutwardEmissionVelocityModuleTemplate@FXParticleSystem@@UAE@XZ
OutwardEmissionVelocityModuleTemplate::~OutwardEmissionVelocityModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f9cc;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??1ParticleSystemInfo@FXParticleSystem@@UAE@XZ
__declspec(naked) ParticleSystemInfo::~ParticleSystemInfo()
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x3e
        __emit 0x26
        __emit 0xff
        __emit 0x00
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x8d
        __emit 0x4e
        __emit 0x78
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x02
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0x33
        __emit 0x8a
        __emit 0x82
        __emit 0x00
        __emit 0x8d
        __emit 0x4e
        __emit 0x68
        __emit 0xc6
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x01
        __emit 0xe8
        __emit 0x26
        __emit 0x8a
        __emit 0x82
        __emit 0x00
        __emit 0x8d
        __emit 0x4e
        __emit 0x10
        __emit 0xc6
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x00
        __emit 0xe8
        __emit 0x19
        __emit 0x8a
        __emit 0x82
        __emit 0x00
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0xc7
        __emit 0x06
        __emit 0x44
        __emit 0x37
        __emit 0x07
        __emit 0x01
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc3
    }
}

// ??1ParticleSystemTemplate@FXParticleSystem@@UAE@XZ
__declspec(naked) ParticleSystemTemplate::~ParticleSystemTemplate()
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xa6
        __emit 0xa4
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0xc7
        __emit 0x06
        __emit 0x64
        __emit 0xfe
        __emit 0x10
        __emit 0x01
        __emit 0x8d
        __emit 0x8e
        __emit 0xa0
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0xb9
        __emit 0x5f
        __emit 0xa5
        __emit 0xff
        __emit 0x8d
        __emit 0x8e
        __emit 0x98
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc6
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x00
        __emit 0xe8
        __emit 0x2a
        __emit 0x94
        __emit 0x2b
        __emit 0x00
        __emit 0x8b
        __emit 0xce
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0x39
        __emit 0x4a
        __emit 0xa3
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc3
    }
}

// ??1PointEmissionVolumeModuleTemplate@FXParticleSystem@@UAE@XZ
PointEmissionVolumeModuleTemplate::~PointEmissionVolumeModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f9ac;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??1QuadDrawModuleTemplate@FXParticleSystem@@UAE@XZ
struct QuadDrawDtorBody
{
    void destroy();
};

void QuadDrawDtorBody::destroy()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f97c;
    *(volatile unsigned int *)this = 0x01073758;
}
#pragma comment(linker, "/alternatename:??1QuadDrawModuleTemplate@FXParticleSystem@@UAE@XZ=?destroy@QuadDrawDtorBody@FXParticleSystem@@QAEXXZ")
#pragma comment(linker, "/alternatename:??1ButterflyDrawModuleTemplate@FXParticleSystem@@UAE@XZ=?destroy@QuadDrawDtorBody@FXParticleSystem@@QAEXXZ")

// ??1RenderObjectDrawModuleInfo@FXParticleSystem@@UAE@XZ
__declspec(naked) RenderObjectDrawModuleInfo::~RenderObjectDrawModuleInfo()
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x4e
        __emit 0xae
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x8d
        __emit 0x4e
        __emit 0x30
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x02
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0x23
        __emit 0x97
        __emit 0x2a
        __emit 0x00
        __emit 0x8d
        __emit 0x4e
        __emit 0x20
        __emit 0xc6
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x01
        __emit 0xe8
        __emit 0x16
        __emit 0x97
        __emit 0x2a
        __emit 0x00
        __emit 0x8d
        __emit 0x4e
        __emit 0x10
        __emit 0xc6
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x00
        __emit 0xe8
        __emit 0x09
        __emit 0x97
        __emit 0x2a
        __emit 0x00
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0xc7
        __emit 0x06
        __emit 0x44
        __emit 0x37
        __emit 0x07
        __emit 0x01
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc3
    }
}

// ??1RenderObjectDrawModuleTemplate@FXParticleSystem@@UAE@XZ
__declspec(naked) RenderObjectDrawModuleTemplate::~RenderObjectDrawModuleTemplate()
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xd8
        __emit 0xae
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x85
        __emit 0xf6
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x05
        __emit 0x8d
        __emit 0x4e
        __emit 0x08
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xc9
        __emit 0xe8
        __emit 0x3e
        __emit 0x44
        __emit 0xa4
        __emit 0xff
        __emit 0x85
        __emit 0xf6
        __emit 0x74
        __emit 0x09
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x7c
        __emit 0xf9
        __emit 0x10
        __emit 0x01
        __emit 0xeb
        __emit 0x08
        __emit 0x33
        __emit 0xc0
        __emit 0xc7
        __emit 0x00
        __emit 0x7c
        __emit 0xf9
        __emit 0x10
        __emit 0x01
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0xc7
        __emit 0x06
        __emit 0x58
        __emit 0x37
        __emit 0x07
        __emit 0x01
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc3
    }
}

// ??1SphereEmissionVolumeModuleTemplate@FXParticleSystem@@UAE@XZ
__declspec(naked) SphereEmissionVolumeModuleTemplate::~SphereEmissionVolumeModuleTemplate()
{
    __asm {
        __emit 0x85
        __emit 0xc9
        __emit 0x74
        __emit 0x05
        __emit 0x8d
        __emit 0x41
        __emit 0x08
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xc0
        __emit 0x85
        __emit 0xc9
        __emit 0xc7
        __emit 0x00
        __emit 0x44
        __emit 0x37
        __emit 0x07
        __emit 0x01
        __emit 0x74
        __emit 0x0e
        __emit 0xc7
        __emit 0x41
        __emit 0x04
        __emit 0xac
        __emit 0xf9
        __emit 0x10
        __emit 0x01
        __emit 0xc7
        __emit 0x01
        __emit 0x58
        __emit 0x37
        __emit 0x07
        __emit 0x01
        __emit 0xc3
        __emit 0x33
        __emit 0xc0
        __emit 0xc7
        __emit 0x00
        __emit 0xac
        __emit 0xf9
        __emit 0x10
        __emit 0x01
        __emit 0xc7
        __emit 0x01
        __emit 0x58
        __emit 0x37
        __emit 0x07
        __emit 0x01
        __emit 0xc3
    }
}

// ??1SphericalEmissionVelocityModuleTemplate@FXParticleSystem@@UAE@XZ
__declspec(naked) SphericalEmissionVelocityModuleTemplate::~SphericalEmissionVelocityModuleTemplate()
{
    __asm {
        __emit 0x85
        __emit 0xc9
        __emit 0x74
        __emit 0x05
        __emit 0x8d
        __emit 0x41
        __emit 0x08
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xc0
        __emit 0x85
        __emit 0xc9
        __emit 0xc7
        __emit 0x00
        __emit 0x44
        __emit 0x37
        __emit 0x07
        __emit 0x01
        __emit 0x74
        __emit 0x0e
        __emit 0xc7
        __emit 0x41
        __emit 0x04
        __emit 0xcc
        __emit 0xf9
        __emit 0x10
        __emit 0x01
        __emit 0xc7
        __emit 0x01
        __emit 0x58
        __emit 0x37
        __emit 0x07
        __emit 0x01
        __emit 0xc3
        __emit 0x33
        __emit 0xc0
        __emit 0xc7
        __emit 0x00
        __emit 0xcc
        __emit 0xf9
        __emit 0x10
        __emit 0x01
        __emit 0xc7
        __emit 0x01
        __emit 0x58
        __emit 0x37
        __emit 0x07
        __emit 0x01
        __emit 0xc3
    }
}

// ??1StreakDrawModuleTemplate@FXParticleSystem@@UAE@XZ
StreakDrawModuleTemplate::~StreakDrawModuleTemplate()
{
    unsigned char *info = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)info = 0x01073744;

    unsigned char *base = this ? (unsigned char *)this + 4 : 0;
    *(volatile unsigned int *)base = 0x0110f97c;
    *(volatile unsigned int *)this = 0x01073758;
}

// ??1TerrainCollisionModuleInfo@FXParticleSystem@@UAE@XZ
__declspec(naked) TerrainCollisionModuleInfo::~TerrainCollisionModuleInfo()
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x18
        __emit 0xaf
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x04
        __emit 0x8d
        __emit 0x4e
        __emit 0x04
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0xc3
        __emit 0x92
        __emit 0x2a
        __emit 0x00
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0xc7
        __emit 0x06
        __emit 0x44
        __emit 0x37
        __emit 0x07
        __emit 0x01
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xc3
    }
}

// ??1TerrainCollisionModuleTemplate@FXParticleSystem@@UAE@XZ
__declspec(naked) TerrainCollisionModuleTemplate::~TerrainCollisionModuleTemplate()
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x80
        __emit 0xaf
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xec
        __emit 0x08
        __emit 0x56
        __emit 0x8b
        __emit 0xf1
        __emit 0x57
        __emit 0x89
        __emit 0x74
        __emit 0x24
        __emit 0x0c
        __emit 0x85
        __emit 0xf6
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x05
        __emit 0x8d
        __emit 0x7e
        __emit 0x0c
        __emit 0xeb
        __emit 0x02
        __emit 0x33
        __emit 0xff
        __emit 0x89
        __emit 0x7c
        __emit 0x24
        __emit 0x08
        __emit 0x8d
        __emit 0x4f
        __emit 0x04
        __emit 0xc6
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x01
        __emit 0xe8
        __emit 0x8c
        __emit 0x90
        __emit 0x2a
        __emit 0x00
        __emit 0x85
        __emit 0xf6
        __emit 0xc7
        __emit 0x07
        __emit 0x44
        __emit 0x37
        __emit 0x07
        __emit 0x01
        __emit 0x74
        __emit 0x09
        __emit 0xc7
        __emit 0x46
        __emit 0x04
        __emit 0x5c
        __emit 0x37
        __emit 0x07
        __emit 0x01
        __emit 0xeb
        __emit 0x08
        __emit 0x33
        __emit 0xc0
        __emit 0xc7
        __emit 0x00
        __emit 0x5c
        __emit 0x37
        __emit 0x07
        __emit 0x01
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x10
        __emit 0xc7
        __emit 0x06
        __emit 0x58
        __emit 0x37
        __emit 0x07
        __emit 0x01
        __emit 0x5f
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x14
        __emit 0xc3
    }
}

// ??4BoxEmissionVolumeInfo@FXParticleSystem@@QAEAAV01@ABV01@@Z
BoxEmissionVolumeInfo &BoxEmissionVolumeInfo::operator=(const BoxEmissionVolumeInfo &that)
{
    struct Float3 {
        float x;
        float y;
        float z;
    };

    m_flag = that.m_flag;
    *(Float3 *)m_unk = *(const Float3 *)that.m_unk;
    return *this;
}

// ??4BoxEmissionVolumeModuleTemplate@FXParticleSystem@@QAEAAV01@ABV01@@Z
BoxEmissionVolumeModuleTemplate &BoxEmissionVolumeModuleTemplate::operator=(const BoxEmissionVolumeModuleTemplate &that)
{
    BoxEmissionVolumeInfo::operator=(that);
    return *this;
}

// ??4CylinderEmissionVolumeInfo@FXParticleSystem@@QAEAAV01@ABV01@@Z
CylinderEmissionVolumeInfo &CylinderEmissionVolumeInfo::operator=(const CylinderEmissionVolumeInfo &that)
{
    struct Float3 {
        float x;
        float y;
        float z;
    };

    m_flag = that.m_flag;
    m_unk[0] = that.m_unk[0];
    m_unk[1] = that.m_unk[1];
    *(Float3 *)&m_unk[2] = *(const Float3 *)&that.m_unk[2];
    return *this;
}

// ??4CylinderEmissionVolumeModuleTemplate@FXParticleSystem@@QAEAAV01@ABV01@@Z
CylinderEmissionVolumeModuleTemplate &CylinderEmissionVolumeModuleTemplate::operator=(const CylinderEmissionVolumeModuleTemplate &that)
{
    CylinderEmissionVolumeInfo::operator=(that);
    return *this;
}

CylindricalEmissionVelocityInfo &CylindricalEmissionVelocityInfo::operator=(const CylindricalEmissionVelocityInfo &that)
{
    struct VariableBlock {
        unsigned int value0;
        unsigned int value1;
        unsigned int value2;
    };

    *(VariableBlock *)&m_var0 = *(const VariableBlock *)&that.m_var0;
    *(VariableBlock *)&m_var1 = *(const VariableBlock *)&that.m_var1;
    return *this;
}

// ??4CylindricalEmissionVelocityModuleTemplate@FXParticleSystem@@QAEAAV01@ABV01@@Z
CylindricalEmissionVelocityModuleTemplate &CylindricalEmissionVelocityModuleTemplate::operator=(const CylindricalEmissionVelocityModuleTemplate &that)
{
    CylindricalEmissionVelocityInfo::operator=(that);
    return *this;
}

// ??4DefaultColorModuleInfo@FXParticleSystem@@QAEAAV01@ABV01@@Z
DefaultColorModuleInfo &DefaultColorModuleInfo::operator=(const DefaultColorModuleInfo &that)
{
    struct ColorKeyBlock {
        unsigned int value0;
        unsigned int value1;
        unsigned int value2;
        unsigned int value3;
    };
    struct VariableBlock {
        unsigned int value0;
        unsigned int value1;
        unsigned int value2;
    };

    *(ColorKeyBlock *)&m_colorKey[0] = *(const ColorKeyBlock *)&that.m_colorKey[0];
    *(ColorKeyBlock *)&m_colorKey[1] = *(const ColorKeyBlock *)&that.m_colorKey[1];
    *(ColorKeyBlock *)&m_colorKey[2] = *(const ColorKeyBlock *)&that.m_colorKey[2];
    *(ColorKeyBlock *)&m_colorKey[3] = *(const ColorKeyBlock *)&that.m_colorKey[3];
    *(ColorKeyBlock *)&m_colorKey[4] = *(const ColorKeyBlock *)&that.m_colorKey[4];
    *(ColorKeyBlock *)&m_colorKey[5] = *(const ColorKeyBlock *)&that.m_colorKey[5];
    *(ColorKeyBlock *)&m_colorKey[6] = *(const ColorKeyBlock *)&that.m_colorKey[6];
    *(ColorKeyBlock *)&m_colorKey[7] = *(const ColorKeyBlock *)&that.m_colorKey[7];
    *(VariableBlock *)&m_colorScale = *(const VariableBlock *)&that.m_colorScale;
    return *this;
}

// ??4DefaultPhysicsModuleInfo@FXParticleSystem@@QAEAAV01@ABV01@@Z
DefaultPhysicsModuleInfo &DefaultPhysicsModuleInfo::operator=(const DefaultPhysicsModuleInfo &that)
{
    struct Float3 {
        float x;
        float y;
        float z;
    };
    struct VariableBlock {
        unsigned int value0;
        unsigned int value1;
        unsigned int value2;
    };

    *(Float3 *)&m_field0 = *(const Float3 *)&that.m_field0;
    m_field3 = that.m_field3;
    *(VariableBlock *)&m_var1 = *(const VariableBlock *)&that.m_var1;
    return *this;
}

// ??4DefaultUpdateModuleInfo@FXParticleSystem@@QAEAAV01@ABV01@@Z
DefaultUpdateModuleInfo &DefaultUpdateModuleInfo::operator=(const DefaultUpdateModuleInfo &that)
{
    struct VariableBlock {
        unsigned int value0;
        unsigned int value1;
        unsigned int value2;
    };

    *(VariableBlock *)&m_var0 = *(const VariableBlock *)&that.m_var0;
    *(VariableBlock *)&m_var1 = *(const VariableBlock *)&that.m_var1;
    *(VariableBlock *)&m_var2 = *(const VariableBlock *)&that.m_var2;
    *(VariableBlock *)&m_var3 = *(const VariableBlock *)&that.m_var3;
    *(VariableBlock *)&m_var4 = *(const VariableBlock *)&that.m_var4;
    m_extra = that.m_extra;
    return *this;
}

EmissionVolumeInfo &EmissionVolumeInfo::operator=(const EmissionVolumeInfo &that)
{
    m_flag = that.m_flag;
    return *this;
}

// ??4HemisphericalEmissionVelocityModuleTemplate@FXParticleSystem@@QAEAAV01@ABV01@@Z
HemisphericalEmissionVelocityModuleTemplate &HemisphericalEmissionVelocityModuleTemplate::operator=(const HemisphericalEmissionVelocityModuleTemplate &that)
{
    SphericalEmissionVelocityInfo::operator=(that);
    return *this;
}

// ??4LifeEventModuleInfo@FXParticleSystem@@QAEAAV01@ABV01@@Z
LifeEventModuleInfo &LifeEventModuleInfo::operator=(const LifeEventModuleInfo &that)
{
    struct ThreeDwords {
        unsigned int value0;
        unsigned int value1;
        unsigned int value2;
    };

    unsigned char *destination = (unsigned char *)this;
    const unsigned char *source = (const unsigned char *)&that;
    ((LifeEventAsciiStringAssignShim *)(destination + 4))->assign(source + 4);
    *(ThreeDwords *)(destination + 8) = *(const ThreeDwords *)(source + 8);
    *(unsigned int *)(destination + 20) = *(const unsigned int *)(source + 20);
    return *this;
}

// ??4LifeEventModuleTemplate@FXParticleSystem@@QAEAAV01@ABV01@@Z
LifeEventModuleTemplate &LifeEventModuleTemplate::operator=(const LifeEventModuleTemplate &that)
{
    const void *src = &that;
    unsigned char *destination = (unsigned char *)this;
    const unsigned char *base = src ? (const unsigned char *)src + 8 : 0;
    *(unsigned short *)(destination + 8) = *(const unsigned short *)base;

    const unsigned char *info = src ? (const unsigned char *)src + 0x0c : 0;
    ((LifeEventAsciiStringAssignShim *)(destination + 0x10))->assign(info + 4);
    struct ThreeDwords {
        unsigned int value0;
        unsigned int value1;
        unsigned int value2;
    };
    *(ThreeDwords *)(destination + 0x14) = *(const ThreeDwords *)(info + 8);
    *(unsigned int *)(destination + 0x20) = *(const unsigned int *)(info + 0x14);
    return *this;
}

// ??4LightningDrawModuleInfo@FXParticleSystem@@QAEAAV01@ABV01@@Z
LightningDrawModuleInfo &LightningDrawModuleInfo::operator=(const LightningDrawModuleInfo &that)
{
    struct VariableBlock {
        unsigned int value0;
        unsigned int value1;
        unsigned int value2;
    };

    *(VariableBlock *)&m_gcrv1 = *(const VariableBlock *)&that.m_gcrv1;
    *(VariableBlock *)&m_gcrv2 = *(const VariableBlock *)&that.m_gcrv2;
    *(VariableBlock *)&m_gcrv3 = *(const VariableBlock *)&that.m_gcrv3;
    m_field28 = that.m_field28;
    m_flag = that.m_flag;
    return *this;
}

// ??4LightningDrawModuleTemplate@FXParticleSystem@@QAEAAV01@ABV01@@Z
LightningDrawModuleTemplate &LightningDrawModuleTemplate::operator=(const LightningDrawModuleTemplate &that)
{
    LightningDrawModuleInfo::operator=(that);
    return *this;
}

// ??4LightningEmissionModuleTemplate@FXParticleSystem@@QAEAAV01@ABV01@@Z
LightningEmissionModuleTemplate &LightningEmissionModuleTemplate::operator=(const LightningEmissionModuleTemplate &that)
{
    LightningEmissionInfo::operator=(that);
    return *this;
}

// ??4LineEmissionVolumeModuleTemplate@FXParticleSystem@@QAEAAV01@ABV01@@Z
LineEmissionVolumeModuleTemplate &LineEmissionVolumeModuleTemplate::operator=(const LineEmissionVolumeModuleTemplate &that)
{
	const void *src = &that;
	const unsigned char *base = src ? (const unsigned char *)src + 8 : 0;
	*((unsigned char *)this + 0x0c) = base[4];
	memcpy((unsigned char *)this + 0x10, base + 8, 12);
	memcpy((unsigned char *)this + 0x1c, base + 0x14, 12);
	return *this;
}

OrthoEmissionVelocityInfo &OrthoEmissionVelocityInfo::operator=(const OrthoEmissionVelocityInfo &that)
{
    struct VariableBlock {
        unsigned int value0;
        unsigned int value1;
        unsigned int value2;
    };

    *(VariableBlock *)&m_var0 = *(const VariableBlock *)&that.m_var0;
    *(VariableBlock *)&m_var1 = *(const VariableBlock *)&that.m_var1;
    *(VariableBlock *)&m_var2 = *(const VariableBlock *)&that.m_var2;
    return *this;
}

// ??4OrthoEmissionVelocityModuleTemplate@FXParticleSystem@@QAEAAV01@ABV01@@Z
OrthoEmissionVelocityModuleTemplate &OrthoEmissionVelocityModuleTemplate::operator=(const OrthoEmissionVelocityModuleTemplate &that)
{
    OrthoEmissionVelocityInfo::operator=(that);
    return *this;
}

OutwardEmissionVelocityInfo &OutwardEmissionVelocityInfo::operator=(const OutwardEmissionVelocityInfo &that)
{
    struct VariableBlock {
        unsigned int value0;
        unsigned int value1;
        unsigned int value2;
    };

    *(VariableBlock *)&m_var0 = *(const VariableBlock *)&that.m_var0;
    *(VariableBlock *)&m_var1 = *(const VariableBlock *)&that.m_var1;
    return *this;
}

// ??4OutwardEmissionVelocityModuleTemplate@FXParticleSystem@@QAEAAV01@ABV01@@Z
OutwardEmissionVelocityModuleTemplate &OutwardEmissionVelocityModuleTemplate::operator=(const OutwardEmissionVelocityModuleTemplate &that)
{
    OutwardEmissionVelocityInfo::operator=(that);
    return *this;
}

// ??4ParticleSystemInfo@FXParticleSystem@@QAEAAV01@ABV01@@Z
ParticleSystemInfo &ParticleSystemInfo::operator=(const ParticleSystemInfo &that)
{
    const unsigned char *source = (const unsigned char *)&that;
    unsigned char *destination = (unsigned char *)this;
    destination[4] = source[4];
    *(unsigned int *)(destination + 8) = *(const unsigned int *)(source + 8);
    *(unsigned int *)(destination + 0x0c) = *(const unsigned int *)(source + 0x0c);
    ((LifeEventAsciiStringAssignShim *)(destination + 0x10))->assign(source + 0x10);

    struct ThreeDwords {
        unsigned int value0;
        unsigned int value1;
        unsigned int value2;
    };

    *(ThreeDwords *)(destination + 0x14) = *(const ThreeDwords *)(source + 0x14);
    *(unsigned int *)(destination + 0x20) = *(const unsigned int *)(source + 0x20);
    *(unsigned int *)(destination + 0x24) = *(const unsigned int *)(source + 0x24);
    *(ThreeDwords *)(destination + 0x28) = *(const ThreeDwords *)(source + 0x28);
    *(ThreeDwords *)(destination + 0x34) = *(const ThreeDwords *)(source + 0x34);
    *(unsigned int *)(destination + 0x40) = *(const unsigned int *)(source + 0x40);
    *(ThreeDwords *)(destination + 0x44) = *(const ThreeDwords *)(source + 0x44);
    *(ThreeDwords *)(destination + 0x50) = *(const ThreeDwords *)(source + 0x50);
    *(ThreeDwords *)(destination + 0x5c) = *(const ThreeDwords *)(source + 0x5c);
    ((LifeEventAsciiStringAssignShim *)(destination + 0x68))->assign(source + 0x68);
    *(ThreeDwords *)(destination + 0x6c) = *(const ThreeDwords *)(source + 0x6c);
    ((LifeEventAsciiStringAssignShim *)(destination + 0x78))->assign(source + 0x78);
    *(unsigned int *)(destination + 0x7c) = *(const unsigned int *)(source + 0x7c);
    destination[0x80] = source[0x80];
    destination[0x81] = source[0x81];
    destination[0x82] = source[0x82];
    destination[0x83] = source[0x83];

    struct FourDwords {
        unsigned int value0;
        unsigned int value1;
        unsigned int value2;
        unsigned int value3;
    };

    *(FourDwords *)(destination + 0x84) = *(const FourDwords *)(source + 0x84);
    *(unsigned int *)(destination + 0x94) = *(const unsigned int *)(source + 0x94);
    return *this;
}

// ??4ParticleSystemTemplate@FXParticleSystem@@QAEAAV01@ABV01@@Z
ParticleSystemTemplate &ParticleSystemTemplate::operator=(const ParticleSystemTemplate &that)
{
    const unsigned char *source = (const unsigned char *)&that;
    ((ParticleSystemTemplateInfoAssignShim *)this)->assign(source);
    ((LifeEventAsciiStringAssignShim *)((unsigned char *)this + 0x98))->assign(source + 0x98);
    unsigned char *tail = (unsigned char *)this + 0xa0;
    *(unsigned int *)((unsigned char *)this + 0x9c) = 0;
    ((ParticleSystemTemplateTailAssignShim *)tail)->assign(source + 0xa0);
    return *this;
}

// ??4PointEmissionVolumeModuleTemplate@FXParticleSystem@@QAEAAV01@ABV01@@Z
PointEmissionVolumeModuleTemplate &PointEmissionVolumeModuleTemplate::operator=(const PointEmissionVolumeModuleTemplate &that)
{
    const EmissionVolumeInfo *info = (&that != 0) ? (const EmissionVolumeInfo *)&that : 0;
    m_flag = info->m_flag;
    return *this;
}

RandomAlphaKeyframe &RandomAlphaKeyframe::operator=(const RandomAlphaKeyframe &that)
{
    struct KeyBlock {
        unsigned int value0;
        unsigned int value1;
        unsigned int value2;
        unsigned int value3;
    };

    *(KeyBlock *)this = *(const KeyBlock *)&that;
    return *this;
}

// ??4RenderObjectDrawModuleInfo@FXParticleSystem@@QAEAAV01@ABV01@@Z
RenderObjectDrawModuleInfo &RenderObjectDrawModuleInfo::operator=(const RenderObjectDrawModuleInfo &that)
{
    const unsigned char *source = (const unsigned char *)&that;
    unsigned char *destination = (unsigned char *)this;
    destination[4] = source[4];
    *(unsigned int *)(destination + 8) = *(const unsigned int *)(source + 8);
    destination[0x0c] = source[0x0c];
    ((LifeEventAsciiStringAssignShim *)(destination + 0x10))->assign(source + 0x10);
    *(unsigned int *)(destination + 0x14) = *(const unsigned int *)(source + 0x14);
    *(unsigned int *)(destination + 0x18) = *(const unsigned int *)(source + 0x18);
    *(unsigned int *)(destination + 0x1c) = *(const unsigned int *)(source + 0x1c);
    ((LifeEventAsciiStringAssignShim *)(destination + 0x20))->assign(source + 0x20);
    *(unsigned int *)(destination + 0x24) = *(const unsigned int *)(source + 0x24);
    *(unsigned int *)(destination + 0x28) = *(const unsigned int *)(source + 0x28);
    *(unsigned int *)(destination + 0x2c) = *(const unsigned int *)(source + 0x2c);
    ((LifeEventAsciiStringAssignShim *)(destination + 0x30))->assign(source + 0x30);
    *(unsigned int *)(destination + 0x34) = *(const unsigned int *)(source + 0x34);
    *(unsigned int *)(destination + 0x38) = *(const unsigned int *)(source + 0x38);
    *(unsigned int *)(destination + 0x3c) = *(const unsigned int *)(source + 0x3c);
    return *this;
}

// ??4RenderObjectDrawModuleTemplate@FXParticleSystem@@QAEAAV01@ABV01@@Z
RenderObjectDrawModuleTemplate &RenderObjectDrawModuleTemplate::operator=(const RenderObjectDrawModuleTemplate &that)
{
    const void *source = &that;
    const unsigned char *info = source ? (const unsigned char *)source + 8 : 0;
    ((RenderObjectDrawTemplateAssignShim *)((unsigned char *)this + 8))->assign(info);
    return *this;
}

// ??4RenderObjectUpdateModuleInfo@FXParticleSystem@@QAEAAV01@ABV01@@Z
RenderObjectUpdateModuleInfo &RenderObjectUpdateModuleInfo::operator=(const RenderObjectUpdateModuleInfo &that)
{
    struct VariableBlock {
        unsigned int value0;
        unsigned int value1;
        unsigned int value2;
    };

    *(VariableBlock *)((char *)this + 0x4) = *(const VariableBlock *)((const char *)&that + 0x4);
    *(VariableBlock *)((char *)this + 0x10) = *(const VariableBlock *)((const char *)&that + 0x10);
    *(VariableBlock *)((char *)this + 0x1c) = *(const VariableBlock *)((const char *)&that + 0x1c);
    *(VariableBlock *)((char *)this + 0x28) = *(const VariableBlock *)((const char *)&that + 0x28);
    *(VariableBlock *)((char *)this + 0x34) = *(const VariableBlock *)((const char *)&that + 0x34);
    *(VariableBlock *)((char *)this + 0x40) = *(const VariableBlock *)((const char *)&that + 0x40);
    *(VariableBlock *)((char *)this + 0x4c) = *(const VariableBlock *)((const char *)&that + 0x4c);
    *(VariableBlock *)((char *)this + 0x58) = *(const VariableBlock *)((const char *)&that + 0x58);
    *(VariableBlock *)((char *)this + 0x64) = *(const VariableBlock *)((const char *)&that + 0x64);
    *(VariableBlock *)((char *)this + 0x70) = *(const VariableBlock *)((const char *)&that + 0x70);
    *(VariableBlock *)((char *)this + 0x7c) = *(const VariableBlock *)((const char *)&that + 0x7c);
    *(VariableBlock *)((char *)this + 0x88) = *(const VariableBlock *)((const char *)&that + 0x88);
    *(unsigned int *)((char *)this + 0x94) = *(const unsigned int *)((const char *)&that + 0x94);
    return *this;
}

// ??4RenderObjectUpdateModuleTemplate@FXParticleSystem@@QAEAAV01@ABV01@@Z
RenderObjectUpdateModuleTemplate &RenderObjectUpdateModuleTemplate::operator=(const RenderObjectUpdateModuleTemplate &that)
{
    const void *source = &that;
    const unsigned char *info = source ? (const unsigned char *)source + 8 : 0;
    ((RenderObjectUpdateTemplateAssignShim *)((unsigned char *)this + 8))->assign(info);
    return *this;
}

SphereEmissionVolumeInfo &SphereEmissionVolumeInfo::operator=(const SphereEmissionVolumeInfo &that)
{
    m_flag = that.m_flag;
    m_radius = that.m_radius;
    return *this;
}

// ??4SphereEmissionVolumeModuleTemplate@FXParticleSystem@@QAEAAV01@ABV01@@Z
SphereEmissionVolumeModuleTemplate &SphereEmissionVolumeModuleTemplate::operator=(const SphereEmissionVolumeModuleTemplate &that)
{
    SphereEmissionVolumeInfo::operator=(that);
    return *this;
}

SphericalEmissionVelocityInfo &SphericalEmissionVelocityInfo::operator=(const SphericalEmissionVelocityInfo &that)
{
    struct VariableBlock {
        unsigned int value0;
        unsigned int value1;
        unsigned int value2;
    };

    *(VariableBlock *)&m_var0 = *(const VariableBlock *)&that.m_var0;
    return *this;
}

// ??4SphericalEmissionVelocityModuleTemplate@FXParticleSystem@@QAEAAV01@ABV01@@Z
SphericalEmissionVelocityModuleTemplate &SphericalEmissionVelocityModuleTemplate::operator=(const SphericalEmissionVelocityModuleTemplate &that)
{
    SphericalEmissionVelocityInfo::operator=(that);
    return *this;
}

// ??4TerrainCollisionModuleInfo@FXParticleSystem@@QAEAAV01@ABV01@@Z
TerrainCollisionModuleInfo &TerrainCollisionModuleInfo::operator=(const TerrainCollisionModuleInfo &that)
{
    struct ThreeDwords {
        unsigned int value0;
        unsigned int value1;
        unsigned int value2;
    };

    unsigned char *destination = (unsigned char *)this;
    const unsigned char *source = (const unsigned char *)&that;
    ((LifeEventAsciiStringAssignShim *)(destination + 4))->assign(source + 4);
    *(ThreeDwords *)(destination + 8) = *(const ThreeDwords *)(source + 8);
    *(unsigned char *)(destination + 20) = *(const unsigned char *)(source + 20);
    *(unsigned int *)(destination + 24) = *(const unsigned int *)(source + 24);
    return *this;
}

// ??4TerrainCollisionModuleTemplate@FXParticleSystem@@QAEAAV01@ABV01@@Z
TerrainCollisionModuleTemplate &TerrainCollisionModuleTemplate::operator=(const TerrainCollisionModuleTemplate &that)
{
    const void *src = &that;
    unsigned char *destination = (unsigned char *)this;
    const unsigned char *base = src ? (const unsigned char *)src + 8 : 0;
    *(unsigned short *)(destination + 8) = *(const unsigned short *)base;

    const unsigned char *info = src ? (const unsigned char *)src + 0x0c : 0;
    ((LifeEventAsciiStringAssignShim *)(destination + 0x10))->assign(info + 4);
    struct ThreeDwords {
        unsigned int value0;
        unsigned int value1;
        unsigned int value2;
    };
    *(ThreeDwords *)(destination + 0x14) = *(const ThreeDwords *)(info + 8);
    *(unsigned char *)(destination + 0x20) = *(const unsigned char *)(info + 0x14);
    *(unsigned int *)(destination + 0x24) = *(const unsigned int *)(info + 0x18);
    return *this;
}

// ??4WindModuleInfo@FXParticleSystem@@QAEAAV01@ABV01@@Z
WindModuleInfo &WindModuleInfo::operator=(const WindModuleInfo &that)
{
    m_type = that.m_type;
    m_f0 = that.m_f0;
    m_f1 = that.m_f1;
    m_f2 = that.m_f2;
    m_f3 = that.m_f3;
    m_f4 = that.m_f4;
    m_f5 = that.m_f5;
    m_f6 = that.m_f6;
    m_f7 = that.m_f7;
    m_f8 = that.m_f8;
    m_f9 = that.m_f9;
    m_f10 = that.m_f10;
    m_f11 = that.m_f11;
    m_f12 = that.m_f12;
    m_flag = that.m_flag;
    m_i0 = that.m_i0;
    m_i1 = that.m_i1;
    return *this;
}

// ?DoXfer@ButterflyDrawModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z
void ButterflyDrawModuleInfo::DoXfer(Xfer &xfer)
{
    Xfer::Version v;
    v.data[0] = 1;
    v.data[1] = 1;
    xfer == v;
}

// ?DoXfer@DefaultAlphaModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z
void DefaultAlphaModuleInfo::DoXfer(Xfer &xfer)
{
    Xfer::Version v;
    v.data[0] = 1;
    v.data[1] = 1;
    xfer == v;
    for (int i = 0; i < 8; ++i) {
        xferRandomVariable(xfer, m_alphaKey[i].var);
        xfer == *(unsigned int *)&m_alphaKey[i].frame;
    }
}

// ?DoXfer@DefaultColorModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z
void DefaultColorModuleInfo::DoXfer(Xfer &xfer)
{
    Xfer::Version v;
    v.data[0] = 1;
    v.data[1] = 1;
    xfer == v;
    for (int i = 0; i < 8; ++i) {
        xfer == *(RGBColor *)&m_colorKey[i].red;
        xfer == *(unsigned int *)&m_colorKey[i].frame;
    }
    xferRandomVariable(xfer, m_colorScale);
}

// ?DoXfer@DefaultDrawModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z
void DefaultDrawModuleInfo::DoXfer(Xfer &xfer)
{
    Xfer::Version v;
    v.data[0] = 1;
    v.data[1] = 1;
    xfer == v;
}

// ?DoXfer@DefaultPhysicsModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z
void DefaultPhysicsModuleInfo::DoXfer(Xfer &xfer)
{
    Xfer::Version v;
    v.data[0] = 1;
    v.data[1] = 1;
    xfer == v;
    xfer == *(float *)&m_field3;
    xfer == *(Coord3DBase *)&m_field0;
    xferRandomVariable(xfer, m_var1);
}

// ?DoXfer@DefaultUpdateModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z
void DefaultUpdateModuleInfo::DoXfer(Xfer &xfer)
{
    if (xfer.IsLightCRC()) {
        return;
    }

    Xfer::Version v;
    v.data[0] = 1;
    v.data[1] = 1;
    xfer == v;
    xferRandomVariable(xfer, m_var0);
    xferRandomVariable(xfer, m_var1);
    xferRandomVariable(xfer, m_var2);
    xferRandomVariable(xfer, m_var3);
    xferRandomVariable(xfer, m_var4);
    xferInteger(xfer, m_extra);
}

// ?DoXfer@LifeEventModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z
void LifeEventModuleInfo::DoXfer(Xfer &xfer)
{
    if (xfer.IsLightCRC()) {
        return;
    }

    Xfer::Version version;
    version.data[0] = 1;
    version.data[1] = 1;
    xfer == version;
    xferRandomVariable(xfer,
                       *(GameClientRandomVariable *)((unsigned char *)this + 8));
    xfer == *(AsciiString *)((unsigned char *)this + 4);
}

// ?DoXfer@LightningDrawModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z
void LightningDrawModuleInfo::DoXfer(Xfer &xfer)
{
    Xfer::Version v;
    v.data[0] = 1;
    v.data[1] = 1;
    xfer == v;
    xferRandomVariable(xfer, m_gcrv1);
    xferRandomVariable(xfer, m_gcrv2);
    xferRandomVariable(xfer, m_gcrv3);
    xfer == *(float *)&m_field28;
    xfer == m_flag;
}

// ?DoXfer@ParticleSystemInfo@FXParticleSystem@@UAEXAAVXfer@@@Z
void ParticleSystemInfo::DoXfer(Xfer &xfer)
{
    if (xfer.IsLightCRC()) {
        return;
    }
    Xfer::Version v;
    v.data[0] = 1;
    v.data[1] = 2;
    xfer == v;
    xfer == *(bool *)((char *)this + 0x04);
    xferInteger(xfer, *(int *)((char *)this + 0x08));
    xferInteger(xfer, *(int *)((char *)this + 0x0c));
    xfer == *(AsciiString *)((char *)this + 0x10);
    xferRandomVariable(xfer, *(GameClientRandomVariable *)((char *)this + 0x14));
    xfer == *(unsigned int *)((char *)this + 0x20);
    xfer == *(unsigned int *)((char *)this + 0x24);
    xferRandomVariable(xfer, *(GameClientRandomVariable *)((char *)this + 0x28));
    xferRandomVariable(xfer, *(GameClientRandomVariable *)((char *)this + 0x34));
    xferRandomVariable(xfer, *(GameClientRandomVariable *)((char *)this + 0x44));
    xferRandomVariable(xfer, *(GameClientRandomVariable *)((char *)this + 0x50));
    xferRandomVariable(xfer, *(GameClientRandomVariable *)((char *)this + 0x5c));
    xfer == *(AsciiString *)((char *)this + 0x68);
    xfer == *(Coord3DBase *)((char *)this + 0x6c);
    xfer == *(AsciiString *)((char *)this + 0x78);
    xferInteger(xfer, *(int *)((char *)this + 0x7c));
    xfer == *(bool *)((char *)this + 0x80);
    xfer == *(bool *)((char *)this + 0x81);
    xfer == *(bool *)((char *)this + 0x82);
    xfer == *(bool *)((char *)this + 0x83);
    if (v.data[1] >= 2) {
        xfer == *(unsigned int *)((char *)this + 0x40);
        xfer.XferRawBytes((char *)this + 0x94, 4);
    }
}

// ?DoXfer@QuadDrawModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z
void QuadDrawModuleInfo::DoXfer(Xfer &xfer)
{
    Xfer::Version v;
    v.data[0] = 1;
    v.data[1] = 1;
    xfer == v;
}

// ?DoXfer@RenderObjectDrawModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z
void RenderObjectDrawModuleInfo::DoXfer(Xfer &xfer)
{
    Xfer::Version v;
    v.data[0] = 1;
    v.data[1] = 1;
    xfer == v;
    xfer == *(bool *)((char *)this + 0x0c);
    xfer == *(AsciiString *)((char *)this + 0x10);
    xfer == *(int *)((char *)this + 0x14);
    xfer == *(float *)((char *)this + 0x18);
    xferRandomVariable(xfer, *(GameClientRandomVariable *)((char *)this + 0x1c));
    xfer == *(AsciiString *)((char *)this + 0x20);
    xfer == *(int *)((char *)this + 0x24);
    xfer == *(float *)((char *)this + 0x28);
    xferRandomVariable(xfer, *(GameClientRandomVariable *)((char *)this + 0x2c));
    xfer == *(AsciiString *)((char *)this + 0x30);
    xfer == *(int *)((char *)this + 0x34);
    xfer == *(float *)((char *)this + 0x38);
    xferRandomVariable(xfer, *(GameClientRandomVariable *)((char *)this + 0x3c));
    xfer == *(bool *)((char *)this + 0x04);
    xfer == *(float *)((char *)this + 0x08);
}

// ?DoXfer@RenderObjectUpdateModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z
void RenderObjectUpdateModuleInfo::DoXfer(Xfer &xfer)
{
    if (xfer.IsLightCRC()) {
        return;
    }
    Xfer::Version v;
    v.data[0] = 1;
    v.data[1] = 1;
    xfer == v;
    xferRandomVariable(xfer, *(GameClientRandomVariable *)((char *)this + 0x04));
    xferRandomVariable(xfer, *(GameClientRandomVariable *)((char *)this + 0x10));
    xferRandomVariable(xfer, *(GameClientRandomVariable *)((char *)this + 0x1c));
    xferRandomVariable(xfer, *(GameClientRandomVariable *)((char *)this + 0x28));
    xferRandomVariable(xfer, *(GameClientRandomVariable *)((char *)this + 0x34));
    xferRandomVariable(xfer, *(GameClientRandomVariable *)((char *)this + 0x40));
    xferRandomVariable(xfer, *(GameClientRandomVariable *)((char *)this + 0x4c));
    xferRandomVariable(xfer, *(GameClientRandomVariable *)((char *)this + 0x58));
    xferRandomVariable(xfer, *(GameClientRandomVariable *)((char *)this + 0x64));
    xferRandomVariable(xfer, *(GameClientRandomVariable *)((char *)this + 0x70));
    xferRandomVariable(xfer, *(GameClientRandomVariable *)((char *)this + 0x7c));
    xferRandomVariable(xfer, *(GameClientRandomVariable *)((char *)this + 0x88));
    xferInteger(xfer, *(int *)((char *)this + 0x94));
}

// ?DoXfer@StreakDrawModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z
void StreakDrawModuleInfo::DoXfer(Xfer &xfer)
{
    Xfer::Version v;
    v.data[0] = 1;
    v.data[1] = 1;
    xfer == v;
}

// ?DoXfer@TerrainCollisionModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z
void TerrainCollisionModuleInfo::DoXfer(Xfer &xfer)
{
    Xfer::Version v;
    v.data[0] = 1;
    v.data[1] = 1;
    xfer == v;
    xferRandomVariable(xfer, *(GameClientRandomVariable *)((char *)this + 0x8));
    xfer == *(AsciiString *)((char *)this + 0x4);
    xfer == *(bool *)((char *)this + 0x14);
}

// ?DoXfer@WindModuleInfo@FXParticleSystem@@UAEXAAVXfer@@@Z
void WindModuleInfo::DoXfer(Xfer &xfer)
{
    if (xfer.IsLightCRC()) {
        return;
    }
    Xfer::Version v;
    v.data[0] = 1;
    v.data[1] = 1;
    xfer == v;
    xferInteger(xfer, m_type);
    xfer == m_f0;
    xfer == m_f1;
    xfer == m_f2;
    xfer == m_f3;
    xfer == m_f4;
    xfer == m_f5;
    xfer == m_f6;
    xfer == m_f7;
    xfer == m_f8;
    xfer == m_f9;
    xfer == m_f10;
    xfer == m_f11;
    xfer == m_f12;
    xfer == *(char *)((char *)this + 0x3c);
    xfer == *(float *)((char *)this + 0x40);
    xfer == *(float *)((char *)this + 0x44);
}

// ?createSlaveSystem@ParticleSystemTemplate@FXParticleSystem@@QBE?AV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@@_N@Z
__declspec(naked) TrackingPtr<ParticleSystem> ParticleSystemTemplate::createSlaveSystem(bool) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x38
        __emit 0x9f
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xec
        __emit 0x1c
        __emit 0x53
        __emit 0x33
        __emit 0xdb
        __emit 0x56
        __emit 0x33
        __emit 0xc0
        __emit 0x57
        __emit 0x8b
        __emit 0xf9
        __emit 0x89
        __emit 0x5c
        __emit 0x24
        __emit 0x0c
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x89
        __emit 0x5c
        __emit 0x24
        __emit 0x14
        __emit 0x89
        __emit 0x5c
        __emit 0x24
        __emit 0x18
        __emit 0x39
        __emit 0x9f
        __emit 0x9c
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x5c
        __emit 0x24
        __emit 0x30
        __emit 0x75
        __emit 0x62
        __emit 0x8b
        __emit 0x4f
        __emit 0x68
        __emit 0x3b
        __emit 0xcb
        __emit 0x8d
        __emit 0x57
        __emit 0x68
        __emit 0x74
        __emit 0x58
        __emit 0x66
        __emit 0x39
        __emit 0x59
        __emit 0x04
        __emit 0x74
        __emit 0x52
        __emit 0x8b
        __emit 0x0d
        __emit 0xbc
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0x81
        __emit 0xc1
        __emit 0x9c
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x52
        __emit 0x33
        __emit 0xf6
        __emit 0xe8
        __emit 0xa6
        __emit 0x44
        __emit 0xa4
        __emit 0xff
        __emit 0x3b
        __emit 0xc3
        __emit 0x74
        __emit 0x03
        __emit 0x8b
        __emit 0x70
        __emit 0x08
        __emit 0x3b
        __emit 0xf3
        __emit 0x89
        __emit 0xb7
        __emit 0x9c
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x29
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x3c
        __emit 0x50
        __emit 0x56
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x24
        __emit 0x51
        __emit 0x8b
        __emit 0x0d
        __emit 0xbc
        __emit 0x64
        __emit 0x2f
        __emit 0x01
        __emit 0xe8
        __emit 0x3f
        __emit 0x39
        __emit 0xa4
        __emit 0xff
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x14
        __emit 0xe8
        __emit 0x8b
        __emit 0x47
        __emit 0xa4
        __emit 0xff
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x1c
        __emit 0xe8
        __emit 0xd9
        __emit 0x86
        __emit 0xa4
        __emit 0xff
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x3b
        __emit 0xc3
        __emit 0x8b
        __emit 0x74
        __emit 0x24
        __emit 0x38
        __emit 0x89
        __emit 0x06
        __emit 0x74
        __emit 0x28
        __emit 0x8b
        __emit 0x90
        __emit 0x9c
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x56
        __emit 0x04
        __emit 0x89
        __emit 0x5e
        __emit 0x08
        __emit 0x89
        __emit 0xb0
        __emit 0x9c
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0x46
        __emit 0x04
        __emit 0x3b
        __emit 0xc3
        __emit 0x74
        __emit 0x05
        __emit 0x89
        __emit 0x70
        __emit 0x08
        __emit 0xeb
        __emit 0x10
        __emit 0x8b
        __emit 0x06
        __emit 0x89
        __emit 0xb0
        __emit 0x98
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xeb
        __emit 0x06
        __emit 0x89
        __emit 0x5e
        __emit 0x08
        __emit 0x89
        __emit 0x5e
        __emit 0x04
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x10
        __emit 0xe8
        __emit 0x94
        __emit 0x86
        __emit 0xa4
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x28
        __emit 0x5f
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0x5b
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x28
        __emit 0xc2
        __emit 0x08
        __emit 0x00
    }
}

// ?getEventFX@LifeEventModuleInfo@FXParticleSystem@@QAEPBVFXList@@XZ
const FXList *LifeEventModuleInfo::getEventFX()
{
    unsigned char *base = (unsigned char *)this;
    LifeEventInfoView *view = (LifeEventInfoView *)this;
    if (!view->cached) {
        TerrainCollisionFXNameShim *name = (TerrainCollisionFXNameShim *)(base + 4);
        view->cached = g_terrainCollisionEventFXListStore->lookup(
            name->m_text ? name->m_text + 8 : DefaultModuleName<8>::VALUE);
    }
    return view->cached;
}

// ?getEventFX@TerrainCollisionModuleInfo@FXParticleSystem@@QAEPBVFXList@@XZ
const FXList *TerrainCollisionModuleInfo::getEventFX()
{
    unsigned char *base = (unsigned char *)this;
    TerrainCollisionInfoView *view = (TerrainCollisionInfoView *)this;
    if (!view->cached) {
        TerrainCollisionFXNameShim *name = (TerrainCollisionFXNameShim *)(base + 4);
        _ReadWriteBarrier();
        view->cached = g_terrainCollisionEventFXListStore->lookup(
            name->m_text ? name->m_text + 8 : DefaultModuleName<8>::VALUE);
    }
    return view->cached;
}

// ?parse@BoxEmissionVolumeModuleTemplate@FXParticleSystem@@QAEXPAVINI@@@Z
void BoxEmissionVolumeModuleTemplate::parse(INI *ini)
{
    ini->initFromINI(this, BOX_EMISSION_VOLUME_MODULE_TEMPLATE_PARSE_TABLE);
}

// ?parse@ButterflyDrawModuleTemplate@FXParticleSystem@@QAEXPAVINI@@@Z
void ButterflyDrawModuleTemplate::parse(INI *ini)
{
    ini->initFromINI(this, BUTTERFLY_DRAW_MODULE_TEMPLATE_PARSE_TABLE);
}

// ?parse@CylinderEmissionVolumeModuleTemplate@FXParticleSystem@@QAEXPAVINI@@@Z
void CylinderEmissionVolumeModuleTemplate::parse(INI *ini)
{
    ini->initFromINI(this, CYLINDER_EMISSION_VOLUME_MODULE_TEMPLATE_PARSE_TABLE);
}

// ?parse@CylindricalEmissionVelocityModuleTemplate@FXParticleSystem@@QAEXPAVINI@@@Z
void CylindricalEmissionVelocityModuleTemplate::parse(INI *ini)
{
    ini->initFromINI(this, CYLINDRICAL_EMISSION_VELOCITY_MODULE_TEMPLATE_PARSE_TABLE);
}

// ?parse@LifeEventModuleTemplate@FXParticleSystem@@QAEXPAVINI@@@Z
void LifeEventModuleTemplate::parse(INI *ini)
{
    ini->initFromINI(this, LIFE_EVENT_MODULE_TEMPLATE_PARSE_TABLE);
}

// ?parse@LightningDrawModuleTemplate@FXParticleSystem@@QAEXPAVINI@@@Z
void LightningDrawModuleTemplate::parse(INI *ini)
{
    ini->initFromINI(this, LIGHTNING_DRAW_MODULE_TEMPLATE_PARSE_TABLE);
}

// ?parse@LightningEmissionModuleTemplate@FXParticleSystem@@QAEXPAVINI@@@Z
void LightningEmissionModuleTemplate::parse(INI *ini)
{
    ini->initFromINI(this, LIGHTNING_EMISSION_MODULE_TEMPLATE_PARSE_TABLE);
}

// ?parse@LineEmissionVolumeModuleTemplate@FXParticleSystem@@QAEXPAVINI@@@Z
void LineEmissionVolumeModuleTemplate::parse(INI *ini)
{
    ini->initFromINI(this, LINE_EMISSION_VOLUME_MODULE_TEMPLATE_PARSE_TABLE);
}

// ?parse@OrthoEmissionVelocityModuleTemplate@FXParticleSystem@@QAEXPAVINI@@@Z
void OrthoEmissionVelocityModuleTemplate::parse(INI *ini)
{
    ini->initFromINI(this, ORTHO_EMISSION_VELOCITY_MODULE_TEMPLATE_PARSE_TABLE);
}

// ?parse@OutwardEmissionVelocityModuleTemplate@FXParticleSystem@@QAEXPAVINI@@@Z
void OutwardEmissionVelocityModuleTemplate::parse(INI *ini)
{
    ini->initFromINI(this, OUTWARD_EMISSION_VELOCITY_MODULE_TEMPLATE_PARSE_TABLE);
}

// ?parse@ParticleSystemTemplate@FXParticleSystem@@SAXPAVINI@@PAX1PBX@Z
__declspec(naked) void ParticleSystemTemplate::parse(INI *ini, void *data, void *store, const void *userData)
{
    __asm {
        __emit 0x81
        __emit 0xec
        __emit 0x50
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x33
        __emit 0xc0
        __emit 0xb9
        __emit 0x50
        __emit 0x10
        __emit 0xc5
        __emit 0x00
        __emit 0x89
        __emit 0x4c
        __emit 0x24
        __emit 0x04
        __emit 0x89
        __emit 0x4c
        __emit 0x24
        __emit 0x24
        __emit 0x89
        __emit 0x4c
        __emit 0x24
        __emit 0x34
        __emit 0xb9
        __emit 0xe0
        __emit 0x1e
        __emit 0xc5
        __emit 0x00
        __emit 0xba
        __emit 0x00
        __emit 0x2e
        __emit 0xc5
        __emit 0x00
        __emit 0x89
        __emit 0x4c
        __emit 0x24
        __emit 0x44
        __emit 0x89
        __emit 0x4c
        __emit 0x24
        __emit 0x54
        __emit 0x89
        __emit 0x4c
        __emit 0x24
        __emit 0x74
        __emit 0xb9
        __emit 0x15
        __emit 0x66
        __emit 0x43
        __emit 0x00
        __emit 0xc7
        __emit 0x04
        __emit 0x24
        __emit 0x40
        __emit 0x16
        __emit 0x08
        __emit 0x01
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x08
        __emit 0x02
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x0c
        __emit 0x7c
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x38
        __emit 0xfb
        __emit 0x10
        __emit 0x01
        __emit 0x89
        __emit 0x54
        __emit 0x24
        __emit 0x14
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x1c
        __emit 0x04
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x20
        __emit 0x90
        __emit 0x27
        __emit 0x0f
        __emit 0x01
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x28
        __emit 0x80
        __emit 0x01
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x2c
        __emit 0x08
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x30
        __emit 0xdc
        __emit 0x0d
        __emit 0x08
        __emit 0x01
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x38
        __emit 0xb0
        __emit 0x01
        __emit 0x11
        __emit 0x01
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x3c
        __emit 0x0c
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x40
        __emit 0x28
        __emit 0xfb
        __emit 0x10
        __emit 0x01
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x48
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x4c
        __emit 0x10
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x50
        __emit 0x18
        __emit 0xfb
        __emit 0x10
        __emit 0x01
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x58
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x5c
        __emit 0x68
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x60
        __emit 0x04
        __emit 0xfb
        __emit 0x10
        __emit 0x01
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x64
        __emit 0x80
        __emit 0x33
        __emit 0xc5
        __emit 0x00
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x68
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x6c
        __emit 0x6c
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x70
        __emit 0xe4
        __emit 0xfa
        __emit 0x10
        __emit 0x01
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x78
        __emit 0xc7
        __emit 0x44
        __emit 0x24
        __emit 0x7c
        __emit 0x78
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0x80
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xec
        __emit 0x26
        __emit 0x0f
        __emit 0x01
        __emit 0x89
        __emit 0x8c
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x84
        __emit 0x24
        __emit 0x88
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0x8c
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x14
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0x90
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xd0
        __emit 0xfa
        __emit 0x10
        __emit 0x01
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0x94
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc0
        __emit 0x2a
        __emit 0xc5
        __emit 0x00
        __emit 0x89
        __emit 0x84
        __emit 0x24
        __emit 0x98
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0x9c
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x20
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xa0
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc4
        __emit 0xfa
        __emit 0x10
        __emit 0x01
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xa4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc0
        __emit 0x2a
        __emit 0xc5
        __emit 0x00
        __emit 0x89
        __emit 0x84
        __emit 0x24
        __emit 0xa8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xac
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x24
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xb0
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x08
        __emit 0xe3
        __emit 0x0e
        __emit 0x01
        __emit 0x89
        __emit 0x8c
        __emit 0x24
        __emit 0xb4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x84
        __emit 0x24
        __emit 0xb8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xbc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x28
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xc0
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xb4
        __emit 0xfa
        __emit 0x10
        __emit 0x01
        __emit 0x89
        __emit 0x8c
        __emit 0x24
        __emit 0xc4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x84
        __emit 0x24
        __emit 0xc8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xcc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x34
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xd0
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xa4
        __emit 0xfa
        __emit 0x10
        __emit 0x01
        __emit 0x89
        __emit 0x8c
        __emit 0x24
        __emit 0xd4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x84
        __emit 0x24
        __emit 0xd8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xdc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x44
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xe0
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x88
        __emit 0x31
        __emit 0x0f
        __emit 0x01
        __emit 0x89
        __emit 0x8c
        __emit 0x24
        __emit 0xe4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x84
        __emit 0x24
        __emit 0xe8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xf0
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0x2d
        __emit 0x08
        __emit 0x01
        __emit 0x89
        __emit 0x8c
        __emit 0x24
        __emit 0xf4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xfc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x5c
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0x00
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x90
        __emit 0xfa
        __emit 0x10
        __emit 0x01
        __emit 0x89
        __emit 0x94
        __emit 0x24
        __emit 0x04
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x84
        __emit 0x24
        __emit 0x08
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0x0c
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x80
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0x10
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0xfa
        __emit 0x10
        __emit 0x01
        __emit 0x89
        __emit 0x94
        __emit 0x24
        __emit 0x14
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x84
        __emit 0x24
        __emit 0x18
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0x1c
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0x20
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x54
        __emit 0xfa
        __emit 0x10
        __emit 0x01
        __emit 0x89
        __emit 0x94
        __emit 0x24
        __emit 0x24
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x84
        __emit 0x24
        __emit 0x28
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0x2c
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x82
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0x58
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x84
        __emit 0x24
        __emit 0x38
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x84
        __emit 0x24
        __emit 0x40
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x84
        __emit 0x24
        __emit 0x44
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x84
        __emit 0x24
        __emit 0x48
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x84
        __emit 0x24
        __emit 0x4c
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x04
        __emit 0x24
        __emit 0x50
        __emit 0x51
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0x5c
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0x38
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x40
        __emit 0xfa
        __emit 0x10
        __emit 0x01
        __emit 0x89
        __emit 0x94
        __emit 0x24
        __emit 0x3c
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0x44
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0xd9
        __emit 0x3a
        __emit 0x29
        __emit 0x00
        __emit 0x81
        __emit 0xc4
        __emit 0x50
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0xc3
    }
}

// ?parse@PointEmissionVolumeModuleTemplate@FXParticleSystem@@QAEXPAVINI@@@Z
void PointEmissionVolumeModuleTemplate::parse(INI *ini)
{
    ini->initFromINI(this, POINT_EMISSION_VOLUME_MODULE_TEMPLATE_PARSE_TABLE);
}

// ?parse@QuadDrawModuleTemplate@FXParticleSystem@@QAEXPAVINI@@@Z
void QuadDrawModuleTemplate::parse(INI *ini)
{
    ini->initFromINI(this, QUAD_DRAW_MODULE_TEMPLATE_PARSE_TABLE);
}

// ?parse@RenderObjectDrawModuleTemplate@FXParticleSystem@@QAEXPAVINI@@@Z
void RenderObjectDrawModuleTemplate::parse(INI *ini)
{
    ini->initFromINI(this, RENDER_OBJECT_DRAW_MODULE_TEMPLATE_PARSE_TABLE);
}

// ?parse@RenderObjectUpdateModuleTemplate@FXParticleSystem@@QAEXPAVINI@@@Z
void RenderObjectUpdateModuleTemplate::parse(INI *ini)
{
    ini->initFromINI(this, RENDER_OBJECT_UPDATE_MODULE_TEMPLATE_PARSE_TABLE);
}

// ?parse@SphereEmissionVolumeModuleTemplate@FXParticleSystem@@QAEXPAVINI@@@Z
void SphereEmissionVolumeModuleTemplate::parse(INI *ini)
{
    ini->initFromINI(this, SPHERE_EMISSION_VOLUME_MODULE_TEMPLATE_PARSE_TABLE);
}

// ?parse@SphericalEmissionVelocityModuleTemplate@FXParticleSystem@@QAEXPAVINI@@@Z
void SphericalEmissionVelocityModuleTemplate::parse(INI *ini)
{
    ini->initFromINI(this, SPHERICAL_EMISSION_VELOCITY_MODULE_TEMPLATE_PARSE_TABLE);
}

// ?parse@StreakDrawModuleTemplate@FXParticleSystem@@QAEXPAVINI@@@Z
void StreakDrawModuleTemplate::parse(INI *ini)
{
    ini->initFromINI(this, STREAK_DRAW_MODULE_TEMPLATE_PARSE_TABLE);
}

// ?parse@TerrainCollisionModuleTemplate@FXParticleSystem@@QAEXPAVINI@@@Z
void TerrainCollisionModuleTemplate::parse(INI *ini)
{
    ini->initFromINI(this, TERRAIN_COLLISION_MODULE_TEMPLATE_PARSE_TABLE);
}

// ?parseEventFXListName@LifeEventModuleTemplate@FXParticleSystem@@SAXPAVINI@@PAX1PBX@Z
void LifeEventModuleTemplate::parseEventFXListName(INI *ini, void *data, void *store, const void *userData)
{
    INI::parseFXList(ini, data, store, 0);
}

// ?parseEventFXListName@TerrainCollisionModuleTemplate@FXParticleSystem@@SAXPAVINI@@PAX1PBX@Z
void TerrainCollisionModuleTemplate::parseEventFXListName(INI *ini, void *data, void *store, const void *userData)
{
    INI::parseFXList(ini, data, store, 0);
}

// ?tintAllColors@DefaultColorModuleInfo@FXParticleSystem@@QAEXH@Z
__declspec(naked) void DefaultColorModuleInfo::tintAllColors(int tint)
{
    __asm {
        __emit 0x83
        __emit 0xec
        __emit 0x0c
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x8b
        __emit 0xd0
        __emit 0xc1
        __emit 0xfa
        __emit 0x10
        __emit 0x81
        __emit 0xe2
        __emit 0xff
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x54
        __emit 0x24
        __emit 0x10
        __emit 0xdb
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x8b
        __emit 0xd0
        __emit 0xc1
        __emit 0xfa
        __emit 0x08
        __emit 0x81
        __emit 0xe2
        __emit 0xff
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xd8
        __emit 0x0d
        __emit 0x4c
        __emit 0xc6
        __emit 0x07
        __emit 0x01
        __emit 0x89
        __emit 0x54
        __emit 0x24
        __emit 0x10
        __emit 0xdb
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x25
        __emit 0xff
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x6a
        __emit 0x01
        __emit 0xd8
        __emit 0x0d
        __emit 0x4c
        __emit 0xc6
        __emit 0x07
        __emit 0x01
        __emit 0xdb
        __emit 0x44
        __emit 0x24
        __emit 0x14
        __emit 0xd8
        __emit 0x0d
        __emit 0x4c
        __emit 0xc6
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x0c
        __emit 0xd9
        __emit 0xc1
        __emit 0xd8
        __emit 0x49
        __emit 0x14
        __emit 0xd9
        __emit 0x59
        __emit 0x14
        __emit 0xd9
        __emit 0xc0
        __emit 0xd8
        __emit 0x49
        __emit 0x18
        __emit 0xd9
        __emit 0x59
        __emit 0x18
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x0c
        __emit 0xd8
        __emit 0x49
        __emit 0x1c
        __emit 0xd9
        __emit 0x59
        __emit 0x1c
        __emit 0xd9
        __emit 0xc1
        __emit 0xd8
        __emit 0x49
        __emit 0x24
        __emit 0xd9
        __emit 0x59
        __emit 0x24
        __emit 0xd9
        __emit 0xc0
        __emit 0xd8
        __emit 0x49
        __emit 0x28
        __emit 0xd9
        __emit 0x59
        __emit 0x28
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x0c
        __emit 0xd8
        __emit 0x49
        __emit 0x2c
        __emit 0xd9
        __emit 0x59
        __emit 0x2c
        __emit 0xd9
        __emit 0xc1
        __emit 0xd8
        __emit 0x49
        __emit 0x34
        __emit 0xd9
        __emit 0x59
        __emit 0x34
        __emit 0xd9
        __emit 0xc0
        __emit 0xd8
        __emit 0x49
        __emit 0x38
        __emit 0xd9
        __emit 0x59
        __emit 0x38
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x0c
        __emit 0xd8
        __emit 0x49
        __emit 0x3c
        __emit 0xd9
        __emit 0x59
        __emit 0x3c
        __emit 0xd9
        __emit 0xc1
        __emit 0xd8
        __emit 0x49
        __emit 0x44
        __emit 0xd9
        __emit 0x59
        __emit 0x44
        __emit 0xd9
        __emit 0xc0
        __emit 0xd8
        __emit 0x49
        __emit 0x48
        __emit 0xd9
        __emit 0x59
        __emit 0x48
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x0c
        __emit 0xd8
        __emit 0x49
        __emit 0x4c
        __emit 0xd9
        __emit 0x59
        __emit 0x4c
        __emit 0xd9
        __emit 0xc1
        __emit 0xd8
        __emit 0x49
        __emit 0x54
        __emit 0xd9
        __emit 0x59
        __emit 0x54
        __emit 0xd9
        __emit 0xc0
        __emit 0xd8
        __emit 0x49
        __emit 0x58
        __emit 0xd9
        __emit 0x59
        __emit 0x58
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x0c
        __emit 0xd8
        __emit 0x49
        __emit 0x5c
        __emit 0xd9
        __emit 0x59
        __emit 0x5c
        __emit 0xd9
        __emit 0xc1
        __emit 0xd8
        __emit 0x49
        __emit 0x64
        __emit 0xd9
        __emit 0x59
        __emit 0x64
        __emit 0xd9
        __emit 0xc0
        __emit 0xd8
        __emit 0x49
        __emit 0x68
        __emit 0xd9
        __emit 0x59
        __emit 0x68
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x0c
        __emit 0xd8
        __emit 0x49
        __emit 0x6c
        __emit 0xd9
        __emit 0x59
        __emit 0x6c
        __emit 0xd9
        __emit 0xc9
        __emit 0xd8
        __emit 0x49
        __emit 0x74
        __emit 0xd9
        __emit 0x59
        __emit 0x74
        __emit 0xd8
        __emit 0x49
        __emit 0x78
        __emit 0xd9
        __emit 0x59
        __emit 0x78
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x0c
        __emit 0xd8
        __emit 0x49
        __emit 0x7c
        __emit 0xd9
        __emit 0x59
        __emit 0x7c
        __emit 0x6a
        __emit 0x00
        __emit 0x6a
        __emit 0x00
        __emit 0x81
        __emit 0xc1
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0x83
        __emit 0x74
        __emit 0xa1
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x0c
        __emit 0xc2
        __emit 0x04
        __emit 0x00
    }
}

// ?writeINI@BoxEmissionVolumeModuleTemplate@FXParticleSystem@@UBEXAAVFile@@I@Z
__declspec(naked) void BoxEmissionVolumeModuleTemplate::writeINI(File &file, unsigned int flags) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x86
        __emit 0xc6
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0xec
        __emit 0xdc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x56
        __emit 0x57
        __emit 0x8b
        __emit 0xbc
        __emit 0x24
        __emit 0xf4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x8b
        __emit 0xf1
        __emit 0x57
        __emit 0x56
        __emit 0xe8
        __emit 0x12
        __emit 0xf9
        __emit 0xa2
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x0c
        __emit 0x6a
        __emit 0x01
        __emit 0x6a
        __emit 0x10
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x1c
        __emit 0xe8
        __emit 0xaa
        __emit 0x55
        __emit 0xa3
        __emit 0xff
        __emit 0x8a
        __emit 0x4e
        __emit 0x0c
        __emit 0x84
        __emit 0xc9
        __emit 0x8d
        __emit 0x46
        __emit 0x0c
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1b
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x68
        __emit 0x7c
        __emit 0x3a
        __emit 0x11
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x20
        __emit 0x52
        __emit 0xe8
        __emit 0x49
        __emit 0x87
        __emit 0xa0
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x10
        __emit 0xd9
        __emit 0x01
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x24
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0x70
        __emit 0x3a
        __emit 0x11
        __emit 0x01
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x20
        __emit 0x51
        __emit 0xe8
        __emit 0x2f
        __emit 0xf5
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x08
        __emit 0x52
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x18
        __emit 0xe8
        __emit 0x60
        __emit 0x3c
        __emit 0xa2
        __emit 0xff
        __emit 0x8b
        __emit 0x08
        __emit 0x8b
        __emit 0x40
        __emit 0x04
        __emit 0x8b
        __emit 0x17
        __emit 0x2b
        __emit 0xc1
        __emit 0x50
        __emit 0x51
        __emit 0x8b
        __emit 0xcf
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0xf4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x01
        __emit 0xff
        __emit 0x52
        __emit 0x10
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x2b
        __emit 0xc1
        __emit 0x85
        __emit 0xc9
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1c
        __emit 0x3d
        __emit 0x80
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x76
        __emit 0x0b
        __emit 0x51
        __emit 0xe8
        __emit 0xaf
        __emit 0x90
        __emit 0x28
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xeb
        __emit 0x0a
        __emit 0x50
        __emit 0x51
        __emit 0xe8
        __emit 0xe3
        __emit 0x57
        __emit 0x23
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x57
        __emit 0xe8
        __emit 0x6e
        __emit 0xd3
        __emit 0xa4
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0x42
        __emit 0x0a
        __emit 0xa3
        __emit 0xff
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc4
        __emit 0xeb
        __emit 0x12
        __emit 0x01
        __emit 0xe8
        __emit 0xe1
        __emit 0x68
        __emit 0x24
        __emit 0x00
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xe4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x5f
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0xc4
        __emit 0xe8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc2
        __emit 0x08
        __emit 0x00
    }
}

// ?writeINI@ButterflyDrawModuleTemplate@FXParticleSystem@@UBEXAAVFile@@I@Z
void ButterflyDrawModuleTemplate::writeINI(File &file, unsigned int flags) const
{
    writeDrawTemplateBase(this, file, &flags);
    writeDrawInfo(file, &flags);
}

// ?writeINI@CylinderEmissionVolumeModuleTemplate@FXParticleSystem@@UBEXAAVFile@@I@Z
__declspec(naked) void CylinderEmissionVolumeModuleTemplate::writeINI(File &file, unsigned int flags) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x16
        __emit 0xc7
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0xec
        __emit 0xdc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x56
        __emit 0x57
        __emit 0x8b
        __emit 0xbc
        __emit 0x24
        __emit 0xf4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x8b
        __emit 0xf1
        __emit 0x57
        __emit 0x56
        __emit 0xe8
        __emit 0x42
        __emit 0xf0
        __emit 0xa2
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x0c
        __emit 0x6a
        __emit 0x01
        __emit 0x6a
        __emit 0x10
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x1c
        __emit 0xe8
        __emit 0xda
        __emit 0x4c
        __emit 0xa3
        __emit 0xff
        __emit 0x8a
        __emit 0x4e
        __emit 0x0c
        __emit 0x84
        __emit 0xc9
        __emit 0x8d
        __emit 0x46
        __emit 0x0c
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1b
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x68
        __emit 0x7c
        __emit 0x3a
        __emit 0x11
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x20
        __emit 0x52
        __emit 0xe8
        __emit 0x79
        __emit 0x7e
        __emit 0xa0
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x10
        __emit 0xd9
        __emit 0x01
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0x10
        __emit 0xee
        __emit 0x08
        __emit 0x01
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x20
        __emit 0x51
        __emit 0xe8
        __emit 0x29
        __emit 0x66
        __emit 0xa2
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x14
        __emit 0xd9
        __emit 0x01
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x94
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0x94
        __emit 0x3c
        __emit 0x11
        __emit 0x01
        __emit 0x52
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x20
        __emit 0x50
        __emit 0xe8
        __emit 0xfa
        __emit 0x65
        __emit 0xa2
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x18
        __emit 0xd9
        __emit 0x01
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x24
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x51
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xfc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x68
        __emit 0xa4
        __emit 0xf2
        __emit 0x09
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x20
        __emit 0x52
        __emit 0xe8
        __emit 0x01
        __emit 0xec
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x18
        __emit 0xe8
        __emit 0x32
        __emit 0x33
        __emit 0xa2
        __emit 0xff
        __emit 0x8b
        __emit 0x08
        __emit 0x8b
        __emit 0x40
        __emit 0x04
        __emit 0x8b
        __emit 0x17
        __emit 0x2b
        __emit 0xc1
        __emit 0x50
        __emit 0x51
        __emit 0x8b
        __emit 0xcf
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0xf4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x01
        __emit 0xff
        __emit 0x52
        __emit 0x10
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x2b
        __emit 0xc1
        __emit 0x85
        __emit 0xc9
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1c
        __emit 0x3d
        __emit 0x80
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x76
        __emit 0x0b
        __emit 0x51
        __emit 0xe8
        __emit 0x81
        __emit 0x87
        __emit 0x28
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xeb
        __emit 0x0a
        __emit 0x50
        __emit 0x51
        __emit 0xe8
        __emit 0xb5
        __emit 0x4e
        __emit 0x23
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x57
        __emit 0xe8
        __emit 0x40
        __emit 0xca
        __emit 0xa4
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0x14
        __emit 0x01
        __emit 0xa3
        __emit 0xff
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc4
        __emit 0xeb
        __emit 0x12
        __emit 0x01
        __emit 0xe8
        __emit 0xb3
        __emit 0x5f
        __emit 0x24
        __emit 0x00
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xe4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x5f
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0xc4
        __emit 0xe8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc2
        __emit 0x08
        __emit 0x00
    }
}

// ?writeINI@CylindricalEmissionVelocityModuleTemplate@FXParticleSystem@@UBEXAAVFile@@I@Z
__declspec(naked) void CylindricalEmissionVelocityModuleTemplate::writeINI(File &file, unsigned int flags) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xe6
        __emit 0xc6
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0xec
        __emit 0xdc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x56
        __emit 0x57
        __emit 0x8b
        __emit 0xbc
        __emit 0x24
        __emit 0xf4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x8b
        __emit 0xf1
        __emit 0x57
        __emit 0x56
        __emit 0xe8
        __emit 0x1f
        __emit 0xe5
        __emit 0xa2
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x0c
        __emit 0x6a
        __emit 0x01
        __emit 0x6a
        __emit 0x10
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x1c
        __emit 0xe8
        __emit 0x2a
        __emit 0x51
        __emit 0xa3
        __emit 0xff
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x46
        __emit 0x10
        __emit 0x8d
        __emit 0x4e
        __emit 0x0c
        __emit 0xda
        __emit 0xe9
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x51
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xfc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x68
        __emit 0x0c
        __emit 0xa9
        __emit 0x0f
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x20
        __emit 0x52
        __emit 0xe8
        __emit 0x85
        __emit 0xa1
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x18
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0x3c
        __emit 0xc3
        __emit 0x09
        __emit 0x01
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x20
        __emit 0x51
        __emit 0xe8
        __emit 0x43
        __emit 0xa1
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x08
        __emit 0x52
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x18
        __emit 0xe8
        __emit 0xd4
        __emit 0x37
        __emit 0xa2
        __emit 0xff
        __emit 0x8b
        __emit 0x08
        __emit 0x8b
        __emit 0x40
        __emit 0x04
        __emit 0x8b
        __emit 0x17
        __emit 0x2b
        __emit 0xc1
        __emit 0x50
        __emit 0x51
        __emit 0x8b
        __emit 0xcf
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0xf4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x01
        __emit 0xff
        __emit 0x52
        __emit 0x10
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x2b
        __emit 0xc1
        __emit 0x85
        __emit 0xc9
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1c
        __emit 0x3d
        __emit 0x80
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x76
        __emit 0x0b
        __emit 0x51
        __emit 0xe8
        __emit 0x23
        __emit 0x8c
        __emit 0x28
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xeb
        __emit 0x0a
        __emit 0x50
        __emit 0x51
        __emit 0xe8
        __emit 0x57
        __emit 0x53
        __emit 0x23
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x57
        __emit 0xe8
        __emit 0xe2
        __emit 0xce
        __emit 0xa4
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0xb6
        __emit 0x05
        __emit 0xa3
        __emit 0xff
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc4
        __emit 0xeb
        __emit 0x12
        __emit 0x01
        __emit 0xe8
        __emit 0x55
        __emit 0x64
        __emit 0x24
        __emit 0x00
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xe4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x5f
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0xc4
        __emit 0xe8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc2
        __emit 0x08
        __emit 0x00
    }
}

// ?writeINI@LifeEventModuleTemplate@FXParticleSystem@@UBEXAAVFile@@I@Z
__declspec(naked) void LifeEventModuleTemplate::writeINI(File &file, unsigned int flags) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xa6
        __emit 0xc9
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0xec
        __emit 0xdc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x56
        __emit 0x57
        __emit 0x8b
        __emit 0xbc
        __emit 0x24
        __emit 0xf4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x8b
        __emit 0xf1
        __emit 0x57
        __emit 0x56
        __emit 0xe8
        __emit 0x04
        __emit 0xab
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x0c
        __emit 0x6a
        __emit 0x01
        __emit 0x6a
        __emit 0x10
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x1c
        __emit 0xe8
        __emit 0x8a
        __emit 0x15
        __emit 0xa3
        __emit 0xff
        __emit 0x8b
        __emit 0x94
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x4e
        __emit 0x14
        __emit 0x51
        __emit 0x68
        __emit 0x40
        __emit 0x44
        __emit 0x11
        __emit 0x01
        __emit 0x52
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x20
        __emit 0x50
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xfc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0x09
        __emit 0x66
        __emit 0xa3
        __emit 0xff
        __emit 0x8b
        __emit 0x94
        __emit 0x24
        __emit 0x08
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x4e
        __emit 0x10
        __emit 0x51
        __emit 0x68
        __emit 0x34
        __emit 0x44
        __emit 0x11
        __emit 0x01
        __emit 0x52
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x30
        __emit 0x50
        __emit 0xe8
        __emit 0x5d
        __emit 0x88
        __emit 0xa3
        __emit 0xff
        __emit 0x8b
        __emit 0x94
        __emit 0x24
        __emit 0x18
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x4e
        __emit 0x08
        __emit 0x51
        __emit 0x68
        __emit 0x24
        __emit 0x44
        __emit 0x11
        __emit 0x01
        __emit 0x52
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x40
        __emit 0x50
        __emit 0xe8
        __emit 0xfa
        __emit 0x46
        __emit 0xa0
        __emit 0xff
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0x28
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc6
        __emit 0x09
        __emit 0x56
        __emit 0x68
        __emit 0x10
        __emit 0x44
        __emit 0x11
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x50
        __emit 0x52
        __emit 0xe8
        __emit 0xdf
        __emit 0x46
        __emit 0xa0
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x40
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x18
        __emit 0xe8
        __emit 0x49
        __emit 0xfc
        __emit 0xa1
        __emit 0xff
        __emit 0x8b
        __emit 0x08
        __emit 0x8b
        __emit 0x40
        __emit 0x04
        __emit 0x8b
        __emit 0x17
        __emit 0x2b
        __emit 0xc1
        __emit 0x50
        __emit 0x51
        __emit 0x8b
        __emit 0xcf
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0xf4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x01
        __emit 0xff
        __emit 0x52
        __emit 0x10
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x2b
        __emit 0xc1
        __emit 0x85
        __emit 0xc9
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1c
        __emit 0x3d
        __emit 0x80
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x76
        __emit 0x0b
        __emit 0x51
        __emit 0xe8
        __emit 0x98
        __emit 0x50
        __emit 0x28
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xeb
        __emit 0x0a
        __emit 0x50
        __emit 0x51
        __emit 0xe8
        __emit 0xcc
        __emit 0x17
        __emit 0x23
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x57
        __emit 0xe8
        __emit 0x57
        __emit 0x93
        __emit 0xa4
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0x2b
        __emit 0xca
        __emit 0xa2
        __emit 0xff
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc4
        __emit 0xeb
        __emit 0x12
        __emit 0x01
        __emit 0xe8
        __emit 0xca
        __emit 0x28
        __emit 0x24
        __emit 0x00
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xe4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x5f
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0xc4
        __emit 0xe8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc2
        __emit 0x08
        __emit 0x00
    }
}

// ?writeINI@LightningDrawModuleTemplate@FXParticleSystem@@UBEXAAVFile@@I@Z
__declspec(naked) void LightningDrawModuleTemplate::writeINI(File &file, unsigned int flags) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x16
        __emit 0xc5
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0xec
        __emit 0xdc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x56
        __emit 0x57
        __emit 0x8b
        __emit 0xbc
        __emit 0x24
        __emit 0xf4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x8b
        __emit 0xf1
        __emit 0x57
        __emit 0x56
        __emit 0xe8
        __emit 0x44
        __emit 0x0f
        __emit 0xa5
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x0c
        __emit 0x6a
        __emit 0x01
        __emit 0x6a
        __emit 0x10
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x1c
        __emit 0xe8
        __emit 0x4a
        __emit 0x91
        __emit 0xa3
        __emit 0xff
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x46
        __emit 0x10
        __emit 0x8d
        __emit 0x4e
        __emit 0x0c
        __emit 0xda
        __emit 0xe9
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x51
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xfc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x68
        __emit 0xd8
        __emit 0x36
        __emit 0x11
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x20
        __emit 0x52
        __emit 0xe8
        __emit 0xa5
        __emit 0xe1
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x18
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0xcc
        __emit 0x36
        __emit 0x11
        __emit 0x01
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x20
        __emit 0x51
        __emit 0xe8
        __emit 0x63
        __emit 0xe1
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x24
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x94
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0xc0
        __emit 0x36
        __emit 0x11
        __emit 0x01
        __emit 0x52
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x20
        __emit 0x50
        __emit 0xe8
        __emit 0x21
        __emit 0xe1
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x30
        __emit 0xd9
        __emit 0x01
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x51
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xfc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x68
        __emit 0xb0
        __emit 0x36
        __emit 0x11
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x20
        __emit 0x52
        __emit 0xe8
        __emit 0xf8
        __emit 0xa9
        __emit 0xa2
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8a
        __emit 0x4e
        __emit 0x34
        __emit 0x84
        __emit 0xc9
        __emit 0x8d
        __emit 0x46
        __emit 0x34
        __emit 0x74
        __emit 0x1b
        __emit 0x50
        __emit 0x8b
        __emit 0x84
        __emit 0x24
        __emit 0xfc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x68
        __emit 0xa0
        __emit 0x36
        __emit 0x11
        __emit 0x01
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x20
        __emit 0x51
        __emit 0xe8
        __emit 0xf4
        __emit 0xc1
        __emit 0xa0
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x08
        __emit 0x52
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x18
        __emit 0xe8
        __emit 0x5e
        __emit 0x77
        __emit 0xa2
        __emit 0xff
        __emit 0x8b
        __emit 0x08
        __emit 0x8b
        __emit 0x40
        __emit 0x04
        __emit 0x8b
        __emit 0x17
        __emit 0x2b
        __emit 0xc1
        __emit 0x50
        __emit 0x51
        __emit 0x8b
        __emit 0xcf
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0xf4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x01
        __emit 0xff
        __emit 0x52
        __emit 0x10
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x2b
        __emit 0xc1
        __emit 0x85
        __emit 0xc9
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1c
        __emit 0x3d
        __emit 0x80
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x76
        __emit 0x0b
        __emit 0x51
        __emit 0xe8
        __emit 0xad
        __emit 0xcb
        __emit 0x28
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xeb
        __emit 0x0a
        __emit 0x50
        __emit 0x51
        __emit 0xe8
        __emit 0xe1
        __emit 0x92
        __emit 0x23
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x57
        __emit 0xe8
        __emit 0x6c
        __emit 0x0e
        __emit 0xa5
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0x40
        __emit 0x45
        __emit 0xa3
        __emit 0xff
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc4
        __emit 0xeb
        __emit 0x12
        __emit 0x01
        __emit 0xe8
        __emit 0xdf
        __emit 0xa3
        __emit 0x24
        __emit 0x00
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xe4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x5f
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0xc4
        __emit 0xe8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc2
        __emit 0x08
        __emit 0x00
    }
}

// ?writeINI@LightningEmissionModuleTemplate@FXParticleSystem@@UBEXAAVFile@@I@Z
__declspec(naked) void LightningEmissionModuleTemplate::writeINI(File &file, unsigned int flags) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xb6
        __emit 0xc8
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0xec
        __emit 0xdc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x56
        __emit 0x57
        __emit 0x8b
        __emit 0xbc
        __emit 0x24
        __emit 0xf4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x8b
        __emit 0xf1
        __emit 0x57
        __emit 0x56
        __emit 0xe8
        __emit 0x52
        __emit 0xc8
        __emit 0xa2
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x0c
        __emit 0x6a
        __emit 0x01
        __emit 0x6a
        __emit 0x10
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x1c
        __emit 0xe8
        __emit 0xea
        __emit 0x24
        __emit 0xa3
        __emit 0xff
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x46
        __emit 0x10
        __emit 0x8d
        __emit 0x4e
        __emit 0x10
        __emit 0xda
        __emit 0xe9
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x24
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x51
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xfc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x68
        __emit 0x20
        __emit 0x3e
        __emit 0x11
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x20
        __emit 0x52
        __emit 0xe8
        __emit 0x93
        __emit 0xc4
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x1c
        __emit 0xd9
        __emit 0x01
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x24
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0x14
        __emit 0x3e
        __emit 0x11
        __emit 0x01
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x20
        __emit 0x51
        __emit 0xe8
        __emit 0x40
        __emit 0xc4
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x28
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x94
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0x0c
        __emit 0x1a
        __emit 0x0f
        __emit 0x01
        __emit 0x52
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x20
        __emit 0x50
        __emit 0xe8
        __emit 0x9e
        __emit 0x74
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x34
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x51
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xfc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x68
        __emit 0xec
        __emit 0x42
        __emit 0x11
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x20
        __emit 0x52
        __emit 0xe8
        __emit 0x5c
        __emit 0x74
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x40
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0xe4
        __emit 0x42
        __emit 0x11
        __emit 0x01
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x20
        __emit 0x51
        __emit 0xe8
        __emit 0x1a
        __emit 0x74
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x4c
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x94
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0xfc
        __emit 0x19
        __emit 0x0f
        __emit 0x01
        __emit 0x52
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x20
        __emit 0x50
        __emit 0xe8
        __emit 0xd8
        __emit 0x73
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x58
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x51
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xfc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x68
        __emit 0xd4
        __emit 0x42
        __emit 0x11
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x20
        __emit 0x52
        __emit 0xe8
        __emit 0x96
        __emit 0x73
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x64
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0xcc
        __emit 0x42
        __emit 0x11
        __emit 0x01
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x20
        __emit 0x51
        __emit 0xe8
        __emit 0x54
        __emit 0x73
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x70
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x94
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0xbc
        __emit 0x42
        __emit 0x11
        __emit 0x01
        __emit 0x52
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x20
        __emit 0x50
        __emit 0xe8
        __emit 0x12
        __emit 0x73
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x7c
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x51
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xfc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x68
        __emit 0xac
        __emit 0x42
        __emit 0x11
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x20
        __emit 0x52
        __emit 0xe8
        __emit 0xd0
        __emit 0x72
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x8e
        __emit 0x88
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0xa4
        __emit 0x42
        __emit 0x11
        __emit 0x01
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x20
        __emit 0x51
        __emit 0xe8
        __emit 0x8b
        __emit 0x72
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x08
        __emit 0x52
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x18
        __emit 0xe8
        __emit 0x1c
        __emit 0x09
        __emit 0xa2
        __emit 0xff
        __emit 0x8b
        __emit 0x08
        __emit 0x8b
        __emit 0x40
        __emit 0x04
        __emit 0x8b
        __emit 0x17
        __emit 0x2b
        __emit 0xc1
        __emit 0x50
        __emit 0x51
        __emit 0x8b
        __emit 0xcf
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0xf4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x01
        __emit 0xff
        __emit 0x52
        __emit 0x10
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x2b
        __emit 0xc1
        __emit 0x85
        __emit 0xc9
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1c
        __emit 0x3d
        __emit 0x80
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x76
        __emit 0x0b
        __emit 0x51
        __emit 0xe8
        __emit 0x6b
        __emit 0x5d
        __emit 0x28
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xeb
        __emit 0x0a
        __emit 0x50
        __emit 0x51
        __emit 0xe8
        __emit 0x9f
        __emit 0x24
        __emit 0x23
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x57
        __emit 0xe8
        __emit 0x2a
        __emit 0xa0
        __emit 0xa4
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0xfe
        __emit 0xd6
        __emit 0xa2
        __emit 0xff
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc4
        __emit 0xeb
        __emit 0x12
        __emit 0x01
        __emit 0xe8
        __emit 0x9d
        __emit 0x35
        __emit 0x24
        __emit 0x00
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xe4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x5f
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0xc4
        __emit 0xe8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc2
        __emit 0x08
        __emit 0x00
    }
}

// ?writeINI@LineEmissionVolumeModuleTemplate@FXParticleSystem@@UBEXAAVFile@@I@Z
__declspec(naked) void LineEmissionVolumeModuleTemplate::writeINI(File &file, unsigned int flags) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x46
        __emit 0xc7
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0xec
        __emit 0xdc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x56
        __emit 0x57
        __emit 0x8b
        __emit 0xbc
        __emit 0x24
        __emit 0xf4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x8b
        __emit 0xf1
        __emit 0x57
        __emit 0x56
        __emit 0xe8
        __emit 0x82
        __emit 0xea
        __emit 0xa2
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x0c
        __emit 0x6a
        __emit 0x01
        __emit 0x6a
        __emit 0x10
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x1c
        __emit 0xe8
        __emit 0x1a
        __emit 0x47
        __emit 0xa3
        __emit 0xff
        __emit 0x8a
        __emit 0x4e
        __emit 0x0c
        __emit 0x84
        __emit 0xc9
        __emit 0x8d
        __emit 0x46
        __emit 0x0c
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1b
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x68
        __emit 0x7c
        __emit 0x3a
        __emit 0x11
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x20
        __emit 0x52
        __emit 0xe8
        __emit 0xb9
        __emit 0x78
        __emit 0xa0
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x10
        __emit 0xd9
        __emit 0x01
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x24
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0x20
        __emit 0x3e
        __emit 0x11
        __emit 0x01
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x20
        __emit 0x51
        __emit 0xe8
        __emit 0x9f
        __emit 0xe6
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x1c
        __emit 0xd9
        __emit 0x01
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x24
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x94
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0x14
        __emit 0x3e
        __emit 0x11
        __emit 0x01
        __emit 0x52
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x20
        __emit 0x50
        __emit 0xe8
        __emit 0x4c
        __emit 0xe6
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x51
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x18
        __emit 0xe8
        __emit 0x7d
        __emit 0x2d
        __emit 0xa2
        __emit 0xff
        __emit 0x8b
        __emit 0x08
        __emit 0x8b
        __emit 0x40
        __emit 0x04
        __emit 0x8b
        __emit 0x17
        __emit 0x2b
        __emit 0xc1
        __emit 0x50
        __emit 0x51
        __emit 0x8b
        __emit 0xcf
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0xf4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x01
        __emit 0xff
        __emit 0x52
        __emit 0x10
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x2b
        __emit 0xc1
        __emit 0x85
        __emit 0xc9
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1c
        __emit 0x3d
        __emit 0x80
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x76
        __emit 0x0b
        __emit 0x51
        __emit 0xe8
        __emit 0xcc
        __emit 0x81
        __emit 0x28
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xeb
        __emit 0x0a
        __emit 0x50
        __emit 0x51
        __emit 0xe8
        __emit 0x00
        __emit 0x49
        __emit 0x23
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x57
        __emit 0xe8
        __emit 0x8b
        __emit 0xc4
        __emit 0xa4
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0x5f
        __emit 0xfb
        __emit 0xa2
        __emit 0xff
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc4
        __emit 0xeb
        __emit 0x12
        __emit 0x01
        __emit 0xe8
        __emit 0xfe
        __emit 0x59
        __emit 0x24
        __emit 0x00
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xe4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x5f
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0xc4
        __emit 0xe8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc2
        __emit 0x08
        __emit 0x00
    }
}

// ?writeINI@OrthoEmissionVelocityModuleTemplate@FXParticleSystem@@UBEXAAVFile@@I@Z
__declspec(naked) void OrthoEmissionVelocityModuleTemplate::writeINI(File &file, unsigned int flags) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x76
        __emit 0xc7
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0xec
        __emit 0xdc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x56
        __emit 0x57
        __emit 0x8b
        __emit 0xbc
        __emit 0x24
        __emit 0xf4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x8b
        __emit 0xf1
        __emit 0x57
        __emit 0x56
        __emit 0xe8
        __emit 0xef
        __emit 0xd7
        __emit 0xa2
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x0c
        __emit 0x6a
        __emit 0x01
        __emit 0x6a
        __emit 0x10
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x1c
        __emit 0xe8
        __emit 0xfa
        __emit 0x43
        __emit 0xa3
        __emit 0xff
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x46
        __emit 0x10
        __emit 0x8d
        __emit 0x4e
        __emit 0x0c
        __emit 0xda
        __emit 0xe9
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x51
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xfc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x68
        __emit 0x84
        __emit 0x92
        __emit 0x08
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x20
        __emit 0x52
        __emit 0xe8
        __emit 0x55
        __emit 0x94
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x18
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0x1c
        __emit 0x14
        __emit 0x0a
        __emit 0x01
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x20
        __emit 0x51
        __emit 0xe8
        __emit 0x13
        __emit 0x94
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x24
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x94
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0x00
        __emit 0xf4
        __emit 0x0a
        __emit 0x01
        __emit 0x52
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x20
        __emit 0x50
        __emit 0xe8
        __emit 0xd1
        __emit 0x93
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x51
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x18
        __emit 0xe8
        __emit 0x62
        __emit 0x2a
        __emit 0xa2
        __emit 0xff
        __emit 0x8b
        __emit 0x08
        __emit 0x8b
        __emit 0x40
        __emit 0x04
        __emit 0x8b
        __emit 0x17
        __emit 0x2b
        __emit 0xc1
        __emit 0x50
        __emit 0x51
        __emit 0x8b
        __emit 0xcf
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0xf4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x01
        __emit 0xff
        __emit 0x52
        __emit 0x10
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x2b
        __emit 0xc1
        __emit 0x85
        __emit 0xc9
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1c
        __emit 0x3d
        __emit 0x80
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x76
        __emit 0x0b
        __emit 0x51
        __emit 0xe8
        __emit 0xb1
        __emit 0x7e
        __emit 0x28
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xeb
        __emit 0x0a
        __emit 0x50
        __emit 0x51
        __emit 0xe8
        __emit 0xe5
        __emit 0x45
        __emit 0x23
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x57
        __emit 0xe8
        __emit 0x70
        __emit 0xc1
        __emit 0xa4
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0x44
        __emit 0xf8
        __emit 0xa2
        __emit 0xff
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc4
        __emit 0xeb
        __emit 0x12
        __emit 0x01
        __emit 0xe8
        __emit 0xe3
        __emit 0x56
        __emit 0x24
        __emit 0x00
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xe4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x5f
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0xc4
        __emit 0xe8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc2
        __emit 0x08
        __emit 0x00
    }
}

// ?writeINI@OutwardEmissionVelocityModuleTemplate@FXParticleSystem@@UBEXAAVFile@@I@Z
__declspec(naked) void OutwardEmissionVelocityModuleTemplate::writeINI(File &file, unsigned int flags) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xa6
        __emit 0xc7
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0xec
        __emit 0xdc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x56
        __emit 0x57
        __emit 0x8b
        __emit 0xbc
        __emit 0x24
        __emit 0xf4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x8b
        __emit 0xf1
        __emit 0x57
        __emit 0x56
        __emit 0xe8
        __emit 0xdf
        __emit 0xd4
        __emit 0xa2
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x0c
        __emit 0x6a
        __emit 0x01
        __emit 0x6a
        __emit 0x10
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x1c
        __emit 0xe8
        __emit 0xea
        __emit 0x40
        __emit 0xa3
        __emit 0xff
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x46
        __emit 0x10
        __emit 0x8d
        __emit 0x4e
        __emit 0x0c
        __emit 0xda
        __emit 0xe9
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x51
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xfc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x68
        __emit 0x4c
        __emit 0xd8
        __emit 0x09
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x20
        __emit 0x52
        __emit 0xe8
        __emit 0x45
        __emit 0x91
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x18
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0xd4
        __emit 0x3f
        __emit 0x11
        __emit 0x01
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x20
        __emit 0x51
        __emit 0xe8
        __emit 0x03
        __emit 0x91
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x08
        __emit 0x52
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x18
        __emit 0xe8
        __emit 0x94
        __emit 0x27
        __emit 0xa2
        __emit 0xff
        __emit 0x8b
        __emit 0x08
        __emit 0x8b
        __emit 0x40
        __emit 0x04
        __emit 0x8b
        __emit 0x17
        __emit 0x2b
        __emit 0xc1
        __emit 0x50
        __emit 0x51
        __emit 0x8b
        __emit 0xcf
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0xf4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x01
        __emit 0xff
        __emit 0x52
        __emit 0x10
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x2b
        __emit 0xc1
        __emit 0x85
        __emit 0xc9
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1c
        __emit 0x3d
        __emit 0x80
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x76
        __emit 0x0b
        __emit 0x51
        __emit 0xe8
        __emit 0xe3
        __emit 0x7b
        __emit 0x28
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xeb
        __emit 0x0a
        __emit 0x50
        __emit 0x51
        __emit 0xe8
        __emit 0x17
        __emit 0x43
        __emit 0x23
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x57
        __emit 0xe8
        __emit 0xa2
        __emit 0xbe
        __emit 0xa4
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0x76
        __emit 0xf5
        __emit 0xa2
        __emit 0xff
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc4
        __emit 0xeb
        __emit 0x12
        __emit 0x01
        __emit 0xe8
        __emit 0x15
        __emit 0x54
        __emit 0x24
        __emit 0x00
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xe4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x5f
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0xc4
        __emit 0xe8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc2
        __emit 0x08
        __emit 0x00
    }
}

// ?writeINI@ParticleSystemTemplate@FXParticleSystem@@QBEXAAVFile@@I@Z
__declspec(naked) void ParticleSystemTemplate::writeINI(File &file, unsigned int flags) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xb7
        __emit 0xa1
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0xec
        __emit 0x04
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x55
        __emit 0x56
        __emit 0x57
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x0f
        __emit 0x50
        __emit 0x8b
        __emit 0xf1
        __emit 0x68
        __emit 0x24
        __emit 0x76
        __emit 0x0e
        __emit 0x01
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x24
        __emit 0xe8
        __emit 0x35
        __emit 0xe8
        __emit 0xa6
        __emit 0xff
        __emit 0x6a
        __emit 0x20
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x18
        __emit 0x51
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0x24
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0x22
        __emit 0x29
        __emit 0xa7
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x0c
        __emit 0x8b
        __emit 0x8e
        __emit 0x98
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x85
        __emit 0xc9
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0x18
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x01
        __emit 0x74
        __emit 0x05
        __emit 0x83
        __emit 0xc1
        __emit 0x08
        __emit 0xeb
        __emit 0x05
        __emit 0xb9
        __emit 0x8b
        __emit 0x38
        __emit 0x07
        __emit 0x01
        __emit 0x51
        __emit 0x50
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x3c
        __emit 0x52
        __emit 0xe8
        __emit 0x66
        __emit 0x2e
        __emit 0xa6
        __emit 0xff
        __emit 0x8b
        __emit 0xac
        __emit 0x24
        __emit 0x2c
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0x00
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0x30
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x55
        __emit 0x50
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0x30
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x02
        __emit 0xe8
        __emit 0xeb
        __emit 0x3a
        __emit 0xa4
        __emit 0xff
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x4c
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x54
        __emit 0x83
        __emit 0xc4
        __emit 0x18
        __emit 0x2b
        __emit 0xc1
        __emit 0x85
        __emit 0xc9
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0x18
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x01
        __emit 0x74
        __emit 0x1c
        __emit 0x3d
        __emit 0x80
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x76
        __emit 0x0b
        __emit 0x51
        __emit 0xe8
        __emit 0x44
        __emit 0x53
        __emit 0x2b
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xeb
        __emit 0x0a
        __emit 0x50
        __emit 0x51
        __emit 0xe8
        __emit 0x78
        __emit 0x1a
        __emit 0x26
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x10
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x18
        __emit 0x2b
        __emit 0xc1
        __emit 0x85
        __emit 0xc9
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0x18
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1c
        __emit 0x3d
        __emit 0x80
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x76
        __emit 0x0b
        __emit 0x51
        __emit 0xe8
        __emit 0x12
        __emit 0x53
        __emit 0x2b
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xeb
        __emit 0x0a
        __emit 0x50
        __emit 0x51
        __emit 0xe8
        __emit 0x46
        __emit 0x1a
        __emit 0x26
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x1c
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x24
        __emit 0x2b
        __emit 0xc1
        __emit 0x85
        __emit 0xc9
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0x18
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0x74
        __emit 0x1c
        __emit 0x3d
        __emit 0x80
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x76
        __emit 0x0b
        __emit 0x51
        __emit 0xe8
        __emit 0xdd
        __emit 0x52
        __emit 0x2b
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xeb
        __emit 0x0a
        __emit 0x50
        __emit 0x51
        __emit 0xe8
        __emit 0x11
        __emit 0x1a
        __emit 0x26
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x94
        __emit 0x24
        __emit 0x24
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x52
        __emit 0x55
        __emit 0x68
        __emit 0x54
        __emit 0xf9
        __emit 0x10
        __emit 0x01
        __emit 0xe8
        __emit 0x3c
        __emit 0x3a
        __emit 0xa4
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x0c
        __emit 0x6a
        __emit 0x01
        __emit 0x6a
        __emit 0x10
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x48
        __emit 0xe8
        __emit 0xda
        __emit 0x16
        __emit 0xa6
        __emit 0xff
        __emit 0x8b
        __emit 0x46
        __emit 0x7c
        __emit 0x83
        __emit 0xf8
        __emit 0x01
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0x18
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x03
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x22
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0x24
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x04
        __emit 0x85
        __emit 0x08
        __emit 0x02
        __emit 0x11
        __emit 0x01
        __emit 0x50
        __emit 0x68
        __emit 0x40
        __emit 0x16
        __emit 0x08
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x4c
        __emit 0x52
        __emit 0xe8
        __emit 0xcc
        __emit 0x34
        __emit 0xa5
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8a
        __emit 0x4e
        __emit 0x04
        __emit 0x84
        __emit 0xc9
        __emit 0x8d
        __emit 0x46
        __emit 0x04
        __emit 0x74
        __emit 0x1b
        __emit 0x50
        __emit 0x8b
        __emit 0x84
        __emit 0x24
        __emit 0x28
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x68
        __emit 0x38
        __emit 0xfb
        __emit 0x10
        __emit 0x01
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x4c
        __emit 0x51
        __emit 0xe8
        __emit 0x4f
        __emit 0x48
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8b
        __emit 0x46
        __emit 0x08
        __emit 0x83
        __emit 0xf8
        __emit 0x01
        __emit 0x74
        __emit 0x22
        __emit 0x8d
        __emit 0x14
        __emit 0x85
        __emit 0x80
        __emit 0x01
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0x84
        __emit 0x24
        __emit 0x24
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x52
        __emit 0x68
        __emit 0x90
        __emit 0x27
        __emit 0x0f
        __emit 0x01
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x4c
        __emit 0x51
        __emit 0xe8
        __emit 0x7d
        __emit 0x34
        __emit 0xa5
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8b
        __emit 0x46
        __emit 0x0c
        __emit 0x83
        __emit 0xf8
        __emit 0x01
        __emit 0x74
        __emit 0x22
        __emit 0x8d
        __emit 0x14
        __emit 0x85
        __emit 0xb0
        __emit 0x01
        __emit 0x11
        __emit 0x01
        __emit 0x8b
        __emit 0x84
        __emit 0x24
        __emit 0x24
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x52
        __emit 0x68
        __emit 0xdc
        __emit 0x0d
        __emit 0x08
        __emit 0x01
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x4c
        __emit 0x51
        __emit 0xe8
        __emit 0x53
        __emit 0x34
        __emit 0xa5
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8b
        __emit 0x84
        __emit 0x24
        __emit 0x24
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x56
        __emit 0x10
        __emit 0x52
        __emit 0x68
        __emit 0x28
        __emit 0xfb
        __emit 0x10
        __emit 0x01
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x4c
        __emit 0x51
        __emit 0xe8
        __emit 0x25
        __emit 0x89
        __emit 0xa6
        __emit 0xff
        __emit 0x8b
        __emit 0x46
        __emit 0x68
        __emit 0x8d
        __emit 0x4e
        __emit 0x68
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x85
        __emit 0xc0
        __emit 0x74
        __emit 0x3d
        __emit 0x66
        __emit 0x83
        __emit 0x78
        __emit 0x04
        __emit 0x00
        __emit 0x74
        __emit 0x36
        __emit 0x8b
        __emit 0x94
        __emit 0x24
        __emit 0x24
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0x18
        __emit 0xfb
        __emit 0x10
        __emit 0x01
        __emit 0x52
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x4c
        __emit 0x50
        __emit 0xe8
        __emit 0xf9
        __emit 0x88
        __emit 0xa6
        __emit 0xff
        __emit 0x8b
        __emit 0x94
        __emit 0x24
        __emit 0x34
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x4e
        __emit 0x6c
        __emit 0x51
        __emit 0x68
        __emit 0x04
        __emit 0xfb
        __emit 0x10
        __emit 0x01
        __emit 0x52
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x5c
        __emit 0x50
        __emit 0xe8
        __emit 0xcf
        __emit 0xb5
        __emit 0xa6
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x20
        __emit 0x8b
        __emit 0x46
        __emit 0x78
        __emit 0x85
        __emit 0xc0
        __emit 0x8d
        __emit 0x4e
        __emit 0x78
        __emit 0x74
        __emit 0x22
        __emit 0x66
        __emit 0x83
        __emit 0x78
        __emit 0x04
        __emit 0x00
        __emit 0x74
        __emit 0x1b
        __emit 0x51
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0x28
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x68
        __emit 0xe4
        __emit 0xfa
        __emit 0x10
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x4c
        __emit 0x52
        __emit 0xe8
        __emit 0xb2
        __emit 0x88
        __emit 0xa6
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x14
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x84
        __emit 0x24
        __emit 0x24
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0xec
        __emit 0x26
        __emit 0x0f
        __emit 0x01
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x4c
        __emit 0x51
        __emit 0xe8
        __emit 0x01
        __emit 0x66
        __emit 0xa6
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8b
        __emit 0x4e
        __emit 0x20
        __emit 0x85
        __emit 0xc9
        __emit 0x8d
        __emit 0x46
        __emit 0x20
        __emit 0x74
        __emit 0x1b
        __emit 0x8b
        __emit 0x94
        __emit 0x24
        __emit 0x24
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x68
        __emit 0xd0
        __emit 0xfa
        __emit 0x10
        __emit 0x01
        __emit 0x52
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x4c
        __emit 0x50
        __emit 0xe8
        __emit 0x00
        __emit 0x4d
        __emit 0xa5
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8b
        __emit 0x4e
        __emit 0x24
        __emit 0x85
        __emit 0xc9
        __emit 0x8d
        __emit 0x46
        __emit 0x24
        __emit 0x74
        __emit 0x1b
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0x24
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x68
        __emit 0xc4
        __emit 0xfa
        __emit 0x10
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x4c
        __emit 0x52
        __emit 0xe8
        __emit 0xdb
        __emit 0x4c
        __emit 0xa5
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x28
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x84
        __emit 0x24
        __emit 0x24
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0x08
        __emit 0xe3
        __emit 0x0e
        __emit 0x01
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x4c
        __emit 0x51
        __emit 0xe8
        __emit 0x75
        __emit 0x65
        __emit 0xa6
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x34
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x94
        __emit 0x24
        __emit 0x24
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0xb4
        __emit 0xfa
        __emit 0x10
        __emit 0x01
        __emit 0x52
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x4c
        __emit 0x50
        __emit 0xe8
        __emit 0x33
        __emit 0x65
        __emit 0xa6
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x44
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x51
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0x28
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x68
        __emit 0xa4
        __emit 0xfa
        __emit 0x10
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x4c
        __emit 0x52
        __emit 0xe8
        __emit 0xf1
        __emit 0x64
        __emit 0xa6
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x50
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x84
        __emit 0x24
        __emit 0x24
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0x88
        __emit 0x31
        __emit 0x0f
        __emit 0x01
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x4c
        __emit 0x51
        __emit 0xe8
        __emit 0xaf
        __emit 0x64
        __emit 0xa6
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x5c
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x94
        __emit 0x24
        __emit 0x24
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0xe8
        __emit 0x2d
        __emit 0x08
        __emit 0x01
        __emit 0x52
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x4c
        __emit 0x50
        __emit 0xe8
        __emit 0x6d
        __emit 0x64
        __emit 0xa6
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8a
        __emit 0x8e
        __emit 0x80
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x84
        __emit 0xc9
        __emit 0x8d
        __emit 0x86
        __emit 0x80
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1b
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0x24
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x68
        __emit 0x90
        __emit 0xfa
        __emit 0x10
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x4c
        __emit 0x52
        __emit 0xe8
        __emit 0x69
        __emit 0x45
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8a
        __emit 0x8e
        __emit 0x81
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x84
        __emit 0xc9
        __emit 0x8d
        __emit 0x86
        __emit 0x81
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1b
        __emit 0x50
        __emit 0x8b
        __emit 0x84
        __emit 0x24
        __emit 0x28
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x68
        __emit 0x74
        __emit 0xfa
        __emit 0x10
        __emit 0x01
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x4c
        __emit 0x51
        __emit 0xe8
        __emit 0x3e
        __emit 0x45
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8a
        __emit 0x8e
        __emit 0x82
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x84
        __emit 0xc9
        __emit 0x8d
        __emit 0x86
        __emit 0x82
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1b
        __emit 0x8b
        __emit 0x94
        __emit 0x24
        __emit 0x24
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x68
        __emit 0x54
        __emit 0xfa
        __emit 0x10
        __emit 0x01
        __emit 0x52
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x4c
        __emit 0x50
        __emit 0xe8
        __emit 0x13
        __emit 0x45
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8a
        __emit 0x8e
        __emit 0x83
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x84
        __emit 0xc9
        __emit 0x8d
        __emit 0x86
        __emit 0x83
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1b
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0x24
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x68
        __emit 0x40
        __emit 0xfa
        __emit 0x10
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x4c
        __emit 0x52
        __emit 0xe8
        __emit 0xe8
        __emit 0x44
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x28
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x44
        __emit 0xe8
        __emit 0x52
        __emit 0xfa
        __emit 0xa4
        __emit 0xff
        __emit 0x8b
        __emit 0x08
        __emit 0x8b
        __emit 0x40
        __emit 0x04
        __emit 0x8b
        __emit 0x55
        __emit 0x00
        __emit 0x2b
        __emit 0xc1
        __emit 0x50
        __emit 0x51
        __emit 0x8b
        __emit 0xcd
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0x20
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x04
        __emit 0xff
        __emit 0x52
        __emit 0x10
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x28
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x30
        __emit 0x2b
        __emit 0xc1
        __emit 0x85
        __emit 0xc9
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0x18
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x03
        __emit 0x74
        __emit 0x1c
        __emit 0x3d
        __emit 0x80
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x76
        __emit 0x0b
        __emit 0x51
        __emit 0xe8
        __emit 0xa0
        __emit 0x4e
        __emit 0x2b
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xeb
        __emit 0x0a
        __emit 0x50
        __emit 0x51
        __emit 0xe8
        __emit 0xd4
        __emit 0x15
        __emit 0x26
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0x24
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x55
        __emit 0xe8
        __emit 0x5f
        __emit 0x91
        __emit 0xa7
        __emit 0xff
        __emit 0x8b
        __emit 0x8e
        __emit 0xa0
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0xbc
        __emit 0x24
        __emit 0x2c
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x85
        __emit 0xc9
        __emit 0x74
        __emit 0x07
        __emit 0x8b
        __emit 0x11
        __emit 0x57
        __emit 0x55
        __emit 0xff
        __emit 0x52
        __emit 0x0c
        __emit 0x8b
        __emit 0x8e
        __emit 0xa4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x85
        __emit 0xc9
        __emit 0x74
        __emit 0x07
        __emit 0x8b
        __emit 0x01
        __emit 0x57
        __emit 0x55
        __emit 0xff
        __emit 0x50
        __emit 0x0c
        __emit 0x8b
        __emit 0x8e
        __emit 0xa8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x85
        __emit 0xc9
        __emit 0x74
        __emit 0x07
        __emit 0x8b
        __emit 0x11
        __emit 0x57
        __emit 0x55
        __emit 0xff
        __emit 0x52
        __emit 0x0c
        __emit 0x57
        __emit 0x55
        __emit 0x8d
        __emit 0x8e
        __emit 0xac
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0xa5
        __emit 0x30
        __emit 0xa5
        __emit 0xff
        __emit 0x8d
        __emit 0x84
        __emit 0x24
        __emit 0x24
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x55
        __emit 0xe8
        __emit 0x07
        __emit 0x91
        __emit 0xa7
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0xb0
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0x18
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0xdb
        __emit 0xc7
        __emit 0xa5
        __emit 0xff
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0xb0
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xb0
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc4
        __emit 0xeb
        __emit 0x12
        __emit 0x01
        __emit 0xe8
        __emit 0x7a
        __emit 0x26
        __emit 0x27
        __emit 0x00
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0x10
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x5f
        __emit 0x5e
        __emit 0x5d
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0xc4
        __emit 0x10
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0xc2
        __emit 0x08
        __emit 0x00
    }
}

// ?writeINI@PointEmissionVolumeModuleTemplate@FXParticleSystem@@UBEXAAVFile@@I@Z
__declspec(naked) void PointEmissionVolumeModuleTemplate::writeINI(File &file, unsigned int flags) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xd6
        __emit 0xc7
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0xec
        __emit 0xdc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x56
        __emit 0x8b
        __emit 0xb4
        __emit 0x24
        __emit 0xf0
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x57
        __emit 0x8d
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x8b
        __emit 0xf9
        __emit 0x56
        __emit 0x57
        __emit 0xe8
        __emit 0x22
        __emit 0xe1
        __emit 0xa2
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x0c
        __emit 0x6a
        __emit 0x01
        __emit 0x6a
        __emit 0x10
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x1c
        __emit 0xe8
        __emit 0xba
        __emit 0x3d
        __emit 0xa3
        __emit 0xff
        __emit 0x8a
        __emit 0x4f
        __emit 0x0c
        __emit 0x84
        __emit 0xc9
        __emit 0x8d
        __emit 0x47
        __emit 0x0c
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1b
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x68
        __emit 0x7c
        __emit 0x3a
        __emit 0x11
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x20
        __emit 0x52
        __emit 0xe8
        __emit 0x59
        __emit 0x6f
        __emit 0xa0
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x18
        __emit 0xe8
        __emit 0xc3
        __emit 0x24
        __emit 0xa2
        __emit 0xff
        __emit 0x8b
        __emit 0x08
        __emit 0x8b
        __emit 0x40
        __emit 0x04
        __emit 0x8b
        __emit 0x16
        __emit 0x2b
        __emit 0xc1
        __emit 0x50
        __emit 0x51
        __emit 0x8b
        __emit 0xce
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0xf4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x01
        __emit 0xff
        __emit 0x52
        __emit 0x10
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x2b
        __emit 0xc1
        __emit 0x85
        __emit 0xc9
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1c
        __emit 0x3d
        __emit 0x80
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x76
        __emit 0x0b
        __emit 0x51
        __emit 0xe8
        __emit 0x12
        __emit 0x79
        __emit 0x28
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xeb
        __emit 0x0a
        __emit 0x50
        __emit 0x51
        __emit 0xe8
        __emit 0x46
        __emit 0x40
        __emit 0x23
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0xe8
        __emit 0xd1
        __emit 0xbb
        __emit 0xa4
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0xa5
        __emit 0xf2
        __emit 0xa2
        __emit 0xff
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc4
        __emit 0xeb
        __emit 0x12
        __emit 0x01
        __emit 0xe8
        __emit 0x44
        __emit 0x51
        __emit 0x24
        __emit 0x00
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xe4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x5f
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0xc4
        __emit 0xe8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc2
        __emit 0x08
        __emit 0x00
    }
}

// ?writeINI@QuadDrawModuleTemplate@FXParticleSystem@@UBEXAAVFile@@I@Z
void QuadDrawModuleTemplate::writeINI(File &file, unsigned int flags) const
{
    writeDrawTemplateBase(this, file, &flags);
    writeDrawInfo(file, &flags);
}

// ?writeINI@RenderObjectDrawModuleTemplate@FXParticleSystem@@UBEXAAVFile@@I@Z
__declspec(naked) void RenderObjectDrawModuleTemplate::writeINI(File &file, unsigned int flags) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0xe6
        __emit 0xc5
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0xec
        __emit 0xdc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x56
        __emit 0x57
        __emit 0x8b
        __emit 0xbc
        __emit 0x24
        __emit 0xf4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x8b
        __emit 0xf1
        __emit 0x57
        __emit 0x56
        __emit 0xe8
        __emit 0x44
        __emit 0xe6
        __emit 0xa4
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x0c
        __emit 0x6a
        __emit 0x01
        __emit 0x6a
        __emit 0x10
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x1c
        __emit 0xe8
        __emit 0x4a
        __emit 0x68
        __emit 0xa3
        __emit 0xff
        __emit 0x8a
        __emit 0x4e
        __emit 0x14
        __emit 0x84
        __emit 0xc9
        __emit 0x8d
        __emit 0x46
        __emit 0x14
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1b
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x68
        __emit 0x94
        __emit 0x38
        __emit 0x11
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x20
        __emit 0x52
        __emit 0xe8
        __emit 0xe9
        __emit 0x99
        __emit 0xa0
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8b
        __emit 0x46
        __emit 0x18
        __emit 0x85
        __emit 0xc0
        __emit 0x8d
        __emit 0x4e
        __emit 0x18
        __emit 0x74
        __emit 0x22
        __emit 0x66
        __emit 0x83
        __emit 0x78
        __emit 0x04
        __emit 0x00
        __emit 0x74
        __emit 0x1b
        __emit 0x8b
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0x84
        __emit 0x38
        __emit 0x11
        __emit 0x01
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x20
        __emit 0x51
        __emit 0xe8
        __emit 0x05
        __emit 0xdb
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8b
        __emit 0x4e
        __emit 0x1c
        __emit 0x85
        __emit 0xc9
        __emit 0x8d
        __emit 0x46
        __emit 0x1c
        __emit 0x74
        __emit 0x1b
        __emit 0x8b
        __emit 0x94
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x68
        __emit 0x74
        __emit 0x38
        __emit 0x11
        __emit 0x01
        __emit 0x52
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x20
        __emit 0x50
        __emit 0xe8
        __emit 0x8d
        __emit 0x1d
        __emit 0xa5
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x20
        __emit 0xd9
        __emit 0x01
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x51
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xfc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x68
        __emit 0x68
        __emit 0x38
        __emit 0x11
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x20
        __emit 0x52
        __emit 0xe8
        __emit 0x48
        __emit 0x81
        __emit 0xa2
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8b
        __emit 0x46
        __emit 0x24
        __emit 0x83
        __emit 0xf8
        __emit 0x08
        __emit 0x74
        __emit 0x22
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x04
        __emit 0x85
        __emit 0x80
        __emit 0x01
        __emit 0x11
        __emit 0x01
        __emit 0x50
        __emit 0x68
        __emit 0x5c
        __emit 0x38
        __emit 0x11
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x20
        __emit 0x52
        __emit 0xe8
        __emit 0x97
        __emit 0x85
        __emit 0xa2
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8b
        __emit 0x46
        __emit 0x28
        __emit 0x85
        __emit 0xc0
        __emit 0x8d
        __emit 0x4e
        __emit 0x28
        __emit 0x74
        __emit 0x22
        __emit 0x66
        __emit 0x83
        __emit 0x78
        __emit 0x04
        __emit 0x00
        __emit 0x74
        __emit 0x1b
        __emit 0x8b
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0x4c
        __emit 0x38
        __emit 0x11
        __emit 0x01
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x20
        __emit 0x51
        __emit 0xe8
        __emit 0x5b
        __emit 0xda
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8b
        __emit 0x4e
        __emit 0x2c
        __emit 0x85
        __emit 0xc9
        __emit 0x8d
        __emit 0x46
        __emit 0x2c
        __emit 0x74
        __emit 0x1b
        __emit 0x8b
        __emit 0x94
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x68
        __emit 0x3c
        __emit 0x38
        __emit 0x11
        __emit 0x01
        __emit 0x52
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x20
        __emit 0x50
        __emit 0xe8
        __emit 0xe3
        __emit 0x1c
        __emit 0xa5
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x30
        __emit 0xd9
        __emit 0x01
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x51
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xfc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x68
        __emit 0x30
        __emit 0x38
        __emit 0x11
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x20
        __emit 0x52
        __emit 0xe8
        __emit 0x9e
        __emit 0x80
        __emit 0xa2
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8b
        __emit 0x46
        __emit 0x34
        __emit 0x83
        __emit 0xf8
        __emit 0x08
        __emit 0x74
        __emit 0x22
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x04
        __emit 0x85
        __emit 0x80
        __emit 0x01
        __emit 0x11
        __emit 0x01
        __emit 0x50
        __emit 0x68
        __emit 0x24
        __emit 0x38
        __emit 0x11
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x20
        __emit 0x52
        __emit 0xe8
        __emit 0xed
        __emit 0x84
        __emit 0xa2
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8b
        __emit 0x46
        __emit 0x38
        __emit 0x85
        __emit 0xc0
        __emit 0x8d
        __emit 0x4e
        __emit 0x38
        __emit 0x74
        __emit 0x22
        __emit 0x66
        __emit 0x83
        __emit 0x78
        __emit 0x04
        __emit 0x00
        __emit 0x74
        __emit 0x1b
        __emit 0x8b
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0x14
        __emit 0x38
        __emit 0x11
        __emit 0x01
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x20
        __emit 0x51
        __emit 0xe8
        __emit 0xb1
        __emit 0xd9
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8b
        __emit 0x4e
        __emit 0x3c
        __emit 0x85
        __emit 0xc9
        __emit 0x8d
        __emit 0x46
        __emit 0x3c
        __emit 0x74
        __emit 0x1b
        __emit 0x8b
        __emit 0x94
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x68
        __emit 0x04
        __emit 0x38
        __emit 0x11
        __emit 0x01
        __emit 0x52
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x20
        __emit 0x50
        __emit 0xe8
        __emit 0x39
        __emit 0x1c
        __emit 0xa5
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x40
        __emit 0xd9
        __emit 0x01
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x51
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xfc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x68
        __emit 0xf8
        __emit 0x37
        __emit 0x11
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x20
        __emit 0x52
        __emit 0xe8
        __emit 0xf4
        __emit 0x7f
        __emit 0xa2
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8b
        __emit 0x46
        __emit 0x44
        __emit 0x83
        __emit 0xf8
        __emit 0x08
        __emit 0x74
        __emit 0x22
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x04
        __emit 0x85
        __emit 0x80
        __emit 0x01
        __emit 0x11
        __emit 0x01
        __emit 0x50
        __emit 0x68
        __emit 0xec
        __emit 0x37
        __emit 0x11
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x20
        __emit 0x52
        __emit 0xe8
        __emit 0x43
        __emit 0x84
        __emit 0xa2
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8a
        __emit 0x4e
        __emit 0x0c
        __emit 0x84
        __emit 0xc9
        __emit 0x8d
        __emit 0x46
        __emit 0x0c
        __emit 0x74
        __emit 0x1b
        __emit 0x50
        __emit 0x8b
        __emit 0x84
        __emit 0x24
        __emit 0xfc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x68
        __emit 0xd0
        __emit 0x37
        __emit 0x11
        __emit 0x01
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x20
        __emit 0x51
        __emit 0xe8
        __emit 0xc6
        __emit 0x97
        __emit 0xa0
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x10
        __emit 0xd9
        __emit 0x01
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x94
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0x38
        __emit 0x69
        __emit 0x0a
        __emit 0x01
        __emit 0x52
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x20
        __emit 0x50
        __emit 0xe8
        __emit 0x76
        __emit 0x7f
        __emit 0xa2
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x51
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x18
        __emit 0xe8
        __emit 0x01
        __emit 0x4d
        __emit 0xa2
        __emit 0xff
        __emit 0x8b
        __emit 0x08
        __emit 0x8b
        __emit 0x40
        __emit 0x04
        __emit 0x8b
        __emit 0x17
        __emit 0x2b
        __emit 0xc1
        __emit 0x50
        __emit 0x51
        __emit 0x8b
        __emit 0xcf
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0xf4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x01
        __emit 0xff
        __emit 0x52
        __emit 0x10
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x2b
        __emit 0xc1
        __emit 0x85
        __emit 0xc9
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1c
        __emit 0x3d
        __emit 0x80
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x76
        __emit 0x0b
        __emit 0x51
        __emit 0xe8
        __emit 0x50
        __emit 0xa1
        __emit 0x28
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xeb
        __emit 0x0a
        __emit 0x50
        __emit 0x51
        __emit 0xe8
        __emit 0x84
        __emit 0x68
        __emit 0x23
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x57
        __emit 0xe8
        __emit 0x0f
        __emit 0xe4
        __emit 0xa4
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0xe3
        __emit 0x1a
        __emit 0xa3
        __emit 0xff
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc4
        __emit 0xeb
        __emit 0x12
        __emit 0x01
        __emit 0xe8
        __emit 0x82
        __emit 0x79
        __emit 0x24
        __emit 0x00
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xe4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x5f
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0xc4
        __emit 0xe8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc2
        __emit 0x08
        __emit 0x00
    }
}

// ?writeINI@RenderObjectUpdateModuleTemplate@FXParticleSystem@@UBEXAAVFile@@I@Z
__declspec(naked) void RenderObjectUpdateModuleTemplate::writeINI(File &file, unsigned int flags) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x96
        __emit 0xcd
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0xec
        __emit 0xdc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x56
        __emit 0x57
        __emit 0x8b
        __emit 0xbc
        __emit 0x24
        __emit 0xf4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x8b
        __emit 0xf1
        __emit 0x57
        __emit 0x56
        __emit 0xe8
        __emit 0xcd
        __emit 0x6d
        __emit 0xa4
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x0c
        __emit 0x6a
        __emit 0x01
        __emit 0x6a
        __emit 0x10
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x1c
        __emit 0xe8
        __emit 0x8a
        __emit 0xd4
        __emit 0xa2
        __emit 0xff
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x46
        __emit 0x10
        __emit 0x8d
        __emit 0x4e
        __emit 0x0c
        __emit 0xda
        __emit 0xe9
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x51
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xfc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x68
        __emit 0x90
        __emit 0x4a
        __emit 0x11
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x20
        __emit 0x52
        __emit 0xe8
        __emit 0xe5
        __emit 0x24
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x18
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0x80
        __emit 0x4a
        __emit 0x11
        __emit 0x01
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x20
        __emit 0x51
        __emit 0xe8
        __emit 0xa3
        __emit 0x24
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x24
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x94
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0x70
        __emit 0x4a
        __emit 0x11
        __emit 0x01
        __emit 0x52
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x20
        __emit 0x50
        __emit 0xe8
        __emit 0x61
        __emit 0x24
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x30
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x51
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xfc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x68
        __emit 0x64
        __emit 0x4a
        __emit 0x11
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x20
        __emit 0x52
        __emit 0xe8
        __emit 0x1f
        __emit 0x24
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x3c
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0x58
        __emit 0x4a
        __emit 0x11
        __emit 0x01
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x20
        __emit 0x51
        __emit 0xe8
        __emit 0xdd
        __emit 0x23
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x48
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x94
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0x4c
        __emit 0x4a
        __emit 0x11
        __emit 0x01
        __emit 0x52
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x20
        __emit 0x50
        __emit 0xe8
        __emit 0x9b
        __emit 0x23
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x54
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x51
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xfc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x68
        __emit 0x3c
        __emit 0x4a
        __emit 0x11
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x20
        __emit 0x52
        __emit 0xe8
        __emit 0x59
        __emit 0x23
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x60
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0x2c
        __emit 0x4a
        __emit 0x11
        __emit 0x01
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x20
        __emit 0x51
        __emit 0xe8
        __emit 0x17
        __emit 0x23
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x6c
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x94
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0x1c
        __emit 0x4a
        __emit 0x11
        __emit 0x01
        __emit 0x52
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x20
        __emit 0x50
        __emit 0xe8
        __emit 0xd5
        __emit 0x22
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x78
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x51
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xfc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x68
        __emit 0x30
        __emit 0x49
        __emit 0x11
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x20
        __emit 0x52
        __emit 0xe8
        __emit 0x93
        __emit 0x22
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x8e
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0x20
        __emit 0x49
        __emit 0x11
        __emit 0x01
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x20
        __emit 0x51
        __emit 0xe8
        __emit 0x4e
        __emit 0x22
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x8e
        __emit 0x90
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x94
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0x0c
        __emit 0x49
        __emit 0x11
        __emit 0x01
        __emit 0x52
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x20
        __emit 0x50
        __emit 0xe8
        __emit 0x09
        __emit 0x22
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8b
        __emit 0xb6
        __emit 0x9c
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xfe
        __emit 0x01
        __emit 0x74
        __emit 0x22
        __emit 0x8b
        __emit 0x94
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x0c
        __emit 0xb5
        __emit 0x58
        __emit 0x02
        __emit 0x11
        __emit 0x01
        __emit 0x51
        __emit 0x68
        __emit 0x00
        __emit 0x49
        __emit 0x11
        __emit 0x01
        __emit 0x52
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x20
        __emit 0x50
        __emit 0xe8
        __emit 0x5b
        __emit 0xef
        __emit 0xa1
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x51
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x18
        __emit 0xe8
        __emit 0x6d
        __emit 0xb8
        __emit 0xa1
        __emit 0xff
        __emit 0x8b
        __emit 0x08
        __emit 0x8b
        __emit 0x40
        __emit 0x04
        __emit 0x8b
        __emit 0x17
        __emit 0x2b
        __emit 0xc1
        __emit 0x50
        __emit 0x51
        __emit 0x8b
        __emit 0xcf
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0xf4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x01
        __emit 0xff
        __emit 0x52
        __emit 0x10
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x2b
        __emit 0xc1
        __emit 0x85
        __emit 0xc9
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1c
        __emit 0x3d
        __emit 0x80
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x76
        __emit 0x0b
        __emit 0x51
        __emit 0xe8
        __emit 0xbc
        __emit 0x0c
        __emit 0x28
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xeb
        __emit 0x0a
        __emit 0x50
        __emit 0x51
        __emit 0xe8
        __emit 0xf0
        __emit 0xd3
        __emit 0x22
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x57
        __emit 0xe8
        __emit 0x7b
        __emit 0x4f
        __emit 0xa4
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0x4f
        __emit 0x86
        __emit 0xa2
        __emit 0xff
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc4
        __emit 0xeb
        __emit 0x12
        __emit 0x01
        __emit 0xe8
        __emit 0xee
        __emit 0xe4
        __emit 0x23
        __emit 0x00
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xe4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x5f
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0xc4
        __emit 0xe8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc2
        __emit 0x08
        __emit 0x00
    }
}

// ?writeINI@SphereEmissionVolumeModuleTemplate@FXParticleSystem@@UBEXAAVFile@@I@Z
__declspec(naked) void SphereEmissionVolumeModuleTemplate::writeINI(File &file, unsigned int flags) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x36
        __emit 0xc8
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0xec
        __emit 0xdc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x56
        __emit 0x57
        __emit 0x8b
        __emit 0xbc
        __emit 0x24
        __emit 0xf4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x8b
        __emit 0xf1
        __emit 0x57
        __emit 0x56
        __emit 0xe8
        __emit 0x22
        __emit 0xdb
        __emit 0xa2
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x0c
        __emit 0x6a
        __emit 0x01
        __emit 0x6a
        __emit 0x10
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x1c
        __emit 0xe8
        __emit 0xba
        __emit 0x37
        __emit 0xa3
        __emit 0xff
        __emit 0x8a
        __emit 0x4e
        __emit 0x0c
        __emit 0x84
        __emit 0xc9
        __emit 0x8d
        __emit 0x46
        __emit 0x0c
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1b
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x68
        __emit 0x7c
        __emit 0x3a
        __emit 0x11
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x20
        __emit 0x52
        __emit 0xe8
        __emit 0x59
        __emit 0x69
        __emit 0xa0
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x8d
        __emit 0x4e
        __emit 0x10
        __emit 0xd9
        __emit 0x01
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x8b
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x68
        __emit 0x10
        __emit 0xee
        __emit 0x08
        __emit 0x01
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x20
        __emit 0x51
        __emit 0xe8
        __emit 0x09
        __emit 0x51
        __emit 0xa2
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x08
        __emit 0x52
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x18
        __emit 0xe8
        __emit 0x94
        __emit 0x1e
        __emit 0xa2
        __emit 0xff
        __emit 0x8b
        __emit 0x08
        __emit 0x8b
        __emit 0x40
        __emit 0x04
        __emit 0x8b
        __emit 0x17
        __emit 0x2b
        __emit 0xc1
        __emit 0x50
        __emit 0x51
        __emit 0x8b
        __emit 0xcf
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0xf4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x01
        __emit 0xff
        __emit 0x52
        __emit 0x10
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x2b
        __emit 0xc1
        __emit 0x85
        __emit 0xc9
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1c
        __emit 0x3d
        __emit 0x80
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x76
        __emit 0x0b
        __emit 0x51
        __emit 0xe8
        __emit 0xe3
        __emit 0x72
        __emit 0x28
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xeb
        __emit 0x0a
        __emit 0x50
        __emit 0x51
        __emit 0xe8
        __emit 0x17
        __emit 0x3a
        __emit 0x23
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x57
        __emit 0xe8
        __emit 0xa2
        __emit 0xb5
        __emit 0xa4
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0x76
        __emit 0xec
        __emit 0xa2
        __emit 0xff
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc4
        __emit 0xeb
        __emit 0x12
        __emit 0x01
        __emit 0xe8
        __emit 0x15
        __emit 0x4b
        __emit 0x24
        __emit 0x00
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xe4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x5f
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0xc4
        __emit 0xe8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc2
        __emit 0x08
        __emit 0x00
    }
}

// ?writeINI@SphericalEmissionVelocityModuleTemplate@FXParticleSystem@@UBEXAAVFile@@I@Z
__declspec(naked) void SphericalEmissionVelocityModuleTemplate::writeINI(File &file, unsigned int flags) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x06
        __emit 0xc8
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0xec
        __emit 0xdc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x56
        __emit 0x8b
        __emit 0xb4
        __emit 0x24
        __emit 0xf0
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x57
        __emit 0x8d
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x8b
        __emit 0xf9
        __emit 0x56
        __emit 0x57
        __emit 0xe8
        __emit 0x7f
        __emit 0xcf
        __emit 0xa2
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x0c
        __emit 0x6a
        __emit 0x01
        __emit 0x6a
        __emit 0x10
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x1c
        __emit 0xe8
        __emit 0x8a
        __emit 0x3b
        __emit 0xa3
        __emit 0xff
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x47
        __emit 0x10
        __emit 0x8d
        __emit 0x4f
        __emit 0x0c
        __emit 0xda
        __emit 0xe9
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x12
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7b
        __emit 0x1b
        __emit 0x51
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xfc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x68
        __emit 0x4c
        __emit 0xd8
        __emit 0x09
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x20
        __emit 0x52
        __emit 0xe8
        __emit 0xe5
        __emit 0x8b
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x18
        __emit 0xe8
        __emit 0x76
        __emit 0x22
        __emit 0xa2
        __emit 0xff
        __emit 0x8b
        __emit 0x08
        __emit 0x8b
        __emit 0x40
        __emit 0x04
        __emit 0x8b
        __emit 0x16
        __emit 0x2b
        __emit 0xc1
        __emit 0x50
        __emit 0x51
        __emit 0x8b
        __emit 0xce
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0xf4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x01
        __emit 0xff
        __emit 0x52
        __emit 0x10
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x2b
        __emit 0xc1
        __emit 0x85
        __emit 0xc9
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1c
        __emit 0x3d
        __emit 0x80
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x76
        __emit 0x0b
        __emit 0x51
        __emit 0xe8
        __emit 0xc5
        __emit 0x76
        __emit 0x28
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xeb
        __emit 0x0a
        __emit 0x50
        __emit 0x51
        __emit 0xe8
        __emit 0xf9
        __emit 0x3d
        __emit 0x23
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x56
        __emit 0xe8
        __emit 0x84
        __emit 0xb9
        __emit 0xa4
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0x58
        __emit 0xf0
        __emit 0xa2
        __emit 0xff
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc4
        __emit 0xeb
        __emit 0x12
        __emit 0x01
        __emit 0xe8
        __emit 0xf7
        __emit 0x4e
        __emit 0x24
        __emit 0x00
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xe4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x5f
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0xc4
        __emit 0xe8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc2
        __emit 0x08
        __emit 0x00
    }
}

// ?writeINI@StreakDrawModuleTemplate@FXParticleSystem@@UBEXAAVFile@@I@Z
void StreakDrawModuleTemplate::writeINI(File &file, unsigned int flags) const
{
    writeDrawTemplateBase(this, file, &flags);
    writeDrawInfo(file, &flags);
}

// ?writeINI@TerrainCollisionModuleTemplate@FXParticleSystem@@UBEXAAVFile@@I@Z
__declspec(naked) void TerrainCollisionModuleTemplate::writeINI(File &file, unsigned int flags) const
{
    __asm {
        __emit 0x6a
        __emit 0xff
        __emit 0x68
        __emit 0x66
        __emit 0xca
        __emit 0x03
        __emit 0x01
        __emit 0x64
        __emit 0xa1
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x64
        __emit 0x89
        __emit 0x25
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0xec
        __emit 0xdc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x56
        __emit 0x57
        __emit 0x8b
        __emit 0xbc
        __emit 0x24
        __emit 0xf4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x84
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x50
        __emit 0x8b
        __emit 0xf1
        __emit 0x57
        __emit 0x56
        __emit 0xe8
        __emit 0x84
        __emit 0xa0
        __emit 0xa3
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x0c
        __emit 0x6a
        __emit 0x01
        __emit 0x6a
        __emit 0x10
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x1c
        __emit 0xe8
        __emit 0x0a
        __emit 0x0b
        __emit 0xa3
        __emit 0xff
        __emit 0x8b
        __emit 0x94
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x4e
        __emit 0x14
        __emit 0x51
        __emit 0x68
        __emit 0x04
        __emit 0x45
        __emit 0x11
        __emit 0x01
        __emit 0x52
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x20
        __emit 0x50
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xfc
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xe8
        __emit 0x89
        __emit 0x5b
        __emit 0xa3
        __emit 0xff
        __emit 0x8b
        __emit 0x94
        __emit 0x24
        __emit 0x08
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x4e
        __emit 0x10
        __emit 0x51
        __emit 0x68
        __emit 0x34
        __emit 0x44
        __emit 0x11
        __emit 0x01
        __emit 0x52
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x30
        __emit 0x50
        __emit 0xe8
        __emit 0xdd
        __emit 0x7d
        __emit 0xa3
        __emit 0xff
        __emit 0x8b
        __emit 0x94
        __emit 0x24
        __emit 0x18
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x4e
        __emit 0x20
        __emit 0x51
        __emit 0x68
        __emit 0xec
        __emit 0x44
        __emit 0x11
        __emit 0x01
        __emit 0x52
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x40
        __emit 0x50
        __emit 0xe8
        __emit 0x7a
        __emit 0x3c
        __emit 0xa0
        __emit 0xff
        __emit 0x8b
        __emit 0x94
        __emit 0x24
        __emit 0x28
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x8d
        __emit 0x4e
        __emit 0x08
        __emit 0x51
        __emit 0x68
        __emit 0x24
        __emit 0x44
        __emit 0x11
        __emit 0x01
        __emit 0x52
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x50
        __emit 0x50
        __emit 0xe8
        __emit 0x5f
        __emit 0x3c
        __emit 0xa0
        __emit 0xff
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0x38
        __emit 0x01
        __emit 0x00
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x40
        __emit 0x83
        __emit 0xc6
        __emit 0x09
        __emit 0x56
        __emit 0x68
        __emit 0x10
        __emit 0x44
        __emit 0x11
        __emit 0x01
        __emit 0x51
        __emit 0x8d
        __emit 0x54
        __emit 0x24
        __emit 0x20
        __emit 0x52
        __emit 0xe8
        __emit 0x41
        __emit 0x3c
        __emit 0xa0
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x10
        __emit 0x8d
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x50
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x18
        __emit 0xe8
        __emit 0xab
        __emit 0xf1
        __emit 0xa1
        __emit 0xff
        __emit 0x8b
        __emit 0x08
        __emit 0x8b
        __emit 0x40
        __emit 0x04
        __emit 0x8b
        __emit 0x17
        __emit 0x2b
        __emit 0xc1
        __emit 0x50
        __emit 0x51
        __emit 0x8b
        __emit 0xcf
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0xf4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x01
        __emit 0xff
        __emit 0x52
        __emit 0x10
        __emit 0x8b
        __emit 0x4c
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x2b
        __emit 0xc1
        __emit 0x85
        __emit 0xc9
        __emit 0xc6
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x74
        __emit 0x1c
        __emit 0x3d
        __emit 0x80
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x76
        __emit 0x0b
        __emit 0x51
        __emit 0xe8
        __emit 0xfa
        __emit 0x45
        __emit 0x28
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x04
        __emit 0xeb
        __emit 0x0a
        __emit 0x50
        __emit 0x51
        __emit 0xe8
        __emit 0x2e
        __emit 0x0d
        __emit 0x23
        __emit 0x00
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0xf8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x51
        __emit 0x57
        __emit 0xe8
        __emit 0xb9
        __emit 0x88
        __emit 0xa4
        __emit 0xff
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0xec
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xff
        __emit 0xe8
        __emit 0x8d
        __emit 0xbf
        __emit 0xa2
        __emit 0xff
        __emit 0x8d
        __emit 0x8c
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc7
        __emit 0x84
        __emit 0x24
        __emit 0x84
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc4
        __emit 0xeb
        __emit 0x12
        __emit 0x01
        __emit 0xe8
        __emit 0x2c
        __emit 0x1e
        __emit 0x24
        __emit 0x00
        __emit 0x8b
        __emit 0x8c
        __emit 0x24
        __emit 0xe4
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x5f
        __emit 0x5e
        __emit 0x64
        __emit 0x89
        __emit 0x0d
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x81
        __emit 0xc4
        __emit 0xe8
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0xc2
        __emit 0x08
        __emit 0x00
    }
}


} // namespace FXParticleSystem
