// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x00563370, full 1073 bytes. Named factory 104CC0 and destructor
// 55E320 prove this is Options.apt. True primary/registry base ownership keeps
// the secondary view live through callback registration. OptionPreferences
// occupies 0x14 bytes at +260; the UserPreferences base owns a filename at +10.
// The tail resets the observed global at 12F4AE4 after destroying the label
// and its argument copy, while the returned version string remains alive.
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

#include <cstring>
// Existing legacy pin spelling; this constructor publishes the Options
// singleton in the actual slot at 0x012F4AD4.
extern void *g_quitMenuLayout;

class OptionPreferences
{
public:
	OptionPreferences();
	virtual ~OptionPreferences();

private:
	char m_unmodelled[ 0x10 ];
};

// ABI-compatible view of the already matched version-text result. The
// existing BfmeVersionAL body at AED00 returns the same four-byte wide string;
// the forwarding lifetime operations below retain its actual StringBase ABI.
class UnicodeStringAL : public UnicodeString
{
public:
 UnicodeStringAL(const UnicodeStringAL &other) : UnicodeString(other) {}
 ~UnicodeStringAL() {}
};
class BfmeVersionAL
{
public:
 UnicodeStringAL bfmeVersionTextAL();
};

class Rva0055F140FunctorHolder
{
public:
	Rva0055F140FunctorHolder( FunctorBinding binding );
	Rva0055F140FunctorHolder( const Rva0055F140FunctorHolder &other ) throw()
	{
		m_ptr = other.m_ptr;
		if (m_ptr) ++((unsigned int *)m_ptr)[1];
	}
	~Rva0055F140FunctorHolder();

private:
	void *m_ptr;
};

class Rva0055F1B0FunctorHolder
{
public:
	Rva0055F1B0FunctorHolder( FunctorBinding binding );
	Rva0055F1B0FunctorHolder( const Rva0055F1B0FunctorHolder &other ) throw()
	{
		m_ptr = other.m_ptr;
		if (m_ptr) ++((unsigned int *)m_ptr)[1];
	}
	~Rva0055F1B0FunctorHolder();

private:
	void *m_ptr;
};

extern void j_000338ed();
extern void j_0003df14();
typedef void (*OptionsInitRegistrar)(const AsciiString &, Rva0055F1B0FunctorHolder);
// Existing common registrar routes 338ED -> 464ED0 and 3DF14 -> 4628E0
// consume these pointer-sized intrusive holders with the same retail ABI.
class __single_inheritance OptionsRegistry
{
public:
 typedef void (OptionsRegistry::*PlainRegistrar)(const AsciiString &, Rva0055F140FunctorHolder);
 static __forceinline PlainRegistrar plainRegistrar()
 {
  union Bits { PlainRegistrar member; void (*code)(); } bits;
  bits.code=j_000338ed; return bits.member;
 }
};

// Options.apt, retail 0x00104CC0, object 0x310 bytes.
class __multiple_inheritance BfmeAptScreenOptions
	: public _bfme_AptGameWindow
{
public:
	BfmeAptScreenOptions( void *context );
	virtual ~BfmeAptScreenOptions();
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
	int m_field25C;
	OptionPreferences m_options;
	int m_fields274[ 4 ];
	int m_fields284[ 5 ];
	int m_fields298;
	int m_fields29C[ 2 ];
	int m_fields2A4;
	int m_fields2A8[ 24 ];
	bool m_field308;
	int m_field30C;
};

extern void j_00009197();
extern void j_00012544();
extern void j_00007d0b();
extern void j_0003d811();
extern void j_00032768();
extern void j_0002b33c();
union OptionsMethodBits { FunctorMethod member; unsigned int words[2]; };

BfmeAptScreenOptions::BfmeAptScreenOptions( void *context )
	: _bfme_AptGameWindow( context ), m_field258(0), m_field25C(0)
{
	memset( m_fields274, 0, sizeof( m_fields274 ) );
	m_fields284[ 0 ] = 0;
	m_fields284[ 1 ] = 0;
	m_fields284[ 2 ] = 0;
	m_fields284[ 3 ] = 0;
	m_fields284[ 4 ] = 0;
	m_fields29C[ 0 ] = 0;
	m_fields29C[ 1 ] = 0;
	m_fields2A8[ 0 ] = 0;
	m_fields2A8[ 1 ] = 0;
	m_fields2A8[ 2 ] = 0;
	m_fields2A8[ 3 ] = 0;
	m_fields2A8[ 4 ] = 0;
	m_fields2A8[ 5 ] = 0;
	m_fields2A8[ 6 ] = 0;
	m_fields2A8[ 7 ] = 0;
	m_fields2A8[ 8 ] = 0;
	m_fields2A8[ 9 ] = 0;
	m_fields2A8[ 10 ] = 0;
	m_fields2A8[ 11 ] = 0;
	m_fields2A8[ 12 ] = 0;
	m_fields2A8[ 13 ] = 0;
	m_fields2A8[ 14 ] = 0;
	m_fields2A8[ 15 ] = 0;
	m_fields2A8[ 16 ] = 0;
	m_fields2A8[ 17 ] = 0;
	m_fields2A8[ 18 ] = 0;
	m_fields2A8[ 19 ] = 0;
	m_fields2A8[ 20 ] = 0;
	m_fields2A8[ 21 ] = 0;
	m_fields2A8[ 22 ] = 0;
	m_fields2A8[ 23 ] = 0;
	m_field308 = false;
	m_field30C = -1;

	if( g_quitMenuLayout == 0 )
	{
		g_quitMenuLayout = this;
		OptionsRegistry *registry =
			(OptionsRegistry *)( (char *)this + 0x218 );

		{
			OptionsMethodBits callback;
			callback.words[0]=(unsigned int)j_00009197;
			callback.words[1]=0;
			AsciiString name( "AptOptions::OnInitialized" );
			(registry->*OptionsRegistry::plainRegistrar())( name,
				Rva0055F140FunctorHolder( FunctorBinding( callback.member, (FunctorTarget *)this ) ) );
		}

		{
			OptionsMethodBits callback;
			callback.words[0]=(unsigned int)j_00012544;
			callback.words[1]=0;
			AsciiString name( "AptOptions::Save" );
			(registry->*OptionsRegistry::plainRegistrar())( name,
				Rva0055F140FunctorHolder( FunctorBinding( callback.member, (FunctorTarget *)this ) ) );
		}

		{
			OptionsMethodBits callback;
			callback.words[0]=(unsigned int)j_00007d0b;
			callback.words[1]=0;
			AsciiString name( "AptOptions::Reset" );
			(registry->*OptionsRegistry::plainRegistrar())( name,
				Rva0055F140FunctorHolder( FunctorBinding( callback.member, (FunctorTarget *)this ) ) );
		}

		{
			OptionsMethodBits callback;
			callback.words[0]=(unsigned int)j_0003d811;
			callback.words[1]=0;
			AsciiString name( "AptOptions::Cancel" );
			(registry->*OptionsRegistry::plainRegistrar())( name,
				Rva0055F140FunctorHolder( FunctorBinding( callback.member, (FunctorTarget *)this ) ) );
		}

		{
			OptionsMethodBits callback;
			callback.words[0]=(unsigned int)j_00032768;
			callback.words[1]=0;
			AsciiString name( "AptOptions::RefreshNat" );
			(registry->*OptionsRegistry::plainRegistrar())( name,
				Rva0055F140FunctorHolder( FunctorBinding( callback.member, (FunctorTarget *)this ) ) );
		}

		{
			OptionsMethodBits callback;
			callback.words[0]=(unsigned int)j_0002b33c;
			callback.words[1]=0;
			AsciiString name( "AptOptions::InitGadgets" );
			((OptionsInitRegistrar)j_0003df14)( name,
				Rva0055F1B0FunctorHolder( FunctorBinding( callback.member, (FunctorTarget *)this ) ) );
		}

		UnicodeStringAL version = (*(BfmeVersionAL **)0x012ED644)->bfmeVersionTextAL();
		{
			AsciiString versionName( "APT:VersionNum" );
			g_theWindowManager->bfme_setAptText( versionName, UnicodeString( version ) );
		}
		*(int *)0x012F4AE4 = 0;
	}
}


typedef char OptionsObjectSize[(sizeof(BfmeAptScreenOptions)==0x310)?1:-1];
