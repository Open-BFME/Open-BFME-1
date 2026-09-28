// ?d_000d1e30@@YAXXZ
// partial score=0.2651 date=2026-09-28
// ?rva000D1E30@Player@@QAEXABVAsciiString@@@Z present-unmatched
// Retail 0x000D1E30, 830 bytes. The receiver's +0x24 field is Player::m_playerIndex
// (name_oracle layout witness); the body calls the matched Player::findSkirmishSide
// thunk. Keep the method itself address-derived until a matched caller names it.
//
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include "string_base.h"

typedef int Int;
typedef bool Bool;
enum NameKeyType { NAMEKEY_INVALID = 0 };

extern void j_00009304();
extern void j_00006c5d();
extern void j_0000fe52();
extern void j_00014475();
extern void j_000220c5();
extern void j_0002af90();

#include <string.h>
#pragma intrinsic(memcmp)

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	__forceinline int compare(const AsciiString &other) const
	{
		typedef int (AsciiString::*CompareThunk)(const AsciiString &) const;
		union
		{
			void (*function)();
			CompareThunk member;
		} thunk;
		thunk.function = j_000220c5;
		return (this->*thunk.member)(other);
	}

	__forceinline bool operator==(const AsciiString &other) const
	{
		const StringBase<char>::Header *leftData = m_data;
		const StringBase<char>::Header *rightData = other.m_data;
		const int leftLength = leftData ? leftData->length : 0;
		const int rightLength = rightData ? rightData->length : 0;
		const char *leftText = leftData ? leftData->data : "";
		const char *rightText = rightData ? rightData->data : "";
		const int commonLength =
			leftLength < rightLength ? leftLength : rightLength;
		int result = memcmp(leftText, rightText, commonLength);
		if (result == 0)
			result = leftLength - rightLength;
		return result == 0;
	}
};


class StaticNameKey
{
public:
	__forceinline NameKeyType key() const
	{
		typedef NameKeyType (StaticNameKey::*KeyThunk)() const;
		union
		{
			void (*function)();
			KeyThunk member;
		} thunk;
		thunk.function = j_00009304;
		return (this->*thunk.member)();
	}
};

extern const StaticNameKey TheKey_playerName;
extern const StaticNameKey TheKey_teamName;
extern const StaticNameKey TheKey_teamOwner;


class Rva0002FF6DStringPresenceThunk
{
public:
	AsciiString forward(int key, Bool *exists = 0) const;
};

struct DictData
{
	unsigned short m_refCount;
};

class Dict : public Rva0002FF6DStringPresenceThunk
{
public:
	Dict(const Dict &other) : m_data(other.m_data)
	{
		if (m_data)
			++m_data->m_refCount;
	}

	__forceinline ~Dict()
	{
		typedef void (Dict::*DestructorThunk)();
		union
		{
			void (*function)();
			DestructorThunk member;
		} thunk;
		thunk.function = j_00014475;
		(this->*thunk.member)();
	}

	__forceinline void setAsciiString(
		NameKeyType key, const AsciiString &value)
	{
		typedef void (Dict::*SetThunk)(NameKeyType, const AsciiString &);
		union
		{
			void (*function)();
			SetThunk member;
		} thunk;
		thunk.function = j_0002af90;
		(this->*thunk.member)(key, value);
	}

private:
	DictData *m_data;
};
class Deletable
{
public:
	virtual ~Deletable();
};

extern void j_000093f4();
extern void j_00031f57();
extern void j_000081b6();
extern void j_000384e7();
extern void j_00029bef();
extern void j_0000fdf8();
extern void j_00045dc7();

class ScriptList : public Deletable
{
public:
	ScriptList *rva0035E450()
	{
		typedef ScriptList *(ScriptList::*MemberThunk)();
		union
		{
			void (*function)();
			MemberThunk member;
		} thunk;
		thunk.function = j_00031f57;
		return (this->*thunk.member)();
	}

	void bfmeSwapEAT(ScriptList *other)
	{
		typedef void (ScriptList::*MemberThunk)(ScriptList *);
		union
		{
			void (*function)();
			MemberThunk member;
		} thunk;
		thunk.function = j_000081b6;
		(this->*thunk.member)(other);
	}

	void rvaClearActiveRecords()
	{
		typedef void (ScriptList::*MemberThunk)();
		union
		{
			void (*function)();
			MemberThunk member;
		} thunk;
		thunk.function = j_000384e7;
		(this->*thunk.member)();
	}
};

struct SideInfo
{
	Int field_0;
	Dict dict;
	ScriptList *scripts;
	char field_c[12];
};

struct TeamNode
{
	short next;
	short previous;
	short reserved;
	short free;
	Int generation;
	Dict dict;
};

class Rva0019BE80TeamRec
{
public:
	void removeTeam(Int index)
	{
		typedef void (Rva0019BE80TeamRec::*MemberThunk)(Int);
		union
		{
			void (*function)();
			MemberThunk member;
		} thunk;
		thunk.function = j_0000fdf8;
		(this->*thunk.member)(index);
	}

	Int append(const Dict *dict)
	{
		typedef Int (Rva0019BE80TeamRec::*MemberThunk)(const Dict *);
		union
		{
			void (*function)();
			MemberThunk member;
		} thunk;
		thunk.function = j_00045dc7;
		return (this->*thunk.member)(dict);
	}

public:
	char m_prefix[0x0c];
	TeamNode *m_begin;
	TeamNode *m_end;
	TeamNode *m_capacity;
	short m_numActive;
	short m_freeHead;
};

class BfmeSidesList
{
public:
	char m_prefix[0x28];
	Int m_numSides;
	SideInfo m_sides[32];
	Int m_numSkirmishSides;
	SideInfo m_skirmishSides[32];
	Rva0019BE80TeamRec teams;
	Rva0019BE80TeamRec skirmishTeams;

	SideInfo *getSideInfo(Int index)
	{
		if (index >= 0 && index < m_numSides)
			return &m_sides[index];
		return 0;
	}

	SideInfo *getSkirmishSideInfo(Int index)
	{
		if (index >= 0 && index < m_numSkirmishSides)
			return &m_skirmishSides[index];
		return 0;
	}

};

extern BfmeSidesList *TheSidesList;

class Player
{
public:
	Bool findSkirmishSide(Int *index);
	void rva000D1E30(const AsciiString &newOwner);

private:
	char m_prefix[0x24];
	Int m_playerIndex;
};

void Player::rva000D1E30(const AsciiString &newOwner)
{
	Int skirmishSideIndex;
	typedef Bool (Player::*FindSkirmishSide)(Int *);
	union
	{
		void (*function)();
		FindSkirmishSide member;
	} findSide;
	findSide.function = j_000093f4;
	if (!(this->*findSide.member)(&skirmishSideIndex))
		return;

	BfmeSidesList *sides = TheSidesList;
	SideInfo *skirmishSide = sides->getSkirmishSideInfo(skirmishSideIndex);
	if (skirmishSide->scripts)
	{
		ScriptList *newScripts = skirmishSide->scripts->rva0035E450();
		SideInfo *playerSide = sides->getSideInfo(m_playerIndex);
		if (playerSide->scripts)
		{
			newScripts->bfmeSwapEAT(playerSide->scripts);
			delete playerSide->scripts;
			newScripts->rvaClearActiveRecords();
		}
		playerSide->scripts = newScripts;
	}

	AsciiString originalName =
		skirmishSide->dict.forward(TheKey_playerName.key());
	for (Int teamIndex = sides->skirmishTeams.m_begin[0].next; teamIndex;
		 teamIndex = sides->skirmishTeams.m_begin[teamIndex].next)
	{
		Dict *source = &sides->skirmishTeams.m_begin[teamIndex].dict;
		if (source->forward(TheKey_teamOwner.key()) == originalName)
		{
			Dict teamDict(*source);
			AsciiString teamName = teamDict.forward(TheKey_teamName.key());
			typedef AsciiString (*AddStringThunk)(
				AsciiString, const AsciiString &);
			union
			{
				void (*function)();
				AddStringThunk typed;
			} addString;
			addString.function = j_0000fe52;
			if (teamName.compare(addString.typed(
					AsciiString("team"), originalName)) == 0)
				teamDict.setAsciiString(TheKey_teamName.key(),
					addString.typed(AsciiString("team"), newOwner));
			teamDict.setAsciiString(TheKey_teamOwner.key(), newOwner);

			Int existingTeamIndex;
			typedef AsciiString (*AddCharThunk)(AsciiString, const char *);
			union
			{
				void (*function)();
				AddCharThunk typed;
			} addChar;
			addChar.function = j_00006c5d;
			typedef void *(BfmeSidesList::*FindTeamInfoThunk)(
				AsciiString, Int *);
			union
			{
				void (*function)();
				FindTeamInfoThunk member;
			} findTeamInfo;
			findTeamInfo.function = j_00029bef;
			if ((sides->*findTeamInfo.member)(
					addString.typed(addChar.typed(newOwner, "/"), teamName),
					&existingTeamIndex))
				sides->teams.removeTeam(existingTeamIndex);
			sides->teams.append(&teamDict);
		}
	}
}
