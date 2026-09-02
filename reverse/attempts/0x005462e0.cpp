// ?bfmeOnlineHomeRankText@@YA?AVUnicodeString@@H@Z
// partial score=0.56 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef unsigned short WideChar;

template <typename T> class StringBase
{
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

public:
	void set( const StringBase<T> &other );

protected:
	void *m_data;
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() {}
	UnicodeString( const WideChar *text ) : StringBase<WideChar>( text ) {}
	UnicodeString( const UnicodeString &other ) : StringBase<WideChar>( other ) {}
	~UnicodeString() {}
	UnicodeString &operator=( const UnicodeString &other )
	{
		set( other );
		return *this;
	}
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

UnicodeString bfmeOnlineHomeRankText( int rank )
{
	int value = rank;
	UnicodeString text;
	if( value < 0 )
		text = TheGameText->fetch( "TOOLTIP:LadderRankUnavailable" );
	else
		text.format( (const WideChar *)L"%d", value );
	return text;
}
