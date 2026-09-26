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

class CylinderEmissionVolumeInfo : public EmissionVolumeInfo
{
public:
	CylinderEmissionVolumeInfo( const CylinderEmissionVolumeInfo &that )
		: EmissionVolumeInfo( that )
	{
		m_shape[ 0 ] = that.m_shape[ 0 ];
		m_shape[ 1 ] = that.m_shape[ 1 ];
		m_shape[ 2 ] = that.m_shape[ 2 ];
		m_shape[ 3 ] = that.m_shape[ 3 ];
		m_shape[ 4 ] = that.m_shape[ 4 ];
	}
	virtual void unusedVirtual();

private:
	float m_shape[ 5 ];
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

class CylinderEmissionVolumeModuleTemplate
	: public CategoryModuleTemplateSlice, public CylinderEmissionVolumeInfo
{
};

class CylinderEmissionVolumeModule
	: public DefaultParticleModule<5>, public CylinderEmissionVolumeInfo
{
public:
	CylinderEmissionVolumeModule( TrackingPtr<ParticleSystem> &system,
		const CylinderEmissionVolumeModuleTemplate *module_template );
};

CylinderEmissionVolumeModule::CylinderEmissionVolumeModule(
	TrackingPtr<ParticleSystem> &system,
	const CylinderEmissionVolumeModuleTemplate *module_template )
	: DefaultParticleModule<5>( &system,
		const_cast<CylinderEmissionVolumeModuleTemplate *>( module_template ) ),
	  CylinderEmissionVolumeInfo( *module_template )
{
}

}
