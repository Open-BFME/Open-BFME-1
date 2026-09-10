// ?d_0055d7f0@@YAXXZ
// partial score=0.46 date=2026-09-10
// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Key-message pre-dispatch for an Online Shell style Apt screen, retail
// 0x0055D7F0 (597 bytes). Message type 0x15 with scan code 1 (escape-like)
// or 0x1C/0x9C (enter-like) special-cases a logoff confirmation; anything
// else and the fall-through both walk a listener vector at +0x25c/+0x260.
// The two GameText keys read from the binary at 0x011090B4/0x01109094 are
// "APT:LogoffConfirmationTitle" and "APT:LogoffConfirmationMsg", and the two
// FunctorSlot callback thunks installed are the OK/cancel handlers at
// 0x0042D2BD (j_0002d2bd -> 0x0055BD30) and 0x00418C00 (j_00018c00 ->
// 0x0055BD20), neither of which is landed yet.

typedef int Bool;

class StringBaseG
{
public:
	~StringBaseG() { releaseBuffer(); }

	void *m_bfmeBufDQ;

private:
	void releaseBuffer();
};

class GameTextInterface
{
public:
	virtual void bfmeSlot00GT();
	virtual void bfmeSlot01GT();
	virtual void bfmeSlot02GT();
	virtual void bfmeSlot03GT();
	virtual void bfmeSlot04GT();
	virtual void bfmeSlot05GT();
	virtual void bfmeSlot06GT();
	virtual void bfmeSlot07GT();
	virtual void bfmeSlot08GT();
	virtual void bfmeSlot09GT();
	virtual StringBaseG bfmeFetchDQ( const char *label, char *found );
};

extern GameTextInterface *TheGameText;

class GameSpyInfo
{
public:
	virtual void slot000(); virtual void slot004(); virtual void slot008(); virtual void slot00C();
	virtual void slot010(); virtual void slot014(); virtual void slot018(); virtual void slot01C();
	virtual void slot020(); virtual void slot024(); virtual void slot028(); virtual void slot02C();
	virtual void slot030(); virtual void slot034(); virtual void slot038(); virtual void slot03C();
	virtual void slot040(); virtual void slot044(); virtual void slot048(); virtual void slot04C();
	virtual void slot050(); virtual void slot054(); virtual void slot058(); virtual void slot05C();
	virtual void slot060(); virtual void slot064(); virtual void slot068(); virtual void slot06C();
	virtual void slot070(); virtual void slot074(); virtual void slot078(); virtual void slot07C();
	virtual void slot080(); virtual void slot084(); virtual void slot088(); virtual void slot08C();
	virtual void slot090(); virtual void slot094(); virtual void slot098(); virtual void slot09C();
	virtual void slot0A0(); virtual void slot0A4(); virtual void slot0A8(); virtual void slot0AC();
	virtual void slot0B0(); virtual void slot0B4(); virtual void slot0B8(); virtual void slot0BC();
	virtual void slot0C0(); virtual void slot0C4(); virtual void slot0C8(); virtual void slot0CC();
	virtual void slot0D0(); virtual void slot0D4(); virtual void slot0D8(); virtual void slot0DC();
	virtual void slot0E0(); virtual void slot0E4(); virtual void slot0E8(); virtual void slot0EC();
	virtual void slot0F0(); virtual void slot0F4(); virtual void slot0F8(); virtual void slot0FC();
	virtual void slot100(); virtual void slot104(); virtual void slot108(); virtual void slot10C();
	virtual void slot110(); virtual void slot114(); virtual void slot118(); virtual void slot11C();
	virtual void slot120(); virtual void slot124(); virtual void slot128(); virtual void slot12C();
	virtual void slot130(); virtual void slot134(); virtual void slot138(); virtual void slot13C();
	virtual void slot140(); virtual void slot144(); virtual void slot148(); virtual void slot14C();
	virtual void slot150(); virtual void slot154(); virtual void slot158(); virtual void slot15C();
	virtual void slot160(); virtual void slot164(); virtual void slot168(); virtual void slot16C();
	virtual void slot170(); virtual void slot174(); virtual void slot178();
	virtual Bool bfmeCanConfirmLogoff();
};

extern GameSpyInfo *TheGameSpyInfo;

class Rva005127A0InGameChat;
extern Rva005127A0InGameChat *g_Rva005127A0InGameChat;

extern void HideInGameChat();
extern void j_0002d2bd();
extern void j_00018c00();
extern void j_00028a51();

struct FunctorSlot
{
	__forceinline FunctorSlot( void *slot ) : m_slot( slot ) {}

	void *m_slot;
};

class FunctorSlotWrapperHead
{
public:
	__forceinline FunctorSlotWrapperHead() : m_refCount( 0 ) {}

	virtual void functorSlotWrapperAnchor();

	unsigned int m_refCount;
};

class Rva0055D8DBFunctorSlotWrapper : public FunctorSlotWrapperHead
{
public:
	__forceinline Rva0055D8DBFunctorSlotWrapper( const FunctorSlot &slot ) : m_slot( slot ) {}

	FunctorSlot m_slot;
};

class Rva0055D999FunctorSlotWrapper : public FunctorSlotWrapperHead
{
public:
	__forceinline Rva0055D999FunctorSlotWrapper( const FunctorSlot &slot ) : m_slot( slot ) {}

	FunctorSlot m_slot;
};

class Open2Counted
{
public:
	virtual void release( int deleting );

	int m_refs;
};

class Open2Handle
{
public:
	Open2Handle( Open2Counted *p ) : m_held( p )
	{
		if( m_held != 0 )
			++m_held->m_refs;
	}

	Open2Handle( const Open2Handle &other ) : m_held( other.m_held )
	{
		if( m_held != 0 )
			++m_held->m_refs;
	}

	~Open2Handle()
	{
		if( m_held != 0 && --m_held->m_refs <= 0 )
			m_held->release( 1 );
	}

	Open2Counted *m_held;
};

class Rva004C5C30
{
public:
	Rva004C5C30( Open2Handle first, Open2Handle second );

	Open2Handle m_first;
	Open2Handle m_second;
};

class Bfme5RefCounted
{
public:
	int m_refs;
};

class Bfme5RefPtr
{
public:
	Bfme5RefCounted *m_ptr;
};

struct Bfme5RefPairVal
{
	Bfme5RefPairVal( Bfme5RefCounted *a, Bfme5RefCounted *b )
	{
		m_a.m_ptr = a;
		m_b.m_ptr = b;
	}

	Bfme5RefPtr m_a;
	Bfme5RefPtr m_b;
	~Bfme5RefPairVal();
};

class Rva004C6370
{
public:
	Rva004C6370( Bfme5RefPairVal s );

	void *m_bfmeNode;
};

class BfmeTagZB
{
public:
	BfmeTagZB( int tag ) { m_bfmeTagZB = tag; }
	BfmeTagZB( const BfmeTagZB &other ) throw() { m_bfmeTagZB = other.m_bfmeTagZB; }
	~BfmeTagZB();

	int m_bfmeTagZB;
};

extern void __cdecl bfmeSendZB( void *first, void *second, void *third, BfmeTagZB tag );

class Rva0055D7F0Handler
{
public:
	virtual void hSlot00();
	virtual void hSlot04();
	virtual void hSlot08();
	virtual int handleKey( void *owner, int msgType, int code, int flags );
};

class Rva0055D7F0Owner
{
public:
	int handleLogoffKey( int msgType, int code, int flags );

private:
	unsigned char m_pad[ 0x25c ];
	Rva0055D7F0Handler **m_listBegin;
	Rva0055D7F0Handler **m_listEnd;
};

// @?handleLogoffKey@Rva0055D7F0Owner@@QAEHHHH@Z 0x0055D7F0
int Rva0055D7F0Owner::handleLogoffKey( int msgType, int code, int flags )
{
	unsigned char wantsConfirm = 0;

	if( msgType == 0x15 )
	{
		if( (unsigned char)code == 1 )
		{
			if( (unsigned char)code & (unsigned char)flags )
			{
				if( g_Rva005127A0InGameChat )
				{
					HideInGameChat();
					return 1;
				}
				wantsConfirm = 1;
			}
		}
		else if( (unsigned char)code == 0x1c || (unsigned char)code == 0x9c )
		{
			if( flags & 0xc )
			{
				if( TheGameSpyInfo && TheGameSpyInfo->bfmeCanConfirmLogoff() )
				{
					if( flags & 1 )
					{
						if( g_Rva005127A0InGameChat )
						{
							HideInGameChat();
							return 1;
						}
						j_00028a51();
						return 1;
					}
					return 1;
				}
			}
		}
	}

	for( Rva0055D7F0Handler **it = m_listBegin; it != m_listEnd; ++it )
	{
		if( (*it)->handleKey( this, msgType, code, flags ) == 1 )
			return 1;
	}

	if( !wantsConfirm )
		return 0;

	StringBaseG title = TheGameText->bfmeFetchDQ( "APT:LogoffConfirmationTitle", 0 );
	StringBaseG message = TheGameText->bfmeFetchDQ( "APT:LogoffConfirmationMsg", 0 );

	Rva004C5C30 pair(
		Open2Handle( (Open2Counted *)new Rva0055D8DBFunctorSlotWrapper( FunctorSlot( (void *)&j_0002d2bd ) ) ),
		Open2Handle( (Open2Counted *)new Rva0055D999FunctorSlotWrapper( FunctorSlot( (void *)&j_00018c00 ) ) ) );

	Rva004C6370 grand( Bfme5RefPairVal(
		(Bfme5RefCounted *)pair.m_first.m_held,
		(Bfme5RefCounted *)pair.m_second.m_held ) );

	bfmeSendZB( &title, &message, &grand, BfmeTagZB( 2 ) );

	return 0;
}
