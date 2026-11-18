// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib

// Retail reaches both compareNoCase and releaseBuffer as StringBase<G>
// members so UnicodeString is spelled as the derived class rather than a
// stand-in. That also rules out the languagefilter shim here -- its minimal
// StringBase would redefine the real one that AsciiString.h pulls in.
#include "Common/AsciiString.h"

#include "../../Include/Common/Enums/SlotState.h"









// Modelled on the AsciiString shim rather than derived from StringBase: the
// real StringBase default ctor is out of line so inheriting it emits a call
// where retail inlines a single zero store and shares the zero with the EH
// state. An undefined ~UnicodeString is already pinned to the same address as
// releaseBuffer<G>. unsigned short not wchar_t because this TU compiles with
// /Zc:wchar_t- and pulls no header declaring wchar_t; G is unsigned short.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
#include "../../../Libraries/Source/WWVegas/WWLib/unicode_string.h"
inline UnicodeString::UnicodeString() { m_text = 0; }


// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	virtual void reset(void) = 0;	// vptr; m_state therefore lands at offset 4
	bool isPlayer(AsciiString userName) const;
protected:
	SlotState m_state;
	unsigned char m_gap08[0x28 - 0x08];
	UnicodeString m_name;
};

// ?isPlayer@GameSlot@@QBE_NVAsciiString@@@Z
bool GameSlot::isPlayer(AsciiString userName) const
{
	UnicodeString uName;
	uName.translate(userName);
	return (m_state == SLOT_PLAYER && !m_name.compareNoCase(uName));
}
