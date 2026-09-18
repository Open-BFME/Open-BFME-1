// ?removeSide@SidesList@@QAEXH@Z
// partial score=0.21 date=2026-09-17
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#include <string.h>

#pragma intrinsic(memcmp)

typedef int Int;
typedef bool Bool;

struct BfmeAsciiStringHeader
{
	int references;
	unsigned short length;
	unsigned short capacity;
	char data[1];
};

template <typename T> class StringBase;

class AsciiString;

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase<T> &other);
	void releaseBuffer(void);

	struct Header
	{
		int references;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class AsciiString
{
public:
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}

	~AsciiString(void);

	int compare(const AsciiString &other) const
	{
		const StringBase<char> *otherBase =
			(const StringBase<char> *)&other;
		const StringBase<char> *thisBase =
			(const StringBase<char> *)this;
		int otherLength = otherBase->m_data ? otherBase->m_data->length : 0;
		const char *otherData = otherBase->m_data ?
			otherBase->m_data->data : "";
		int thisLength = thisBase->m_data ? thisBase->m_data->length : 0;
		const char *thisData = thisBase->m_data ?
			thisBase->m_data->data : "";
		int count = thisLength < otherLength ? thisLength : otherLength;
		int result = memcmp(thisData, otherData, count);
		if (result != 0)
			return result;
		return thisLength - otherLength;
	}

private:
	char *m_text;
};

inline AsciiString::~AsciiString(void)
{
	((StringBase<char> *)this)->releaseBuffer();
}

class BFMERetailAsciiString
{
public:
	void releaseBuffer(void);

	int compare(const BFMERetailAsciiString &other) const
	{
		int otherLength = other.m_data ? other.m_data->length : 0;
		const char *otherData = other.m_data ? other.m_data->data : "";
		int thisLength = m_data ? m_data->length : 0;
		const char *thisData = m_data ? m_data->data : "";
		int count = thisLength < otherLength ? thisLength : otherLength;
		int result = memcmp(thisData, otherData, count);
		if (result != 0)
			return result;
		return thisLength - otherLength;
	}

	protected:
	BfmeAsciiStringHeader *m_data;
};

class BfmeStringPresenceValue : public BFMERetailAsciiString
{
public:
	~BfmeStringPresenceValue(void)
	{
		releaseBuffer();
	}

	bool operator==(const BfmeStringPresenceValue &other) const
	{
		return compare(other) == 0;
	}
};

class BfmeStringPresenceDict
{
private:
	void *m_data;

public:
	BfmeStringPresenceValue getAsciiString(int key, bool *exists) const;
};

class GenKey
{
public:
	NameKeyType fetch(void);
};

class StaticNameKey
{
public:
	NameKeyType key(void) const;
};

class Dict
{
public:
	enum DataType
	{
		DICT_NONE = -1,
		DICT_BOOL,
		DICT_INT,
		DICT_REAL,
		DICT_ASCIISTRING
	};

	DataType getType(NameKeyType key) const;
	BfmeStringPresenceValue getAsciiString(NameKeyType key, bool *exists) const;

private:
	void *m_data;
};

class Gen0035B3A0
{
public:
	void cleanup(void);
};

class BfmeMapObjectExtra
{
public:
	void bfmeReset(void);
};

struct BfmeTeamInfoSlot
{
	short m_next;
	short m_previous;
	short m_reserved;
	short m_free;
	Int m_generation;
	Dict m_dict;
};

typedef char BfmeTeamInfoSlotSizeCheck[
	(sizeof(BfmeTeamInfoSlot) == 0x10) ? 1 : -1];

class BfmeIndexedNodesFM
{
public:
	void bfmePrepareRelease(int index);

	char m_tree[0x0c];
	BfmeTeamInfoSlot *m_nodes;
	char m_gap[8];
	short m_count;
	short m_freeHead;
};

typedef char BfmeIndexedNodesFMSizeCheck[
	(sizeof(BfmeIndexedNodesFM) == 0x1c) ? 1 : -1];

struct BfmeSidesInfo
{
	void *m_buildList;
	BfmeStringPresenceDict m_dict;
	Gen0035B3A0 *m_scripts;
	char m_tail[0x0c];
};

typedef char BfmeSidesInfoSizeCheck[
	(sizeof(BfmeSidesInfo) == 0x18) ? 1 : -1];

class SidesList
{
public:
	void removeSide(int index);

private:
	char m_prefix[0x28];
	int m_numSides;
	BfmeSidesInfo m_sides[32];
	int m_numSkirmishSides;
	BfmeSidesInfo m_skirmishSides[32];
	BfmeIndexedNodesFM m_teamrec;
};

extern GenKey GenKey0012A7918;
extern StaticNameKey TheKey_teamOwner;

// ?removeSide@SidesList@@QAEXH@Z
void SidesList::removeSide(int index)
{
	SidesList *self = this;
	int zero = 0;
	int teamIndex;
	BfmeSidesInfo *side;
	if (index < zero || index >= self->m_numSides)
		side = 0;
	else
		side = &self->m_sides[index];

	if (side->m_scripts != 0)
		side->m_scripts->cleanup();

	BfmeStringPresenceValue sideName =
		side->m_dict.getAsciiString(GenKey0012A7918.fetch(), 0);

	teamIndex = self->m_teamrec.m_nodes[0].m_next;
	for (; teamIndex != zero; )
	{
		int teamOffset = teamIndex * sizeof(BfmeTeamInfoSlot);
		BfmeTeamInfoSlot *team = (BfmeTeamInfoSlot *)
			((unsigned char *)self->m_teamrec.m_nodes + teamOffset);
		int nextTeam = team->m_next;
		Bool matches;
		if (team->m_dict.getType(
			TheKey_teamOwner.key()) == Dict::DICT_ASCIISTRING)
		{
			{
				BfmeStringPresenceValue teamOwner =
					team->m_dict.getAsciiString(TheKey_teamOwner.key(), 0);
				if (teamOwner.compare(sideName) != 0)
					goto team_owner_mismatch;
				matches = true;
				goto team_owner_match_done;
			team_owner_mismatch:
				matches = false;
			team_owner_match_done:
				;
			}
		}
		else
		{
			matches = false;
		}
		if (matches)
		{
			self->m_teamrec.bfmePrepareRelease(teamIndex);
			reinterpret_cast<BfmeMapObjectExtra *>(&team->m_dict)->bfmeReset();
			self->m_teamrec.m_nodes[team->m_previous].m_next = team->m_next;
			self->m_teamrec.m_nodes[team->m_next].m_previous = team->m_previous;
			short oldFreeHead = self->m_teamrec.m_freeHead;
			--self->m_teamrec.m_count;
			team->m_next = oldFreeHead;
			self->m_teamrec.m_freeHead = static_cast<short>(teamIndex);
		}
		teamIndex = nextTeam;
	}
}
