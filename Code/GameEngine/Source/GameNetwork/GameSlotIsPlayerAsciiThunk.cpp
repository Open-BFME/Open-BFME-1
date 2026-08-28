// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/campaignmanagerascii /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib

// Retail reaches both compareNoCase and releaseBuffer as StringBase<G>
// members so UnicodeString is spelled as the derived class rather than a
// stand-in. That also rules out the languagefilter shim here -- its minimal
// StringBase would redefine the real one that AsciiString.h pulls in.
#include "Common/AsciiString.h"

enum SlotState
{
	SLOT_OPEN,
	SLOT_CLOSED,
	SLOT_EASY_AI,
	SLOT_MED_AI,
	SLOT_BRUTAL_AI,
	SLOT_PLAYER
};

// Modelled on the AsciiString shim rather than derived from StringBase: the
// real StringBase default ctor is out of line so inheriting it emits a call
// where retail inlines a single zero store and shares the zero with the EH
// state. An undefined ~UnicodeString is already pinned to the same address as
// releaseBuffer<G>. unsigned short not wchar_t because this TU compiles with
// /Zc:wchar_t- and pulls no header declaring wchar_t; G is unsigned short.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	UnicodeString() { m_text = 0; }
	~UnicodeString();

	void translate(const AsciiString& stringSrc);

	int compareNoCase(const UnicodeString& that) const
	{
		return ((const StringBase<unsigned short> *)this)->compareNoCase(
			*(const StringBase<unsigned short> *)&that);
	}

private:
	unsigned short *m_text;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
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
