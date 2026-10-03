// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/gameinfo /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
class INI;
#include "GameNetwork/GameInfo.h"
// Matched dispatch00529EC0 names MpGameSetup::rva00525D10.
// Retail368B through RET4 at00525E7D; one scoped four-byte adapter.
// See identity_evidence/00525d10-selection.md.
class GameInfo;
class GameSlot;
class GameWindow;
class MultiplayerSettings;
extern MultiplayerSettings *TheMultiplayerSettings;
class Gen_004b5a60 { public: void *m(void *); };
class Gen_004b5a70 { public: void m(); };
class BfmeC1040 { public: int bfmeGo1040C(); };
class BfmeThingCCH { public: int bfmeGoCCH(void *); };
class Rva00525D10Owner {
public:
    virtual void slot0()=0;
    virtual void slot1()=0;
    virtual void slot2()=0;
    virtual bool slot3(GameSlot *, int)=0;
    virtual void slot4()=0;
    virtual void slot5()=0;
    virtual void slot6()=0;
    virtual void slot7()=0;
    virtual void slot8()=0;
    virtual bool slot9(GameInfo *)=0;
};
struct Rva00525D10Adapter {
    GameWindow *window;
    Rva00525D10Adapter(GameWindow *const &w) { ((Gen_004b5a60 *)this)->m((void *)&w); }
    ~Rva00525D10Adapter() { ((Gen_004b5a70 *)this)->m(); }
    int selected() { return ((BfmeC1040 *)this)->bfmeGo1040C(); }
    int data(int row) { return ((BfmeThingCCH *)this)->bfmeGoCCH((void *)row); }
};
struct Rva00525D10Settings {
    char unknown00[0x34];
    int count34;
    int unknown38;
    int count3c;
    int count() { if(count3c==0) count3c=count34; return count3c; }
};
class MpGameSetup {
public:
    bool rva00525D10(int);
    char unknown00[4];
    Rva00525D10Owner *owner;
    GameInfo *first;
    GameInfo *second;
    char unknown10[7];
    bool pending;
    char unknown18[0x70];
    GameWindow *windows[8];
};
bool MpGameSetup::rva00525D10(int index)
{
    if (first && !owner->slot9(first)) first=0;
    if (second && !owner->slot9(second)) second=0;
    if (!first) return false;
    pending=false;
    Rva00525D10Adapter combo(windows[index]);
    int value=combo.data(combo.selected());
    if(value < -1) return false;
    GameSlot *slot=first->getSlot(index);
    if (!slot) return false;
    if (value == *(int *)((char *)slot+0xc)) return false;
    if (value >= ((Rva00525D10Settings *)TheMultiplayerSettings)->count()) return false;
    if (value != -1) {
        for (int i=0;i<8;++i) {
            GameSlot *other=first->getSlot(i);
            if(other && value == *(int *)((char *)other+0xc) && slot != other) return false;
        }
    }
    return owner->slot3(slot,value);
}
