// ?xfer@W3DGhostObject@@MAEXPAVXfer@@@Z
// partial score=0.97 date=2026-09-26
// cl: /O2 /Ob2 /GR- /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ?xfer@W3DGhostObject@@MAEXPAVXfer@@@Z
#include <string.h>

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
struct XferVersion {
    UnsignedByte version;
    UnsignedByte currentVersion;
};

class RetailLayoutString {
public:
    void set(const char *text, int length);
protected:
    void *m_text;
};
class BFMERetailAsciiString : private RetailLayoutString {
public:
    BFMERetailAsciiString() { m_text = 0; }
    ~BFMERetailAsciiString() { releaseBuffer(); }
    const char *str() const { return m_text ? (const char *)m_text + 8 : (const char *)0x0107388B; }
    void set(const char *text, int length) { RetailLayoutString::set(text, length); }
private:
    void releaseBuffer();
};

class Xfer {
public:
    virtual void slot00();
    virtual bool isLoading();
    virtual bool isSaving();
    virtual void slot0C();
    virtual bool isCRC();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void xferVersion(XferVersion *version);
    virtual void slot2C();
    virtual void xferSnapshot(void *snapshot);
    virtual void slot34();
    virtual void slot38();
    virtual void slot3C();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4C();
    virtual void slot50();
    virtual void slot54();
    virtual void slot58();
    virtual void slot5C();
    virtual void slot60();
    virtual void slot64();
    virtual void xferAsciiString(BFMERetailAsciiString *value);
    virtual void xferReal(float *value);
    virtual void slot70();
    virtual void xferUnsignedInt(UnsignedInt *value);
    virtual void xferInt(int *value);
    virtual void slot7C();
    virtual void slot80();
    virtual void xferUnsignedByte(UnsignedByte *value);
};

struct DrawableInfo {
    UnsignedInt objectID;
    void *drawable;
    void *ghost;
    int flags;
};
class Drawable {
public:
    UnsignedInt getID() const;
};

class RenderObjClass {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0C(); virtual void slot10(); virtual void slot14();
    virtual const char *Get_Name() const;
#define RENDER_PAD(n) virtual void slot##n();
    RENDER_PAD(1C) RENDER_PAD(20) RENDER_PAD(24) RENDER_PAD(28) RENDER_PAD(2C)
    RENDER_PAD(30) RENDER_PAD(34) RENDER_PAD(38) RENDER_PAD(3C) RENDER_PAD(40)
    RENDER_PAD(44) RENDER_PAD(48) RENDER_PAD(4C) RENDER_PAD(50) RENDER_PAD(54)
    RENDER_PAD(58) RENDER_PAD(5C) RENDER_PAD(60) RENDER_PAD(64) RENDER_PAD(68)
    RENDER_PAD(6C) RENDER_PAD(70) RENDER_PAD(74) RENDER_PAD(78) RENDER_PAD(7C)
    RENDER_PAD(80) RENDER_PAD(84) RENDER_PAD(88) RENDER_PAD(8C) RENDER_PAD(90)
    RENDER_PAD(94) RENDER_PAD(98) RENDER_PAD(9C) RENDER_PAD(A0) RENDER_PAD(A4)
    RENDER_PAD(A8) RENDER_PAD(AC) RENDER_PAD(B0) RENDER_PAD(B4) RENDER_PAD(B8)
    RENDER_PAD(BC) RENDER_PAD(C0) RENDER_PAD(C4) RENDER_PAD(C8) RENDER_PAD(CC)
    RENDER_PAD(D0) RENDER_PAD(D4) RENDER_PAD(D8) RENDER_PAD(DC) RENDER_PAD(E0)
    RENDER_PAD(E4) RENDER_PAD(E8) RENDER_PAD(EC) RENDER_PAD(F0) RENDER_PAD(F4)
    RENDER_PAD(F8) RENDER_PAD(FC) RENDER_PAD(100) RENDER_PAD(104) RENDER_PAD(108)
    RENDER_PAD(10C) RENDER_PAD(110) RENDER_PAD(114) RENDER_PAD(118) RENDER_PAD(11C)
    RENDER_PAD(120) RENDER_PAD(124) RENDER_PAD(128) RENDER_PAD(12C) RENDER_PAD(130)
    RENDER_PAD(134) RENDER_PAD(138) RENDER_PAD(13C) RENDER_PAD(140) RENDER_PAD(144)
    RENDER_PAD(148) RENDER_PAD(14C) RENDER_PAD(150)
#undef RENDER_PAD
    virtual void Set_User_Data(DrawableInfo *data, bool recursive);
    char pad04[0x44];
    float scale;
    UnsignedInt color;
};

class Snapshot {
public:
    virtual ~Snapshot();
    virtual void loadPostProcess();
    virtual const char *slot08();
    virtual void xfer(Xfer *xfer);
};
class W3DRenderObjectSnapshot : public Snapshot {
public:
    virtual ~W3DRenderObjectSnapshot();
    virtual void loadPostProcess();
    virtual const char *slot08();
    virtual void xfer(Xfer *xfer);
    W3DRenderObjectSnapshot(RenderObjClass *renderObj, DrawableInfo *drawInfo, bool cloneParentRobj)
        { m_next = 0; m_robj = renderObj; renderObj->Set_User_Data(drawInfo, cloneParentRobj); }
    RenderObjClass *m_robj;
    W3DRenderObjectSnapshot *m_next;
};

class GhostObject {
public:
    virtual void slot00();
protected:
    virtual void xfer(Xfer *xfer);
public:
    char pad04[8];
    void *m_parentObject;
    char pad10[0x70];
};
class W3DGhostObject : public GhostObject {
public:
    void removeParentObject();
    W3DRenderObjectSnapshot *m_parentSnapshots[32];
    DrawableInfo m_drawableInfo;
protected:
    virtual void xfer(Xfer *xfer);
};

class Rva006BD6E0Client {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0C(); virtual void slot10(); virtual void slot14();
    virtual void slot18(); virtual void slot1C(); virtual void slot20();
    virtual void slot24(); virtual void slot28();
    virtual Drawable *findDrawableByID(UnsignedInt id);
};
extern Rva006BD6E0Client *TheGameClient;

class Rva006BD6E0Scene {
public:
    virtual void slot00(); virtual void slot04();
    virtual void addRenderObject(RenderObjClass *renderObject);
};
extern Rva006BD6E0Scene *g_012F8058;
struct Rva006BD6E0Player { char pad24[0x24]; int playerIndex; };
struct Rva006BD6E0PlayerList { char pad0C[12]; Rva006BD6E0Player *localPlayer; };
extern Rva006BD6E0PlayerList *g_012ED748;

extern void friend_xferObjectID(Xfer *xfer, UnsignedInt *objectID);
extern void BfmeParticleSystemXferHandle(Xfer &xfer, void *value);
extern RenderObjClass *Create_Render_Obj(const char *name, float scale, int color);
extern void disableUVAnimations(RenderObjClass *renderObj);
struct XferException { void *text; int tag; };
extern "C" XferException *__cdecl bfmeFormatText(XferException *result, int tag, const char *format, ...);
__declspec(noreturn) void __stdcall _CxxThrowException(void *object, void *throwInfo);

void W3DGhostObject::xfer(Xfer *xfer)
{
    GhostObject::xfer(xfer);
    if (xfer->isCRC()) return;
    {
        union VersionStorage { XferVersion version; unsigned char pad[4]; } versionStorage;
        versionStorage.version.version = 1;
        versionStorage.version.currentVersion = 1;
        xfer->xferVersion(&versionStorage.version);
    }
    friend_xferObjectID(xfer, &m_drawableInfo.objectID);
    xfer->xferInt(&m_drawableInfo.flags);
    UnsignedInt drawableID = m_drawableInfo.drawable ? ((Drawable *)m_drawableInfo.drawable)->getID() : 0;
    BfmeParticleSystemXferHandle(*xfer, &drawableID);
    if (xfer->isLoading())
        m_drawableInfo.drawable = TheGameClient->findDrawableByID(drawableID);

    {
    UnsignedByte count;
    for (int i = 0; i < 32; ++i) {
        count = 0;
        W3DRenderObjectSnapshot *snap = m_parentSnapshots[i];
        while (snap) { ++count; snap = snap->m_next; }
        xfer->xferUnsignedByte(&count);
        XferException error;
        if (count == 0 && m_parentSnapshots[i] != 0) {
            bfmeFormatText(&error, 4, 0);
            _CxxThrowException(&error, (void *)0x011DFE5C);
        }
        float scale;
        UnsignedInt color;
        BFMERetailAsciiString name;
        if (xfer->isSaving()) {
            snap = m_parentSnapshots[i];
            while (snap) {
                const char *text = snap->m_robj->Get_Name();
                name.set(text, text ? strlen(text) : 0);
                xfer->xferAsciiString(&name);
                scale = snap->m_robj->scale;
                xfer->xferReal(&scale);
                color = snap->m_robj->color;
                xfer->xferUnsignedInt(&color);
                xfer->xferSnapshot(snap);
                snap = snap->m_next;
            }
        } else {
            RenderObjClass *renderObj;
            W3DRenderObjectSnapshot *prev = 0;
            for (UnsignedByte j = 0; j < count; ++j) {
                xfer->xferAsciiString(&name);
                xfer->xferReal(&scale);
                xfer->xferUnsignedInt(&color);
                renderObj = Create_Render_Obj(name.str(), scale, color);
                if (renderObj == 0) {
                    bfmeFormatText(&error, 4, 0);
                    _CxxThrowException(&error, (void *)0x011DFE5C);
                }
                disableUVAnimations(renderObj);
                snap = new W3DRenderObjectSnapshot(renderObj, &m_drawableInfo, false);
                if (prev) prev->m_next = snap;
                else m_parentSnapshots[i] = snap;
                prev = snap;
                xfer->xferSnapshot(snap);
                g_012F8058->addRenderObject(snap->m_robj);
            }
        }
    }
    }
    if (m_parentObject && m_parentSnapshots[g_012ED748->localPlayer->playerIndex] && xfer->isLoading())
        removeParentObject();
}
