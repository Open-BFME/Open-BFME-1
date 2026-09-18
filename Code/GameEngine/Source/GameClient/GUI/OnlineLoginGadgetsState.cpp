// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

template <typename T> class StringBase
{
	friend class AsciiString;

public:
	int compareNoCase( const T *text ) const;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}

	int compareNoCase( const char *text ) const
	{
		return ((const StringBase<char> *)this)->compareNoCase( text );
	}
};

bool GetStringFromRegistry( AsciiString path, AsciiString key, AsciiString &value );

class BfmeAptScreenOnlineLogin
{
public:
	bool _bfme_loginGadgetsState();
};

bool BfmeAptScreenOnlineLogin::_bfme_loginGadgetsState()
{
	AsciiString registeredValue;
	GetStringFromRegistry( "", "Registered", registeredValue );
	return registeredValue.compareNoCase( (const char *)0x01080FB4 ) == 0;
}
