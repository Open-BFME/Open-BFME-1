// cl: /DNDEBUG /MD /EHsc
// Open-BFME: AI::parseSideInfo at retail 0x0014BF10, 299 bytes.
// The SideInfo field table identifies this callback. The allocation size and
// member offsets match AISideInfo, whose existing constructor body is named
// BfmeOwnVUP at retail 0x0014B6B0.

typedef int Int;

extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

class BFMERetailAsciiString;

template <typename T>
class StringBase
{
public:
	struct Header
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		T m_data[1];
	};

	void set(const StringBase<T> &other);
	Header *m_data;

private:
	friend class BFMERetailAsciiString;
	StringBase(const T *text);
	~StringBase();
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(text);
	}

	~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

	BFMERetailAsciiString &operator=(const BFMERetailAsciiString &other)
	{
		((StringBase<char> *)this)->set(*(const StringBase<char> *)&other);
		return *this;
	}

	int compare(const BFMERetailAsciiString &other) const
	{
		int rightLength = other.m_data ? *(const unsigned short *)(other.m_data + 4) : 0;
		const char *right = other.m_data ? other.m_data + 8 : "";
		int leftLength = m_data ? *(const unsigned short *)(m_data + 4) : 0;
		const char *left = m_data ? m_data + 8 : "";
		int length = leftLength < rightLength ? leftLength : rightLength;
		int result = memcmp(left, right, length);
		if (result != 0)
			return result;
		return leftLength - rightLength;
	}

	bool operator==(const BFMERetailAsciiString &other) const
	{
		return compare(other) == 0;
	}

private:
	void releaseBuffer();
	char *m_data;
};

class INI
{
public:
	const char *getNextToken(const char *separators = 0);
	void initFromINI(void *instance, const void *fieldParse);
	static void parseInt(INI *, void *, void *, const void *);
	static void parseAsciiString(INI *, void *, void *, const void *);
};

struct FieldParse
{
	const char *name;
	void (*parse)(INI *, void *, void *, const void *);
	const void *userData;
	unsigned int offset;
};

class AI;

class BfmeOwnVUP
{
public:
	BfmeOwnVUP();
	virtual void bfmeSlot0VUP();

	BFMERetailAsciiString m_side;
	Int m_easy;
	Int m_normal;
	Int m_hard;
	char m_skillSets[5 * 0x54];
	BFMERetailAsciiString m_baseDefenseStructure1;
	BfmeOwnVUP *m_next;
};

typedef BfmeOwnVUP AISideInfo;

class TAiData
{
public:
	void addSideInfo(AISideInfo *info)
	{
		info->m_next = m_sideInfo;
		m_sideInfo = info;
	}

	char m_padding[0xec];
	AISideInfo *m_sideInfo;
};

class AI
{
public:
	static void parseSideInfo(INI *, void *, void *, const void *);
	static void parseSkillSet(INI *, void *, void *, const void *);
};

void AI::parseSideInfo(INI *ini, void *instance, void *, const void *)
{
	const char *c = ini->getNextToken();
	BFMERetailAsciiString side(c);

	static const FieldParse myFieldParse[] =
	{
		{ "ResourceGatherersEasy", INI::parseInt, 0, 8 },
		{ "ResourceGatherersNormal", INI::parseInt, 0, 12 },
		{ "ResourceGatherersHard", INI::parseInt, 0, 16 },
		{ "BaseDefenseStructure1", INI::parseAsciiString, 0, 0x1b8 },
		{ "SkillSet1", AI::parseSkillSet, 0, 0x14 },
		{ "SkillSet2", AI::parseSkillSet, 0, 0x68 },
		{ "SkillSet3", AI::parseSkillSet, 0, 0xbc },
		{ "SkillSet4", AI::parseSkillSet, 0, 0x110 },
		{ "SkillSet5", AI::parseSkillSet, 0, 0x164 },
		{ 0, 0, 0, 0 }
	};

	AISideInfo *resourceInfo = ((TAiData *)instance)->m_sideInfo;
	while (resourceInfo)
	{
		if (side == resourceInfo->m_side)
			break;
		resourceInfo = resourceInfo->m_next;
	}
	if (resourceInfo == 0)
	{
		resourceInfo = new AISideInfo;
		((TAiData *)instance)->addSideInfo(resourceInfo);
	}
	resourceInfo->m_side = side;
	ini->initFromINI(resourceInfo, myFieldParse);
}
