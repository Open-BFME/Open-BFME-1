// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Igame/Libraries/Source/WWVegas/WWLib

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

class GameSlot;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	int compareNoCase(const UnicodeString& that) const
	{
		return ((const StringBase<unsigned short> *)this)->compareNoCase(
			*(const StringBase<unsigned short> *)&that);
	}


protected:
	friend class GameSlot;
	void releaseBuffer();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	virtual void reset(void) = 0;
	bool isPlayer(UnicodeString userName) const;
protected:
	SlotState m_state;
	unsigned char m_gap08[0x28 - 0x08];
	UnicodeString m_name;
};

bool GameSlot::isPlayer(UnicodeString userName) const
{
	bool result;
	if (m_state == SLOT_PLAYER && m_name.compareNoCase(userName) == 0) {
		result = true;
	} else {
		result = false;
	}

done:
	userName.releaseBuffer();
	return result;
}
