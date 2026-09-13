// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: SiegeEngineContain module ctor.
//
// This is the retail OpenContain multiple-inheritance slice.  The base
// constructor is the shared ILT already identified as HordeTransport's base
// constructor; keeping that ABI name also makes the call resolve to the
// existing 0x23A1 pin.  The three STLport members are laid out from the
// matching destructor: list at +0xE4, map at +0xF0, and list at +0xFC.

#include <list>
#include <map>

class Thing;
class ModuleData;

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
	unsigned char m_pad[0x9c];
};

class SiegeEngineContainTenthBase
{
public:
	virtual ~SiegeEngineContainTenthBase() {}
};

// The 0x23A1 body is shared with HordeTransportContainBase in the retail
// image, so use its established decorated identity for this ABI slice.
class __declspec(novtable) HordeTransportContainBase
	: public OpenContain,
	  public SiegeEngineContainTenthBase
{
public:
	HordeTransportContainBase(Thing *, const ModuleData *);
	virtual ~HordeTransportContainBase();

private:
	unsigned char m_pad[0x0c];
};

struct Gen_t_00223550_p4pod { int a[1]; };
bool operator==(const Gen_t_00223550_p4pod&, const Gen_t_00223550_p4pod&);
bool operator<(const Gen_t_00223550_p4pod&, const Gen_t_00223550_p4pod&);

class SiegeEngineContain : public HordeTransportContainBase
{
public:
	SiegeEngineContain(Thing *, const ModuleData *);
	virtual ~SiegeEngineContain();

private:
	_STL::list<int> m_listA;
	int m_e8;
	bool m_ec;
	_STL::map<int, Gen_t_00223550_p4pod> m_map;
	_STL::list<int> m_listB;
};

// ??0SiegeEngineContain@@QAE@PAVThing@@PBVModuleData@@@Z
SiegeEngineContain::SiegeEngineContain(Thing *thing, const ModuleData *moduleData)
	: HordeTransportContainBase(thing, moduleData), m_listB(_STL::allocator<int>())
{
	m_e8 = 0;
	m_ec = false;
}
