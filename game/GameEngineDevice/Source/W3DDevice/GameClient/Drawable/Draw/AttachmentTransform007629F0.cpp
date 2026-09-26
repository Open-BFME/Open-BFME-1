// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
// RVA 007629F0: thiscall(Matrix3D&), ret4, frame30. Hub0077B3F0+281
// proves the writable matrix and primary receiver; see its analyst report.
// ZH adjustTransformMtx supplies the attachment and height paths. BFME adds
// parent attachment, angle adjustment and the frame-based matrix blend.
#include "matrix3d.h"
#include "ascii_string.h"
#include <stddef.h>

// Retail expands both accessors: the canonical Header has a 16-bit length
// at +4 and its characters at +8. Keep the canonical class and layout.
template <> inline const char *StringBase<char>::str() const {
    return m_data ? m_data->data : "";
}
template <> inline bool StringBase<char>::isNotEmpty() const {
    return m_data && m_data->length != 0;
}

class GeometryInfo { public: float getMaxHeightAbovePosition() const; };
class BfmeHostYA { public: float bfmeGetYA(); }; // Checked landed 001C3460 ABI.
struct ObjectFields007629F0;
class Drawable {
public:
    bool getCurrentWorldspaceClientBonePositions(const char *, Matrix3D &) const;
    char unknown00[0xFC];
    ObjectFields007629F0 *m_object;
};
#define SLOT(n) virtual void slot##n();
#define SLOTS00_1C SLOT(00) SLOT(04) SLOT(08) SLOT(0C) SLOT(10) SLOT(14) SLOT(18) SLOT(1C)
#define SLOTS20_3C SLOT(20) SLOT(24) SLOT(28) SLOT(2C) SLOT(30) SLOT(34) SLOT(38) SLOT(3C)
#define SLOTS40_5C SLOT(40) SLOT(44) SLOT(48) SLOT(4C) SLOT(50) SLOT(54) SLOT(58) SLOT(5C)
#define SLOTS60_7C SLOT(60) SLOT(64) SLOT(68) SLOT(6C) SLOT(70) SLOT(74) SLOT(78) SLOT(7C)
#define SLOTS80_9C SLOT(80) SLOT(84) SLOT(88) SLOT(8C) SLOT(90) SLOT(94) SLOT(98) SLOT(9C)
class Client007629F0 {
public:
    SLOTS00_1C SLOT(20) SLOT(24) SLOT(28)
    virtual Drawable *slot2C(unsigned int);
    SLOT(30) SLOT(34) SLOT(38) SLOT(3C) SLOTS40_5C SLOT(60) SLOT(64)
    virtual unsigned int slot68();
};
class Contain007629F0 {
public:
    SLOTS00_1C SLOTS20_3C SLOTS40_5C SLOTS60_7C SLOTS80_9C
    virtual bool slotA0();
};
struct ObjectFields007629F0 {
    char unknown00[0x1FC];
    Contain007629F0 *m_contain;
    Contain007629F0 *contain() const { return m_contain; }
    char unknown200[0x20];
    float value220;
    float buildRate() { return reinterpret_cast<BfmeHostYA *>(this)->bfmeGetYA(); }
    const GeometryInfo &geometry() const { return *reinterpret_cast<const GeometryInfo *>((const char *)this + 0xAC); }
};
struct Engine007629F0 { char unknown00[0x30]; int mode30; int unknown34; float value38; };
extern Client007629F0 *ClientGlobal007629F0;
extern Engine007629F0 *EngineGlobal007629F0;
extern int AttachmentFailures007629F0;
void stepAngleToward(float *, float);
struct State007629F0 { char unknown00[0x38]; unsigned flags38; };
struct Data007629F0 { char unknown00[0x40]; AsciiString AttachToBoneInAnotherModule; };
class AttachmentTransform007629F0 {
public:
    void adjust(Matrix3D &);
    bool angle0075F210(float *); // Independent full helper: ECX input; ret4; AL success; writes *arg at +146.
    char unknown00[4];
    const Data007629F0 *data04;
    Drawable *drawable08;
    char unknown0C[8];
    State007629F0 *m_curState;
    char unknown18[0x70-0x18];
    float angle70;
    char unknown74[0x88-0x74];
    unsigned int parentID88;
    char unknown8C[0x98-0x8C];
    AsciiString bone98;
    char unknown9C[0x20C-0x9C];
    float value20C;
    char unknown210[0x234-0x210];
    Matrix3D matrix234;
    float blend264;
    unsigned int frame268;
};
typedef char AttachmentMatrixOffset007629F0[offsetof(AttachmentTransform007629F0, matrix234) == 0x234 ? 1 : -1];
typedef char AttachmentBoneOffset007629F0[offsetof(AttachmentTransform007629F0, bone98) == 0x98 ? 1 : -1];

void AttachmentTransform007629F0::adjust(Matrix3D &mtx)
{
    if (parentID88) {
        Drawable *parent = ClientGlobal007629F0->slot2C(parentID88);
        if (parent) {
            ObjectFields007629F0 *object = parent->m_object;
            Matrix3D boneMtx;
            if (parent->getCurrentWorldspaceClientBonePositions(bone98.str(), boneMtx)) {
                mtx = boneMtx;
                if (object->contain() && object->contain()->slotA0()) {
                    float angle = mtx.Get_Z_Rotation();
                    if (!angle0075F210(&angle)) {
                        stepAngleToward(&angle70, angle);
                        angle = angle70 - angle;
                    }
                    mtx.Rotate_Z(angle);
                }
                return;
            }
            if (AttachmentFailures007629F0 < 100) ++AttachmentFailures007629F0;
        }
    }
    const Data007629F0 *d = data04;
    if (d->AttachToBoneInAnotherModule.isNotEmpty()) {
        Matrix3D boneMtx;
        if (drawable08->getCurrentWorldspaceClientBonePositions(d->AttachToBoneInAnotherModule.str(), boneMtx))
            mtx = boneMtx;
    }
    if (blend264 < 1.0f) {
        if (frame268 < ClientGlobal007629F0->slot68()) {
            frame268 = ClientGlobal007629F0->slot68();
            blend264 += 1.0f / 30.0f;
            if (blend264 > 1.0f) blend264 = 1.0f;
        }
        Matrix3D::Lerp(matrix234, mtx, blend264, mtx);
    } else {
        blend264 = 1.0f;
        frame268 = ~0u;
    }
    if (m_curState && (m_curState->flags38 & 8)) {
        ObjectFields007629F0 *object = drawable08->m_object;
        if (object) {
            if (EngineGlobal007629F0->mode30 == 1) value20C = object->value220;
            if (value20C >= 0.0f) {
                float pct = object->buildRate() * EngineGlobal007629F0->value38 + value20C;
                float height = object->geometry().getMaxHeightAbovePosition();
                mtx.Translate_Z(height * pct * 0.01f - height);
            }
        }
    }
}
