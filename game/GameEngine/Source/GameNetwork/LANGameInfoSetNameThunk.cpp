// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib

// BFME delegates this assignment to StringBase<wchar_t>::set at 0x00888530.
// The legacy languagefilter adapter emitted UnicodeString::operator= instead.
#include <stddef.h>
#include "Common/UnicodeString.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
class LANGameInfo
{
public:
	void setName(UnicodeString name);
private:
	unsigned char m_pad[0x3a0];
	UnicodeString m_gameName;
};

// ?setName@LANGameInfo@@QAEXVUnicodeString@@@Z
void LANGameInfo::setName(UnicodeString name)
{
	m_gameName = name;
}
