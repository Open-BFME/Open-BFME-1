// cl: /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/GameEngine/Include
// readable body of ?evaluateCondition@ScriptConditions@@UAE_NPAVCondition@@@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
//
// The script condition template table, retail 0x003307E0, 19131 bytes.
//
// The ledger row names this ScriptConditions::evaluateCondition, which it
// provably is not: the body ends in a plain `ret`, so it takes no stack
// argument, and it appears in no vtable -- a `virtual bool
// evaluateCondition(Condition *)` would have to emit `ret 4` and be reachable
// through one. What it actually does is fill 175 condition templates. The row
// keeps the retail name so the ledger stays addressable and points at the real
// signature with object-symbol=.
//
// The object is ScriptEngine: m_conditionTemplates lands at +0x10720, which is
// exactly 543 * 0x7C past m_actionTemplates at +0x1C -- the array
// ScriptEngine::init (0x003107F0) fills with the same 0x7C Template records.
// The prefix is a blob here rather than an include because script_engine.h
// stops at the action table; only the offset matters to this function.
//
// Retail expands operator=(const char *) inline for the first 109 assignments
// -- `push strlen; push str; call StringBase<char>::set` with the length folded
// -- and calls it out of line for the remaining 730. The switch lands mid
// template (55's m_uiName inlines, its m_uiStrings[0] does not), so it is the
// compiler exhausting its per-function inline budget, not two source forms.
// Reproducing that cutoff needs the body visible here AND at the retail nesting
// depth: operator= -> set(const char *) -> stringLength. Flattening any level
// makes the budget last longer and the cutoff drift (155 or 309 expansions
// instead of 109), which moves every byte after 0x003311D4.
//
// Nine indices -- 59, 60, 67, 68, 72, 73, 115, 116 and 122 -- are never
// written, so the enum has holes. Index 13 is registered twice: NAMED_INSIDE_AREA
// goes in with four UI strings and is then overwritten with two. The second
// pass leaves the first pass's m_uiStrings[2] and [3] in place but puts
// m_numUiStrings back to 2, so they are dead. Shipped that way.

#include <string.h>
#include "ascii_string.h"

static inline int stringLength(const char *str)
{
	return str ? strlen(str) : 0;
}

template <> inline void StringBase<char>::set(const char *str)
{
	set(str, stringLength(str));
}

inline AsciiString &AsciiString::operator=(const char *str)
{
	((StringBase<char> *)this)->set(str);
	return *this;
}

// sizeof 0x7C, no vtable: `lea edi,[esi+0x10720]` points straight at m_uiName.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Template
{
public:
	AsciiString m_uiName;          // +0x00
	AsciiString m_uiName2;         // +0x04
	AsciiString m_internalName;    // +0x08
	int         m_internalNameKey; // +0x0C
	int         m_numUiStrings;    // +0x10
	AsciiString m_uiStrings[12];   // +0x14
	int         m_numParameters;   // +0x44
	int         m_parameters[12];  // +0x48
	int         m_pad;             // +0x78
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	void initConditionTemplates();

	char     m_pre[0x10720];
	Template m_conditionTemplates[184];
};

// ?evaluateCondition@ScriptConditions@@UAE_NPAVCondition@@@Z
void ScriptEngine::initConditionTemplates()
{

	Template *curTemplate;

	curTemplate = &m_conditionTemplates[0];
	curTemplate->m_internalName = "CONDITION_FALSE";
	curTemplate->m_uiName = "Scripting_/ False.";
	curTemplate->m_numParameters = 0;
	curTemplate->m_numUiStrings = 1;
	curTemplate->m_uiStrings[0] = "False.";

	curTemplate = &m_conditionTemplates[1];
	curTemplate->m_internalName = "COUNTER";
	curTemplate->m_uiName = "Scripting_/ Counter compared to a value.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 4;
	curTemplate->m_parameters[1] = 6;
	curTemplate->m_parameters[2] = 0;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = "Counter ";
	curTemplate->m_uiStrings[1] = " IS ";
	curTemplate->m_uiStrings[2] = " ";

	curTemplate = &m_conditionTemplates[112];
	curTemplate->m_internalName = "COUNTER_SECONDS";
	curTemplate->m_uiName = "Scripting_/ Counter compared to time in seconds.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 4;
	curTemplate->m_parameters[1] = 6;
	curTemplate->m_parameters[2] = 1;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = "Counter ";
	curTemplate->m_uiStrings[1] = " IS ";
	curTemplate->m_uiStrings[2] = " time ";
	curTemplate->m_uiStrings[3] = " secs. ";

	curTemplate = &m_conditionTemplates[111];
	curTemplate->m_internalName = "COUNTER_COUNTER";
	curTemplate->m_uiName = "Scripting_/ Counter compared to another Counter.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 4;
	curTemplate->m_parameters[1] = 6;
	curTemplate->m_parameters[2] = 4;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = "Counter ";
	curTemplate->m_uiStrings[1] = " IS ";
	curTemplate->m_uiStrings[2] = " counter ";

	curTemplate = &m_conditionTemplates[113];
	curTemplate->m_internalName = "DISTANCE_BETWEEN_OBJ";
	curTemplate->m_uiName = "Scripting_/ Compare distance between 2 objects.";
	curTemplate->m_numParameters = 4;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_parameters[1] = 14;
	curTemplate->m_parameters[2] = 6;
	curTemplate->m_parameters[3] = 1;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = "Distance between object ";
	curTemplate->m_uiStrings[1] = " and object ";
	curTemplate->m_uiStrings[2] = " IS ";
	curTemplate->m_uiStrings[3] = " to value ";

	curTemplate = &m_conditionTemplates[114];
	curTemplate->m_internalName = "DISTANCE_BETWEEN_TEAM";
	curTemplate->m_uiName = "Scripting_/ Compare distance between 2 teams.";
	curTemplate->m_numParameters = 4;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 3;
	curTemplate->m_parameters[2] = 6;
	curTemplate->m_parameters[3] = 1;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = "Distance between team ";
	curTemplate->m_uiStrings[1] = " and team ";
	curTemplate->m_uiStrings[2] = " IS ";
	curTemplate->m_uiStrings[3] = " to value ";

	curTemplate = &m_conditionTemplates[53];
	curTemplate->m_internalName = "UNIT_HEALTH";
	curTemplate->m_uiName = "Unit_/ Unit health % compared to a value.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_parameters[1] = 6;
	curTemplate->m_parameters[2] = 0;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " Health IS ";
	curTemplate->m_uiStrings[2] = " ";
	curTemplate->m_uiStrings[3] = " percent.";

	curTemplate = &m_conditionTemplates[2];
	curTemplate->m_internalName = "FLAG";
	curTemplate->m_uiName = "Scripting_/ Flag compared to a value.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 5;
	curTemplate->m_parameters[1] = 8;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " IS ";

	curTemplate = &m_conditionTemplates[11];
	curTemplate->m_internalName = "TEAM_STATE_IS";
	curTemplate->m_uiName = "Team_/ Team state is.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 18;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " state IS ";

	curTemplate = &m_conditionTemplates[12];
	curTemplate->m_internalName = "TEAM_STATE_IS_NOT";
	curTemplate->m_uiName = "Team_/ Team state is not.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 18;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " state IS NOT ";

	curTemplate = &m_conditionTemplates[143];
	curTemplate->m_internalName = "TEAM_HAS_CUSTOM_STATE";
	curTemplate->m_uiName = "Team_/ Team custom has state.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 18;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has the custom state ";

	curTemplate = &m_conditionTemplates[3];
	curTemplate->m_internalName = "CONDITION_TRUE";
	curTemplate->m_uiName = "Scripting_/ True.";
	curTemplate->m_numParameters = 0;
	curTemplate->m_numUiStrings = 1;
	curTemplate->m_uiStrings[0] = "True.";

	curTemplate = &m_conditionTemplates[4];
	curTemplate->m_internalName = "TIMER_EXPIRED";
	curTemplate->m_uiName = "Scripting_/ Timer expired.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 4;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = "Timer ";
	curTemplate->m_uiStrings[1] = " has expired.";

	curTemplate = &m_conditionTemplates[5];
	curTemplate->m_internalName = "PLAYER_ALL_DESTROYED";
	curTemplate->m_uiName = "Player_/ All destroyed.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = "Everything belonging to  ";
	curTemplate->m_uiStrings[1] = " has been destroyed.";

	curTemplate = &m_conditionTemplates[6];
	curTemplate->m_internalName = "PLAYER_ALL_BUILDFACILITIES_DESTROYED";
	curTemplate->m_uiName = "Player_/ All factories destroyed.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = "All factories belonging to  ";
	curTemplate->m_uiStrings[1] = " have been destroyed.";

	curTemplate = &m_conditionTemplates[7];
	curTemplate->m_internalName = "TEAM_INSIDE_AREA_PARTIALLY";
	curTemplate->m_uiName = "Team_/ Team has units in an area.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 9;
	curTemplate->m_parameters[2] = 37;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has one or more units in ";
	curTemplate->m_uiStrings[2] = " (";
	curTemplate->m_uiStrings[3] = ").";

	curTemplate = &m_conditionTemplates[13];
	curTemplate->m_internalName = "NAMED_INSIDE_AREA";
	curTemplate->m_uiName = "Unit_/ Unit entered area.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_parameters[1] = 9;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " is in ";
	curTemplate->m_uiStrings[2] = " (";
	curTemplate->m_uiStrings[3] = ").";

	curTemplate = &m_conditionTemplates[8];
	curTemplate->m_internalName = "TEAM_DESTROYED";
	curTemplate->m_uiName = "Team_/ Team is destroyed.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has been destroyed.";

	curTemplate = &m_conditionTemplates[170];
	curTemplate->m_internalName = "TEAM_HAS_FEWER_THAN_X_UNITS_WITH_KINDOF";
	curTemplate->m_uiName = "Team_/ Team has fewer than X units left of KindOf..";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 0;
	curTemplate->m_parameters[2] = 27;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = "";
	curTemplate->m_uiStrings[1] = " has fewer than ";
	curTemplate->m_uiStrings[2] = " units left of type ";
	curTemplate->m_uiStrings[3] = ".";

	curTemplate = &m_conditionTemplates[172];
	curTemplate->m_internalName = "NAMED_RANK_LEVEL";
	curTemplate->m_uiName = "Unit_/Experience/ Unit is rank level or above.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_parameters[1] = 0;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " is rank ";
	curTemplate->m_uiStrings[2] = " or above.";

	curTemplate = &m_conditionTemplates[15];
	curTemplate->m_internalName = "NAMED_DESTROYED";
	curTemplate->m_uiName = "Unit_/ Unit is destroyed.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has been destroyed.";

	curTemplate = &m_conditionTemplates[56];
	curTemplate->m_internalName = "NAMED_DYING";
	curTemplate->m_uiName = "Unit_/ Unit is dying.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has been killed, but still on screen.";

	curTemplate = &m_conditionTemplates[57];
	curTemplate->m_internalName = "NAMED_TOTALLY_DEAD";
	curTemplate->m_uiName = "Unit_/ Unit is finished dying.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has been killed, and is finished dying.";

	curTemplate = &m_conditionTemplates[55];
	curTemplate->m_internalName = "BRIDGE_BROKEN";
	curTemplate->m_uiName = "Unit_/ Bridge is broken.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 26;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has been broken.";

	curTemplate = &m_conditionTemplates[54];
	curTemplate->m_internalName = "BRIDGE_REPAIRED";
	curTemplate->m_uiName = "Unit_/ Bridge is repaired.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 26;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has been repaired.";

	curTemplate = &m_conditionTemplates[16];
	curTemplate->m_internalName = "NAMED_NOT_DESTROYED";
	curTemplate->m_uiName = "Unit_/ Unit exists and is alive.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " exists and is alive.";

	curTemplate = &m_conditionTemplates[10];
	curTemplate->m_internalName = "TEAM_HAS_UNITS";
	curTemplate->m_uiName = "Team_/ Team has units.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has one or more units.";

	curTemplate = &m_conditionTemplates[9];
	curTemplate->m_internalName = "CAMERA_MOVEMENT_FINISHED";
	curTemplate->m_uiName = "Camera_/ Camera movement finished.";
	curTemplate->m_numParameters = 0;
	curTemplate->m_numUiStrings = 1;
	curTemplate->m_uiStrings[0] = "The camera movement has finished.";

	curTemplate = &m_conditionTemplates[13];
	curTemplate->m_internalName = "NAMED_INSIDE_AREA";
	curTemplate->m_uiName = "Unit_/ Unit inside an area.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_parameters[1] = 9;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " is inside ";

	curTemplate = &m_conditionTemplates[14];
	curTemplate->m_internalName = "NAMED_OUTSIDE_AREA";
	curTemplate->m_uiName = "Unit_/ Unit outside an area.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_parameters[1] = 9;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " is outside ";

	curTemplate = &m_conditionTemplates[17];
	curTemplate->m_internalName = "TEAM_INSIDE_AREA_ENTIRELY";
	curTemplate->m_uiName = "Team_/ Team completely inside an area.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 9;
	curTemplate->m_parameters[2] = 37;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " is all inside ";
	curTemplate->m_uiStrings[2] = " (";
	curTemplate->m_uiStrings[3] = ").";

	curTemplate = &m_conditionTemplates[18];
	curTemplate->m_internalName = "TEAM_OUTSIDE_AREA_ENTIRELY";
	curTemplate->m_uiName = "Team_/ Team is completely outside an area.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 9;
	curTemplate->m_parameters[2] = 37;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " is completely outside ";
	curTemplate->m_uiStrings[2] = " (";
	curTemplate->m_uiStrings[3] = ").";

	curTemplate = &m_conditionTemplates[19];
	curTemplate->m_internalName = "NAMED_ATTACKED_BY_OBJECTTYPE";
	curTemplate->m_uiName = "Unit_/ Unit is attacked by a specific unit type.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_parameters[1] = 61;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has been attacked by a(n) ";

	curTemplate = &m_conditionTemplates[20];
	curTemplate->m_internalName = "TEAM_ATTACKED_BY_OBJECTTYPE";
	curTemplate->m_uiName = "Team_/ Team is attacked by a specific unit type.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 61;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has been attacked by a(n) ";

	curTemplate = &m_conditionTemplates[21];
	curTemplate->m_internalName = "NAMED_ATTACKED_BY_PLAYER";
	curTemplate->m_uiName = "Unit_/ Unit has been attacked by a player.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_parameters[1] = 11;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has been attacked by ";

	curTemplate = &m_conditionTemplates[22];
	curTemplate->m_internalName = "TEAM_ATTACKED_BY_PLAYER";
	curTemplate->m_uiName = "Team_/ Team has been attacked by a player.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 11;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has been attacked by ";

	curTemplate = &m_conditionTemplates[23];
	curTemplate->m_internalName = "BUILT_BY_PLAYER";
	curTemplate->m_uiName = "Player_/ Player has built an object type.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 61;
	curTemplate->m_parameters[1] = 11;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has been built by ";

	curTemplate = &m_conditionTemplates[24];
	curTemplate->m_internalName = "NAMED_CREATED";
	curTemplate->m_uiName = "Unit_/ Unit has been created.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has been created.";

	curTemplate = &m_conditionTemplates[25];
	curTemplate->m_internalName = "TEAM_CREATED";
	curTemplate->m_uiName = "Team_/ Team has been created.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has been created.";

	curTemplate = &m_conditionTemplates[26];
	curTemplate->m_internalName = "PLAYER_HAS_CREDITS";
	curTemplate->m_uiName = "Player_/ Player has (comparison) to a number of credits.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 0;
	curTemplate->m_parameters[1] = 6;
	curTemplate->m_parameters[2] = 11;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " is ";
	curTemplate->m_uiStrings[2] = " the number of credits possessed by ";

	curTemplate = &m_conditionTemplates[27];
	curTemplate->m_internalName = "NAMED_DISCOVERED";
	curTemplate->m_uiName = "Player_/ Player has discovered a specific unit.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_parameters[1] = 11;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has been discovered by ";

	curTemplate = &m_conditionTemplates[78];
	curTemplate->m_internalName = "NAMED_BUILDING_IS_EMPTY";
	curTemplate->m_uiName = "Unit_/ A specific building is empty.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " is empty.";

	curTemplate = &m_conditionTemplates[51];
	curTemplate->m_internalName = "BUILDING_ENTERED_BY_PLAYER";
	curTemplate->m_uiName = "Player_/ Player has entered a specific building.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 14;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has entered building named ";

	curTemplate = &m_conditionTemplates[52];
	curTemplate->m_internalName = "ENEMY_SIGHTED";
	curTemplate->m_uiName = "Unit_/ Unit has sighted a(n) friendly/neutral/enemy unit belonging to a side.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_parameters[1] = 19;
	curTemplate->m_parameters[2] = 11;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " sees a(n) ";
	curTemplate->m_uiStrings[2] = " unit belonging to ";
	curTemplate->m_uiStrings[3] = ".";

	curTemplate = &m_conditionTemplates[133];
	curTemplate->m_internalName = "ENEMY_SIGHTED_BY_TEAM";
	curTemplate->m_uiName = "Team/ Team has sighted a(n) friendly/neutral/enemy unit belonging to a side.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 19;
	curTemplate->m_parameters[2] = 11;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " sees a(n) ";
	curTemplate->m_uiStrings[2] = " unit belonging to ";
	curTemplate->m_uiStrings[3] = ".";

	curTemplate = &m_conditionTemplates[77];
	curTemplate->m_internalName = "TYPE_SIGHTED";
	curTemplate->m_uiName = "Unit_/ Unit has sighted a type of unit belonging to a side.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_parameters[1] = 61;
	curTemplate->m_parameters[2] = 11;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " sees a(n) ";
	curTemplate->m_uiStrings[2] = " belonging to ";
	curTemplate->m_uiStrings[3] = ".";

	curTemplate = &m_conditionTemplates[28];
	curTemplate->m_internalName = "TEAM_DISCOVERED";
	curTemplate->m_uiName = "Player_/ Player has discovered a team.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 11;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has been discovered by ";

	curTemplate = &m_conditionTemplates[29];
	curTemplate->m_internalName = "MISSION_ATTEMPTS";
	curTemplate->m_uiName = "Player_/ Player has attempted the mission a number of times.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 6;
	curTemplate->m_parameters[2] = 0;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has attempted the mission ";
	curTemplate->m_uiStrings[2] = " ";
	curTemplate->m_uiStrings[3] = " times.";

	curTemplate = &m_conditionTemplates[30];
	curTemplate->m_internalName = "NAMED_OWNED_BY_PLAYER";
	curTemplate->m_uiName = "Player/Owns/ Player owns the specific Unit.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_parameters[1] = 11;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " is owned by ";

	curTemplate = &m_conditionTemplates[31];
	curTemplate->m_internalName = "TEAM_OWNED_BY_PLAYER";
	curTemplate->m_uiName = "Player/Owns/ Player owns a specific team.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 11;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " is owned by ";

	curTemplate = &m_conditionTemplates[79];
	curTemplate->m_internalName = "PLAYER_HAS_N_OR_FEWER_FACTION_BUILDINGS";
	curTemplate->m_uiName = "Player/Owns/ Player currently owns N or fewer faction buildings.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 0;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " currently owns ";
	curTemplate->m_uiStrings[2] = " or fewer faction buildings.";

	curTemplate = &m_conditionTemplates[131];
	curTemplate->m_internalName = "PLAYER_HAS_N_OR_FEWER_BASES";
	curTemplate->m_uiName = "Player/Owns/ Player currently controls N or fewer bases.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 0;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " currently controls ";
	curTemplate->m_uiStrings[2] = " or fewer bases.";

	curTemplate = &m_conditionTemplates[33];
	curTemplate->m_internalName = "PLAYER_HAS_POWER";
	curTemplate->m_uiName = "Player_/ Player's base currently has power.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " buildings are powered.";

	curTemplate = &m_conditionTemplates[47];
	curTemplate->m_internalName = "PLAYER_HAS_NO_POWER";
	curTemplate->m_uiName = "Player_/ Player's base currently has no power.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " buildings are not powered.";

	curTemplate = &m_conditionTemplates[34];
	curTemplate->m_internalName = "NAMED_REACHED_WAYPOINTS_END";
	curTemplate->m_uiName = "Unit_/ Unit has reached the end of a specific waypoint path.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_parameters[1] = 24;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has reached the end of ";

	curTemplate = &m_conditionTemplates[35];
	curTemplate->m_internalName = "TEAM_REACHED_WAYPOINTS_END";
	curTemplate->m_uiName = "Team_/ Team has reached the end of a specific waypoint path.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 24;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has reached the end of ";

	curTemplate = &m_conditionTemplates[37];
	curTemplate->m_internalName = "NAMED_SELECTED";
	curTemplate->m_uiName = "Unit_/ Unit currently selected.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " is currently selected.";

	curTemplate = &m_conditionTemplates[38];
	curTemplate->m_internalName = "NAMED_ENTERED_AREA";
	curTemplate->m_uiName = "Unit_/ Unit enters an area.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_parameters[1] = 9;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " enters ";

	curTemplate = &m_conditionTemplates[39];
	curTemplate->m_internalName = "NAMED_EXITED_AREA";
	curTemplate->m_uiName = "Unit_/ Unit exits an area.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_parameters[1] = 9;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " exits ";

	curTemplate = &m_conditionTemplates[40];
	curTemplate->m_internalName = "TEAM_ENTERED_AREA_ENTIRELY";
	curTemplate->m_uiName = "Team_/ Team entirely enters an area.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 9;
	curTemplate->m_parameters[2] = 37;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " all enter ";
	curTemplate->m_uiStrings[2] = " (";
	curTemplate->m_uiStrings[3] = ").";

	curTemplate = &m_conditionTemplates[121];
	curTemplate->m_internalName = "NAMED_BASE_UNPACKABLE_FOR_PLAYER";
	curTemplate->m_uiName = "Base/ Player is allowed to unpack a base.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_parameters[1] = 11;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " is unpackable for the player: ";
	curTemplate->m_uiStrings[2] = ".";

	curTemplate = &m_conditionTemplates[41];
	curTemplate->m_internalName = "TEAM_ENTERED_AREA_PARTIALLY";
	curTemplate->m_uiName = "Team_/ One unit enters an area.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 9;
	curTemplate->m_parameters[2] = 37;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = "One unit from ";
	curTemplate->m_uiStrings[1] = " enters ";
	curTemplate->m_uiStrings[2] = " (";
	curTemplate->m_uiStrings[3] = ").";

	curTemplate = &m_conditionTemplates[42];
	curTemplate->m_internalName = "TEAM_EXITED_AREA_ENTIRELY";
	curTemplate->m_uiName = "Team_/ Team entirely exits an area.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 9;
	curTemplate->m_parameters[2] = 37;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " all exit ";
	curTemplate->m_uiStrings[2] = " (";
	curTemplate->m_uiStrings[3] = ").";

	curTemplate = &m_conditionTemplates[43];
	curTemplate->m_internalName = "TEAM_EXITED_AREA_PARTIALLY";
	curTemplate->m_uiName = "Team_/ One unit exits an area.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 9;
	curTemplate->m_parameters[2] = 37;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = "One unit from ";
	curTemplate->m_uiStrings[1] = " exits ";
	curTemplate->m_uiStrings[2] = " (";
	curTemplate->m_uiStrings[3] = ").";

	curTemplate = &m_conditionTemplates[44];
	curTemplate->m_internalName = "MULTIPLAYER_ALLIED_VICTORY";
	curTemplate->m_uiName = "Multiplayer_/ Multiplayer allied victory.";
	curTemplate->m_numParameters = 0;
	curTemplate->m_numUiStrings = 1;
	curTemplate->m_uiStrings[0] = "The multiplayer game has ended in victory for the local player and his allies.";

	curTemplate = &m_conditionTemplates[45];
	curTemplate->m_internalName = "MULTIPLAYER_ALLIED_DEFEAT";
	curTemplate->m_uiName = "Multiplayer_/ Multiplayer allied defeat.";
	curTemplate->m_numParameters = 0;
	curTemplate->m_numUiStrings = 1;
	curTemplate->m_uiStrings[0] = "The multiplayer game has ended in defeat for the local player and his allies.";

	curTemplate = &m_conditionTemplates[46];
	curTemplate->m_internalName = "MULTIPLAYER_PLAYER_DEFEAT";
	curTemplate->m_uiName = "Multiplayer_/ Multiplayer local player defeat check.";
	curTemplate->m_numParameters = 0;
	curTemplate->m_numUiStrings = 1;
	curTemplate->m_uiStrings[0] = "Everything belonging to the local player has been destroyed, but his allies may or may not have been defeated.";

	curTemplate = &m_conditionTemplates[48];
	curTemplate->m_internalName = "HAS_FINISHED_VIDEO";
	curTemplate->m_uiName = "Multimedia_/ Video has completed playing.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 23;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has completed playing.";

	curTemplate = &m_conditionTemplates[49];
	curTemplate->m_internalName = "HAS_FINISHED_SPEECH";
	curTemplate->m_uiName = "Multimedia_/ Speech has completed playing.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 21;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has completed playing.";

	curTemplate = &m_conditionTemplates[50];
	curTemplate->m_internalName = "HAS_FINISHED_AUDIO";
	curTemplate->m_uiName = "Multimedia_/ Sound has completed playing.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 12;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has completed playing.";

	curTemplate = &m_conditionTemplates[61];
	curTemplate->m_internalName = "PLAYER_TRIGGERED_SPECIAL_POWER";
	curTemplate->m_uiName = "Player_/ Player starts using a special power.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 31;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = "Player ";
	curTemplate->m_uiStrings[1] = " starts using ";
	curTemplate->m_uiStrings[2] = ".";

	curTemplate = &m_conditionTemplates[64];
	curTemplate->m_internalName = "PLAYER_TRIGGERED_SPECIAL_POWER_FROM_NAMED";
	curTemplate->m_uiName = "Player_/ Player start using a special power from a named unit.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 31;
	curTemplate->m_parameters[2] = 14;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = "Player ";
	curTemplate->m_uiStrings[1] = " starts using ";
	curTemplate->m_uiStrings[2] = " from ";
	curTemplate->m_uiStrings[3] = ".";

	curTemplate = &m_conditionTemplates[63];
	curTemplate->m_internalName = "PLAYER_MIDWAY_SPECIAL_POWER";
	curTemplate->m_uiName = "Player_/ Player is midway through using a special power.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 31;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = "Player ";
	curTemplate->m_uiStrings[1] = " is midway using ";
	curTemplate->m_uiStrings[2] = ".";

	curTemplate = &m_conditionTemplates[66];
	curTemplate->m_internalName = "PLAYER_MIDWAY_SPECIAL_POWER_FROM_NAMED";
	curTemplate->m_uiName = "Player_/ Player is midway through using a special power from a named unit.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 31;
	curTemplate->m_parameters[2] = 14;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = "Player ";
	curTemplate->m_uiStrings[1] = " is midway using ";
	curTemplate->m_uiStrings[2] = " from ";
	curTemplate->m_uiStrings[3] = ".";

	curTemplate = &m_conditionTemplates[62];
	curTemplate->m_internalName = "PLAYER_COMPLETED_SPECIAL_POWER";
	curTemplate->m_uiName = "Player_/ Player completed using a special power.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 31;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = "Player ";
	curTemplate->m_uiStrings[1] = " completed using ";
	curTemplate->m_uiStrings[2] = ".";

	curTemplate = &m_conditionTemplates[65];
	curTemplate->m_internalName = "PLAYER_COMPLETED_SPECIAL_POWER_FROM_NAMED";
	curTemplate->m_uiName = "Player_/ Player completed using a special power from a named unit.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 31;
	curTemplate->m_parameters[2] = 14;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = "Player ";
	curTemplate->m_uiStrings[1] = " completed using ";
	curTemplate->m_uiStrings[2] = " from ";
	curTemplate->m_uiStrings[3] = ".";

	curTemplate = &m_conditionTemplates[100];
	curTemplate->m_internalName = "PLAYER_ACQUIRED_SCIENCE";
	curTemplate->m_uiName = "Player_/ Player acquired a Science.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 32;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = "Player ";
	curTemplate->m_uiStrings[1] = " acquired ";
	curTemplate->m_uiStrings[2] = ".";

	curTemplate = &m_conditionTemplates[102];
	curTemplate->m_internalName = "PLAYER_CAN_PURCHASE_SCIENCE";
	curTemplate->m_uiName = "Player_/ Player can purchase a particular Science (has all prereqs & points).";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 32;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = "Player ";
	curTemplate->m_uiStrings[1] = " can purchase ";
	curTemplate->m_uiStrings[2] = ".";

	curTemplate = &m_conditionTemplates[173];
	curTemplate->m_internalName = "PLAYER_HAS_REACHED_LEVEL_CAP";
	curTemplate->m_uiName = "Player_/Upgrades & Sciences/Has Player Reached Level Cap";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has reached his level cap (cannot gain any more Science Purchace Points)";

	curTemplate = &m_conditionTemplates[101];
	curTemplate->m_internalName = "PLAYER_HAS_SCIENCEPURCHASEPOINTS";
	curTemplate->m_uiName = "Player_/ Player has a certain number of Science Purchase Points available.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 0;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = "Player ";
	curTemplate->m_uiStrings[1] = " has at least ";
	curTemplate->m_uiStrings[2] = " Science Purchase Points available.";

	curTemplate = &m_conditionTemplates[69];
	curTemplate->m_internalName = "PLAYER_BUILT_UPGRADE";
	curTemplate->m_uiName = "Player_/ Player built an upgrade.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 33;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = "Player ";
	curTemplate->m_uiStrings[1] = " built ";
	curTemplate->m_uiStrings[2] = ".";

	curTemplate = &m_conditionTemplates[70];
	curTemplate->m_internalName = "PLAYER_BUILT_UPGRADE_FROM_NAMED";
	curTemplate->m_uiName = "Player_/ Player built an upgrade from a named unit.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 33;
	curTemplate->m_parameters[2] = 14;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = "Player ";
	curTemplate->m_uiStrings[1] = " built ";
	curTemplate->m_uiStrings[2] = " from ";
	curTemplate->m_uiStrings[3] = ".";

	curTemplate = &m_conditionTemplates[32];
	curTemplate->m_internalName = "PLAYER_HAS_N_OR_FEWER_BUILDINGS";
	curTemplate->m_uiName = "Player/Owns/ Player currently owns N or fewer buildings.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 0;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " currently owns ";
	curTemplate->m_uiStrings[2] = " or fewer buildings.";

	curTemplate = &m_conditionTemplates[71];
	curTemplate->m_internalName = "PLAYER_DESTROYED_N_BUILDINGS_PLAYER";
	curTemplate->m_uiName = "Player_/ Player destroyed N or more of an opponent's buildings.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 0;
	curTemplate->m_parameters[2] = 11;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = "Player ";
	curTemplate->m_uiStrings[1] = " destroyed ";
	curTemplate->m_uiStrings[2] = " or more buildings owned by ";
	curTemplate->m_uiStrings[3] = ".";

	curTemplate = &m_conditionTemplates[58];
	curTemplate->m_internalName = "PLAYER_HAS_OBJECT_COMPARISON";
	curTemplate->m_uiName = "Player_/ Player has (comparison) unit type.";
	curTemplate->m_numParameters = 4;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 6;
	curTemplate->m_parameters[2] = 0;
	curTemplate->m_parameters[3] = 61;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has ";
	curTemplate->m_uiStrings[2] = " ";
	curTemplate->m_uiStrings[3] = " unit or structure of type ";

	curTemplate = &m_conditionTemplates[110];
	curTemplate->m_internalName = "PLAYER_HAS_COMPARISON_UNIT_TYPE_IN_TRIGGER_AREA_WITH_UPGRADE";
	curTemplate->m_uiName = "Player_/ Player has (comparison) kind of unit or structure in an area with a specified upgrade.";
	curTemplate->m_numParameters = 6;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 6;
	curTemplate->m_parameters[2] = 0;
	curTemplate->m_parameters[3] = 61;
	curTemplate->m_parameters[4] = 9;
	curTemplate->m_parameters[5] = 33;
	curTemplate->m_numUiStrings = 6;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has ";
	curTemplate->m_uiStrings[2] = " ";
	curTemplate->m_uiStrings[3] = " unit or structure with ";
	curTemplate->m_uiStrings[4] = " in the ";
	curTemplate->m_uiStrings[5] = " with upgrade ";

	curTemplate = &m_conditionTemplates[74];
	curTemplate->m_internalName = "PLAYER_HAS_COMPARISON_UNIT_TYPE_IN_TRIGGER_AREA";
	curTemplate->m_uiName = "Player_/ Player has (comparison) unit type in an area.";
	curTemplate->m_numParameters = 5;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 6;
	curTemplate->m_parameters[2] = 0;
	curTemplate->m_parameters[3] = 61;
	curTemplate->m_parameters[4] = 9;
	curTemplate->m_numUiStrings = 5;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has ";
	curTemplate->m_uiStrings[2] = " ";
	curTemplate->m_uiStrings[3] = " unit or structure of type ";
	curTemplate->m_uiStrings[4] = " in the ";

	curTemplate = &m_conditionTemplates[160];
	curTemplate->m_internalName = "PLAYER_HAS_NUMBER_OBJECTS_WITH_MODELCONDITION";
	curTemplate->m_uiName = "Player_/ Player has (comparison) objects with model condition";
	curTemplate->m_numParameters = 4;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 58;
	curTemplate->m_parameters[2] = 6;
	curTemplate->m_parameters[3] = 0;
	curTemplate->m_numUiStrings = 5;
	curTemplate->m_uiStrings[0] = " # of objects owned by player ";
	curTemplate->m_uiStrings[1] = " with model condition ";
	curTemplate->m_uiStrings[2] = " is ";
	curTemplate->m_uiStrings[3] = " ";
	curTemplate->m_uiStrings[4] = ".";

	curTemplate = &m_conditionTemplates[161];
	curTemplate->m_internalName = "PLAYER_HAS_NUMBER_UNITS_DISTANCE_FROM_OBJECT";
	curTemplate->m_uiName = "Player_/ Player has (comparison) units more than x distance from object";
	curTemplate->m_numParameters = 5;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 6;
	curTemplate->m_parameters[2] = 0;
	curTemplate->m_parameters[3] = 1;
	curTemplate->m_parameters[4] = 14;
	curTemplate->m_numUiStrings = 6;
	curTemplate->m_uiStrings[0] = " Player ";
	curTemplate->m_uiStrings[1] = " has ";
	curTemplate->m_uiStrings[2] = " ";
	curTemplate->m_uiStrings[3] = " units at least ";
	curTemplate->m_uiStrings[4] = " yards from ";
	curTemplate->m_uiStrings[5] = ".";

	curTemplate = &m_conditionTemplates[134];
	curTemplate->m_internalName = "COMPARISON_TREES_IN_TRIGGER_AREA";
	curTemplate->m_uiName = "Trees_/ There are (comparison) trees in an area.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 6;
	curTemplate->m_parameters[1] = 0;
	curTemplate->m_parameters[2] = 9;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = "There are ";
	curTemplate->m_uiStrings[1] = " ";
	curTemplate->m_uiStrings[2] = " trees in the ";
	curTemplate->m_uiStrings[3] = " .";

	curTemplate = &m_conditionTemplates[75];
	curTemplate->m_internalName = "PLAYER_HAS_COMPARISON_UNIT_KIND_IN_TRIGGER_AREA";
	curTemplate->m_uiName = "Player_/ Player has (comparison) kind of unit or structure in an area.";
	curTemplate->m_numParameters = 5;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 6;
	curTemplate->m_parameters[2] = 0;
	curTemplate->m_parameters[3] = 27;
	curTemplate->m_parameters[4] = 9;
	curTemplate->m_numUiStrings = 5;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has ";
	curTemplate->m_uiStrings[2] = " ";
	curTemplate->m_uiStrings[3] = " unit or structure with ";
	curTemplate->m_uiStrings[4] = " in the ";

	curTemplate = &m_conditionTemplates[83];
	curTemplate->m_internalName = "PLAYER_POWER_COMPARE_PERCENT";
	curTemplate->m_uiName = "Player_/ Player has (comparison) percent power supply to consumption.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 6;
	curTemplate->m_parameters[2] = 0;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has ";
	curTemplate->m_uiStrings[2] = " ";
	curTemplate->m_uiStrings[3] = " percent power supply ratio.";

	curTemplate = &m_conditionTemplates[84];
	curTemplate->m_internalName = "PLAYER_EXCESS_POWER_COMPARE_VALUE";
	curTemplate->m_uiName = "Player_/ Player has (comparison) kilowatts excess power supply.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 6;
	curTemplate->m_parameters[2] = 0;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has ";
	curTemplate->m_uiStrings[2] = " ";
	curTemplate->m_uiStrings[3] = " excess kilowatts power supply.";

	curTemplate = &m_conditionTemplates[76];
	curTemplate->m_internalName = "UNIT_EMPTIED";
	curTemplate->m_uiName = "Unit_/ Unit has emptied its contents.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " emptied its contents.";

	curTemplate = &m_conditionTemplates[85];
	curTemplate->m_internalName = "SKIRMISH_SPECIAL_POWER_READY";
	curTemplate->m_uiName = "Skirmish_/ Player's special power is ready to fire.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 31;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " is ready to fire ";
	curTemplate->m_uiStrings[2] = ".";

	curTemplate = &m_conditionTemplates[171];
	curTemplate->m_internalName = "SKIRMISH_FIRE_SPECIAL_POWER_ON_TEAM";
	curTemplate->m_uiName = "Skirmish_/ Player's special power is able to fire on team.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 31;
	curTemplate->m_parameters[2] = 3;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " can perform special power ";
	curTemplate->m_uiStrings[2] = " at team location ";
	curTemplate->m_uiStrings[3] = ".";

	curTemplate = &m_conditionTemplates[80];
	curTemplate->m_internalName = "UNIT_HAS_OBJECT_STATUS";
	curTemplate->m_uiName = "Unit_/ Unit has object status.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_parameters[1] = 41;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has ";

	curTemplate = &m_conditionTemplates[81];
	curTemplate->m_internalName = "TEAM_ALL_HAS_OBJECT_STATUS";
	curTemplate->m_uiName = "Team_/ Team has object status - all.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 41;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has ";

	curTemplate = &m_conditionTemplates[82];
	curTemplate->m_internalName = "TEAM_SOME_HAVE_OBJECT_STATUS";
	curTemplate->m_uiName = "Team_/ Team has object status - partial.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 41;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has ";

	curTemplate = &m_conditionTemplates[86];
	curTemplate->m_internalName = "SKIRMISH_VALUE_IN_AREA";
	curTemplate->m_uiName = "Skirmish Only_/ Player has total value in area.";
	curTemplate->m_numParameters = 4;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 6;
	curTemplate->m_parameters[2] = 0;
	curTemplate->m_parameters[3] = 9;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has ";
	curTemplate->m_uiStrings[2] = " ";
	curTemplate->m_uiStrings[3] = " within area ";

	curTemplate = &m_conditionTemplates[87];
	curTemplate->m_internalName = "SKIRMISH_PLAYER_FACTION";
	curTemplate->m_uiName = "Skirmish_/ Player is faction. - untested";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 47;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " is ";

	curTemplate = &m_conditionTemplates[88];
	curTemplate->m_internalName = "SKIRMISH_SUPPLIES_VALUE_WITHIN_DISTANCE";
	curTemplate->m_uiName = "Skirmish Only_/ Supplies are within specified distance.";
	curTemplate->m_numParameters = 4;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 1;
	curTemplate->m_parameters[2] = 9;
	curTemplate->m_parameters[3] = 1;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has supplies within ";
	curTemplate->m_uiStrings[2] = " of ";
	curTemplate->m_uiStrings[3] = " worth at least ";

	curTemplate = &m_conditionTemplates[89];
	curTemplate->m_internalName = "SKIRMISH_COMMAND_BUTTON_READY_ALL";
	curTemplate->m_uiName = "Skirmish_/ Command Ability is ready - all.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 3;
	curTemplate->m_parameters[2] = 42;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = "'s ";
	curTemplate->m_uiStrings[2] = " are ready to use ";
	curTemplate->m_uiStrings[3] = " (all applicable members).";

	curTemplate = &m_conditionTemplates[90];
	curTemplate->m_internalName = "SKIRMISH_COMMAND_BUTTON_READY_PARTIAL";
	curTemplate->m_uiName = "Skirmish_/ Command Ability is ready - partial";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 3;
	curTemplate->m_parameters[2] = 42;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = "'s ";
	curTemplate->m_uiStrings[2] = " are ready to use ";
	curTemplate->m_uiStrings[3] = " (at least one member).";

	curTemplate = &m_conditionTemplates[91];
	curTemplate->m_internalName = "SKIRMISH_UNOWNED_FACTION_UNIT_EXISTS";
	curTemplate->m_uiName = "Skirmish_/ Unowned faction unit -- comparison.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 6;
	curTemplate->m_parameters[2] = 0;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = ". There are ";
	curTemplate->m_uiStrings[2] = " ";
	curTemplate->m_uiStrings[3] = " unowned faction units.";

	curTemplate = &m_conditionTemplates[92];
	curTemplate->m_internalName = "SKIRMISH_PLAYER_HAS_PREREQUISITE_TO_BUILD";
	curTemplate->m_uiName = "Skirmish_/ Player has prerequisites to build an object type.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 61;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " can build ";
	curTemplate->m_uiStrings[2] = ".";

	curTemplate = &m_conditionTemplates[93];
	curTemplate->m_internalName = "SKIRMISH_PLAYER_HAS_COMPARISON_GARRISONED";
	curTemplate->m_uiName = "Skirmish_/ Player has garrisoned buildings -- comparison.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 6;
	curTemplate->m_parameters[2] = 0;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has ";
	curTemplate->m_uiStrings[2] = " ";
	curTemplate->m_uiStrings[3] = " garrisoned buildings.";

	curTemplate = &m_conditionTemplates[94];
	curTemplate->m_internalName = "SKIRMISH_PLAYER_HAS_COMPARISON_CAPTURED_UNITS";
	curTemplate->m_uiName = "Skirmish_/ Player has captured units -- comparison";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 6;
	curTemplate->m_parameters[2] = 0;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has captured ";
	curTemplate->m_uiStrings[2] = " ";
	curTemplate->m_uiStrings[3] = " units.";

	curTemplate = &m_conditionTemplates[95];
	curTemplate->m_internalName = "SKIRMISH_NAMED_AREA_EXIST";
	curTemplate->m_uiName = "Skirmish_/ Area exists.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 9;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = ". ";
	curTemplate->m_uiStrings[2] = " exists.";

	curTemplate = &m_conditionTemplates[96];
	curTemplate->m_internalName = "SKIRMISH_PLAYER_HAS_UNITS_IN_AREA";
	curTemplate->m_uiName = "Skirmish_/ Player has units in an area";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 9;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has units in ";
	curTemplate->m_uiStrings[2] = ".";

	curTemplate = &m_conditionTemplates[97];
	curTemplate->m_internalName = "SKIRMISH_PLAYER_HAS_BEEN_ATTACKED_BY_PLAYER";
	curTemplate->m_uiName = "Skirmish_/ Player has been attacked by player.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 11;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has been attacked by ";
	curTemplate->m_uiStrings[2] = ".";

	curTemplate = &m_conditionTemplates[98];
	curTemplate->m_internalName = "SKIRMISH_PLAYER_IS_OUTSIDE_AREA";
	curTemplate->m_uiName = "Skirmish_/ Player doesn't have units in an area.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 9;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has doesn't have units in ";
	curTemplate->m_uiStrings[2] = ".";

	curTemplate = &m_conditionTemplates[99];
	curTemplate->m_internalName = "SKIRMISH_PLAYER_HAS_DISCOVERED_PLAYER";
	curTemplate->m_uiName = "Skirmish_/ Player has discovered another player.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 11;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has discovered ";
	curTemplate->m_uiStrings[2] = ".";

	curTemplate = &m_conditionTemplates[103];
	curTemplate->m_internalName = "MUSIC_TRACK_HAS_COMPLETED";
	curTemplate->m_uiName = "Multimedia_/ Music track has completed some number of times.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 22;
	curTemplate->m_parameters[1] = 0;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has completed at least ";
	curTemplate->m_uiStrings[2] = " times. (NOTE: This can only be used to start other music. USING THIS SCRIPT IN ANY OTHER WAY WILL CAUSE REPLAYS TO NOT WORK.)";

	curTemplate = &m_conditionTemplates[105];
	curTemplate->m_internalName = "SUPPLY_SOURCE_SAFE";
	curTemplate->m_uiName = "Skirmish_/ Supply source is safe.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 0;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " closest supply src with at least ";
	curTemplate->m_uiStrings[2] = " available resources is SAFE from enemy influence.";

	curTemplate = &m_conditionTemplates[106];
	curTemplate->m_internalName = "SUPPLY_SOURCE_ATTACKED";
	curTemplate->m_uiName = "Skirmish_/ Supply source is attacked.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " supply source is under attack.";

	curTemplate = &m_conditionTemplates[107];
	curTemplate->m_internalName = "START_POSITION_IS";
	curTemplate->m_uiName = "Skirmish_/ Start position.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 0;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " starting position is ";
	curTemplate->m_uiStrings[2] = " .";

	curTemplate = &m_conditionTemplates[108];
	curTemplate->m_internalName = "ZONE_FOCUS_MORE_THAN";
	curTemplate->m_uiName = "LivingWorld_/ Zone Focus Check.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 10;
	curTemplate->m_parameters[1] = 0;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " Zone named ";
	curTemplate->m_uiStrings[1] = " has been entered at least ";
	curTemplate->m_uiStrings[2] = " times.";

	curTemplate = &m_conditionTemplates[109];
	curTemplate->m_internalName = "IS_SEIGE_ATTACHED_TO_WALL";
	curTemplate->m_uiName = "Unit_/ CHeck if Siege Unit is attached to wall.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " Is Siege Unit named ";
	curTemplate->m_uiStrings[1] = " attached to a wall. ";

	curTemplate = &m_conditionTemplates[36];
	curTemplate->m_internalName = "BANNER_PRESSED";
	curTemplate->m_uiName = "LivingWorld_/Banner pressed.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 10;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " Banner button ";
	curTemplate->m_uiStrings[1] = " was pressed.";

	curTemplate = &m_conditionTemplates[104];
	curTemplate->m_internalName = "PLAYER_LOST_OBJECT_TYPE";
	curTemplate->m_uiName = "Player_/ Player has lost an object of type.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 61;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has lost an object of type ";
	curTemplate->m_uiStrings[2] = " (can be an object type list).";

	curTemplate = &m_conditionTemplates[120];
	curTemplate->m_internalName = "CAMERA_HIT_SPECIFIC_SPLINE_WAYPOINT";
	curTemplate->m_uiName = "Camera_/Camera following spline path hits specified waypoint.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 7;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " Camera following spline path hits ";
	curTemplate->m_uiStrings[1] = " waypoint.";

	curTemplate = &m_conditionTemplates[132];
	curTemplate->m_internalName = "CAMERA_ENTERED_AREA";
	curTemplate->m_uiName = "Camera_/Camera entered a specific area.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 9;
	curTemplate->m_numUiStrings = 1;
	curTemplate->m_uiStrings[0] = "Camera enters ";

	curTemplate = &m_conditionTemplates[123];
	curTemplate->m_internalName = "TEAM_IS_LED_BY_UNIT";
	curTemplate->m_uiName = "Team_/ Is Team affected by leadership ability from unit.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 14;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " Is team ";
	curTemplate->m_uiStrings[1] = " affected by leadership ability from unit ";

	curTemplate = &m_conditionTemplates[124];
	curTemplate->m_internalName = "PLAYER_COMPARE_LIGHT_POINTS";
	curTemplate->m_uiName = "Player_/ Player has light points (comparison) to a value.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 6;
	curTemplate->m_parameters[2] = 0;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has light points ";
	curTemplate->m_uiStrings[2] = " to the value ";

	curTemplate = &m_conditionTemplates[125];
	curTemplate->m_internalName = "HAS_COMMAND_POINTS_TO_BUILD_TEAM";
	curTemplate->m_uiName = "Player_/ Player has enough command points to build a team.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 3;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has enough command points to build team ";

	curTemplate = &m_conditionTemplates[126];
	curTemplate->m_internalName = "HAS_COMMAND_POINTS_TO_BUILD_UNIT";
	curTemplate->m_uiName = "Player_/ Player has enough command points to build a unit.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 61;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has enough command points to build unit ";

	curTemplate = &m_conditionTemplates[127];
	curTemplate->m_internalName = "CAN_BUILD_AT_BASE";
	curTemplate->m_uiName = "Player_/ Can build at base.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 14;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " Can player ";
	curTemplate->m_uiStrings[1] = " build at base ";

	curTemplate = &m_conditionTemplates[169];
	curTemplate->m_internalName = "CAN_BUILD_OBJECTTYPE_AT_BASE";
	curTemplate->m_uiName = "Player_/ Can build a particular type of structure at base.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 14;
	curTemplate->m_parameters[2] = 15;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " Can player ";
	curTemplate->m_uiStrings[1] = " build at base";
	curTemplate->m_uiStrings[2] = " an object of type, ";

	curTemplate = &m_conditionTemplates[128];
	curTemplate->m_internalName = "PLAYER_HAS_KILLED_KINDOF_UNITS";
	curTemplate->m_uiName = "Player_/ Player currently has killed N or more units of KindOf.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 0;
	curTemplate->m_parameters[2] = 27;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has killed ";
	curTemplate->m_uiStrings[2] = " or more units of kindof ";

	curTemplate = &m_conditionTemplates[129];
	curTemplate->m_internalName = "PLAYER_HAS_KILLED_TYPE_UNITS";
	curTemplate->m_uiName = "Player_/ Player currently has killed N or more units of type.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 0;
	curTemplate->m_parameters[2] = 61;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has killed ";
	curTemplate->m_uiStrings[2] = " or more units of type ";

	curTemplate = &m_conditionTemplates[130];
	curTemplate->m_internalName = "NAMED_DESTROYED_BY_OBJECTTYPE";
	curTemplate->m_uiName = "Unit_/ Unit is destroyzed by a specific unit type.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_parameters[1] = 61;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has been destroyed by a(n) ";

	curTemplate = &m_conditionTemplates[135];
	curTemplate->m_internalName = "GATE_IS_OPEN";
	curTemplate->m_uiName = "Unit (includes Structures)/ Check if a gate is open. (False, if not a gate, or closed)";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " The unit (presumed a gate) referenced as";
	curTemplate->m_uiStrings[1] = " is OPEN.";

	curTemplate = &m_conditionTemplates[142];
	curTemplate->m_internalName = "MUSIC_IS_PLAYING_FROM_SCRIPT";
	curTemplate->m_uiName = "Audio_/Music/MUSIC_IS_PLAYING_FROM_SCRIPT";
	curTemplate->m_numParameters = 0;
	curTemplate->m_numUiStrings = 1;
	curTemplate->m_uiStrings[0] = " The music scripting system is on.";

	curTemplate = &m_conditionTemplates[136];
	curTemplate->m_internalName = "UNIT_CAN_PATH_TO_WAYPOINT";
	curTemplate->m_uiName = "Unit_/ Unit can path to waypoint.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_parameters[1] = 7;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " can path to waypoint ";

	curTemplate = &m_conditionTemplates[137];
	curTemplate->m_internalName = "UNIT_CAN_PATH_TO_OBJECT";
	curTemplate->m_uiName = "Unit_/ Unit can path to object.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_parameters[1] = 14;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " can path to unit/object ";

	curTemplate = &m_conditionTemplates[139];
	curTemplate->m_internalName = "TEAM_CAN_PATH_TO_WAYPOINT";
	curTemplate->m_uiName = "Team_/ Team can path to waypoint.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 7;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = "The first unit of team ";
	curTemplate->m_uiStrings[1] = " can path to waypoint ";

	curTemplate = &m_conditionTemplates[140];
	curTemplate->m_internalName = "TEAM_CAN_PATH_TO_OBJECT";
	curTemplate->m_uiName = "Team_/ Team can path to object.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 14;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = "The first unit of team ";
	curTemplate->m_uiStrings[1] = " can path to unit/object ";

	curTemplate = &m_conditionTemplates[138];
	curTemplate->m_internalName = "UNIT_CAN_PATH_INTO_PLAYERS_NEAREST_BASE";
	curTemplate->m_uiName = "Unit/ Unit can path into (Player's) nearest base. Or is already inside it :-)";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_parameters[1] = 11;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " Unit";
	curTemplate->m_uiStrings[1] = " is inside, or can path into the nearest base owned by player, ";

	curTemplate = &m_conditionTemplates[141];
	curTemplate->m_internalName = "TEAM_CAN_PATH_INTO_PLAYERS_NEAREST_BASE";
	curTemplate->m_uiName = "Team/ Team can path into (Player's) nearest base. Or is already inside it :-).";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 11;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = "The first unit of team ";
	curTemplate->m_uiStrings[1] = " is inside, or can path into the nearest base owned by player, ";

	curTemplate = &m_conditionTemplates[144];
	curTemplate->m_internalName = "UNIT_COMPARE_RANK";
	curTemplate->m_uiName = "Unit_/ Unit compared to rank level.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_parameters[1] = 6;
	curTemplate->m_parameters[2] = 0;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = "Does unit ";
	curTemplate->m_uiStrings[1] = " have rank ";
	curTemplate->m_uiStrings[2] = " to ";

	curTemplate = &m_conditionTemplates[145];
	curTemplate->m_internalName = "PLAYER_COMPARE_RANK";
	curTemplate->m_uiName = "Player_/ Player compared to rank level.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 6;
	curTemplate->m_parameters[2] = 0;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = "Does player ";
	curTemplate->m_uiStrings[1] = " have rank ";
	curTemplate->m_uiStrings[2] = " to ";

	curTemplate = &m_conditionTemplates[174];
	curTemplate->m_internalName = "EVAL_TEAM_HEALTH";
	curTemplate->m_uiName = "Team_/ Compare team health.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 6;
	curTemplate->m_parameters[2] = 0;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = " Check if Team ";
	curTemplate->m_uiStrings[1] = " has health ";
	curTemplate->m_uiStrings[2] = " to ";
	curTemplate->m_uiStrings[3] = " percent";

	curTemplate = &m_conditionTemplates[117];
	curTemplate->m_internalName = "UNIT_HAS_GAINED_LEVEL";
	curTemplate->m_uiName = "Unit_/Experience/Unit gained experience level.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = "has gained a level";

	curTemplate = &m_conditionTemplates[118];
	curTemplate->m_internalName = "UNIT_IS_AT_LEVEL";
	curTemplate->m_uiName = "Unit_/Experience/Unit is at a specified experience level.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_parameters[1] = 10;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " is at experience level ";

	curTemplate = &m_conditionTemplates[119];
	curTemplate->m_internalName = "UNIT_HAS_NUM_SKILL_POINTS";
	curTemplate->m_uiName = "Unit_/Skill Points/Unit has (comparison) number of skill points.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_parameters[1] = 6;
	curTemplate->m_parameters[2] = 0;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = " ";
	curTemplate->m_uiStrings[1] = " has ";
	curTemplate->m_uiStrings[2] = " ";
	curTemplate->m_uiStrings[3] = " skill points";

	curTemplate = &m_conditionTemplates[146];
	curTemplate->m_internalName = "PLAYER_HAS_OBJECT_OF_VETERANCY";
	curTemplate->m_uiName = "Player/Experience/Player has object of rank level.";
	curTemplate->m_numParameters = 4;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 61;
	curTemplate->m_parameters[2] = 6;
	curTemplate->m_parameters[3] = 0;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = " Player ";
	curTemplate->m_uiStrings[1] = " has obvject of type ";
	curTemplate->m_uiStrings[2] = " with rank level ";
	curTemplate->m_uiStrings[3] = " to ";

	curTemplate = &m_conditionTemplates[147];
	curTemplate->m_internalName = "OBJECT_OF_TYPE_OR_LIST_INSIDE_REFD_BASE";
	curTemplate->m_uiName = "Base/There is an object of given type (or list) inside the base.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 61;
	curTemplate->m_parameters[1] = 54;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " There is a unit of type (or list) ";
	curTemplate->m_uiStrings[1] = " inside the base ";

	curTemplate = &m_conditionTemplates[148];
	curTemplate->m_internalName = "TEAM_ENTERED_REFD_BASE_ENTIRELY";
	curTemplate->m_uiName = "Base/Team/Team entered a base, entirely.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 54;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " Team ";
	curTemplate->m_uiStrings[1] = " has entered the base ";
	curTemplate->m_uiStrings[2] = " entirely.";

	curTemplate = &m_conditionTemplates[149];
	curTemplate->m_internalName = "TEAM_ENTERED_REFD_BASE_PARTIALLY";
	curTemplate->m_uiName = "Base/Team/Team entered a base, partially.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 54;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " Team ";
	curTemplate->m_uiStrings[1] = " has entered the base ";
	curTemplate->m_uiStrings[2] = " partially.";

	curTemplate = &m_conditionTemplates[150];
	curTemplate->m_internalName = "TEAM_EXITED_REFD_BASE_ENTIRELY";
	curTemplate->m_uiName = "Base/Team/Team exited a base, entirely.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 54;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " Team ";
	curTemplate->m_uiStrings[1] = " has exited the base ";
	curTemplate->m_uiStrings[2] = " entirely.";

	curTemplate = &m_conditionTemplates[151];
	curTemplate->m_internalName = "TEAM_EXITED_REFD_BASE_PARTIALLY";
	curTemplate->m_uiName = "Base/Team/Team exited a base, partially.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 54;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " Team ";
	curTemplate->m_uiStrings[1] = " has exited the base ";
	curTemplate->m_uiStrings[2] = " partially.";

	curTemplate = &m_conditionTemplates[156];
	curTemplate->m_internalName = "NAMED_ENTERED_REFD_BASE";
	curTemplate->m_uiName = "Base/Unit/Unit entered a base.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_parameters[1] = 54;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " Unit ";
	curTemplate->m_uiStrings[1] = " has entered the base ";
	curTemplate->m_uiStrings[2] = " entirely.";

	curTemplate = &m_conditionTemplates[157];
	curTemplate->m_internalName = "NAMED_EXITED_REFD_BASE";
	curTemplate->m_uiName = "Base/Unit/Unit exited a base.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_parameters[1] = 54;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " Unit ";
	curTemplate->m_uiStrings[1] = " has exited the base ";
	curTemplate->m_uiStrings[2] = " entirely.";

	curTemplate = &m_conditionTemplates[152];
	curTemplate->m_internalName = "TEAM_ENTERED_NEAREST_BASE_ENTIRELY";
	curTemplate->m_uiName = "Base/Team/Team entered (Player's) nearest base, entirely.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 11;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " Team ";
	curTemplate->m_uiStrings[1] = " has entered the nearest base owned by player ";
	curTemplate->m_uiStrings[2] = " entirely.";

	curTemplate = &m_conditionTemplates[153];
	curTemplate->m_internalName = "TEAM_ENTERED_NEAREST_BASE_PARTIALLY";
	curTemplate->m_uiName = "Base/Team/Team entered (Player's) nearest base, partially.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 11;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " Team ";
	curTemplate->m_uiStrings[1] = " has entered the nearest base owned by player ";
	curTemplate->m_uiStrings[2] = " partially.";

	curTemplate = &m_conditionTemplates[154];
	curTemplate->m_internalName = "TEAM_EXITED_NEAREST_BASE_ENTIRELY";
	curTemplate->m_uiName = "Base/Team/Team exited (Player's) nearest base, entirely.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 11;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " Team ";
	curTemplate->m_uiStrings[1] = " has exited the nearest base owned by player ";
	curTemplate->m_uiStrings[2] = " entirely.";

	curTemplate = &m_conditionTemplates[155];
	curTemplate->m_internalName = "TEAM_EXITED_NEAREST_BASE_PARTIALLY";
	curTemplate->m_uiName = "Base/Team/Team exited (Player's) nearest base, partially.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_parameters[1] = 11;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " Team ";
	curTemplate->m_uiStrings[1] = " has exited the nearest base owned by player ";
	curTemplate->m_uiStrings[2] = " partially.";

	curTemplate = &m_conditionTemplates[158];
	curTemplate->m_internalName = "NAMED_ENTERED_NEAREST_BASE";
	curTemplate->m_uiName = "Base/Unit/Unit entered (Player's) nearest base.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_parameters[1] = 11;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " Unit ";
	curTemplate->m_uiStrings[1] = " has entered the nearest base owned by player ";
	curTemplate->m_uiStrings[2] = " entirely.";

	curTemplate = &m_conditionTemplates[159];
	curTemplate->m_internalName = "NAMED_EXITED_NEAREST_BASE";
	curTemplate->m_uiName = "Base/Unit/Unit exited (Player's) nearest base.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_parameters[1] = 11;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " Unit ";
	curTemplate->m_uiStrings[1] = " has exited the nearest base owned by player ";
	curTemplate->m_uiStrings[2] = " entirely.";

	curTemplate = &m_conditionTemplates[162];
	curTemplate->m_internalName = "UNIT_HAS_PASSENGER";
	curTemplate->m_uiName = "Unit_/Unit/Unit has passenger.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " Evaluate if ";
	curTemplate->m_uiStrings[1] = " is containing any passengers.";

	curTemplate = &m_conditionTemplates[163];
	curTemplate->m_internalName = "UNIT_IS_ATTACKED_AND_CANNOT_RETALIATE";
	curTemplate->m_uiName = "Unit_/Unit is being attacked but cannot retaliate.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " Evaluate if ";
	curTemplate->m_uiStrings[1] = " is being attacked and cannot retaliate.";

	curTemplate = &m_conditionTemplates[164];
	curTemplate->m_internalName = "TEAM_IS_ATTACKED_AND_CANNOT_RETALIATE_ANY";
	curTemplate->m_uiName = "Team_/Any Team meember is being attacked but cannot retaliate.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " Evaluate if any team member of ";
	curTemplate->m_uiStrings[1] = " is being attacked and cannot retaliate.";

	curTemplate = &m_conditionTemplates[165];
	curTemplate->m_internalName = "TEAM_IS_ATTACKED_AND_CANNOT_RETALIATE_ALL";
	curTemplate->m_uiName = "Team_/All Team members who are being attacked cannot retaliate.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 3;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " Evaluate if all team members of ";
	curTemplate->m_uiStrings[1] = " who are being attacked and cannot retaliate.";

	curTemplate = &m_conditionTemplates[166];
	curTemplate->m_internalName = "IS_GAME_IN_SKIRMISH_OR_MULTIPLAYER";
	curTemplate->m_uiName = "GameType/Is game in a skirmish or multiplayer game.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 8;
	curTemplate->m_numUiStrings = 1;
	curTemplate->m_uiStrings[0] = " Is the game in a skirmish or multiplayer mode == ";

	curTemplate = &m_conditionTemplates[167];
	curTemplate->m_internalName = "REGION_CAMPS_SHOULD_UNPACK";
	curTemplate->m_uiName = "Base/ Should camps unpack for this region map?";
	curTemplate->m_numParameters = 0;
	curTemplate->m_numUiStrings = 1;
	curTemplate->m_uiStrings[0] = " Should camps in this region map unpack?";

	curTemplate = &m_conditionTemplates[168];
	curTemplate->m_internalName = "COMPARE_NUM_PLAYERS_IN_GAME";
	curTemplate->m_uiName = "GameType/Compares the number of players in game to a value.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 6;
	curTemplate->m_parameters[1] = 0;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " Is this a ";
	curTemplate->m_uiStrings[1] = " ";
	curTemplate->m_uiStrings[2] = " player game.";

	curTemplate = &m_conditionTemplates[175];
	curTemplate->m_internalName = "IS_UNIT_WEBBED";
	curTemplate->m_uiName = "Unit_/Test webbed status of a unit.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 14;
	curTemplate->m_parameters[1] = 8;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " Is webbed status of ";
	curTemplate->m_uiStrings[1] = " == ";

	curTemplate = &m_conditionTemplates[176];
	curTemplate->m_internalName = "ANY_HERO_REACHED_RANK";
	curTemplate->m_uiName = "ObjectivesTest/Num heroes reached level during game.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 0;
	curTemplate->m_parameters[2] = 0;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " Does ";
	curTemplate->m_uiStrings[1] = " have ";
	curTemplate->m_uiStrings[2] = " Heroes that have reached rank ";

	curTemplate = &m_conditionTemplates[177];
	curTemplate->m_internalName = "NUM_UNITS_LEVELED_UP";
	curTemplate->m_uiName = "ObjectivesTest/Num units leveled up during game.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 0;
	curTemplate->m_parameters[2] = 8;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " Does ";
	curTemplate->m_uiStrings[1] = " have ";
	curTemplate->m_uiStrings[2] = " units that has gained a level this game --> should include Heroes ";

	curTemplate = &m_conditionTemplates[178];
	curTemplate->m_internalName = "PLAYER_HAS_NUM_UNITS_WITH_UPGRADE";
	curTemplate->m_uiName = "ObjectivesTest/Num units has specified upgrade.";
	curTemplate->m_numParameters = 3;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 0;
	curTemplate->m_parameters[2] = 33;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " Does ";
	curTemplate->m_uiStrings[1] = " have ";
	curTemplate->m_uiStrings[2] = " units that has upgrade ";

	curTemplate = &m_conditionTemplates[179];
	curTemplate->m_internalName = "PLAYER_HAS_NUM_UNITS_LOADED_WITH_OBJECT";
	curTemplate->m_uiName = "ObjectivesTest/Num units of type loaded on transport.";
	curTemplate->m_numParameters = 4;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 0;
	curTemplate->m_parameters[2] = 15;
	curTemplate->m_parameters[3] = 15;
	curTemplate->m_numUiStrings = 4;
	curTemplate->m_uiStrings[0] = " Does ";
	curTemplate->m_uiStrings[1] = " have ";
	curTemplate->m_uiStrings[2] = " units of type ";
	curTemplate->m_uiStrings[3] = " loaded on transport of type ";

	curTemplate = &m_conditionTemplates[180];
	curTemplate->m_internalName = "UNIT_HAS_TOGGLED_WEAPON";
	curTemplate->m_uiName = "ObjectivesTest/Does Player have Units that have Toggled Weapon set.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 15;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " Does ";
	curTemplate->m_uiStrings[1] = " have ";
	curTemplate->m_uiStrings[2] = " that have toggled weapon set.";

	curTemplate = &m_conditionTemplates[183];
	curTemplate->m_internalName = "UNIT_IN_ALT_FORMATION";
	curTemplate->m_uiName = "ObjectivesTest/Does Player have Units that are in alternate formation.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 15;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " Does ";
	curTemplate->m_uiStrings[1] = " have ";
	curTemplate->m_uiStrings[2] = " that is currently in alternate formation.";

	curTemplate = &m_conditionTemplates[182];
	curTemplate->m_internalName = "UNIT_USING_AUTOPICKUP";
	curTemplate->m_uiName = "ObjectivesTest/Does Player have Units that have triggered auto pickup.";
	curTemplate->m_numParameters = 2;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_parameters[1] = 15;
	curTemplate->m_numUiStrings = 3;
	curTemplate->m_uiStrings[0] = " Does ";
	curTemplate->m_uiStrings[1] = " have ";
	curTemplate->m_uiStrings[2] = " that has triggered auto pickup.";

	curTemplate = &m_conditionTemplates[181];
	curTemplate->m_internalName = "ANY_UNITS_USING_BLOODTHIRSTY";
	curTemplate->m_uiName = "ObjectivesTest/Does Player have Units that are bloodthirsty.";
	curTemplate->m_numParameters = 1;
	curTemplate->m_parameters[0] = 11;
	curTemplate->m_numUiStrings = 2;
	curTemplate->m_uiStrings[0] = " Does ";
	curTemplate->m_uiStrings[1] = " have any units that are currently bloodthirsty";
}
