// cl: /DNDEBUG /MD /EHsc
// readable body of ?getSlotNum@LANGameInfo@@QAEHVUnicodeString@@@Z: game/GameEngine/Source/GameNetwork/LANGameInfo.cpp
// readable body of ?isUser@LANGameSlot@@QAE_NVUnicodeString@@@Z: game/GameEngine/Source/GameNetwork/LANGameInfo.cpp

template <typename T>
class StringBase
{
    friend class UnicodeString;
public:
    // A nonthrowing comparison preserves the temporary's retail unwind state.
    int compareNoCase(const StringBase<T> &other) const throw();
private:
    StringBase(const StringBase<T> &other);
    ~StringBase();
    void *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<unsigned short>
{
public:
    UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
    ~UnicodeString() {}
    int compareNoCase(const UnicodeString &other) const throw()
    {
        return StringBase<unsigned short>::compareNoCase(other);
    }
};

enum SlotState
{
    SLOT_OPEN,
    SLOT_CLOSED,
    SLOT_EASY_AI,
    SLOT_MED_AI,
    SLOT_BRUTAL_AI,
    SLOT_PLAYER
};

// Retail calls getName and isUser through their separate incremental-link thunks.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
    virtual void reset();
    __declspec(noinline) UnicodeString getName() const;
protected:
    SlotState m_state;
    char m_unrecovered08[0x20];
    UnicodeString m_name;
    char m_unrecovered2C[0x18];
};

// The copy at 0x00686D50 places derived members at +0x44/+0x60/+0x64;
// lookup advances by 0x68. Their unused contents remain opaque here.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
class LANGameSlot : public GameSlot
{
public:
    __declspec(noinline) bool isUser(UnicodeString userName);
private:
    char m_unrecovered44[0x24];
};

typedef char GameSlotSize[sizeof(GameSlot) == 0x44 ? 1 : -1];
typedef char LANGameSlotSize[sizeof(LANGameSlot) == 0x68 ? 1 : -1];

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
class LANGameInfo
{
public:
    int getSlotNum(UnicodeString userName);
private:
    LANGameSlot *getLANSlot(int slotNum)
    {
        if (slotNum < 0 || slotNum >= 8)
            return 0;
        return &m_slots[slotNum];
    }
    unsigned char m_unrecovered00[0x0c];
    bool m_inGame;
    unsigned char m_unrecovered0D[0x4b];
    LANGameSlot m_slots[8];
};

// ?getName@GameSlot@@QBE?AVUnicodeString@@XZ
UnicodeString GameSlot::getName() const
{
    return m_name;
}

// ?isUser@LANGameSlot@@QAE_NVUnicodeString@@@Z
bool LANGameSlot::isUser(UnicodeString userName)
{
    return m_state == SLOT_PLAYER && !userName.compareNoCase(getName());
}

// ?getSlotNum@LANGameInfo@@QAEHVUnicodeString@@@Z
int LANGameInfo::getSlotNum(UnicodeString userName)
{
    if (!m_inGame)
        return -1;
    for (int i = 0; i < 8; ++i)
    {
        LANGameSlot *slot = getLANSlot(i);
        if (slot->isUser(userName))
            return i;
    }
    return -1;
}
