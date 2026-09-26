// cl: /EHs-c-

// The public FX particle header intentionally keeps ConcreteModuleClass
// specializations empty: fx_particle_system.cpp builds a second FXPS_V mode
// with a virtual view.  This TU owns the actual TerrainCollision singleton
// ABI only.  Its four data words are the retail object at 0x012F6B24: table,
// the two source-pointer values, and the category-8 registry link.  The
// constructor and destructor symbols remain the independently matched
// definitions in fx_particle_system_bulk.cpp; this inline semantic view is
// needed only so MSVC7.1 materializes their body inside the guarded
// function-local static.

namespace FXParticleSystem
{

class TerrainCollisionModule;
class TerrainCollisionModuleTemplate;
class ParticleTerrainCollisionModule;
class ParticleTerrainCollisionModuleTemplate;

extern const char TERRAIN_COLLISION_MODULE_KEY[1];
extern const char TERRAIN_COLLISION_MODULE_NAME[1];

template <int Category, const char (&Key)[1], const char (&Name)[1],
	class Module, class ModuleTemplate, class ParticleModule,
	class ParticleModuleTemplate>
class ModuleTag;

template <class Tag>
class ConcreteModuleClass;

typedef ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY,
	TERRAIN_COLLISION_MODULE_NAME, TerrainCollisionModule,
	TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule,
	ParticleTerrainCollisionModuleTemplate> TerrainCollisionTag;

// Retail globals: +4 reads [0x012F6D28], +8 reads [0x012F6D2C], and the
// category-8 chain head is [0x012F6508].  These names are TU-local ABI
// declarations; their DIR32 relocations are checked against those operands.
extern void **terrainCollisionSourceAt4;
extern void **terrainCollisionSourceAt8;
extern ConcreteModuleClass<TerrainCollisionTag> *terrainCollisionRegistryHead;
extern void *terrainCollisionVtable[];

template <>
class ConcreteModuleClass<TerrainCollisionTag>
{
public:
	ConcreteModuleClass()
	{
		void *sourceAt8 = *terrainCollisionSourceAt8;
		void *sourceAt4 = *terrainCollisionSourceAt4;
		m_sourceAt8 = sourceAt8;
		m_sourceAt4 = sourceAt4;
		m_next = terrainCollisionRegistryHead;
		terrainCollisionRegistryHead = this;
		m_table = terrainCollisionVtable;
	}

	~ConcreteModuleClass();
	static const ConcreteModuleClass<TerrainCollisionTag> &getInstance();

private:
	void *m_table;
	void *m_sourceAt4;
	void *m_sourceAt8;
	ConcreteModuleClass *m_next;
};

const ConcreteModuleClass<TerrainCollisionTag> &
ConcreteModuleClass<TerrainCollisionTag>::getInstance()
{
	static ConcreteModuleClass<TerrainCollisionTag> instance;
	return instance;
}

}
