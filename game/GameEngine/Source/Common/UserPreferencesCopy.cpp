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

#include "../../../Libraries/Source/WWVegas/WWLib/unicode_string.h"
inline UnicodeString::UnicodeString(const UnicodeString &that) { ((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&that); }
inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }



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
