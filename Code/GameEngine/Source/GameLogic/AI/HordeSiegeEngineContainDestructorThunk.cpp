// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// HordeSiegeEngineContain's destructor, lifted from its MASM dump to C++.
//
// The retail body is the ordinary compiler-generated shape: restore this
// object's ten subobject vptrs, run the three container members in reverse
// declaration order under an SEH funclet apiece, then tail into the base
// destructor. Nothing here is hand-written code, so the whole job is spelling
// the layout the compiler must see.
//
// The first nine vptrs sit at 0x00, 0x0C, 0x10, 0x20, 0x24, 0x28, 0x2C, 0x30
// and 0x34 -- the same OpenContain subobject group that
// GarrisonContainDestructorThunk.cpp already models, reused verbatim. A tenth
// lands at 0xD4, so a further polymorphic base follows OpenContain's 0xD4 bytes.
//
// SiegeEngineContain's destructor next door tails into the SAME base destructor
// at 0x0003FF49 and puts its own first member at 0x0E4, which is what fixes the
// split: the shared base ends at 0x0E4, and the eight bytes before this class's
// first member are its own.
//
// The members are read off the destructor's own call sites:
//
//   0x0EC  _STL::list<int>                         thunk 0x0000E68D -> 0x000CEBD0
//   0x0F8  _STL::map<int, 4-byte pod>              thunk 0x0001311A -> 0x00223550
//   0x104  _STL::list<int>                         thunk 0x00013449 -> 0x000E5E70
//
// The map's payload is spelled the way Code/gen_small/tgrid_108.cpp spells that
// instantiation, so the emitted _Rb_tree destructor mangles to the name the
// ledger already carries at 0x00223550. The two list members are the same
// _List_base<int> destructor reached through two different COMDAT copies; only
// the 0x00013449 copy was pinned, so this adds the 0x0000E68D one.

#include <list>
#include <map>

// 0x00223550 tree_int_p4pod -- payload spelling from Code/gen_small/tgrid_108.cpp
struct Gen_t_00223550_p4pod { int a[1]; };
bool operator==(const Gen_t_00223550_p4pod&, const Gen_t_00223550_p4pod&);
bool operator<(const Gen_t_00223550_p4pod&, const Gen_t_00223550_p4pod&);

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
	  public SiegeEngineContainTenthBase	///< vptr at 0xD4
{
public:
	virtual ~SiegeEngineContainBase();

private:
	unsigned char m_pad[0x0c];					///< out to sizeof() == 0xE4
};

class HordeSiegeEngineContain : public SiegeEngineContainBase
{
public:
	virtual ~HordeSiegeEngineContain();

private:
	unsigned char m_unreconstructed_e4[8];								///< retail this+0x0E4
	_STL::list<int> m_listA;											///< retail this+0x0EC
	// _List_base<int> is one pointer, so the destructor's `lea ecx,[esi+0xF8]`
	// puts eight unmodelled bytes between the list and the map. They are never
	// touched here -- whatever lives there is trivially destructible.
	unsigned char m_unreconstructed_f0[8];								///< retail this+0x0F0
	_STL::map<int, Gen_t_00223550_p4pod> m_map;							///< retail this+0x0F8
	_STL::list<int> m_listB;											///< retail this+0x104
};

// ??1HordeSiegeEngineContain@@UAE@XZ
HordeSiegeEngineContain::~HordeSiegeEngineContain()
{
}
