// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x00539020, 191 bytes. The formatter uses an internal-linkage
// convention which lets MSVC reuse the dead rank argument slot for a
// UnicodeString temporary.

template <typename T> class StringBase
{
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const unsigned short *text ) : StringBase<unsigned short>( text ) {}
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
	UnicodeString &operator=( const UnicodeString &other );
	void format( UnicodeString format, ... );
};

class GameTextInterface
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
	virtual UnicodeString fetch( const char *label, bool *exists = 0 ) = 0;
};

extern GameTextInterface *TheGameText;

static UnicodeString formatLadderRankText( int rank )
{
	UnicodeString text;
	if( rank < 0 )
		text = TheGameText->fetch( "TOOLTIP:LadderRankUnavailable" );
	else
		text.format( (UnicodeString)L"%d", rank );
	return text;
}

// absent-from-retail: preserves the formatter's private register convention.
// ?formatLadderRankTextCaller@@YAXHPAVUnicodeString@@@Z absent-from-retail
void formatLadderRankTextCaller( int rank, UnicodeString *out )
{
	*out = formatLadderRankText( rank );
}
