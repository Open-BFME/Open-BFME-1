// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeAptScreenOnlineQuickMatch destructor, retail 0x005587F0, 172 bytes.
// The member offsets and InitGadgets callback identify this as the destructor
// paired with the 0x01108BCC OnlineQuickMatch vtable.

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

class BfmeAptGameWindow
{
public:
	virtual ~BfmeAptGameWindow()
	{
		bfmeDestroy();
	}
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	void bfmeDestroy();

private:
	unsigned char m_unmodelled[ 0x3C ];
};

class QuickMatchPreferences
{
public:
	virtual ~QuickMatchPreferences();

private:
	unsigned char m_unmodelled[ 0x10 ];
};

class Gen_uw_0003eb53
{
public:
	~Gen_uw_0003eb53();

private:
	unsigned char m_unmodelled[ 0x14 ];
};

void _bfme_closeAptScreen( const AsciiString &name );

class BfmeAptScreenOnlineQuickMatch;
extern BfmeAptScreenOnlineQuickMatch *g_s4Guard0055BC20;

class BfmeAptScreenOnlineQuickMatch : public BfmeAptGameWindow
{
public:
	virtual ~BfmeAptScreenOnlineQuickMatch();

private:
	class QuickMatchPreferences m_slot40;
	unsigned char m_ready;
	unsigned char m_startRequested;
	unsigned char m_pad56;
	unsigned char m_pad57;
	int m_pad58;
	Gen_uw_0003eb53 m_slot5c;
};

BfmeAptScreenOnlineQuickMatch::~BfmeAptScreenOnlineQuickMatch()
{
	if( this == reinterpret_cast<void * &>(g_s4Guard0055BC20) )
	{
		{
			AsciiString name( "AptOnlineQuickMatch::InitGadgets" );
			_bfme_closeAptScreen( name );
		}
		reinterpret_cast<void * &>(g_s4Guard0055BC20) = 0;
	}
}
