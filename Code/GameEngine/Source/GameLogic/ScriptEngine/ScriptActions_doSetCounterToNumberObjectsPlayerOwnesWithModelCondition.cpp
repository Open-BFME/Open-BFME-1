// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// Open-BFME: SET_COUNTER_TO_NUMBER_OBJECTS_PLAYER_OWNES_WITH_MODELCONDITION
// at retail RVA 0x002F69B0.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class Player;
class ScriptActions;
struct ScriptCounter;

class ScriptEngine
{
protected:
	friend class ScriptActions;
	ScriptCounter *bfmeCounter(AsciiString name);
};

class BfmeScriptEngine_getPlayerMaskFromAsciiString
{
public:
	unsigned short getPlayerMaskFromAsciiString(const AsciiString &name,
		Bool *isWildcard);
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(unsigned short &mask);
};

class Player
{
public:
	Int rva000D4730CountObjects(UnsignedInt bitIndex, Int limit) const;
};

struct ScriptCounter
{
	Int m_value;
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

// The 288-entry ModelConditionFlags name table is reached through the retail
// ILT shared by the already-converted BitFlags setter at 0x001C62B0.
extern Int bfmeLookup_001c62b0(void *name);

class ScriptActions
{
protected:
	void doSetCounterToNumberObjectsPlayerOwnesWithModelCondition(
		const AsciiString &playerName, const AsciiString &modelConditionName,
		const AsciiString &counterName);
};

void ScriptActions::doSetCounterToNumberObjectsPlayerOwnesWithModelCondition(
	const AsciiString &playerName, const AsciiString &modelConditionName,
	const AsciiString &counterName)
{
	unsigned short mask =
		((BfmeScriptEngine_getPlayerMaskFromAsciiString *)TheScriptEngine)
			->getPlayerMaskFromAsciiString(playerName, 0);
	Int value = 0;
	Int modelConditionBit =
		bfmeLookup_001c62b0((void *)modelConditionName.str());
	if (mask)
	{
		do
		{
			Player *thePlayer = ThePlayerList->getEachPlayerFromMask(mask);
			if (thePlayer)
				value += thePlayer->rva000D4730CountObjects(
					(UnsignedInt)modelConditionBit, 0x7ffffffe);
		} while (mask);
	}

	ScriptCounter *destination =
		((ScriptEngine *)TheScriptEngine)->bfmeCounter(counterName);
	destination->m_value = value;
}
