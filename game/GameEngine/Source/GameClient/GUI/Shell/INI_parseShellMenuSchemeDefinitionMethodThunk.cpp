// cl: /DNDEBUG /MD /EHsc /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas
// stlport
// Clean BFME layout reconstruction of INI::parseShellMenuSchemeDefinition.

#include "Common/INI.h"
#include "GameClient/ShellMenuScheme.h"

// TU-local view of the retail shell singleton; 0x012F4B58's one identity is
// ?TheShell@@3PAVShell@@A.
class Shell
{
public:
	unsigned char m_pad[0x60];
	ShellMenuSchemeManager *m_schemeManager;
};

extern Shell *TheShell;

// ?parseShellMenuSchemeDefinition@INI@@SAXPAV1@@Z
void INI::parseShellMenuSchemeDefinition(INI *ini)
{
	AsciiString name;
	const char *text = ini->getNextToken();
	Int length = text ? strlen(text) : 0;
	name.StringBase<char>::set(text, length);

	ShellMenuSchemeManager *manager = TheShell->m_schemeManager;
	if (manager) {
		AsciiString &argument = name;
		ShellMenuScheme *scheme = manager->newShellMenuScheme(argument);
		ini->initFromINI(scheme, manager->getFieldParse());
	}
}
