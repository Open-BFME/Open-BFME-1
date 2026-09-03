// ?formatLadderRankText@@YA?AVUnicodeString@@H@Z
// partial score=0.56 date=2026-09-03
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x00539020, 191 bytes. Return a ladder-rank UnicodeString: negative
// ranks fetch TOOLTIP:LadderRankUnavailable, otherwise format L"%d".
// Exact length; MSVC 7.1 will not hoist rank into EAX before zeroing the
// result local or reuse the argument slot the way retail does (same wall as
// 0x005462E0).

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

UnicodeString formatLadderRankText( int rank )
{
	UnicodeString text;
	if( rank < 0 )
		text = TheGameText->fetch( "TOOLTIP:LadderRankUnavailable" );
	else
		text.format( (UnicodeString)L"%d", rank );
	return text;
}
