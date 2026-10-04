// cl: /DNDEBUG /MD /EHsc

// BeaconClientUpdate::clientUpdate (retail 0x00603640) and the file-static
// createParticleSystem helper it calls (retail 0x006032F0), ported from Zero
// Hour's GameClient/Drawable/Update/BeaconClientUpdate.cpp.
//
// Identity: the vtable 0x01115248 installed by the matched constructor
// 0x006030C0 routes its last slot (+0x28, ClientUpdateModule::clientUpdate)
// through ILT 0x000369C6 to 0x00603640. The helper is reached only from there
// and formats the twin's "BeaconSmoke%6.6X" / "BeaconSmokeFFFFFF" literals.
//
// BFME changes against the twin: particle systems are held through the
// intrusive ParticleSystemHandle (returned in a hidden slot the caller passes
// in ESI, the compiler-private ABI of a same-TU static), the new system is
// offset 3 units up, the failsafe no longer tints, and a hidden beacon is made
// unselectable and sunk to -100.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

enum { FALSE = 0, TRUE = 1 };

struct Coord3D
{
	Real x, y, z;
};

// By-value string argument model: inputs/reference/shims/stringinline/StringInline.h
template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();
	void releaseBuffer();

	StringInlineData<T> *m_data;
};

template <>
inline StringBase<char>::~StringBase()
{
	releaseBuffer();
}

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	void format( AsciiString format, ... );
};

enum ParticleSystemID
{
	INVALID_PARTICLE_SYSTEM_ID = 0
};

class Drawable;
class ParticleSystemHandle;
class ParticleSystemTemplate;

class ParticleSystem
{
public:
	void attachToDrawable( const Drawable *draw );
	void setPosition( const Coord3D *pos );
	ParticleSystemID getSystemID( void ) const { return m_systemID; }

	unsigned char m_unmodelled_00[ 0x98 ];
	ParticleSystemHandle *m_firstHandle;		// +0x98
	ParticleSystemHandle *m_lastHandle;			// +0x9C
	unsigned char m_unmodelled_A0[ 0xC ];
	ParticleSystemID m_systemID;				// +0xAC
};

ParticleSystem *emptyParticleSystem( void );

// Intrusive handle: each handle links itself into its system's handle list.
class ParticleSystemHandle
{
public:
	ParticleSystemHandle() : m_system( 0 ), m_previous( 0 ), m_next( 0 ) {}
	ParticleSystemHandle( const ParticleSystemHandle &other )
		: m_system( other.m_system )
	{
		if (m_system)
		{
			m_previous = m_system->m_lastHandle;
			m_next = 0;
			m_system->m_lastHandle = this;
			if (m_previous)
				m_previous->m_next = this;
			else
				m_system->m_firstHandle = this;
		}
		else
		{
			m_next = 0;
			m_previous = 0;
		}
	}
	~ParticleSystemHandle() throw();
	ParticleSystemHandle &operator=( const ParticleSystemHandle &other ) throw();

	operator Bool() const { return m_system != 0; }
	ParticleSystem *operator->() const
	{
		if (!m_system)
			return emptyParticleSystem();
		return m_system;
	}

	ParticleSystem *m_system;
	ParticleSystemHandle *m_previous;
	ParticleSystemHandle *m_next;
};

class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findTemplate( const AsciiString &name ) const;
	ParticleSystemHandle createParticleSystem( const ParticleSystemTemplate *sysTemplate,
		Bool createSlaves ) throw();
};

extern ParticleSystemManager *TheParticleSystemManager;

class Object
{
public:
	UnsignedInt getIndicatorColor( void ) const;
};

class Thing
{
public:
	void setPositionZ( Real z );
};

class Drawable : public Thing
{
public:
	Object *getObject( void ) { return m_object; }
	Bool isDrawableEffectivelyHidden( void ) const;
	const Coord3D *getPosition( void ) const;
	void setSelectable( Bool selectable );

	unsigned char m_unmodelled_00[ 0xFC ];
	Object *m_object;							// +0xFC
};

// BFME RadarEventType: the twin's RADAR_EVENT_BEACON_PULSE call site passes 6 here.
enum RadarEventType
{
	RADAR_EVENT_BEACON_PULSE = 6
};

class Radar
{
public:
	void createEvent( const Coord3D *world, RadarEventType type, Real secondsToLive );
};

extern Radar *TheRadar;

// InGameUI::deselectDrawable is slot 57 (+0xE4); see Drawable::setSelectable.
#define BEACON_INGAMEUI_SLOT(n) virtual void unmodelledSlot##n() = 0;
class InGameUI
{
public:
	BEACON_INGAMEUI_SLOT(0) BEACON_INGAMEUI_SLOT(1) BEACON_INGAMEUI_SLOT(2) BEACON_INGAMEUI_SLOT(3)
	BEACON_INGAMEUI_SLOT(4) BEACON_INGAMEUI_SLOT(5) BEACON_INGAMEUI_SLOT(6) BEACON_INGAMEUI_SLOT(7)
	BEACON_INGAMEUI_SLOT(8) BEACON_INGAMEUI_SLOT(9) BEACON_INGAMEUI_SLOT(10) BEACON_INGAMEUI_SLOT(11)
	BEACON_INGAMEUI_SLOT(12) BEACON_INGAMEUI_SLOT(13) BEACON_INGAMEUI_SLOT(14) BEACON_INGAMEUI_SLOT(15)
	BEACON_INGAMEUI_SLOT(16) BEACON_INGAMEUI_SLOT(17) BEACON_INGAMEUI_SLOT(18) BEACON_INGAMEUI_SLOT(19)
	BEACON_INGAMEUI_SLOT(20) BEACON_INGAMEUI_SLOT(21) BEACON_INGAMEUI_SLOT(22) BEACON_INGAMEUI_SLOT(23)
	BEACON_INGAMEUI_SLOT(24) BEACON_INGAMEUI_SLOT(25) BEACON_INGAMEUI_SLOT(26) BEACON_INGAMEUI_SLOT(27)
	BEACON_INGAMEUI_SLOT(28) BEACON_INGAMEUI_SLOT(29) BEACON_INGAMEUI_SLOT(30) BEACON_INGAMEUI_SLOT(31)
	BEACON_INGAMEUI_SLOT(32) BEACON_INGAMEUI_SLOT(33) BEACON_INGAMEUI_SLOT(34) BEACON_INGAMEUI_SLOT(35)
	BEACON_INGAMEUI_SLOT(36) BEACON_INGAMEUI_SLOT(37) BEACON_INGAMEUI_SLOT(38) BEACON_INGAMEUI_SLOT(39)
	BEACON_INGAMEUI_SLOT(40) BEACON_INGAMEUI_SLOT(41) BEACON_INGAMEUI_SLOT(42) BEACON_INGAMEUI_SLOT(43)
	BEACON_INGAMEUI_SLOT(44) BEACON_INGAMEUI_SLOT(45) BEACON_INGAMEUI_SLOT(46) BEACON_INGAMEUI_SLOT(47)
	BEACON_INGAMEUI_SLOT(48) BEACON_INGAMEUI_SLOT(49) BEACON_INGAMEUI_SLOT(50) BEACON_INGAMEUI_SLOT(51)
	BEACON_INGAMEUI_SLOT(52) BEACON_INGAMEUI_SLOT(53) BEACON_INGAMEUI_SLOT(54) BEACON_INGAMEUI_SLOT(55)
	BEACON_INGAMEUI_SLOT(56)
	virtual void deselectDrawable( Drawable *draw ) = 0;		///< vtable +0xE4
};
#undef BEACON_INGAMEUI_SLOT

extern InGameUI *TheInGameUI;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	UnsignedInt getFrame( void ) { return m_frame; }

	unsigned char m_unmodelled_00[ 0x3C ];
	UnsignedInt m_frame;						// +0x3C
};

extern GameLogic *TheGameLogic;

// BFME keeps SECONDS_PER_LOGICFRAME_REAL as a writable float each TU reads
// from memory (see GameCommonConvertThunk.cpp); this TU's copy is retail
// 0x012B8EF0.
extern const Real g_012B8EF0;
#define SECONDS_PER_LOGICFRAME_REAL (g_012B8EF0)

class BeaconClientUpdateModuleData
{
public:
	unsigned char m_unmodelled_00[ 8 ];
	UnsignedInt m_framesBetweenRadarPulses;		// +0x08
	UnsignedInt m_radarPulseDuration;			// +0x0C
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Module/BeaconClientUpdate.h
class BeaconClientUpdate
{
public:
	virtual void clientUpdate( void );

protected:
	const BeaconClientUpdateModuleData *getBeaconClientUpdateModuleData() const { return m_moduleData; }
	Drawable *getDrawable() const { return m_drawable; }

	const BeaconClientUpdateModuleData *m_moduleData;	// +0x04
	Drawable *m_drawable;								// +0x08
	ParticleSystemID m_particleSystemID;				// +0x0C
	UnsignedInt m_lastRadarPulse;						// +0x10
};

/**
	Create the beacon's smoke in the owner's indicator colour, falling back to
	white when no template matches.

	@ai-generated
*/
static ParticleSystemHandle createParticleSystem( Drawable *draw )
{
	ParticleSystemHandle system;
	if (draw)
	{
		Object *obj = draw->getObject();
		if (obj)
		{
			AsciiString templateName;
			templateName.format( AsciiString( "BeaconSmoke%6.6X" ), (0xffffff & obj->getIndicatorColor()) );
			const ParticleSystemTemplate *particleTemplate = TheParticleSystemManager->findTemplate( templateName );
			if (particleTemplate)
			{
				system = TheParticleSystemManager->createParticleSystem( particleTemplate, TRUE );
				if (system)
				{
					Coord3D offset;
					offset.x = 0.0f;
					offset.y = 0.0f;
					offset.z = 3.0f;
					system->attachToDrawable( draw );
					system->setPosition( &offset );
				}
			}
			else
			{
				templateName.format( AsciiString( "BeaconSmokeFFFFFF" ) );
				const ParticleSystemTemplate *failsafeTemplate = TheParticleSystemManager->findTemplate( templateName );
				if (failsafeTemplate)
				{
					system = TheParticleSystemManager->createParticleSystem( failsafeTemplate, TRUE );
					if (system)
						system->attachToDrawable( draw );
				}
			}
		}
	}
	return system;
}

/**
	Keep the beacon's smoke alive and pulse the radar; a hidden beacon is made
	unselectable and sunk out of sight.

	@ai-generated
*/
// ?clientUpdate@BeaconClientUpdate@@UAEXXZ present-unmatched
void BeaconClientUpdate::clientUpdate( void )
{
	Drawable *draw = getDrawable();
	if (!draw)
		return;

	if (m_particleSystemID == INVALID_PARTICLE_SYSTEM_ID)
	{
		ParticleSystemHandle system = createParticleSystem( draw );
		if (system)
			m_particleSystemID = system->getSystemID();
	}

	if (!draw->isDrawableEffectivelyHidden())
	{
		const BeaconClientUpdateModuleData *moduleData = getBeaconClientUpdateModuleData();
		if (TheGameLogic->getFrame() > m_lastRadarPulse + moduleData->m_framesBetweenRadarPulses)
		{
			TheRadar->createEvent( draw->getPosition(), RADAR_EVENT_BEACON_PULSE,
				moduleData->m_radarPulseDuration * SECONDS_PER_LOGICFRAME_REAL );
			m_lastRadarPulse = TheGameLogic->getFrame();
		}
	}
	else
	{
		draw->setSelectable( FALSE );
		TheInGameUI->deselectDrawable( draw );
		draw->setPositionZ( -100.0f );
	}
}
