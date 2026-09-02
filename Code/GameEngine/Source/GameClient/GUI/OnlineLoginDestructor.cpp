// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase( const T *text );
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	~AsciiString() {}
};

class BfmeOnlineLoginMember3C
{
public:
	~BfmeOnlineLoginMember3C();

private:
	unsigned char m_data[ 0x6C ];
};

class BfmeAptGameWindow
{
public:
	virtual ~BfmeAptGameWindow()
	{
		bfmeDestroy();
	}
	void bfmeDestroy();

private:
	unsigned char m_unmodelled[ 0x38 ];
};

class GameWindowManager
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5C() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual void slot68() = 0;
	virtual void slot6C() = 0;
	virtual void slot70() = 0;
	virtual void slot74() = 0;
	virtual void slot78() = 0;
	virtual void slot7C() = 0;
	virtual void slot80() = 0;
	virtual void slot84() = 0;
	virtual void slot88() = 0;
	virtual void slot8C() = 0;
	virtual void slot90() = 0;
	virtual void slot94() = 0;
	virtual void slot98() = 0;
	virtual void slot9C() = 0;
	virtual void bfmeOnlineLoginShutdown() = 0;
};

class BfmeImeManager
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void bfmeDetach() = 0;
};

void _bfme_closeAptScreen( const AsciiString &name );

extern GameWindowManager *TheWindowManager;
extern BfmeImeManager *TheBfmeImeManager;

class BfmeAptScreenOnlineLogin;
extern BfmeAptScreenOnlineLogin *TheBfmeOnlineLogin;

class BfmeAptScreenOnlineLogin : public BfmeAptGameWindow
{
public:
	virtual ~BfmeAptScreenOnlineLogin();

private:
	BfmeOnlineLoginMember3C m_state;
	AsciiString m_name;
	unsigned int m_tail;
};

BfmeAptScreenOnlineLogin::~BfmeAptScreenOnlineLogin()
{
	if( TheBfmeOnlineLogin == this )
	{
		{
			AsciiString callback( "AptOnlineLogin::InitGadgets" );
			_bfme_closeAptScreen( callback );
		}
		if( TheWindowManager )
			TheWindowManager->bfmeOnlineLoginShutdown();
		TheBfmeImeManager->bfmeDetach();
		TheBfmeOnlineLogin = 0;
	}
}
