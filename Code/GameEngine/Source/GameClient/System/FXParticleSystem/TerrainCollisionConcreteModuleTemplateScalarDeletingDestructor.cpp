// cl: /O2
// Retail RVA 0x005E1F80. Destructor ILT 0x0001BA81 routes directly to the
// matched TerrainCollision ConcreteModuleTemplate destructor.
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
TerrainCollisionTemplate *MakeTerrainCollisionTemplate()
{
    return new TerrainCollisionTemplate;
}
void DeleteTerrainCollisionTemplate(TerrainCollisionTemplate *object)
{
    delete object;
}
}
