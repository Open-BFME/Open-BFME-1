// ?_bfme_populateCountryList@BfmeAptScreenOnlineLogin@@QAEXXZ
// BfmeAptScreenOnlineLogin::_bfme_populateCountryList, retail 0x005506F0.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// The matched _bfme_onInitGadget caller at 0x00551DD0 stores the country-list
// window at +0x88. It calls this method through ILT 0x00005F83.
//
// This method adds "WOL:Locale01" as row 0.
// It stores locales 02 through 37 in a map from UnicodeString names to
// Rva0054FA30Mapped values.
// The map sorts those rows by locale name before the method adds them.
// It selects the row that matches the registry language.
// An empty registry language or "english" selects "United States".

void __cdecl operator delete[]( void * ) throw();
void __cdecl operator delete( void * ) throw();
#include <map>

extern "C" __declspec(dllimport) unsigned int __cdecl wcslen( const unsigned short *text );

class GameWindow;

struct Rva0009ECA0NoCaseTraits
{
	Rva0009ECA0NoCaseTraits() {}
	int compareNoCaseRaw( const unsigned short *left, const unsigned short *right,
		int length ) const throw();

};

template <typename T>
class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

public:
	int compare( const StringBase<T> &str ) const;

	bool isEmpty() const { return getLength() == 0; }
	int getLength() const { return m_data ? m_data->length : 0; }

	void set( const T *str, int len );

	const T *str() const { return m_data ? m_data->data : (const T *)L""; }

	int compareNoCase( const T *str, int strLength ) const
	{
		int thisLength = m_data ? m_data->length : 0;
		const T *thisText = m_data ? m_data->data : (const T *)L"";
		int result = ((const Rva0009ECA0NoCaseTraits *)(this + 5))->compareNoCaseRaw( thisText, str,
			thisLength < strLength ? thisLength : strLength );
		return result != 0 ? result : thisLength - strLength;
	}

	int compareNoCase( const T *str ) const { return compareNoCase( str, wcslen( str ) ); }

	int compareNoCase( const StringBase<T> &other ) const
	{
		return compareNoCase( other.str(), other.getLength() );
	}

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *str );
	StringBase( const StringBase<T> &src ) throw();
	~StringBase() { releaseBuffer(); }

	void releaseBuffer();

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[ 1 ];
	};

	Header *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString() {}
	AsciiString( const char *str ) : StringBase<char>( str ) {}
	~AsciiString() {}

	void __cdecl format( AsciiString fmt, ... );
	const char *str() const { return m_data ? m_data->data : ""; }
};

class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString() {}
	UnicodeString( const UnicodeString &that ) : StringBase<unsigned short>( that ) {}
	~UnicodeString() {}

	void translate( const AsciiString &that );
	UnicodeString &operator=( const unsigned short *str )
	{
		set( str, wcslen( str ) );
		return *this;
	}
};

namespace _STL
{
template <> struct less<UnicodeString>
{
	bool operator()( const UnicodeString &left, const UnicodeString &right ) const
	{
		return left.compare( right ) < 0;
	}
};
}

enum Rva0054FA30Mapped { Rva0054FA30MappedZero = 0 };

typedef _STL::map<UnicodeString, Rva0054FA30Mapped, _STL::less<UnicodeString>,
	_STL::allocator<_STL::pair<const UnicodeString, Rva0054FA30Mapped> > > CountryLocaleMap;

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0c(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1c(); virtual void slot20();
	virtual void slot24();
	virtual UnicodeString fetch( const char *label, bool *exists = 0 );
};

extern GameTextInterface *TheGameText;
extern int GameSpyColor[];

AsciiString GetRegistryLanguage();
int GadgetListBoxAddEntryText( GameWindow *listbox, UnicodeString text, int color,
	int row, int column, bool overwrite );
void GadgetListBoxSetItemData( GameWindow *listbox, void *data, int row, int column );
void GadgetListBoxSetSelected( GameWindow *listbox, int selectIndex );

class BfmeAptScreenOnlineLogin
{
public:
	void _bfme_populateCountryList();

private:
	unsigned char m_unmodelled00[ 0x88 ];
	GameWindow *m_countryList;
};

// ?_bfme_populateCountryList@BfmeAptScreenOnlineLogin@@QAEXXZ
void BfmeAptScreenOnlineLogin::_bfme_populateCountryList()
{
	AsciiString label;
	label.format( AsciiString( "WOL:Locale%2.2d" ), 1 );
	int row = GadgetListBoxAddEntryText( m_countryList,
		TheGameText->fetch( label.str() ), GameSpyColor[ 0 ], -1, -1, true );
	GadgetListBoxSetItemData( m_countryList, (void *)1, row, 0 );

	CountryLocaleMap locales;
	for( int i = 2; i <= 0x25; ++i )
	{
		AsciiString localeLabel;
		localeLabel.format( AsciiString( "WOL:Locale%2.2d" ), i );
		locales[ TheGameText->fetch( localeLabel.str() ) ] = (Rva0054FA30Mapped)i;
	}

	UnicodeString language;
	language.translate( GetRegistryLanguage() );
	if( language.isEmpty() || language.compareNoCase( (const unsigned short *)L"english" ) == 0 )
		language = (const unsigned short *)L"United States";

	int selectedRow = 0;
	for( CountryLocaleMap::iterator it = locales.begin(); it != locales.end(); ++it )
	{
		row = GadgetListBoxAddEntryText( m_countryList, it->first,
			GameSpyColor[ 0 ], -1, -1, true );
		GadgetListBoxSetItemData( m_countryList, (void *)it->second, row, 0 );
		if( language.compareNoCase( it->first ) == 0 )
			selectedRow = row;
	}

	GadgetListBoxSetSelected( m_countryList, selectedRow );
}
