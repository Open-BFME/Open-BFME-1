// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// ContestableContain's destructor, lifted from its MASM dump to C++.
//
// Its base destructor call lands on 0x0021D9C0, which the ledger already knows
// as GarrisonContain::~GarrisonContain, so this class sits directly on top of
// the layout GarrisonContainDestructorThunk.cpp models: OpenContain's nine
// polymorphic subobjects out to 0x3FC, then Coord3D m_garrisonPoint[3][40],
// which ends the base at 0x99C. ContestableContain adds 0x20 bytes of its own
// before the first member, and the nine vptr writes here are exactly
// OpenContain's group -- no tenth base.
//
// The four members are read off the destructor's own call sites, destroyed in
// reverse declaration order under an SEH funclet apiece:
//
//   0x9BC  _STL::list<int>                    thunk 0x0000E68D -> 0x000CEBD0
//   0x9C0  _STL::list<int>                    thunk 0x00013449 -> 0x000E5E70
//   0x9C4  _STL::map<int, 8-byte class>       thunk 0x000498E6 -> 0x0021B400
//   0x9D0  _STL::list<8-byte pod>             thunk 0x000078C4 -> 0x0021AED0
//
// Both container payloads are spelled the way Code/gen_small/tgrid_107.cpp and
// tgrid_000.cpp spell those instantiations, so the emitted destructors mangle
// to the names the ledger already carries at those addresses.

#include <list>
#include <map>

// 0x0021B400 tree_int_p8cd -- payload spelling from Code/gen_small/tgrid_107.cpp
struct Gen_t_0021b400_p8cd { int a[2]; Gen_t_0021b400_p8cd(); Gen_t_0021b400_p8cd(const Gen_t_0021b400_p8cd&); ~Gen_t_0021b400_p8cd(); Gen_t_0021b400_p8cd& operator=(const Gen_t_0021b400_p8cd&); };
bool operator==(const Gen_t_0021b400_p8cd&, const Gen_t_0021b400_p8cd&);
bool operator<(const Gen_t_0021b400_p8cd&, const Gen_t_0021b400_p8cd&);

// 0x0021AED0 list_p8pod -- payload spelling from Code/gen_small/tgrid_000.cpp
struct Gen_p8pod { int a[2]; };
bool operator==(const Gen_p8pod&, const Gen_p8pod&);
bool operator<(const Gen_p8pod&, const Gen_p8pod&);

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
	unsigned char m_pad[0x3c4];					///< out to sizeof() == 0x3FC
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
class Coord3D
{
public:
	~Coord3D() {}

private:
	float m_value[3];
};

class __declspec(novtable) GarrisonContain : public OpenContain
{
public:
	virtual ~GarrisonContain();

private:
	Coord3D m_garrisonPoint[3][40];				///< out to sizeof() == 0x99C
};

class ContestableContain : public GarrisonContain
{
public:
	virtual ~ContestableContain();

private:
	unsigned char m_unreconstructed_99c[0x20];							///< retail this+0x99C
	_STL::list<int> m_listA;											///< retail this+0x9BC
	_STL::list<int> m_listB;											///< retail this+0x9C0
	_STL::map<int, Gen_t_0021b400_p8cd> m_map;							///< retail this+0x9C4
	_STL::list<Gen_p8pod> m_listC;										///< retail this+0x9D0
};

// ??1ContestableContain@@UAE@XZ
ContestableContain::~ContestableContain()
{
}
