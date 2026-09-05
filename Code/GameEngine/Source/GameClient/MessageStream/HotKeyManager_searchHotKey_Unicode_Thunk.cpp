// cl: /DNDEBUG /MD /EHsc /Ireference/shims/asciistring_downloadmanager

class UnicodeString;

template <typename T>
class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

public:
	void concat( const T *text, int length );

private:
	StringBase() : m_data( 0 ) { }
	StringBase( const StringBase& that );
	void releaseBuffer();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	static const AsciiString TheEmptyString;

	AsciiString() : StringBase<char>() { }
	AsciiString( const AsciiString& that ) : StringBase<char>( that ) { }
	~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
	void translate( const UnicodeString& that );
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	static UnicodeString TheEmptyString;

	UnicodeString() : StringBase<unsigned short>() { }
	UnicodeString( const UnicodeString& that ) : StringBase<unsigned short>( that ) { }
	~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }

	bool isEmpty() const
	{
		return m_data == 0
			|| *reinterpret_cast<const unsigned short *>(
				reinterpret_cast<const char *>(m_data) + 4) == 0;
	}
	const unsigned short *str() const
	{
		return m_data
			? reinterpret_cast<const unsigned short *>(
				reinterpret_cast<const char *>(m_data) + 8)
			: (const unsigned short *)L"";
	}
	void concat( const unsigned short *text, int length )
	{
		StringBase<unsigned short>::concat( text, length );
	}
	void concat( unsigned short character )
	{
		StringBase<unsigned short>::concat( &character, 1 );
	}
};

class HotKeyManager
{
public:
	AsciiString searchHotKey( const UnicodeString& );
};

// ?searchHotKey@HotKeyManager@@QAE?AVAsciiString@@ABVUnicodeString@@@Z
AsciiString HotKeyManager::searchHotKey( const UnicodeString& uStr )
{
	if (uStr.isEmpty())
		return AsciiString::TheEmptyString;

	const unsigned short *marker = uStr.str();
	while (marker && *marker)
	{
		if (*marker == L'&')
		{
			UnicodeString tmp = UnicodeString::TheEmptyString;
			tmp.concat( *(marker + 1) );
			AsciiString retStr;
			retStr.translate( tmp );
			return retStr;
		}
		marker++;
	}
	return AsciiString::TheEmptyString;
}
