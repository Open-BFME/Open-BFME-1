// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x00510130..0x00510235 (exclusive end 0x00510236), ret 4.
// FileTransfer::doFileTransfer at 0x0066CE60 calls the
// BfmeAptScreenMapTransfer timeout body through the retail virtual-file
// transfer path.  This source preserves that body's swprintf ABI and local
// buffer extent without retaining the former naked byte dump.

typedef char Bool;
typedef unsigned short WideChar;

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString( const WideChar *text ) : StringBase<WideChar>( text ) {}
	UnicodeString( const UnicodeString &other )
		: StringBase<WideChar>( other ) {}
	~UnicodeString() {}

	const WideChar *str() const
	{
		if( m_data )
			return reinterpret_cast<const WideChar *>(
				reinterpret_cast<const char *>( m_data ) + 8 );
		return reinterpret_cast<const WideChar *>( 0x0107388C );
	}
};

class GameTextInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual UnicodeString fetch( const char *, Bool *exists = 0 );
};

class WindowManager
{
public:
	void bfme_setAptText( const AsciiString &, const UnicodeString & );
};

extern "C" __declspec(dllimport) int __cdecl swprintf(
	WideChar *, const WideChar *, ... );

extern GameTextInterface *TheGameText;
extern WindowManager *g_theWindowManager;

class BfmeAptScreenMapTransfer
{
public:
	void processTimeout( int secondsLeft );
};

// ?processTimeout@BfmeAptScreenMapTransfer@@QAEXH@Z
void BfmeAptScreenMapTransfer::processTimeout( int secondsLeft )
{
	if( secondsLeft < 0 )
		secondsLeft = 0;

	int minutes = secondsLeft / 60;
	int seconds = secondsLeft - minutes * 60;
	WideChar buffer[ 0x104 ];
	swprintf( buffer, TheGameText->fetch( "MapTransfer:Timeout" ).str(),
		minutes, seconds );

	UnicodeString text( buffer );
	g_theWindowManager->bfme_setAptText(
		AsciiString( "APT:FileTransferLoadingTime" ), text );
}
