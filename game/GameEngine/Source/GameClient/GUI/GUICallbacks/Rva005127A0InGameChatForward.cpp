// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/languagefilter /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib

#include "Common/UnicodeString.h"

class Rva005127A0InGameChat
{
public:
	bool handle(UnicodeString text, int channel);
};

extern Rva005127A0InGameChat *g_Rva005127A0InGameChat;

bool Rva005127A0Forward(UnicodeString text, int channel)
{
	if (!g_Rva005127A0InGameChat)
		return false;

	return g_Rva005127A0InGameChat->handle(text, channel);
}
