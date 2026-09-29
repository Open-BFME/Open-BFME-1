// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Igame/Libraries/Source/WWVegas/WWLib
// BFME VictoryConditions update at 0035F920. Identity: concrete vtable
// 010E8D90 slot 5; matched sibling family and ZH VictoryConditions update.
// BFME dispatches living-world defeat messages and end-game UI, checks
// 32 cached players, and stamps AI lobby slots before killPlayer.
// Layout follows the matched victory_conditions.cpp family and this body's
// explicit offsets; unwitnessed BFME-only fields keep address-derived names.
// areAllies stays visible here for MSVC's private EAX/ESI calling convention.
// Its independently probed 53-byte emission matches retail 0035F150.
#include <wchar.h>
#include "ascii_string.h"
extern const AsciiString Rva01336E50EmptyString;
#include "Common/UnicodeString.h"
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }
enum Relationship { ALLIES = 2 };
enum NameKeyType { NAMEKEY_INVALID = 0 };
enum EvaMessage {};
struct Coord3D;
class Team;
class Player {
  public:
    char pad_00[0x20];
    NameKeyType m_playerNameKey;
    int m_playerIndex;
    char pad_28[0x208];
    Team *m_defaultTeam;
    char pad_234[0x250];
    unsigned m_484;
    Team *getDefaultTeam() const { return m_defaultTeam; }
    Relationship getRelationship(const Team *) const;
    bool isLocalPlayer() const;
    UnicodeString getPlayerDisplayName();
    void killPlayer();
};
class Rva00267FA0 {
  public:
    bool get();
};
inline static bool areAllies(const Player *p1, const Player *p2) {
    if (p1 != p2 && p1->getRelationship(p2->getDefaultTeam()) == ALLIES &&
        p2->getRelationship(p1->getDefaultTeam()) == ALLIES)
        return true;
    return false;
}
class GameLogic {
  public:
    char pad_00[0x3c];
    unsigned m_frame;
    char pad_40[0x50];
    bool m_90;
    char pad_91[0x7b];
    int m_gameMode;
    bool _bfme_isInLivingWorldCampaign();
    bool isInSinglePlayerGame();
};
extern GameLogic *TheGameLogic;
class BfmeThingFGC {
  public:
    void bfmeGoFGC(int);
};
struct Rva006C9270GlobalData {
    char pad_00[0x11f8];
    float m_11f8;
};
extern Rva006C9270GlobalData *TheWritableGlobalData;
class RecorderClass {
  public:
    bool isMultiplayer();
};
extern RecorderClass *TheRecorder;
class PartitionManager {
  public:
    void revealMapForPlayerPermanently(int);
};
extern PartitionManager *TheShroudManager;
class InGameUI {
  public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void __cdecl message(AsciiString, ...);
    virtual void slot13();
    virtual void slot14();
    virtual void __cdecl message_3c(AsciiString, ...);
};
extern InGameUI *TheInGameUI;
class Eva {
  public:
    bool setShouldPlay(EvaMessage, const Coord3D *);
};
extern Eva *TheEva;
class PlayerList {
  public:
    char pad_00[12];
    Player *m_local;
};
extern PlayerList *ThePlayerList;
class WindowManager;
extern WindowManager *g_theWindowManager;
class GameSlot {
  public:
    char pad_00[0x2c];
    AsciiString m_playerName;
    char pad_30[12];
    unsigned m_3c;
    bool isAI() const;
};
class GameInfo {
  public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual bool unidentifiedSlot12();
    GameSlot *getSlot(int);
};
extern GameInfo *TheGameInfo;
class NameKeyGenerator {
  public:
    NameKeyType nameToKey(const char *);
};
extern NameKeyGenerator *TheNameKeyGenerator;
class VictoryConditions {
  public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void update();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual bool hasSinglePlayerBeenDefeated(Player *);
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void showEndGame(const AsciiString &, bool, const AsciiString &, const AsciiString &);
    virtual void slot19();
    virtual void slot20();
    virtual void updateEndGame();
    char pad_04[8];
    bool m_endGameShowing;
    unsigned m_endGameShowTime;
    Player *m_players[32];
    int m_localSlotNum;
    unsigned m_endFrame;
    bool m_isDefeated[32];
    bool m_localPlayerDefeated;
    bool m_singleAllianceRemaining;
    bool m_isObserver;
    int m_defeatCount;
};
void VictoryConditions::update() {
    unsigned frame = TheGameLogic->m_frame;
    updateEndGame();
    unsigned delay = (int)(TheWritableGlobalData ? TheWritableGlobalData->m_11f8 * 5.0f : 25.0f);
    if (!TheRecorder->isMultiplayer())
        return;
    if (m_localSlotNum == -1 && !m_isObserver && TheGameLogic->m_gameMode != 6)
        return;
    if (frame < delay)
        return;
    if (!m_singleAllianceRemaining) {
        Player *first = 0;
        bool onlyOneAlliance = true;
        int i;
        for (i = 0; i < 32; i++) {
            Player *p = m_players[i];
            if (p && !hasSinglePlayerBeenDefeated(p)) {
                if (first) {
                    if (!areAllies(first, p)) {
                        onlyOneAlliance = false;
                        break;
                    }
                } else
                    first = p;
            }
        }
        if (onlyOneAlliance) {
            m_singleAllianceRemaining = true;
            m_endFrame = frame;
            if (!TheGameInfo->unidentifiedSlot12())
                TheGameLogic->m_90 = false;
        }
    }
    for (int i = 0; i < 32; i++) {
        Player *p = m_players[i];
        if (p && !m_isDefeated[i] && hasSinglePlayerBeenDefeated(p)) {
            m_isDefeated[i] = true;
            ((BfmeThingFGC *)TheGameLogic)->bfmeGoFGC(i);
            p->m_484 = frame;
            if (frame > 1) {
                int playerIndex = p->m_playerIndex;
                TheShroudManager->revealMapForPlayerPermanently(playerIndex);
                if (TheGameLogic->_bfme_isInLivingWorldCampaign() && p->isLocalPlayer())
                    TheInGameUI->message("GUI:YouHaveBeenDefeated");
                else if (!TheGameLogic->isInSinglePlayerGame() && TheGameLogic->m_gameMode != 6)
                    TheInGameUI->message_3c("GUI:PlayerHasBeenDefeated",
                                            p->getPlayerDisplayName().str());
                int mode = TheGameLogic->m_gameMode;
                if ((mode == 1 || mode == 5 || mode == 2 || mode == 6) && ThePlayerList && TheEva &&
                    p->getDefaultTeam()) {
                    Player *local = ThePlayerList->m_local;
                    if (local->getRelationship(p->getDefaultTeam()) == ALLIES) {
                        if (local != p)
                            TheEva->setShouldPlay((EvaMessage)9, 0);
                        else if (g_theWindowManager) {
                            Player *local2 = ThePlayerList->m_local;
                            if (local2) {
                                AsciiString gui("Gui_DefeatScreen");
                                AsciiString apt("APT:EndDefeat");
                                showEndGame(apt, ((Rva00267FA0 *)local2)->get(), gui,
                                            Rva01336E50EmptyString);
                            }
                        }
                    }
                }
            }
            for (int j = 0; j < 8; j++) {
                AsciiString name;
                NameKeyType key = p->m_playerNameKey;
                if (key == TheNameKeyGenerator->nameToKey("") && TheGameInfo) {
                    GameSlot *slot = TheGameInfo->getSlot(j);
                    if (slot && slot->isAI()) {
                        name = slot->m_playerName;
                        slot->m_3c = frame;
                    }
                }
            }
            p->killPlayer();
        }
    }
}
