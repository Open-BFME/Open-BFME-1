// ?bfmeQuery0037F050@ExperienceLevelSystem@@QAEPAXPAX@Z
// cl: /O2 /Ob1 /DNDEBUG /MD /EHsc-
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef int Int;

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class BfmeOverridable
{
public:
 BfmeOverridable *friend_getFinalOverride();
 void *m_vtable;
 BfmeOverridable *m_next;
};

class BfmeExperienceRecord
{
public:
	char m_pad0[4];
	BfmeOverridable *m_owner;
	char m_pad08[0x240];
	char *m_nameData;
};

struct Gen_p12cd
{
	Int a[3];
	Gen_p12cd();
	Gen_p12cd(const Gen_p12cd &);
	~Gen_p12cd();
	Gen_p12cd &operator=(const Gen_p12cd &);
};

bool operator==(const Gen_p12cd &, const Gen_p12cd &);
bool operator<(const Gen_p12cd &, const Gen_p12cd &);

typedef _STL::pair<const Int, Gen_p12cd> BfmeExperienceMapPair;
typedef _STL::hash_map<Int, Gen_p12cd, _STL::hash<Int>,
	_STL::equal_to<Int>, _STL::allocator<BfmeExperienceMapPair> >
	BfmeExperienceMap;

class ExperienceLevelSystem
{
public:
	void *bfmeQuery0037F050(void *record);

private:
	char m_subsystemHead[8];
	BfmeExperienceMap m_levelMap;
};

void *ExperienceLevelSystem::bfmeQuery0037F050(void *record)
{
	BfmeExperienceRecord *candidate =
		(BfmeExperienceRecord *)record;
	if (candidate == 0)
		return 0;

	BfmeOverridable *owner = candidate->m_owner;
	if (owner == 0)
		return 0;
	BfmeOverridable *answer = owner;
	if (owner->m_next != 0)
		answer = owner->m_next->friend_getFinalOverride();
	if (answer == 0)
		return 0;

	char *nameData = candidate->m_nameData;
	const char *name = nameData != 0
		? nameData + 8
		: "";
	NameKeyType key = TheNameKeyGenerator->nameToKey(name);

	BfmeExperienceMap::iterator found = m_levelMap.find((Int)key);
	if (found != m_levelMap.end())
		return &found->second;
	return 0;
}
