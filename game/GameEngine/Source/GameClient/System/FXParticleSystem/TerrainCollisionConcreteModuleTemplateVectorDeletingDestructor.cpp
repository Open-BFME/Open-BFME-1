// cl: /O2
// Retail RVA 0x005E1FB0. Destructor ILT 0x0001BA81 routes directly to the
// matched TerrainCollision ConcreteModuleTemplate destructor. Element size 0x28.
void operator delete[](void *block);

namespace FXParticleSystem
{
extern const char TERRAIN_COLLISION_MODULE_KEY[1];
extern const char TERRAIN_COLLISION_MODULE_NAME[1];
class TerrainCollisionModule;
class TerrainCollisionModuleTemplate;
class ParticleTerrainCollisionModule;
class ParticleTerrainCollisionModuleTemplate;
template<int Category, const char (&Key)[1], const char (&Name)[1], class Module,
    class ModuleTemplate, class DefaultModule, class DefaultModuleTemplate>
class ModuleTag;
template<class Tag> class ConcreteModuleTemplate
{
public:
    virtual ~ConcreteModuleTemplate();
private:
    unsigned char m_data[0x24];
};
typedef ConcreteModuleTemplate<ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY,
    TERRAIN_COLLISION_MODULE_NAME, TerrainCollisionModule,
    TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule,
    ParticleTerrainCollisionModuleTemplate> > TerrainCollisionTemplate;
TerrainCollisionTemplate *MakeTerrainCollisionTemplateArray()
{
    return new TerrainCollisionTemplate[2];
}
void DeleteTerrainCollisionTemplateArray(TerrainCollisionTemplate *array)
{
    delete[] array;
}
}
