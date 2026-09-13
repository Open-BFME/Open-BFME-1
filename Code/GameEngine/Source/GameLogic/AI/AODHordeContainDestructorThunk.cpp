// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// AODHordeContain's destructor, lifted from its MASM dump to C++.
//
// Its base destructor call lands on 0x0023EF90 = HordeContain::~HordeContain,
// and it restores exactly HordeContain's eleven vptrs (0x00, 0x0C, 0x10, 0x20,
// 0x24, 0x28, 0x2C, 0x30, 0x34, 0xD4, 0xE4) -- it adds no polymorphic base of
// its own, so the modelled base carries all eleven and runs out to 0x224.
//
// Three members, destroyed in reverse declaration order, unwind states 2..0:
//
//   0x224  _STL::vector<24-byte pod>          inlined (imul 0x2AAAAAAB, *24)
//   0x250  60 x 16-byte class                 __ehvec_dtor(ptr, 0x10, 0x3C, dtor)
//   0x614  20 x 24-byte class                 __ehvec_dtor(ptr, 0x18, 0x14, dtor)
//
// The two arrays go through the eh vector destructor iterator, whose argument
// list is the whole specification the bytes give: element size, element count,
// and the element destructor's address. The element classes here are anonymous
// on purpose -- their destructors are declared and never defined, so the pushed
// address stays a DIR32 the comparison masks, exactly as their identity is
// unknown. The vector's elements are trivially destructible, so retail unrolls
// its free inline and only the 24-byte stride reaches the bytes.

#include <vector>

// vector elements: trivially destructible, so only their size reaches the bytes
struct Gen_p24pod { int a[6]; };

// Array elements: non-trivially destructible, identity unknown. Only the size
// and the destructor's address reach the bytes, and the address is masked.
class AODHordeContainElement16
{
public:
	~AODHordeContainElement16();

private:
	unsigned char m_unreconstructed_00[0x10];
};

class AODHordeContainElement24
{
public:
	~AODHordeContainElement24();

private:
	unsigned char m_unreconstructed_00[0x18];
};

class OpenContainPrimaryBase
{
public:
	virtual ~OpenContainPrimaryBase() {}

private:
	unsigned char m_pad[8];
};

template <int Number>
class OpenContainSecondaryBase
{
public:
	virtual ~OpenContainSecondaryBase() {}
};

class OpenContainWideSecondaryBase
{
public:
	virtual ~OpenContainWideSecondaryBase() {}

private:
	unsigned char m_pad[12];
};

class __declspec(novtable) OpenContain
	: public OpenContainPrimaryBase,
	  public OpenContainSecondaryBase<1>,
	  public OpenContainWideSecondaryBase,
	  public OpenContainSecondaryBase<2>,
	  public OpenContainSecondaryBase<3>,
	  public OpenContainSecondaryBase<4>,
	  public OpenContainSecondaryBase<5>,
	  public OpenContainSecondaryBase<6>,
	  public OpenContainSecondaryBase<7>
{
public:
	virtual ~OpenContain() {}

private:
	unsigned char m_pad[0x9c];					///< out to sizeof() == 0xD4
};

class SiegeEngineContainTenthBase
{
public:
	virtual ~SiegeEngineContainTenthBase() {}
};

// Plain virtual rather than a virtual destructor: retail runs the body at
// unwind state 2 with the three members at 2..0, so this subobject costs a vptr
// write and no state.
class HordeContainEleventhBase
{
public:
	virtual void slot();
};

class __declspec(novtable) SiegeEngineContainBase
	: public OpenContain,
	  public SiegeEngineContainTenthBase		///< vptr at 0xD4
{
public:
	virtual ~SiegeEngineContainBase();

private:
	unsigned char m_pad[0x0c];					///< out to sizeof() == 0xE4
};

class __declspec(novtable) HordeContain
	: public SiegeEngineContainBase,
	  public HordeContainEleventhBase			///< vptr at 0xE4
{
public:
	virtual ~HordeContain();

private:
	unsigned char m_pad[0x13c];					///< out to sizeof() == 0x224
};

class AODHordeContain : public HordeContain
{
public:
	virtual ~AODHordeContain();

private:
	_STL::vector<Gen_p24pod> m_vector;									///< retail this+0x224
	unsigned char m_unreconstructed_230[0x20];
	AODHordeContainElement16 m_arrayA[0x3c];							///< retail this+0x250
	unsigned char m_unreconstructed_610[4];
	AODHordeContainElement24 m_arrayB[0x14];							///< retail this+0x614
};

// ??1AODHordeContain@@UAE@XZ
AODHordeContain::~AODHordeContain()
{
}
