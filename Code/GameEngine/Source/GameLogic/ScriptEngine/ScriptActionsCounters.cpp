// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Every ScriptActions action whose whole job is to work out one number and
// store it in a named script counter:
//
//   0x002F6330  doCounterMathCounter                COUNTER_MATH_COUNTER
//   0x002F6410  doCounterMathValue                  COUNTER_MATH_VALUE
//   0x002F6550  doSetPlayerMoneyToCounter           SET_PLAYER_MONEY_TO_COUNTER
//   0x002F65E0  doSetPlayerLightPointsToCounter     SET_PLAYER_LIGHT_POINTS_TO_COUNTER
//   0x002F6670  doSetUnitExperienceToCounter        SET_UNIT_EXPERIENCE_TO_COUNTER
//   0x002F66E0  doSetPlayerCommandPointsUsedToCounter
//   0x002F6760  doSetPlayerCommandPointsAvailableToCounter
//   0x002F67E0  doSetPlayerCommandPointsTotalToCounter
//   0x002F6920  doSetPlayerKillsOfTypeToCounter     SET_PLAYER_KILLS_OF_TYPE_TO_COUNTER
//   0x002F69B0  doSetCounterToNumberObjectsPlayerOwnesWithModelCondition
//
// All ten end the same way -- ScriptEngine::bfmeCounter on the counter name,
// then a store into ScriptCounter::m_value -- and differ only in where the
// number comes from, so they share every model declared here.

#define _STLP_NO_EXCEPTIONS 1
#include <map>
#include "StringInline.h"

extern const char g_bfmeEmptyAscii[];
extern "C" int __cdecl memcmp(const void *left, const void *right,
	unsigned int count);
#pragma intrinsic(memcmp)

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class Object;
class Player;
class ScriptActions;

// The counter a script names. Only doCounterMathCounter looks past m_value, at
// the countdown-timer flag that tells a timer from a plain counter.
struct ScriptCounter
{
	Int m_value;
	Bool m_isCountdownTimer;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void _slot00() = 0;
	virtual void _slot01() = 0;
	virtual void _slot02() = 0;
	virtual void _slot03() = 0;
	virtual void _slot04() = 0;
	virtual void _slot05() = 0;
	virtual void _slot06() = 0;
	virtual void _slot07() = 0;
	virtual void _slot08() = 0;
	virtual void _slot09() = 0;
	virtual void _slot10() = 0;
	virtual void _slot11() = 0;
	virtual void _slot12() = 0;
	virtual void _slot13() = 0;
	virtual void _slot14() = 0;
	virtual void _slot15() = 0;
	virtual void _slot16() = 0;
	virtual void _slot17() = 0;
	virtual void _slot18() = 0;
	virtual void _slot19() = 0;
	virtual void _slot20() = 0;
	virtual void _slot21() = 0;
	virtual void _slot22() = 0;
	virtual void _slot23() = 0;
	virtual void _slot24() = 0;
	virtual void _slot25() = 0;
	virtual Object *getUnitNamed(const AsciiString &name) = 0;

protected:
	friend class ScriptActions;
	ScriptCounter *bfmeCounter(AsciiString name);
};

// Reached by casting TheScriptEngine: the mask helper is not a slot.
class BfmeScriptEngine_getPlayerMaskFromAsciiString
{
public:
	unsigned short getPlayerMaskFromAsciiString(const AsciiString &name,
		Bool *isWildcard);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	// Distinct retail bodies, not spellings of one: 0x000DF440 returns the
	// first player in the mask, 0x000DF4A0 consumes one bit per call so a
	// caller can walk every player the mask names.
	Player *getPlayerFromMask(unsigned short mask);
	Player *getEachPlayerFromMask(unsigned short &mask);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	Int getInt() const { return m_int; }
	const AsciiString &getString() const { return m_string; }

	unsigned char m_beforeInt[8];
	Int m_int;
	float m_real;
	AsciiString m_string;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Money.h
struct Money
{
	unsigned char m_beforeValue[4];
	Int m_money;
};

// Money is inline at Player+0x48; the other two sub-objects are reached at
// their own offsets through their own retail bodies, so they stay opaque here.
struct BfmePlayerMoney
{
	unsigned char m_beforeMoney[0x48];
	Money m_money;
};

class PlayerCommandPoints
{
};

class PlayerLightPoints
{
};

// PlayerKills uses the retail StringBase layout here: the generated body reads
// a ushort length at data+4 and compares data+8 inline.  The caller-side
// AsciiString remains the canonical StringInline ABI; this view is only the
// BFME PlayerKills member access proved by 0x000E9B20 and the named counter
// caller at 0x002F6920.
struct BfmePlayerKillsStringData
{
	char m_pad00[4];
	unsigned short m_length;
	unsigned short m_pad06;
	char m_text[1];
};

class BfmePlayerKillsStringView
{
public:
	Int compare(const BfmePlayerKillsStringView &other) const
	{
		const BfmePlayerKillsStringView *that = &other;
		const BfmePlayerKillsStringView *self = this;
		Int thatLen = that->m_data ? that->m_data->m_length : 0;
		const char *thatData = that->m_data ? &that->m_data->m_text[0] : g_bfmeEmptyAscii;
		Int thisLen = self->m_data ? self->m_data->m_length : 0;
		const char *thisData = self->m_data ? &self->m_data->m_text[0] : g_bfmeEmptyAscii;
		Int c = memcmp(thisData, thatData,
			(unsigned int)(thisLen < thatLen ? thisLen : thatLen));
		if (c != 0)
			return c;
		return thisLen - thatLen;
	}

	BfmePlayerKillsStringData *m_data;
};

// GameLogic's buildable override and the retail body both place the
// ThingTemplate name at +0x20.  PlayerKills owns 32 adjacent map objects;
// each STLport map is the 12-byte header walked by the retail outer loop.
class BfmePlayerKillsThingTemplateView
{
public:
	char m_beforeName[0x20];
	BfmePlayerKillsStringView m_name;
};

typedef _STL::map<const BfmePlayerKillsThingTemplateView *, Int>
	BfmePlayerKillsMap;

struct PlayerKills
{
	Int getKillsOfType(const AsciiString &objectType);

private:
	char m_beforeKills[0x150];
	BfmePlayerKillsMap m_kills[0x20];
};

Int PlayerKills::getKillsOfType(const AsciiString &objectType)
{
	Int count = 0;
	for (Int i = 0; i < 0x20; ++i)
	{
		for (BfmePlayerKillsMap::iterator it = m_kills[i].begin();
			it != m_kills[i].end(); ++it)
		{
			Int kills = it->second;
			const BfmePlayerKillsThingTemplateView *theTemplate = it->first;
			if (theTemplate && theTemplate->m_name.compare(
				*(const BfmePlayerKillsStringView *)&objectType) == 0)
				count += kills;
		}
	}
	return count;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	unsigned char m_beforeCommandPoints[0x30];
	PlayerCommandPoints m_commandPoints;
	unsigned char m_beforeKills[0x317];
	PlayerKills m_kills;

	Int rva000D4730CountObjects(UnsignedInt bitIndex, Int limit) const;
};

struct UnitExperience
{
	unsigned char m_beforeExperience[0xc];
	float m_experience;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
private:
	unsigned char m_beforeExperience[0x210];

public:
	UnitExperience *m_experience;
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

extern void j_000142b3();
extern void j_00047d34();
extern void j_0003deb0();
extern void j_0001af23();
extern void j_00004e3f();
extern void j_00020dc9();

// The 288-entry ModelConditionFlags name table is reached through the retail
// ILT shared by the already-converted BitFlags setter at 0x001C62B0.
extern Int bfmeLookup_001c62b0(void *name);

class BfmeGetCounterCall
{
};

struct BfmeCommandPointsCall
{
	Int call(Int includeReserved);
};

struct BfmeTotalCommandPointsCall
{
	Int call();
};

static __forceinline int bfmeGetLightPoints(Player *player)
{
	typedef int (PlayerLightPoints::*Function)();
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00047d34;
	return (reinterpret_cast<PlayerLightPoints *>(player)->*fn.member)();
}

static __forceinline int bfmeCommandPointsUsed(PlayerCommandPoints *points)
{
	typedef int (BfmeCommandPointsCall::*Function)(int);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0003deb0;
	return (reinterpret_cast<BfmeCommandPointsCall *>(points)->*fn.member)(1);
}

static __forceinline int bfmeCommandPointsAvailable(PlayerCommandPoints *points)
{
	typedef int (BfmeCommandPointsCall::*Function)(int);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_0001af23;
	return (reinterpret_cast<BfmeCommandPointsCall *>(points)->*fn.member)(1);
}

static __forceinline int bfmeCommandPointsTotal(PlayerCommandPoints *points)
{
	typedef int (BfmeTotalCommandPointsCall::*Function)();
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00004e3f;
	return (reinterpret_cast<BfmeTotalCommandPointsCall *>(points)->*fn.member)();
}

static __forceinline int bfmeGetKillsOfType(PlayerKills *kills,
	const AsciiString &objectType)
{
	typedef int (PlayerKills::*Function)(const AsciiString &);
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00020dc9;
	return (kills->*fn.member)(objectType);
}

static __forceinline Player *bfmePlayerFromParameter(Parameter *player)
{
	unsigned short mask =
		((BfmeScriptEngine_getPlayerMaskFromAsciiString *)TheScriptEngine)
			->getPlayerMaskFromAsciiString(player->m_string, 0);
	if (!mask)
		return 0;
	return ThePlayerList->getPlayerFromMask(mask);
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doCounterMathCounter(Parameter *counter, Parameter *operation,
		Parameter *otherCounter);
	void doCounterMathValue(Parameter *counter, Parameter *operation,
		Parameter *value);
	void doSetPlayerMoneyToCounter(Parameter *player, Parameter *counter);
	void doSetPlayerLightPointsToCounter(Parameter *player, Parameter *counter);
	void doSetUnitExperienceToCounter(const AsciiString &unit,
		Parameter *counter);
	void doSetPlayerCommandPointsUsedToCounter(Parameter *player,
		Parameter *counter);
	void doSetPlayerCommandPointsAvailableToCounter(Parameter *player,
		Parameter *counter);
	void doSetPlayerCommandPointsTotalToCounter(Parameter *player,
		Parameter *counter);
	void doSetPlayerKillsOfTypeToCounter(Parameter *player,
		Parameter *objectType, Parameter *counter);
	void doSetCounterToNumberObjectsPlayerOwnesWithModelCondition(
		const AsciiString &playerName, const AsciiString &modelConditionName,
		const AsciiString &counterName);
};

void ScriptActions::doCounterMathCounter(Parameter *counter,
	Parameter *operation, Parameter *otherCounter)
{
	ScriptCounter *destination;
	int result;
	const ScriptCounter *source;
	destination = TheScriptEngine->bfmeCounter(counter->getString());
	result = destination->m_value;
	int value;
	value = 0;
	typedef const ScriptCounter *(BfmeGetCounterCall::*GetCounterFunction)(AsciiString);
	union { void (*raw)(void); GetCounterFunction member; } getCounter;
	getCounter.raw = j_000142b3;
	source = (reinterpret_cast<BfmeGetCounterCall *>(TheScriptEngine)
		->*getCounter.member)(otherCounter->getString());
	if (source)
		value = source->m_value;

	switch (operation->getInt())
	{
	case 0:
		result += value;
		break;
	case 1:
		result -= value;
		break;
	case 2:
		result *= value;
		break;
	case 3:
		result /= value;
		break;
	}
	destination->m_value = result;
}

void ScriptActions::doCounterMathValue(Parameter *counter,
	Parameter *operation, Parameter *value)
{
	ScriptCounter *destination = TheScriptEngine->bfmeCounter(
		counter->getString());
	int result = destination->m_value;
	int operand = value->getInt();

	switch (operation->getInt())
	{
	case 0:
		result += operand;
		break;
	case 1:
		result -= operand;
		break;
	case 2:
		result *= operand;
		break;
	case 3:
		result /= operand;
		break;
	}
	destination->m_value = result;
}

void ScriptActions::doSetPlayerMoneyToCounter(Parameter *player,
	Parameter *counter)
{
	int value = 0;
	unsigned short mask =
		((BfmeScriptEngine_getPlayerMaskFromAsciiString *)TheScriptEngine)
			->getPlayerMaskFromAsciiString(player->m_string, 0);
	if (mask)
	{
		do
		{
			Player *thePlayer = ThePlayerList->getEachPlayerFromMask(mask);
			if (thePlayer)
			{
				Money *money = &((BfmePlayerMoney *)thePlayer)->m_money;
				if (money)
					value += money->m_money;
			}
		} while (mask);
	}

	ScriptCounter *destination =
		((ScriptEngine *)TheScriptEngine)->bfmeCounter(counter->m_string);
	destination->m_value = value;
}

void ScriptActions::doSetPlayerLightPointsToCounter(Parameter *player,
	Parameter *counter)
{
	int value = 0;
	unsigned short mask =
		((BfmeScriptEngine_getPlayerMaskFromAsciiString *)TheScriptEngine)
			->getPlayerMaskFromAsciiString(player->m_string, 0);
	if (mask)
	{
		do
		{
			Player *thePlayer = ThePlayerList->getEachPlayerFromMask(mask);
			if (thePlayer)
				value += bfmeGetLightPoints(thePlayer);
		} while (mask);
	}

	ScriptCounter *destination =
		((ScriptEngine *)TheScriptEngine)->bfmeCounter(counter->m_string);
	destination->m_value = value;
}

void ScriptActions::doSetUnitExperienceToCounter(const AsciiString &unit,
	Parameter *counter)
{
	Object *object = TheScriptEngine->getUnitNamed(unit);
	if (object)
	{
		UnitExperience *experience = object->m_experience;
		if (experience)
		{
			ScriptCounter *destination = TheScriptEngine->bfmeCounter(
				counter->m_string);
			destination->m_value = (int)experience->m_experience;
		}
	}
}

void ScriptActions::doSetPlayerCommandPointsUsedToCounter(Parameter *player,
	Parameter *counter)
{
	Player *thePlayer = bfmePlayerFromParameter(player);
	if (thePlayer)
	{
		int value = bfmeCommandPointsUsed(&thePlayer->m_commandPoints);
		ScriptCounter *destination = TheScriptEngine->bfmeCounter(
			counter->m_string);
		destination->m_value = value;
	}
}

void ScriptActions::doSetPlayerCommandPointsAvailableToCounter(
	Parameter *player, Parameter *counter)
{
	Player *thePlayer = bfmePlayerFromParameter(player);
	if (thePlayer)
	{
		int value = bfmeCommandPointsAvailable(&thePlayer->m_commandPoints);
		ScriptCounter *destination = TheScriptEngine->bfmeCounter(
			counter->m_string);
		destination->m_value = value;
	}
}

void ScriptActions::doSetPlayerCommandPointsTotalToCounter(Parameter *player,
	Parameter *counter)
{
	Player *thePlayer = bfmePlayerFromParameter(player);
	if (thePlayer)
	{
		int value = bfmeCommandPointsTotal(&thePlayer->m_commandPoints);
		ScriptCounter *destination = TheScriptEngine->bfmeCounter(
			counter->m_string);
		destination->m_value = value;
	}
}

void ScriptActions::doSetPlayerKillsOfTypeToCounter(Parameter *player,
	Parameter *objectType, Parameter *counter)
{
	unsigned short mask =
		((BfmeScriptEngine_getPlayerMaskFromAsciiString *)TheScriptEngine)
			->getPlayerMaskFromAsciiString(player->m_string, 0);
	if (!mask)
		return;

	Player *thePlayer = ThePlayerList->getPlayerFromMask(mask);
	if (!thePlayer)
		return;

	PlayerKills *kills = &thePlayer->m_kills;
	if (!kills)
		return;

	int value = bfmeGetKillsOfType(kills, objectType->m_string);
	ScriptCounter *destination =
		((ScriptEngine *)TheScriptEngine)->bfmeCounter(counter->m_string);
	destination->m_value = value;
}

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
