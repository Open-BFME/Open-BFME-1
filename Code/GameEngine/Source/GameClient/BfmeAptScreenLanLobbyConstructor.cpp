// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x00519F90, 1193 bytes. LanLobby.apt factory and the matched
// destructor at 5199A0 establish the three interfaces at +0/+218/+258,
// Skirmish state at +25C, LAN preferences at +390 and chat hook at +3C0.
// The opaque state extent is 0x134 from both enclosing objects; its matched
// constructor writes through +128 and leaves the final eight bytes untouched.
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
struct UnicodeStringData
{
	unsigned int m_refCount;
	unsigned short m_length;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	static UnicodeString TheEmptyString;

	UnicodeString() : m_data( 0 ) {}
	UnicodeString( const unsigned short *text );
	UnicodeString( const UnicodeString &other )
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
			*(const StringBase<unsigned short> *)&other );
	}
	~UnicodeString();
	void format( UnicodeString format, ... );
	void format( const unsigned short *format, ... );
	void concat( const unsigned short *text, int length );
	void set( const UnicodeString &other )
	{
		((StringBase<unsigned short> *)this)->set(
			*(const StringBase<unsigned short> *)&other );
	}
	void trim()
	{
		((StringBase<unsigned short> *)this)->trim();
	}
	bool isEmpty() const { return !m_data || m_data->m_length == 0; }

private:
	UnicodeStringData *m_data;
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

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09();
	virtual UnicodeString fetch( const char *label, bool *exists = 0 );
};

extern GameTextInterface *TheGameText;

class WindowManager { public: void bfme_setAptText(const AsciiString &name, const UnicodeString &text); };
extern WindowManager *g_theWindowManager;
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


// Actual additional interface table1105690: deleting destructor followed by
// fifteen pure slots. Derived table1105A28 preserves their observed carriers
// and stack widths; placeholder names do not assert original spellings.
class BfmeAptScreenSecondary
{
public:
 virtual ~BfmeAptScreenSecondary() {}
 virtual void *ownerSlot1()=0;
 virtual void ownerSlot2(const UnicodeString &,int)=0;
 virtual bool ownerSlot3(void *,int)=0;
 virtual bool ownerSlot4(void *,int)=0;
 virtual bool ownerSlot5(void *,int)=0;
 virtual bool ownerSlot6(void *,int,int)=0;
 virtual bool ownerSlot7(void *,int)=0;
 virtual bool ownerSlot8(const AsciiString *)=0;
 virtual unsigned char ownerSlot9(int)=0;
 virtual void ownerSlot10(UnicodeString &)=0;
 virtual void ownerSlot11(int)=0;
 virtual bool ownerSlot12()=0;
 virtual void ownerSlot13(int,int)=0;
 virtual void ownerSlot14(bool)=0;
 virtual void ownerSlot15()=0;
};
class Gen00529110Owner;
class SkirmishScreenState
{
public:
 SkirmishScreenState(Gen00529110Owner *,int);
 ~SkirmishScreenState();
private:
 char m_extent[0x134];
};
class LANPreferences
{
public:
 LANPreferences();
 virtual ~LANPreferences();
private:
 char m_extent[0x10];
};
class BfmeThingTC { public: void bfmeBaseTC(); };
// Opaque gadget hook. Existing17B base route479230 initializes the first
// twelve bytes; real table11056DC has deleting-destructor/input/system slots.
// The screen configures the remaining payload after this constructor returns.
class LanLobbyTail
{
public:
 LanLobbyTail()
 {
  ((BfmeThingTC *)this)->bfmeBaseTC();
  m_vptr=(void *)0x011056DC;
 }
 ~LanLobbyTail();
public:
 void *m_vptr; char m_base[8]; int m_value;
 bool m_flag0,m_flag1,m_flag2,m_flag3;
 int m_kind; bool m_flag4; char m_pad[3];
};
class Rva00518B10FunctorHolder
{
public:
 Rva00518B10FunctorHolder(FunctorBinding binding);
 Rva00518B10FunctorHolder(const Rva00518B10FunctorHolder &other) throw() : m_ptr(other.m_ptr)
 { if(m_ptr) ++((unsigned int*)m_ptr)[1]; }
 ~Rva00518B10FunctorHolder();
private:
 void *m_ptr;
};
class Rva00518B80FunctorHolder
{
public:
 Rva00518B80FunctorHolder(FunctorBinding binding);
 Rva00518B80FunctorHolder(const Rva00518B80FunctorHolder &other) throw() : m_ptr(other.m_ptr)
 { if(m_ptr) ++((unsigned int*)m_ptr)[1]; }
 ~Rva00518B80FunctorHolder();
private:
 void *m_ptr;
};
extern void j_000338ed();
extern void j_0003df14();
extern void j_0001d9cb();
typedef void (*LanInitRegistrar)(const AsciiString &,Rva00518B80FunctorHolder);
class __single_inheritance LanRegistry
{
public:
 typedef void (LanRegistry::*Plain)(const AsciiString &,Rva00518B10FunctorHolder);
 static __forceinline Plain registrar()
 { union Bits { Plain member; void(*code)(); } bits; bits.code=j_000338ed;return bits.member; }
};
class BfmeAptScreenLanLobby :public _bfme_AptGameWindow, public BfmeAptScreenSecondary
{
public:
 BfmeAptScreenLanLobby(void *context);
 virtual ~BfmeAptScreenLanLobby();
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
 virtual void *ownerSlot1();
 virtual void ownerSlot2(const UnicodeString &,int);
 virtual bool ownerSlot3(void *,int);
 virtual bool ownerSlot4(void *,int);
 virtual bool ownerSlot5(void *,int);
 virtual bool ownerSlot6(void *,int,int);
 virtual bool ownerSlot7(void *,int);
 virtual bool ownerSlot8(const AsciiString *);
 virtual unsigned char ownerSlot9(int);
 virtual void ownerSlot10(UnicodeString &);
 virtual void ownerSlot11(int);
 virtual bool ownerSlot12();
 virtual void ownerSlot13(int,int);
 virtual void ownerSlot14(bool);
 virtual void ownerSlot15();

private:
 SkirmishScreenState m_state;
 LANPreferences m_prefs;
 UnicodeString m_name;
 int m_3A8,m_3AC,m_3B0,m_3B4,m_3B8,m_3BC;
 LanLobbyTail m_tail;
};
union LanMethodBits { FunctorMethod member; unsigned int words[2]; };
extern void j_00017094();
extern void j_0000a588();
extern void j_0000ccca();
extern void j_000344b4();
extern void j_0003c547();
extern void j_00031818();
extern void j_00043734();
extern void j_0002cf84();
extern void j_0001acee();
typedef char LanSize[(sizeof(BfmeAptScreenLanLobby)==0x3DC)?1:-1];
BfmeAptScreenLanLobby::BfmeAptScreenLanLobby(void *context)
 :_bfme_AptGameWindow(context),m_state((Gen00529110Owner *)(BfmeAptScreenSecondary *)this,0),
 m_3A8(0),m_3AC(0),m_3B0(0),m_3B4(0),m_3B8(0),m_3BC(0)
{
 m_tail.m_value=0;
 m_tail.m_flag0=false; m_tail.m_flag1=false; m_tail.m_flag2=false; m_tail.m_flag3=false;
 m_tail.m_kind=2; m_tail.m_flag4=false;
 if(*(BfmeAptScreenLanLobby **)0x012F4998==0)
 {
  *(BfmeAptScreenLanLobby **)0x012F4998=this;
  LanRegistry *registry=(LanRegistry *)((char *)this+0x218);
  {
   LanMethodBits callback;callback.words[0]=(unsigned int)j_00017094;callback.words[1]=0;
   AsciiString name("AptLanLobby::OnInitialized");
   (registry->*LanRegistry::registrar())(name,Rva00518B10FunctorHolder(FunctorBinding(callback.member,(FunctorTarget *)this)));
  }
  {
   LanMethodBits callback;callback.words[0]=(unsigned int)j_0000a588;callback.words[1]=0;
   AsciiString name("AptLanLobby::Cancel");
   (registry->*LanRegistry::registrar())(name,Rva00518B10FunctorHolder(FunctorBinding(callback.member,(FunctorTarget *)this)));
  }
  {
   LanMethodBits callback;callback.words[0]=(unsigned int)j_0000ccca;callback.words[1]=0;
   AsciiString name("AptLanLobby::Exit");
   (registry->*LanRegistry::registrar())(name,Rva00518B10FunctorHolder(FunctorBinding(callback.member,(FunctorTarget *)this)));
  }
  {
   LanMethodBits callback;callback.words[0]=(unsigned int)j_000344b4;callback.words[1]=0;
   AsciiString name("AptLanLobby::StartGame");
   (registry->*LanRegistry::registrar())(name,Rva00518B10FunctorHolder(FunctorBinding(callback.member,(FunctorTarget *)this)));
  }
  {
   LanMethodBits callback;callback.words[0]=(unsigned int)j_0003c547;callback.words[1]=0;
   AsciiString name("AptLanLobby::CreateGame");
   (registry->*LanRegistry::registrar())(name,Rva00518B10FunctorHolder(FunctorBinding(callback.member,(FunctorTarget *)this)));
  }
  {
   LanMethodBits callback;callback.words[0]=(unsigned int)j_00031818;callback.words[1]=0;
   AsciiString name("AptLanLobby::JoinGameButtonPressed");
   (registry->*LanRegistry::registrar())(name,Rva00518B10FunctorHolder(FunctorBinding(callback.member,(FunctorTarget *)this)));
  }
  {
   LanMethodBits callback;callback.words[0]=(unsigned int)j_00043734;callback.words[1]=0;
   AsciiString name("AptLanLobby::Chat::OnBttnEnterText");
   (registry->*LanRegistry::registrar())(name,Rva00518B10FunctorHolder(FunctorBinding(callback.member,(FunctorTarget *)this)));
  }
  {
   LanMethodBits callback;callback.words[0]=(unsigned int)j_0002cf84;callback.words[1]=0;
   AsciiString name("AptLanLobby::Options");
   (registry->*LanRegistry::registrar())(name,Rva00518B10FunctorHolder(FunctorBinding(callback.member,(FunctorTarget *)this)));
  }
  {
   LanMethodBits callback;callback.words[0]=(unsigned int)j_0001acee;callback.words[1]=0;
   AsciiString name("AptLanLobby::InitGadgets");
   ((LanInitRegistrar)j_0003df14)(name,Rva00518B80FunctorHolder(FunctorBinding(callback.member,(FunctorTarget *)this)));
  }
  ((void(__fastcall *)(BfmeAptScreenLanLobby *))j_0001d9cb)(this);
  {
   AsciiString name("APT:OnlineOrNetwork");
   g_theWindowManager->bfme_setAptText(name,TheGameText->fetch("APT:Network"));
  }
 }
}
