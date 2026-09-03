// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// FXListStore destructor. Same layout as the constructor thunk: SubsystemInterface
// then hash_map at +8. Zero Hour's body is m_fxmap.clear(); the compiler then
// destroys the map and the base.

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

struct Gen_t_0042dc10_p36cd
{
	int a[9];
	Gen_t_0042dc10_p36cd();
	Gen_t_0042dc10_p36cd(const Gen_t_0042dc10_p36cd &);
	~Gen_t_0042dc10_p36cd();
	Gen_t_0042dc10_p36cd &operator=(const Gen_t_0042dc10_p36cd &);
};

bool operator==(const Gen_t_0042dc10_p36cd &, const Gen_t_0042dc10_p36cd &);
bool operator<(const Gen_t_0042dc10_p36cd &, const Gen_t_0042dc10_p36cd &);

typedef _STL::pair<const int, Gen_t_0042dc10_p36cd> FXListStoreMapPair;

class FXListStoreBody : public SubsystemInterface
{
public:
	FXListStoreBody();
	virtual ~FXListStoreBody();
	virtual void init();
	virtual void reset();
	virtual void update();

private:
	_STL::hash_map<int, Gen_t_0042dc10_p36cd, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<FXListStoreMapPair> > m_fxmap;
};

// ??1FXListStoreBody@@UAE@XZ
// Retail FXListStore destructor (0x0042DE50). ??1FXListStore@@UAE@XZ is already
// claimed at 0x009F2800 by a 115-byte lift of a different body.
FXListStoreBody::~FXListStoreBody()
{
	m_fxmap.clear();
}
