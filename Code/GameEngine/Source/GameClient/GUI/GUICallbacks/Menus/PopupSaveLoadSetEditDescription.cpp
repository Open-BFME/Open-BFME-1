// cl: /DNDEBUG /MD /EHsc
// Open-BFME: setEditDescription, retail 0x004DFB40, 361 bytes.
// Converted from gen-dump d_004dfb40. ZH twin is static in PopupSaveLoad.cpp;
// that TU already owns SaveLoadMenu* rows, so this lives here. BFME drops the
// four-char extension strip and reads m_mapName from TheWritableGlobalData+8.

typedef int Int;
typedef bool Bool;
typedef unsigned short WideChar;

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	struct Header
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		T m_text[1];
	};

	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void set( const StringBase<T> &other );

	Header *m_data;
};

class UnicodeString;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}

	const char *str() const
	{
		return m_data ? m_data->m_text : (const char *)0x0107388B;
	}

	const char *reverseFind( char c ) const
	{
		const char *start = m_data ? m_data->m_text : (const char *)0x0107388B;
		const char *p = start + ( m_data ? m_data->m_length : 0 );
		while ( p != start )
		{
			--p;
			if ( *p == c )
				return p;
		}
		return 0;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString( const WideChar *text ) : StringBase<WideChar>( text ) {}
	UnicodeString( const UnicodeString &other ) : StringBase<WideChar>( other ) {}
	~UnicodeString() {}

	const WideChar *str() const
	{
		return m_data ? m_data->m_text : (const WideChar *)0x0107388C;
	}

	void __cdecl format( UnicodeString fmt, ... );
};

class GameWindow;

void GadgetTextEntrySetText( GameWindow *editControl, UnicodeString text );

class GameTextInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual UnicodeString fetch( AsciiString label, Bool *exists = 0 );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/CampaignManager.h
class Campaign
{
public:
	char m_pad[ 0xC ];
	AsciiString m_campaignNameLabel;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/CampaignManager.h
class CampaignManager
{
public:
	Campaign *getCurrentCampaign();
	Int getCurrentMissionNumber();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	char m_pad[ 8 ];
	AsciiString m_mapName;
};

extern GameTextInterface *TheGameText;
extern CampaignManager *TheCampaignManager;
extern GlobalData *TheWritableGlobalData;

// ?setEditDescription@@YAXPAVGameWindow@@@Z
void setEditDescription( GameWindow *editControl )
{
	UnicodeString defaultDesc;
	Campaign *campaign = TheCampaignManager->getCurrentCampaign();

	if ( campaign )
		defaultDesc.format( UnicodeString( L"%s %d" ),
			TheGameText->fetch( campaign->m_campaignNameLabel ).str(),
			TheCampaignManager->getCurrentMissionNumber() + 1 );
	else
	{
		const char *mapName = TheWritableGlobalData->m_mapName.reverseFind( '\\' );

		if ( mapName )
			defaultDesc.format( UnicodeString( L"%S" ), mapName + 1 );
		else
			defaultDesc.format( UnicodeString( L"%S" ), TheWritableGlobalData->m_mapName.str() );
	}

	GadgetTextEntrySetText( editControl, defaultDesc );
}
