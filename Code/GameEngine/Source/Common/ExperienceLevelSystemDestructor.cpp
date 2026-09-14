// ??1ExperienceLevelSystem@@UAE@XZ
// The complete destructor for the BFME experience subsystem at retail RVA
// 0x00380D30.  Its constructor and update body establish the member order.
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <cstring>
extern "C" void *(__cdecl *bfme_memmove_ptr)(void *, const void *, unsigned int);
#define memmove (*bfme_memmove_ptr)
#include <hash_map>
#include <list>
#include <vector>
#undef memmove

typedef bool Bool;

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void loadIniFilesFromLegend() {}
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual void draw() {}

private:
	void *m_name;
};

struct Gen_t_003808e0_p12cd
{
	int m_words[3];
	Gen_t_003808e0_p12cd();
	Gen_t_003808e0_p12cd(const Gen_t_003808e0_p12cd &);
	~Gen_t_003808e0_p12cd();
	Gen_t_003808e0_p12cd &operator=(const Gen_t_003808e0_p12cd &);
};

bool operator==(const Gen_t_003808e0_p12cd &, const Gen_t_003808e0_p12cd &);
bool operator<(const Gen_t_003808e0_p12cd &, const Gen_t_003808e0_p12cd &);

typedef _STL::pair<const int, Gen_t_003808e0_p12cd> ExperienceMapPair;
typedef _STL::hash_map<int, Gen_t_003808e0_p12cd, _STL::hash<int>,
	_STL::equal_to<int>, _STL::allocator<ExperienceMapPair> > ExperienceMap;

struct PendingExperienceLevel
{
	int m_objectId;
	void *m_level;
	Bool m_showEffect;
};

struct ExperienceScalarTable
{
	~ExperienceScalarTable();
};

#pragma comment(linker, "/alternatename:??1ExperienceScalarTable@@QAE@XZ=?j_00016e6e@@YAXXZ")

class ExperienceLevelSystem : public SubsystemInterface
{
public:
	virtual ~ExperienceLevelSystem();
	void cleanup();
	virtual void init() {}
	virtual void reset() {}
	virtual void update() {}

private:
	ExperienceMap m_levelMap;
	_STL::list<PendingExperienceLevel> m_pending;
	std::vector<ExperienceScalarTable *> m_scalarTables;
	ExperienceScalarTable *m_defaultLevel;
};

#pragma comment(linker, "/alternatename:?cleanup@ExperienceLevelSystem@@QAEXXZ=?j_00002568@@YAXXZ")

ExperienceLevelSystem::~ExperienceLevelSystem()
{
	if (m_defaultLevel)
	{
		delete m_defaultLevel;
	}
	m_defaultLevel = 0;

	for (unsigned index = 0; index < m_scalarTables.size(); ++index)
	{
		ExperienceScalarTable *level = m_scalarTables[index];
		if (level)
			delete level;
	}
	m_scalarTables.clear();
	cleanup();
}

void bfmeForceExperienceLevelSystemDestructor(ExperienceLevelSystem *system)
{
	system->~ExperienceLevelSystem();
}

void bfmeForceExperienceLevelSystemVtable()
{
	ExperienceLevelSystem system;
}
