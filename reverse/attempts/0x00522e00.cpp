// ??0Gen00522E00@@QAE@XZ
// partial score=0.85 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Gen00522E00 constructor (the AptGuiFX MessageBox screen host), retail
// 0x00522E00, 955 bytes. Zeroes the object, installs the vftable already
// pinned as ??_7Rva005225F0@@6B@ (0x1106938 -- the destructor at 0x005225F0
// installs the same base and is landed as Rva005225F0Destructor.cpp), then
// registers 8 named AptGuiFX callbacks through the same shared APT-screen
// registrar (ILT 0x000338ED) that AptScreenShow.cpp / BfmeAptScreenQuitMenu
// -Constructor.cpp reach: four button events (Ok/Cancel/Yes/No, imm 0..3)
// landing on the m_3C slot the already-landed Rva005222A0NoteCalls.cpp /
// Rva00522300ApplyOne.cpp apply0..apply3 methods forward through, and four
// lifecycle events (Showing/Shown/Hiding/Hidden, imm 0..3) on the m_40 slot
// the already-landed Rva00522470/5224C0/522830 MessageBox.cpp handlers use
// (m_40 is also Gen00522E00::messageBoxShown/Hiding/Hidden's home). Each
// closure is a private 16-byte wrapper (vtable + refcount + this + a raw
// code address) allocated and reference-counted in place as the by-value
// argument to the registrar call -- same "construct temp in the argument
// area" shape as the landed QuitMenu constructor. The stored code address is
// the incremental-link thunk retail took the address of (0x00407F04 etc,
// each already landed as a Code/gen_small j_<rva> stub), not the final
// apply0/apply1/... target, so the four constants are written as the literal
// VAs retail encodes -- the same technique BfmeAptScreenQuitMenuConstructor
// .cpp uses for its hasFocus callback (0x00410B86). g_bfmeThingCB (0x012F49D0,
// already named) gates the whole block: first construction wins, any later
// one skips registration entirely.

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase( const T *text );
	~StringBase();

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	~AsciiString() {}
};

class Gen00522E00;

class FunctorWrapperHead
{
public:
	FunctorWrapperHead() : m_refCount( 0 ) {}

	virtual void anchor();

	volatile unsigned int m_refCount;
};

class Rva00522E00FunctorWrapper : public FunctorWrapperHead
{
public:
	Rva00522E00FunctorWrapper( Gen00522E00 *target, unsigned int method )
		: m_target( target ), m_method( method ) {}

	Gen00522E00 *m_target;
	unsigned int m_method;
};

class Rva00522E00FunctorHolder
{
public:
	Rva00522E00FunctorHolder( Gen00522E00 *target, unsigned int method )
	{
		m_ptr = new Rva00522E00FunctorWrapper( target, method );
		if( m_ptr != 0 )
			++m_ptr->m_refCount;
	}

	Rva00522E00FunctorWrapper * volatile m_ptr;
};

class Gen_dtor_004654c0
{
public:
	virtual ~Gen_dtor_004654c0();
};

extern Gen00522E00 *g_bfmeThingCB;			// retail 0x012F49D0

class Gen00522E00 : public Gen_dtor_004654c0
{
public:
	Gen00522E00();
	virtual ~Gen00522E00();

	void showAptScreen( const AsciiString &name, Rva00522E00FunctorHolder callback );

private:
	int m_04, m_08, m_0c, m_10, m_14, m_18, m_1c, m_20, m_24, m_28, m_2c, m_30, m_34;
	int m_38;
	void *m_3c;
	void *m_40;
	int m_44;
	bool m_48;
	bool m_49;
};

// ??0Gen00522E00@@QAE@XZ
Gen00522E00::Gen00522E00()
	: m_04( 0 ), m_08( 0 ), m_0c( 0 ), m_10( 0 ), m_14( 0 ), m_18( 0 ), m_1c( 0 ),
	  m_20( 0 ), m_24( 0 ), m_28( 0 ), m_2c( 0 ), m_30( 0 ), m_34( 0 ),
	  m_38( 4 ), m_3c( 0 ), m_40( 0 ), m_44( -1 ), m_48( false ), m_49( false )
{
	if( g_bfmeThingCB == 0 )
	{
		g_bfmeThingCB = this;

		{
			AsciiString name( "AptGuiFX::MessageBoxOk" );
			Rva00522E00FunctorHolder callback( this, 0x00407F04 );
			showAptScreen( name, callback );
		}
		{
			AsciiString name( "AptGuiFX::MessageBoxCancel" );
			Rva00522E00FunctorHolder callback( this, 0x00433F5F );
			showAptScreen( name, callback );
		}
		{
			AsciiString name( "AptGuiFX::MessageBoxYes" );
			Rva00522E00FunctorHolder callback( this, 0x0041398A );
			showAptScreen( name, callback );
		}
		{
			AsciiString name( "AptGuiFX::MessageBoxNo" );
			Rva00522E00FunctorHolder callback( this, 0x004365C5 );
			showAptScreen( name, callback );
		}
		{
			AsciiString name( "AptGuiFX::MessageBoxShowing" );
			Rva00522E00FunctorHolder callback( this, 0x00438465 );
			showAptScreen( name, callback );
		}
		{
			AsciiString name( "AptGuiFX::MessageBoxShown" );
			Rva00522E00FunctorHolder callback( this, 0x0042924E );
			showAptScreen( name, callback );
		}
		{
			AsciiString name( "AptGuiFX::MessageBoxHiding" );
			Rva00522E00FunctorHolder callback( this, 0x0042C381 );
			showAptScreen( name, callback );
		}
		{
			AsciiString name( "AptGuiFX::MessageBoxHidden" );
			Rva00522E00FunctorHolder callback( this, 0x00444198 );
			showAptScreen( name, callback );
		}
	}
}
