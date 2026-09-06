// cl: /DNDEBUG /MD /EHsc /O2
//
// Open-BFME5: retail 0x006BCD80, 89 bytes -- the constructor counterpart of
// the already-landed BfmeBaseVUQ-family destructor at 0x006BCE40
// (Rva006BCE40Destructor.cpp, class Rva006BCE40 : public BfmeBaseVUQ,
// vtable 0x0111D024). Reuses that class name and its established +0x4
// member field; the destructor's TU is untouched (this is a separate file).
// 0.852 difflib match to the landed STLport basic_ios(streambuf*) ctor
// (Code/Libraries/Source/WWVegas/WWLib/stlport_basic_ios_streambuf_ctors.cpp)
// gave the initial "zero fields, install vtable, forward args to an
// out-of-line init" shape, but the retail bytes prove no base-class
// constructor call (BfmeBaseVUQ's destructor is inline/empty here, so its
// implicit default constructor is a no-op), a second zeroed pointer field
// at +0x8 not modelled by the destructor, and a real three-argument
// constructor whose args are forwarded unchanged, in order, to a
// still-unconverted callee reached through ILT thunk 0x00044341. Real
// method and parameter names not recovered.

class BfmeBaseVUQ
{
public:
	virtual ~BfmeBaseVUQ() { }
};

class Rva006BCE40 : public BfmeBaseVUQ
{
public:
	Rva006BCE40( void *p1, void *p2, void *p3 );

	void *m_member;   ///< +0x04
	void *m_field8;   ///< +0x08

private:
	// ?initRva006BCD80@Rva006BCE40@@AAEXPAX00@Z -- pinned to ILT thunk 0x00044341
	void initRva006BCD80( void *p1, void *p2, void *p3 );
};

// ??0Rva006BCE40@@QAE@PAX00@Z
Rva006BCE40::Rva006BCE40( void *p1, void *p2, void *p3 )
	: m_member( 0 ), m_field8( 0 )
{
	initRva006BCD80( p1, p2, p3 );
}
