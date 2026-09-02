// ??1BfmeAptScreenOnlineQuickMatch@@UAE@XZ
// partial score=0.96 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x005587F0: virtual destructor of the OnlineQuickMatch.apt screen.
// Resets the derived vtable, unregisters AptOnlineQuickMatch::InitGadgets when
// this is the published singleton, destroys members at +0x5c and +0x40, then
// the APT window base.

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
	virtual ~BfmeAptGameWindow();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();

private:
	char m_unmodelled[ 0x3C ];
};

void _bfme_closeAptScreen( const AsciiString &name );

class QuickMatchSlot40
{
public:
	~QuickMatchSlot40();

private:
	char m_unmodelled[ 0x14 ];
};

class QuickMatchSlot5C
{
public:
	~QuickMatchSlot5C();

private:
	char m_unmodelled[ 0x20 ];
};

extern const void *BfmeAptScreenOnlineQuickMatchVftable[];
extern void *g_obj12F4ABC;

class BfmeAptScreenOnlineQuickMatch : public BfmeAptGameWindow
{
public:
	virtual ~BfmeAptScreenOnlineQuickMatch();

private:
	QuickMatchSlot40 m_slot40;
	unsigned char m_ready;
	unsigned char m_startRequested;
	unsigned char m_pad56;
	unsigned char m_pad57;
	int m_pad58;
	QuickMatchSlot5C m_slot5c;
};

// ??1BfmeAptScreenOnlineQuickMatch@@UAE@XZ
BfmeAptScreenOnlineQuickMatch::~BfmeAptScreenOnlineQuickMatch()
{
	*(const void ***)( this ) = BfmeAptScreenOnlineQuickMatchVftable;

	if( this == g_obj12F4ABC )
	{
		{
			AsciiString name( "AptOnlineQuickMatch::InitGadgets" );
			_bfme_closeAptScreen( name );
		}
		g_obj12F4ABC = 0;
	}
}
