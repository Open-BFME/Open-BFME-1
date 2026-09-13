// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// HordeContain's destructor, lifted from its MASM dump to C++.
//
// It tails into the same base destructor at 0x0003FF49 as SiegeEngineContain,
// so it stands on the same base: OpenContain's nine vptrs (0x00, 0x0C, 0x10,
// 0x20, 0x24, 0x28, 0x2C, 0x30, 0x34), a tenth at 0xD4, and the base ending at
// 0xE4 -- the split SiegeEngineContainDestructorThunk.cpp establishes. Where
// SiegeEngineContain puts a member at 0xE4, HordeContain puts an eleventh
// polymorphic base there, then 0x2C bytes of data before its members.
//
// Eight members, destroyed in reverse declaration order, unwind states 7..0:
//
//   0x114  _STL::set<4-byte class>            thunk 0x0001FE2E -> 0x000EF440
//   0x120  _STL::map<int, 4-byte pod>         thunk 0x0001311A -> 0x00223550
//   0x12C  _STL::vector<16-byte pod>          inlined (sar 4 / shl 4)
//   0x138  _STL::list<int>                    thunk 0x000383CF -> 0x0020ACD0
//   0x144  _STL::map<int, 16-byte class>      thunk 0x000350A8 -> 0x0023ABB0
//   0x1A8  _STL::map<int, 4-byte pod>         thunk 0x0001311A -> 0x00223550
//   0x1C0  _STL::vector<int>                  inlined (sar 2 / shl 2)
//   0x1D8  _STL::vector<28-byte pod>          inlined (imul 0x1C)
//
// The three vectors hold trivially destructible elements, so retail destroys
// them inline and the element size is the only thing the bytes pin -- 16, 4 and
// 28. The class payloads are spelled the way Code/gen_small/tgrid_124.cpp and
// tgrid_107-ish spell those instantiations, so each emitted _Rb_tree destructor
// mangles to the name the ledger already carries at its address.
//
// The list at 0x138 reaches _List_base<int>::~_List_base through a third COMDAT
// copy at 0x0020ACD0; the 0x000CEBD0 and 0x000E5E70 copies were already pinned,
// so this adds the thunk for that one.

#include <list>
#include <map>
#include <set>
#include <vector>

// payload spellings from Code/gen_small/tgrid_*.cpp
struct Gen_t_000ef440_k4 { int a[1]; Gen_t_000ef440_k4(); Gen_t_000ef440_k4(const Gen_t_000ef440_k4&); ~Gen_t_000ef440_k4(); Gen_t_000ef440_k4& operator=(const Gen_t_000ef440_k4&); };
bool operator==(const Gen_t_000ef440_k4&, const Gen_t_000ef440_k4&);
bool operator<(const Gen_t_000ef440_k4&, const Gen_t_000ef440_k4&);
struct Gen_t_00223550_p4pod { int a[1]; };
bool operator==(const Gen_t_00223550_p4pod&, const Gen_t_00223550_p4pod&);
bool operator<(const Gen_t_00223550_p4pod&, const Gen_t_00223550_p4pod&);
struct Gen_t_0023abb0_p16cd { int a[4]; Gen_t_0023abb0_p16cd(); Gen_t_0023abb0_p16cd(const Gen_t_0023abb0_p16cd&); ~Gen_t_0023abb0_p16cd(); Gen_t_0023abb0_p16cd& operator=(const Gen_t_0023abb0_p16cd&); };
bool operator==(const Gen_t_0023abb0_p16cd&, const Gen_t_0023abb0_p16cd&);
bool operator<(const Gen_t_0023abb0_p16cd&, const Gen_t_0023abb0_p16cd&);

// vector elements: trivially destructible, so only their size reaches the bytes
struct Gen_p16pod { int a[4]; };
struct Gen_p28pod { int a[7]; };

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

class __declspec(novtable) SiegeEngineContainBase
	: public OpenContain,
	  public SiegeEngineContainTenthBase		///< vptr at 0xD4
{
public:
	virtual ~SiegeEngineContainBase();

private:
	unsigned char m_pad[0x0c];					///< out to sizeof() == 0xE4
};

// Declared with a plain virtual rather than a virtual destructor: retail runs
// the body at unwind state 7 with the eight members at 6..0, so this subobject
// costs a vptr write and no state.
class HordeContainEleventhBase
{
public:
	virtual void slot();
};

class HordeContain
	: public SiegeEngineContainBase,
	  public HordeContainEleventhBase			///< vptr at 0xE4
{
public:
	virtual ~HordeContain();

private:
	unsigned char m_unreconstructed_e8[0x2c];							///< retail this+0x0E8
	_STL::set<Gen_t_000ef440_k4> m_set;									///< retail this+0x114
	_STL::map<int, Gen_t_00223550_p4pod> m_mapA;						///< retail this+0x120
	_STL::vector<Gen_p16pod> m_vectorA;									///< retail this+0x12C
	_STL::list<int> m_list;												///< retail this+0x138
	unsigned char m_unreconstructed_13c[8];
	_STL::map<int, Gen_t_0023abb0_p16cd> m_mapB;						///< retail this+0x144
	unsigned char m_unreconstructed_150[0x58];
	_STL::map<int, Gen_t_00223550_p4pod> m_mapC;						///< retail this+0x1A8
	unsigned char m_unreconstructed_1b4[0x0c];
	_STL::vector<int> m_vectorB;										///< retail this+0x1C0
	unsigned char m_unreconstructed_1cc[0x0c];
	_STL::vector<Gen_p28pod> m_vectorC;									///< retail this+0x1D8
};

// ??1HordeContain@@UAE@XZ
HordeContain::~HordeContain()
{
}
