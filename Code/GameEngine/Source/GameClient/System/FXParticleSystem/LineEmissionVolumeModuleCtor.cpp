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

class LineEmissionVolumeInfo : public EmissionVolumeInfo
{
public:
	LineEmissionVolumeInfo( const LineEmissionVolumeInfo &that )
		: EmissionVolumeInfo( that )
	{
		m_endpoints[ 0 ] = that.m_endpoints[ 0 ];
		m_endpoints[ 1 ] = that.m_endpoints[ 1 ];
		m_endpoints[ 2 ] = that.m_endpoints[ 2 ];
		m_endpoints[ 3 ] = that.m_endpoints[ 3 ];
		m_endpoints[ 4 ] = that.m_endpoints[ 4 ];
		m_endpoints[ 5 ] = that.m_endpoints[ 5 ];
	}
	virtual void unusedVirtual();

private:
	float m_endpoints[ 6 ];
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

class LineEmissionVolumeModuleTemplate
	: public CategoryModuleTemplateSlice, public LineEmissionVolumeInfo
{
};

class LineEmissionVolumeModule
	: public DefaultParticleModule<5>, public LineEmissionVolumeInfo
{
public:
	LineEmissionVolumeModule( TrackingPtr<ParticleSystem> &system,
		const LineEmissionVolumeModuleTemplate *module_template );
};

LineEmissionVolumeModule::LineEmissionVolumeModule(
	TrackingPtr<ParticleSystem> &system,
	const LineEmissionVolumeModuleTemplate *module_template )
	: DefaultParticleModule<5>( &system,
		const_cast<LineEmissionVolumeModuleTemplate *>( module_template ) ),
	  LineEmissionVolumeInfo( *module_template )
{
}

}
