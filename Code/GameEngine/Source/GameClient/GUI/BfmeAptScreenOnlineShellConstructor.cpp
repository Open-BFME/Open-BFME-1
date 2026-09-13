// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// OnlineShell constructor, RVA 0x0055D150, full 1060 bytes through ret4 at
// 0x0055D571. Factory createAptScreenOnlineShell (0x00104C40) names the
// constructor. The matched destructor at 0x0055CB50 establishes the +0x218
// secondary view and vector/string members. Registration and image loading
// both belong to the first-instance branch; every instance initializes its
// vector, name, current-screen pointer and OnlineLogin filename.
// The two real polymorphic base views reproduce the EDI secondary pointer.
// By-value temporary holders and the scoped label recover the retail frame.
// stlport
#include <vector>
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

class BfmeAptScreenRef;
extern int g_bfmeFlagMG;

// These are the two by-value holder instantiations used by OnlineShell's
// retail constructor.  Their real constructors are the matched bodies at
// 0x0055CA70 and 0x0055CAE0; keeping the address-derived types here preserves
// the exact wrapper vtables without defining another holder body.
class Rva0055CA70FunctorHolder
{
public:
	Rva0055CA70FunctorHolder( FunctorBinding binding );

	void *m_ptr;
};

class Rva0055CAE0FunctorHolder
{
public:
	Rva0055CAE0FunctorHolder( FunctorBinding binding );

	void *m_ptr;
};

extern void j_000338ed();
extern void j_0000acfe();

// These routes are the already matched AptScreenShow.cpp methods at
// 0x00464ED0 and 0x00464FE0, entered through ILTs 338ED/ACFE. The retail ABI
// consumes one pointer-sized intrusive holder. The explicit four-byte member
// pointer bridge preserves that thiscall ABI with the OnlineShell holder
// specializations, without inventing additional names or pins for the body.
class __single_inheritance ShellCallbackRegistry
{
public:
	typedef void (ShellCallbackRegistry::*PlainRegistrar)(const AsciiString &, Rva0055CA70FunctorHolder);
	typedef void (ShellCallbackRegistry::*ArgRegistrar)(const AsciiString &, void *, Rva0055CAE0FunctorHolder);
	static __forceinline PlainRegistrar plainRegistrar()
	{
		union Bits { PlainRegistrar member; void (*code)(); } bits;
		bits.code = j_000338ed;
		return bits.member;
	}
	static __forceinline ArgRegistrar argRegistrar()
	{
		union Bits { ArgRegistrar member; void (*code)(); } bits;
		bits.code = j_0000acfe;
		return bits.member;
	}
};

class Image;
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Image.h
class ImageCollection
{
public:
	const Image *findImageByName( const AsciiString &name );
};

extern ImageCollection *TheMappedImageCollection;

// OnlineShell.apt, retail 0x0055D150, object 0x280 bytes.  The factory at
// 0x00104C40 is the named caller; this constructor's two vtable views,
// callback names, and ping-image literals independently anchor its identity.
class __multiple_inheritance BfmeAptScreenOnlineShell
	: public _bfme_AptGameWindow
{
public:
	BfmeAptScreenOnlineShell( void *context );
	virtual ~BfmeAptScreenOnlineShell();
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
	bool m_active;
	char m_pad259[3];
	std::vector<BfmeAptScreenRef *> m_refs;
	AsciiString m_name;
	BfmeAptScreenRef *m_current;
	AsciiString m_fileName;
	const Image *m_pingImage03;
	const Image *m_pingImage02;
	const Image *m_pingImage01;
};

extern void j_0002ba1c();
extern void j_0004253c();
extern void j_0000a58d();
extern void j_000074f0();
extern void j_00046402();
extern void j_000384c9();

typedef char ShellBaseSize[(sizeof(BfmeAptScreenBase) == 0x218) ? 1 : -1];
typedef char ShellRegistrySize[(sizeof(S4Owner) == 0x34) ? 1 : -1];
typedef char ShellAptBaseSize[(sizeof(_bfme_AptGameWindow) == 0x258) ? 1 : -1];
typedef char ShellObjectSize[(sizeof(BfmeAptScreenOnlineShell) == 0x280) ? 1 : -1];
typedef char ShellBindingSize[(sizeof(FunctorBinding) == 16) ? 1 : -1];
typedef char ShellHolderSize[(sizeof(Rva0055CA70FunctorHolder) == 4) ? 1 : -1];

union OnlineShellMethodBits
{
	FunctorMethod m_method;
	unsigned int m_words[ 2 ];
};

BfmeAptScreenOnlineShell::BfmeAptScreenOnlineShell( void *context )
	: _bfme_AptGameWindow( context ), m_current( 0 ), m_fileName( "OnlineLogin" )
{
	if( g_bfmeFlagMG == 0 )
	{
		g_bfmeFlagMG = (int)this;
		ShellCallbackRegistry *registry =
			(ShellCallbackRegistry *)( (char *)this + 0x218 );

		{
			OnlineShellMethodBits methodBits;
			methodBits.m_words[ 0 ] = (unsigned int)j_0004253c;
			methodBits.m_words[ 1 ] = 0;
			AsciiString name( "AptOnline::OnInitialized" );
			(registry->*ShellCallbackRegistry::plainRegistrar())( name,
				FunctorBinding( methodBits.m_method, (FunctorTarget *)this ) );
		}

		{
			OnlineShellMethodBits methodBits;
			methodBits.m_words[ 0 ] = (unsigned int)j_0000a58d;
			methodBits.m_words[ 1 ] = 0;
			AsciiString name( "AptOnline::ShellLoadScreen" );
			(registry->*ShellCallbackRegistry::plainRegistrar())( name,
				FunctorBinding( methodBits.m_method, (FunctorTarget *)this ) );
		}

		{
			OnlineShellMethodBits methodBits;
			methodBits.m_words[ 0 ] = (unsigned int)j_000074f0;
			methodBits.m_words[ 1 ] = 0;
			AsciiString name( "AptOnline::ShellUnloadScreen" );
			(registry->*ShellCallbackRegistry::plainRegistrar())( name,
				FunctorBinding( methodBits.m_method, (FunctorTarget *)this ) );
		}

		{
			OnlineShellMethodBits methodBits;
			methodBits.m_words[ 0 ] = (unsigned int)j_00046402;
			methodBits.m_words[ 1 ] = 0;
			AsciiString name( "AptOnline::Options" );
			(registry->*ShellCallbackRegistry::plainRegistrar())( name,
				FunctorBinding( methodBits.m_method, (FunctorTarget *)this ) );
		}

		{
			OnlineShellMethodBits methodBits;
			methodBits.m_words[ 0 ] = (unsigned int)j_000384c9;
			methodBits.m_words[ 1 ] = 0;
			AsciiString name( "AptOnline::ShellExit" );
			(registry->*ShellCallbackRegistry::plainRegistrar())( name,
				FunctorBinding( methodBits.m_method, (FunctorTarget *)this ) );
		}

		{
			OnlineShellMethodBits methodBits;
			methodBits.m_words[ 0 ] = (unsigned int)j_0002ba1c;
			methodBits.m_words[ 1 ] = 0;
			AsciiString name( "OnlineShellStartScreen" );
			(registry->*ShellCallbackRegistry::argRegistrar())( name, (void *)0,
				FunctorBinding( methodBits.m_method, (FunctorTarget *)this ) );
		}

		{
			OnlineShellMethodBits methodBits;
			methodBits.m_words[ 0 ] = (unsigned int)j_0002ba1c;
			methodBits.m_words[ 1 ] = 0;
			AsciiString name( "OnlineAdvMode" );
			(registry->*ShellCallbackRegistry::argRegistrar())( name, (void *)1,
				FunctorBinding( methodBits.m_method, (FunctorTarget *)this ) );
		}

		{
			AsciiString onlineOrNetwork( "APT:OnlineOrNetwork" );
			g_theWindowManager->bfme_setAptText( onlineOrNetwork,
				TheGameText->fetch( "APT:Online", 0 ) );
		}
		m_pingImage03 = TheMappedImageCollection->findImageByName(
			AsciiString( "AptPing03" ) );
		m_pingImage02 = TheMappedImageCollection->findImageByName(
			AsciiString( "AptPing02" ) );
		m_pingImage01 = TheMappedImageCollection->findImageByName(
			AsciiString( "AptPing01" ) );
	}
}
