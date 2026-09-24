// cl: /DNDEBUG /MD /EHsc
// Hotkey helper called by the matched Rva00590010FourString constructor (0x00590010):
// strips '&' markers from the first string and returns the upper-cased hotkey.

typedef unsigned short Rva0058FE60WideChar;

extern const char g_bfmeEmptyUnicode[];

template <typename T> struct Rva0058FE60StringData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class UnicodeString;

public:
	void concat( const T *text, int length );

private:
	StringBase( const T *text );
	StringBase( const StringBase<T> &other, int start, int length );
	~StringBase();

	Rva0058FE60StringData<T> *m_data;
};

class UnicodeString : private StringBase<Rva0058FE60WideChar>
{
public:
	UnicodeString( const Rva0058FE60WideChar *text ) : StringBase<Rva0058FE60WideChar>( text ) {}
	UnicodeString( const UnicodeString &other, int start, int length ) :
		StringBase<Rva0058FE60WideChar>( other, start, length ) {}
	~UnicodeString() {}

	const Rva0058FE60WideChar *str() const
	{
		return m_data ? m_data->m_text : (const Rva0058FE60WideChar *)g_bfmeEmptyUnicode;
	}

	int getLength() const
	{
		return m_data ? m_data->m_length : 0;
	}

	Rva0058FE60WideChar getCharAt( int index ) const
	{
		return m_data ? m_data->m_text[index] : 0;
	}

	void concat( const Rva0058FE60WideChar *text, int length )
	{
		StringBase<Rva0058FE60WideChar>::concat( text, length );
	}

	void swap( UnicodeString &other )
	{
		Rva0058FE60StringData<Rva0058FE60WideChar> *data = m_data;
		m_data = other.m_data;
		other.m_data = data;
	}
};

class Rva00590010FourString
{
public:
	UnicodeString m_first;
	UnicodeString m_second;
	UnicodeString m_third;
	UnicodeString m_fourth;
	unsigned short m_value;
};

extern "C" __declspec(dllimport) int __cdecl iswalnum( Rva0058FE60WideChar character );
extern "C" __declspec(dllimport) Rva0058FE60WideChar __cdecl towupper( Rva0058FE60WideChar character );

unsigned short __cdecl rva0058FE60Compute( Rva00590010FourString *record )
{
	int length = record->m_first.getLength();
	for (int index = 0; index != length; ++index)
	{
		if (record->m_first.getCharAt( index ) == '&')
		{
			Rva0058FE60WideChar hotkey = 0;
			UnicodeString output( UnicodeString( record->m_first.str() ), 0, index );
			for (; index < length; ++index)
			{
				Rva0058FE60WideChar character = record->m_first.getCharAt( index );
				if (character == '&')
				{
					++index;
					if (index >= length)
						break;
					character = record->m_first.getCharAt( index );
					if (hotkey == 0 && iswalnum( character ))
						hotkey = towupper( character );
				}
				output.concat( &character, 1 );
			}
			record->m_first.swap( output );
			return hotkey;
		}
	}
	return 0;
}
