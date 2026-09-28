// ?d_00198f00@@YAXXZ
// partial score=0.5796545105566219 date=2026-09-28
// Conditional temporary restores retail slot EH form; key 012A7770 is teamLibraryMapName.
// Relink after reloading nodes across bfmePrepareRelease.
// ?removeOwnedTeams@SideTeams00198F00@@QAEXH@Z
// partial score=0.21 date=2026-09-17
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#include <string.h>

#pragma intrinsic(memcmp)

typedef int Int;
typedef bool Bool;

#include "ascii_string.h"
enum NameKeyType { NAMEKEY_INVALID = 0 };
class StaticNameKey { public: NameKeyType key() const; };
class Dict {
    void *m_data;
public:
    enum DataType { DICT_NONE=-1, DICT_BOOL, DICT_INT, DICT_REAL, DICT_ASCIISTRING };
    DataType getType(NameKeyType key) const;
    AsciiString getAsciiString(NameKeyType key, bool *exists) const;
    void clear();
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
	void *m_pBuildList;
	Dict m_dict;
	Gen0035B3A0 *m_scripts;
	char m_tail[0x0c];
};

typedef char BfmeSidesInfoSizeCheck[
	(sizeof(BfmeSidesInfo) == 0x18) ? 1 : -1];

class SideTeams00198F00
{
public:
	void removeOwnedTeams(int index);

private:
	char m_prefix[0x28];
	int m_numSides;
	BfmeSidesInfo m_sides[32];
	int m_numSkirmishSides;
	BfmeSidesInfo m_skirmishSides[32];
	BfmeIndexedNodesFM m_teamrec;
};

extern StaticNameKey TheKey_teamLibraryMapName;
class GenKey { public: NameKeyType fetch(); };
extern GenKey GenKey0012A7918;
extern StaticNameKey TheKey_teamOwner;

// ?removeOwnedTeams@SideTeams00198F00@@QAEXH@Z
void SideTeams00198F00::removeOwnedTeams(int index)
{
	SideTeams00198F00 *self = this;
	int zero = 0;
	int teamIndex;
	BfmeSidesInfo *side;
	if (index < zero || index >= self->m_numSides)
		side = 0;
	else
		side = &self->m_sides[index];

	if (side->m_scripts != 0)
		side->m_scripts->cleanup();

	AsciiString sideName =
		side->m_dict.getAsciiString(GenKey0012A7918.fetch(), 0);

	teamIndex = self->m_teamrec.m_nodes[0].m_next;
	for (; teamIndex != zero; )
	{
		BfmeTeamInfoSlot *nodes = self->m_teamrec.m_nodes;
		int nextTeam = nodes[teamIndex].m_next;
        Bool matches = nodes[teamIndex].m_dict.getType(TheKey_teamLibraryMapName.key()) == Dict::DICT_ASCIISTRING &&
            nodes[teamIndex].m_dict.getAsciiString(TheKey_teamOwner.key(), 0).compare(sideName) == 0;
		if (matches)
		{
			self->m_teamrec.bfmePrepareRelease(teamIndex);
			nodes = self->m_teamrec.m_nodes;
            nodes[teamIndex].m_dict.clear();
			self->m_teamrec.m_nodes[nodes[teamIndex].m_next].m_previous = nodes[teamIndex].m_previous;
            self->m_teamrec.m_nodes[nodes[teamIndex].m_previous].m_next = nodes[teamIndex].m_next;
			short oldFreeHead = self->m_teamrec.m_freeHead;
			--self->m_teamrec.m_count;
			nodes[teamIndex].m_next = oldFreeHead;
			self->m_teamrec.m_freeHead = static_cast<short>(teamIndex);
		}
		teamIndex = nextTeam;
	}
}
