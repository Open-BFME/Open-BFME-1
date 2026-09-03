// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#include <stdlib.h>

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<unsigned short>
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString( const UnicodeString &text );
	~AsciiString() {}
	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : (const char *)0x0107388B;
	}
};

// BFME OnlineLogin numeric text validator at retail 0x0054C9E0.
bool bfmeOnlineLoginIntegerInRange( const UnicodeString &text, int minimum, int maximum )
{
	AsciiString narrow( text );
	int value = atoi( narrow.str() );
	if( value < minimum || value > maximum )
		return false;
	return true;
}
