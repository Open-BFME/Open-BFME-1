// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Constructor-only slices keep the proven multiple-inheritance layout local;
// the lower 0x005DD290 base still has no recovered retail identity.

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

template <int Category>
class CategoryModuleInfo
{
public:
	virtual void unusedVirtual();
};

template <int Category>
class DefaultParticleModule : public T1A1_005DD290, public CategoryModuleInfo<Category>
{
public:
	DefaultParticleModule( void *system, void *module_template )
		: T1A1_005DD290( system, module_template )
	{
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ClientRandomValue.h
struct GameClientRandomVariable
{
	unsigned int m_storage[ 3 ];
};

class EmissionVelocityInfo
{
public:
	EmissionVelocityInfo( const EmissionVelocityInfo & ) {}
	virtual void unusedVirtual();
};

#define EMISSION_VELOCITY_INFO( NAME, COUNT )                              \
	class NAME##Info : public EmissionVelocityInfo                          \
	{                                                                       \
	public:                                                                 \
		NAME##Info( const NAME##Info &that )                                 \
			: EmissionVelocityInfo( that )                                    \
		{                                                                    \
			for ( int i = 0; i < COUNT; ++i )                                \
				m_variables[ i ] = that.m_variables[ i ];                       \
		}                                                                    \
	private:                                                                \
		GameClientRandomVariable m_variables[ COUNT ];                       \
	};

EMISSION_VELOCITY_INFO( SphericalEmissionVelocity, 1 )
EMISSION_VELOCITY_INFO( CylindricalEmissionVelocity, 2 )
EMISSION_VELOCITY_INFO( OutwardEmissionVelocity, 2 )

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

#define EMISSION_VELOCITY_MODULE( NAME )                                  \
	class NAME##ModuleTemplate                                              \
		: public CategoryModuleTemplateSlice, public NAME##Info              \
	{                                                                       \
	};                                                                      \
	class NAME##Module                                                      \
		: public DefaultParticleModule<4>, public NAME##Info                  \
	{                                                                       \
	public:                                                                 \
		NAME##Module( TrackingPtr<ParticleSystem> &system,                    \
			const NAME##ModuleTemplate *module_template );                     \
	};                                                                      \
	NAME##Module::NAME##Module( TrackingPtr<ParticleSystem> &system,         \
		const NAME##ModuleTemplate *module_template )                         \
		: DefaultParticleModule<4>( &system,                                  \
			const_cast<NAME##ModuleTemplate *>( module_template ) ),            \
		  NAME##Info( *module_template )                                     \
	{                                                                       \
	}

EMISSION_VELOCITY_MODULE( SphericalEmissionVelocity )
EMISSION_VELOCITY_MODULE( CylindricalEmissionVelocity )
EMISSION_VELOCITY_MODULE( OutwardEmissionVelocity )

}
