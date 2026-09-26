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
	EmissionVolumeInfo( const EmissionVolumeInfo &that )
		: m_flag( that.m_flag )
	{
	}
	virtual void unusedVirtual();

private:
	bool m_flag;
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

class PointEmissionVolumeModuleTemplate
	: public CategoryModuleTemplateSlice, public EmissionVolumeInfo
{
};

class PointEmissionVolumeModule
	: public DefaultParticleModule<5>, public EmissionVolumeInfo
{
public:
	PointEmissionVolumeModule( TrackingPtr<ParticleSystem> &system,
		const PointEmissionVolumeModuleTemplate *module_template );
};

PointEmissionVolumeModule::PointEmissionVolumeModule(
	TrackingPtr<ParticleSystem> &system,
	const PointEmissionVolumeModuleTemplate *module_template )
	: DefaultParticleModule<5>( &system,
		const_cast<PointEmissionVolumeModuleTemplate *>( module_template ) ),
	  EmissionVolumeInfo( *module_template )
{
}

}
