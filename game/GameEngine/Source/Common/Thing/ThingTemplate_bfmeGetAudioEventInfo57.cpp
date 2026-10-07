// cl: /DNDEBUG /MD /EHsc
// BFME-only ThingTemplate audio-event info getter at retail RVA 0x004172E0.

typedef int Int;
typedef long Long;

extern "C" __declspec(dllimport) Long __stdcall InterlockedIncrement(
	Long volatile *addend );

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventInfo.h
class AudioEventInfo
{
public:
	void *m_vtable;
	Long m_refCount;
};

class AudioEventInfoRef
{
public:
	AudioEventInfoRef( const AudioEventInfo *info )
		: m_info( info )
	{
		if ( m_info )
			InterlockedIncrement( &const_cast<AudioEventInfo *>( m_info )->m_refCount );
	}

	const AudioEventInfo *m_info;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	void *m_vtable;
	void *m_filenameToLoad;
	const AudioEventInfo *m_eventInfo;
};

extern AudioEventRTS BfmeTheEmptyAudioEvent;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
public:
	AudioEventInfoRef bfmeGetAudioEventInfo57() const;

	// Retail calls ILT 0x0000286A -> the matched getPerUnitFx at 0x00416F20.
	void *getPerUnitFx( Int index ) const;
};

AudioEventInfoRef ThingTemplate::bfmeGetAudioEventInfo57() const
{
	volatile Int constructionState = 0;

	const AudioEventRTS *sound = (const AudioEventRTS *)getPerUnitFx( 0x57 );
	if ( !sound )
		sound = &BfmeTheEmptyAudioEvent;

	return AudioEventInfoRef( sound->m_eventInfo );
}
