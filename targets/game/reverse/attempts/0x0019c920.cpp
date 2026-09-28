// ?validateSides@SidesList@@QAE_NXZ
// partial score=0.997 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail ?validateSides@SidesList@@QAE_NXZ at 0x0019C920, 1810 bytes.
//
// Port of Zero Hour SidesList::validateSides with BFME's storage: the fixed
// 0x18-byte side records at +0x2C (count at +0x28, Dict at record +4, as in
// SidesListAddPlayerByTemplate.cpp) and the indexed team pool at +0x630,
// whose 0x10-byte nodes start at +0x63C (next/prev shorts, Dict at +0xC),
// with the live count at +0x648 and the free-list head at +0x64A.  BFME finds
// a player's default team by the "owner/name" key built by 0x00195FC0 and
// looked up by 0x0019B780, and walks the pool's linked list where Zero Hour
// indexed an array.  Every callee is an existing ledger or pinned identity.

#include "ascii_string.h"

typedef bool Bool;
typedef int Int;

template <class T> inline bool StringBase<T>::isEmpty() const { return m_data == 0 || m_data->length == 0; }
template <class T> inline void StringBase<T>::concat(const StringBase<T> &s)
{
	concat(s.m_data ? s.m_data->data : "", s.m_data ? s.m_data->length : 0);
}

enum NameKeyType
{
	NAMEKEY_INVALID
};

class StaticNameKey
{
public:
	NameKeyType key() const;
};

extern const StaticNameKey TheKey_playerName;
extern const StaticNameKey TheKey_playerEnemies;
extern const StaticNameKey TheKey_playerAllies;
extern const StaticNameKey TheKey_teamName;
extern const StaticNameKey TheKey_teamOwner;
extern const StaticNameKey TheKey_teamIsSingleton;

extern const AsciiString Rva01336E50EmptyString;

class Dict
{
public:
	Dict(Int numPairsToPreAllocate = 0);
	~Dict() { releaseData(); }

	void clear();
	Bool getBool(NameKeyType key, Bool *exists = 0) const;
	AsciiString getAsciiString(NameKeyType key, Bool *exists = 0) const;
	void setBool(NameKeyType key, Bool value);
	void setAsciiString(NameKeyType key, const AsciiString &value);

private:
	void releaseData();
	void *m_data;
};

AsciiString Rva00195FC0JoinPath(const AsciiString &left, const AsciiString &right);

class SidesInfo
{
public:
	Dict *getDict() { return &m_dict; }

private:
	void *m_pBuildList;
	Dict m_dict;
	unsigned char m_rest[0x10];
};

struct Rva0019C520TeamNode
{
	short m_next;
	short m_prev;
	short m_word04;
	short m_word06;
	int m_word08;
	Dict m_dict;
};

// The team pool at SidesList+0x630.  Its out-of-line operations already carry
// address-derived names on three different placeholder classes; the views
// below name the one pool they all act on.
class Rva0019C520Member
{
public:
	int lookup(AsciiString *name, int extra);
};

class Rva0019BC00Owner
{
public:
	void prepare(int index);
	void finish(int index);
};

class Rva0019BE80TeamRec
{
public:
	int append(const Dict *dict);

	Dict *findTeam(const AsciiString &owner, const AsciiString &name, Int *index)
	{
		AsciiString key = Rva00195FC0JoinPath(owner, name);
		return (Dict *)((Rva0019C520Member *)this)->lookup(&key, (int)index);
	}

	void setTeamOwnerAndName(const Int &index, const AsciiString &owner, const AsciiString &name)
	{
		((Rva0019BC00Owner *)this)->prepare(index);
		Rva0019C520TeamNode *nodes = m_nodes;
		Dict *d = &nodes[index].m_dict;
		d->setAsciiString(TheKey_teamOwner.key(), owner);
		d->setAsciiString(TheKey_teamName.key(), name);
		((Rva0019BC00Owner *)this)->finish(index);
	}

	void removeTeam(Int index)
	{
		((Rva0019BC00Owner *)this)->prepare(index);
		Rva0019C520TeamNode &node = m_nodes[index];
		node.m_dict.clear();
		Rva0019C520TeamNode *nodes = m_nodes;
		nodes[node.m_next].m_prev = node.m_prev;
		Rva0019C520TeamNode *other = m_nodes;
		other[node.m_prev].m_next = node.m_next;
		--m_count;
		node.m_next = m_freeHead;
		m_freeHead = (short)index;
	}

	Int firstTeam() { return m_nodes[0].m_next; }
	Rva0019C520TeamNode *node(Int index) { return &m_nodes[index]; }

	unsigned char m_tree[0xC];
	Rva0019C520TeamNode *m_nodes;
	int m_word10;
	int m_word14;
	short m_count;
	short m_freeHead;
};

typedef char SidesInfoSizeCheck[sizeof(SidesInfo) == 0x18 ? 1 : -1];
typedef char TeamRecSizeCheck[sizeof(Rva0019BE80TeamRec) == 0x1c ? 1 : -1];
typedef char TeamNodeSizeCheck[sizeof(Rva0019C520TeamNode) == 0x10 ? 1 : -1];

class SidesList
{
public:
	Bool validateSides();
	void addPlayerByTemplate(AsciiString playerTemplateName);
	SidesInfo *findSideInfo(AsciiString name, Int *index = 0);

	Int getNumSides() { return m_numSides; }
	SidesInfo *getSideInfo(Int side)
	{
		if (side >= 0 && side < m_numSides)
			return &m_sides[side];
		return 0;
	}

protected:
	Bool validateAllyEnemyList(const AsciiString &tname, AsciiString &allies);

private:
	unsigned char m_prefix[0x28];
	Int m_numSides;
	SidesInfo m_sides[32];
	Int m_numSkirmishSides;
	SidesInfo m_skirmishSides[32];
	Rva0019BE80TeamRec m_teamrec;
};

Bool SidesList::validateSides()
{
	Bool modified = false;

	// ensure we have at least one player, and at least one neutral player.
	Int i;
	Int neutral = -1;
	Int num = getNumSides();
	for (i = 0; i < num; i++)
	{
		Bool exists;
		Dict *d = getSideInfo(i)->getDict();
		if (d && d->getAsciiString(TheKey_playerName.key(), &exists).isEmpty())
		{
			neutral = i;
			break;
		}
	}
	if (neutral == -1)
	{
		addPlayerByTemplate(Rva01336E50EmptyString);
		modified = true;
	}

	// now ensure that every player has a proper "default team"
	for (i = 0; i < getNumSides(); i++)
	{
		Dict *pdict = getSideInfo(i)->getDict();
		AsciiString pname = pdict->getAsciiString(TheKey_playerName.key());
		AsciiString tname("team");
		tname.concat(pname);
		Int index;
		Dict *ti = m_teamrec.findTeam(pname, tname, &index);
		if (ti && index)
		{
			// make sure the team owner points back to the player.
			if (ti->getAsciiString(TheKey_teamOwner.key()).compare(pname) != 0)
			{
				m_teamrec.setTeamOwnerAndName(index, pname, ti->getAsciiString(TheKey_teamName.key()));
				modified = true;
			}
			// default teams are always singletons.
			if (!ti->getBool(TheKey_teamIsSingleton.key()))
			{
				ti->setBool(TheKey_teamIsSingleton.key(), true);
				modified = true;
			}
		}
		else
		{
			Dict d;
			d.setAsciiString(TheKey_teamName.key(), tname);
			d.setAsciiString(TheKey_teamOwner.key(), pname);
			d.setBool(TheKey_teamIsSingleton.key(), true);
			m_teamrec.append(&d);
			modified = true;
		}

		AsciiString allies = pdict->getAsciiString(TheKey_playerAllies.key());
		AsciiString enemies = pdict->getAsciiString(TheKey_playerEnemies.key());

		// ensure all teams have valid allies & enemies.
		if (validateAllyEnemyList(pname, allies))
		{
			pdict->setAsciiString(TheKey_playerAllies.key(), allies);
			modified = true;
		}

		if (validateAllyEnemyList(pname, enemies))
		{
			pdict->setAsciiString(TheKey_playerEnemies.key(), enemies);
			modified = true;
		}
	}

	// ensure there's no overlap between team names and player names.
	// (if there is, the player wins and the team is whacked.)
validate_team_names:
	for (Int t = m_teamrec.firstTeam(); t != 0; )
	{
		Rva0019C520TeamNode *nodes = m_teamrec.m_nodes;
		Int offset = t * sizeof(Rva0019C520TeamNode);
		Int next = *(short *)((char *)nodes + offset);
		Dict *tdict = (Dict *)((char *)nodes + offset + 0xc);
		AsciiString tname = tdict->getAsciiString(TheKey_teamName.key());
		if (findSideInfo(tname))
		{
			m_teamrec.removeTeam(t);
			modified = true;
			goto validate_team_names;
		}
		t = next;
	}

	for (i = m_teamrec.firstTeam(); i != 0; i = m_teamrec.m_nodes[i].m_next)
	{
		if (m_teamrec.m_nodes[i].m_word06 == 0)
		{
			Dict *tdict = &m_teamrec.m_nodes[i].m_dict;
			AsciiString tname = tdict->getAsciiString(TheKey_teamName.key());
			AsciiString towner = tdict->getAsciiString(TheKey_teamOwner.key());
			SidesInfo *si = findSideInfo(towner);
			if (si == 0 || towner.compare(tname) == 0)
			{
				m_teamrec.setTeamOwnerAndName(i, Rva01336E50EmptyString, tname);
				modified = true;
			}
		}
	}

	return modified;
}
