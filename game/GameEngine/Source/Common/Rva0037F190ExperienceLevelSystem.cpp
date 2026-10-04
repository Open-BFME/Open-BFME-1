// cl: /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x0037F190 returns the experience-level list and matching node for
// an Object. The ControlBar multi-select body at 0x004A9300 calls this member
// through ILT 0x0000EDC7 and passes the returned pair to its level helpers.

typedef bool Bool;

#include "ascii_string.h"

class AsciiStringCompareShim
{
private:
	void *m_data;
};

extern void j_000220c5();
extern void j_00048c61();
extern void j_0002603f();

class ExperienceLevelSystemQueryShim
{
};

class Overridable
{
public:
	virtual ~Overridable();
	Overridable *getNextOverride()
	{
		return m_nextOverride;
	}

protected:
	Overridable *m_nextOverride;
	Bool m_isOverride;
};

class ExperienceLevel : public Overridable
{
public:
	AsciiStringCompareShim m_name;
};

struct ExperienceLevelNode
{
	ExperienceLevelNode *m_next;
	ExperienceLevelNode *m_previous;
	ExperienceLevel m_value;
};

struct ExperienceLevelList
{
	ExperienceLevelNode *m_node;
};

#include "../GameLogic/Object/object.h"

struct Rva0037F190Result
{
	ExperienceLevelList *m_list;
	ExperienceLevelNode *m_node;
};

class ExperienceLevelSystem
{
public:
	void rva0037F190(Rva0037F190Result *result, Object *object);
};

void ExperienceLevelSystem::rva0037F190(
	Rva0037F190Result *result, Object *object)
{
	if (object == 0)
		goto noResult;

	ExperienceLevelSystemQueryShim *querySystem =
		(ExperienceLevelSystemQueryShim *)this;
	typedef void *(ExperienceLevelSystemQueryShim::*Query)(void *);
	union { void (*fn)(); Query call; } query = { j_0002603f };
	ExperienceLevelList *levels = (ExperienceLevelList *)
		(querySystem->*query.call)((void *)object);
	if (levels == 0)
		goto noResult;

	AsciiString *levelName = (AsciiString *)
		((unsigned char *)object->m_experienceTracker + 8);
	ExperienceLevelNode *sentinel = levels->m_node;
	ExperienceLevelNode *node = sentinel->m_next;
	while (node != sentinel)
	{
		ExperienceLevel *level = &node->m_value;
		ExperienceLevel *finalLevel = level;
		Overridable *nextOverride = level->getNextOverride();
		typedef Overridable *(Overridable::*FinalOverride)();
		union { void (*fn)(); FinalOverride call; } finalOverride =
			{ j_00048c61 };
		if (nextOverride != 0)
			finalLevel = (ExperienceLevel *)
				(nextOverride->*finalOverride.call)();

		typedef int (AsciiStringCompareShim::*Compare)(
			const AsciiString &) const;
		union { void (*fn)(); Compare call; } compare = { j_000220c5 };
		if ((finalLevel->m_name.*compare.call)(*levelName) == 0)
		{
			volatile Rva0037F190Result *output = result;
			output->m_list = levels;
			output->m_node = node;
			return;
		}

		node = node->m_next;
	}


noResult:
	result->m_list = 0;
}
