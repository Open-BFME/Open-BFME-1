// cl: /DNDEBUG /MD /EHsc
// stlport
// Complete body at RVA 0x005A67E0, reached through ILT 0x0003E621.
// The old 312-byte dump cuts the push at 0x005A6917. The final ret4 is
// 0x005A6ADA; the six-entry jump table and 178-byte case-index table end
// at 0x005A6BAA, before 246 int3 bytes. No semantic owner name is asserted.
// The native STLport find specialization at 0x0058B1F0 is independently
// exact over 105 bytes and takes the real random_access_iterator_tag ABI.
#include <algorithm>
class GameMessage { public: char pad00[0x10]; int type; };
class LookAtTranslator { public: void fillFromMessage(const GameMessage *); };
extern int classifyRva005A6410Value(int);
extern void bfmeGo1017Y(int,int,int);
class BfmeC977 { public: char bfmeGo977C(); };
class WindowManager;
extern WindowManager *Rva00579160TheManager;
struct ManagerView { char pad00[0x1b4]; int mode; };
struct MouseStatus { char pad00[0x18]; int left; char pad1c[8]; int right; char pad28[8]; int middle; };
class Mouse {
public:
    typedef void (Mouse::*SetCursor)(int);
    struct Vtable { void *pad00[14]; SetCursor setCursor; }; Vtable *vtable;
    char pad04[0x4d0c]; MouseStatus status;
    void setCursor(int mode) { (this->*(vtable->setCursor))(mode); }
};
extern Mouse *TheMouse;
enum GameWindowMessage { GWM_NONE };
extern GameWindowMessage rawMouseToWindowMessage(const GameMessage *);
class GameWindow { public: unsigned winGetStatus(); GameWindow *winGetParent(); };
class GameWindowManager { public: char pad00[0x14]; GameWindow *head; };
extern GameWindowManager *TheWindowManager;
class Rva005A67E0Owner {
    void *vtable; char buttons[4]; char events[0x1e0];
    bool flag1e8; int mode; int countLeft; int countRight;
public: int translate(const GameMessage *msg);
};
int Rva005A67E0Owner::translate(const GameMessage *msg)
{
    int disp=0;
    if(flag1e8) { flag1e8=false; return 0; }
    int type=msg->type;
    char *button=&buttons[classifyRva005A6410Value(type)];
    char active=1;
    bool any=std::find(buttons,buttons+4,active)!=buttons+4;
    const MouseStatus *status;
    active=!any && (status=&TheMouse->status) && (status->left || status->right || status->middle);
    switch(type) {
    case 180: flag1e8=true; disp=1; break;
    case 3:
        if(any || (((BfmeC977*)Rva00579160TheManager)->bfmeGo977C() && !active)) {
            TheMouse->setCursor(mode); disp=1;
        }
        if(buttons[0] && !TheMouse->status.left) {
            if(++countLeft>5) {
                ((ManagerView*)Rva00579160TheManager)->mode=0;
                bfmeGo1017Y(0,1,1); buttons[0]=0; countLeft=0;
            }
        } else countLeft=0;
        if(buttons[2] && !TheMouse->status.right) {
            if(++countRight>5) {
                ((ManagerView*)Rva00579160TheManager)->mode=2;
                bfmeGo1017Y(0,1,1); buttons[2]=0; countRight=0;
            }
        } else countRight=0;

        break;
    case 4: case 5: case 14: case 15:
        if(type==4 || type==5) ((ManagerView*)Rva00579160TheManager)->mode=0;
        else ((ManagerView*)Rva00579160TheManager)->mode=2;
        if(((BfmeC977*)Rva00579160TheManager)->bfmeGo977C()) {
            ((LookAtTranslator*)this)->fillFromMessage(msg);
            bfmeGo1017Y(0,0,1); *button=1; disp=1; break;
        }
        break;
    case 6: case 16:
        if(*button) {
            ((LookAtTranslator*)this)->fillFromMessage(msg);
            ((ManagerView*)Rva00579160TheManager)->mode=type==6?0:2;
            bfmeGo1017Y(0,1,1); *button=0; disp=1; break;
        }
        break;
    case 8: case 18:
        if(*button) { disp=1; break; }
        break;
    }
    if(disp==0) {
        if(active) return 0;
        if(rawMouseToWindowMessage(msg)==GWM_NONE) return 0;
        for(GameWindow *w=TheWindowManager->head;w;w=w->winGetParent()) {
            if(w->winGetStatus()&0x08000000) { disp=1; break; }
        }
    }
    return disp;
}
