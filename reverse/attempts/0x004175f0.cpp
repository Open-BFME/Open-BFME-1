// ?bfmeGetAudioEventInfoForSelector@ThingTemplate@@QBE?AVAudioEventInfoRef@@H@Z
// partial score=0.93 date=2026-09-08
// cl: /DNDEBUG /MD /EHsc
// BFME ThingTemplate audio-event info selector at retail RVA 0x004175F0.

typedef bool Bool;
typedef int Int;
typedef long Long;
typedef short Short;

extern "C" __declspec(dllimport) Long __stdcall InterlockedIncrement(
	Long volatile *addend );

class AsciiString
{
public:
	Bool isNotEmpty() const;

	struct Data
	{
		Long m_unused;
		Short m_length;
	};

	Data *m_data;
};

class AudioEventInfo
{
public:
	void *m_vtable;
	Long m_refCount;
};

class AudioEventInfoRef
{
public:
	AudioEventInfoRef() : m_info( 0 ) {}
	AudioEventInfoRef( const AudioEventInfo *info );
	AudioEventInfoRef( const AudioEventInfoRef &other );

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
	AsciiString m_filenameToLoad;
	const AudioEventInfo *m_eventInfo;
	Int m_playingHandle;
	Int m_killThisHandle;
	AsciiString m_eventName;
};

extern AudioEventRTS BfmeTheEmptyAudioEvent;

class ClientSubsystem
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0;
	virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual void slot26() = 0; virtual void slot27() = 0;
	virtual void slot28() = 0; virtual void slot29() = 0;
	virtual void slot30() = 0; virtual void slot31() = 0;
	virtual void slot32() = 0; virtual void slot33() = 0;
	virtual void slot34() = 0; virtual void slot35() = 0;
	virtual void slot36() = 0; virtual void slot37() = 0;
	virtual void slot38() = 0; virtual void slot39() = 0;
	virtual void slot40() = 0; virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void loadAudioEventInfo( const AudioEventRTS *event ) = 0;
};

extern ClientSubsystem *TheAudioClientUpdate;

class ThingTemplate
{
public:
	AudioEventInfoRef bfmeGetAudioEventInfoForSelector( Int selector ) const;


private:
	__declspec( nothrow ) AudioEventRTS *bfmeLookupSound( Int index ) const;

};

AudioEventInfoRef ThingTemplate::bfmeGetAudioEventInfoForSelector( Int selector ) const
{
	volatile Int constructionState = 0;
	const ThingTemplate *owner = this;
	const AudioEventRTS *sound;

	switch ( selector )
	{
		case 1: sound = bfmeLookupSound( 0x5C ); break;
		case 2: sound = bfmeLookupSound( 0x5D ); break;
		case 3: sound = bfmeLookupSound( 0x5E ); break;
		default: sound = bfmeLookupSound( 0x5B ); break;
	}

	if ( !sound )
		sound = &BfmeTheEmptyAudioEvent;

	if ( sound->m_eventName.m_data && sound->m_eventName.m_data->m_length != 0 )
	{
		if ( !sound->m_eventInfo )
			TheAudioClientUpdate->loadAudioEventInfo( sound );
		return AudioEventInfoRef( sound->m_eventInfo );
	}

	if ( selector == 0 || selector == 3 )
		return AudioEventInfoRef();

	sound = owner->bfmeLookupSound( 0x5B );
	if ( !sound )
		sound = &BfmeTheEmptyAudioEvent;

	if ( !sound->m_eventName.isNotEmpty() )
		return AudioEventInfoRef();

	if ( !sound->m_eventInfo )
		TheAudioClientUpdate->loadAudioEventInfo( sound );
	return *(const AudioEventInfoRef *)&sound->m_eventInfo;
}
