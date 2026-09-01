// ??0LifeEventModule@FXParticleSystem@@QAE@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@1@PBVLifeEventModuleTemplate@1@@Z
// partial score=0.78 date=2026-08-31
// cl: /DNDEBUG /MD /GX /O2 /Ob2

class T1A1_005DD290
{
public:
	T1A1_005DD290( void *system, void *module_template );
	virtual void unusedVirtual();

private:
	unsigned int m_storage[ 4 ];
};

class FXList;

class GameClientRandomVariable
{
public:
	float getValue() const;

private:
	unsigned int m_storage[ 3 ];
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

class ParticleLifeEventSlice
{
public:
	ParticleLifeEventSlice() : m_flag0( true ), m_flag1( true ) {}
	virtual void unusedVirtual();

protected:
	bool m_flag0;
	bool m_flag1;
};

class ParticleLifeEventModule
	: public T1A1_005DD290,
	  public ParticleModuleCategorySlice,
	  public ParticleLifeEventSlice
{
public:
	ParticleLifeEventModule( void *system, void *module_template )
		: T1A1_005DD290( system, module_template )
	{
	}
};

class LifeEventModuleInfo
{
public:
	LifeEventModuleInfo();
	virtual ~LifeEventModuleInfo();
	virtual void unusedVirtual();

private:
	unsigned int m_event_name;
	GameClientRandomVariable m_event_time;
	const FXList *m_cached;
};

class LifeEventModuleTemplate
{
};

class TerrainCollisionEventFXLookupShim
{
public:
	const FXList *lookup( const char *name ) const;
};

extern "C" TerrainCollisionEventFXLookupShim *g_terrainCollisionEventFXListStore;

class LifeEventModule
	: public ParticleLifeEventModule, public LifeEventModuleInfo
{
public:
	LifeEventModule( TrackingPtr<ParticleSystem> &system,
		const LifeEventModuleTemplate *module_template );

private:
	int m_event_frame;
	bool m_pending;
};

LifeEventModule::LifeEventModule( TrackingPtr<ParticleSystem> &system,
	const LifeEventModuleTemplate *module_template )
	: ParticleLifeEventModule( &system,
		const_cast<LifeEventModuleTemplate *>( module_template ) ),
	  LifeEventModuleInfo()
{
	const unsigned char *source =
		reinterpret_cast<const unsigned char *>( module_template );
	unsigned char *destination = reinterpret_cast<unsigned char *>( this );

	unsigned int *destination_random =
		reinterpret_cast<unsigned int *>( destination + 0x28 );
	const unsigned int *source_random =
		reinterpret_cast<const unsigned int *>( source + 0x14 );
	destination_random[ 0 ] = source_random[ 0 ];
	destination_random[ 1 ] = source_random[ 1 ];
	destination_random[ 2 ] = source_random[ 2 ];

	const FXList **source_cached = reinterpret_cast<const FXList **>(
		const_cast<unsigned char *>( source ) + 0x20 );
	if ( !*source_cached )
	{
		const char *text = *reinterpret_cast<const char *const *>( source + 0x10 );
		*source_cached = g_terrainCollisionEventFXListStore->lookup(
			text ? text + 8 : reinterpret_cast<const char *>( 0x0107388B ) );
	}
	*reinterpret_cast<const FXList **>( destination + 0x34 ) = *source_cached;

	destination[ 0x1C ] = source[ 8 ];
	destination[ 0x1D ] = source[ 9 ];

	GameClientRandomVariable *event_time =
		reinterpret_cast<GameClientRandomVariable *>( destination + 0x28 );
	m_event_frame = static_cast<int>( event_time->getValue() );
	m_pending = true;
}

}
