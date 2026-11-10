// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include <vector>
#include "ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
class Gen003BD8D0Built;
class Gen003BD7D0Node { public: Gen003BD8D0Built *build(); char m_00[0xc]; float m_0c; float m_10; };
class Rva003BF540 { public: Gen003BD7D0Node *find(int); };
class Gen003C0110Result;
class Rva003BC9C0 { public: void run(Gen003C0110Result *, void *); };
class Gen003BF540Owner { public: bool consume(void *, Gen003BD8D0Built *, void *, void *); };
class LivingWorldRegion;
class LivingWorldRegionManager { public: LivingWorldRegion *rva003C8A50(const AsciiString &); };
struct Flag003C4740 { char m_00[0x18]; char m_18; };
class Gen003BD8D0Built { public: char m_00[0xec]; Flag003C4740 *m_EC; };
struct Holder003C4740 { char m_00[8]; Gen003BD8D0Built *m_08; };
// Views for rva003C3F40 (retail 0x003C3F40, 431B), the snapshot writer the
// method below calls first: it saves the campaign state through a block
// writer (matched base ctor/dtor Gen_009D83D0, also used by GameState::saveGame)
// into a stream named "LivingWorldLogic::StateSnapshotSave" and keeps the
// stream's buffer and size at +0xD4/+0xD8.
class Xfer;
class Gen_009D83D0 { public: Gen_009D83D0(); virtual ~Gen_009D83D0(); private: unsigned char body[0x3c]; };
class BfmeActivationStream {};
class Gen009D6300 { public: bool bfmeTryActivate(BfmeActivationStream *stream, int enabled, bool flags); };
class Gen009D6DD0 { public: void bfmeClose(); };
struct Version003C3F40 { unsigned char version; unsigned char current; };
class XferView003C3F40 {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual void xferVersion(Version003C3F40 *version);
    virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void xferPoint(Coord3D *point);
    virtual void v64(); virtual void v68();
    virtual void xferReal(float *value);
};
class SnapshotView003C3F40 { public: virtual void v00(); virtual void v04(); virtual void v08(); virtual void xfer(Xfer *xfer); };
struct Owner003C3F40 { char m_00[8]; SnapshotView003C3F40 m_snapshot; };
class StateView003C3F40 {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38();
    virtual float getValue();
    virtual void v40();
    virtual void getPoint(Coord3D *point);
};
class BfmeMade_009CB5F0;
BfmeMade_009CB5F0 *bfmeMake_009CB5F0(void *name);
class BfmeThingEC { public: int bfmeTakeEC(int *size); };
class Transfer003C3D90 { public: void transfer(Xfer *xfer); };
class BfmeItemEN;
class BfmeThingEN { public: void bfmeGoEN(BfmeItemEN *item); };
class LivingWorldCampaignManager;
extern LivingWorldCampaignManager *TheLivingWorldCampaignManager;
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;
class GameLogic;
extern GameLogic *TheGameLogic;
class Rva006092D0State;
extern Rva006092D0State *g_rva012F7048LivingWorld;
extern "C" __declspec(dllimport) void __cdecl free(void *block);
class Glo012F1028Type {
public:
    void rva003C4740();
    void StateSnapshotSave();
    char m_00[0x28];
    Holder003C4740 *m_28;
    char m_2C[8];
    int m_34;
    char m_38[0x9c];
    void *m_D4;
    int m_D8;
};
// ?StateSnapshotSave@Glo012F1028Type@@QAEXXZ
void Glo012F1028Type::StateSnapshotSave() {
    free(m_D4);
    m_D4 = 0;
    m_D8 = 0;
    BfmeMade_009CB5F0 *stream = bfmeMake_009CB5F0("LivingWorldLogic::StateSnapshotSave");
    if (stream == 0)
        return;
    Gen_009D83D0 writer;
    XferView003C3F40 *xfer = (XferView003C3F40 *)&writer;
    ((Gen009D6300 *)&writer)->bfmeTryActivate((BfmeActivationStream *)stream, 0, false);
    ((Transfer003C3D90 *)this)->transfer((Xfer *)&writer);
    ((Owner003C3F40 *)TheLivingWorldCampaignManager)->m_snapshot.xfer((Xfer *)&writer);
    ((SnapshotView003C3F40 *)m_28)->xfer((Xfer *)&writer);
    ((BfmeThingEN *)TheGameLogic)->bfmeGoEN((BfmeItemEN *)&writer);
    ((Owner003C3F40 *)TheLivingWorldManager)->m_snapshot.xfer((Xfer *)&writer);
    Version003C3F40 version;
    version.version = 1;
    version.current = 2;
    xfer->xferVersion(&version);
    Coord3D point;
    point.x = 0.0f;
    point.y = 0.0f;
    point.z = 0.0f;
    ((StateView003C3F40 *)g_rva012F7048LivingWorld)->getPoint(&point);
    Gen003BD7D0Node *node = ((Rva003BF540 *)this)->find(m_34);
    if (node) {
        Coord3D at;
        at.x = node->m_0c;
        at.y = node->m_10;
        at.z = 0.0f;
        point = at;
    }
    xfer->xferPoint(&point);
    float value = ((StateView003C3F40 *)g_rva012F7048LivingWorld)->getValue();
    xfer->xferReal(&value);
    m_D4 = (void *)((BfmeThingEC *)stream)->bfmeTakeEC(&m_D8);
    ((Gen009D6DD0 *)&writer)->bfmeClose();
}
void Glo012F1028Type::rva003C4740() {
    if(m_34) {
        Gen003BD8D0Built *p=m_28->m_08;
        if(p) {
            StateSnapshotSave();
            Gen003BD7D0Node *owner=((Rva003BF540*)this)->find(m_34);
            if(!owner->build()) {
                ((Rva003BC9C0*)this)->run((Gen003C0110Result*)owner,p);
                return;
            }
            std::vector<AsciiString> names;
            char saved=p->m_EC->m_18;
            p->m_EC->m_18=1;
            if(((Gen003BF540Owner*)m_28)->consume(owner->build(),p,&names,0)) {
                if(owner->build()==p)
                    ((Rva003BC9C0*)this)->run((Gen003C0110Result*)owner,p);
                else {
                    for(unsigned i=1; i<names.size(); ++i) {
                        ((Rva003BC9C0*)this)->run((Gen003C0110Result*)owner,((LivingWorldRegionManager*)m_28)->rva003C8A50(names[i]));
                        names[i].~AsciiString();
                    }
                    names[0].~AsciiString();
                }
            }
            p=(Gen003BD8D0Built*)p->m_EC;
            ((Flag003C4740*)p)->m_18=saved;
        }
    }
}
