// cl: /Iinputs/reference/shims/stringbaseunicode /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// The DebugCommandMap block. It reads the entry name and throws it away, parses
// a full entry into a local, and then discards that too -- so in a release build
// the block validates its own syntax and stores nothing. The retail code really
// is this: getNextToken with the result unused, initFromINI into stack space,
// and two UnicodeString destructors on the way out.
//
// Field names and offsets are the retail table at 0x0110E570
// (docs/ini_schema.md). Nothing writes 0x00-0x07, so that stays a pad.
#include "PreRTS.h"
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }
#include "Common/INI.h"

struct DebugCommandMapEntry
{
	char m_unknown00[ 0x08 ];		// 0x00  no INI field writes here
	Int m_key;						// 0x08  Key
	Int m_transition;				// 0x0c  Transition
	Int m_modifiers;				// 0x10  Modifiers
	Int m_useableIn;				// 0x14  UseableIn
	Int m_category;					// 0x18  Category
	UnicodeString m_description;	// 0x1c  Description
	UnicodeString m_displayName;	// 0x20  DisplayName


};

extern const LookupListRec KeyNames[], TransitionNames[], ModifierNames[], CategoryListName[];
extern const char *TheCommandUsableInNames[];
extern "C" void __identifier("?parseLookupList@INI@@SAXPAV1@PAX1PBX@Z")(INI *, void *, void *, const void *);
extern "C" void __identifier("?parseBitString32@INI@@SAXPAV1@PAX1PBX@Z")(INI *, void *, void *, const void *);
extern "C" void __identifier("?parseAndTranslateLabel@INI@@SAXPAV1@PAX1PBX@Z")(INI *, void *, void *, const void *);

extern const FieldParse TheMetaMapFieldParseTable[] =
{
	{ "Key", __identifier("?parseLookupList@INI@@SAXPAV1@PAX1PBX@Z"), KeyNames, 0x8 },
	{ "Transition", __identifier("?parseLookupList@INI@@SAXPAV1@PAX1PBX@Z"), TransitionNames, 0xc },
	{ "Modifiers", __identifier("?parseLookupList@INI@@SAXPAV1@PAX1PBX@Z"), ModifierNames, 0x10 },
	{ "UseableIn", __identifier("?parseBitString32@INI@@SAXPAV1@PAX1PBX@Z"), TheCommandUsableInNames, 0x14 },
	{ "Category", __identifier("?parseLookupList@INI@@SAXPAV1@PAX1PBX@Z"), CategoryListName, 0x18 },
	{ "Description", __identifier("?parseAndTranslateLabel@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1c },
	{ "DisplayName", __identifier("?parseAndTranslateLabel@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x20 },
	{ 0, 0, 0, 0 }
};

extern const LookupListRec KeyNames[] =
{
	{ "KEY_ESC", 1 },
	{ "KEY_BACKSPACE", 14 },
	{ "KEY_ENTER", 28 },
	{ "KEY_SPACE", 57 },
	{ "KEY_TAB", 15 },
	{ "KEY_F1", 59 },
	{ "KEY_F2", 60 },
	{ "KEY_F3", 61 },
	{ "KEY_F4", 62 },
	{ "KEY_F5", 63 },
	{ "KEY_F6", 64 },
	{ "KEY_F7", 65 },
	{ "KEY_F8", 66 },
	{ "KEY_F9", 67 },
	{ "KEY_F10", 68 },
	{ "KEY_F11", 87 },
	{ "KEY_F12", 88 },
	{ "KEY_A", 30 },
	{ "KEY_B", 48 },
	{ "KEY_C", 46 },
	{ "KEY_D", 32 },
	{ "KEY_E", 18 },
	{ "KEY_F", 33 },
	{ "KEY_G", 34 },
	{ "KEY_H", 35 },
	{ "KEY_I", 23 },
	{ "KEY_J", 36 },
	{ "KEY_K", 37 },
	{ "KEY_L", 38 },
	{ "KEY_M", 50 },
	{ "KEY_N", 49 },
	{ "KEY_O", 24 },
	{ "KEY_P", 25 },
	{ "KEY_Q", 16 },
	{ "KEY_R", 19 },
	{ "KEY_S", 31 },
	{ "KEY_T", 20 },
	{ "KEY_U", 22 },
	{ "KEY_V", 47 },
	{ "KEY_W", 17 },
	{ "KEY_X", 45 },
	{ "KEY_Y", 21 },
	{ "KEY_Z", 44 },
	{ "KEY_1", 2 },
	{ "KEY_2", 3 },
	{ "KEY_3", 4 },
	{ "KEY_4", 5 },
	{ "KEY_5", 6 },
	{ "KEY_6", 7 },
	{ "KEY_7", 8 },
	{ "KEY_8", 9 },
	{ "KEY_9", 10 },
	{ "KEY_0", 11 },
	{ "KEY_KP1", 79 },
	{ "KEY_KP2", 80 },
	{ "KEY_KP3", 81 },
	{ "KEY_KP4", 75 },
	{ "KEY_KP5", 76 },
	{ "KEY_KP6", 77 },
	{ "KEY_KP7", 71 },
	{ "KEY_KP8", 72 },
	{ "KEY_KP9", 73 },
	{ "KEY_KP0", 82 },
	{ "KEY_MINUS", 12 },
	{ "KEY_EQUAL", 13 },
	{ "KEY_LBRACKET", 26 },
	{ "KEY_RBRACKET", 27 },
	{ "KEY_SEMICOLON", 39 },
	{ "KEY_APOSTROPHE", 40 },
	{ "KEY_TICK", 41 },
	{ "KEY_BACKSLASH", 43 },
	{ "KEY_COMMA", 51 },
	{ "KEY_PERIOD", 52 },
	{ "KEY_SLASH", 53 },
	{ "KEY_UP", 200 },
	{ "KEY_DOWN", 208 },
	{ "KEY_LEFT", 203 },
	{ "KEY_RIGHT", 205 },
	{ "KEY_HOME", 199 },
	{ "KEY_END", 207 },
	{ "KEY_PGUP", 201 },
	{ "KEY_PGDN", 209 },
	{ "KEY_INS", 210 },
	{ "KEY_DEL", 211 },
	{ "KEY_KPSLASH", 181 },
	{ "KEY_NONE", 0 },
	{ 0, 0 }
};

extern const LookupListRec TransitionNames[] =
{
	{ "DOWN", 0 },
	{ "UP", 1 },
	{ "DOUBLEDOWN", 2 },
	{ 0, 0 }
};

extern const LookupListRec ModifierNames[] =
{
	{ "NONE", 0 },
	{ "CTRL", 4 },
	{ "ALT", 64 },
	{ "SHIFT", 16 },
	{ "CTRL_ALT", 68 },
	{ "SHIFT_CTRL", 20 },
	{ "SHIFT_ALT", 80 },
	{ "SHIFT_ALT_CTRL", 84 },
	{ 0, 0 }
};

extern const LookupListRec CategoryListName[] =
{
	{ "CONTROL", 0 },
	{ "INFORMATION", 1 },
	{ "INTERFACE", 2 },
	{ "SELECTION", 3 },
	{ "TAUNT", 4 },
	{ "TEAM", 5 },
	{ "MISC", 6 },
	{ "DEBUG", 7 },
	{ 0, 0 }
};

const char *TheCommandUsableInNames[] =
{
	"SHELL",
	"GAME",
	0
};

void parseDebugCommandMap( INI *ini )
{
	ini->getNextToken();

	DebugCommandMapEntry entry;
	ini->initFromINI( &entry, TheMetaMapFieldParseTable );
}
