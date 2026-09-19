// ?unidentified_000062DF@BfmeAptScreenSpellStore@@QAEXXZ
// partial score=0.99 date=2026-09-17
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeAptScreenSpellStore::unidentified_000062DF, retail 0x005996F0, 441 bytes.
// AptScreenFactories.cpp calls this body after registering the SpellStore
// callbacks. The 0x000062DF thunk names the final SpellStore update method.

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
private:
	char m_unmodelled[ 0x9C ];
	GameWindow *m_spellButtons[ 12 ];
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

class BfmeThingBIF
{
public:
	void bfmeGoBIF( void *what, void *out );
};

extern BfmeThingBIF *Rva00579160TheManager;

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

	int spell = 1;
	int controlOffset = 0x9C;
	SpellStorePair *field = m_fields260;
	int remaining = 12;

	do
	{
		GameWindow *button = *(GameWindow **)( controlOffset + (unsigned int)TheControlBar );
		if( button == 0 )
			goto next;
		if( button->winIsHidden() )
			goto next;

		SpellButtonData *data = (SpellButtonData *)GadgetButtonGetData( button );
		if( data == 0 )
			goto next;

		field->first = button;
		field->second = 0;
		int current = ( (Gen_0049AFE0 *)data )->bfmeCurrent();
		if( current != 0 )
		{
			{
				AsciiString name;
				name.format( AsciiString( "SpellStore/Buttons/Spell%d" ), spell );
				Rva00579160TheManager->bfmeGoBIF( &name, (void *)current );
			}

		}

		ScienceType *scienceBegin = data->getScienceVec().begin();
		ScienceType science = scienceBegin[ 0 ];
		int cost = TheScienceStore->getSciencePurchaseCost( science );
		{
			UnicodeString costText;
			costText.format( UnicodeString( (const unsigned short *)L"%d" ), cost );
			AsciiString costName;
			costName.format( AsciiString( "APT:Spell%dCost" ), spell );
			Rva00579160TheManager->bfmeGoBIF( &costName, &costText );
		}

	next:
		controlOffset += 4;
		field++;
		++spell;
	}
	while( --remaining != 0 );
}
