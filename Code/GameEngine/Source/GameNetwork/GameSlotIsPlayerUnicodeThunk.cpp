// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/campaignmanagerascii /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /ICode/Libraries/Source/WWVegas/WWLib

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
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
