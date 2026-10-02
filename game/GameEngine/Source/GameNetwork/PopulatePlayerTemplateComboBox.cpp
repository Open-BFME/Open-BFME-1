// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// PopulatePlayerTemplateComboBox, retail 0x006247B0 (764 bytes); the symbol
// is pinned and InitLanGameGadgets, InitWOLGameGadgets and
// WOLGameSetupMenuSystem call it.  The Zero Hour GUIUtil.cpp body with the
// BFME init guard (the flag PopulateColorComboBox also tests), without the
// starting-building / old-faction / locked-general filters, and with the side
// label looked up once to test that it exists before it is added.

typedef unsigned short WideChar;
typedef bool Bool;
typedef int Int;
typedef int Color;

void __cdecl operator delete( void * ) throw();
#include <vector>
#include <set>

template <typename T> struct Rva006247B0StringData
{
	int m_refCount;
	int m_length;
	T m_text[ 1 ];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();
	Rva006247B0StringData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}

	void format( AsciiString format, ... );

	const char *str() const
	{
		return m_data ? m_data->m_text : "";
	}

	friend bool operator<( const AsciiString &left, const AsciiString &right );
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString( const UnicodeString &other ) : StringBase<WideChar>( other ) {}
	~UnicodeString() {}
};

class GameWindow;
class GameInfo;

class GameTextInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual UnicodeString fetch( const char *label, Bool *exists = 0 ) = 0;
	virtual UnicodeString fetch( AsciiString label, Bool *exists = 0 ) = 0;
};

class MultiplayerColorDefinition
{
public:
	Color getColor() const { return m_color; }

private:
	char m_unmodelled[ 0x10 ];
	Color m_color;
};

class MultiplayerSettings
{
public:
	MultiplayerColorDefinition *getColor( Int which );
};

enum
{
	PLAYERTEMPLATE_RANDOM = -1,
	PLAYERTEMPLATE_OBSERVER = -2
};

class PlayerTemplate
{
public:
	const AsciiString &getSide() const { return m_side; }

private:
	char m_unmodelled[ 0x08 ];
	AsciiString m_side;
	char m_rest[ 0x124 - 0x0c ];
};

class PlayerTemplateStore
{
public:
	Int getPlayerTemplateCount() const { return m_playerTemplates.size(); }
	const PlayerTemplate *getNthPlayerTemplate( Int i ) const;

private:
	char m_unmodelled[ 0x08 ];
	_STL::vector<PlayerTemplate> m_playerTemplates;
};

extern GameTextInterface *TheGameText;
extern MultiplayerSettings *TheMultiplayerSettings;
extern PlayerTemplateStore *ThePlayerTemplateStore;
class SkirmishScreenState;
extern SkirmishScreenState *TheSkirmishScreenState;

extern void GadgetComboBoxReset( GameWindow *comboBox );
extern Int GadgetComboBoxAddEntry( GameWindow *comboBox, UnicodeString text, Color color );
extern void GadgetComboBoxSetItemData( GameWindow *comboBox, Int item, void *data );
extern void GadgetComboBoxSetSelectedPos( GameWindow *comboBox, Int item, Bool dontHide = false );

// ?PopulatePlayerTemplateComboBox@@YAXHQAPAVGameWindow@@PAVGameInfo@@_N@Z
void PopulatePlayerTemplateComboBox( Int comboBox, GameWindow *comboArray[],
	GameInfo *myGame, Bool allowObservers )
{
	if( TheSkirmishScreenState )
		return;

	Int numPlayerTemplates = ThePlayerTemplateStore->getPlayerTemplateCount();
	UnicodeString playerTemplateName;

	GadgetComboBoxReset( comboArray[ comboBox ] );

	MultiplayerColorDefinition *def = TheMultiplayerSettings->getColor( PLAYERTEMPLATE_RANDOM );
	Int newIndex = GadgetComboBoxAddEntry( comboArray[ comboBox ],
		TheGameText->fetch( "GUI:Random" ), def->getColor() );
	GadgetComboBoxSetItemData( comboArray[ comboBox ], newIndex, (void *)PLAYERTEMPLATE_RANDOM );

	_STL::set<AsciiString> seenSides;

	for( Int c = 0; c < numPlayerTemplates; ++c )
	{
		const PlayerTemplate *fac = ThePlayerTemplateStore->getNthPlayerTemplate( c );
		if( !fac )
			continue;

		AsciiString side;
		side.format( AsciiString( "SIDE:%s" ), fac->getSide().str() );
		_STL::set<AsciiString>::iterator found = seenSides.find( side );
		if( found != seenSides.end() )
			continue;

		seenSides.insert( side );

		Bool exists;
		UnicodeString sideName = TheGameText->fetch( side, &exists );
		if( !exists )
			continue;

		newIndex = GadgetComboBoxAddEntry( comboArray[ comboBox ],
			TheGameText->fetch( side ), def->getColor() );
		GadgetComboBoxSetItemData( comboArray[ comboBox ], newIndex, (void *)c );
	}
	seenSides.clear();

	if( allowObservers )
	{
		def = TheMultiplayerSettings->getColor( PLAYERTEMPLATE_OBSERVER );
		newIndex = GadgetComboBoxAddEntry( comboArray[ comboBox ],
			TheGameText->fetch( "GUI:Observer" ), def->getColor() );
		GadgetComboBoxSetItemData( comboArray[ comboBox ], newIndex, (void *)PLAYERTEMPLATE_OBSERVER );
	}
	GadgetComboBoxSetSelectedPos( comboArray[ comboBox ], 0 );
}
