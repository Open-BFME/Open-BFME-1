// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

// Open-BFME5: TerrainCollision ConcreteModuleTemplate::clone

namespace FXParticleSystem
{
class TerrainCollisionModule {};
class TerrainCollisionModuleTemplate {};
class ParticleTerrainCollisionModule {};
class ParticleTerrainCollisionModuleTemplate {};
extern const char TERRAIN_COLLISION_MODULE_KEY[1];
extern const char TERRAIN_COLLISION_MODULE_NAME[1];
template <int Category, const char (&Key)[1], const char (&Name)[1], class Module,
    class ModuleTemplate, class ParticleModule, class ParticleModuleTemplate>
class ModuleTag {};
typedef ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME,
    TerrainCollisionModule, TerrainCollisionModuleTemplate,
    ParticleTerrainCollisionModule, ParticleTerrainCollisionModuleTemplate> TerrainCollisionModuleTag;
void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);
class TerrainCollisionTemplateCopyCtorShim
{
public:
    void construct(const void *source);
};
extern "C" char TerrainCollisionConcrete_vtbl0;
extern "C" char TerrainCollisionConcrete_vtbl4;
extern "C" char TerrainCollisionConcrete_vtbl12;
class TerrainCollisionTemplateAllocation
{
public:
    __forceinline TerrainCollisionTemplateAllocation(const void *source)
    {
        ((TerrainCollisionTemplateCopyCtorShim *)this)->construct(source);
        *(void **)((char *)this + 0) = &TerrainCollisionConcrete_vtbl0;
        *(void **)((char *)this + 4) = &TerrainCollisionConcrete_vtbl4;
        *(void **)((char *)this + 12) = &TerrainCollisionConcrete_vtbl12;
    }
private:
    unsigned char m_bytes[0x28];
};
template <class Tag> class ConcreteModuleTemplate;
template <>
class ConcreteModuleTemplate<TerrainCollisionModuleTag>
{
public:
    virtual TerrainCollisionModuleTemplate *clone() const;
};
TerrainCollisionModuleTemplate *ConcreteModuleTemplate<TerrainCollisionModuleTag>::clone() const
{
    return (TerrainCollisionModuleTemplate *)new TerrainCollisionTemplateAllocation(this);
}
}
