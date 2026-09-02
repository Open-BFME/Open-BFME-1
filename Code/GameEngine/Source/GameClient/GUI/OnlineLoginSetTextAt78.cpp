// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

template <typename T> class StringBase
{
	friend class UnicodeString;

private:
	StringBase( const StringBase<T> &other );
	~StringBase();

public:
	int compare( const StringBase<T> &other ) const;

	void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
	int compare( const UnicodeString &other ) const
	{
		return StringBase<unsigned short>::compare( other );
	}
};

class GameWindow;

void GadgetComboBoxSetText( GameWindow *window, UnicodeString text );

class BfmeAptScreenOnlineLogin
{
public:
	UnicodeString bfmeGetTextAt78() const;
	bool bfmeSetTextAt78( const UnicodeString &text );

private:
	unsigned char m_unmodelled[ 0x78 ];
	GameWindow *m_control78;
};

bool BfmeAptScreenOnlineLogin::bfmeSetTextAt78( const UnicodeString &text )
{
	bool result = false;
	UnicodeString current = bfmeGetTextAt78();
	if( current.compare( text ) == 0 )
		return false;

	if( m_control78 )
	{
		GadgetComboBoxSetText( m_control78, text );
		result = true;
	}
	return result;
}
