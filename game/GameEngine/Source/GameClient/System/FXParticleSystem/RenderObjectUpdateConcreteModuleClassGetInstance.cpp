// cl: /EHs-c-

// The public FX particle header keeps ConcreteModuleClass specializations
// empty because fx_particle_system.cpp also builds an FXPS_V virtual view.
// This TU owns the named RenderObjectUpdate singleton ABI only.  The module
// is the RenderObjectParticleUpdate family represented by ModuleTag<2,...>
// (the MSVC $01 spelling), and its four data words are the retail object at
// 0x012F6B0C: table, the two source-pointer values, and the registry link at
// 0x012F64F0.  The constructor and destructor remain the independently
// matched definitions in fx_particle_system_bulk.cpp.

namespace FXParticleSystem
{

class RenderObjectUpdateModule;
class RenderObjectUpdateModuleTemplate;
class RenderObjectParticleUpdateModule;
class RenderObjectParticleUpdateModuleTemplate;

extern const char RENDEROBJECT_UPDATE_MODULE_KEY[1];
extern const char RENDEROBJECT_UPDATE_MODULE_NAME[1];

template <int Category, const char (&Key)[1], const char (&Name)[1],
	class Module, class ModuleTemplate, class ParticleModule,
	class ParticleModuleTemplate>
class ModuleTag;

template <class Tag>
class ConcreteModuleClass;

typedef ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY,
	RENDEROBJECT_UPDATE_MODULE_NAME,
	RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate,
	RenderObjectParticleUpdateModule,
	RenderObjectParticleUpdateModuleTemplate>
	RenderObjectUpdateTag;

// Retail globals: +4 reads [0x012F6D20], +8 reads [0x012F6D24], and the
// registry chain head is [0x012F64F0].  These names are TU-local ABI
// declarations; their DIR32 relocations are checked against those operands.
extern void **renderObjectUpdateSourceAt4;
extern void **renderObjectUpdateSourceAt8;
extern ConcreteModuleClass<RenderObjectUpdateTag> *
	renderObjectUpdateRegistryHead;
extern void *renderObjectUpdateVtable[];

template <>
class ConcreteModuleClass<RenderObjectUpdateTag>
{
public:
	ConcreteModuleClass()
	{
		void *sourceAt8 = *renderObjectUpdateSourceAt8;
		void *sourceAt4 = *renderObjectUpdateSourceAt4;
		m_sourceAt8 = sourceAt8;
		m_sourceAt4 = sourceAt4;
		m_next = renderObjectUpdateRegistryHead;
		renderObjectUpdateRegistryHead = this;
		m_table = renderObjectUpdateVtable;
	}

	~ConcreteModuleClass();
	static const ConcreteModuleClass<RenderObjectUpdateTag> &getInstance();

private:
	void *m_table;
	void *m_sourceAt4;
	void *m_sourceAt8;
	ConcreteModuleClass *m_next;
};

const ConcreteModuleClass<RenderObjectUpdateTag> &
ConcreteModuleClass<RenderObjectUpdateTag>::getInstance()
{
	static ConcreteModuleClass<RenderObjectUpdateTag> instance;
	return instance;
}

}
