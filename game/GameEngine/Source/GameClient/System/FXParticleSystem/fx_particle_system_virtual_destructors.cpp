namespace FXParticleSystem {

class RenderObjectDrawModule;
class LifeEventModule;
class TerrainCollisionModule;
class ParticleLifeEventModule;
class ParticleLifeEventModuleTemplate;
class ParticleTerrainCollisionModule;
class ParticleTerrainCollisionModuleTemplate;
template <int N> class DefaultParticleModule;
template <int N> class DefaultParticleModuleTemplate;

extern const char RENDEROBJECT_DRAW_MODULE_KEY[1];
extern const char RENDEROBJECT_DRAW_MODULE_NAME[1];
extern const char LIFE_EVENT_MODULE_KEY[1];
extern const char LIFE_EVENT_MODULE_NAME[1];
extern const char TERRAIN_COLLISION_MODULE_KEY[1];
extern const char TERRAIN_COLLISION_MODULE_NAME[1];

class RenderObjectDrawModuleTemplate { public: virtual ~RenderObjectDrawModuleTemplate(); };
class LifeEventModuleTemplate { public: virtual ~LifeEventModuleTemplate(); };
class TerrainCollisionModuleTemplate { public: virtual ~TerrainCollisionModuleTemplate(); };

template <int Category, const char (&Key)[1], const char (&Name)[1], class Module,
	class ModuleTemplate, class DefaultParticleModule, class DefaultParticleModuleTemplate>
class ModuleTag;
template <typename Tag> class ConcreteModuleTemplate;

typedef ModuleTag<6, RENDEROBJECT_DRAW_MODULE_KEY, RENDEROBJECT_DRAW_MODULE_NAME,
	RenderObjectDrawModule, RenderObjectDrawModuleTemplate,
	DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > RenderObjectDrawTag;
typedef ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME,
	LifeEventModule, LifeEventModuleTemplate,
	ParticleLifeEventModule, ParticleLifeEventModuleTemplate> LifeEventTag;
typedef ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME,
	TerrainCollisionModule, TerrainCollisionModuleTemplate,
	ParticleTerrainCollisionModule, ParticleTerrainCollisionModuleTemplate> TerrainCollisionTag;

template <> class __declspec(novtable) ConcreteModuleTemplate<RenderObjectDrawTag>
	: public RenderObjectDrawModuleTemplate { public: virtual ~ConcreteModuleTemplate(); };
template <> class __declspec(novtable) ConcreteModuleTemplate<LifeEventTag>
	: public LifeEventModuleTemplate { public: virtual ~ConcreteModuleTemplate(); };
template <> class __declspec(novtable) ConcreteModuleTemplate<TerrainCollisionTag>
	: public TerrainCollisionModuleTemplate { public: virtual ~ConcreteModuleTemplate(); };

ConcreteModuleTemplate<RenderObjectDrawTag>::~ConcreteModuleTemplate() {}
ConcreteModuleTemplate<LifeEventTag>::~ConcreteModuleTemplate() {}
ConcreteModuleTemplate<TerrainCollisionTag>::~ConcreteModuleTemplate() {}

}
