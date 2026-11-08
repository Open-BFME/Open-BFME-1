// cl: /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?evaluatePlayerSpecialPowerFromUnitComplete@ScriptConditions@@IAE_NPAVParameter@@00@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluatePlayerSpecialPowerFromUnitMidway@ScriptConditions@@IAE_NPAVParameter@@00@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluatePlayerSpecialPowerFromUnitTriggered@ScriptConditions@@IAE_NPAVParameter@@00@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluateUpgradeFromUnitComplete@ScriptConditions@@IAE_NPAVParameter@@00@Z: game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// Open-BFME5 conversions.

typedef int Int;
typedef bool Bool;
typedef unsigned short PlayerMaskType;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameType.h
enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_TO_LONG_SIZE = 0x7ffffff
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
#include "ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	const AsciiString &getString(void) const { return m_string; }

private:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	ObjectID getID(void) const { return m_id; }

private:
	unsigned char m_beforeID[0x74];
	ObjectID m_id;
};

// Player (upstream Player.h m_playerIndex; retail reads it at +0x24, see
// RTS/Player.cpp:638).
class Player
{
public:
	char m_bfmePad[0x24];
	Int m_playerIndex;
};

// PlayerList (ThePlayerList shares g_bfmeD1088's address); getEachPlayerFromMask is
// the ILT-called row at the pinned name. The global is retail's ThePlayerList,
// declared with the defining spelling ?ThePlayerList@@3PAVPlayerList@@A.
class PlayerList
{
public:
	Player *getEachPlayerFromMask(unsigned short &mask);
};

// ScriptEngine's player-mask resolver is the pinned row at 0x0034DB40.
class ScriptEngine
{
public:
	unsigned short unidentified_0034DB40(Parameter *parameter);
};

// ScriptEngine (TheScriptEngine shares g_bfmeP1088's address): this view carries
// only the vtable slots the bodies below call.
class BfmeP1088
{
public:
	virtual void bfmeSlot1088P_0(void);
	virtual void bfmeSlot1088P_1(void);
	virtual void bfmeSlot1088P_2(void);
	virtual void bfmeSlot1088P_3(void);
	virtual void bfmeSlot1088P_4(void);
	virtual void bfmeSlot1088P_5(void);
	virtual void bfmeSlot1088P_6(void);
	virtual void bfmeSlot1088P_7(void);
	virtual void bfmeSlot1088P_8(void);
	virtual void bfmeSlot1088P_9(void);
	virtual void bfmeSlot1088P_10(void);
	virtual void bfmeSlot1088P_11(void);
	virtual void bfmeSlot1088P_12(void);
	virtual void bfmeSlot1088P_13(void);
	virtual void bfmeSlot1088P_14(void);
	virtual void bfmeSlot1088P_15(void);
	virtual void bfmeSlot1088P_16(void);
	virtual void bfmeSlot1088P_17(void);
	virtual void bfmeSlot1088P_18(void);
	virtual void bfmeSlot1088P_19(void);
	virtual void bfmeSlot1088P_20(void);
	virtual void bfmeSlot1088P_21(void);
	virtual void bfmeSlot1088P_22(void);
	virtual void bfmeSlot1088P_23(void);
	virtual void bfmeSlot1088P_24(void);
	virtual void bfmeSlot1088P_25(void);
	virtual Object *getUnitNamed(const AsciiString &unitName);	// slot 26, vtable+0x68
	virtual void bfmeSlot1088P_27(void);
	virtual void bfmeSlot1088P_28(void);
	virtual void bfmeSlot1088P_29(void);
	virtual void bfmeSlot1088P_30(void);
	virtual void bfmeSlot1088P_31(void);
	virtual void bfmeSlot1088P_32(void);
	virtual void bfmeSlot1088P_33(void);
	virtual void bfmeSlot1088P_34(void);
	virtual void bfmeSlot1088P_35(void);
	virtual void bfmeSlot1088P_36(void);
	virtual void bfmeSlot1088P_37(void);
	virtual void bfmeSlot1088P_38(void);
	virtual void bfmeSlot1088P_39(void);
	virtual void bfmeSlot1088P_40(void);
	virtual void bfmeSlot1088P_41(void);
	virtual void bfmeSlot1088P_42(void);
	virtual void bfmeSlot1088P_43(void);
	virtual void bfmeSlot1088P_44(void);
	virtual Bool isSpecialPowerTriggered(Int playerIndex, const AsciiString &completedPower, Bool removeFromList, ObjectID sourceObj);
	virtual Bool isSpecialPowerMidway(Int playerIndex, const AsciiString &completedPower, Bool removeFromList, ObjectID sourceObj);
	virtual Bool isSpecialPowerComplete(Int playerIndex, const AsciiString &completedPower, Bool removeFromList, ObjectID sourceObj);
	virtual Bool isUpgradeComplete(Int playerIndex, const AsciiString &upgrade, Bool removeFromList, ObjectID sourceObj);
	virtual void bfmeSlot1088P_49(void);
};

// 0x012F076C is retail's TheScriptEngine singleton; the class is declared by
// GameLogic/ScriptEngine/script_engine.h; the BfmeP1088 surface above is only the
// stand-in for the vtable slots this body calls, so the real global is
// reinterpreted at each call.
extern PlayerList *ThePlayerList;
extern ScriptEngine *TheScriptEngine;

// Retail keeps the resolver's whole EAX (no zero-extension of the 16-bit mask),
// so the row is called through its own symbol with an int result view.
static __forceinline int nextPlayerMask(Parameter *parameter)
{
	typedef int (ScriptEngine::*Raw)(Parameter *);
	Raw raw = reinterpret_cast<Raw>(&ScriptEngine::unidentified_0034DB40);
	return (TheScriptEngine->*raw)(parameter);
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptConditions.h
class ScriptConditions
{
protected:
	Bool evaluatePlayerSpecialPowerFromUnitTriggered(
		Parameter *pPlayerParm, Parameter *pSpecialPowerParm, Parameter *pUnitParm);
	Bool evaluatePlayerSpecialPowerFromUnitMidway(
		Parameter *pPlayerParm, Parameter *pSpecialPowerParm, Parameter *pUnitParm);
	Bool evaluatePlayerSpecialPowerFromUnitComplete(
		Parameter *pPlayerParm, Parameter *pSpecialPowerParm, Parameter *pUnitParm);
	Bool evaluateUpgradeFromUnitComplete(
		Parameter *pPlayerParm, Parameter *pUpgradeParm, Parameter *pUnitParm);
};

// BFME resolves the player Parameter to a PlayerMaskType and asks every player
// in it, where Zero Hour's playerFromParam yielded one Player. Retail hands the
// unit Parameter's own address to getUnitNamed as the AsciiString reference.

// ?evaluatePlayerSpecialPowerFromUnitTriggered@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluatePlayerSpecialPowerFromUnitTriggered(
	Parameter *pPlayerParm, Parameter *pSpecialPowerParm, Parameter *pUnitParm)
{
	ObjectID sourceID = INVALID_ID;

	if (pUnitParm) {
		Object *pUnit = reinterpret_cast<BfmeP1088 *>(TheScriptEngine)->getUnitNamed(*reinterpret_cast<const AsciiString *>(pUnitParm));

		if (!pUnit)
			return false;
		sourceID = pUnit->getID();
	}
	PlayerMaskType playerMask = nextPlayerMask(pPlayerParm);
	while (playerMask) {
		Player *pPlayer = ThePlayerList->getEachPlayerFromMask(playerMask);

		if (pPlayer) {
			Int playerIndex = pPlayer->m_playerIndex;

			if (reinterpret_cast<BfmeP1088 *>(TheScriptEngine)->isSpecialPowerTriggered(playerIndex, pSpecialPowerParm->getString(), true, sourceID))
				return true;
		}
	}
	return false;
}

// ?evaluatePlayerSpecialPowerFromUnitMidway@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluatePlayerSpecialPowerFromUnitMidway(
	Parameter *pPlayerParm, Parameter *pSpecialPowerParm, Parameter *pUnitParm)
{
	ObjectID sourceID = INVALID_ID;

	if (pUnitParm) {
		Object *pUnit = reinterpret_cast<BfmeP1088 *>(TheScriptEngine)->getUnitNamed(*reinterpret_cast<const AsciiString *>(pUnitParm));

		if (!pUnit)
			return false;
		sourceID = pUnit->getID();
	}
	PlayerMaskType playerMask = nextPlayerMask(pPlayerParm);
	while (playerMask) {
		Player *pPlayer = ThePlayerList->getEachPlayerFromMask(playerMask);

		if (pPlayer) {
			Int playerIndex = pPlayer->m_playerIndex;

			if (reinterpret_cast<BfmeP1088 *>(TheScriptEngine)->isSpecialPowerMidway(playerIndex, pSpecialPowerParm->getString(), true, sourceID))
				return true;
		}
	}
	return false;
}

// ?evaluatePlayerSpecialPowerFromUnitComplete@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluatePlayerSpecialPowerFromUnitComplete(
	Parameter *pPlayerParm, Parameter *pSpecialPowerParm, Parameter *pUnitParm)
{
	ObjectID sourceID = INVALID_ID;

	if (pUnitParm) {
		Object *pUnit = reinterpret_cast<BfmeP1088 *>(TheScriptEngine)->getUnitNamed(*reinterpret_cast<const AsciiString *>(pUnitParm));

		if (!pUnit)
			return false;
		sourceID = pUnit->getID();
	}
	PlayerMaskType playerMask = nextPlayerMask(pPlayerParm);
	while (playerMask) {
		Player *pPlayer = ThePlayerList->getEachPlayerFromMask(playerMask);

		if (pPlayer) {
			Int playerIndex = pPlayer->m_playerIndex;

			if (reinterpret_cast<BfmeP1088 *>(TheScriptEngine)->isSpecialPowerComplete(playerIndex, pSpecialPowerParm->getString(), true, sourceID))
				return true;
		}
	}
	return false;
}

// ?evaluateUpgradeFromUnitComplete@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluateUpgradeFromUnitComplete(
	Parameter *pPlayerParm, Parameter *pUpgradeParm, Parameter *pUnitParm)
{
	ObjectID sourceID = INVALID_ID;

	if (pUnitParm) {
		Object *pUnit = reinterpret_cast<BfmeP1088 *>(TheScriptEngine)->getUnitNamed(*reinterpret_cast<const AsciiString *>(pUnitParm));

		if (!pUnit)
			return false;
		sourceID = pUnit->getID();
	}
	PlayerMaskType playerMask = nextPlayerMask(pPlayerParm);
	while (playerMask) {
		Player *pPlayer = ThePlayerList->getEachPlayerFromMask(playerMask);

		if (pPlayer) {
			Int playerIndex = pPlayer->m_playerIndex;

			if (reinterpret_cast<BfmeP1088 *>(TheScriptEngine)->isUpgradeComplete(playerIndex, pUpgradeParm->getString(), true, sourceID))
				return true;
		}
	}
	return false;
}
