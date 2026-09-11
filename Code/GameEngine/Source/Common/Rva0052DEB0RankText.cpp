// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x0052DEB0, 191 bytes. This copy has the same unavailable-rank
// strings and branch boundary as the named ladder formatters, but no caller
// recovers a stronger owner name. Internal linkage reproduces retail's dead
// argument-slot reuse.

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

static UnicodeString Rva0052DEB0RankText( int rank )
{
	UnicodeString text;
	if( rank < 0 )
		text = TheGameText->fetch( "TOOLTIP:LadderRankUnavailable" );
	else
		text.format( (UnicodeString)L"%d", rank );
	return text;
}

// absent-from-retail: preserves the formatter's private register convention.
// ?Rva0052DEB0RankTextCaller@@YAXHPAVUnicodeString@@@Z absent-from-retail
void Rva0052DEB0RankTextCaller( int rank, UnicodeString *out )
{
	*out = Rva0052DEB0RankText( rank );
}
