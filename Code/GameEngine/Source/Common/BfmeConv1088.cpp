// readable body of ?evaluatePlayerSpecialPowerFromUnitComplete@ScriptConditions@@IAE_NPAVParameter@@00@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluatePlayerSpecialPowerFromUnitMidway@ScriptConditions@@IAE_NPAVParameter@@00@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluatePlayerSpecialPowerFromUnitTriggered@ScriptConditions@@IAE_NPAVParameter@@00@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluateUpgradeFromUnitComplete@ScriptConditions@@IAE_NPAVParameter@@00@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// Open-BFME5 conversions.

typedef int Int;
typedef bool Bool;
typedef unsigned short PlayerMaskType;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameType.h
enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_TO_LONG_SIZE = 0x7ffffff
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
	char *m_text;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	const AsciiString &getString(void) const { return m_string; }

private:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	ObjectID getID(void) const { return m_id; }

private:
	unsigned char m_beforeID[0x74];
	ObjectID m_id;
};

// Player (upstream Player.h m_playerIndex; retail reads it at +0x24, see
// RTS/Player.cpp:638). The invented name stays because bfmeLook1088's
// symbols.csv pin mangles it.
struct BfmeR1088
{
	char m_bfmePad[0x24];
	Int m_playerIndex;
};

// PlayerList (ThePlayerList shares g_bfmeD1088's address); bfmeLook1088 is the
// getEachPlayerFromMask ILT thunk, pinned under this name.
class BfmeD1088
{
public:
	BfmeR1088 *bfmeLook1088(short *h);
};

// ScriptEngine (TheScriptEngine shares g_bfmeP1088's address). bfmeNext1088 is
// the pinned name of the resolver that turns a player Parameter into a mask.
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
	int bfmeNext1088(int a);
};

extern BfmeD1088 *g_bfmeD1088;
extern BfmeP1088 *g_bfmeP1088;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptConditions.h
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
		Object *pUnit = g_bfmeP1088->getUnitNamed(*reinterpret_cast<const AsciiString *>(pUnitParm));

		if (!pUnit)
			return false;
		sourceID = pUnit->getID();
	}
	PlayerMaskType playerMask = g_bfmeP1088->bfmeNext1088(reinterpret_cast<int>(pPlayerParm));
	while (playerMask) {
		BfmeR1088 *pPlayer = g_bfmeD1088->bfmeLook1088(reinterpret_cast<short *>(&playerMask));

		if (pPlayer) {
			Int playerIndex = pPlayer->m_playerIndex;

			if (g_bfmeP1088->isSpecialPowerTriggered(playerIndex, pSpecialPowerParm->getString(), true, sourceID))
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
		Object *pUnit = g_bfmeP1088->getUnitNamed(*reinterpret_cast<const AsciiString *>(pUnitParm));

		if (!pUnit)
			return false;
		sourceID = pUnit->getID();
	}
	PlayerMaskType playerMask = g_bfmeP1088->bfmeNext1088(reinterpret_cast<int>(pPlayerParm));
	while (playerMask) {
		BfmeR1088 *pPlayer = g_bfmeD1088->bfmeLook1088(reinterpret_cast<short *>(&playerMask));

		if (pPlayer) {
			Int playerIndex = pPlayer->m_playerIndex;

			if (g_bfmeP1088->isSpecialPowerMidway(playerIndex, pSpecialPowerParm->getString(), true, sourceID))
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
		Object *pUnit = g_bfmeP1088->getUnitNamed(*reinterpret_cast<const AsciiString *>(pUnitParm));

		if (!pUnit)
			return false;
		sourceID = pUnit->getID();
	}
	PlayerMaskType playerMask = g_bfmeP1088->bfmeNext1088(reinterpret_cast<int>(pPlayerParm));
	while (playerMask) {
		BfmeR1088 *pPlayer = g_bfmeD1088->bfmeLook1088(reinterpret_cast<short *>(&playerMask));

		if (pPlayer) {
			Int playerIndex = pPlayer->m_playerIndex;

			if (g_bfmeP1088->isSpecialPowerComplete(playerIndex, pSpecialPowerParm->getString(), true, sourceID))
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
		Object *pUnit = g_bfmeP1088->getUnitNamed(*reinterpret_cast<const AsciiString *>(pUnitParm));

		if (!pUnit)
			return false;
		sourceID = pUnit->getID();
	}
	PlayerMaskType playerMask = g_bfmeP1088->bfmeNext1088(reinterpret_cast<int>(pPlayerParm));
	while (playerMask) {
		BfmeR1088 *pPlayer = g_bfmeD1088->bfmeLook1088(reinterpret_cast<short *>(&playerMask));

		if (pPlayer) {
			Int playerIndex = pPlayer->m_playerIndex;

			if (g_bfmeP1088->isUpgradeComplete(playerIndex, pUpgradeParm->getString(), true, sourceID))
				return true;
		}
	}
	return false;
}
