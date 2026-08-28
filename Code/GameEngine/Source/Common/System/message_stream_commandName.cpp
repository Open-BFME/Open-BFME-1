// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
//
// GameMessage::getCommandTypeAsAsciiString, retail 0x0008B600, 7143 bytes.
//
// Static, not a member call: the body ends in a plain `ret`, so the ledger's
// QAE row name cannot be right -- a thiscall taking the hidden return pointer
// and the type would clean 8 bytes. The SA row is a 5-byte incremental-link
// thunk to this body.

#include <stddef.h>
#include <string.h>
#include "string_base.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() { m_data = 0; }

	AsciiString( const char *str )
	{
		if (str != 0) {
			((StringBase<char> *)this)->StringBase<char>::StringBase( str );
		} else {
			((StringBase<char> *)this)->StringBase<char>::StringBase( str );
		}
	}

	// Declared only: retail's `return commandName` calls the copy constructor
	// out of line rather than expanding StringBase's.
	AsciiString( const AsciiString &that );

	~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }

	void __cdecl format( AsciiString fmt, ... );

private:
	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
class GameMessage
{
public:
	enum Type { MSG_INVALID = 0 };
	static AsciiString getCommandTypeAsAsciiString( Type t );
};

#define CHECK_IF(v, x) if (t == v) { return x; }

// ?getCommandTypeAsAsciiString@GameMessage@@QAE?AVAsciiString@@W4Type@1@@Z
AsciiString GameMessage::getCommandTypeAsAsciiString( GameMessage::Type t )
{
	AsciiString commandName;
	commandName.format( "UNKNOWN COMMAND %d", t );
	if (t >= 2027)
	{
		commandName.format( "OUT OF RANGE COMMAND %d", t );
	}

	switch (t)
	{
		case 33: return "MSG_META_SAVE_VIEW1";
		case 34: return "MSG_META_SAVE_VIEW2";
		case 35: return "MSG_META_SAVE_VIEW3";
		case 36: return "MSG_META_SAVE_VIEW4";
		case 37: return "MSG_META_SAVE_VIEW5";
		case 38: return "MSG_META_SAVE_VIEW6";
		case 39: return "MSG_META_SAVE_VIEW7";
		case 40: return "MSG_META_SAVE_VIEW8";
		case 41: return "MSG_META_VIEW_VIEW1";
		case 42: return "MSG_META_VIEW_VIEW2";
		case 43: return "MSG_META_VIEW_VIEW3";
		case 44: return "MSG_META_VIEW_VIEW4";
		case 45: return "MSG_META_VIEW_VIEW5";
		case 46: return "MSG_META_VIEW_VIEW6";
		case 47: return "MSG_META_VIEW_VIEW7";
		case 48: return "MSG_META_VIEW_VIEW8";
		case 49: return "MSG_META_CREATE_TEAM0";
		case 50: return "MSG_META_CREATE_TEAM1";
		case 51: return "MSG_META_CREATE_TEAM2";
		case 52: return "MSG_META_CREATE_TEAM3";
		case 53: return "MSG_META_CREATE_TEAM4";
		case 54: return "MSG_META_CREATE_TEAM5";
		case 55: return "MSG_META_CREATE_TEAM6";
		case 56: return "MSG_META_CREATE_TEAM7";
		case 57: return "MSG_META_CREATE_TEAM8";
		case 58: return "MSG_META_CREATE_TEAM9";
		case 59: return "MSG_META_SELECT_TEAM0";
		case 60: return "MSG_META_SELECT_TEAM1";
		case 61: return "MSG_META_SELECT_TEAM2";
		case 62: return "MSG_META_SELECT_TEAM3";
		case 63: return "MSG_META_SELECT_TEAM4";
		case 64: return "MSG_META_SELECT_TEAM5";
		case 65: return "MSG_META_SELECT_TEAM6";
		case 66: return "MSG_META_SELECT_TEAM7";
		case 67: return "MSG_META_SELECT_TEAM8";
		case 68: return "MSG_META_SELECT_TEAM9";
		case 69: return "MSG_META_ADD_TEAM0";
		case 70: return "MSG_META_ADD_TEAM1";
		case 71: return "MSG_META_ADD_TEAM2";
		case 72: return "MSG_META_ADD_TEAM3";
		case 73: return "MSG_META_ADD_TEAM4";
		case 74: return "MSG_META_ADD_TEAM5";
		case 75: return "MSG_META_ADD_TEAM6";
		case 76: return "MSG_META_ADD_TEAM7";
		case 77: return "MSG_META_ADD_TEAM8";
		case 78: return "MSG_META_ADD_TEAM9";
		case 79: return "MSG_META_VIEW_TEAM0";
		case 80: return "MSG_META_VIEW_TEAM1";
		case 81: return "MSG_META_VIEW_TEAM2";
		case 82: return "MSG_META_VIEW_TEAM3";
		case 83: return "MSG_META_VIEW_TEAM4";
		case 84: return "MSG_META_VIEW_TEAM5";
		case 85: return "MSG_META_VIEW_TEAM6";
		case 86: return "MSG_META_VIEW_TEAM7";
		case 87: return "MSG_META_VIEW_TEAM8";
		case 88: return "MSG_META_VIEW_TEAM9";
		case 89: return "MSG_META_SELECT_MATCHING_UNITS";
		case 90: return "MSG_META_SELECT_NEXT_UNIT";
		case 91: return "MSG_META_SELECT_PREV_UNIT";
		case 92: return "MSG_META_SELECT_NEXT_WORKER";
		case 93: return "MSG_META_SELECT_PREV_WORKER";
		case 94: return "MSG_META_VIEW_HOME_BASE";
		case 95: return "MSG_META_VIEW_LAST_RADAR_EVENT";
		case 96: return "MSG_META_SELECT_HERO";
		case 97: return "MSG_META_SELECT_ALL";
		case 98: return "MSG_META_SCATTER";
		case 99: return "MSG_META_STOP";
		case 100: return "MSG_META_DEPLOY";
		case 101: return "MSG_META_CREATE_FORMATION";
		case 102: return "MSG_META_AUTO_SAVE";
		case 103: return "MSG_META_FOLLOW";
		case 104: return "MSG_META_CHAT_PLAYERS";
		case 105: return "MSG_META_CHAT_BUDDIES";
		case 106: return "MSG_META_CHAT_ALLIES";
		case 107: return "MSG_META_CHAT_EVERYONE";
		case 108: return "MSG_META_DIPLOMACY";
		case 109: return "MSG_META_OPTIONS";
		case 110: return "MSG_META_TOGGLE_LOWER_DETAILS";
		case 111: return "MSG_META_TOGGLE_CONTROL_BAR";
		case 112: return "MSG_META_BEGIN_PATH_BUILD";
		case 113: return "MSG_META_END_PATH_BUILD";
		case 114: return "MSG_META_BEGIN_FORCEATTACK";
		case 115: return "MSG_META_END_FORCEATTACK";
		case 116: return "MSG_META_BEGIN_FORCEMOVE";
		case 117: return "MSG_META_END_FORCEMOVE";
		case 118: return "MSG_META_BEGIN_WAYPOINTS";
		case 119: return "MSG_META_END_WAYPOINTS";
		case 120: return "MSG_META_BEGIN_PREFER_SELECTION";
		case 121: return "MSG_META_END_PREFER_SELECTION";
		case 122: return "MSG_META_TAKE_SCREENSHOT";
		case 123: return "MSG_META_ALL_CHEER";
		case 124: return "MSG_META_TOGGLE_ATTACKMOVE";
		case 125: return "MSG_META_BEGIN_CAMERA_ROTATE_LEFT";
		case 126: return "MSG_META_END_CAMERA_ROTATE_LEFT";
		case 127: return "MSG_META_BEGIN_CAMERA_ROTATE_RIGHT";
		case 128: return "MSG_META_END_CAMERA_ROTATE_RIGHT";
		case 129: return "MSG_META_BEGIN_CAMERA_ZOOM_IN";
		case 130: return "MSG_META_END_CAMERA_ZOOM_IN";
		case 131: return "MSG_META_BEGIN_CAMERA_ZOOM_OUT";
		case 132: return "MSG_META_END_CAMERA_ZOOM_OUT";
		case 133: return "MSG_META_CAMERA_RESET";
		case 134: return "MSG_META_BEGIN_CAMERA_SCROLL_LEFT";
		case 135: return "MSG_META_END_CAMERA_SCROLL_LEFT";
		case 136: return "MSG_META_BEGIN_CAMERA_SCROLL_RIGHT";
		case 137: return "MSG_META_END_CAMERA_SCROLL_RIGHT";
		case 138: return "MSG_META_BEGIN_CAMERA_SCROLL_UP";
		case 139: return "MSG_META_END_CAMERA_SCROLL_UP";
		case 140: return "MSG_META_BEGIN_CAMERA_SCROLL_DOWN";
		case 141: return "MSG_META_END_CAMERA_SCROLL_DOWN";
		case 142: return "MSG_META_PLACE_BEACON";
		case 143: return "MSG_META_DELETE_BEACON";
		case 144: return "MSG_META_SPELL_STORE";
		case 145: return "MSG_META_DEMO_PERFORM_STATISTICAL_DUMP";
		case 146: return "MSG_META_TOGGLE_FAST_FORWARD_MODE";
		case 1001: return "MSG_CREATE_SELECTED_GROUP";
		case 1002: return "MSG_CREATE_SELECTED_GROUP_NO_SOUND";
		case 1003: return "MSG_DESTROY_SELECTED_GROUP";
		case 1004: return "MSG_REMOVE_FROM_SELECTED_GROUP";
		case 1005: return "MSG_CREATE_TEAM0";
		case 1006: return "MSG_CREATE_TEAM1";
		case 1007: return "MSG_CREATE_TEAM2";
		case 1008: return "MSG_CREATE_TEAM3";
		case 1009: return "MSG_CREATE_TEAM4";
		case 1010: return "MSG_CREATE_TEAM5";
		case 1011: return "MSG_CREATE_TEAM6";
		case 1012: return "MSG_CREATE_TEAM7";
		case 1013: return "MSG_CREATE_TEAM8";
		case 1014: return "MSG_CREATE_TEAM9";
		case 1015: return "MSG_SELECT_TEAM0";
		case 1016: return "MSG_SELECT_TEAM1";
		case 1017: return "MSG_SELECT_TEAM2";
		case 1018: return "MSG_SELECT_TEAM3";
		case 1019: return "MSG_SELECT_TEAM4";
		case 1020: return "MSG_SELECT_TEAM5";
		case 1021: return "MSG_SELECT_TEAM6";
		case 1022: return "MSG_SELECT_TEAM7";
		case 1023: return "MSG_SELECT_TEAM8";
		case 1024: return "MSG_SELECT_TEAM9";
		case 1025: return "MSG_ADD_TEAM0";
		case 1026: return "MSG_ADD_TEAM1";
		case 1027: return "MSG_ADD_TEAM2";
		case 1028: return "MSG_ADD_TEAM3";
		case 1029: return "MSG_ADD_TEAM4";
		case 1030: return "MSG_ADD_TEAM5";
		case 1031: return "MSG_ADD_TEAM6";
		case 1032: return "MSG_ADD_TEAM7";
		case 1033: return "MSG_ADD_TEAM8";
		case 1034: return "MSG_ADD_TEAM9";
		case 1035: return "MSG_DO_ATTACKSQUAD";
		case 1036: return "MSG_DO_WEAPON";
		case 1037: return "MSG_DO_WEAPON_AT_LOCATION";
		case 1038: return "MSG_DO_WEAPON_AT_OBJECT";
		case 1039: return "MSG_DO_SPECIAL_POWER";
		case 1040: return "MSG_DO_SPECIAL_POWER_AT_LOCATION";
		case 1041: return "MSG_DO_SPECIAL_POWER_AT_OBJECT";
		case 1042: return "MSG_SET_RALLY_POINT";
		case 1043: return "MSG_PURCHASE_SCIENCE";
		case 1044: return "MSG_QUEUE_UPGRADE";
		case 1045: return "MSG_CANCEL_UPGRADE";
		case 1046: return "MSG_QUEUE_UNIT_CREATE";
		case 1047: return "MSG_CANCEL_UNIT_CREATE";
		case 1048: return "MSG_FOUNDATION_CONSTRUCT";
		case 1049: return "MSG_UNUSED";
		case 1050: return "MSG_DOZER_CANCEL_CONSTRUCT";
		case 1051: return "MSG_SELL";
		case 1052: return "MSG_EXIT";
		case 1053: return "MSG_EVACUATE";
		case 1054: return "MSG_EVACUATE_CONTESTERS";
		case 1055: return "MSG_SACRIFICE";
		case 1056: return "MSG_COMBATDROP_AT_LOCATION";
		case 1057: return "MSG_COMBATDROP_AT_OBJECT";
		case 1058: return "MSG_COMBINE_HORDES_WITH_OBJECT";
		case 1059: return "MSG_AREA_SELECTION";
		case 1060: return "MSG_DO_ATTACK_OBJECT";
		case 1061: return "MSG_DO_FORCE_ATTACK_OBJECT";
		case 1062: return "MSG_DO_FORCE_ATTACK_GROUND";
		case 1063: return "MSG_GET_REPAIRED";
		case 1064: return "MSG_GET_HEALED";
		case 1065: return "MSG_DO_REPAIR";
		case 1066: return "MSG_RESUME_CONSTRUCTION";
		case 1067: return "MSG_ENTER";
		case 1068: return "MSG_DOCK";
		case 1069: return "MSG_HARVEST";
		case 1070: return "MSG_DO_MOVETO";
		case 1071: return "MSG_DO_ATTACKMOVETO";
		case 1072: return "MSG_DO_FORCEMOVETO";
		case 1073: return "MSG_ADD_WAYPOINT";
		case 1074: return "MSG_DO_GUARD_POSITION";
		case 1075: return "MSG_DO_GUARD_OBJECT";
		case 1076: return "MSG_DO_STOP";
		case 1077: return "MSG_DO_SCATTER";
		case 1078: return "MSG_OPEN_GATE";
		case 1079: return "MSG_DO_CHEER";
		case 1080: return "MSG_CLOSE_GATE";
		case 1081: return "MSG_SWITCH_WEAPONS";
		case 1082: return "MSG_CONVERT_TO_CARBOMB";
		case 1083: return "MSG_CAPTUREBUILDING";
		case 1084: return "MSG_CASTLE_UNPACK";
		case 1085: return "MSG_CASTLE_PACK";
		case 1086: return "MSG_CASTLE_UNPACK_EXPLICIT_OBJECT";
		case 1087: return "MSG_SNIPE_VEHICLE";
		case 1088: return "MSG_DO_SPECIAL_POWER_OVERRIDE_DESTINATION";
		case 1089: return "MSG_DO_SALVAGE";
		case 1090: return "MSG_CLEAR_INGAME_POPUP_MESSAGE";
		case 1091: return "MSG_PLACE_BEACON";
		case 1092: return "MSG_REMOVE_BEACON";
		case 1093: return "MSG_SET_BEACON_TEXT";
		case 1094: return "MSG_SET_REPLAY_CAMERA";
		case 1095: return "MSG_SELF_DESTRUCT";
		case 1096: return "MSG_CREATE_FORMATION";
		case 1097: return "MSG_LOGIC_CRC";
		case 1098: return "MSG_SET_MINE_CLEARING_DETAIL";
		case 1099: return "MSG_DO_USER1";
		case 1100: return "MSG_DO_USER2";
		case 1101: return "MSG_DO_USER3";
		case 1102: return "MSG_DO_USER4";
		case 1103: return "MSG_MOVE_ARMY_TO_POSITION";
		case 1104: return "MSG_AUTO_SAVE";
		case 1105: return "MSG_CHANGE_CAMERA_ARRIVED_AT_WAYPOINTID";
		case 1106: return "MSG_HORDE_TOGGLE_FORMATION";
		case 1107: return "MSG_ONE_RING";
		case 1108: return "MSG_CREW_EVACUATE";
		case 1109: return "MSG_DO_SPELLBOOK_SPECIAL_POWER";
		case 1110: return "MSG_WEAPONSET_TOGGLE";
		case 1111: return "MSG_DO_AUTO_ABILITY";
		case 1112: return "MSG_DO_AUTO_ABILITY_WEAPON";
		case 1113: return "MSG_REVIVE";
		case 1114: return "MSG_TOGGLE_NO_AUTO_ACQUIRE";
		case 1115: return "MSG_WAKE_AUTO_PICKUP";
		case 1116: return "MSG_START_SELF_REPAIR";
		case 1117: return "MSG_SUMMON_REINFORCEMENTS";
		case 1118: return "MSG_CALL_IN_REINFORCEMENTS";
		case 1119: return "MSG_HORDE_SET_FORMATION";
		case 1120: return "MSG_CREATE_SELECT_ALL_GROUP";
		case 1121: return "MSG_ENABLE_RETALIATION_MODE";
	}
	CHECK_IF(0, "MSG_INVALID")
	CHECK_IF(2, "MSG_RAW_MOUSE_BEGIN")
	CHECK_IF(3, "MSG_RAW_MOUSE_POSITION")
	CHECK_IF(4, "MSG_RAW_MOUSE_LEFT_BUTTON_DOWN")
	CHECK_IF(5, "MSG_RAW_MOUSE_LEFT_DOUBLE_CLICK")
	CHECK_IF(6, "MSG_RAW_MOUSE_LEFT_BUTTON_UP")
	CHECK_IF(7, "MSG_RAW_MOUSE_LEFT_CLICK")
	CHECK_IF(8, "MSG_RAW_MOUSE_LEFT_DRAG")
	CHECK_IF(10, "MSG_RAW_MOUSE_MIDDLE_BUTTON_DOWN")
	CHECK_IF(11, "MSG_RAW_MOUSE_MIDDLE_DOUBLE_CLICK")
	CHECK_IF(12, "MSG_RAW_MOUSE_MIDDLE_BUTTON_UP")
	CHECK_IF(13, "MSG_RAW_MOUSE_MIDDLE_DRAG")
	CHECK_IF(14, "MSG_RAW_MOUSE_RIGHT_BUTTON_DOWN")
	CHECK_IF(15, "MSG_RAW_MOUSE_RIGHT_DOUBLE_CLICK")
	CHECK_IF(16, "MSG_RAW_MOUSE_RIGHT_BUTTON_UP")
	CHECK_IF(18, "MSG_RAW_MOUSE_RIGHT_DRAG")
	CHECK_IF(19, "MSG_RAW_MOUSE_WHEEL")
	CHECK_IF(20, "MSG_RAW_MOUSE_END")
	CHECK_IF(21, "MSG_RAW_KEY_DOWN")
	CHECK_IF(22, "MSG_RAW_KEY_UP")
	CHECK_IF(23, "MSG_MOUSE_LEFT_CLICK")
	CHECK_IF(24, "MSG_MOUSE_LEFT_DOUBLE_CLICK")
	CHECK_IF(25, "MSG_MOUSE_MIDDLE_CLICK")
	CHECK_IF(26, "MSG_MOUSE_MIDDLE_DOUBLE_CLICK")
	CHECK_IF(27, "MSG_MOUSE_RIGHT_CLICK")
	CHECK_IF(28, "MSG_MOUSE_RIGHT_DOUBLE_CLICK")
	CHECK_IF(29, "MSG_CLEAR_GAME_DATA")
	CHECK_IF(30, "MSG_NEW_GAME")
	CHECK_IF(31, "MSG_START_LIVING_WORLD_LOGIC")
	CHECK_IF(32, "MSG_BEGIN_META_MESSAGES")
	CHECK_IF(147, "MSG_END_META_MESSAGES")
	CHECK_IF(148, "MSG_MOUSEOVER_DRAWABLE_HINT")
	CHECK_IF(149, "MSG_MOUSEOVER_LOCATION_HINT")
	CHECK_IF(150, "MSG_VALID_GUICOMMAND_HINT")
	CHECK_IF(151, "MSG_INVALID_GUICOMMAND_HINT")
	CHECK_IF(152, "MSG_AREA_SELECTION_HINT")
	CHECK_IF(153, "MSG_DO_ATTACK_OBJECT_HINT")
	CHECK_IF(178, "MSG_DO_ATTACK_OBJECT_AFTER_MOVING_HINT")
	CHECK_IF(155, "MSG_DO_FORCE_ATTACK_OBJECT_HINT")
	CHECK_IF(156, "MSG_DO_FORCE_ATTACK_GROUND_HINT")
	CHECK_IF(157, "MSG_GET_REPAIRED_HINT")
	CHECK_IF(158, "MSG_GET_HEALED_HINT")
	CHECK_IF(159, "MSG_DO_REPAIR_HINT")
	CHECK_IF(160, "MSG_RESUME_CONSTRUCTION_HINT")
	CHECK_IF(161, "MSG_ENTER_HINT")
	CHECK_IF(162, "MSG_CONTEST_HINT")
	CHECK_IF(163, "MSG_DOCK_HINT")
	CHECK_IF(164, "MSG_HARVEST_HINT")
	CHECK_IF(165, "MSG_DO_MOVETO_HINT")
	CHECK_IF(166, "MSG_DO_ATTACKMOVETO_HINT")
	CHECK_IF(167, "MSG_ADD_WAYPOINT_HINT")
	CHECK_IF(168, "MSG_HIJACK_HINT")
	CHECK_IF(169, "MSG_FIREBOMB_HINT")
	CHECK_IF(170, "MSG_CONVERT_TO_CARBOMB_HINT")
	CHECK_IF(171, "MSG_CAPTUREBUILDING_HINT")
	CHECK_IF(180, "MSG_APT_SKIP_NEXT_MSG")
	CHECK_IF(172, "MSG_SNIPE_VEHICLE_HINT")
	CHECK_IF(173, "MSG_DEFECTOR_HINT")
	CHECK_IF(174, "MSG_SET_RALLY_POINT_HINT")
	CHECK_IF(176, "MSG_DO_SALVAGE_HINT")
	CHECK_IF(177, "MSG_DO_INVALID_HINT")
	CHECK_IF(1000, "MSG_BEGIN_NETWORK_MESSAGES")
	CHECK_IF(1999, "MSG_END_NETWORK_MESSAGES")
	CHECK_IF(2000, "MSG_TIMESTAMP")
	CHECK_IF(2001, "MSG_OBJECT_CREATED")
	CHECK_IF(2002, "MSG_OBJECT_DESTROYED")
	CHECK_IF(2003, "MSG_OBJECT_POSITION")
	CHECK_IF(2004, "MSG_OBJECT_ORIENTATION")
	CHECK_IF(2005, "MSG_OBJECT_JOINED_TEAM")
	CHECK_IF(2006, "MSG_GIVE_UPGRADE_HINT")
	CHECK_IF(2007, "MSG_JOIN_HORDE_HINT")
	CHECK_IF(2008, "MSG_CAN_GRAB_HINT")
	return commandName;
}
