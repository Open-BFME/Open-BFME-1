// ?refreshAmbientSound@Drawable@@AAEXXZ
// partial score=0.89 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// BFME Drawable selected-ambient refresh, retail 0x0041AE50.

typedef unsigned int UnsignedInt;

class AsciiString
{
};

class Rva000B97D0Ptr
{
public:
	Rva000B97D0Ptr( const Rva000B97D0Ptr &other );
	~Rva000B97D0Ptr();
	Rva000B97D0Ptr &operator=( const Rva000B97D0Ptr &other );
	void *m_ptr;
};

#pragma comment(linker, "/alternatename:??0Rva000B97D0Ptr@@QAE@ABV0@@Z=?j_00036075@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva000B97D0Ptr@@QAE@XZ=?j_000362ff@@YAXXZ")
#pragma comment(linker, "/alternatename:??4Rva000B97D0Ptr@@QAEAAV0@ABV0@@Z=?j_0002c6d8@@YAXXZ")

class __declspec(novtable) AudioEventRTS
{
public:
	AudioEventRTS() {}
	virtual ~AudioEventRTS();
	bool isCurrentlyPlaying() const;
	AudioEventRTS &assign( const AudioEventRTS &other );
	void setObjectID( UnsignedInt id );
	void setPlayingHandle( UnsignedInt handle );
	Rva000B97D0Ptr &eventInfo()
	{
		return *reinterpret_cast<Rva000B97D0Ptr *>( m_data + 4 );
	}

	char m_data[0x6c];
};

#pragma comment(linker, "/alternatename:?isCurrentlyPlaying@AudioEventRTS@@QBE_NXZ=?j_00035a5d@@YAXXZ")
#pragma comment(linker, "/alternatename:?assign@AudioEventRTS@@QAEAAV1@ABV1@@Z=?j_0001f753@@YAXXZ")
#pragma comment(linker, "/alternatename:?setObjectID@AudioEventRTS@@QAEXI@Z=?j_00011428@@YAXXZ")
#pragma comment(linker, "/alternatename:?setPlayingHandle@AudioEventRTS@@QAEXI@Z=?j_00040a52@@YAXXZ")

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

#pragma comment(linker, "/alternatename:?lookup@Rva00417200@@QAEPAVAudioEventRTS@@XZ=?j_000339b5@@YAXXZ")

class ThingTemplate
{
public:
	AudioEventRTS *lookupSound( int index ) const;
};

#pragma comment(linker, "/alternatename:?lookupSound@ThingTemplate@@QBEPAVAudioEventRTS@@H@Z=?j_0000286a@@YAXXZ")

class DynamicAudioEventRTS
{
public:
	DynamicAudioEventRTS() throw();
	AudioEventRTS &event()
	{
		return *reinterpret_cast<AudioEventRTS *>( m_data + 4 );
	}
	unsigned char m_data[0x74];
};

#pragma comment(linker, "/alternatename:??0DynamicAudioEventRTS@@QAE@XZ=?j_00040d18@@YAXXZ")


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
	virtual UnsignedInt addAudioEvent( AudioEventRTS *event );
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
	virtual void getAudioEventInfo( AudioEventRTS *event );
#undef CLIENT_SUBSYSTEM_SLOT
};

extern ClientSubsystem *TheAudioClientUpdate;

class Drawable
{
private:
	void refreshAmbientSound();

	unsigned char m_bfmeHead[0x140];
	unsigned char m_ambientSoundEnabled;
	unsigned char m_ambientSoundEnabledFromScript;
	unsigned char m_bfmeGap142;
	unsigned char m_selected;
	DynamicAudioEventRTS *m_ambientSound;
	DynamicAudioEventRTS *m_damagedAmbientSound;
	DynamicAudioEventRTS *m_selectedAmbientSound;
	unsigned char m_bfmeGap150[0x100];
	unsigned int m_conditionState[10];
};

void Drawable::refreshAmbientSound()
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
		DynamicAudioEventRTS *created = new DynamicAudioEventRTS;
		m_selectedAmbientSound = created;
	}

	m_selectedAmbientSound->event().assign( *selected );
	Rva000B97D0Ptr eventInfo( m_selectedAmbientSound->event().eventInfo() );

	if ( eventInfo.m_ptr == 0 )
	{
		TheAudioClientUpdate->getAudioEventInfo( &m_selectedAmbientSound->event() );
		eventInfo = m_selectedAmbientSound->event().eventInfo();
	}

	if ( eventInfo.m_ptr != 0 )
	{
		m_selectedAmbientSound->event().setObjectID( *(const UnsignedInt *)(
			reinterpret_cast<const unsigned char *>( this ) + 0x100 ) );
		m_selectedAmbientSound->event().setPlayingHandle(
			TheAudioClientUpdate->addAudioEvent( &m_selectedAmbientSound->event() ) );
	}
}
