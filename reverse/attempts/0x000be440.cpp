// ?d_000be440@@YAXXZ
// partial score=0.3065 date=2026-09-21
// Scratch only: nested STLport science-group parser for RVA 0x000BE440.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

extern "C" __declspec(dllimport) int __cdecl _strcmpi(
	const char *left, const char *right);

enum ScienceType
{
	SCIENCE_INVALID = -1
};

class INI
{
public:
	const char *getNextTokenOrNull(const char *delims = 0);
};

class ScienceStore
{
public:
	ScienceType friend_lookupScience(const char *token);
};

extern ScienceStore *TheScienceStore;

typedef _STL::vector<ScienceType> ScienceVec;
typedef _STL::vector<ScienceVec> ScienceGroupVec;

// STLport's three pointer vector layout is witnessed by the native callee
// contracts in this body.  These are views over the real containers, not
// replacement storage.
struct Rva000BE440ScienceVecLayout
{
	ScienceType *begin;
	ScienceType *finish;
	ScienceType *capacity;
};

struct Rva000BE440GroupVecLayout
{
	ScienceVec *begin;
	ScienceVec *finish;
	ScienceVec *capacity;
};

class Rva000BE440Store
{
public:
	void resizeGroups(unsigned count, ScienceVec value);
	ScienceGroupVec m_groups;
};

#pragma comment(linker, "/alternatename:?resizeGroups@Rva000BE440Store@@QAEXIV?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@@Z=?j_0004835b@@YAXXZ")

// ?Rva000BE440@@YAXPAVINI@@PAX1PBX@Z
void __cdecl Rva000BE440(INI *ini, void *, void *store,
	const void *)
{
	Rva000BE440Store *self = (Rva000BE440Store *)store;
	self->resizeGroups(1, ScienceVec());
	ScienceVec *current = &self->m_groups.back();

	const char *token = ini->getNextTokenOrNull(0);
	if (token == 0)
		goto finish;

	while (token != 0)
	{
		if (_strcmpi(token, "None") == 0)
		{
			current->clear();
			goto finish;
		}

		if (_strcmpi(token, "OR") == 0)
		{
			self->m_groups.push_back(ScienceVec());
			current = &self->m_groups.back();
		}
		else
		{
			if (current->begin() == current->end())
				goto finish;
			self->m_groups.push_back(ScienceVec());
			current = &self->m_groups.back();
			ScienceType science = TheScienceStore->friend_lookupScience(token);
			current->push_back(science);
		}

		token = ini->getNextTokenOrNull(0);
	}

finish:
	Rva000BE440ScienceVecLayout *currentLayout =
		(Rva000BE440ScienceVecLayout *)current;
	ScienceType *source = currentLayout->finish;
	ScienceType *destination = currentLayout->begin;
	int count = (int)(currentLayout->finish - source);
	if (count > 0)
	{
		do
		{
			*destination++ = *source++;
			--count;
		} while (count > 0);
	}
	currentLayout->finish = destination;
	if (currentLayout->begin != currentLayout->finish)
		return;

	Rva000BE440GroupVecLayout *groups =
		(Rva000BE440GroupVecLayout *)&self->m_groups;
	ScienceVec *sourceGroup = groups->finish;
	ScienceVec *destinationGroup = groups->begin;
	unsigned int groupCount = (unsigned int)(
		(char *)sourceGroup - (char *)sourceGroup) / sizeof(ScienceVec);
	while (groupCount > 0)
	{
		*destinationGroup = *sourceGroup;
		++sourceGroup;
		++destinationGroup;
		--groupCount;
	}
	ScienceVec *group = destinationGroup;
	while (group != groups->finish)
	{
		group->~ScienceVec();
		++group;
	}
	groups->finish = destinationGroup;
}
