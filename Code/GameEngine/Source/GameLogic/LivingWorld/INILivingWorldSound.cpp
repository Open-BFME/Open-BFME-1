// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/campaignmanagerascii /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#include "Common/AsciiString.h"

class Xfer;

struct Coord3DBase
{
	Coord3DBase() : x( 0.0f ), y( 0.0f ), z( 0.0f ) {}

	float x;
	float y;
	float z;
};

struct Region2DBase
{
	Region2DBase( const Region2DBase &that ) :
		xMin( that.xMin ),
		yMin( that.yMin ),
		xMax( that.xMax ),
		yMax( that.yMax )
	{
	}

	float xMin;
	float yMin;
	float xMax;
	float yMax;
};

extern const Region2DBase TheInvalidRegion;

struct LivingWorldSoundEvent
{
	explicit LivingWorldSoundEvent( int initial ) : value( initial ) {}

	int value;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot() {}
	virtual void LoadPostProcess() = 0;
	virtual const char *GetSnapshotName() = 0;
	virtual void DoXfer( Xfer &xfer ) = 0;
};

class LivingWorldSound : public Snapshot
{
public:
	LivingWorldSound( const AsciiString &name );
	virtual ~LivingWorldSound();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName() { return "LivingWorldSound"; }
	virtual void DoXfer( Xfer &xfer );

private:
	AsciiString m_name;
	Coord3DBase m_position;
	LivingWorldSoundEvent m_sound;
	unsigned int m_flags;
	Region2DBase m_zoomRegion;
	int m_playState;
	bool m_shouldFade;
	bool m_isPlaying;
	bool m_hasPlayed;
};

LivingWorldSound::LivingWorldSound( const AsciiString &name ) :
	m_name( name ),
	m_position(),
	m_sound( 0 ),
	m_flags( 0 ),
	m_zoomRegion( TheInvalidRegion ),
	m_shouldFade( false ),
	m_isPlaying( false ),
	m_hasPlayed( false )
{
	m_flags = 0;
	m_playState = 1;
}
