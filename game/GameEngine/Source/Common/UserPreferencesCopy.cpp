// ??0UserPreferences@@QAE@ABV0@@Z
// Retail 0x0057D2D0: UserPreferences copy constructor.
// cl: /O2 /Ob1 /DNDEBUG /MD /EHsc
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <map>

class AsciiString
{
private:
	void *m_data;
};

typedef _STL::map<AsciiString, AsciiString> PreferenceMapShim;

class UnicodeString;

template <typename T> class StringBase
{
private:
	friend class UnicodeString;
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString( const UnicodeString &other ) :
		StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
};

class UserPreferences : public PreferenceMapShim
{
public:
	UserPreferences( const UserPreferences &other );
	virtual ~UserPreferences();

private:
	UnicodeString m_filename;
};

UserPreferences::UserPreferences( const UserPreferences &other ) :
	PreferenceMapShim( other ),
	m_filename( other.m_filename )
{
}
