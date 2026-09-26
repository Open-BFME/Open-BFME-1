// ?rva004175F0@ThingTemplate@@QBE?AVAudioEventInfoRef@@H@Z
// partial score=0.96 date=2026-09-25
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// ThingTemplate selector-driven audio-event info accessor at retail RVA 0x004175F0.
//
// Owner: `this` is handed unchanged to ThingTemplate's sound lookup (ILT 0x0000286A
// -> 0x00416F20) in both calls. The switch is the out-of-line member at 0x004172A0
// (slots 0x5B..0x5E) inlined; the first null fallback is getSound (0x00416FA0) inlined.
// Method name is address-derived: no caller, vtable slot, string or ZH twin names it.

#include "ascii_string.h"

typedef int Int;
typedef long Long;

extern "C" __declspec(dllimport) Long __stdcall InterlockedIncrement( Long volatile *addend );
extern "C" __declspec(dllimport) Long __stdcall InterlockedDecrement( Long volatile *addend );

// Retail's out-of-line StringBase<char>::isNotEmpty (0x0005E510) is `!isEmpty()` with
// isEmpty expanded, and the first path here tests the header inline: isEmpty is inline.
template <> inline bool StringBase<char>::isEmpty() const
{
	return m_data == 0 || m_data->length == 0;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventInfo.h
class AudioEventInfo
{
public:
	virtual ~AudioEventInfo();
	Long m_refCount;
};

class AudioEventInfoRef
{
public:
	AudioEventInfoRef() : m_info( 0 ) {}
	AudioEventInfoRef( const AudioEventInfoRef &other );
	~AudioEventInfoRef()
	{
		if ( m_info && InterlockedDecrement( &m_info->m_refCount ) <= 0 )
			delete m_info;
	}

	AudioEventInfo *m_info;
};

// Out-of-line instance is retail 0x000B97D0 (ILT 0x00036075).
inline AudioEventInfoRef::AudioEventInfoRef( const AudioEventInfoRef &other )
	: m_info( other.m_info )
{
	if ( m_info )
		InterlockedIncrement( &m_info->m_refCount );
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	virtual ~AudioEventRTS();
	AsciiString m_filenameToLoad;
	AudioEventInfoRef m_eventInfo;
	Int m_playingHandle;
	Int m_killThisHandle;
	AsciiString m_eventName;
};

extern AudioEventRTS BfmeTheEmptyAudioEvent;

struct Rva005A00B0AudioClient
{
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42();
	virtual void slotAC( const AudioEventRTS *event ) const;	// vtable +0xAC
};

extern Rva005A00B0AudioClient *TheAudioClientUpdate;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
public:
	const AudioEventRTS *getSound( Int index ) const
	{
		const AudioEventRTS *sound = bfmeLookupSound( index );
		if ( !sound )
			sound = &BfmeTheEmptyAudioEvent;
		return sound;
	}
	AudioEventInfoRef rva004175F0( Int selector ) const;

private:
	const AudioEventRTS *bfmeLookupSound( Int index ) const;	// ILT 0x0000286A
};

AudioEventInfoRef ThingTemplate::rva004175F0( Int selector ) const
{
	const AudioEventRTS *sound;
	switch ( selector )
	{
		case 1: sound = getSound( 0x5C ); break;
		case 2: sound = getSound( 0x5D ); break;
		case 3: sound = getSound( 0x5E ); break;
		default: sound = getSound( 0x5B ); break;
	}

	if ( !sound->m_eventName.isEmpty() )
	{
		if ( !sound->m_eventInfo.m_info )
			TheAudioClientUpdate->slotAC( sound );
		return sound->m_eventInfo;
	}

	if ( selector != 0 && selector != 3 )
	{
		const AudioEventRTS *fallback = bfmeLookupSound( 0x5B );
		sound = fallback ? fallback : &BfmeTheEmptyAudioEvent;
		if ( sound->m_eventName.isNotEmpty() )
		{
			if ( !sound->m_eventInfo.m_info )
				TheAudioClientUpdate->slotAC( sound );
			return sound->m_eventInfo;
		}
	}
	return AudioEventInfoRef();
}
