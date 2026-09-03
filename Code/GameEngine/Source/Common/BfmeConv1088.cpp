// readable body of ?evaluatePlayerSpecialPowerFromUnitComplete@ScriptConditions@@IAE_NPAVParameter@@00@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluatePlayerSpecialPowerFromUnitMidway@ScriptConditions@@IAE_NPAVParameter@@00@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluatePlayerSpecialPowerFromUnitTriggered@ScriptConditions@@IAE_NPAVParameter@@00@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// readable body of ?evaluateUpgradeFromUnitComplete@ScriptConditions@@IAE_NPAVParameter@@00@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// Open-BFME5 conversions.

struct BfmeE1088
{
	char m_bfmePad[0x74];
	int m_bfme74;
};

struct BfmeR1088
{
	char m_bfmePad[0x24];
	int m_bfme24;
};

class BfmeD1088
{
public:
	BfmeR1088 *bfmeLook1088(short *h);
};

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
	virtual BfmeE1088 *bfmeSlot1088P_26(int a);
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
	virtual char bfmeSlot1088P_45(int a, int b, int c, int d);
	virtual char bfmeSlot1088P_46(int a, int b, int c, int d);
	virtual char bfmeSlot1088P_47(int a, int b, int c, int d);
	virtual char bfmeSlot1088P_48(int a, int b, int c, int d);
	virtual void bfmeSlot1088P_49(void);
	int bfmeNext1088(int a);
};

extern BfmeD1088 *g_bfmeD1088;
extern BfmeP1088 *g_bfmeP1088;

class Parameter;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptConditions.h
class ScriptConditions
{
protected:
	bool evaluatePlayerSpecialPowerFromUnitTriggered(
		Parameter *playerParm, Parameter *specialPowerParm, Parameter *unitParm);
	bool evaluatePlayerSpecialPowerFromUnitMidway(
		Parameter *playerParm, Parameter *specialPowerParm, Parameter *unitParm);
	bool evaluatePlayerSpecialPowerFromUnitComplete(
		Parameter *playerParm, Parameter *specialPowerParm, Parameter *unitParm);
	bool evaluateUpgradeFromUnitComplete(
		Parameter *playerParm, Parameter *upgradeParm, Parameter *unitParm);
};

// ?evaluatePlayerSpecialPowerFromUnitTriggered@ScriptConditions@@IAE_NPAVParameter@@00@Z
bool ScriptConditions::evaluatePlayerSpecialPowerFromUnitTriggered(
	Parameter *playerParm, Parameter *specialPowerParm, Parameter *unitParm)
{
	int sourceID = 0;

	if (unitParm) {
		BfmeE1088 *unit = g_bfmeP1088->bfmeSlot1088P_26(
			reinterpret_cast<int>(unitParm));

		if (!unit)
			return false;
		sourceID = unit->m_bfme74;
	}
	unitParm = reinterpret_cast<Parameter *>(
		g_bfmeP1088->bfmeNext1088(reinterpret_cast<int>(playerParm)));
	while ((short)reinterpret_cast<int>(unitParm)) {
		BfmeR1088 *player = g_bfmeD1088->bfmeLook1088(
			reinterpret_cast<short *>(&unitParm));

		if (player) {
			int playerIndex = player->m_bfme24;

			if (g_bfmeP1088->bfmeSlot1088P_45(
					playerIndex,
					reinterpret_cast<int>(specialPowerParm) + 0x10,
					1,
					sourceID))
				return true;
		}
	}
	return false;
}

// ?evaluatePlayerSpecialPowerFromUnitMidway@ScriptConditions@@IAE_NPAVParameter@@00@Z
bool ScriptConditions::evaluatePlayerSpecialPowerFromUnitMidway(
	Parameter *playerParm, Parameter *specialPowerParm, Parameter *unitParm)
{
	int sourceID = 0;

	if (unitParm) {
		BfmeE1088 *unit = g_bfmeP1088->bfmeSlot1088P_26(
			reinterpret_cast<int>(unitParm));

		if (!unit)
			return false;
		sourceID = unit->m_bfme74;
	}
	unitParm = reinterpret_cast<Parameter *>(
		g_bfmeP1088->bfmeNext1088(reinterpret_cast<int>(playerParm)));
	while ((short)reinterpret_cast<int>(unitParm)) {
		BfmeR1088 *player = g_bfmeD1088->bfmeLook1088(
			reinterpret_cast<short *>(&unitParm));

		if (player) {
			int playerIndex = player->m_bfme24;

			if (g_bfmeP1088->bfmeSlot1088P_46(
					playerIndex,
					reinterpret_cast<int>(specialPowerParm) + 0x10,
					1,
					sourceID))
				return true;
		}
	}
	return false;
}

// ?evaluatePlayerSpecialPowerFromUnitComplete@ScriptConditions@@IAE_NPAVParameter@@00@Z
bool ScriptConditions::evaluatePlayerSpecialPowerFromUnitComplete(
	Parameter *playerParm, Parameter *specialPowerParm, Parameter *unitParm)
{
	int sourceID = 0;

	if (unitParm) {
		BfmeE1088 *unit = g_bfmeP1088->bfmeSlot1088P_26(
			reinterpret_cast<int>(unitParm));

		if (!unit)
			return false;
		sourceID = unit->m_bfme74;
	}
	unitParm = reinterpret_cast<Parameter *>(
		g_bfmeP1088->bfmeNext1088(reinterpret_cast<int>(playerParm)));
	while ((short)reinterpret_cast<int>(unitParm)) {
		BfmeR1088 *player = g_bfmeD1088->bfmeLook1088(
			reinterpret_cast<short *>(&unitParm));

		if (player) {
			int playerIndex = player->m_bfme24;

			if (g_bfmeP1088->bfmeSlot1088P_47(
					playerIndex,
					reinterpret_cast<int>(specialPowerParm) + 0x10,
					1,
					sourceID))
				return true;
		}
	}
	return false;
}

// ?evaluateUpgradeFromUnitComplete@ScriptConditions@@IAE_NPAVParameter@@00@Z
bool ScriptConditions::evaluateUpgradeFromUnitComplete(
	Parameter *playerParm, Parameter *upgradeParm, Parameter *unitParm)
{
	int sourceID = 0;

	if (unitParm) {
		BfmeE1088 *unit = g_bfmeP1088->bfmeSlot1088P_26(
			reinterpret_cast<int>(unitParm));

		if (!unit)
			return false;
		sourceID = unit->m_bfme74;
	}
	unitParm = reinterpret_cast<Parameter *>(
		g_bfmeP1088->bfmeNext1088(reinterpret_cast<int>(playerParm)));
	while ((short)reinterpret_cast<int>(unitParm)) {
		BfmeR1088 *player = g_bfmeD1088->bfmeLook1088(
			reinterpret_cast<short *>(&unitParm));

		if (player) {
			int playerIndex = player->m_bfme24;

			if (g_bfmeP1088->bfmeSlot1088P_48(
					playerIndex,
					reinterpret_cast<int>(upgradeParm) + 0x10,
					1,
					sourceID))
				return true;
		}
	}
	return false;
}
