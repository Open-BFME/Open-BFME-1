// cl: /GS
// EA FESL game-browser request at retail 0x007F6740.
//
// The matched 0x00802910 forwarding caller fixes this as a thiscall on the
// browser object and fixes the fifteen incoming stack words.  This body shows
// that two of those opaque words are array pointers and the following words
// are their counts: it joins an int64 array and a string array with ';' before
// forwarding the request through browser service slot 0x1C.

typedef __int64 Rva007F6740Int64;

class BfmeMsgVJH
{
public:
	BfmeMsgVJH( char *buffer, int size ) throw();
	~BfmeMsgVJH() throw();

	char m_data[ 0x34 ];
};

void Rva00800040JoinI64( const Rva007F6740Int64 *parts, unsigned count,
	char *dest, unsigned destSize, char separator );
void Rva00800170Join( const char **parts, unsigned count, char *dest,
	unsigned destSize, char separator );

class Rva007F6740Receiver;
class Rva007E8810Message;

// Retail 0x007F6730 is the cdecl two-argument reply adapter: it forwards its
// first argument to the browser object supplied as its second argument.
void __cdecl Rva007F6730Callback( Rva007E8810Message *message,
	Rva007F6740Receiver *browser );

class Rva007F6740RequestService
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void send( BfmeMsgVJH *message, void *context,
		int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8,
		int a14, int a13, const char *int64Text,
		const char *stringText ) throw() = 0;
};

class Rva007F6740AsyncService
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void send( BfmeMsgVJH *message,
		void (__cdecl *callback)( Rva007E8810Message *,
			Rva007F6740Receiver * ),
		Rva007F6740Receiver *owner, int transaction ) throw() = 0;
};

class Rva007F6740Receiver
{
public:
	void call( void *context, int a1, int a2, int a3, int a4, int a5,
		int a6, int a7, int a8, const Rva007F6740Int64 *int64Parts,
		unsigned int64Count, const char **stringParts,
		unsigned stringCount, int a13, int a14 ) throw();

private:
	char m_pad00[ 0x10 ];
	Rva007F6740RequestService *m_requestService;
	Rva007F6740AsyncService *m_asyncService;
	char m_pad18[ 0x2C4 ];
	char m_messageBuffer[ 0x400 ];
	int m_transaction;
};

void Rva007F6740Receiver::call( void *context, int a1, int a2, int a3,
	int a4, int a5, int a6, int a7, int a8,
	const Rva007F6740Int64 *int64Parts, unsigned int64Count,
	const char **stringParts, unsigned stringCount, int a13,
	int a14 ) throw()
{
	BfmeMsgVJH message( m_messageBuffer, sizeof( m_messageBuffer ) );
	char stringText[ 0x100 ];
	char int64Text[ 0x100 ];

	stringText[ 0 ] = 0;
	int64Text[ 0 ] = 0;

	Rva00800040JoinI64( int64Parts, int64Count,
		int64Text, sizeof( int64Text ), ';' );
	Rva00800170Join( stringParts, stringCount,
		stringText, sizeof( stringText ), ';' );

	m_requestService->send( &message, context, a1, a2, a3, a4, a5, a6,
		a7, a8, a14, a13, int64Text, stringText );
	m_asyncService->send( &message, Rva007F6730Callback, this,
		m_transaction );
}
