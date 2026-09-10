// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ?setOnlineIPAddress@OptionPreferences@@QAEXI@Z
//
// The unsigned overload is the helper called by the online-IP selection in
// OptionsMenu.cpp.  Its retail body constructs an AsciiString format argument
// in place, then writes the formatted address through the preference map.

#include <map>

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}

	void format( AsciiString format, ... );
	AsciiString &operator=( const AsciiString &other );
};

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()( const AsciiString &left, const AsciiString &right ) const;
};
}

typedef _STL::map<AsciiString, AsciiString, _STL::less<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, AsciiString> > > PreferenceMap;

template AsciiString &PreferenceMap::operator[]( const AsciiString & );

class UserPreferences : public PreferenceMap
{
public:
	virtual ~UserPreferences();
};

class OptionPreferences : public UserPreferences
{
public:
	void setOnlineIPAddress( unsigned IP );
};

void OptionPreferences::setOnlineIPAddress( unsigned IP )
{
	AsciiString tmp;
	tmp.format( AsciiString( "%d.%d.%d.%d" ), IP >> 24,
		((IP & 0xff0000) >> 16), ((IP & 0xff00) >> 8), (IP & 0xff) );
	AsciiString key( "GameSpyIPAddress" );
	AsciiString &slot = (*this)[key];
	slot = tmp;
}
