// cl: /DNDEBUG /MD /EHsc
// BFME-only ThingTemplate audio-event info getter at retail RVA 0x004172E0.

typedef int Int;
typedef long Long;

extern "C" __declspec(dllimport) Long __stdcall InterlockedIncrement(
	Long volatile *addend );

class AudioEventInfo
{
public:
	void *m_vtable;
	Long m_refCount;
};

class AudioEventInfoRef
{
public:
	AudioEventInfoRef( const AudioEventInfo *info );

	const AudioEventInfo *m_info;
};

inline AudioEventInfoRef::AudioEventInfoRef( const AudioEventInfo *info )
	: m_info( info )
{
	if ( m_info )
		InterlockedIncrement( &const_cast<AudioEventInfo *>( m_info )->m_refCount );
}

class AudioEventRTS
{
public:
	void *m_vtable;
	void *m_filenameToLoad;
	const AudioEventInfo *m_eventInfo;
};

extern AudioEventRTS BfmeTheEmptyAudioEvent;

class ThingTemplate
{
public:
	AudioEventInfoRef bfmeGetAudioEventInfo57() const;

private:
	const AudioEventRTS *bfmeLookupSound( Int index ) const;
};

AudioEventInfoRef ThingTemplate::bfmeGetAudioEventInfo57() const
{
	volatile Int constructionState = 0;

	const AudioEventRTS *sound = bfmeLookupSound( 0x57 );
	if ( !sound )
		sound = &BfmeTheEmptyAudioEvent;

	return AudioEventInfoRef( sound->m_eventInfo );
}
