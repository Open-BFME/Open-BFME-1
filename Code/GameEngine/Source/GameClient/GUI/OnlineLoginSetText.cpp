// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

template <typename T> class StringBase
{
	friend class UnicodeString;

private:
	StringBase( const StringBase<T> &other );
	~StringBase();

protected:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
	bool isEmpty() const
	{
		return !m_data || *(const unsigned short *)( (const char *)m_data + 4 ) == 0;
	}
};

class GameWindow;

void bfmeSetControlEnabled( GameWindow *window, bool enabled );
void GadgetTextEntrySetText( GameWindow *window, UnicodeString text );

class BfmeAptScreenOnlineLogin
{
public:
	bool bfmeSetTextAt7C( const UnicodeString &text, bool updateEnabled );

private:
	unsigned char m_unmodelled[ 0x7C ];
	GameWindow *m_textEntry;
	GameWindow *m_dependentControl;
};

bool BfmeAptScreenOnlineLogin::bfmeSetTextAt7C(
	const UnicodeString &text, bool updateEnabled )
{
	bool result = false;
	if( m_textEntry )
	{
		if( m_dependentControl && updateEnabled )
			bfmeSetControlEnabled( m_dependentControl, !text.isEmpty() );

		GadgetTextEntrySetText( m_textEntry, text );
		result = true;
	}
	return result;
}
