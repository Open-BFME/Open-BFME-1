// cl: /DNDEBUG /MD /EHsc
// readable body of ?getSlotNum@LANGameInfo@@QAEHVUnicodeString@@@Z: Code/GameEngine/Source/GameNetwork/LANGameInfo.cpp

typedef bool Bool;
typedef int Int;

class UnicodeString;

// Retail inlines the wide-string base copy here, preserving its EH temporary ordering.
template <class Character>
class StringBase
{
private:
	StringBase(const StringBase &that);
	friend class UnicodeString;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	UnicodeString(const UnicodeString &that)
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
			*(const StringBase<unsigned short> *)&that);
	}
	~UnicodeString();

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
class LANGameSlot
{
public:
	Bool isUser(UnicodeString userName);

private:
	unsigned char m_data[0x68];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
class LANGameInfo
{
public:
	Int getSlotNum(UnicodeString userName);

private:
	LANGameSlot *getLANSlot(Int slotNum)
	{
		if (slotNum < 0 || slotNum >= 8)
			return 0;
		return &m_slots[slotNum];
	}

	unsigned char m_unreconstructed_00[0x0c];
	Bool m_inGame;
	unsigned char m_unreconstructed_0d[0x4b];
	LANGameSlot m_slots[8];
};

// ?getSlotNum@LANGameInfo@@QAEHVUnicodeString@@@Z
Int LANGameInfo::getSlotNum(UnicodeString userName)
{
	if (!m_inGame)
		return -1;

	for (Int i = 0; i < 8; ++i) {
		LANGameSlot *slot = getLANSlot(i);
		if (slot->isUser(userName))
			return i;
	}
	return -1;
}
