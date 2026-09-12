// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
#include <vector>
//
// OnlineShell primary virtual slot 1: RVA 0x0055D7F0, 597 bytes. The paired
// constructor installs table 0x01108F48 whose slot routes through 0x0001DED0
// to this complete body (last ret12 at 0x0055DA42..44). The method spelling
// is reconstructed. The vector at +0x25c is also owned by the matched
// OnlineShell constructor/destructor.
//
// Message 0x15 handles Escape/Enter scan codes, toggles the in-game chat
// shortcut, then offers unconsumed messages to screen references. An
// unconsumed Escape opens the localized logoff confirmation. Its callback
// pair contains the WindowManager action (18C00 ->55BD20) and a no-op
// (2D2BD ->55BD30). Typed holders preserve the actual reference ownership.
// The strings belong inside the confirmation branch: this lexical scope
// reproduces retail's reuse of the first two dead incoming-argument slots.

class UnicodeString
{
public:
	~UnicodeString();
private:
	void *m_data;
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
	virtual UnicodeString fetch( const char *label, bool *found );
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
	// Retail vtable11188D0 +17C ->1CBDE ->637210: byte at +6FC.
	// Its wider original meaning is not recovered; this caller uses it as
	// the chat-shortcut gate, not as a permission to show logoff confirmation.
	virtual unsigned char getChatGateRva00637210() const;
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
	FunctorSlot(void (*callback)()) : m_callback(callback) {}
	void (*m_callback)();
};
class Open2Counted
{
public:
	Open2Counted() : m_refs(0) {}
	virtual ~Open2Counted();
	int m_refs;
};
class Rva010FDFACFunctorSlotWrapper : public Open2Counted
{
public:
	Rva010FDFACFunctorSlotWrapper(const FunctorSlot &slot) : m_callback(slot.m_callback) {}
	virtual ~Rva010FDFACFunctorSlotWrapper(); // slot0: 4C56A0 deleting destructor
	virtual void invoke(); // slot1: 4C5690, jumps through callback at +8
	void (*m_callback)();
};

class Open2Handle
{
public:
	Open2Handle( const FunctorSlot &slot ) : m_held( new Rva010FDFACFunctorSlotWrapper(slot) )
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
			delete m_held;
	}

	Open2Counted *m_held;
};

class Bfme5RefCounted
{
public:
	virtual ~Bfme5RefCounted();
	int m_refs;
};
class Bfme5RefPtr
{
public:
	Bfme5RefPtr(const Bfme5RefPtr &other) : m_ptr(other.m_ptr)
	{
		if(m_ptr) ++m_ptr->m_refs;
	}
	Bfme5RefCounted *m_ptr;
};
struct Bfme5RefPairVal
{
	Bfme5RefPtr m_a;
	Bfme5RefPtr m_b;
	~Bfme5RefPairVal();
};
class Rva004C5C30 : public Bfme5RefPairVal
{
public:
	Rva004C5C30(Open2Handle first, Open2Handle second);
};
class Rva004C6370
{
public:
	Rva004C6370(Bfme5RefPairVal s);
	Rva004C6370(const Rva004C6370 &other) throw() : m_bfmeNode(other.m_bfmeNode)
	{
		if(m_bfmeNode) ++((Open2Counted *)m_bfmeNode)->m_refs;
	}
	~Rva004C6370();
	void *m_bfmeNode;
};
// Existing byte-verified routes, used with their observed cdecl signatures:
// 28A51 ->511CC0 consumes mode3; 2E0B9 ->522D20 consumes dialog kind,
// the two UnicodeString references and the by-value callback-pair holder.
extern void j_0002e0b9();
typedef char KeyTextSize[(sizeof(UnicodeString) == 4) ? 1 : -1];
typedef char KeyCallbackSize[(sizeof(Rva010FDFACFunctorSlotWrapper) == 12) ? 1 : -1];
typedef char KeyPairSize[(sizeof(Rva004C5C30) == 8) ? 1 : -1];
typedef char KeyDialogHolderSize[(sizeof(Rva004C6370) == 4) ? 1 : -1];

class Rva0055D7F0Handler
{
public:
	virtual ~Rva0055D7F0Handler();
	virtual void hSlot04();
	virtual void hSlot08();
	virtual int handleKey( void *owner, int msgType, int code, int flags );
};

class BfmeAptScreenOnlineShell
{
public:
	int handleLogoffKey( int msgType, int code, int flags );

private:
	unsigned char m_pad[ 0x25c ];
	std::vector<Rva0055D7F0Handler *> m_list;
};

// @?handleLogoffKey@BfmeAptScreenOnlineShell@@QAEHHHH@Z 0x0055D7F0
int BfmeAptScreenOnlineShell::handleLogoffKey( int msgType, int code, int flags )
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
				if( TheGameSpyInfo && TheGameSpyInfo->getChatGateRva00637210() )
				{
					if( flags & 1 )
					{
						if( !g_Rva005127A0InGameChat )
						{
							((void (__cdecl *)(int))j_00028a51)(3);
							return 1;
						}
						HideInGameChat();
						return 1;
					}
					return 1;
				}
			}
		}
	}

	for( std::vector<Rva0055D7F0Handler *>::iterator it = m_list.begin(); it != m_list.end(); ++it )
	{
		if( (*it)->handleKey( this, msgType, code, flags ) == 1 )
			return 1;
	}

	if( wantsConfirm )
	{
		UnicodeString title = TheGameText->fetch( "APT:LogoffConfirmationTitle", 0 );
		UnicodeString message = TheGameText->fetch( "APT:LogoffConfirmationMsg", 0 );

		((void (__cdecl *)(int, const UnicodeString &, const UnicodeString &, Rva004C6370))j_0002e0b9)(
			2, title, message, Rva004C5C30(
				FunctorSlot(j_00018c00),
				FunctorSlot(j_0002d2bd)));

	}
	return 0;
}
