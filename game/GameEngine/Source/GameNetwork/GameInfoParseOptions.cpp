// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Native BFME GameInfo option parser at 0x00621C40 (4834 bytes with switch tables).
// Derived from GameInfo.cpp, Copyright 2025 Electronic Arts Inc., GPL-3.0-or-later.
// Independent identity, connection layout, callee and complete-boundary evidence:
// targets/game/reverse/identity_evidence/00621c40-gameinfo-parser.md.
#define __PLACEMENT_VEC_NEW_INLINE
#define _STLP_NO_EXCEPTIONS 1
#include "ascii_string.h"
#include "unicode_string.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#pragma intrinsic(strlen)
template <> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }
template <> inline int StringBase<char>::getLength() const { return m_data ? m_data->length : 0; }
template <> inline bool StringBase<char>::isEmpty() const { return !m_data || m_data->length == 0; }
template <> inline int StringBase<char>::compare(const char *other) const {
    int otherLength = other ? strlen(other) : 0;
    int length = m_data ? m_data->length : 0;
    const char *data = m_data ? m_data->data : "";
    int result = memcmp(data, other, length < otherLength ? length : otherLength);
    if (result == 0)
        result = length - otherLength;
    return result;
}
inline AsciiString &AsciiString::operator=(const char *str) {
    StringBase<char>::set(str, str ? strlen(str) : 0);
    return *this;
}
inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::UnicodeString(const UnicodeString &s) {
    ((StringBase<unsigned short> *)this)
        ->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&s);
}
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }
inline UnicodeString &UnicodeString::operator=(const UnicodeString &s) {
    ((StringBase<unsigned short> *)this)->set(*(const StringBase<unsigned short> *)&s);
    return *this;
}
inline UnicodeString &UnicodeString::operator=(const wchar_t *s) {
    ((StringBase<unsigned short> *)this)->set((const unsigned short *)s);
    return *this;
}
extern const UnicodeString Rva01336E54EmptyUnicode;
extern char *__cdecl BFMEDuplicateString(const char *);
extern AsciiString _Rva00621350GameInfoMapPath(const AsciiString &, bool);
extern char *__cdecl strtok_r(char *, const char *, char **);
extern std::basic_string<unsigned short> MultiByteToWideCharSingleLine(const char *);
typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
#define FALSE false
#define TRUE true
enum { MAX_SLOTS = 8, PLAYERTEMPLATE_MIN = -2 };
enum SlotState { SLOT_OPEN, SLOT_CLOSED, SLOT_EASY_AI, SLOT_MED_AI, SLOT_BRUTAL_AI, SLOT_PLAYER };
// setState at 0061F210 copies IP and the complete port/padding word to +30/+34.
struct GameSlotConnectInfo {
    GameSlotConnectInfo() : m_ip(0), m_port(0) {}
    unsigned int m_ip;
    unsigned short m_port;
    char m_padding[2];
};
class GameTextInterface {
  public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20();
    virtual void slot24();
    virtual UnicodeString fetch(const char *, bool * = 0);
};
extern GameTextInterface *TheGameText;
class MultiplayerSettings {
  public:
    int getNumColors();
};
extern MultiplayerSettings *TheMultiplayerSettings;
class PlayerTemplateStore {
  public:
    int getPlayerTemplateCount() const;
};
extern PlayerTemplateStore *ThePlayerTemplateStore;
// Scoped BFME layout: the older GameInfo reference shim places IP/NAT incorrectly.
class GameSlot {
  public:
    GameSlot();
    GameSlot(const GameSlot &);
    ~GameSlot();
    virtual void reset();
    UnicodeString getName() const;
    void setState(SlotState state, UnicodeString name, const GameSlotConnectInfo *connectInfo) {
        if (!(isAI() &&
              (state == SLOT_EASY_AI || state == SLOT_MED_AI || state == SLOT_BRUTAL_AI))) {
            m_color = -1;
            m_startPos = -1;
            m_playerTemplate = -1;
            m_teamNumber = -1;
        }
        if (state == SLOT_PLAYER) {
            reset();
            m_state = state;
            m_name = name;
        } else {
            m_state = state;
            m_isAccepted = true;
            m_hasMap = true;
            switch (state) {
            case SLOT_OPEN:
                m_name = TheGameText->fetch("GUI:Open");
                break;
            case SLOT_EASY_AI:
                m_name = TheGameText->fetch("GUI:EasyAI");
                break;
            case SLOT_MED_AI:
                m_name = TheGameText->fetch("GUI:MediumAI");
                break;
            case SLOT_BRUTAL_AI:
                m_name = TheGameText->fetch("GUI:HardAI");
                break;
            default:
                m_name = TheGameText->fetch("GUI:Closed");
                break;
            }
        }
        m_connectInfo = *connectInfo;
    }
    bool isAI() const {
        return m_state == SLOT_EASY_AI || m_state == SLOT_MED_AI || m_state == SLOT_BRUTAL_AI;
    }
    void setAccept() { m_isAccepted = true; }
    void unAccept() {
        if (m_state == SLOT_PLAYER)
            m_isAccepted = false;
    }
    void setMapAvailability(bool b) {
        if (m_state == SLOT_PLAYER)
            m_hasMap = b;
    }
    void setColor(int c) { m_color = c; }
    void setPlayerTemplate(int);
    void setStartPos(int s) { m_startPos = s; }
    int getStartPos() const { return m_startPos; }
    void setTeamNumber(int t) { m_teamNumber = t; }
    void setNATBehavior(int b) { m_nat = b; }

  private:
    SlotState m_state;
    bool m_isAccepted, m_hasMap, m_isMuted;
    int m_color, m_startPos, m_playerTemplate, m_teamNumber;
    int m_origColor, m_origStartPos, m_origPlayerTemplate;
    UnicodeString m_name;
    AsciiString m_slotNameKeyText;
    GameSlotConnectInfo m_connectInfo;
    int m_nat;
    unsigned int m_lastFrameInGame;
    bool m_disconnected;
};
typedef char GameSlotSizeCheck[sizeof(GameSlot) == 0x44 ? 1 : -1];
class GameInfo {
  public:
    void setSlot(int, GameSlot);
    void setMap(AsciiString);
    void setMapCRC(unsigned int);
    void setMapSize(unsigned int);
    GameSlot *getSlot(int i) { return i < 0 || i >= 8 ? 0 : m_slots[i]; }
    void setMapContentsMask(int n) { m_mapContentsMask = n; }
    void setSeed(int n) { m_seed = n; }

  private:
    char m_unknown00[0x14];
    GameSlot *m_slots[8];
    char m_unknown34[0x14];
    int m_mapContentsMask, m_seed;
};
static const char slotListID = 'S';

static Int grabHexInt3(const char *s) {
    char tmp[6] = "0xfff";
    tmp[2] = s[0];
    tmp[3] = s[1];
    tmp[4] = s[2];
    Int b = strtol(tmp, NULL, 16);
    return b;
}
Bool ParseAsciiStringToGameInfo(GameInfo *game, AsciiString options, Bool useIncomingNames) {
    // Parse game options
    char *buf = BFMEDuplicateString(options.str());
    char *bufPtr = buf;
    char *strPos, *keyValPair;
    GameSlot newSlot[MAX_SLOTS];
    Bool optionsOk = true;
    AsciiString mapName;
    Int mapContentsMask = 0;
    UnsignedInt mapCRC = 0, mapSize = 0;
    Int seed = 0;
    Bool sawMap, sawMapCRC, sawMapSize, sawSeed, sawSlotlist;
    sawMap = sawMapCRC = sawMapSize = sawSeed = sawSlotlist = FALSE;
    UnicodeString oldNames[MAX_SLOTS];
    if (!useIncomingNames) {
        for (unsigned int i = 0; i < MAX_SLOTS; ++i)
            oldNames[i] = game->getSlot(i)->getName();
    }

    while ((keyValPair = strtok_r(bufPtr, ";", &strPos)) != NULL) {
        bufPtr = NULL; // strtok within the same string

        AsciiString key, val;
        char *pos = NULL;
        char *keyPtr, *valPtr;
        keyPtr = (strtok_r(keyValPair, "=", &pos));
        valPtr = (strtok_r(NULL, "\n", &pos));
        if (keyPtr)
            key = keyPtr;
        if (valPtr)
            val = valPtr;

        if (val.isEmpty()) {
            optionsOk = false;
            break;
        }

        if (key.compare("M") == 0) {
            if (val.getLength() < 3) {
                optionsOk = FALSE;
                break;
            }
            mapContentsMask = grabHexInt3(val.str());
            mapName = _Rva00621350GameInfoMapPath(AsciiString(val.str() + 3), FALSE);
            sawMap = true;
        } else if (key.compare("MC") == 0) {
            mapCRC = 0;
            sscanf(val.str(), "%X", &mapCRC);
            sawMapCRC = true;
        } else if (key.compare("MS") == 0) {
            mapSize = atoi(val.str());
            sawMapSize = true;
        } else if (key.compare("SD") == 0) {
            seed = atoi(val.str());
            sawSeed = true;
        } else if (key.getLength() == 1 && *key.str() == slotListID) {
            sawSlotlist = true;
            char *rawSlotBuf = BFMEDuplicateString(val.str());
            char *freeMe = NULL;
            AsciiString rawSlot;

            for (int i = 0; i < MAX_SLOTS; ++i) {
                rawSlot = strtok_r(rawSlotBuf, ":", &pos);
                if (rawSlotBuf)
                    freeMe = rawSlotBuf;
                rawSlotBuf = NULL;
                switch (*rawSlot.str()) {
                case 'H': {
                    char *slotPos = NULL;
                    // Parse out the Name
                    AsciiString slotValue(strtok_r((char *)rawSlot.str(), ",", &slotPos));
                    if (slotValue.StringBase<char>::isEmpty()) {
                        optionsOk = false;
                        break;
                    }
                    UnicodeString name;
                    name =
                        (const wchar_t *)MultiByteToWideCharSingleLine(slotValue.str() + 1).c_str();
                    if (!useIncomingNames && name.isEmpty())
                        name = oldNames[i];

                    // Parse out the IP
                    slotValue = strtok_r(NULL, ",", &slotPos);
                    if (slotValue.StringBase<char>::isEmpty()) {
                        optionsOk = false;
                        break;
                    }
                    UnsignedInt playerIP = 0;
                    sscanf(slotValue.str(), "%x", &playerIP);

                    // parse out the port
                    slotValue = strtok_r(NULL, ",", &slotPos);
                    if (slotValue.StringBase<char>::isEmpty()) {
                        optionsOk = false;
                        break;
                    }
                    UnsignedInt playerPort = 0;
                    sscanf(slotValue.str(), "%d", &playerPort);
                    GameSlotConnectInfo connectInfo;
                    connectInfo.m_ip = playerIP;
                    connectInfo.m_port = (unsigned short)playerPort;
                    newSlot[i].setState(SLOT_PLAYER, name, &connectInfo);

                    // Read if it's accepted or not
                    slotValue = strtok_r(NULL, ",", &slotPos);
                    if (slotValue.getLength() != 2) {
                        optionsOk = false;
                        break;
                    }
                    const char *svs = slotValue.str();
                    if (*svs == 'T') {
                        newSlot[i].setAccept();
                    } else if (*svs == 'F') {
                        newSlot[i].unAccept();
                    }
                    ++svs;
                    if (*svs == 'T') {
                        newSlot[i].setMapAvailability(TRUE);
                    } else {
                        newSlot[i].setMapAvailability(FALSE);
                    }

                    // Read color index
                    slotValue = strtok_r(NULL, ",", &slotPos);
                    if (slotValue.StringBase<char>::isEmpty()) {
                        optionsOk = false;
                        break;
                    }
                    Int color = atoi(slotValue.str());
                    if (color < -1 || color >= TheMultiplayerSettings->getNumColors()) {
                        optionsOk = false;
                        break;
                    }
                    newSlot[i].setColor(color);

                    // Read playerTemplate index
                    slotValue = strtok_r(NULL, ",", &slotPos);
                    if (slotValue.StringBase<char>::isEmpty()) {
                        optionsOk = false;
                        break;
                    }
                    Int playerTemplate = atoi(slotValue.str());
                    if (playerTemplate < PLAYERTEMPLATE_MIN ||
                        playerTemplate >= ThePlayerTemplateStore->getPlayerTemplateCount()) {
                        optionsOk = false;
                        break;
                    }
                    newSlot[i].setPlayerTemplate(playerTemplate);

                    // Read start position index
                    slotValue = strtok_r(NULL, ",", &slotPos);
                    if (slotValue.StringBase<char>::isEmpty()) {
                        optionsOk = false;
                        break;
                    }
                    Int startPos = atoi(slotValue.str());
                    if (startPos < -1 || startPos >= MAX_SLOTS) {
                        optionsOk = false;
                        break;
                    }
                    newSlot[i].setStartPos(startPos);

                    // Read team index
                    slotValue = strtok_r(NULL, ",", &slotPos);
                    if (slotValue.StringBase<char>::isEmpty()) {
                        optionsOk = false;
                        break;
                    }
                    Int team = atoi(slotValue.str());
                    if (team < -1 || team >= MAX_SLOTS / 2) {
                        optionsOk = false;
                        break;
                    }
                    newSlot[i].setTeamNumber(team);

                    // Read the NAT behavior
                    slotValue = strtok_r(NULL, ",", &slotPos);
                    if (slotValue.StringBase<char>::isEmpty()) {
                        optionsOk = false;
                        break;
                    }
                    int NATType = atoi(slotValue.str());
                    if ((NATType < 0) || (NATType > 128)) {
                        optionsOk = false;
                        break;
                    }
                    newSlot[i].setNATBehavior(NATType);
                } // case 'H':
                break;
                case 'C': {
                    char *slotPos = NULL;
                    // Parse out the Name
                    AsciiString slotValue(strtok_r((char *)rawSlot.str(), ",", &slotPos));
                    if (slotValue.StringBase<char>::isEmpty()) {
                        optionsOk = false;
                        break;
                    }

                    switch (*(slotValue.str() + 1)) {
                    case 'E': {
                        GameSlotConnectInfo info;
                        newSlot[i].setState(SLOT_EASY_AI, Rva01336E54EmptyUnicode, &info);
                    } break;
                    case 'M': {
                        GameSlotConnectInfo info;
                        newSlot[i].setState(SLOT_MED_AI, Rva01336E54EmptyUnicode, &info);
                    } break;
                    case 'H': {
                        GameSlotConnectInfo info;
                        newSlot[i].setState(SLOT_BRUTAL_AI, Rva01336E54EmptyUnicode, &info);
                    } break;
                    default: {
                        optionsOk = false;
                    } break;
                    } // switch(*rawSlot.str()+1)

                    // Read color index
                    slotValue = strtok_r(NULL, ",", &slotPos);
                    if (slotValue.StringBase<char>::isEmpty()) {
                        optionsOk = false;
                        break;
                    }
                    Int color = atoi(slotValue.str());
                    if (color < -1 || color >= TheMultiplayerSettings->getNumColors()) {
                        optionsOk = false;
                        break;
                    }
                    newSlot[i].setColor(color);

                    // Read playerTemplate index
                    slotValue = strtok_r(NULL, ",", &slotPos);
                    if (slotValue.StringBase<char>::isEmpty()) {
                        optionsOk = false;
                        break;
                    }
                    Int playerTemplate = atoi(slotValue.str());
                    if (playerTemplate < PLAYERTEMPLATE_MIN ||
                        playerTemplate >= ThePlayerTemplateStore->getPlayerTemplateCount()) {
                        optionsOk = false;
                        break;
                    }
                    newSlot[i].setPlayerTemplate(playerTemplate);

                    // Read start pos
                    slotValue = strtok_r(NULL, ",", &slotPos);
                    if (slotValue.StringBase<char>::isEmpty()) {
                        optionsOk = false;
                        break;
                    }
                    Int startPos = atoi(slotValue.str());
                    Bool isStartPosBad = FALSE;
                    if (startPos < -1 || startPos >= MAX_SLOTS) {
                        isStartPosBad = TRUE;
                    }
                    // Retail checks slot i on every iteration, preserving the original behavior.
                    for (Int j = 0; j < i; ++j) {
                        if (startPos >= 0 && startPos == newSlot[i].getStartPos()) {
                            isStartPosBad =
                                TRUE;
                        }
                    }
                    if (isStartPosBad) {
                        optionsOk = false;
                        break;
                    }
                    newSlot[i].setStartPos(startPos);

                    // Read team index
                    slotValue = strtok_r(NULL, ",", &slotPos);
                    if (slotValue.StringBase<char>::isEmpty()) {
                        optionsOk = false;
                        break;
                    }
                    Int team = atoi(slotValue.str());
                    if (team < -1 || team >= MAX_SLOTS / 2) {
                        optionsOk = false;
                        break;
                    }
                    newSlot[i].setTeamNumber(team);

                } // case 'C':
                break;
                case 'O': {
                    GameSlotConnectInfo info;
                    newSlot[i].setState(SLOT_OPEN, Rva01336E54EmptyUnicode, &info);
                } // case 'O':
                break;
                case 'X': {
                    GameSlotConnectInfo info;
                    newSlot[i].setState(SLOT_CLOSED, Rva01336E54EmptyUnicode, &info);
                } // case 'X':
                break;
                default: {
                    optionsOk = false;
                } break;
                }
            }
            if (freeMe)
                free(freeMe);
        } else {
            optionsOk = false;
            break;
        }
    }
    if (buf)
        free(buf);

    if (optionsOk && sawMap && sawMapCRC && sawMapSize && sawSeed && sawSlotlist) {
        // We were setting the Global Data directly here, but Instead, I'm now
        // first setting the data in game.  We'll set the global data when
        // we start a game.
        if (!game)
            return true;

        for (Int i = 0; i < MAX_SLOTS; i++)
            game->setSlot(i, newSlot[i]);

        game->setMap(mapName);
        game->setMapCRC(mapCRC);
        game->setMapSize(mapSize);
        game->setMapContentsMask(mapContentsMask);
        game->setSeed(seed);

        return true;
    }

    return false;
}
