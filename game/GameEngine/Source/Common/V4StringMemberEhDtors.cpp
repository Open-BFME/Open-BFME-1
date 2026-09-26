// stlport
#include <set>
#include <vector>

// Six destructors with an EH frame whose entire body is calls into the string
// helper at 0x00887940 and whose members are then destroyed by it as well.
//
// WHAT 0x00887940 IS.  The ledger already matches that body as
// StringBase<char>::releaseBuffer -- and, at the same address, as the
// destructors of a dozen classes: releasing the buffer IS the destructor, and
// COMDAT folding left one copy.  So a call to it inside a destructor's BODY is a
// source-level "drop the contents" call on a member that is destroyed again a
// moment later, and both spellings compile to the same five bytes.  That is why
// the class below carries both a `release()` and a destructor, and why both are
// pinned to the one address.
//
// THE EH STATE INDEX READS OUT THE MEMBER COUNT.  MSVC stores the state before
// each step: the body runs at the state that means "all members alive" -- N-1
// for N members -- and each member destruction drops it by one, ending at -1.
//
//   0x003B8450  state 2, then 1, 0, -1: THREE members, and three body calls
//               ahead of them.  Their receivers are +4, +0xC, +8 in the body and
//               +0xC, +8, +4 in the destruction run.  Reverse declaration order
//               fixes the members as +4, +8, +0xC; the BODY order is source
//               order, so the body drops the first, the third and the second, in
//               that order.  It opens with a vftable store at offset 0, so this
//               class is polymorphic.
//   0x003B8710  state 0, then -1: ONE member, at offset 0, dropped once in the
//               body and destroyed after.  No vftable store, so no vptr.
//   0x003BA580  state 0, then -1: TWO subobjects and NO body call -- the two
//               calls ARE the destruction run, +8 first and +4 second, so the
//               members are declared +4 then +8.  The one at +8 is destroyed by
//               a different callee entirely.  The vftable store at offset 0 puts
//               a vptr in front of both.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address; the callee
// pins are address-derived and additive.

// Four bytes wide, and the member offsets say so: the three members of
// 0x003B8450 sit at +4, +8 and +0xC, and 0x003BA580's second subobject sits at
// +8 behind one of these.  A string that releases a buffer holds a pointer.
class Mem00887940
{
public:
	void release();
	~Mem00887940();
	char * m_buffer;
};

// The element payload is twenty bytes: the string-like member at +0, a
// four-byte scalar at +4, and the twelve-byte STLport tree at +8.  The vector
// destructor below walks this payload in 0x14 steps, calling the two non-trivial
// member destructors in declaration order.
struct Mem003BB060Element
{
	Mem00887940   m_at00;
	char          m_pad04[ 0x4 ];
	_STL::set< int > m_at08;
};
typedef char Mem003BB060ElementMustBe20[ sizeof( Mem003BB060Element ) == 0x14 ? 1 : -1 ];

// Sixteen bytes wide: 0x003BA500 destroys one of these at +0xC and the next
// subobject it destroys sits at +0x1C.  That is an upper bound, not a
// measurement -- anything between them that needs no destructor is invisible --
// so the padding is spelled as part of this class rather than around it.
class Mem000658A0
{
public:
	~Mem000658A0();
	char m_at00[ 0x10 ];
};

class Mem003AB460
{
public:
	~Mem003AB460();
	char m_at00[ 0x8 ];
};

typedef _STL::vector< Mem003BB060Element > Mem003BB060;

class Inner01073744
{
public:
	virtual ~Inner01073744() {}
};

class Rva003B8450
{
public:
	virtual void handle();
	~Rva003B8450();
	Mem00887940 m_at04;
	Mem00887940 m_at08;
	Mem00887940 m_at0C;
};
Rva003B8450::~Rva003B8450()
{
	m_at04.release();
	m_at0C.release();
	m_at08.release();
}

class Rva003B8710
{
public:
	~Rva003B8710();
	Mem00887940 m_at00;
};
Rva003B8710::~Rva003B8710()
{
	m_at00.release();
}

class Rva003BA580
{
public:
	virtual void handle();
	~Rva003BA580();
	Mem00887940 m_at04;
	Mem000658A0 m_at08;
};
Rva003BA580::~Rva003BA580()
{
}

class Rva003BA500
{
public:
	virtual void handle();
	~Rva003BA500();
	Mem00887940 m_at04;
	char        m_pad08[ 0x4 ];
	Mem000658A0 m_at0C;
	Mem00887940 m_at1C;
};
Rva003BA500::~Rva003BA500()
{
}

class Rva003BC170 : public Inner01073744
{
public:
	virtual void handle();
	~Rva003BC170();
	char        m_pad04[ 0x8 ];
	Mem00887940 m_at0C;
};
Rva003BC170::~Rva003BC170()
{
	m_at0C.release();
}

class GenBase003BB1E0
{
public:
	virtual void handle();
	~GenBase003BB1E0();
	void         clear();
	Mem003AB460  m_at04;
	char         m_pad0C[ 0x8 ];
	Mem003BB060  m_at14;
};
GenBase003BB1E0::~GenBase003BB1E0()
{
	clear();
}
