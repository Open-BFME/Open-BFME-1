// ?populateCommand@ControlBar@@IAEXPAVObject@@_N@Z
// partial score=0.443881245474294 date=2026-09-24
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /I. /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
// ControlBar::populateCommand, RVA 004A5E30, 1381 bytes through ret8 at 004A6392.
// Identity: matched ControlBar::switchToContext at 0049E780, command arm
// 0049E93E calls ILT 0000D495 with Object* and Bool (caller source line 2332).
// Raw contracts from tools/callees.py; offsets witnessed in astra_R/LAYOUTS.md.
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "Code/Libraries/Source/WWVegas/WWLib/ascii_string.h"
inline AsciiString::~AsciiString(){((StringBase<char>*)this)->releaseBuffer();}
template<class T> inline void StringBase<T>::clear(){releaseBuffer();}

#include "Common/GameMemory.h"
#include "Common/Overridable.h"
class CommandButton; class CommandSet; class Player; class Image;
enum ScienceType { SCIENCE_INVALID=-1 };

class Object { public: Player *getControllingPlayer() const; const AsciiString &getCommandSetString() const; };
class Player { public: Bool hasScience(ScienceType) const; };
class GameWindow { public: void bfmeClose(Bool); unsigned winSetStatus(unsigned); unsigned winClearStatus(unsigned); };
class BfmeUnit1013 { public: void bfmeStop1013(char); };
class CommandSet { public: const CommandButton *getCommandButton(int) const; };
class BFMERetailCommandButton { public: void setButtonImage(const Image*); };
class Rva004A5E30Calls {};
extern void j_00001947();
extern void j_00002135();
extern void j_00003a85();
extern void j_00003f80();
extern void j_000056cd();
extern void j_00006938();
extern void j_0000943f();
extern void j_0000d436();
extern void j_00015da7();
extern void j_000179bd();
extern void j_0001a73f();
extern void j_0001f0d7();
extern void j_0001ff91();
extern void j_00020824();
extern void j_00023d4e();
extern void j_00027b24();
extern void j_00027f2a();
extern void j_00029dc0();
extern void j_0002a7ed();
extern void j_0002bf85();
extern void j_0002d1af();
extern void j_00033523();
extern void j_0003367c();
extern void j_00033f19();
extern void j_00034b58();
extern void j_0003672d();
extern void j_00046c18();
extern void j_00046f4c();
extern void j_00048c61();
extern void j_00048cca();
extern void j_0004a1fb();
extern void j_0004a66f();
template<class R> static __forceinline R rvaCall0(const void *owner,void (*raw)()) {
    typedef R (Rva004A5E30Calls::*Method)();
    union { void (*raw)(); Method member; } route;
    route.raw=raw;
    return (reinterpret_cast<Rva004A5E30Calls*>(const_cast<void*>(owner))->*route.member)();
}
template<class R, class A0> static __forceinline R rvaCall1(const void *owner,void (*raw)(), A0 a0) {
    typedef R (Rva004A5E30Calls::*Method)(A0);
    union { void (*raw)(); Method member; } route;
    route.raw=raw;
    return (reinterpret_cast<Rva004A5E30Calls*>(const_cast<void*>(owner))->*route.member)(a0);
}
template<class R, class A0, class A1> static __forceinline R rvaCall2(const void *owner,void (*raw)(), A0 a0, A1 a1) {
    typedef R (Rva004A5E30Calls::*Method)(A0, A1);
    union { void (*raw)(); Method member; } route;
    route.raw=raw;
    return (reinterpret_cast<Rva004A5E30Calls*>(const_cast<void*>(owner))->*route.member)(a0, a1);
}
template<class R, class A0, class A1, class A2> static __forceinline R rvaCall3(const void *owner,void (*raw)(), A0 a0, A1 a1, A2 a2) {
    typedef R (Rva004A5E30Calls::*Method)(A0, A1, A2);
    union { void (*raw)(); Method member; } route;
    route.raw=raw;
    return (reinterpret_cast<Rva004A5E30Calls*>(const_cast<void*>(owner))->*route.member)(a0, a1, a2);
}

class Rva004A5E30Contain {
public:
    virtual void *slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot0a();
    virtual void slot0b();
    virtual void slot0c();
    virtual void slot0d();
    virtual void slot0e();
    virtual void slot0f();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot1a();
    virtual void slot1b();
    virtual void slot1c();
    virtual void slot1d();
    virtual void slot1e();
    virtual void slot1f();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot2a();
    virtual void slot2b();
    virtual void slot2c();
    virtual Bool slot2d();
};
class Rva004A5E30Exit {
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void *slot08();
};
struct Rva004A5E30ObjectView { char pad00[0x1fc]; Rva004A5E30Contain *field1fc; };
struct Rva004A5E30PlayerList { char pad00[0xc]; Player *field0c; };
extern Rva004A5E30PlayerList *Rva012ED748;
extern void *Rva012F4B98;
class ControlBar;
extern ControlBar *Rva012F33F8;

struct Rva004A5E30Override : public Overridable {
    char pad0c[0x10]; int field1c;
    int requiredView() const { return ((const Rva004A5E30Override*)friend_getFinalOverride())->field1c; }
};

struct Rva004A5E30ButtonView {
    char pad00[0x10]; int field10; CommandButton *field14; unsigned field18;
    char pad1c[0x18]; Rva004A5E30Override *field34;
    char pad38[0x30]; AsciiString field68;
    char pad6c[0x18]; std::vector<int> field84;
    char pad90[0x10]; int fielda0;
    char pada4[0xa9]; unsigned char field14d;
    char pad14e[4]; unsigned char field152; unsigned char field153;
};
class ControlBar {
public:
    const CommandSet *findCommandSet(const AsciiString&);
    void setControlCommand(GameWindow*,const CommandButton*);
protected:
    void resetContainData();
    void doTransportInventoryUI(Object*,const CommandSet*);
    void showRallyPoint(const Coord3D*);
    void populateCommand(Object *object,Bool refresh);
    char pad00[0x28]; CommandButton *field28;
    char pad2c[0xd4]; GameWindow *field100[20];
    char pad150[0x50]; GameWindow *field1a0[20];
    char pad1f0[0x100]; void *field2f0;
};

void ControlBar::populateCommand(Object *object,Bool refresh)
{
    Player *player=object->getControllingPlayer();
    resetContainData();
    const CommandSet *commandSet=Rva012F33F8->findCommandSet(object->getCommandSetString());
    void *overrideData=rvaCall0<void*>(object,j_0002bf85);
    if(overrideData) commandSet=Rva012F33F8->findCommandSet(*(AsciiString*)((char*)overrideData+0x2c));
    if(!commandSet) {
        if(Rva012F4B98) rvaCall0<void>(Rva012F4B98,j_0003367c);
        return;
    }
    int i;
    for(i=0;i<20;++i) {
        if(field100[i]) {
            const CommandButton *button=commandSet->getCommandButton(i);
            if(!button) field100[i]->bfmeClose(true);
            else rvaCall2<void>(button,j_00006938,object,false);
            setControlCommand(field100[i],button);
        }
    }
    Rva004A5E30Contain *contain=((Rva004A5E30ObjectView*)object)->field1fc;
    if(contain && contain->slot2d()) doTransportInventoryUI(object,commandSet);
    int specialIndex[2];
    specialIndex[1] = 0;
    for(i=0;i<20;++i) {
        const CommandButton *button=commandSet->getCommandButton(i);
        Rva004A5E30ButtonView *b=(Rva004A5E30ButtonView*)button;
        if(!b || !b->field152) continue;
        if(b->field18&0x80000) {
            if(field100[i]) field100[i]->bfmeClose(true);
            continue;
        }
        if(contain && b->field153) {
            void *data=contain->slot00();
            if(data && !*((unsigned char*)data+0xb6)) continue;
        }
        if(b->field10==0x2c) {
            if(!rvaCall1<Bool>(Rva012ED748,j_00003a85,object)) {
                field100[i]->bfmeClose(true);
                continue;
            }
            void *image=rvaCall1<void*>((char*)player+0x684,j_0004a66f,specialIndex[1]);
            void *item=rvaCall1<void*>((char*)player+0x684,j_00002135,specialIndex[1]);
            if(image && item) {
                ((BFMERetailCommandButton*)button)->setButtonImage((const Image*)image);
                AsciiString text;
                if(rvaCall1<Bool>(item,j_00046c18,&text)) b->field68=text;
                if(field100[i]) setControlCommand(field100[i],button);
                b->field68.clear();
                b->fielda0=specialIndex[1];
            } else b->fielda0=-1;
            ++specialIndex[1];
        }
        if(b->field10==0xf) continue;
        if(field100[i]) {
            field100[i]->bfmeClose(false);
            ((BfmeUnit1013*)field100[i])->bfmeStop1013(1);
            if(b->field14d) field100[i]->winSetStatus(0x4000000U);
            else field100[i]->winClearStatus(0x4000000U);
        }
        if((b->field18&0x80) && b->field34) {
            Rva004A5E30Override *power=b->field34;
            if(power->requiredView()!=-1) {
                if(!player->hasScience((ScienceType)power->requiredView())) {
                    if(field100[i]) field100[i]->bfmeClose(true);
                    goto rvaCommandNext;
                } else {
                    int bestIndex=-1;
                    for(unsigned scienceIndex=0;scienceIndex<b->field84.size();++scienceIndex) {
                        int science=b->field84[scienceIndex];
                        if(player->hasScience((ScienceType)science)) bestIndex=scienceIndex;
                        else break;
                    }
                    if(bestIndex!=-1) {
                        int science=b->field84[bestIndex];
                        for(CommandButton *candidate=field28;candidate;candidate=((Rva004A5E30ButtonView*)candidate)->field14) {
                            Rva004A5E30ButtonView *c=(Rva004A5E30ButtonView*)candidate;
                            if(c->field10==0x18 && !c->field84.empty() && c->field84[0]==science)
                                rvaCall2<void>(button,j_00001947,candidate,true);
                        }
                    }
                }
            }
        }
        rvaCommandNext:;
    }
    if(rvaCall0<Bool>(object,j_0001ff91) || !rvaCall0<Bool>(Rva012ED748->field0c,j_000179bd)) {
        Rva004A5E30Exit *exit=rvaCall0<Rva004A5E30Exit*>(object,j_00023d4e);
        if(exit) showRallyPoint((const Coord3D*)exit->slot08());
    }
    rvaCall0<void>(this,j_0003672d);
    rvaCall1<void>(Rva012F4B98,j_0001f0d7,object);
    if(field2f0) {
        if(!rvaCall0<Bool>(object,j_0001ff91) && rvaCall0<Bool>(Rva012ED748->field0c,j_000179bd)) {
            rvaCall0<void>(field2f0,j_00033f19);
            return;
        }
        std::vector<GameWindow*> windows;
        rvaCall1<void>(&windows,j_00046f4c,20U);
        for(int k=0;k<20;++k) {
            GameWindow *window=field1a0[k];
            if(window) windows.push_back(window);
        }
        rvaCall1<void>(field2f0,j_00034b58,&windows);
    }
}
