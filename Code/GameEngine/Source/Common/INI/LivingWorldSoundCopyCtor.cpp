// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/campaignmanagerascii /ICode/Libraries/Source/WWVegas/WWLib

#include "Common/AsciiString.h"

class Xfer;

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement( long volatile *addend );
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement( long volatile *addend );

struct Coord3DBase
{
	Coord3DBase() {}
	Coord3DBase( const Coord3DBase &that ) : x( that.x ), y( that.y ), z( that.z ) {}

	float x;
	float y;
	float z;
};

struct Region2DBase
{
	float xMin;
	float yMin;
	float xMax;
	float yMax;
};

class SoundEvent
{
public:
	SoundEvent() : m_sound( 0 ) {}
	SoundEvent( const SoundEvent &that ) : m_sound( that.m_sound )
	{
		if ( m_sound != 0 )
			InterlockedIncrement( (long volatile *)( (char *)m_sound + 4 ) );
	}
	~SoundEvent()
	{
		if ( m_sound != 0 )
			InterlockedDecrement( (long volatile *)( (char *)m_sound + 4 ) );
	}

	void *m_sound;
};

class Snapshot
{
public:
	virtual ~Snapshot() {}
	virtual void LoadPostProcess() = 0;
	virtual const char *GetSnapshotName() = 0;
	virtual void DoXfer( Xfer &xfer ) = 0;
};

class LivingWorldSound : public Snapshot
{
public:
	LivingWorldSound( const LivingWorldSound &that );
	virtual ~LivingWorldSound();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer( Xfer &xfer );
	void Rva0061C060();

private:
	AsciiString m_name;
	Coord3DBase m_position;
	SoundEvent m_sound;
	unsigned int m_flags;
	Region2DBase m_zoomRegion;
	int m_playState;
	bool m_shouldFade;
	bool m_isPlaying;
	bool m_hasPlayed;
};

#pragma comment(linker, "/alternatename:?Rva0061C060@LivingWorldSound@@QAEXXZ=?j_00002c2a@@YAXXZ")

// ??0LivingWorldSound@@QAE@ABV0@@Z
// field-by-field copy preserves the retail snapshot layout.
LivingWorldSound::LivingWorldSound( const LivingWorldSound &that ) :
	m_name( that.m_name ),
	m_position( that.m_position ),
	m_sound( that.m_sound )
{
	m_flags = that.m_flags;
	m_zoomRegion.xMin = that.m_zoomRegion.xMin;
	m_zoomRegion.yMin = that.m_zoomRegion.yMin;
	m_zoomRegion.xMax = that.m_zoomRegion.xMax;
	m_zoomRegion.yMax = that.m_zoomRegion.yMax;
	m_playState = 1;
	m_shouldFade = that.m_shouldFade;
	m_isPlaying = that.m_isPlaying;
	m_hasPlayed = that.m_hasPlayed;
	if ( (unsigned int)that.m_playState >= 5 && m_sound.m_sound != 0 )
		Rva0061C060();
}
