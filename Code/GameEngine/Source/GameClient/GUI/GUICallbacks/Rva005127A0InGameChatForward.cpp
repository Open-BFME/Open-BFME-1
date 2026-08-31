// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/languagefilter /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib

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
