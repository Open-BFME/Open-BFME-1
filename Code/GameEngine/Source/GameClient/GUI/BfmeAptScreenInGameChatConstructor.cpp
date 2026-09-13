// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

public:
	void set( const StringBase<T> &other );
	void trim();

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
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	void format( AsciiString format, ... );
	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : (const char *)0x0107388B;
	}
};

// Erased eight-byte multiple-inheritance member pointer. The constructor
// only binds these code addresses; their argument-bearing callbacks are
// invoked by the existing wrappers, never through this erased carrier.
class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)( void );

struct FunctorBinding
{
	FunctorBinding( FunctorMethod method, FunctorTarget *target )
		: m_target( target ), m_method( method ) {}

	FunctorTarget *m_target;
	char m_alignmentPadding[4];
	FunctorMethod m_method;
};

// Primary APT/GameWindow view: 14 slots including the deleting destructor.
// Placeholder slot names preserve observed stack widths and return carriers;
// they are not proposed original method names.
class BfmeAptScreenBase
{
public:
	virtual ~BfmeAptScreenBase();
	virtual int aptSlot1(unsigned int, unsigned int, unsigned int);
	virtual int aptSlot2(unsigned int, unsigned int, unsigned int);
	virtual int aptSlot3(unsigned int);
	virtual int aptSlot4(unsigned int, unsigned int);
	virtual int aptSlot5();
	virtual int aptSlot6();
	virtual void *aptSlot7();
	virtual int aptSlot8();
	virtual int aptSlot9();
	virtual bool aptSlot10();
	virtual bool aptSlot11();
	virtual void aptSlot12();
	virtual void aptSlot13();
private:
	char m_unmodelled[0x214];
};
class S4Owner
{
public:
	virtual ~S4Owner();
private:
	char m_unmodelled[0x30];
};
class _bfme_AptGameWindow : public BfmeAptScreenBase, public S4Owner
{
public:
	_bfme_AptGameWindow(void *context);
	virtual ~_bfme_AptGameWindow();
private:
	char m_tail[0xC];
};

class BfmeThingTC { public: void bfmeBaseTC(); };
extern "C" const void *_bfmeVftTC[];

class Rva005127A0InGameChat;
extern Rva005127A0InGameChat *g_Rva005127A0InGameChat;   // 0x012F4988

// Opaque 16-byte gadget hook view. The existing constructor route 21FFD
// initializes the 12-byte base at 479230; its matching teardown at 479A30
// detaches the owner callback and restores the base table. Table 11051EC has
// deleting-destructor, input, and system slots; this view does not emit it.
class InGameChatSlot
{
public:
	InGameChatSlot()
	{
		((BfmeThingTC *)this)->bfmeBaseTC();
		m_bfmeVft = (void *)_bfmeVftTC;
		m_bfmeWhat = (void *)4;
	}
	~InGameChatSlot();


	void *m_bfmeVft;
	unsigned char m_bfmeGap[ 8 ];
	void *m_bfmeWhat;
};

class Rva00512B70FunctorHolder
{
public:
	Rva00512B70FunctorHolder( FunctorBinding binding );
	Rva00512B70FunctorHolder( const Rva00512B70FunctorHolder &other ) throw()
	{
		m_ptr = other.m_ptr;
		if (m_ptr) ++((unsigned int *)m_ptr)[1];
	}
	~Rva00512B70FunctorHolder();

private:
	void *m_ptr;
};

class Rva00512BE0FunctorHolder
{
public:
	Rva00512BE0FunctorHolder( FunctorBinding binding );
	Rva00512BE0FunctorHolder( const Rva00512BE0FunctorHolder &other ) throw()
	{
		m_ptr = other.m_ptr;
		if (m_ptr) ++((unsigned int *)m_ptr)[1];
	}
	~Rva00512BE0FunctorHolder();

private:
	void *m_ptr;
};

class Rva00512C50FunctorHolder
{
public:
	Rva00512C50FunctorHolder( FunctorBinding binding );
	Rva00512C50FunctorHolder( const Rva00512C50FunctorHolder &other ) throw()
	{
		m_ptr = other.m_ptr;
		if (m_ptr) ++((unsigned int *)m_ptr)[1];
	}
	~Rva00512C50FunctorHolder();

private:
	void *m_ptr;
};

extern void j_0003df14();
extern void j_000338ed();
extern void j_0000acfe();
typedef void (*InitRegistrar)(const AsciiString &, Rva00512B70FunctorHolder);

// Already identified registrar routes: the cdecl InitGadgets entry 3DF14,
// and S4Owner methods 338ED/ACFE, whose pointer-sized holder ABI is shared
// by these three concrete, already matched wrapper constructor types.
class __single_inheritance InGameChatRegistry
{
public:
 typedef void (InGameChatRegistry::*PlainRegistrar)(const AsciiString &, Rva00512BE0FunctorHolder);
 typedef void (InGameChatRegistry::*ArgRegistrar)(const AsciiString &, void *, Rva00512C50FunctorHolder);
 static __forceinline PlainRegistrar plainRegistrar()
 {
  union Bits { PlainRegistrar member; void (*code)(); } bits;
  bits.code=j_000338ed; return bits.member;
 }
 static __forceinline ArgRegistrar argRegistrar()
 {
  union Bits { ArgRegistrar member; void (*code)(); } bits;
  bits.code=j_0000acfe; return bits.member;
 }
};

// InGameChat.apt, retail 0x001050C0, object 0x2A4 bytes.
class __multiple_inheritance BfmeAptScreenInGameChat
	: public _bfme_AptGameWindow
{
public:
	BfmeAptScreenInGameChat( void *context );
	virtual ~BfmeAptScreenInGameChat();
	virtual int aptSlot1(unsigned int, unsigned int, unsigned int);
	virtual int aptSlot2(unsigned int, unsigned int, unsigned int);
	virtual int aptSlot3(unsigned int);
	virtual int aptSlot4(unsigned int, unsigned int);
	virtual int aptSlot5();
	virtual int aptSlot6();
	virtual void *aptSlot7();
	virtual int aptSlot8();
	virtual int aptSlot9();
	virtual bool aptSlot10();
	virtual bool aptSlot11();
	virtual void aptSlot12();
	virtual void aptSlot13();
private:
	int m_field258;
	char m_padding25C[ 4 ];
	int m_field260;
	int m_field264;
	int m_field268;
	char m_padding26C[ 4 ];
	InGameChatSlot m_firstControl;
	InGameChatSlot m_secondControl;
	bool m_field290;
	bool m_field291;
	bool m_field292;
	bool m_field293;
	bool m_field294;
	bool m_field295;
	char m_padding296[ 2 ];
	int m_field298;
	int m_field29C;
	int m_field2A0;
};

typedef char ChatObjectSize[(sizeof(BfmeAptScreenInGameChat)==0x2A4)?1:-1];
typedef char ChatAptBaseSize[(sizeof(_bfme_AptGameWindow)==0x258)?1:-1];
typedef char ChatControlSize[(sizeof(InGameChatSlot)==0x10)?1:-1];
union InGameChatMethodBits { FunctorMethod member; unsigned int words[2]; };
extern void j_00010280();
extern void j_00014231();
extern void j_00019d3f();
extern void j_0001b40a();
extern void j_00040d90();
extern void j_0001ce63();
extern void j_00018dd1();
extern void j_0002263d();

BfmeAptScreenInGameChat::BfmeAptScreenInGameChat( void *context )
	: _bfme_AptGameWindow( context ), m_field258(0), m_field260(0), m_field264(0), m_field268(0)
{
	InGameChatRegistry *registry =
		(InGameChatRegistry *)( (char *)this + 0x218 );

	m_field290 = true;
	m_field291 = false;
	m_field292 = true;
	m_field293 = false;
	m_field294 = true;
	m_field295 = false;
	m_field298 = 0;
	m_field29C = 0;
	m_field2A0 = 0;

	if( g_Rva005127A0InGameChat == 0 )
	{
		g_Rva005127A0InGameChat = (Rva005127A0InGameChat *)this;

		{
			InGameChatMethodBits callback;
			callback.words[0]=(unsigned int)j_00010280;
			callback.words[1]=0;
			AsciiString name( "AptInGameChat::InitGadgets" );
			((InitRegistrar)j_0003df14)( name,
				Rva00512B70FunctorHolder( FunctorBinding( callback.member, (FunctorTarget *)this ) ) );
		}

		{
			InGameChatMethodBits callback;
			callback.words[0]=(unsigned int)j_00014231;
			callback.words[1]=0;
			AsciiString name( "AptInGameChat::OnInitialized" );
			(registry->*InGameChatRegistry::plainRegistrar())( name,
				Rva00512BE0FunctorHolder( FunctorBinding( callback.member, (FunctorTarget *)this ) ) );
		}

		{
			InGameChatMethodBits callback;
			callback.words[0]=(unsigned int)j_00019d3f;
			callback.words[1]=0;
			AsciiString name( "AptInGameChat::OnClosed" );
			(registry->*InGameChatRegistry::plainRegistrar())( name,
				Rva00512BE0FunctorHolder( FunctorBinding( callback.member, (FunctorTarget *)this ) ) );
		}

		{
			InGameChatMethodBits callback;
			callback.words[0]=(unsigned int)j_0001b40a;
			callback.words[1]=0;
			AsciiString name( "AptInGameChat::Close" );
			(registry->*InGameChatRegistry::plainRegistrar())( name,
				Rva00512BE0FunctorHolder( FunctorBinding( callback.member, (FunctorTarget *)this ) ) );
		}

		{
			InGameChatMethodBits callback;
			callback.words[0]=(unsigned int)j_00040d90;
			callback.words[1]=0;
			AsciiString name( "AptInGameChat::Send" );
			(registry->*InGameChatRegistry::plainRegistrar())( name,
				Rva00512BE0FunctorHolder( FunctorBinding( callback.member, (FunctorTarget *)this ) ) );
		}

		{
			InGameChatMethodBits callback;
			callback.words[0]=(unsigned int)j_0001ce63;
			callback.words[1]=0;
			AsciiString name( "AptInGameChat::OnBttnAddFriend" );
			(registry->*InGameChatRegistry::plainRegistrar())( name,
				Rva00512BE0FunctorHolder( FunctorBinding( callback.member, (FunctorTarget *)this ) ) );
		}

		{
			InGameChatMethodBits callback;
			callback.words[0]=(unsigned int)j_00018dd1;
			callback.words[1]=0;
			AsciiString name( "AptInGameChat::OnBttnRemoveFriend" );
			(registry->*InGameChatRegistry::plainRegistrar())( name,
				Rva00512BE0FunctorHolder( FunctorBinding( callback.member, (FunctorTarget *)this ) ) );
		}

		{
			InGameChatMethodBits callback;
			callback.words[0]=(unsigned int)j_0002263d;
			callback.words[1]=0;
			AsciiString name( "ScreenType" );
			(registry->*InGameChatRegistry::argRegistrar())( name, (void *)0,
				Rva00512C50FunctorHolder( FunctorBinding( callback.member, (FunctorTarget *)this ) ) );
		}
	}
}

