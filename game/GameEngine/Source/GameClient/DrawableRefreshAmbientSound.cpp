// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Selected ambient refresh with retail ABI views.
// Evidence: targets/game/reverse/identity_evidence/0x0041ae50-refresh-ambient.md

typedef unsigned int UnsignedInt;
enum DrawableID { INVALID_DRAWABLE_ID = 0 };

#include "ascii_string.h"

class Rva000B97D0Ptr
{
public:
	Rva000B97D0Ptr( const Rva000B97D0Ptr &other );
	~Rva000B97D0Ptr();
	Rva000B97D0Ptr &operator=( const Rva000B97D0Ptr &other );
	void *m_ptr;
};

class __declspec(novtable) AudioEventRTS
{
public:
	AudioEventRTS();
	virtual ~AudioEventRTS();
	bool isCurrentlyPlaying() const;
	AudioEventRTS &assign( const AudioEventRTS &other );
	void setObjectID( UnsignedInt id );
	void setDrawableID(DrawableID id);
	void setPlayingHandle( UnsignedInt handle );
	// ?eventInfo@AudioEventRTS@@QAEAAVRva000B97D0Ptr@@XZ absent-from-retail
	Rva000B97D0Ptr &eventInfo()
	{
		return *reinterpret_cast<Rva000B97D0Ptr *>( m_data + 4 );
	}

	char m_data[0x6c];
};

class BfmeSubBTB
{
public:
	void bfmeSetBTB( void *one, void *two );
};

class BfmeThingBTB
{
public:
	BfmeThingBTB *bfmeInitBTB( void *one, void *two );
	void *m_bfmeVft;
	BfmeSubBTB m_bfmeSub;
};

class Rva00417200
{
public:
	AudioEventRTS *lookup();
};

class ThingTemplate
{
public:
	void *getPerUnitFx(int index) const;
	// ?lookupSound@ThingTemplate@@QBEPAVAudioEventRTS@@H@Z absent-from-retail
	AudioEventRTS *lookupSound(int index) const { return static_cast<AudioEventRTS *>(getPerUnitFx(index)); }
};

class DynamicAudioEventRTS000B9A70
{
public:
	DynamicAudioEventRTS000B9A70(const AsciiString &name, int timeOfDay);
	// ?event@DynamicAudioEventRTS000B9A70@@QAEAAVAudioEventRTS@@XZ absent-from-retail
	AudioEventRTS &event()
	{
		return *reinterpret_cast<AudioEventRTS *>( m_data + 4 );
	}
	unsigned char m_data[0x74];
};

class ClientSubsystem
{
public:
#define CLIENT_SUBSYSTEM_SLOT(number) virtual void slot##number();
	CLIENT_SUBSYSTEM_SLOT(00) CLIENT_SUBSYSTEM_SLOT(01)
	CLIENT_SUBSYSTEM_SLOT(02) CLIENT_SUBSYSTEM_SLOT(03)
	CLIENT_SUBSYSTEM_SLOT(04) CLIENT_SUBSYSTEM_SLOT(05)
	CLIENT_SUBSYSTEM_SLOT(06) CLIENT_SUBSYSTEM_SLOT(07)
	CLIENT_SUBSYSTEM_SLOT(08) CLIENT_SUBSYSTEM_SLOT(09)
	CLIENT_SUBSYSTEM_SLOT(10) CLIENT_SUBSYSTEM_SLOT(11)
	CLIENT_SUBSYSTEM_SLOT(12) CLIENT_SUBSYSTEM_SLOT(13)
	CLIENT_SUBSYSTEM_SLOT(14) CLIENT_SUBSYSTEM_SLOT(15)
	CLIENT_SUBSYSTEM_SLOT(16)
	virtual UnsignedInt addAudioEvent( const AudioEventRTS *event );
	CLIENT_SUBSYSTEM_SLOT(18) CLIENT_SUBSYSTEM_SLOT(19)
	CLIENT_SUBSYSTEM_SLOT(20) CLIENT_SUBSYSTEM_SLOT(21)
	CLIENT_SUBSYSTEM_SLOT(22) CLIENT_SUBSYSTEM_SLOT(23)
	CLIENT_SUBSYSTEM_SLOT(24) CLIENT_SUBSYSTEM_SLOT(25)
	CLIENT_SUBSYSTEM_SLOT(26) CLIENT_SUBSYSTEM_SLOT(27)
	CLIENT_SUBSYSTEM_SLOT(28) CLIENT_SUBSYSTEM_SLOT(29)
	CLIENT_SUBSYSTEM_SLOT(30) CLIENT_SUBSYSTEM_SLOT(31)
	CLIENT_SUBSYSTEM_SLOT(32) CLIENT_SUBSYSTEM_SLOT(33)
	CLIENT_SUBSYSTEM_SLOT(34) CLIENT_SUBSYSTEM_SLOT(35)
	CLIENT_SUBSYSTEM_SLOT(36) CLIENT_SUBSYSTEM_SLOT(37)
	CLIENT_SUBSYSTEM_SLOT(38) CLIENT_SUBSYSTEM_SLOT(39)
	CLIENT_SUBSYSTEM_SLOT(40) CLIENT_SUBSYSTEM_SLOT(41)
	CLIENT_SUBSYSTEM_SLOT(42)
	virtual void getAudioEventInfo( const AudioEventRTS *event ) const;
#undef CLIENT_SUBSYSTEM_SLOT
};

// Retail 0x012ED668 is ?TheAudio@@3PAVAudioManager@@A (data_rows.csv,
// Common/Audio/GameAudio.cpp); TheAudioClientUpdate was only a pin.
class AudioManager;
extern AudioManager *TheAudio;
#define TheAudioClientUpdate ( *(ClientSubsystem **)&TheAudio )

class Drawable
{
public:
	DrawableID getID() const { return *(const DrawableID *)(reinterpret_cast<const unsigned char *>(this) + 0x100); }

private:
	void refreshAmbientSound0041AE50();

	unsigned char m_bfmeHead[0x140];
	unsigned char m_ambientSoundEnabled;
	unsigned char m_ambientSoundEnabledFromScript;
	unsigned char m_bfmeGap142;
	unsigned char m_selected;
	DynamicAudioEventRTS000B9A70 *m_ambientSound;
	DynamicAudioEventRTS000B9A70 *m_damagedAmbientSound;
	DynamicAudioEventRTS000B9A70 *m_selectedAmbientSound;
	unsigned char m_bfmeGap150[0x100];
	unsigned int m_conditionState[10];
};

// ?refreshAmbientSound0041AE50@Drawable@@AAEXXZ
void Drawable::refreshAmbientSound0041AE50()
{
	if ( !m_bfmeGap142 || !m_ambientSoundEnabledFromScript || !m_selected ||
		(m_conditionState[4] & 0x80000) == 0 )
		return;

	if ( m_selectedAmbientSound && m_selectedAmbientSound->event().isCurrentlyPlaying() )
		return;

	AudioEventRTS *sound = reinterpret_cast<const ThingTemplate *>( this )->lookupSound( 0x5f );
	if ( !sound )
		return;

	AudioEventRTS *selected = reinterpret_cast<Rva00417200 *>( this )->lookup();
	if ( m_selectedAmbientSound == 0 )
	{
		DynamicAudioEventRTS000B9A70 *created = new DynamicAudioEventRTS000B9A70(AsciiString::TheEmptyString, 0);
		m_selectedAmbientSound = created;
	}

	m_selectedAmbientSound->event().assign( *selected );
	{
		Rva000B97D0Ptr eventInfo( m_selectedAmbientSound->event().eventInfo() );

		if ( eventInfo.m_ptr == 0 )
		{
			TheAudioClientUpdate->getAudioEventInfo( &m_selectedAmbientSound->event() );
			eventInfo = m_selectedAmbientSound->event().eventInfo();
		}

		if ( eventInfo.m_ptr != 0 )
		{
			m_selectedAmbientSound->event().setDrawableID( getID() );
			UnsignedInt handle = TheAudioClientUpdate->addAudioEvent( &m_selectedAmbientSound->event() );
			m_selectedAmbientSound->event().setPlayingHandle(handle);
		}
	}
}
