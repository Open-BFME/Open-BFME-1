// cl: /ICode/Libraries/Source/WWVegas/WWLib
// ?Rva002E3750SetModule@@YADDPBD@Z
// The Lua ShowModule and HideModule callbacks (0x002E3820 pushes 1, 0x002E3840
// pushes 0, each with lua_tostring(L, 1)) share this module-name helper.
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

extern BfmeOwnerBR *g_bfmeOwnerBR;

char Rva002E3750SetModule(char on, const char *text)
{
	if (g_bfmeOwnerBR->m_bfmeTarget != 0) {
		BfmeOwnerAE *owner = g_bfmeOwnerBR->m_bfmeTarget->m_bfmeOwner;
		AsciiString name(text);
		if (owner != 0)
			return owner->bfmeSetAE((BfmeStrAE *)&name, on == 0);
	}
	return 0;
}
