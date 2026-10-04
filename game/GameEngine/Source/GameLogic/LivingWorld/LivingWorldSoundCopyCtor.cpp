// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/campaignmanagerascii /Igame/Libraries/Source/WWVegas/WWLib

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

struct Coord3D
{
	float x;
	float y;
	float z;
};

class SoundEventReferent
{
public:
	char m_padding[ 0x84 ];
	unsigned int m_playingHandle;
	unsigned int getPlayingHandle() const { return m_playingHandle; }
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

	SoundEventReferent *m_sound;
};

class LwsAudioEventRTS
{
private:
	char m_storage[ 0x70 ];
};

class AudioManager
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot0a() = 0;
	virtual void slot0b() = 0;
	virtual void slot0c() = 0;
	virtual void slot0d() = 0;
	virtual void slot0e() = 0;
	virtual void slot0f() = 0;
	virtual void slot10() = 0;
	virtual unsigned int addAudioEvent( const LwsAudioEventRTS *event ) = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot1a() = 0;
	virtual void startAudio( int one, int two, int three ) = 0;
};

class BfmeSwitchDR
{
public:
	int m_bfmeHead[ 7 ];
	bool m_bfmeUseHigh;
};

extern AudioManager *TheAudio;

// The retail global at 0x012F1024 is EA's
// `LivingWorldCampaignManager *TheLivingWorldCampaignManager`, defined once in
// game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldCampaignManager.cpp;
// BfmeSwitchDR above is this TU's view of the object, cast at each use.
class LivingWorldCampaignManager;

extern LivingWorldCampaignManager *TheLivingWorldCampaignManager;

static inline const BfmeSwitchDR *livingWorldCampaignManagerSwitchView()
{
	return (const BfmeSwitchDR *)TheLivingWorldCampaignManager;
}

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

extern void j_000113c4();
extern void j_00026f35();
extern void j_0002c5cf();

// TU-local scope object standing in for a local LwsAudioEventRTS. Its inline
// ctor/dtor/method bodies call the retail ILT thunks through member-function
// pointers so no link-time alias is needed; the object needs a real destructor
// so the compiler keeps the unwind frame retail emits for this function.
class LwsAudioEventRTSScope
{
public:
	typedef void ( LwsAudioEventRTS::*Ctor )( const AsciiString &, const Coord3D *, int );
	typedef void ( LwsAudioEventRTS::*Dtor )();
	typedef void ( LwsAudioEventRTS::*SetIsLogicalAudio )( bool );

	__forceinline LwsAudioEventRTSScope( const AsciiString &eventName,
		const Coord3D *position, int extra )
	{
		union { void ( *fn )(); Ctor call; } ctor = { j_000113c4 };
		( reinterpret_cast<LwsAudioEventRTS *>( this )->*ctor.call )( eventName, position, extra );
	}

	__forceinline ~LwsAudioEventRTSScope()
	{
		union { void ( *fn )(); Dtor call; } dtor = { j_00026f35 };
		( reinterpret_cast<LwsAudioEventRTS *>( this )->*dtor.call )();
	}

	__forceinline void setIsLogicalAudio( bool logical )
	{
		union { void ( *fn )(); SetIsLogicalAudio call; } setLogical = { j_0002c5cf };
		( reinterpret_cast<LwsAudioEventRTS *>( this )->*setLogical.call )( logical );
	}

private:
	char m_storage[ 0x70 ];
};

// ?Rva0061C060@LivingWorldSound@@QAEXXZ
// Reactivates a copied LivingWorldSound when its sound is still eligible.
void LivingWorldSound::Rva0061C060()
{
	if ( (unsigned int)m_playState >= 5 )
		return;

	SoundEvent *soundEvent = &m_sound;

	if ( soundEvent->m_sound == 0 )
		return;

	if ( TheAudio == 0 )
		return;

	if ( m_flags & 0x80 )
	{
		if ( livingWorldCampaignManagerSwitchView()->m_bfmeUseHigh )
			return;
	}
	else if ( ( m_flags & 0x100 ) != 0 && !livingWorldCampaignManagerSwitchView()->m_bfmeUseHigh )
	{
		return;
	}

	if ( soundEvent->m_sound->getPlayingHandle() != 0 )
	{
	}
	else
		TheAudio->startAudio( 1, 1, 0 );

	LwsAudioEventRTSScope sound( reinterpret_cast<const AsciiString &>( *soundEvent ),
		reinterpret_cast<const Coord3D *>( &m_position ), 1 );
	if ( m_flags & 0x40 )
		sound.setIsLogicalAudio( true );
	m_playState = TheAudio->addAudioEvent( (const LwsAudioEventRTS *)&sound );
	m_shouldFade = true;
}

// ??0LivingWorldSound@@QAE@ABV0@@Z
// Field-by-field copy preserves the retail snapshot layout.
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
