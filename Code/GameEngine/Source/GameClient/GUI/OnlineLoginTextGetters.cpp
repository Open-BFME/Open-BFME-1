// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

template <typename T> class StringBase
{
	friend class UnicodeString;

private:
	StringBase( const StringBase<T> &other );
	~StringBase();

public:
	void set( const StringBase<T> &other );

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
	UnicodeString &operator=( const UnicodeString &other )
	{
		set( other );
		return *this;
	}

	static const UnicodeString TheEmptyString;
};

class GameWindow;

UnicodeString GadgetComboBoxGetText( GameWindow *window );
UnicodeString GadgetTextEntryGetText( GameWindow *window );

class BfmeAptScreenOnlineLogin
{
public:
	UnicodeString bfmeGetTextAt74() const;
	UnicodeString bfmeGetTextAt78() const;
	UnicodeString bfmeGetTextAt7C() const;

private:
	unsigned char m_unmodelled[ 0x74 ];
	GameWindow *m_control74;
	GameWindow *m_control78;
	GameWindow *m_control7C;
};

UnicodeString BfmeAptScreenOnlineLogin::bfmeGetTextAt74() const
{
	UnicodeString text = UnicodeString::TheEmptyString;
	if( m_control74 )
		text = GadgetComboBoxGetText( m_control74 );
	return text;
}

UnicodeString BfmeAptScreenOnlineLogin::bfmeGetTextAt78() const
{
	UnicodeString text = UnicodeString::TheEmptyString;
	if( m_control78 )
		text = GadgetComboBoxGetText( m_control78 );
	return text;
}

UnicodeString BfmeAptScreenOnlineLogin::bfmeGetTextAt7C() const
{
	UnicodeString text = UnicodeString::TheEmptyString;
	if( m_control7C )
		text = GadgetTextEntryGetText( m_control7C );
	return text;
}
