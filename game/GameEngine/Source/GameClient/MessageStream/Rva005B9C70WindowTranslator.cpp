// cl: /DNDEBUG /MD /EHs-c-
// Complete RVA 0x005B9C70 body including its switch tables.
// Start: ILT 0x00002428 and int3 padding. Final ret4: 0x005B9FCA.
// Tables at 0x005B9FD0/0x005B9FE8 end at 0x005B9FFC.
// This BFME translator adds input phases and Palantir/pause guards to the
// WindowXlat reference algorithm. Local views preserve witnessed ABI slots.
struct ICoord2D { int x,y; };
union GameMessageArgumentType { int integer; ICoord2D pixel; };
class GameMessage { public: const GameMessageArgumentType *getArgument(int) const; char pad00[0x10]; int type; };
enum GameWindowMessage { GWM_NONE };
extern GameWindowMessage rawMouseToWindowMessage(const GameMessage *);
class BfmeGameLogicPause { public: bool isGamePaused(); };
class GameLogic;
extern GameLogic *TheGameLogic;
static inline BfmeGameLogicPause *pauseView005B9C70() { return (BfmeGameLogicPause *)TheGameLogic; }
class PalantirUIState { public: char pad00[8]; bool flag08; };
extern PalantirUIState *g_aptPalantirUIState;
extern char g_bfmeDoneSJA;
extern bool bfmeIsSet();
class Shell { public: char pad00[0x58]; bool active; };
extern Shell *TheShell;
class GameWindowManager {
public:
    typedef int (GameWindowManager::*MouseEvent)(GameWindowMessage,const ICoord2D *,const void *);
    typedef int (GameWindowManager::*KeyEvent)(unsigned char,unsigned char);
    struct Vtable { void *pad00[41]; MouseEvent mouse; KeyEvent key; };
    Vtable *vtable;
    char pad04[0x34]; int phase;
    int mouse(GameWindowMessage m,const ICoord2D *p,const void *d) { return (this->*(vtable->mouse))(m,p,d); }
    int key(unsigned char k,unsigned char s) { return (this->*(vtable->key))(k,s); }
};
extern GameWindowManager *TheWindowManager;
class View {
public:
    typedef bool (View::*Locked)();
    struct Vtable { void *pad[105]; Locked locked; }; Vtable *vtable;
    bool isMouseLocked() { return (this->*(vtable->locked))(); }
};
extern View *TheTacticalView;
class InGameUI {
public:
    bool getInputEnabled() const;
    typedef bool (InGameUI::*Anchored)();
    struct Vtable { void *pad[53]; Anchored anchored; }; Vtable *vtable;
    bool isPlacementAnchored() { return (this->*(vtable->anchored))(); }
};
extern InGameUI *TheInGameUI;
class Display {
public:
    typedef void (Display::*Stop)(); typedef bool (Display::*Playing)();
    struct Vtable { void *pad[59]; Stop stop; Playing playing; }; Vtable *vtable;
    bool isMoviePlaying() { return (this->*(vtable->playing))(); }
    void stopMovie() { (this->*(vtable->stop))(); }
};
extern Display *TheDisplay;
class GlobalData { public: char pad[3000]; bool flagBB8; };
extern GlobalData *TheGlobalData;
struct Rva00465D50Point { int x,y; };
class Rva00465D50Owner { public: void apply(Rva00465D50Point *); };
class WindowManager;
extern WindowManager *Rva00579160TheManager;
class Rva005B9C70Owner {
    void *vtable; int phase;
public: int translate(const GameMessage *msg);
};
int Rva005B9C70Owner::translate(const GameMessage *msg)
{
    TheWindowManager->phase = phase;
    int disp = 0;
    bool forceKeepMessage = false;
    int returnCode = 0;
    GameWindowMessage firstMessage = rawMouseToWindowMessage(msg);
    if (phase == 1) {
        if (g_aptPalantirUIState && g_aptPalantirUIState->flag08 && !pauseView005B9C70()->isGamePaused()) {
            if (!TheShell || !TheShell->active) return 0;
        }
    } else {
        if (firstMessage != GWM_NONE) {
            ICoord2D pos = msg->getArgument(0)->pixel;
            ((Rva00465D50Owner *)Rva00579160TheManager)->apply((Rva00465D50Point *)&pos);
        }
        if (g_bfmeDoneSJA || bfmeIsSet()) return 0;
    }
    if (TheTacticalView && TheTacticalView->isMouseLocked()) return 0;
    switch (msg->type) {
    case 6:
        if (TheInGameUI && TheInGameUI->isPlacementAnchored()) forceKeepMessage=true;
    case 3: case 4: case 5: case 10: case 11: case 12: case 14: case 15: case 16:
        {
            ICoord2D mousePos=msg->getArgument(0)->pixel;
            if (TheWindowManager) returnCode=TheWindowManager->mouse(firstMessage,&mousePos,0);
            if (phase && !(g_aptPalantirUIState && g_aptPalantirUIState->flag08 && !pauseView005B9C70()->isGamePaused())) {
                if (TheShell && TheShell->active) returnCode=1;
                if (TheInGameUI && !TheInGameUI->getInputEnabled()) returnCode=1;
            }
            break;
        }
    case 8: case 13: case 18:
        {
            ICoord2D mousePos=msg->getArgument(0)->pixel;
            ICoord2D delta=msg->getArgument(1)->pixel;
            GameWindowMessage gwm=rawMouseToWindowMessage(msg);
            if (TheWindowManager) returnCode=TheWindowManager->mouse(gwm,&mousePos,&delta);
            if (phase == 1) {
                if (TheShell && TheShell->active) returnCode=1;
                if (TheInGameUI && !TheInGameUI->getInputEnabled()) returnCode=1;
            }
            break;
        }
    case 19:
        {
            ICoord2D mousePos=msg->getArgument(0)->pixel;
            int wheelPos=msg->getArgument(1)->integer;
            GameWindowMessage gwm=rawMouseToWindowMessage(msg);
            if (TheWindowManager) returnCode=TheWindowManager->mouse(gwm,&mousePos,&wheelPos);
            if (phase == 1) {
                if (TheShell && TheShell->active) returnCode=1;
                if (TheInGameUI && !TheInGameUI->getInputEnabled()) returnCode=1;
            }
            break;
        }
    case 21: case 22:
        {
            unsigned char key=msg->getArgument(0)->integer;
            unsigned char state=msg->getArgument(1)->integer;
            if (TheWindowManager) returnCode=TheWindowManager->key(key,state);
            if (phase == 1) {
                if (returnCode != 1 && key == 1 && (state&1) && TheDisplay->isMoviePlaying() && TheGlobalData->flagBB8 == true) {
                    TheDisplay->stopMovie();returnCode=1;
                }
                if (returnCode != 1 && key == 1 && (state&1) && TheInGameUI && !TheInGameUI->getInputEnabled()) returnCode=1;
            }
            break;
        }
    default: break;
    }
    if (returnCode == 1 && !forceKeepMessage) disp=1;
    return disp;
}
