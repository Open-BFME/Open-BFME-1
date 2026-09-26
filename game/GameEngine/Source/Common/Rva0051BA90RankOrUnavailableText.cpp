// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x0051BA90, 191 bytes. Same TOOLTIP:LadderRankUnavailable / L"%d"
// shape as the banked formatLadderRankText siblings (0x0052DEB0, 0x00539020,
// 0x005462E0), but those three branch "jge" (rank>=0 formats, rank<0 falls
// back) while this one branches "jg" (rank>0 formats, rank<=0 falls back), so
// the rank==0 case differs and the identity is not the same function. Landed
// address-derived.
//
// The wall on all four is the same: retail needs three frame slots (the
// result local, the fetch temporary, the return-UDT flag) but allocates two
// with sub esp,8, so the fetch temporary lands in the dead incoming
// parameter-home slot. That is retail's internal-linkage register convention
// (matches Rva002E32A0ObjectIdAsStr.cpp's static-function lever); an
// externally-linked definition of the same body places the slot 53 bytes
// apart. Static plus a TU-local absent-from-retail caller reproduces it.

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

static UnicodeString Rva0051BA90RankOrUnavailableText( int rank )
{
	UnicodeString text;
	if( rank <= 0 )
		text = TheGameText->fetch( "TOOLTIP:LadderRankUnavailable" );
	else
		text.format( (UnicodeString)L"%d", rank );
	return text;
}

// absent-from-retail: keeps the static formatter emitted with retail's
// internal-linkage register convention.
// ?Rva0051BA90Caller@@YAXHPAVUnicodeString@@@Z absent-from-retail
void Rva0051BA90Caller( int rank, UnicodeString *out )
{
	*out = Rva0051BA90RankOrUnavailableText( rank );
}
