// Retail 0x0037F190 returns the experience-level list and matching node for
// an Object. The ControlBar multi-select body at 0x004A9300 calls this member
// through ILT 0x0000EDC7 and passes the returned pair to its level helpers.

typedef bool Bool;

class AsciiString
{
private:
	void *m_data;
};

class AsciiStringCompareShim
{
public:
	int compare(const AsciiString &other) const;

private:
	void *m_data;
};

#pragma comment(linker, "/alternatename:?compare@AsciiStringCompareShim@@QBEHABVAsciiString@@@Z=?j_000220c5@@YAXXZ")
#pragma comment(linker, "/alternatename:?friend_getFinalOverride@Overridable@@QAEPAV1@XZ=?j_00048c61@@YAXXZ")
#pragma comment(linker, "/alternatename:?query@ExperienceLevelSystemQueryShim@@QAEPAXPAX@Z=?j_0002603f@@YAXXZ")

class ExperienceLevelSystemQueryShim
{
public:
	void *query(void *object);
};

class Overridable
{
public:
	virtual ~Overridable();
	Overridable *friend_getFinalOverride();
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

class Object
{
public:
	unsigned char m_pad[0x210];
	void *m_experienceTracker;
};

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
	ExperienceLevelList *levels = (ExperienceLevelList *)
		querySystem->query((void *)object);
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
		if (nextOverride != 0)
			finalLevel = (ExperienceLevel *)
				nextOverride->friend_getFinalOverride();

		if (finalLevel->m_name.compare(*levelName) == 0)
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
