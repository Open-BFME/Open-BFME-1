// ?d_0058fe60@@YAXXZ
// partial score=0.86 date=2026-09-11
// cl: /DNDEBUG /MD /EHsc

typedef unsigned short Rva0058FE60WideChar;

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

private:
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	StringBase( const StringBase<T> &other, int start, int length );
	~StringBase();
	void concat( const T *text, int length );

	Rva0058FE60StringData<T> *m_data;
};

class UnicodeString : private StringBase<Rva0058FE60WideChar>
{
public:
	UnicodeString( const Rva0058FE60WideChar *text ) : StringBase<Rva0058FE60WideChar>( text ) {}
	UnicodeString( const UnicodeString &other, int start, int length ) :
		StringBase<Rva0058FE60WideChar>( other, start, length ) {}
	~UnicodeString() {}

	Rva0058FE60StringData<Rva0058FE60WideChar> *data() const
	{
		return m_data;
	}

	void setData( Rva0058FE60StringData<Rva0058FE60WideChar> *data )
	{
		m_data = data;
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

struct Rva0058FE60StringSlot
{
	Rva0058FE60StringData<Rva0058FE60WideChar> *m_data;

	Rva0058FE60WideChar getCharAt( int index ) const
	{
		return m_data ? m_data->m_text[index] : 0;
	}
};

class Rva00590010FourString
{
public:
	Rva0058FE60StringSlot m_first;
	Rva0058FE60StringSlot m_second;
	Rva0058FE60StringSlot m_third;
	Rva0058FE60StringSlot m_fourth;
	unsigned short m_value;
};

extern const char g_bfmeEmptyUnicode[];
extern "C" __declspec(dllimport) int __cdecl iswalnum( Rva0058FE60WideChar character );
extern "C" __declspec(dllimport) Rva0058FE60WideChar __cdecl towupper( Rva0058FE60WideChar character );

// ?rva0058FE60Compute@@YAGPAVRva00590010FourString@@@Z
unsigned short __cdecl rva0058FE60Compute( Rva00590010FourString *record )
{
	Rva0058FE60StringData<Rva0058FE60WideChar> *data = record->m_first.m_data;
	int length = data ? (int)data->m_length : 0;
	if (length == 0)
		return 0;
	int index = 0;

	const Rva0058FE60WideChar *text = data ? data->m_text :
		(const Rva0058FE60WideChar *)g_bfmeEmptyUnicode;
	while (index < length && text[index] != (Rva0058FE60WideChar)'&')
		++index;
	if (index == length)
		return 0;

	Rva0058FE60WideChar hotkey = 0;
	UnicodeString output( UnicodeString( text ), 0, 0 );
	while (index < length)
	{
		Rva0058FE60WideChar character = record->m_first.getCharAt( index );
		if (character == (Rva0058FE60WideChar)'&')
		{
			++index;
			if (index >= length)
				break;
			character = record->m_first.getCharAt( index );
			if (hotkey == 0 && iswalnum( character ))
				hotkey = towupper( character );
		}
		output.concat( &character, 1 );
		++index;
	}

	Rva0058FE60StringData<Rva0058FE60WideChar> *oldData = record->m_first.m_data;
	record->m_first.m_data = output.data();
	output.setData( oldData );
	return hotkey;
}
