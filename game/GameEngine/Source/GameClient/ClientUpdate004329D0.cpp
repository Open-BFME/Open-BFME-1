// cl: /DNDEBUG
// Byte-exact reconstruction of retail RVA 004329D0, 1632 bytes.
// Evidence: targets/game/reverse/identity_evidence/004329D0-client-update.md.
// The generic dispatch class is a slot-index ABI view, not a shared class
// identity for the subsystems. The constructor-only Shell view is 0x70 bytes.
// The named callee declarations below carry no unverified data layout.
// ZH GameClient::update supplies the drawable/shroud loop; BFME-specific
// callbacks and shell recreation are taken from retail, not guessed ZH code.
// Address-qualified ABI views deliberately do not claim class identities.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
class Dispatch004329D0 {
public:
    virtual void v00(unsigned int);
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18(void *,int);
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual unsigned int v2c();
    virtual unsigned int v30();
    virtual void v34();
    virtual unsigned int v38();
    virtual void v3c();
    virtual unsigned int v40();
    virtual bool v44(unsigned int,unsigned int,unsigned int,unsigned int);
    virtual void v48();
    virtual void v4c();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5c();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6c();
    virtual void v70();
    virtual bool v74();
    virtual void v78();
    virtual void v7c();
    virtual void v80();
    virtual void v84();
    virtual void v88();
    virtual void v8c();
    virtual void v90();
    virtual void v94();
    virtual void v98();
    virtual void v9c();
    virtual void va0();
    virtual void va4();
    virtual void va8();
    virtual void vac();
    virtual void vb0();
    virtual void vb4();
    virtual void vb8();
    virtual void vbc();
    virtual void vc0();
    virtual void vc4();
    virtual void vc8();
    virtual void vcc();
    virtual void vd0();
    virtual bool vd4();
    virtual void vd8();
    virtual void vdc();
    virtual void ve0();
    virtual void ve4();
    virtual void ve8();
    virtual void vec();
    virtual void vf0();
    virtual void vf4();
    virtual void vf8();
    virtual void vfc();
    virtual void v100();
    virtual void v104();
    virtual void v108();
    virtual void v10c();
    virtual void v110();
    virtual void v114();
    virtual void v118();
    virtual void v11c();
    virtual void v120();
    virtual void v124();
    virtual void v128();
    virtual void v12c();
    virtual void v130();
    virtual void v134();
    virtual void v138();
    virtual void v13c();
    virtual void v140();
    virtual void v144();
    virtual void v148();
    virtual void v14c();
    virtual void v150();
    virtual void v154();
    virtual void v158();
    virtual void v15c();
    virtual void v160();
    virtual void v164();
    virtual void v168();
    virtual void v16c();
    virtual void v170();
    virtual void v174();
    virtual void v178();
    virtual void v17c();
    virtual void v180();
    virtual void v184();
    virtual void v188();
};
// These offsets are read directly in 004329D0. No semantic member identity
// is asserted by these two typed accessors.
template<class T> __forceinline T &at(void *p, unsigned int offset) { return *(T *)((char *)p + offset); }
enum ObjectShroudStatus { ObjectShroudStatusUnknown004329D0 = 0 };
class Object { public: ObjectShroudStatus getShroudedStatus(int) const; };
class Drawable { public: void setDrawableHidden(bool); };
class GameLogicClientUpdate { public: void deleteLoadScreen(); };
class BfmeGameLogicPause { public: bool isGamePaused(); };
class Rva00336EF0ByteField { public: unsigned char get() const; };
class ScriptEngine {
public:
    bool isTimeFrozenDebug();
    bool _bfme_isClientFrameFrozen();
    __forceinline bool debugFrozen() { return isTimeFrozenDebug() || _bfme_isClientFrameFrozen(); }
};
class HeaderTemplateManager {
public:
    __forceinline void refreshFonts004329D0() { populateGameFonts(); }
private:
    void populateGameFonts();
};
class Gen_005a4400 { public: void m(); };
struct Calls004329D0 {
    void rva005B5590();
    void rva005B4D40();
    void rva0041BE60();
    void rva0040DE00();
};
struct Drawable004329D0 : Calls004329D0 {
    char pad00[0xfc];
    Calls004329D0 *m_at00FC;
    char pad100[4];
    Drawable004329D0 *m_at0104;
    char pad108[0x2c];
    unsigned int m_at0134;
    __forceinline Drawable004329D0 *getNext() const { return m_at0104; }
    __forceinline Calls004329D0 *getObject() const { return m_at00FC; }
    __forceinline unsigned int getClearFrame() const { return m_at0134; }
};
struct Logic004329D0 {
    char pad00[0x3c]; unsigned int m_at003C;
    __forceinline unsigned int getFrame() const { return m_at003C; }
};
struct Object004329D0 {
    char pad00[0x344]; unsigned int m_at0344;
    __forceinline bool isDead() const { return (m_at0344&1)!=0; }
};
// Retail 42F190 reads two stack words and ends in ret 8. The existing
// functor form uses the low byte of its second word; this call view models
// the two pushes in this caller without imposing an invented semantic name.
class Rva0042F190Host { public: void rva0042F190(unsigned int,bool); };
void bfmeGo924G();
void Rva0090F050();
void bfmeRun_004647E0();
struct LoadGameFadeSlot { LoadGameFadeSlot(void *fn): m_fn(fn) {} void *m_fn; };
class LoadGameFadeWrapperHead {
public:
    LoadGameFadeWrapperHead() throw(): m_refCount(0) {}
    virtual void loadGameFadeWrapperAnchor();
    unsigned int m_refCount;
};
class LoadGameFadeWrapper: public LoadGameFadeWrapperHead {
public:
    __forceinline LoadGameFadeWrapper(const LoadGameFadeSlot &slot) throw(): m_slot(slot) {}
    LoadGameFadeSlot m_slot;
};
class LoadGameFadeHolder {
public:
    __forceinline LoadGameFadeHolder(LoadGameFadeSlot binding) throw() {
        m_ptr = new LoadGameFadeWrapper(binding);
        if (m_ptr) m_ptr->m_refCount++;
    }
    ~LoadGameFadeHolder() {}
    LoadGameFadeWrapper *m_ptr;
};
void postTimedOp(LoadGameFadeHolder,void *);
class Shell: public Dispatch004329D0 {
public:
    Shell();
    void push(AsciiString,bool);
    char storage[0x6c];
};
extern Dispatch004329D0 *g_012F4C84;
extern Dispatch004329D0 *g_012F4C80;
extern Dispatch004329D0 *g_012F15F4;
extern Dispatch004329D0 *g_012F1104;
extern Dispatch004329D0 *g_012F10F0;
extern Dispatch004329D0 *g_012F4CA8;
extern Dispatch004329D0 *g_012F4C50;
extern Dispatch004329D0 *g_012F142C;
extern Dispatch004329D0 *g_012F4C5C;
extern Dispatch004329D0 *g_012ED5C8;
extern Dispatch004329D0 *g_012F1270;
extern Dispatch004329D0 *g_012F1B40;
extern Dispatch004329D0 *g_0130B190;
extern Dispatch004329D0 *g_012F1600;
extern Dispatch004329D0 *g_012F076C;
extern Dispatch004329D0 *g_012F0898;
extern Dispatch004329D0 *g_012ED748;
extern Dispatch004329D0 *g_012ED524;
extern Dispatch004329D0 *g_012EF4FC;
extern Dispatch004329D0 *g_012F10D0;
extern Dispatch004329D0 *g_012F7014;
extern Dispatch004329D0 *g_012F64BC;
extern Dispatch004329D0 *g_012F12CC;
extern Dispatch004329D0 *g_012F19E8;
extern Dispatch004329D0 *g_012F148C;
extern Dispatch004329D0 *g_012F333C;
extern Shell *g_012F4B58;
extern bool g_012B534C;
extern unsigned int g_012F1468, g_012B5348;
struct Player004329D0 {
    char pad00[0x24]; int m_at0024;
    __forceinline int getIndex() const { return m_at0024; }
};
struct PlayerList004329D0 {
    char pad00[0xc]; Player004329D0 *m_at000C;
    __forceinline Player004329D0 *getLocal() const { return m_at000C; }
};
class ClientUpdate004329D0: public Dispatch004329D0 {
public:
    __forceinline unsigned int getFrame() const { return m_at000C; }
    void update();
    char pad04[8];
    unsigned int m_at000C;
    char pad10[0xb5];
    bool m_at00C5, m_at00C6;
    char padC7;
    unsigned int m_at00C8, m_at00CC, m_at00D0;
    unsigned int m_at00D4, m_at00D8, m_at00DC;
};
void ClientUpdate004329D0::update() {
    ((Calls004329D0 *)g_012F4C84)->rva005B5590();
    ((Calls004329D0 *)g_012F4C80)->rva005B4D40();
    if (g_012B534C) {
        postTimedOp(LoadGameFadeSlot((void *)0x00448B03),(void *)0x012ED588);
        postTimedOp(LoadGameFadeSlot((void *)0x00449977),(void *)0x012ED588);
        postTimedOp(LoadGameFadeSlot((void *)0x00412AC6),(void *)0x012ED588);
        postTimedOp(LoadGameFadeSlot((void *)0x0040743C),(void *)0x012ED588);
    }
    g_012B534C = false;
    if (g_012F15F4) g_012F15F4->v14();
    if (g_012F1104) g_012F1104->v14();
    if (g_012F10F0) g_012F10F0->v14();
    g_012F4CA8->v14();
    if (g_012F4C50) { g_012F4C50->v14(); g_012F4C50->v28(); }
    g_012F142C->v14();
    if (g_012F4C5C) { g_012F4C5C->v14(); g_012F4C5C->v2c(); }
    bfmeGo924G();
    if (at<bool>(g_012ED5C8,0xbb6) || at<bool>(g_012ED5C8,0xbb7)) {
        g_012F1270->v1c();
        g_012F1270->v14();
        return;
    }
    g_012F1B40->v14();
    g_0130B190->v14();
    Rva0090F050();
    if (at<int>(g_012ED5C8,0xd08)>0) {
        unsigned long now = timeGetTime();
        if (now - g_012F1468 > 3000) {
            unsigned long tick;
            do { tick = timeGetTime(); } while (tick < at<int>(g_012ED5C8,0xd08) + now);
            g_012F1468 = timeGetTime();
        }
    }
    bool freezeTime = (g_012F1600->vd4() && !g_012F1600->v74())
        || ((ScriptEngine *)g_012F076C)->debugFrozen()
        || ((Rva00336EF0ByteField *)g_012F076C)->get()
        || ((BfmeGameLogicPause *)g_012F0898)->isGamePaused();
    int localPlayerIndex = g_012ED748 ? ((PlayerList004329D0 *)g_012ED748)->getLocal()->getIndex() : 0;
    freezeTime = freezeTime || (g_012B5348 == m_at000C);
    bool shroud = at<int>(g_012ED524,0x30)==1;
    if (!freezeTime && !at<bool>(g_012F0898,0x11d)) {
        g_012B5348 = m_at000C;
        if (shroud) g_012EF4FC->v18(0,0);
        Drawable004329D0 *draw = (Drawable004329D0 *)v30();
        while (draw) {
            Drawable004329D0 *next = draw->getNext();
            if (shroud) {
                Calls004329D0 *object = draw->getObject();
                if (object) {
                    int status = ((Object *)object)->getShroudedStatus(localPlayerIndex);
                    if (status >= 3 && draw->getClearFrame()!=0) {
                        unsigned int limit = 10;
                        if (((Object004329D0 *)object)->isDead()) limit=25;
                        if (((Logic004329D0 *)g_012F0898)->getFrame() < limit+draw->getClearFrame()) status=1;
                    }
                    ((Drawable *)draw)->setDrawableHidden(status>=3);
                }
            }
            draw->rva0041BE60();
            draw = next;
        }
        g_012F10D0->v14();
        if (at<int>(g_012ED524,0x30)==1)
            ((Rva0042F190Host *)this)->rva0042F190(((Logic004329D0 *)g_012F0898)->getFrame(),true);
        else
            ((Rva0042F190Host *)this)->rva0042F190(((Logic004329D0 *)g_012F0898)->getFrame(),false);
    }
    ((GameLogicClientUpdate *)g_012F0898)->deleteLoadScreen();
    if (!at<bool>(g_012F0898,0x11d)) {
        ((Dispatch004329D0 *)((char *)g_012F7014+4))->v14();
        g_012F1270->v14();
    } else {
        ((Calls004329D0 *)g_012F1270)->rva0040DE00();
    }
    if (!freezeTime) at<int>(g_012F64BC,0x98)=localPlayerIndex;
    g_012F1270->v1c();
    g_012F12CC->v14();
    if (!at<bool>(g_012F0898,0x11d)) {
        g_012F4B58->v14();
        if (m_at00C5) {
            if (g_012F4B58) g_012F4B58->v00(1);
            g_012F4B58=0;
            m_at00C5=false;
            if (m_at00C8>0 && m_at00CC>0 && m_at00D0>0
                && (m_at00C8!=at<unsigned int>(g_012ED5C8,0x2c)
                    || m_at00CC!=at<unsigned int>(g_012ED5C8,0x30))) {
                if (m_at00C6) {
                    m_at00D4=g_012F1270->v2c();
                    m_at00D8=g_012F1270->v30();
                    m_at00DC=g_012F1270->v38();
                }
                if (g_012F1270->v44(m_at00C8,m_at00CC,m_at00D0,g_012F1270->v40())) {
                    at<unsigned int>(g_012ED5C8,0x2c)=m_at00C8;
                    at<unsigned int>(g_012ED5C8,0x30)=m_at00CC;
                    ((HeaderTemplateManager *)g_012F333C)->refreshFonts004329D0();
                    ((Gen_005a4400 *)g_012F4C5C)->m();
                    bfmeRun_004647E0();
                } else m_at00C6=false;
                m_at00C8=0;
                m_at00CC=0;
                m_at00D0=0;
            }
            g_012F4B58=new Shell;
            if (g_012F4B58) g_012F4B58->v04();
            g_012F1B40->v14();
            g_012F19E8->v14();
            g_012F148C->v188();
            g_012F4B58->push(AsciiString("MainMenu.apt"),false);
        }
    }
    g_012F148C->v14();
    v80();
}

