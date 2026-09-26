// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// FILE: ScriptEngineGetQualifiedTriggerAreaByName.cpp ///////////////////////
//
// ScriptEngine::getQualifiedTriggerAreaByName, retail 0x0034CF60 (526 bytes).
//
// Identity: ScriptEngine vtable 0x010E7A30 slot 22 (+0x58) reaches this body
// through ILT 0x000352F6, and the landed ScriptConditions callers
// (evaluateSkirmishNamedAreaExists 0x00325680, evaluateNamedExitedArea
// 0x00324DE0) dispatch getQualifiedTriggerAreaByName through +0x58.  The
// literals it pushes -- "[Skirmish]MyInnerPerimeter" ... "OuterPerimeter",
// "%s%d", "!!!WARNING!!! Trigger area '" and "' not found." -- are Zero
// Hour's ScriptEngine.cpp body line for line.  Slot order agrees with ZH:
// slot 19 is getCurrentPlayer (0x0033DA70), slot 20 getObjectTypes
// (0x0034CE80), slot 21 0x0034E370, then this one.
//
// Player::getCurrentEnemy is reached through ILT 0x00015438 at the body the
// ledger holds as Rva000C9420::call (reads Player+0x220 m_ai, tail-calls its
// slot +0x30); the call is spelled with that ledger name.
//
///////////////////////////////////////////////////////////////////////////////

typedef bool Bool;
typedef int Int;

#include <string.h>
#include "ascii_string.h"

// Retail inlines both concats: the AsciiString one reads length/data from the
// header, the literal one pushes its strlen as an immediate.
template <> inline void StringBase<char>::concat(const StringBase<char> &s)
{
	const int len = s.m_data ? s.m_data->length : 0;
	const char *data = s.m_data ? &s.m_data->data[0] : "";
	concat(data, len);
}
template <> inline void StringBase<char>::concat(const char *s) { concat(s, (int)strlen(s)); }

#define MY_INNER_PERIMETER "[Skirmish]MyInnerPerimeter"
#define MY_OUTER_PERIMETER "[Skirmish]MyOuterPerimeter"
#define ENEMY_INNER_PERIMETER "[Skirmish]EnemyInnerPerimeter"
#define ENEMY_OUTER_PERIMETER "[Skirmish]EnemyOuterPerimeter"
#define INNER_PERIMETER "InnerPerimeter"
#define OUTER_PERIMETER "OuterPerimeter"

class PolygonTrigger;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
	unsigned char m_pad[0x224];
	Int m_mpStartIndex;		// +0x224, read where ZH calls getMpStartIndex

public:
	Int getMpStartIndex(void) const { return m_mpStartIndex; }
};

// Player::getCurrentEnemy (ZH), held by the ledger under this address name.
class Rva000C9420
{
public:
	Int call(void);
};

// Only the one slot this body reaches is spelled out; the padding puts it at
// vtable +0x90 (same slot INIAerialPathfindNoFlyZone.cpp dispatches).
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	virtual void _bfme_pad_00() = 0;
	virtual void _bfme_pad_01() = 0;
	virtual void _bfme_pad_02() = 0;
	virtual void _bfme_pad_03() = 0;
	virtual void _bfme_pad_04() = 0;
	virtual void _bfme_pad_05() = 0;
	virtual void _bfme_pad_06() = 0;
	virtual void _bfme_pad_07() = 0;
	virtual void _bfme_pad_08() = 0;
	virtual void _bfme_pad_09() = 0;
	virtual void _bfme_pad_10() = 0;
	virtual void _bfme_pad_11() = 0;
	virtual void _bfme_pad_12() = 0;
	virtual void _bfme_pad_13() = 0;
	virtual void _bfme_pad_14() = 0;
	virtual void _bfme_pad_15() = 0;
	virtual void _bfme_pad_16() = 0;
	virtual void _bfme_pad_17() = 0;
	virtual void _bfme_pad_18() = 0;
	virtual void _bfme_pad_19() = 0;
	virtual void _bfme_pad_20() = 0;
	virtual void _bfme_pad_21() = 0;
	virtual void _bfme_pad_22() = 0;
	virtual void _bfme_pad_23() = 0;
	virtual void _bfme_pad_24() = 0;
	virtual void _bfme_pad_25() = 0;
	virtual void _bfme_pad_26() = 0;
	virtual void _bfme_pad_27() = 0;
	virtual void _bfme_pad_28() = 0;
	virtual void _bfme_pad_29() = 0;
	virtual void _bfme_pad_30() = 0;
	virtual void _bfme_pad_31() = 0;
	virtual void _bfme_pad_32() = 0;
	virtual void _bfme_pad_33() = 0;
	virtual void _bfme_pad_34() = 0;
	virtual void _bfme_pad_35() = 0;
	virtual PolygonTrigger *getTriggerAreaByName( AsciiString name ) = 0;	// +0x90
};

extern TerrainLogic *TheTerrainLogic;				// 0x012EF4CC

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void _bfme_pad_00(void) = 0;
	virtual void _bfme_pad_01(void) = 0;
	virtual void _bfme_pad_02(void) = 0;
	virtual void _bfme_pad_03(void) = 0;
	virtual void _bfme_pad_04(void) = 0;
	virtual void _bfme_pad_05(void) = 0;
	virtual void _bfme_pad_06(void) = 0;
	virtual void _bfme_pad_07(void) = 0;
	virtual void _bfme_pad_08(void) = 0;
	virtual void _bfme_pad_09(void) = 0;
	virtual void _bfme_pad_10(void) = 0;
	virtual void _bfme_pad_11(void) = 0;
	virtual void _bfme_pad_12(void) = 0;
	virtual void _bfme_pad_13(void) = 0;
	virtual void _bfme_pad_14(void) = 0;
	virtual void _bfme_pad_15(void) = 0;
	virtual void _bfme_pad_16(void) = 0;
	virtual void _bfme_pad_17(void) = 0;
	virtual void _bfme_pad_18(void) = 0;
	virtual Player *getCurrentPlayer(void) = 0;						// +0x4C
	virtual void _bfme_pad_20(void) = 0;
	virtual void _bfme_pad_21(void) = 0;
	virtual PolygonTrigger *getQualifiedTriggerAreaByName( AsciiString name );	// +0x58

	void AppendDebugMessage(const AsciiString &strToAdd, Bool forcePause);

private:
	char m_bfmeHead[0x170ac - 4];
	Player *m_currentPlayer;										// @0x170ac
};

PolygonTrigger *ScriptEngine::getQualifiedTriggerAreaByName( AsciiString name )
{
	if (name.compare(MY_INNER_PERIMETER) == 0 || name.compare(MY_OUTER_PERIMETER) == 0) {
		if (m_currentPlayer) {
			Int ndx = m_currentPlayer->getMpStartIndex()+1;
			if (name.compare(MY_INNER_PERIMETER) == 0) {
				name.format("%s%d", INNER_PERIMETER, ndx);
			}	else {
				name.format("%s%d", OUTER_PERIMETER, ndx);
			}
		}	else {
			return 0;
		}
	} else if (name.compare(ENEMY_INNER_PERIMETER) == 0 || name.compare(ENEMY_OUTER_PERIMETER) == 0) {

		Int mpNdx;
		mpNdx = -1;
		if (m_currentPlayer) {
			Player *enemy = (Player *)((Rva000C9420 *)getCurrentPlayer())->call();
			if (enemy) {
				mpNdx = enemy->getMpStartIndex()+1;
			}
		}
		if (name.compare(ENEMY_INNER_PERIMETER) == 0) {
			name.format("%s%d", INNER_PERIMETER, mpNdx);
		}	else {
			name.format("%s%d", OUTER_PERIMETER, mpNdx);
		}
	}
	PolygonTrigger *trig = TheTerrainLogic->getTriggerAreaByName(name);
	if (trig==0) {
		AsciiString msg = "!!!WARNING!!! Trigger area '";
		((StringBase<char> *)&msg)->concat(*(const StringBase<char> *)&name);
		((StringBase<char> *)&msg)->concat("' not found.");
		AppendDebugMessage(msg, true);
	}

	return trig;
}
