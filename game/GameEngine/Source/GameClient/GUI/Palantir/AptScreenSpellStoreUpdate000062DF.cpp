// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeAptScreenSpellStore::unidentified_000062DF, retail 0x005996F0, 441 bytes.
// AptScreenFactories.cpp calls this body after registering the SpellStore
// callbacks. The 0x000062DF thunk names the final SpellStore update method.
// For each of the twelve windows in the ControlBar array at +0x9C that is
// present, visible and carries button data, the pair at +0x260 records the
// window, the current value is published as SpellStore/Buttons/Spell%d, and
// the first science's purchase cost as APT:Spell%dCost.  Written as a plain
// indexed loop: MSVC strength-reduces the index into the byte offset, spell
// number, pair pointer and countdown retail keeps.

template <typename T> struct StringData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_max;
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

	StringData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	void format( AsciiString format, ... );
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const unsigned short *text )
		: StringBase<unsigned short>( text ) {}
	UnicodeString( const UnicodeString &other )
		: StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
	void format( UnicodeString format, ... );
};

class GameWindow
{
public:
	bool winIsHidden();
};

extern void *GadgetButtonGetData( GameWindow *button );

class ControlBar
{
public:
	char m_unmodelled[ 0x9C ];
	GameWindow *m_windows09C[ 12 ];
};

extern ControlBar *TheControlBar;

class Gen_0049AFE0
{
public:
	int bfmeCurrent() const;
};

enum ScienceType
{
	SCIENCE_INVALID = -1
};

class SpellScienceVector
{
public:
	ScienceType *begin() const { return m_start; }
	unsigned int size() const
	{
		return (unsigned int)( m_finish - m_start );
	}

private:
	ScienceType *m_start;
	ScienceType *m_finish;
	ScienceType *m_end;
};

class SpellButtonData
{
private:
	char m_unmodelled[ 0x84 ];
	SpellScienceVector m_science;

public:
	const SpellScienceVector &getScienceVec() const { return m_science; }
};

class ScienceStore
{
public:
	int getSciencePurchaseCost( ScienceType science ) const;
};

extern ScienceStore *TheScienceStore;

// The window manager's name -> value store (matched at 0x0046C770 under the
// BfmeThingBIF spelling) and its APT text setter (0x0046CBF0).
class BfmeThingBIF
{
public:
	void bfmeGoBIF( void *what, void *out );
};

class WindowManager
{
public:
	void bfme_setAptText( const AsciiString &name, const UnicodeString &text );
};

extern WindowManager *g_theWindowManager;

class BfmeAptScreenSpellStore
{
public:
	void unidentified_000062DF();

private:
	char m_unmodelled[ 0x25A ];
	bool m_field25A;
	char m_unmodelled25B[ 5 ];
	struct SpellStorePair
	{
		GameWindow *first;
		int second;
	};
	SpellStorePair m_fields260[ 12 ];
};

void BfmeAptScreenSpellStore::unidentified_000062DF()
{
	if( m_field25A )
		return;

	for( int i = 0; i < 12; ++i )
	{
		GameWindow *button = TheControlBar->m_windows09C[ i ];
		if( button == 0 )
			continue;
		if( button->winIsHidden() )
			continue;

		SpellButtonData *data = (SpellButtonData *)GadgetButtonGetData( button );
		if( data == 0 )
			continue;

		SpellStorePair *field = &m_fields260[ i ];
		field->first = button;
		field->second = 0;
		int current = ( (Gen_0049AFE0 *)data )->bfmeCurrent();
		if( current != 0 )
		{
			{
				AsciiString name;
				name.format( AsciiString( "SpellStore/Buttons/Spell%d" ), i + 1 );
				( (BfmeThingBIF *)g_theWindowManager )->bfmeGoBIF( &name, (void *)current );
			}

		}

		ScienceType *scienceBegin = data->getScienceVec().begin();
		ScienceType science = scienceBegin[ 0 ];
		int cost = TheScienceStore->getSciencePurchaseCost( science );
		{
			UnicodeString costText;
			costText.format( UnicodeString( (const unsigned short *)L"%d" ), cost );
			AsciiString costName;
			costName.format( AsciiString( "APT:Spell%dCost" ), i + 1 );
			g_theWindowManager->bfme_setAptText( costName, costText );
		}
	}
}
