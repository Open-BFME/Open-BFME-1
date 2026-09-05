// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Byte-twin of ??1FXListStoreBody@@UAE@XZ at 0x0042DE50
// (FXListStoreDtorThunk.cpp): identical 98 bytes once relocations are
// masked; only the installed vtable (0x010758F8, tools/vtable_lookup.py)
// differs, so this is a sibling class with the same hash_map<int, POD>
// member layout, claimed address-derived. The value-type struct is
// uniquely named so the internal hashtable helpers get fresh mangled
// names distinct from FXListStoreBody's own instantiation.

#include <hash_map>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual bool loadIniFilesFromLegend();
	virtual void reset() = 0;
	virtual void update() = 0;

private:
	void *m_name;
};

struct Gen_t_000678b0_p36cd
{
	int a[9];
	Gen_t_000678b0_p36cd();
	Gen_t_000678b0_p36cd(const Gen_t_000678b0_p36cd &);
	~Gen_t_000678b0_p36cd();
	Gen_t_000678b0_p36cd &operator=(const Gen_t_000678b0_p36cd &);
};

bool operator==(const Gen_t_000678b0_p36cd &, const Gen_t_000678b0_p36cd &);
bool operator<(const Gen_t_000678b0_p36cd &, const Gen_t_000678b0_p36cd &);

typedef _STL::pair<const int, Gen_t_000678b0_p36cd> Rva000678B0MapPair;

class Rva000678B0Body : public SubsystemInterface
{
public:
	Rva000678B0Body();
	virtual ~Rva000678B0Body();
	virtual void init();
	virtual void reset();
	virtual void update();

private:
	_STL::hash_map<int, Gen_t_000678b0_p36cd, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<Rva000678B0MapPair> > m_fxmap;
};

Rva000678B0Body::~Rva000678B0Body()
{
	m_fxmap.clear();
}
