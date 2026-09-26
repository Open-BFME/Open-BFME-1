// cl: /DNDEBUG /MD /EHsc
// readable body of ?evaluateTeamCountCompare@ScriptConditions@@IAE_NPAVParameter@@00@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluateTeamOwnedByPlayer@ScriptConditions@@IAE_NPAVParameter@@0@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluateTeamCachedFloatCompare@ScriptConditions@@IAE_NPAVParameter@@000@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp

// The three ScriptConditions conditions that look a team up by name and then
// compare something about it against a script parameter:
//
//   0x00324600  evaluateTeamCountCompare        how many of a kind it holds
//   0x00324D40  evaluateTeamOwnedByPlayer       whose team it is
//   0x00325E50  evaluateTeamCachedFloatCompare  a per-frame cached float
//
// They sat in three files that each carried a private copy of AsciiString,
// Parameter and the ScriptEngine vtable, and those copies had drifted in the
// two ways separate files always drift.
//
// The string first. One file gave AsciiString a char* member, one gave it no
// members at all, and one included the stringinline shim, where AsciiString
// derives privately from StringBase<char>. Three shapes and three sizes for a
// class every one of them passes BY VALUE to getTeamNamed. The delegating
// slice below is the shape that puts the __$SEHRec$ store ahead of `mov ecx,
// esp`, and all three bodies byte-match against it, which is the only way to
// find out that the other two spellings were incidental.
//
// Then Parameter. One file spelled the string offset as a flat 0x10-byte run,
// one as an Int at +0x08 followed by four unnamed bytes, and one as the Int at
// +0x08 with a Real at +0x0C. The third is right and now stands for all three:
// getInt reads +0x08, the Real is +0x0C, the string is +0x10.
//
// The two callees that are still address-derived stay address-derived: the
// count-of-a-kind call is reached through the thunk at 0x0000A957, and the
// cached float through Rva000F72D0FrameCachedValue::value at 0x000F72D0, which
// this file reaches by casting the Team pointer because that is what retail
// does.

typedef bool Bool;
typedef float Real;
typedef unsigned short UnsignedShort;

template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase &);
	~StringBase();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}
	~AsciiString();

private:
	char *m_text;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	const AsciiString &getString(void) const { return m_string; }
	int getInt(void) const { return m_int; }

	unsigned char m_beforeInt[8];
	int m_int;						// this+0x08
	Real m_real;						// this+0x0C
	AsciiString m_string;					// this+0x10
};

class Player;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Player *getControllingPlayer(void) const;
};

// The per-frame cached float the third condition reads; retail 0x000F72D0. It
// is reached by casting the Team pointer, which is what retail does.
class Rva000F72D0FrameCachedValue
{
public:
	Real value(Real range);
};

// The count-of-a-kind call, still only known as the thunk at 0x0000A957.
class BfmeTeamCountKindCall
{
public:
	int countKind(int kind, Bool includeContained, Bool includeDead);
};

extern void j_0000a957();

static __forceinline int bfmeCountKind(Team *team, int kind)
{
	typedef int (BfmeTeamCountKindCall::*Function)(int, Bool, Bool);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0000a957;
	return (reinterpret_cast<BfmeTeamCountKindCall *>(team)->*fn.member)(
		kind, false, true);
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	Player *getEachPlayerFromMask(UnsignedShort &mask);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual Team *getTeamNamed(AsciiString name, Bool exact) = 0;	// slot 17, vtable+0x44
	UnsignedShort unidentified_0034DB40(Parameter *);
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptConditions.h
class ScriptConditions
{
protected:
	Bool evaluateTeamCountCompare(Parameter *, Parameter *, Parameter *);
	Bool evaluateTeamOwnedByPlayer(Parameter *, Parameter *);
	Bool evaluateTeamCachedFloatCompare(Parameter *, Parameter *, Parameter *, Parameter *);
};

// ?evaluateTeamCountCompare@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluateTeamCountCompare(
	Parameter *teamParm, Parameter *countParm, Parameter *kindParm)
{
	Team *team = TheScriptEngine->getTeamNamed(teamParm->getString(), false);
	if (team) {
		int kind = kindParm->getInt();
		if (countParm->getInt() < bfmeCountKind(team, kind)) {
			return true;
		}
		return false;
	}

	return false;
}

// ?evaluateTeamOwnedByPlayer@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateTeamOwnedByPlayer(
	Parameter *teamParm, Parameter *playerParm)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamParm->getString(), false);
	if (!theTeam) {
		return false;
	}

	UnsignedShort mask = TheScriptEngine->unidentified_0034DB40(playerParm);
	while (mask != 0) {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (theTeam->getControllingPlayer() == player) {
			return true;
		}
	}

	return false;
}

// ?evaluateTeamCachedFloatCompare@ScriptConditions@@IAE_NPAVParameter@@000@Z
Bool ScriptConditions::evaluateTeamCachedFloatCompare(
	Parameter *pTeamParm, Parameter *pComparisonParm,
	Parameter *pValueParm, Parameter *pContextParm)
{
	if (pTeamParm) {
		if (pContextParm) {
			if (pComparisonParm) {
				if (pValueParm) {
					Rva000F72D0FrameCachedValue *theTeam =
						(Rva000F72D0FrameCachedValue *)TheScriptEngine->getTeamNamed(
						pTeamParm->getString(), false);
					if (theTeam) {
						Real range = pContextParm->m_real;
						Real value = theTeam->value(range);
						switch (pComparisonParm->m_int) {
						case 0: return (value < pValueParm->m_real);
						case 1: return (value <= pValueParm->m_real);
						case 2: return (value == pValueParm->m_real);
						case 3: return (value >= pValueParm->m_real);
						case 4: return (value > pValueParm->m_real);
						case 5: return (value != pValueParm->m_real);
						}
					}
				}
			}
		}
	}

	return false;
}
