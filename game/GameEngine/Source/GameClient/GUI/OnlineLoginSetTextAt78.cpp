// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

template <typename T> class StringBase
{
	friend class UnicodeString;

private:
	StringBase( const StringBase<T> &other );
	~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();

public:
	int compare( const StringBase<T> &other ) const;

	void *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
};

// UnicodeString::compare, expanded in place: the StringBase<unsigned short>
// compare call.  An inline member would emit a ?compare@UnicodeString@@QBEHABV1@@Z
// COMDAT; retail has no such body (the name routes through ILT 0x000226EC).
static __forceinline int wideCompare( const UnicodeString &string, const UnicodeString &other )
{
	return reinterpret_cast<const StringBase<unsigned short> &>( string ).compare(
		reinterpret_cast<const StringBase<unsigned short> &>( other ) );
}

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
	if( wideCompare( current, text ) == 0 )
		return false;

	if( m_control78 )
	{
		GadgetComboBoxSetText( m_control78, text );
		result = true;
	}
	return result;
}
