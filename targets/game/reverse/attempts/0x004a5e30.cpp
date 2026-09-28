// ?populateCommand@ControlBar@@IAEXPAVObject@@_N@Z
// partial score=0.557 date=2026-09-28
// ?populateCommand@ControlBar@@IAEXPAVObject@@_N@Z
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /I. /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
//
// ControlBar::populateCommand(Object *, Bool), RVA 004A5E30, 1381 bytes through
// the final ret 8 at 004A6392. Identity: matched ControlBar::switchToContext
// (0049E780) calls ILT 0000D495 with Object* and Bool from its command arm.
//
// Clean-member rewrite of the older rvaCall bank. Callee identities are the
// ledger's (tools/callees.py 0x004A5E30 1381); bodies that are still dumps are
// reached through their ILT j_ symbol with /alternatename and keep an
// address-derived member name. Retail frame map (esp-relative after the four
// pushes; = EBP-0x48+N): +10 loop-2 window cursor, +14 this, +18 specialIndex,
// +1C commandSet, +20 text, +24 player, +28 i, +2C contain, +30 windows.
// Retail holds a zero in EBX for all of loop 2 and the tail (xor ebx,ebx at
// +12F); the cursor is therefore spilled and the frame is 0x2c.
//
// STATE OF THIS BANK (opus-5.5, 2026-09-28): the two stores marked NOT RETAIL
// in loop 2 are placeholders. They are the only structural difference left:
// with them VC7.1 hoists a zero into EBX at the loop-2 preheader exactly as
// retail does, the frame becomes 0x2c, the two hide arms stop tail-merging,
// and probe --shape reports 0.993 with only those two stores and one
// alignment filler (lea ecx,[ecx] vs lea esp,[esp] at +34D) different.
// Without them the body is 1341 B / 861 differing bytes with the cursor in
// EBX. Measured: one extra zero store does not flip EBX, two do (in the same
// or different blocks); pushes of 0 and memory compares against 0 do not
// count; without the text block even three or four stores do not flip.
// The lever still missing is the retail construct that supplies that zero
// weight while emitting nothing. The ZH-style `ScienceType science` variable
// assigned inside the science loop is what fixed the science-load order.
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "../../../../game/Libraries/Source/WWVegas/WWLib/ascii_string.h"
template<class T> inline void StringBase<T>::clear(){releaseBuffer();}
#include "Common/GameMemory.h"
#include "Common/Overridable.h"
class CommandButton; class CommandSet; class Player; class Image; class GameWindow; class ThingTemplate;
enum ScienceType { SCIENCE_INVALID=-1 };
struct Coord3D;

// Object::getContain() witnessed in ControlBarContextUI.cpp (+0x1fc).
// Slot 0 is asOpenContain (the +0xb6 flag is read as in doTransportInventoryUI);
// slot 45 (+0xb4) is the byte-returning test transports use here.
class OpenContain;
class ContainModuleInterface {
public:
    virtual OpenContain *asOpenContain();
    virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s0a(); virtual void s0b(); virtual void s0c(); virtual void s0d(); virtual void s0e(); virtual void s0f();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s1a(); virtual void s1b(); virtual void s1c(); virtual void s1d(); virtual void s1e(); virtual void s1f();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28(); virtual void s29(); virtual void s2a(); virtual void s2b(); virtual void s2c();
    virtual Bool slot45();
};
class ExitInterface {
public:
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual const Coord3D *slot08();
};
// 0x001CAF20 (ILT 0x0002BF85): returns a record whose +0x2c AsciiString names
// the command set that overrides the object's own.
struct Rva001CAF20Record { char pad[0x2c]; AsciiString commandSetName; };
class Object {
public:
    Player *getControllingPlayer() const;
    const AsciiString &getCommandSetString() const;
    Rva001CAF20Record *Rva001CAF20();
    Bool isLocallyControlled() const;
    ExitInterface *getObjectExitInterface() const;
    ContainModuleInterface *getContain() const { return m_contain; }
    char pad00[0x1fc]; ContainModuleInterface *m_contain;
};
#pragma comment(linker, "/alternatename:?Rva001CAF20@Object@@QAEPAURva001CAF20Record@@XZ=?j_0002bf85@@YAXXZ")
// player+0x684: 0x000FA800 (ILT 0x0004A66F) returns the image, 0x000F9670
// (ILT 0x00002135) the ThingTemplate, both keyed by the running special index.
class Rva000F9670Store {
public:
    const Image *Rva000FA800(int index);
    const ThingTemplate *rva000F9670(int index);
};
#pragma comment(linker, "/alternatename:?Rva000FA800@Rva000F9670Store@@QAEPBVImage@@H@Z=?j_0004a66f@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva000F9670@Rva000F9670Store@@QAEPBVThingTemplate@@H@Z=?j_00002135@@YAXXZ")
class Player {
public:
    Bool hasScience(ScienceType) const;
    Bool isPlayerActive() const;
    char pad[0x684]; Rva000F9670Store m_store684;
};
// 0x0013E4D0 (ILT 0x00046C18): copies the template's +0x1c string out when it
// is not empty. Retail's string is the wide one (it calls UnicodeString::set,
// ICF-shared with StringBase<char>::set at 0x00887C90); the narrow shim here
// compiles to the same bytes.
class Rva0013E4D0 { public: Bool take(AsciiString &out); };
#pragma comment(linker, "/alternatename:?take@Rva0013E4D0@@QAE_NAAVAsciiString@@@Z=?j_00046c18@@YAXXZ")
class GameWindow { public: void bfmeClose(Bool); unsigned winSetStatus(unsigned); unsigned winClearStatus(unsigned); int winEnable(Bool); };
class CommandSet { public: const CommandButton *getCommandButton(int) const; };
class PlayerList { public: unsigned char isLocalAlliedWith(Object*); char pad[0xc]; Player *m_localPlayer; };
extern PlayerList *ThePlayerList;
class Glo012F4B98Type { public: void Rva0058C040(); void Rva005976B0(Object*); };
#pragma comment(linker, "/alternatename:?Rva0058C040@Glo012F4B98Type@@QAEXXZ=?j_0003367c@@YAXXZ")
#pragma comment(linker, "/alternatename:?Rva005976B0@Glo012F4B98Type@@QAEXPAVObject@@@Z=?j_0001f0d7@@YAXXZ")
extern Glo012F4B98Type *Glo012F4B98;
class ControlBar;
extern ControlBar *TheControlBar;
class Rva004B19E0Owner { public: void bfmeClear(); void Rva004B19E0(std::vector<GameWindow*>*); };
#pragma comment(linker, "/alternatename:?bfmeClear@Rva004B19E0Owner@@QAEXXZ=?j_00033f19@@YAXXZ")
#pragma comment(linker, "/alternatename:?Rva004B19E0@Rva004B19E0Owner@@QAEXPAV?$vector@PAVGameWindow@@V?$allocator@PAVGameWindow@@@_STL@@@_STL@@@Z=?j_00034b58@@YAXXZ")

struct SpecialPowerTemplate : public Overridable {
    char pad0c[0x10]; int m_requiredScience;
    int getRequiredScience() const { return ((const SpecialPowerTemplate*)friend_getFinalOverride())->m_requiredScience; }
};
class CommandButton {
public:
    void Rva0049BA80(Object*,Bool) const;
    void setButtonImage(const Image*) const;
    void bfmeCopyFrom(const CommandButton*,Bool) const;
    char pad00[0x10]; int m_command;
    CommandButton *m_upgradeTemplate;   // oracle name for +0x14; retail walks the list through it
    unsigned m_options;
    char pad1c[0x18]; SpecialPowerTemplate *m_specialPower;
    char pad38[0x30]; AsciiString field68;
    char pad6c[0x18]; std::vector<int> m_science;
    char pad90[0x8]; int m_zeroPlaceholderA; int m_zeroPlaceholderB; int fielda0;
    char pada4[0xa9]; unsigned char field14d;
    char pad14e[4]; unsigned char field152; unsigned char field153;
};
#pragma comment(linker, "/alternatename:?Rva0049BA80@CommandButton@@QBEXPAVObject@@_N@Z=?j_00006938@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeCopyFrom@CommandButton@@QBEXPBV1@_N@Z=?j_00001947@@YAXXZ")
#pragma comment(linker, "/alternatename:?setButtonImage@CommandButton@@QBEXPBVImage@@@Z=?j_0002a7ed@@YAXXZ")
class ControlBar {
public:
    const CommandSet *findCommandSet(const AsciiString&);
    void setControlCommand(GameWindow*,const CommandButton*);
protected:
    void resetContainData();
    void doTransportInventoryUI(Object*,const CommandSet*);
    void showRallyPoint(const Coord3D*);
    void Rva004A5950();
    void populateCommand(Object *object,Bool refresh);
    char pad00[0x28]; CommandButton *m_commandButtons;
    char pad2c[0xd4]; GameWindow *m_commandWindows[20];
    char pad150[0x50]; GameWindow *field1a0[20];
    char pad1f0[0x100]; Rva004B19E0Owner *field2f0;
};
#pragma comment(linker, "/alternatename:?Rva004A5950@ControlBar@@IAEXXZ=?j_0003672d@@YAXXZ")
struct Rva004A4090WindowVec : std::vector<GameWindow*> { void reserve20(unsigned); };
#pragma comment(linker, "/alternatename:?reserve20@Rva004A4090WindowVec@@QAEXI@Z=?j_00046f4c@@YAXXZ")

void ControlBar::populateCommand(Object *object,Bool refresh)
{
    Player *player=object->getControllingPlayer();
    resetContainData();
    const CommandSet *commandSet=TheControlBar->findCommandSet(object->getCommandSetString());
    Rva001CAF20Record *overrideRecord=object->Rva001CAF20();
    if(overrideRecord) commandSet=TheControlBar->findCommandSet(overrideRecord->commandSetName);
    if(!commandSet) {
        if(Glo012F4B98) Glo012F4B98->Rva0058C040();
        return;
    }
    int i;
    for(i=0;i<20;++i) {
        if(m_commandWindows[i]) {
            const CommandButton *button=commandSet->getCommandButton(i);
            if(!button) m_commandWindows[i]->bfmeClose(true);
            else button->Rva0049BA80(object,false);
            setControlCommand(m_commandWindows[i],button);
        }
    }
    ContainModuleInterface *contain=object->getContain();
    if(contain && contain->slot45()) doTransportInventoryUI(object,commandSet);
    int specialIndex=0;
    for(i=0;i<20;++i) {
        const CommandButton *button=commandSet->getCommandButton(i);
        CommandButton *b=(CommandButton*)button;
        if(!b || !b->field152) continue;
        if(b->m_options&0x80000) {
            if(m_commandWindows[i]) m_commandWindows[i]->bfmeClose(true);
            continue;
        }
        if(contain && b->field153) {
            OpenContain *open=contain->asOpenContain();
            if(open && !*((const unsigned char*)open+0xb6)) continue;
        }
        if(b->m_command==0x2c) {
            if(!ThePlayerList->isLocalAlliedWith(object)) {
                m_commandWindows[i]->bfmeClose(true);
                continue;
            }
            const Image *image=player->m_store684.Rva000FA800(specialIndex);
            Rva0013E4D0 *tmpl=(Rva0013E4D0*)player->m_store684.rva000F9670(specialIndex);
            if(image && tmpl) {
                button->setButtonImage(image);
                AsciiString text;
                if(tmpl->take(text)) b->field68=text;
                if(m_commandWindows[i]) setControlCommand(m_commandWindows[i],button);
                b->field68.clear();
                b->fielda0=specialIndex;
            } else b->fielda0=-1;
            ++specialIndex;
        }
        // NOT RETAIL: two placeholder zero stores; see header.
        b->m_zeroPlaceholderA=0; b->m_zeroPlaceholderB=0;
        if(b->m_command==0xf) continue;
        if(m_commandWindows[i]) {
            m_commandWindows[i]->bfmeClose(false);
            m_commandWindows[i]->winEnable(true);
            if(b->field14d) m_commandWindows[i]->winSetStatus(0x4000000U);
            else m_commandWindows[i]->winClearStatus(0x4000000U);
        }
        if((b->m_options&0x80) && b->m_specialPower) {
            SpecialPowerTemplate *power=b->m_specialPower;
            if(power->getRequiredScience()!=-1) {
                if(!player->hasScience((ScienceType)power->getRequiredScience())) {
                    if(m_commandWindows[i]) m_commandWindows[i]->bfmeClose(true);
                } else {
                    int bestIndex=-1;
                    ScienceType science;
                    for(unsigned scienceIndex=0;scienceIndex<b->m_science.size();++scienceIndex) {
                        science=(ScienceType)b->m_science[scienceIndex];
                        if(player->hasScience(science)) bestIndex=scienceIndex;
                        else break;
                    }
                    if(bestIndex!=-1) {
                        science=(ScienceType)b->m_science[bestIndex];
                        for(CommandButton *candidate=m_commandButtons;candidate;candidate=candidate->m_upgradeTemplate) {
                            if(candidate->m_command==0x18 && !candidate->m_science.empty() && candidate->m_science[0]==science)
                                button->bfmeCopyFrom(candidate,true);
                        }
                    }
                }
            }
        }
    }
    if(object->isLocallyControlled() || !ThePlayerList->m_localPlayer->isPlayerActive()) {
        ExitInterface *exitInterface=object->getObjectExitInterface();
        if(exitInterface) showRallyPoint(exitInterface->slot08());
    }
    Rva004A5950();
    Glo012F4B98->Rva005976B0(object);
    if(field2f0) {
        if(!object->isLocallyControlled() && ThePlayerList->m_localPlayer->isPlayerActive()) {
            field2f0->bfmeClear();
            return;
        }
        Rva004A4090WindowVec windows;
        windows.reserve20(20U);
        for(int k=0;k<20;++k) {
            GameWindow *window=field1a0[k];
            if(window) windows.push_back(window);
        }
        field2f0->Rva004B19E0(&windows);
    }
}
