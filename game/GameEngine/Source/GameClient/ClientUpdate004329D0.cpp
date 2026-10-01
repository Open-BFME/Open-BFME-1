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
extern unsigned fadeQueueKey;
void j_00048b03();
void j_00049977();
void j_00012ac6();
void j_0000743c();
class Shell: public Dispatch004329D0 {
public:
    Shell();
    void push(AsciiString,bool);
    char storage[0x6c];
};
// The singleton globals 004329D0 reaches carry retail's own variable and type
// names, because that pair is what the mangled reference spells. None of these
// classes is given a layout here: every call below still goes through the
// slot-index view above or through a typed accessor, so a forward declaration
// is all the spelling needs and no data layout is claimed for them. The
// struct/class split is load-bearing: MSVC spells a pointer-to-struct `PAU`
// and a pointer-to-class `PAV`, and retail's own DIR32 names fix which one
// each of these is.
class BfmeOwnVVD;
class Gen_005B42F0;
class SnowManager;
class CloudEffectSystem;
class CloudSystem;
class Anim2DCollection;
struct Keyboard0040F780;
class BfmeGlobal_012f142c;
class Mouse;
class GenFallback;
class Rva00367810VirtualGate;
struct MovieControl0040F780;
struct MovieFactory0040E3B0;
class FadeView;
class BfmeGlobal_012f076c;
struct Frame00200420;
struct Players005999B0;
struct Engine007629F0;
class BfmeGhostAH;
class Gen_00409040Registry;
class Rva001A8820TerrainVisual;
class ParticleSystemManager;
class Rva0048EC80Manager;
class Gen000290D2;
struct InGameUI;
extern BfmeOwnVVD *g_bfmeSingletonVVD;
extern Gen_005B42F0 *g_bfmeInstanceXE;
extern SnowManager *TheSnowManager;
extern CloudEffectSystem *TheCloudEffectSystem;
extern CloudSystem *TheCloudSystem;
extern Anim2DCollection *Rva012f4ca8;
extern Keyboard0040F780 *KeyboardGlobal0040F780;
extern BfmeGlobal_012f142c *TheBfmeGlobal_012f142c;
extern Mouse *Mouse0040F780;
extern GenFallback *GenFallback0012ED5C8;
extern Rva00367810VirtualGate *Rva00367810TheVirtualGate;
extern MovieControl0040F780 *Control0040F780;
extern MovieFactory0040E3B0 *MovieFactoryGlobal0040E3B0;
extern FadeView *FadeTacticalView;
extern BfmeGlobal_012f076c *TheBfmeGlobal_012f076c;
extern Frame00200420 *Clock00200420;
extern Players005999B0 *PlayerList005999B0;
extern Engine007629F0 *EngineGlobal007629F0;
extern BfmeGhostAH *TheBfmeGhostAH;
extern Gen_00409040Registry *g_012F10D0;
extern Rva001A8820TerrainVisual *TheTerrainVisual;
extern ParticleSystemManager *TheParticleSystemManager;
extern Rva0048EC80Manager *Rva0048EC80TheManager;
extern Gen000290D2 *R2Ptr012F19E8;
extern InGameUI *TheInGameUI;
extern HeaderTemplateManager *TheHeaderTemplateManager;
extern Shell *TheShell;
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
    ((Calls004329D0 *)g_bfmeSingletonVVD)->rva005B5590();
    ((Calls004329D0 *)g_bfmeInstanceXE)->rva005B4D40();
    if (g_012B534C) {
        postTimedOp(LoadGameFadeSlot((void *)j_00048b03),&fadeQueueKey);
        postTimedOp(LoadGameFadeSlot((void *)j_00049977),&fadeQueueKey);
        postTimedOp(LoadGameFadeSlot((void *)j_00012ac6),&fadeQueueKey);
        postTimedOp(LoadGameFadeSlot((void *)j_0000743c),&fadeQueueKey);
    }
    g_012B534C = false;
    if (TheSnowManager) ((Dispatch004329D0 *)TheSnowManager)->v14();
    if (TheCloudEffectSystem) ((Dispatch004329D0 *)TheCloudEffectSystem)->v14();
    if (TheCloudSystem) ((Dispatch004329D0 *)TheCloudSystem)->v14();
    ((Dispatch004329D0 *)Rva012f4ca8)->v14();
    if (KeyboardGlobal0040F780) { ((Dispatch004329D0 *)KeyboardGlobal0040F780)->v14(); ((Dispatch004329D0 *)KeyboardGlobal0040F780)->v28(); }
    ((Dispatch004329D0 *)TheBfmeGlobal_012f142c)->v14();
    if (Mouse0040F780) { ((Dispatch004329D0 *)Mouse0040F780)->v14(); ((Dispatch004329D0 *)Mouse0040F780)->v2c(); }
    bfmeGo924G();
    if (at<bool>(GenFallback0012ED5C8,0xbb6) || at<bool>(GenFallback0012ED5C8,0xbb7)) {
        ((Dispatch004329D0 *)Rva00367810TheVirtualGate)->v1c();
        ((Dispatch004329D0 *)Rva00367810TheVirtualGate)->v14();
        return;
    }
    ((Dispatch004329D0 *)Control0040F780)->v14();
    ((Dispatch004329D0 *)MovieFactoryGlobal0040E3B0)->v14();
    Rva0090F050();
    if (at<int>(GenFallback0012ED5C8,0xd08)>0) {
        unsigned long now = timeGetTime();
        if (now - g_012F1468 > 3000) {
            unsigned long tick;
            do { tick = timeGetTime(); } while (tick < at<int>(GenFallback0012ED5C8,0xd08) + now);
            g_012F1468 = timeGetTime();
        }
    }
    bool freezeTime = (((Dispatch004329D0 *)FadeTacticalView)->vd4() && !((Dispatch004329D0 *)FadeTacticalView)->v74())
        || ((ScriptEngine *)TheBfmeGlobal_012f076c)->debugFrozen()
        || ((Rva00336EF0ByteField *)TheBfmeGlobal_012f076c)->get()
        || ((BfmeGameLogicPause *)Clock00200420)->isGamePaused();
    int localPlayerIndex = PlayerList005999B0 ? ((PlayerList004329D0 *)PlayerList005999B0)->getLocal()->getIndex() : 0;
    freezeTime = freezeTime || (g_012B5348 == m_at000C);
    bool shroud = at<int>(EngineGlobal007629F0,0x30)==1;
    if (!freezeTime && !at<bool>(Clock00200420,0x11d)) {
        g_012B5348 = m_at000C;
        if (shroud) ((Dispatch004329D0 *)TheBfmeGhostAH)->v18(0,0);
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
                        if (((Logic004329D0 *)Clock00200420)->getFrame() < limit+draw->getClearFrame()) status=1;
                    }
                    ((Drawable *)draw)->setDrawableHidden(status>=3);
                }
            }
            draw->rva0041BE60();
            draw = next;
        }
        ((Dispatch004329D0 *)g_012F10D0)->v14();
        if (at<int>(EngineGlobal007629F0,0x30)==1)
            ((Rva0042F190Host *)this)->rva0042F190(((Logic004329D0 *)Clock00200420)->getFrame(),true);
        else
            ((Rva0042F190Host *)this)->rva0042F190(((Logic004329D0 *)Clock00200420)->getFrame(),false);
    }
    ((GameLogicClientUpdate *)Clock00200420)->deleteLoadScreen();
    if (!at<bool>(Clock00200420,0x11d)) {
        ((Dispatch004329D0 *)((char *)TheTerrainVisual+4))->v14();
        ((Dispatch004329D0 *)Rva00367810TheVirtualGate)->v14();
    } else {
        ((Calls004329D0 *)Rva00367810TheVirtualGate)->rva0040DE00();
    }
    if (!freezeTime) at<int>(TheParticleSystemManager,0x98)=localPlayerIndex;
    ((Dispatch004329D0 *)Rva00367810TheVirtualGate)->v1c();
    ((Dispatch004329D0 *)Rva0048EC80TheManager)->v14();
    if (!at<bool>(Clock00200420,0x11d)) {
        TheShell->v14();
        if (m_at00C5) {
            if (TheShell) TheShell->v00(1);
            TheShell=0;
            m_at00C5=false;
            if (m_at00C8>0 && m_at00CC>0 && m_at00D0>0
                && (m_at00C8!=at<unsigned int>(GenFallback0012ED5C8,0x2c)
                    || m_at00CC!=at<unsigned int>(GenFallback0012ED5C8,0x30))) {
                if (m_at00C6) {
                    m_at00D4=((Dispatch004329D0 *)Rva00367810TheVirtualGate)->v2c();
                    m_at00D8=((Dispatch004329D0 *)Rva00367810TheVirtualGate)->v30();
                    m_at00DC=((Dispatch004329D0 *)Rva00367810TheVirtualGate)->v38();
                }
                if (((Dispatch004329D0 *)Rva00367810TheVirtualGate)->v44(m_at00C8,m_at00CC,m_at00D0,((Dispatch004329D0 *)Rva00367810TheVirtualGate)->v40())) {
                    at<unsigned int>(GenFallback0012ED5C8,0x2c)=m_at00C8;
                    at<unsigned int>(GenFallback0012ED5C8,0x30)=m_at00CC;
                    TheHeaderTemplateManager->refreshFonts004329D0();
                    ((Gen_005a4400 *)Mouse0040F780)->m();
                    bfmeRun_004647E0();
                } else m_at00C6=false;
                m_at00C8=0;
                m_at00CC=0;
                m_at00D0=0;
            }
            TheShell=new Shell;
            if (TheShell) TheShell->v04();
            ((Dispatch004329D0 *)Control0040F780)->v14();
            ((Dispatch004329D0 *)R2Ptr012F19E8)->v14();
            ((Dispatch004329D0 *)TheInGameUI)->v188();
            TheShell->push(AsciiString("MainMenu.apt"),false);
        }
    }
    ((Dispatch004329D0 *)TheInGameUI)->v14();
    v80();
}

