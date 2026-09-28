// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// BFME Rva0061FDA0Owner::xfer at retail 0x0061FDA0 (901 bytes).
// Twin of SkirmishGameInfo::xfer at 0x0061F930: the twin TU compiled here
// probes EXACT 901/901 modulo relocations, so the instruction shape is shared.
// Distinct class, not the same function. Identity evidence (retail image):
// ctor 0x00619720 stores vtable 0x011171C8 into this object, while the twin's
// ctor 0x00075C10 stores 0x01075E7C; dir32 rows ??_7SkirmishGameInfo@@6BSnapshot@@@
// -> 0x011171C8 vs ??_7Open2SlotOwner75C10@@6BSnapshot@@@ -> 0x01075E7C, slot 3.
// Owner unproven, so the address-derived name keeps the address token.
// Derived from Zero Hour GameInfo.cpp, Copyright 2025 Electronic Arts Inc., GPL-3.0-or-later.

#include "ascii_string.h"
#include "unicode_string.h"

// ??0UnicodeString@@QAE@ABV0@@Z absent-from-retail
inline UnicodeString::UnicodeString(const UnicodeString &other)
{
    ((StringBase<unsigned short> *)this)
        ->StringBase<unsigned short>::StringBase(
            *(const StringBase<unsigned short> *)&other);
}

// ??1UnicodeString@@QAE@XZ absent-from-retail
inline UnicodeString::~UnicodeString()
{
    ((StringBase<unsigned short> *)this)->releaseBuffer();
}

typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;

struct BfmeXferVersion
{
    UnsignedByte m_version;
    UnsignedByte m_currentVersion;
};

class Xfer
{
public:
    virtual void slot00();
    virtual Bool getXferMode();
    virtual void slot02();
    virtual void slot03();
    virtual Bool isDraft();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void xferVersion(BfmeXferVersion *version);
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void xferUnicodeString(UnicodeString *value);
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void xferUnsignedInt(UnsignedInt *value);
    virtual void xferInt(Int *value);
    virtual void xferUnsignedShort(UnsignedShort *value);
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void xferBool(Bool *value);
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

// Retail builds the loop's zeroed argument and the tail's IP/port pair as
// 8-byte objects that share one stack slot.
struct GameSlotConnectInfo
{
    GameSlotConnectInfo() : m_nat(0), m_port(0) {}
    GameSlotConnectInfo(UnsignedInt ip, UnsignedShort port) : m_nat(ip), m_port(port) {}
    Int m_nat;
    UnsignedShort m_port;
};

class GameSlot
{
public:
    virtual void reset();
    SlotState getState() const { return m_state; }
    UnicodeString getName() const;
    Bool isAccepted() const { return m_isAccepted; }
    Bool isMuted() const { return m_isMuted; }
    Int getColor() const { return m_color; }
    Int getStartPos() const { return m_startPos; }
    Int getPlayerTemplate() const { return m_playerTemplate; }
    Int getTeamNumber() const { return m_teamNumber; }
    Int getOriginalColor() const { return m_origColor; }
    Int getOriginalStartPos() const { return m_origStartPos; }
    Int getOriginalPlayerTemplate() const { return m_origPlayerTemplate; }
    void setState(SlotState state, UnicodeString name,
        const GameSlotConnectInfo *connectInfo);
    void setAccept() { m_isAccepted = true; }
    void mute(Bool value) { m_isMuted = value; }
    void setColor(Int value) { m_color = value; }
    void setStartPos(Int value) { m_startPos = value; }
    void setPlayerTemplate(Int value)
    {
        m_playerTemplate = value;
        if (value <= -2)
            m_startPos = -1;
    }
    void setTeamNumber(Int value) { m_teamNumber = value; }
    void saveOffOriginalInfo()
    {
        m_origPlayerTemplate = m_playerTemplate;
        m_origStartPos = m_startPos;
        m_origColor = m_color;
    }

protected:
    SlotState m_state;
    Bool m_isAccepted;
    Bool m_hasMap;
    Bool m_isMuted;
    Int m_color;
    Int m_startPos;
    Int m_playerTemplate;
    Int m_teamNumber;
    Int m_origColor;
    Int m_origStartPos;
    Int m_origPlayerTemplate;
    UnicodeString m_name;
    unsigned char m_tail[0x18];
};

class GameInfo
{
public:
    virtual void reset();

protected:
    Int m_preorderMask;
    Int m_crcInterval;
    Bool m_inGame;
    Bool m_inProgress;
    Bool m_surrendered;
    unsigned char m_padding0f;
    Int m_gameID;
    GameSlot *m_slot[8];
    UnsignedInt m_localIP;
    Int m_extra38;
    AsciiString m_mapName;
    UnsignedInt m_mapCRC;
    UnsignedInt m_mapSize;
    Int m_mapMask;
    Int m_seed;
    Int m_useStats;
    Int m_tail;
};

class Snapshot
{
protected:
    virtual void crc(Xfer *xfer) = 0;
    virtual void xfer(Xfer *xfer) = 0;
    virtual void loadPostProcess() = 0;
};

class Rva0061FDA0Owner : public GameInfo, public Snapshot
{
protected:
    virtual void xfer(Xfer *xfer);
};

extern void __cdecl xferMapName(Xfer *xfer, AsciiString *mapName);

// ?xfer@Rva0061FDA0Owner@@MAEXPAVXfer@@@Z
void Rva0061FDA0Owner::xfer(Xfer *xfer)
{
    if (!xfer->isDraft())
    {
        {
            BfmeXferVersion version = { 1, 1 };
            xfer->xferVersion(&version);
        }

        xfer->xferInt(&m_preorderMask);
        xfer->xferInt(&m_crcInterval);
        xfer->xferBool(&m_inGame);
        xfer->xferBool(&m_inProgress);
        xfer->xferBool(&m_surrendered);
        xfer->xferInt(&m_gameID);

        Int slot = 8;
        xfer->xferInt(&slot);
        for (slot = 0; slot < 8; ++slot)
        {
            Int state = m_slot[slot]->getState();
            xfer->xferInt(&state);

            UnicodeString name = m_slot[slot]->getName();
            xfer->xferUnicodeString(&name);

            Bool isAccepted = m_slot[slot]->isAccepted();
            xfer->xferBool(&isAccepted);

            Bool isMuted = m_slot[slot]->isMuted();
            xfer->xferBool(&isMuted);
            m_slot[slot]->mute(isMuted);

            Int color = m_slot[slot]->getColor();
            xfer->xferInt(&color);

            Int startPos = m_slot[slot]->getStartPos();
            xfer->xferInt(&startPos);

            Int playerTemplate = m_slot[slot]->getPlayerTemplate();
            xfer->xferInt(&playerTemplate);

            Int teamNumber = m_slot[slot]->getTeamNumber();
            xfer->xferInt(&teamNumber);

            Int origColor = m_slot[slot]->getOriginalColor();
            xfer->xferInt(&origColor);

            Int origStartPos = m_slot[slot]->getOriginalStartPos();
            xfer->xferInt(&origStartPos);

            Int origPlayerTemplate = m_slot[slot]->getOriginalPlayerTemplate();
            xfer->xferInt(&origPlayerTemplate);

            if (xfer->getXferMode())
            {
                GameSlotConnectInfo connectInfo;
                m_slot[slot]->setState((SlotState)state, name, &connectInfo);
                if (isAccepted)
                    m_slot[slot]->setAccept();
                m_slot[slot]->setPlayerTemplate(origPlayerTemplate);
                m_slot[slot]->setStartPos(origStartPos);
                m_slot[slot]->setColor(origColor);
                m_slot[slot]->saveOffOriginalInfo();
                m_slot[slot]->setTeamNumber(teamNumber);
                m_slot[slot]->setColor(color);
                m_slot[slot]->setStartPos(startPos);
                m_slot[slot]->setPlayerTemplate(playerTemplate);
            }
        }
        UnsignedInt localIP = m_localIP;
        xfer->xferUnsignedInt(&localIP);
        UnsignedShort extra38 = (UnsignedShort)m_extra38;
        xfer->xferUnsignedShort(&extra38);
        // Retail writes GameInfo+0x34 and +0x38 back as one 8-byte pair copy.
        *(GameSlotConnectInfo *)&m_localIP = GameSlotConnectInfo(localIP, extra38);
        xferMapName(xfer, &m_mapName);
        xfer->xferUnsignedInt(&m_mapCRC);
        xfer->xferUnsignedInt(&m_mapSize);
        xfer->xferInt(&m_mapMask);
        xfer->xferInt(&m_seed);
    }
}
