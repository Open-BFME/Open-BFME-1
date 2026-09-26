// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System
// stlport
//
// ExperienceLevelSystem constructor, retail RVA 0x00381480.
// GameEngine::init registers TheExperienceLevelSystem at this constructor, as
// recorded in targets/game/reverse/gameengine_init_subsystems.tsv. The constructor vtable
// and member offsets also agree with the matched ExperienceLevelSystem bodies.

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>
#include <list>
#include <vector>

#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

#include "subsystem_interface.h"

class ExperienceLevel
{
public:
	char m_data[0xd8];
};

typedef _STL::list<ExperienceLevel> ExperienceLevelList;
typedef _STL::pair<const Int, ExperienceLevelList> ExperienceLevelMapPair;
typedef _STL::hash_map<Int, ExperienceLevelList, _STL::hash<Int>,
	_STL::equal_to<Int>, _STL::allocator<ExperienceLevelMapPair> > ExperienceLevelMap;

struct PendingExperienceLevel
{
	Int m_objectId;
	void *m_level;
	Bool m_showEffect;
};

class ExperienceScalarTable
{
public:
	ExperienceScalarTable(const AsciiString &name);
	std::vector<Real> m_scalars;
	AsciiString m_name;
};

class ExperienceLevelSystem : public SubsystemInterface
{
public:
	ExperienceLevelSystem();
	virtual ~ExperienceLevelSystem();
	virtual void init() {}
	virtual void reset() {}
	virtual void update() {}

private:
	ExperienceLevelMap m_levelMap;
	_STL::list<PendingExperienceLevel> m_pending;
	std::vector<ExperienceScalarTable *> m_scalarTables;
	ExperienceScalarTable *m_defaultLevel;
};

// ??0ExperienceLevelSystem@@QAE@XZ
ExperienceLevelSystem::ExperienceLevelSystem()
	: SubsystemInterface(),
	  m_levelMap(100),
	  m_pending(),
	  m_scalarTables()
{
	m_defaultLevel = new ExperienceScalarTable(
		AsciiString((const char *)0x010EA974));
	m_defaultLevel->m_scalars.push_back(1.0f);
}
