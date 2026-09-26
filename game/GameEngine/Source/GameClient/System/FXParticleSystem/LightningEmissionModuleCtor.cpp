// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Constructor-only slices preserve the retail multiple-inheritance layout
// without exposing it through the shared particle-system header.

class T1A1_005DD290
{
public:
	T1A1_005DD290( void *system, void *module_template );
	virtual void unusedVirtual();

private:
	unsigned int m_storage[ 4 ];
};

namespace FXParticleSystem
{

class ParticleSystem;

template <class T>
class TrackingPtr
{
};

class ParticleModuleCategorySlice
{
public:
	virtual void unusedVirtual();
};

class ParticleModuleSnapshotSlice
{
public:
	virtual void unusedVirtual();
};

template <int Category>
class DefaultParticleModule
	: public T1A1_005DD290,
	  public ParticleModuleCategorySlice,
	  public ParticleModuleSnapshotSlice
{
public:
	DefaultParticleModule( void *system, void *module_template )
		: T1A1_005DD290( system, module_template )
	{
	}
};

class EmissionVolumeInfo
{
public:
	virtual void unusedVirtual();

private:
	unsigned int m_storage;
};

class LightningEmissionInfo : public EmissionVolumeInfo
{
public:
	LightningEmissionInfo( const LightningEmissionInfo &that );
	virtual ~LightningEmissionInfo();
};

struct LightningEmissionRecord
{
	unsigned int m_words[ 3 ];
};

class ModuleTemplateSlice
{
public:
	virtual void unusedVirtual();
};

class CategoryModuleTemplateInfoSlice
{
public:
	virtual void unusedVirtual();
};

class CategoryModuleTemplateSlice
	: public ModuleTemplateSlice, public CategoryModuleTemplateInfoSlice
{
};

class LightningEmissionModuleTemplate
	: public CategoryModuleTemplateSlice,
 	  public LightningEmissionInfo
{
public:
	LightningEmissionRecord m_records[ 11 ];
};

class LightningEmissionModule
	: public DefaultParticleModule<5>,
 	  public LightningEmissionInfo
{
public:
	LightningEmissionModule( TrackingPtr<ParticleSystem> &system,
		const LightningEmissionModuleTemplate *module_template );

private:
	LightningEmissionRecord m_records[ 11 ];
};

LightningEmissionModule::LightningEmissionModule(
	TrackingPtr<ParticleSystem> &system,
	const LightningEmissionModuleTemplate *module_template )
	: DefaultParticleModule<5>( &system,
		const_cast<LightningEmissionModuleTemplate *>( module_template ) ),
 	  LightningEmissionInfo( *module_template )
{
	m_records[ 0 ] = module_template->m_records[ 0 ];
	m_records[ 1 ] = module_template->m_records[ 1 ];
	m_records[ 2 ] = module_template->m_records[ 2 ];
	m_records[ 3 ] = module_template->m_records[ 3 ];
	m_records[ 4 ] = module_template->m_records[ 4 ];
	m_records[ 5 ] = module_template->m_records[ 5 ];
	m_records[ 6 ] = module_template->m_records[ 6 ];
	m_records[ 7 ] = module_template->m_records[ 7 ];
	m_records[ 8 ] = module_template->m_records[ 8 ];
	m_records[ 9 ] = module_template->m_records[ 9 ];
	m_records[ 10 ] = module_template->m_records[ 10 ];
}

}
