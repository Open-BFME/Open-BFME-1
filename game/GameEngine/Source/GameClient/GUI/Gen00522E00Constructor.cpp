// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Gen00522E00 constructor, retail00522E00/955B. Retains the banked class
// name; factory00510AC0 allocates4C and calls its ILT0001B879.
// S4Owner ctor00464B20 and destructor00464E20 independently witness four
// vector<AsciiString> members at4,10,1C,28. The derived destructor005225F0
// clears singleton012F49D0 and releases reference holders at3C and40.
// Retail FuncInfo00E201B4 has11 unwind states: S4Owner, holder3C via004C5790,
// holder40 via0051E6E0, then eight string temporaries. Native initialization
// and member ownership reproduce those lifetimes without synthetic stores.
// Registration00464ED0 takes an AsciiString reference and callee-owned
// four-byte callback holder. Each allocated wrapper is10 hex bytes: virtual
// destructor slot0, invoke slot1, refcount+4, bound receiver+8, single-
// inheritance member pointer+C. Matched wrapper ctor00522570 and invoker
//005225A0 independently prove this layout; the latter forwards the stack int.
// All eight callback addresses are verified ILT routes to matched member
// bodies. Existing lifecycle names and button apply0..3 names are retained;
// the address-bearing owner remains opaque. Vtable00D0692C belongs to the
// wrapper; primary00D06938 is independently installed by destructor005225F0.

#include "ascii_string.h"
#include <vector>
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }

class __single_inheritance Gen00522E00;
typedef void (Gen00522E00::*Rva00522E00Callback)(int);

struct Rva00522E00FunctorBinding
{
	Rva00522E00FunctorBinding( Gen00522E00 *target, Rva00522E00Callback method )
		: m_target( target ), m_method( method ) {}

	Gen00522E00 *m_target;
	Rva00522E00Callback m_method;
};

class FunctorWrapperHead
{
public:
	FunctorWrapperHead() : m_refCount( 0 ) {}

	virtual ~FunctorWrapperHead();
	virtual void anchor(int value);

	unsigned int m_refCount;
};

class Rva00522E00FunctorWrapper : public FunctorWrapperHead
{
public:
	virtual ~Rva00522E00FunctorWrapper();
	virtual void anchor(int value);
	Rva00522E00FunctorWrapper( const Rva00522E00FunctorBinding &binding )
		: m_binding( binding ) {}

	Rva00522E00FunctorBinding m_binding;
};

class Rva00522E00FunctorHolder
{
public:
	__forceinline Rva00522E00FunctorHolder( Rva00522E00FunctorBinding binding )
	{
		m_ptr = new Rva00522E00FunctorWrapper( binding );
		if( m_ptr != 0 )
			++m_ptr->m_refCount;
	}

	~Rva00522E00FunctorHolder();
	Rva00522E00FunctorWrapper *m_ptr;
};

// Four 12-byte string vectors are independently witnessed by the matched
// S4Owner destructor00464E20 and constructor00464B20.
class S4Owner
{
public:
 S4Owner() {}
 virtual ~S4Owner();
private:
 std::vector<AsciiString> m_vec0, m_vec1, m_vec2, m_vec3;
};

class Rva00522E00RefPtr3C
{
public:
	Rva00522E00RefPtr3C() : m_ptr(0) {}
	~Rva00522E00RefPtr3C();

	void *m_ptr;
};

class Rva00522E00RefPtr40
{
public:
	Rva00522E00RefPtr40() : m_ptr(0) {}
	~Rva00522E00RefPtr40();

	void *m_ptr;
};

extern Gen00522E00 *g_bfmeThingCB;			// retail 0x012F49D0

class Gen00522E00 : public S4Owner
{
public:
	Gen00522E00();
	virtual ~Gen00522E00();
	void apply0(int); void apply1(int); void apply2(int); void apply3(int);
	void messageBoxShowing(int); void messageBoxShown(int);
	void messageBoxHiding(int); void messageBoxHidden(int);

	void showAptScreen( const AsciiString &name, Rva00522E00FunctorHolder callback );

private:
	int m_34;
	int m_38;
	Rva00522E00RefPtr3C m_3c;
	Rva00522E00RefPtr40 m_40;
	int m_44;
	bool m_48;
	bool m_49;
};

// ??0Gen00522E00@@QAE@XZ
Gen00522E00::Gen00522E00() : m_34(0), m_38(4)
{
	m_44 = -1;
	m_48 = false;
	m_49 = false;
	if( g_bfmeThingCB == 0 )
	{
		g_bfmeThingCB = this;

		{
			AsciiString name( "AptGuiFX::MessageBoxOk" );
			showAptScreen( name, Rva00522E00FunctorBinding( this, &Gen00522E00::apply0 ) );
		}
		{
			AsciiString name( "AptGuiFX::MessageBoxCancel" );
			showAptScreen( name, Rva00522E00FunctorBinding( this, &Gen00522E00::apply1 ) );
		}
		{
			AsciiString name( "AptGuiFX::MessageBoxYes" );
			showAptScreen( name, Rva00522E00FunctorBinding( this, &Gen00522E00::apply2 ) );
		}
		{
			AsciiString name( "AptGuiFX::MessageBoxNo" );
			showAptScreen( name, Rva00522E00FunctorBinding( this, &Gen00522E00::apply3 ) );
		}
		{
			AsciiString name( "AptGuiFX::MessageBoxShowing" );
			showAptScreen( name, Rva00522E00FunctorBinding( this, &Gen00522E00::messageBoxShowing ) );
		}
		{
			AsciiString name( "AptGuiFX::MessageBoxShown" );
			showAptScreen( name, Rva00522E00FunctorBinding( this, &Gen00522E00::messageBoxShown ) );
		}
		{
			AsciiString name( "AptGuiFX::MessageBoxHiding" );
			showAptScreen( name, Rva00522E00FunctorBinding( this, &Gen00522E00::messageBoxHiding ) );
		}
		{
			AsciiString name( "AptGuiFX::MessageBoxHidden" );
			showAptScreen( name, Rva00522E00FunctorBinding( this, &Gen00522E00::messageBoxHidden ) );
		}
	}
}
