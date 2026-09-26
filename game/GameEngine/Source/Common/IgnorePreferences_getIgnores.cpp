// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include "PreRTS.h"
#include "Common/IgnorePreferences.h"

// ?getIgnores@IgnorePreferences@@QAE?AV?$map@HVAsciiString@@U?$less@H@_STL@@V?$allocator@U?$pair@$$CBHVAsciiString@@@_STL@@@3@@_STL@@XZ
IgnorePrefMap IgnorePreferences::getIgnores(void)
{
	IgnorePrefMap ignores;

	IgnorePreferences::iterator it;
	for (it = begin(); it != end(); ++it)
	{
		AsciiString profileStr = it->first;
		AsciiString lastLoginStr = it->second;
		Int profileID = atoi(profileStr.str());

		ignores[profileID] = lastLoginStr;
	}

	return ignores;
}
