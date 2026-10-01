// Forwarders preserve the incoming object around one direct call.
#include <new>

namespace FXParticleSystem
{
template <int N> class DefaultModuleTag;
template <int N> class DefaultParticleModule;
template <int N> class DefaultParticleModuleTemplate;
template <int Category, const char (&Key)[1], const char (&Name)[1],
    class Module, class ModuleTemplate, class ParticleModule, class ParticleModuleTemplate>
class ModuleTag;
template <class Tag>
class ConcreteModuleClass
{
public:
    static const ConcreteModuleClass &getInstance();
};
class BoxEmissionVolumeModule;
class BoxEmissionVolumeModuleTemplate;
class ButterflyDrawModule;
class ButterflyDrawModuleTemplate;
class CylinderEmissionVolumeModule;
class CylinderEmissionVolumeModuleTemplate;
class CylindricalEmissionVelocityModule;
class CylindricalEmissionVelocityModuleTemplate;
class HemisphericalEmissionVelocityModule;
class HemisphericalEmissionVelocityModuleTemplate;
class LifeEventModule;
class LifeEventModuleTemplate;
class LightningDrawModule;
class LightningDrawModuleTemplate;
class LightningEmissionModule;
class LightningEmissionModuleTemplate;
class LineEmissionVolumeModule;
class LineEmissionVolumeModuleTemplate;
class OutwardEmissionVelocityModule;
class OutwardEmissionVelocityModuleTemplate;
class ParticleLifeEventModule;
class ParticleLifeEventModuleTemplate;
class ParticleTerrainCollisionModule;
class ParticleTerrainCollisionModuleTemplate;
class QuadDrawModule;
class QuadDrawModuleTemplate;
class RenderObjectDrawModule;
class RenderObjectDrawModuleTemplate;
class RenderObjectParticleUpdateModule;
class RenderObjectParticleUpdateModuleTemplate;
class RenderObjectUpdateModule;
class RenderObjectUpdateModuleTemplate;
class SphereEmissionVolumeModule;
class SphereEmissionVolumeModuleTemplate;
class SphericalEmissionVelocityModule;
class SphericalEmissionVelocityModuleTemplate;
class StreakDrawModule;
class StreakDrawModuleTemplate;
class TerrainCollisionModule;
class TerrainCollisionModuleTemplate;
extern const char BOX_EMISSION_VOLUME_MODULE_KEY[1];
extern const char BOX_EMISSION_VOLUME_MODULE_NAME[1];
extern const char BUTTERFLY_DRAW_MODULE_KEY[1];
extern const char BUTTERFLY_DRAW_MODULE_NAME[1];
extern const char CYLINDER_EMISSION_VOLUME_MODULE_KEY[1];
extern const char CYLINDER_EMISSION_VOLUME_MODULE_NAME[1];
extern const char CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY[1];
extern const char CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME[1];
extern const char HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY[1];
extern const char HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME[1];
extern const char LIFE_EVENT_MODULE_KEY[1];
extern const char LIFE_EVENT_MODULE_NAME[1];
extern const char LIGHTNING_DRAW_MODULE_KEY[1];
extern const char LIGHTNING_DRAW_MODULE_NAME[1];
extern const char LIGHTNING_EMISSION_MODULE_KEY[1];
extern const char LIGHTNING_EMISSION_MODULE_NAME[1];
extern const char LINE_EMISSION_VOLUME_MODULE_KEY[1];
extern const char LINE_EMISSION_VOLUME_MODULE_NAME[1];
extern const char OUTWARD_EMISSION_VELOCITY_MODULE_KEY[1];
extern const char OUTWARD_EMISSION_VELOCITY_MODULE_NAME[1];
extern const char QUAD_DRAW_MODULE_KEY[1];
extern const char QUAD_DRAW_MODULE_NAME[1];
extern const char RENDEROBJECT_DRAW_MODULE_KEY[1];
extern const char RENDEROBJECT_DRAW_MODULE_NAME[1];
extern const char RENDEROBJECT_UPDATE_MODULE_KEY[1];
extern const char RENDEROBJECT_UPDATE_MODULE_NAME[1];
extern const char SPHERE_EMISSION_VOLUME_MODULE_KEY[1];
extern const char SPHERE_EMISSION_VOLUME_MODULE_NAME[1];
extern const char SPHERICAL_EMISSION_VELOCITY_MODULE_KEY[1];
extern const char SPHERICAL_EMISSION_VELOCITY_MODULE_NAME[1];
extern const char STREAK_DRAW_MODULE_KEY[1];
extern const char STREAK_DRAW_MODULE_NAME[1];
extern const char TERRAIN_COLLISION_MODULE_KEY[1];
extern const char TERRAIN_COLLISION_MODULE_NAME[1];
struct OrthoEmissionVelocityModuleTag;
struct PointEmissionVolumeModuleTag;
typedef DefaultModuleTag<0> DefaultModuleTag0Tag;
typedef DefaultModuleTag<1> DefaultModuleTag1Tag;
typedef DefaultModuleTag<2> DefaultModuleTag2Tag;
typedef DefaultModuleTag<3> DefaultModuleTag3Tag;
typedef DefaultModuleTag<6> DefaultModuleTag6Tag;
typedef DefaultModuleTag<7> DefaultModuleTag7Tag;
typedef ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule, RenderObjectParticleUpdateModuleTemplate> RenderObjectUpdateTag;
typedef ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > CylindricalEmissionVelocityTag;
typedef ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > HemisphericalEmissionVelocityTag;
typedef ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > OutwardEmissionVelocityTag;
typedef ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > SphericalEmissionVelocityTag;
typedef ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > BoxEmissionVolumeTag;
typedef ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME, CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > CylinderEmissionVolumeTag;
typedef ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > LightningEmissionTag;
typedef ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > LineEmissionVolumeTag;
typedef ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY, SPHERE_EMISSION_VOLUME_MODULE_NAME, SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate, DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > SphereEmissionVolumeTag;
typedef ModuleTag<6, BUTTERFLY_DRAW_MODULE_KEY, BUTTERFLY_DRAW_MODULE_NAME, ButterflyDrawModule, ButterflyDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > ButterflyDrawTag;
typedef ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME, LightningDrawModule, LightningDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > LightningDrawTag;
typedef ModuleTag<6, QUAD_DRAW_MODULE_KEY, QUAD_DRAW_MODULE_NAME, QuadDrawModule, QuadDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > QuadDrawTag;
typedef ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY, RENDEROBJECT_DRAW_MODULE_NAME, RenderObjectDrawModule, RenderObjectDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > RenderObjectDrawTag;
typedef ModuleTag<6, STREAK_DRAW_MODULE_KEY, STREAK_DRAW_MODULE_NAME, StreakDrawModule, StreakDrawModuleTemplate, DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > StreakDrawTag;
typedef ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule, ParticleLifeEventModuleTemplate> LifeEventTag;
typedef ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME, TerrainCollisionModule, TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule, ParticleTerrainCollisionModuleTemplate> TerrainCollisionTag;
typedef OrthoEmissionVelocityModuleTag OrthoEmissionVelocityTag;
typedef PointEmissionVolumeModuleTag PointEmissionVolumeTag;
}



class Gen_002df780 { public: void *m(); };
class Template { public: __declspec(nothrow) Template(); };
class Gen003A0410 { public: __declspec(nothrow) Gen003A0410(); };
class Rva00761E10 { public: __declspec(nothrow) Rva00761E10(); };
void __cdecl InitDbghelp();
void __cdecl W3DRadarResetLock();

using namespace FXParticleSystem;

#define BFME_THIS_FORWARD(NAME, CALL) \
    class NAME { public: NAME *forward(); }; \
    NAME *NAME::forward() { __assume(this != 0); CALL; return this; }

BFME_THIS_FORWARD( Rva0007BCD0Forwarder, (W3DRadarResetLock()) )
BFME_THIS_FORWARD( Rva002DB200Forwarder, (new (this) Gen003A0410) )
BFME_THIS_FORWARD( Rva002E2A30Forwarder, (((Gen_002df780 *)this)->m()) )
BFME_THIS_FORWARD( Rva00339580Forwarder, (new (this) Template) )
BFME_THIS_FORWARD( Rva0033B090Forwarder, (new (this) Template) )
BFME_THIS_FORWARD( Rva005E3FD0Forwarder, (ConcreteModuleClass<DefaultModuleTag1Tag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E3FE0Forwarder, (ConcreteModuleClass<DefaultModuleTag0Tag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E3FF0Forwarder, (ConcreteModuleClass<DefaultModuleTag3Tag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E4000Forwarder, (ConcreteModuleClass<DefaultModuleTag2Tag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E4010Forwarder, (ConcreteModuleClass<DefaultModuleTag7Tag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E4020Forwarder, (ConcreteModuleClass<LifeEventTag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E4030Forwarder, (ConcreteModuleClass<RenderObjectUpdateTag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E4040Forwarder, (ConcreteModuleClass<TerrainCollisionTag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E4050Forwarder, (ConcreteModuleClass<OrthoEmissionVelocityTag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E4060Forwarder, (ConcreteModuleClass<SphericalEmissionVelocityTag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E4070Forwarder, (ConcreteModuleClass<HemisphericalEmissionVelocityTag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E4080Forwarder, (ConcreteModuleClass<CylindricalEmissionVelocityTag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E4090Forwarder, (ConcreteModuleClass<OutwardEmissionVelocityTag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E40A0Forwarder, (ConcreteModuleClass<PointEmissionVolumeTag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E40B0Forwarder, (ConcreteModuleClass<LineEmissionVolumeTag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E40C0Forwarder, (ConcreteModuleClass<BoxEmissionVolumeTag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E40D0Forwarder, (ConcreteModuleClass<SphereEmissionVolumeTag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E40E0Forwarder, (ConcreteModuleClass<CylinderEmissionVolumeTag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E40F0Forwarder, (ConcreteModuleClass<LightningEmissionTag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E5710Forwarder, (ConcreteModuleClass<DefaultModuleTag1Tag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E5720Forwarder, (ConcreteModuleClass<DefaultModuleTag0Tag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E5730Forwarder, (ConcreteModuleClass<DefaultModuleTag3Tag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E5740Forwarder, (ConcreteModuleClass<DefaultModuleTag2Tag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E5750Forwarder, (ConcreteModuleClass<DefaultModuleTag7Tag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E5760Forwarder, (ConcreteModuleClass<LifeEventTag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E5770Forwarder, (ConcreteModuleClass<RenderObjectUpdateTag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E5780Forwarder, (ConcreteModuleClass<TerrainCollisionTag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E5790Forwarder, (ConcreteModuleClass<OrthoEmissionVelocityTag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E57A0Forwarder, (ConcreteModuleClass<SphericalEmissionVelocityTag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E57B0Forwarder, (ConcreteModuleClass<HemisphericalEmissionVelocityTag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E57C0Forwarder, (ConcreteModuleClass<CylindricalEmissionVelocityTag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E57D0Forwarder, (ConcreteModuleClass<OutwardEmissionVelocityTag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E57E0Forwarder, (ConcreteModuleClass<PointEmissionVolumeTag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E57F0Forwarder, (ConcreteModuleClass<LineEmissionVolumeTag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E5800Forwarder, (ConcreteModuleClass<BoxEmissionVolumeTag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E5810Forwarder, (ConcreteModuleClass<SphereEmissionVolumeTag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E5820Forwarder, (ConcreteModuleClass<CylinderEmissionVolumeTag>::getInstance()) )
BFME_THIS_FORWARD( Rva005E5830Forwarder, (ConcreteModuleClass<LightningEmissionTag>::getInstance()) )
BFME_THIS_FORWARD( Rva005F2D70Forwarder, (ConcreteModuleClass<ButterflyDrawTag>::getInstance()) )
BFME_THIS_FORWARD( Rva005F36C0Forwarder, (ConcreteModuleClass<DefaultModuleTag6Tag>::getInstance()) )
BFME_THIS_FORWARD( Rva005F4FE0Forwarder, (ConcreteModuleClass<LightningDrawTag>::getInstance()) )
BFME_THIS_FORWARD( Rva005F6580Forwarder, (ConcreteModuleClass<QuadDrawTag>::getInstance()) )
BFME_THIS_FORWARD( Rva005F7970Forwarder, (ConcreteModuleClass<RenderObjectDrawTag>::getInstance()) )
BFME_THIS_FORWARD( Rva005F8530Forwarder, (ConcreteModuleClass<StreakDrawTag>::getInstance()) )
BFME_THIS_FORWARD( Rva00765AF0Forwarder, (new (this) Rva00761E10) )
BFME_THIS_FORWARD( Rva0088CDC0Forwarder, (InitDbghelp()) )
