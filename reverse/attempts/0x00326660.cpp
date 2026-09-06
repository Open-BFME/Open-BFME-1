// ?d_00326660@@YAXXZ
// partial score=0.95 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// ScriptConditions::evaluatePlayerHasKilledTypeUnits, retail 0x00326660.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;
typedef unsigned short UnsignedShort;

class Player;
class ScriptConditions;

class Parameter
{
public:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

class AsciiStringVector
{
public:
	AsciiString operator[](Int index) const;

	const AsciiString *m_begin;
	const AsciiString *m_end;
	const AsciiString *m_capacity;
};

class ObjectTypes
{
public:
	virtual ~ObjectTypes() {}

	__forceinline AsciiString getNthInList(Int index) const
	{
		return m_objectTypes[index];
	}

	__forceinline Int getListSize(void) const
	{
		return (Int)(m_objectTypes.m_end - m_objectTypes.m_begin);
	}

private:
	AsciiString m_listName;
	AsciiStringVector m_objectTypes;
};

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
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual ObjectTypes *getObjectTypes(const AsciiString &objectTypeList) = 0;
	UnsignedShort unidentified_0034DB40(Parameter *parameter);
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(UnsignedShort &mask);
};

struct PlayerKills
{
	int getKillsOfType(const AsciiString &objectType);
};

class Player
{
private:
	unsigned char m_beforeKills[0x348];

public:
	PlayerKills m_kills;
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

extern void j_00020dc9();

static __forceinline int bfmeGetKillsOfType(PlayerKills *kills,
	const AsciiString &objectType)
{
	typedef int (PlayerKills::*Function)(const AsciiString &);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00020dc9;
	return (kills->*fn.member)(objectType);
}

class ScriptConditions
{
protected:
	Bool evaluatePlayerHasKilledTypeUnits(Parameter *, Parameter *, Parameter *);
};

// ?evaluatePlayerHasKilledTypeUnits@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluatePlayerHasKilledTypeUnits(
	Parameter *pPlayerParm, Parameter *pCountParm, Parameter *pTypeParm)
{
	UnsignedShort mask = TheScriptEngine->unidentified_0034DB40(pPlayerParm);
	Player *thePlayer = ThePlayerList->getEachPlayerFromMask(mask);
	if (thePlayer) {
		PlayerKills *kills = &thePlayer->m_kills;
		if (kills) {
			ObjectTypes *types;
			types = TheScriptEngine->getObjectTypes(pTypeParm->m_string);
			if (types) {
				int total = 0;
				for (Int typeIndex = 0; typeIndex < types->getListSize(); ++typeIndex) {
					AsciiString typeName = types->getNthInList(typeIndex);
					total += bfmeGetKillsOfType(kills, typeName);
				}
				return total >= *(int *)((char *)pCountParm + 8);
			}
		}
	}

	return false;
}
