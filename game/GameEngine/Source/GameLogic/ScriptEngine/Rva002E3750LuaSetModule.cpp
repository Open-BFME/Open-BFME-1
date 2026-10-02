// cl: /Igame/Libraries/Source/WWVegas/WWLib
// ?Rva002E3750SetModule@@YADDPBD@Z
// The Lua CurDrawableHideModule (0x002E3820, pushes hide = 1) and
// CurDrawableShowModule (0x002E3840, pushes hide = 0) callbacks, each with
// lua_tostring(L, 1), share this module-name helper; the owner call receives
// the inverted flag.
//
// The owner is read through the chain in one expression, not through a named
// intermediate for the +0x78 pointer: with that local, MSVC 7.1 loads the owner
// before the text and allocates ESI/EAX and EBX/CL instead of retail's
// text-in-ECX and AL/DL flag schedule.

#include "ascii_string.h"

struct BfmeStrAE
{
	char *m_bfmeDataAE;
};

class BfmeOwnerAE
{
public:
	char bfmeSetAE(BfmeStrAE *name, char on);
};

struct BfmeTargetBR
{
	char m_bfmePad[0x0c];
	BfmeOwnerAE *m_bfmeOwner;
};

struct BfmeOwnerBR
{
	char m_bfmePad[0x78];
	BfmeTargetBR *m_bfmeTarget;
};

// Retail's singleton at 0x012F060C is EA's `LuaScriptEngine
// *TheLuaScriptEngine` (defined by game/GameEngine/Source/Common/RTS/
// Team_updateState.cpp:334, data_rows.csv row 36); the +0x78 chain read
// below walks the same cell through this TU's address-derived view.
class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;

char Rva002E3750SetModule(char hide, const char *text)
{
	if (((BfmeOwnerBR *)TheLuaScriptEngine)->m_bfmeTarget != 0) {
		BfmeOwnerAE *owner = ((BfmeOwnerBR *)TheLuaScriptEngine)->m_bfmeTarget->m_bfmeOwner;
		AsciiString name(text);
		if (owner != 0)
			return owner->bfmeSetAE((BfmeStrAE *)&name, hide == 0);
	}
	return 0;
}
