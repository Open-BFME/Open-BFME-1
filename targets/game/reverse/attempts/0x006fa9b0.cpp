// ?doParticles@W3DParticleSystemManager@@UAEXAAVRenderInfoClass@@@Z
// partial score=0.8689 date=2026-10-08
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/shims/sweep /Iinputs/reference/shims/smudgenopool
// stlport
// Retail 0x006FA9B0 uses 12-byte intrusive handles and a deferred renderer.
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "winbase_shim.h"
#include "camera.h"
#include "rinfo.h"
#include "aabox.h"
#include "vector2.h"
#include "texture.h"
#include "color.h"
#include "ascii_string.h"
typedef int Int;
typedef float Real;
typedef bool Bool;
#include <GameClient/Smudge.h>
#include <vector>
#include <list>
#include <stddef.h>

class BaseHeightMapRenderObjClass {
public:
    bool getMaximumVisibleBox(const FrustumClass &, AABoxClass *, bool);
};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
struct Rva006FA9B0SmudgeProbe { unsigned char m_beforeProbe[0x40]; int m_probeColor; };
class SnowManager;
class W3DSnowManager { public: void render(RenderInfoClass &); };
extern SnowManager *TheSnowManager;
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct Rva006FA9B0GlobalData { unsigned char m_beforeHeat[0x1d]; bool m_useHeatEffects; };
extern int g_bfmeVal991;
extern unsigned char g_get_006f9ff0;
extern bool Rva012D6D75;
extern const char g_bfmeEmptyAscii[];
float GetGameClientRandomValueReal(float, float, char *, int);
class Rva005C30A0Owner {
public:
    float Rva005C30A0() const;
    float Rva005C3120() const;
};
class Rva005C3160Owner { public: float Rva005C3160() const; };
class Rva005C3180 { public: int dispatch() const; };
struct Rva006FA9B0Particle {
    unsigned char m_beforePosition[0x1c];
    Vector3 m_position;
    unsigned char m_beforeNext[0x14];
    Rva006FA9B0Particle *m_systemNext;
};
class Rva006FA9B0Renderer {
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual int render(RenderInfoClass &, const AABoxClass *, unsigned int *);
};
struct GenNode_006fa270;
struct GenOwner_006fa270 {
    unsigned char m_beforeKind[0xc];
    int m_kind;
    AsciiString m_name;
    unsigned char m_beforePriority[0x10];
    unsigned int m_deferredIndex24;
    unsigned char m_beforeHandles[0x70];
    GenNode_006fa270 *m_head, *m_tail;
    Rva006FA9B0Particle *m_firstParticle;
    unsigned char m_beforeRenderer[0x124];
    Rva006FA9B0Renderer *m_renderer;
};
struct GenNode_006fa270 {
    GenOwner_006fa270 *m_owner;
    GenNode_006fa270 *m_prev, *m_next;
    GenNode_006fa270(GenOwner_006fa270 *owner) {
        m_owner=owner;
        if (owner) {
            m_prev=owner->m_tail;
            m_next=0;
            owner->m_tail=this;
            if (m_prev) m_prev->m_next=this;
            else m_owner->m_head=this;
        } else { m_next=0; m_prev=0; }
    }
    GenNode_006fa270(const GenNode_006fa270 &other) {
        m_owner=other.m_owner;
        if (m_owner) {
            m_prev=m_owner->m_tail;
            m_next=0;
            m_owner->m_tail=this;
            if (m_prev) m_prev->m_next=this;
            else m_owner->m_head=this;
        } else { m_next=0; m_prev=0; }
    }
    void unlink() {
        if (m_owner) {
            if (m_prev) m_prev->m_next=m_next;
            else m_owner->m_head=m_next;
            if (m_next) m_next->m_prev=m_prev;
            else m_owner->m_tail=m_prev;
            m_prev=0; m_next=0;
        }
    }
    ~GenNode_006fa270() { unlink(); }
    GenNode_006fa270 &operator=(const GenNode_006fa270 &other) {
        if (this!=&other) {
            unlink(); m_owner=other.m_owner;
            if (m_owner) {
                m_prev=m_owner->m_tail; m_next=0; m_owner->m_tail=this;
                if (m_prev) m_prev->m_next=this;
                else m_owner->m_head=this;
            }
        }
        return *this;
    }
};
class BfmeHandleCX {
public:
    TextureClass *p;
    BfmeHandleCX() : p(0) {}
    ~BfmeHandleCX() { if (p) p->Release_Ref(); }
};
class ParticleSystemManager {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0c(); virtual void slot10(); virtual void slot14();
    virtual void slot18(); virtual void slot1c(); virtual void slot20();
    virtual void slot24(); virtual void setOnScreenParticleCount(int);
    unsigned char m_beforeList[0x7c];
    std::list<GenNode_006fa270> m_allParticleSystemList;
};
extern ParticleSystemManager *TheParticleSystemManager;
class W3DParticleSystemManager {
public:
    virtual void doParticles(RenderInfoClass &);
    unsigned char m_beforeFieldCount[0x84];
    unsigned int m_fieldParticleCount;
    unsigned char m_beforeOnScreen[4];
    int m_onScreenParticleCount;
    unsigned char m_beforeReady[0x28];
    bool m_readyToRender;
    std::vector<GenNode_006fa270> m_deferred[2];
};
typedef char check_owner_renderer[offsetof(GenOwner_006fa270,m_renderer)==0x1c8?1:-1];
typedef char check_handle[sizeof(GenNode_006fa270)==12?1:-1];
typedef char check_ready[offsetof(W3DParticleSystemManager,m_readyToRender)==0xbc?1:-1];
typedef char check_deferred[offsetof(W3DParticleSystemManager,m_deferred)==0xc0?1:-1];

// ?doParticles@W3DParticleSystemManager@@UAEXAAVRenderInfoClass@@@Z
void W3DParticleSystemManager::doParticles(RenderInfoClass &rinfo)
{
    if (!m_readyToRender) return;
    m_readyToRender=false;
    g_bfmeVal991=0;
    if (TheSmudgeManager) TheSmudgeManager->setSmudgeCountLastFrame(0);
    const FrustumClass &frustum=rinfo.Camera.Get_Frustum();
    AABoxClass bbox;
    TheTerrainRenderObject->getMaximumVisibleBox(frustum,&bbox,true);
    float bcX=bbox.Center.X, bcY=bbox.Center.Y, bcZ=bbox.Center.Z;
    float beX=bbox.Extent.X, beY=bbox.Extent.Y, beZ=bbox.Extent.Z;
    SmudgeSet *set=0;
    if (TheSmudgeManager) set=TheSmudgeManager->addSmudgeSet();
    BfmeHandleCX texture;
    std::list<GenNode_006fa270> &systems=TheParticleSystemManager->m_allParticleSystemList;
    for (std::list<GenNode_006fa270>::iterator it=systems.begin();it!=systems.end();++it) {
        GenNode_006fa270 sys(*it);
        if (!sys.m_owner) continue;
        if (sys.m_owner->m_kind==6) continue;
        if (g_get_006f9ff0 && sys.m_owner->m_deferredIndex24>0 && sys.m_owner->m_deferredIndex24<2) {
            m_deferred[sys.m_owner->m_deferredIndex24].push_back(sys);
            continue;
        }
        const char *name=sys.m_owner->m_name.str();
        if (*(const unsigned int *)name==0x44554d53) {
            if (TheSmudgeManager && TheSmudgeManager->getHardwareSupport() &&
                ((Rva006FA9B0GlobalData *)TheWritableGlobalData)->m_useHeatEffects) {
                bool gotColor=false;
                for (Rva006FA9B0Particle *p=sys.m_owner->m_firstParticle;p;p=p->m_systemNext) {
                    const Vector3 *pos=&p->m_position;
                    float psize=((Rva005C30A0Owner *)p)->Rva005C30A0();
                    if (WWMath::Fabs(pos->X-bcX)>(beX+psize)) continue;
                    if (WWMath::Fabs(pos->Y-bcY)>(beY+psize)) continue;
                    if (WWMath::Fabs(pos->Z-bcZ)>(beZ+psize)) continue;
                    if (!gotColor) {
                        RGBColor *color=(RGBColor *)((Rva005C3180 *)p)->dispatch();
                        ((Rva006FA9B0SmudgeProbe *)TheSmudgeManager)->m_probeColor=color->getAsInt();
                        gotColor=true;
                    }
                    Smudge *smudge=set->addSmudgeToSet();
                    float jitter=((Rva005C30A0Owner *)p)->Rva005C3120();
                    smudge->m_pos.Set(pos->X,pos->Y,pos->Z);
                    smudge->m_offset.Set(
                        GetGameClientRandomValueReal(-2.0f*jitter,2.0f*jitter,"F:\\bfme\\Code\\gameenginedevice\\Source\\W3DDevice\\GameClient\\W3DFXParticleSystem.cpp",189),
                        GetGameClientRandomValueReal(-psize,psize,"F:\\bfme\\Code\\gameenginedevice\\Source\\W3DDevice\\GameClient\\W3DFXParticleSystem.cpp",189));
                    smudge->m_size=psize;
                    smudge->m_opacity=((Rva005C3160Owner *)p)->Rva005C3160();
                    ++g_bfmeVal991;
                }
            }
            continue;
        }
        Rva006FA9B0Renderer *renderer=sys.m_owner->m_renderer;
        if (renderer)
            m_onScreenParticleCount+=renderer->render(rinfo,&bbox,&m_fieldParticleCount);
    }
    if (g_get_006f9ff0) {
        bool sorting=Rva012D6D75;
        if (sorting) Rva012D6D75=0;
        for (int pass=1;pass>=0;--pass) {
            for (int i=m_deferred[pass].size()-1;i>=0;--i) {
                GenNode_006fa270 sys(m_deferred[pass][i]);
                if (!sys.m_owner) continue;
                Rva006FA9B0Renderer *renderer=sys.m_owner->m_renderer;
                if (renderer)
                    m_onScreenParticleCount+=renderer->render(rinfo,&bbox,&m_fieldParticleCount);
            }
            m_deferred[pass].erase(m_deferred[pass].begin(),m_deferred[pass].end());
        }
        if (sorting) Rva012D6D75=1;
    }
    TheParticleSystemManager->setOnScreenParticleCount(m_onScreenParticleCount);
    if (TheSnowManager) ((W3DSnowManager *)TheSnowManager)->render(rinfo);
}
