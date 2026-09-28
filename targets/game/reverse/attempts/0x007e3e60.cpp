// ?upload@YuvUpload007E3E60@@QAEXXZ
// partial score=0.91 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail RVA 0x007E3E60, 1804 bytes. Candidate symbol: ?upload@YuvUpload007E3E60@@QAEXXZ.
// Owner: slot 3 (+0xC) of vtable 0x01128DA8 (ILT 0x000144A7), the class landed as
// Rva007E3C20Vp6Stream; the bank keeps its address-derived YuvUpload007E3E60 view.
// The callee at 0x009A51A0 fills the ten-dword plane descriptor; no pin was added.
// Tables are separate globals written by 0x007E4D40; retail indexes them with the
// raw chroma byte (*u, *v), which is what yields the shared shl-by-2 index.
// Probe 2026-09-28: 1804 vs 1804 bytes, 61 non-relocation byte differences.
// Frame 0x1098 and every stack slot agree. Remaining residue is scheduling only:
// +0x124..+0x153 and +0x45E..+0x47B (retail keeps uvHeight in edx and builds j
// with lea, storing frame.uvHeight after the imul; with j as a user local ours
// stores it first and decrements in place), and the opaque loop-exit reload order
// at +0x65C (retail reloads ebp=this last, ours first).
#include <string.h>
struct PlaneDescriptor007E3E60 {
    int width, height, stride, uvWidth, uvHeight, uvStride;
    unsigned char *y, *u, *v, *allocation;
};
void DecodePlanes009A51A0(void *, PlaneDescriptor007E3E60 *);
void W3DRadarResetLock();
char bfmeUnlock1179();
struct ScopedLock007E3E60 {
    ScopedLock007E3E60() { W3DRadarResetLock(); }
    ~ScopedLock007E3E60() { bfmeUnlock1179(); }
};
// Exact table VAs are 0x01307438..0x01308838, in steps of 0x400.
extern unsigned int g_alpha00F07438[256];
extern int g_vRed00F07838[256];
extern int g_vGreen00F07C38[256];
extern int g_uGreen00F08038[256];
extern int g_uBlue00F08438[256];
extern unsigned int g_clip00F08838[];
// Prefix agrees with W3DVideoBufferCtorBfme.cpp; retail calls lock at slot 0x10
// and unlock at 0x14. Slots 0..0x0c are not invoked by this body.
class Buffer007E3E60 {
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void *lock();
    virtual void unlock();
    unsigned int x, y, width, height, textureWidth, textureHeight;
    int pitch;
    float at20;
    int format;
};
class YuvUpload007E3E60 {
public:
    void upload();
    __forceinline void renderAlpha(PlaneDescriptor007E3E60 &, PlaneDescriptor007E3E60 &, unsigned int *, int);
    __forceinline void renderOpaque(PlaneDescriptor007E3E60 &, unsigned int *, int);
    void *vtable;
    int at04, at08, at0c, at10;
    void *at14, *at18;
    int at1c[4];
    Buffer007E3E60 *at2c;
    int at30, at34;
    bool at38;
    int at3c, at40, at44, at48, at4c;
};
#define RGB007E3E60(Y) (((g_clip00F08838[(Y) + red] << 8) | g_clip00F08838[(Y) + green]) << 8 | g_clip00F08838[(Y) + blue])
#define OPAQUE007E3E60(Y) ((((g_clip00F08838[(Y) + red] | 0xffffff00U) << 8) | g_clip00F08838[(Y) + green]) << 8 | g_clip00F08838[(Y) + blue])
__forceinline void YuvUpload007E3E60::renderAlpha(PlaneDescriptor007E3E60 &frame, PlaneDescriptor007E3E60 &alpha, unsigned int *dest, int pitch) {
    unsigned int row[1024];
        unsigned char *y0 = frame.y + (frame.height - 1) * frame.stride;
        unsigned char *y1 = y0 - frame.stride;
        int j = frame.uvHeight - 1;
        unsigned char *u = frame.u + j * frame.uvStride;
        unsigned char *v = frame.v + j * frame.uvStride;
        unsigned char *a0 = alpha.y + (alpha.height - 1) * alpha.stride;
        unsigned char *a1 = a0 - alpha.stride;
        unsigned char *next = (unsigned char *)dest + pitch;
        unsigned int *temp = row;
        int ystep = -frame.width - 2 * frame.stride;
        int uvstep = -frame.uvWidth - frame.uvStride;
        int astep = -alpha.width - 2 * alpha.stride;
        int dststep = (pitch - 2 * frame.width) * 2;
        for (; j >= 0; --j) {
            for (int i = frame.uvWidth - 1; i >= 0; --i) {
                int blue = g_uBlue00F08438[*u];
                int green = g_uGreen00F08038[*u] + g_vGreen00F07C38[*v];
                int red = g_vRed00F07838[*v];
                ++u; ++v;
                *dest++ = RGB007E3E60(*y0) | g_alpha00F07438[*a0];
                ++y0; ++a0;
                *dest++ = RGB007E3E60(*y0) | g_alpha00F07438[*a0];
                ++y0; ++a0;
                *temp++ = RGB007E3E60(*y1) | g_alpha00F07438[*a1];
                ++y1; ++a1;
                *temp++ = RGB007E3E60(*y1) | g_alpha00F07438[*a1];
                ++y1; ++a1;
            }
            y0 += ystep; y1 += ystep;
            u += uvstep; v += uvstep;
            a0 += astep; a1 += astep;
            dest = (unsigned int *)((unsigned char *)dest + dststep);
            memcpy(next, row, at30 * 4);
            temp = row;
            next += pitch * 2;
        }
 }
__forceinline void YuvUpload007E3E60::renderOpaque(PlaneDescriptor007E3E60 &frame, unsigned int *dest, int pitch) {
    unsigned int row[1024];
        unsigned char *y0 = frame.y + (frame.height - 1) * frame.stride;
        unsigned char *y1 = y0 - frame.stride;
        int j = frame.uvHeight - 1;
        unsigned char *u = frame.u + j * frame.uvStride;
        unsigned char *v = frame.v + j * frame.uvStride;
        unsigned char *next = (unsigned char *)dest + pitch;
        unsigned int *temp = row;
        int ystep = -frame.width - 2 * frame.stride;
        int uvstep = -frame.uvWidth - frame.uvStride;
        int dststep = (pitch - 2 * frame.width) * 2;
        for (; j >= 0; --j) {
            for (int i = frame.uvWidth - 1; i >= 0; --i) {
                int blue = g_uBlue00F08438[*u];
                int green = g_uGreen00F08038[*u] + g_vGreen00F07C38[*v];
                int red = g_vRed00F07838[*v];
                ++u; ++v;
                *dest++ = OPAQUE007E3E60(*y0); ++y0;
                *dest++ = OPAQUE007E3E60(*y0); ++y0;
                *temp++ = OPAQUE007E3E60(*y1); ++y1;
                *temp++ = OPAQUE007E3E60(*y1); ++y1;
            }
            y0 += ystep; y1 += ystep;
            u += uvstep; v += uvstep;
            dest = (unsigned int *)((unsigned char *)dest + dststep);
            memcpy(next, row, at30 * 4);
            temp = row;
            next += pitch * 2;
        }
}
void YuvUpload007E3E60::upload()
{
    if (!at2c || !at14 || (at38 && !at18)) return;
    ScopedLock007E3E60 lock;
    if (at2c->format != 5 && at2c->format != 2) return;
    unsigned int *dest = (unsigned int *)at2c->lock();
    if (!dest) return;
    int pitch = at2c->pitch;
    PlaneDescriptor007E3E60 frame;
    PlaneDescriptor007E3E60 alpha;
    if (at38 && at2c->format == 5) {
        DecodePlanes009A51A0(at14, &frame);
        DecodePlanes009A51A0(at18, &alpha);
        frame.width = at30; frame.height = at34;
        frame.uvWidth = at30 >> 1; frame.uvHeight = at34 >> 1;
        alpha.width = at30; alpha.height = at34;
        alpha.uvWidth = at30 >> 1; alpha.uvHeight = at34 >> 1;
        renderAlpha(frame, alpha, dest, pitch);
    } else {
        DecodePlanes009A51A0(at14, &frame);
        frame.width = at30; frame.height = at34;
        frame.uvWidth = at30 >> 1; frame.uvHeight = at34 >> 1;
        renderOpaque(frame, dest, pitch);
    }
    at2c->unlock();
    at4c = at48;
}
