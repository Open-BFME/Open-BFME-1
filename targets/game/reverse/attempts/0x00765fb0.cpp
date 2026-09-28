// ?rva00765FB0@Rva0076C080@@QAEXPAUState00765FB0@@M_N11@Z
// partial score=0.88 date=2026-09-28
// ?advanceAnimation@Rva0076C080@@QAEXXZ
// cl: /O2 /Ob2 /DNDEBUG /MD /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
// BFME model-draw animation step (Zero Hour twin: the animation half of W3DModelDraw::doDrawModule).
// Distance fade, per-track frame advance and the transition/idle restart; owner layout is address-derived.
#include "wwmath.h"
#include "ww3d.h"
#include <stddef.h>
#pragma intrinsic(sqrt, fabs)
typedef unsigned int U32;
struct Coord0076C080 { float x,y,z; };
class Render0076C080 { public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual int classID();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
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
    virtual void opacity(float);
    virtual void slot60();
    virtual void slot64();
    virtual void slot68();
    virtual void slot6C();
    virtual void slot70();
    virtual void slot74();
    virtual void slot78();
    virtual void slot7C();
    virtual void slot80();
    virtual void slot84();
    virtual void slot88();
    virtual void slot8C();
    virtual void slot90();
    virtual void slot94();
    virtual void slot98();
    virtual void slot9C();
    virtual void slotA0();
    virtual void slotA4();
    virtual void slotA8();
    virtual void slotAC();
    virtual void slotB0();
    virtual void slotB4();
    virtual void slotB8();
    virtual void slotBC();
    virtual void slotC0();
    virtual void slotC4();
    virtual void slotC8();
    virtual void slotCC();
    virtual void slotD0();
    virtual void slotD4();
    virtual void slotD8();
    virtual void slotDC();
    virtual void slotE0();
    virtual void slotE4();
    virtual void slotE8();
    virtual void slotEC();
    virtual void slotF0();
    virtual void slotF4();
    virtual void slotF8();
    virtual void slotFC();
    virtual void slot100();
    virtual void slot104();
    virtual void slot108();
    virtual void slot10C();
    virtual void slot110();
    virtual void slot114();
    virtual void slot118();
    virtual void slot11C();
    virtual void slot120();
    virtual void slot124();
    virtual void slot128();
    virtual void slot12C();
    virtual void slot130();
    virtual void slot134();
    virtual void slot138();
    virtual void slot13C();
    virtual void slot140();
    virtual void slot144();
    virtual void slot148();
    virtual void slot14C();
    virtual void slot150();
    virtual void slot154();
    virtual void slot158();
    virtual void slot15C();
    virtual void slot160();
    virtual void slot164();
    virtual void slot168();
    virtual void slot16C();
    virtual void slot170();
    virtual void slot174();
    virtual void slot178();
    virtual void slot17C();
    virtual void slot180();
    virtual void slot184();
    virtual void slot188();
    virtual void slot18C();
    virtual void hidden(int);
};
class Anim0076C080 { public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual int frames();
    virtual float rate();
};
class View0076C080 { public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
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
    virtual void slot68();
    virtual void slot6C();
    virtual void slot70();
    virtual void slot74();
    virtual void slot78();
    virtual void slot7C();
    virtual void slot80();
    virtual void slot84();
    virtual void slot88();
    virtual void slot8C();
    virtual void slot90();
    virtual void slot94();
    virtual void slot98();
    virtual void slot9C();
    virtual void slotA0();
    virtual void slotA4();
    virtual void slotA8();
    virtual void slotAC();
    virtual void slotB0();
    virtual void slotB4();
    virtual void slotB8();
    virtual void slotBC();
    virtual void slotC0();
    virtual void slotC4();
    virtual void slotC8();
    virtual void slotCC();
    virtual void slotD0();
    virtual void slotD4();
    virtual void slotD8();
    virtual void slotDC();
    virtual void slotE0();
    virtual void slotE4();
    virtual void slotE8();
    virtual void slotEC();
    virtual void slotF0();
    virtual void slotF4();
    virtual void slotF8();
    virtual void slotFC();
    virtual void slot100();
    virtual void slot104();
    virtual void slot108();
    virtual void slot10C();
    virtual void slot110();
    virtual void slot114();
    virtual const Coord0076C080* position();
};
class Interface0076C080 { public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
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
    virtual void slot68();
    virtual void pause(bool);
};

struct Coord3D;
class BFMERopeDrawableGetPositionShim { public: const Coord3D* get() const; };
class BfmeThing923B { public: void bfmeGo923B(char); };
class Gen_004181B0 { public: bool bfmeAllows(bool) const; };
class BfmeHostESC { public: void bfmeSendESC(void*,int); };
class Gen_00208330 { public: unsigned char bfmeAny() const; };
struct BfmeRecord6BE90;
class BfmeRecordHook6BE90 { public: void bfmeSelect6BE90(BfmeRecord6BE90*,int,int); };
struct State0076C080;
template<int N> class BitFlags;
struct RvaModelConditionInfo;
class RvaModuleData { public: const RvaModelConditionInfo* findByCondition(const BitFlags<117>&) const; };
struct Data0076C080 {
    unsigned char pad00[0x6a]; bool b6a;
    unsigned char pad6b[0x118-0x6b];
    float f118,f11c,f120; unsigned char pad124[8]; int i12c;
};
struct Track0076C080 {
    Anim0076C080* p00;
    float f04,f08,f0c;
    int i10,i14;
    bool b18,b19;
};
struct Info0076C080 {
    unsigned char pad00[0x2c]; float f2c,f30; bool b34;
};
struct State0076C080 {
    unsigned char pad00[0x2c]; Info0076C080* p2c;
    unsigned char pad30[8]; U32 u38;
};

// ---- retail 0x00765FB0: declarations the animation-selection body needs ----
template<class T> struct StringData00765FB0 { int refCount; unsigned short length, capacity; T text[1]; };
template<class T> class StringBase {
public:
    StringBase() : m_data(0) {}
    ~StringBase() { releaseBuffer(); }
    void set(const StringBase &other);
    bool isNotEmpty() const;
    int compareNoCase(const StringBase &other) const;
    bool isEmpty() const { return m_data == 0 || m_data->length == 0; }
    int getLength() const { return m_data ? m_data->length : 0; }
    const T *str() const { return m_data ? m_data->text : (const T *)""; }
private:
    void releaseBuffer();
    StringData00765FB0<T> *m_data;
};
class AsciiString : public StringBase<char> {
public:
    AsciiString() {}
    ~AsciiString() {}
};

class HAnimClass { public:
    virtual void Delete_This();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual int Get_Num_Frames();
    int NumRefs;
};

// One 0x38-byte animation record of a model state.
class Rva007657F0 { public:
    HAnimClass *resolve(const AsciiString &model, bool variant, int index);
    AsciiString m_name;             // +0x00
    AsciiString m_04;
    unsigned char pad08[8];
    float f10;
    int i14;
    int i18;
    float f1c, f20;
    bool b24, b25;
    unsigned char pad26[0x38-0x26];
};
struct Anims00765FB0 {
    Rva007657F0 *m_begin, *m_end;
    unsigned int size() const { return m_end - m_begin; }
};
struct State00765FB0 {
    AsciiString m_name;             // +0x00
    unsigned char pad04[0x2c-4];
    Anims00765FB0 m_animations;     // +0x2C
    unsigned char pad34[4];
    U32 u38;
    unsigned char pad3c[0x48-0x3c];
    AsciiString m_48;
    int i4c;
    unsigned char pad50[0x6c-0x50];
    bool b6c;
};
class Rva00765AC0 { public: unsigned char ready() const; };
class Gen_0075F090 { public: int bfmeValue() const; int rva0075F0E0(int avoid, int limit) const; };
struct Entry00765FB0 { AsciiString m_name; unsigned char pad[0xbc-4]; };
struct Data00765FB0 {
    unsigned char pad00[0x24];
    Entry00765FB0 *m_begin, *m_end;
    unsigned char pad2c[0x108-0x2c];
    bool b108, b109;
};
struct Owner00765FB0 { unsigned char pad00[0x34]; AsciiString m_34; };
class Object00765FB0;
struct Drawable00765FB0 {
    unsigned char pad00[0xfc]; Object00765FB0 *m_fc;
    unsigned char pad100[0x110-0x100]; U32 u110;
};
class AssistedTargetingObjectShim { public: void *find(int); };
enum WeaponStatus { WEAPON_STATUS_3 = 3 };
class Rva0076C080;
class Weapon {
    friend class Rva0076C080;
    WeaponStatus bfmeComputeStatus(bool *) const;
};
class Rva001E18A0 { public: int difference() const; };
class BfmeThing941B { public: int bfmeGo941B(void *, void *); };
class Rva001E6F10Weapon { public: int delay00013818(Object00765FB0 *, int, int); };
#pragma comment(linker, "/alternatename:?delay00013818@Rva001E6F10Weapon@@QAEHPAVObject00765FB0@@HH@Z=?j_00013818@@YAXXZ")
struct Rva002E4470Context;
class Rva002E4470Owner { public: AsciiString run(const char *, unsigned long, Rva002E4470Context *); };
extern Rva002E4470Owner *g_bfmeOwnerBR;
class Gen_00762E10 { public:
    Gen_00762E10(void *drawable) : m_drawable(drawable), m_10(0.0f), m_14(false) {}
    ~Gen_00762E10();
    AsciiString m_00, m_04, m_08;
    void *m_drawable;
    float m_10;
    bool m_14;
};
class BfmeHostYB { public: void bfmeResetYB(int); };
class Rva0075C990 { public: bool test(); };
struct State0076B800;
class Select0076B800 { public: bool select(State0076B800 *, bool, int); };
class Obj0075B520;
int rva0075b520(Obj0075B520 *, int);
int lod0075B4A0(void *, int);
#pragma comment(linker, "/alternatename:?lod0075B4A0@@YAHPAXH@Z=?j_00004f4d@@YAXXZ")
class Draw00765FB0 { public:
    int randomFrame0075CE50(int frames);
    void play00760660(HAnimClass *, int, int, int, float, float, int, float);
};
#pragma comment(linker, "/alternatename:?randomFrame0075CE50@Draw00765FB0@@QAEHH@Z=?j_000494f9@@YAXXZ")
#pragma comment(linker, "/alternatename:?play00760660@Draw00765FB0@@QAEXPAVHAnimClass@@HHHMMHM@Z=?j_00017364@@YAXXZ")
float GetGameClientRandomValueReal(float, float, char *, int);
extern char g_bfmeTag1028[];
class DrawVirtuals00765FB0 { public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
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
    virtual void slot68();
    virtual void slot6C();
    virtual void slot70();
    virtual void slot74();
    virtual void slot78();
    virtual void slot7C();
    virtual void slot80();
    virtual void slot84();
    virtual void slot88();
    virtual void slot8C();
    virtual void slot90();
    virtual void slot94();
    virtual void slot98();
    virtual void slot9C();
    virtual void slotA0();
    virtual void slotA4();
    virtual void slotA8();
    virtual void slotAC();
    virtual void slotB0();
    virtual void slotB4();
    virtual void slotB8();
    virtual void slotBC();
    virtual void slotC0();
    virtual void slotC4();
    virtual void slotC8();
    virtual void slotCC();
    virtual void slotD0();
    virtual void slotD4();
    virtual void slotD8();
    virtual void slotDC();
    virtual void slotE0();
    virtual void slotE4();
    virtual void slotE8();
    virtual void slotEC();
    virtual void slotF0();
    virtual void slotF4();
    virtual int vf8();
    virtual int vfc(int);
};
class View;
class GameLODManager;
extern View* TheTacticalView;
extern GameLODManager* TheGameLODManager;
extern int g_Va012F8064;
float minf(float,float);
float maxf(float,float);
class Rva0076C080;
class Rva00766A70W3DScriptedModelDraw {
    friend class Rva0076C080;
    void apply(void *model, int value, int from, int to, int flags);
};
void b_00762900();
typedef void (__fastcall *Finish0076C080)(Rva0076C080*);
class Rva0076C080 {
public:
    void advanceAnimation();
    void finish();
    void rva00765FB0(State00765FB0 *prev, float prevFraction, bool keepFrame, bool useFraction, bool restart);
    int vf8() { return ((DrawVirtuals00765FB0 *)this)->vf8(); }
    int vfc(int frames) { return ((DrawVirtuals00765FB0 *)this)->vfc(frames); }
    unsigned char pad00[4]; Data0076C080* p04; void* p08;
    Interface0076C080 secondary;
    void* p10; State0076C080* p14;
    unsigned char pad18[0x10]; int i28;
    unsigned char pad2c[8]; Render0076C080* p34;
    unsigned char pad38[0x6c-0x38]; int i6c;
    unsigned char pad70[4]; float f74,f78,f7c,f80;
    unsigned char pad84[0x9c-0x84]; U32 u9c; int ia0;
    unsigned char pada4[0xdc-0xa4]; Track0076C080 tracks[3];
    unsigned char pad130[0x148-0x130]; U32 u148[4];
    unsigned char pad158[0x173-0x158]; bool b173; U32 u174;
    unsigned char pad178[0x1fc-0x178]; bool b1fc;
    unsigned char pad1fd[0x230-0x1fd]; bool b230,b231;
};
inline void Rva0076C080::finish() { ((Finish0076C080)&b_00762900)(this); }
inline bool testFlagBit0076C080(U32 flags, int bit) { return ((flags>>bit)&1)!=0; }
// ?complete0075B980@@YA_NPAVRender0076C080@@ABUTrack0076C080@@_N@Z
static bool complete0075B980(Render0076C080* r, const Track0076C080& t, bool flag)
{
    if (r && r->classID()==25 && t.p00) {
        switch (t.i10) {
        case 0: case 1: case 3: case 5: if (flag) return t.b18; return false;
        case 2: if (t.p00->frames()-1.0f <= t.f04) break; return false;
        case 6: if (t.f04 <= 0.0f) break; return false;
        }
    }
    return true;
}
// ?advanceAnimation@Rva0076C080@@QAEXXZ
void Rva0076C080::advanceAnimation()
{
    if (!p34 || !p14) return;
    const Data0076C080* d=p04;
    *((bool*)p34+0xc4)=false;
    if (b231 && d->f120 < 1.0f) {
        Coord0076C080 camera;
        const Coord0076C080* cameraPtr=((View0076C080*)TheTacticalView)->position();
        camera.x=cameraPtr->x; camera.y=cameraPtr->y;
        float cx=camera.x, cy=camera.y;
        const Coord0076C080* pos=(const Coord0076C080*)((BFMERopeDrawableGetPositionShim*)p08)->get();
        float dx=cx-pos->x,dy=cy-pos->y;
        float dist=dx*dx+dy*dy;
        if (dist >= d->f118*d->f118) {
            ((BfmeThing923B*)p08)->bfmeGo923B(1);
            p34->hidden(0);
            p34->opacity(1.0f);
            if (d->i12c>=0) *(int*)((char*)p34+0xa0)=0;
        } else {
            float opacity;
            if (dist <= d->f11c*d->f11c) opacity=d->f120;
            else {
                float distance=WWMath::Sqrt(dist);
                float a=distance-d->f11c;
                float b=d->f118-d->f11c;
                opacity=((b-a)*d->f120+a)/b;
            }
            if (TheGameLODManager && *(int*)((char*)TheGameLODManager+0x16c4)<=1) {
                ((BfmeThing923B*)p08)->bfmeGo923B(0);
                p34->hidden(1);
                if (d->i12c>=0) *(int*)((char*)p34+0xa0)=0;
            } else {
                if (opacity>0.0f) {
                    ((BfmeThing923B*)p08)->bfmeGo923B(1);
                    p34->hidden(0);
                } else {
                    ((BfmeThing923B*)p08)->bfmeGo923B(0);
                    p34->hidden(1);
                }
                p34->opacity(opacity);
                *((bool*)p34+0xc4)=true;
                if (d->i12c>=0) *(int*)((char*)p34+0xa0)=d->i12c;
            }
        }
    }
    if (!tracks[0].p00 && !tracks[1].p00) {
        if (b173) {
            State0076C080* next=(State0076C080*)((const RvaModuleData*)d)->findByCondition(*(const BitFlags<117>*)u148);
            if (next) {
                b230=false;
                ((BfmeRecordHook6BE90*)this)->bfmeSelect6BE90((BfmeRecord6BE90*)next,0,0);
            }
            u174=0;
            b173=false;
        }
        return;
    }
    U32 now=g_Va012F8064;
    U32 elapsed=now-u9c;
    u9c=now;
    if (b1fc) {
        b1fc=false;
        elapsed=WW3D::Get_Frame_Time();
    }
    Gen_004181B0* drawable=(Gen_004181B0*)p08;
    secondary.pause(!drawable->bfmeAllows(d->b6a));
    if (!tracks[0].p00 && tracks[1].p00) {
        ((BfmeHostESC*)this)->bfmeSendESC(0,1);
        if (tracks[2].p00) {
            ((BfmeHostESC*)this)->bfmeSendESC((void*)1,2);
            float blend=tracks[1].f0c;
            if (blend>0.0f) f74=f78=maxf(1.0f,minf(blend,tracks[1].p00->frames()-1.0f));
            else f74=f78=maxf(1.0f,minf(5.0f,tracks[1].p00->frames()-1.0f));
        }
    }
    for (int i=0;i<3;++i) {
        Track0076C080& t=tracks[i];
        if (t.p00) {
            float delta=t.p00->rate()*f80*f7c*elapsed*0.001f;
            float last=t.p00->frames()-1.0f;
            t.f08=t.f04;
            t.b18=false;
            switch(t.i10) {
            case 1:
                t.f04+=delta;
                if (t.f04>last) { int loops=(int)(t.f04/last); t.f04-=loops*last; t.b18=true; }
                break;
            case 2:
                t.f04+=delta;
                if (t.f04>last) { t.f04=last; t.b18=true; }
                break;
            case 3:
                t.f04+=t.i14*delta;
                if (t.i14==1) {
                    if (t.f04>last) { int loops=(int)(t.f04/last); float wrapped=loops*last; t.f04=(wrapped+last)-t.f04; t.i14=-1; t.b18=true; }
                } else if (t.f04<0.0f) {
                    int loops=(int)(fabs(t.f04)/last);
                    if (loops>0) t.f04=loops*last+t.f04;
                    t.i14=1; t.f04=-t.f04; t.b18=true;
                }
                break;
            case 5:
                t.f04-=delta;
                if (t.f04<0.0f) { int loops=(int)(fabs(t.f04)/last); float wrapped=loops*last; t.f04=t.f04+(wrapped+last); t.b18=true; }
                break;
            case 6:
                t.f04-=delta;
                if (t.f04<0.0f) { t.f04=0.0f; t.b18=true; }
                break;
            }
        }
    }
    if (tracks[0].p00 && tracks[1].p00) {
        f74-=tracks[1].p00->rate()*f80*f7c*elapsed*0.001f;
        if (f74<0.0f) {
            ((BfmeHostESC*)this)->bfmeSendESC(0,1);
            if (tracks[2].p00) {
                ((BfmeHostESC*)this)->bfmeSendESC((void*)1,2);
                float blend=tracks[1].f0c;
                if (blend>0.0f) f74=f78=maxf(1.0f,minf(blend,tracks[1].p00->frames()-1.0f));
                else f74=f78=maxf(1.0f,minf(5.0f,tracks[1].p00->frames()-1.0f));
            } else f74=0.0f;
        }
    }
    if (!tracks[0].p00 || !tracks[1].p00) {
        if (complete0075B980(p34,tracks[0],b173) && p34 && p14 && i28!=-1) {
            const State0076C080* state=p14;
            if (b173) {
                State0076C080* next=(State0076C080*)((const RvaModuleData*)d)->findByCondition(*(const BitFlags<117>*)u148);
                if (next) {
                    u174=0;
                    b230=false;
                    ((BfmeRecordHook6BE90*)this)->bfmeSelect6BE90((BfmeRecord6BE90*)next,0,0);
                    if (!u174) b173=false;
                    return;
                }
                u174=0;
                b173=false;
            }
            if (!((Gen_00208330*)((char*)state+4))->bfmeAny())
                reinterpret_cast<Rva00766A70W3DScriptedModelDraw*>(this)->apply((void*)state,(int)0xBF800000,0,0,0);
            else if (testFlagBit0076C080(state->u38,5))
                reinterpret_cast<Rva00766A70W3DScriptedModelDraw*>(this)->apply((void*)state,(int)0xBF800000,0,0,0);
        }
    }
    const Info0076C080* info=p14->p2c+i28;
    if (info && info->f2c>0.0f && info->f30>info->f2c && tracks[0].p00) {
        float frame=tracks[0].f04;
        float end=info->f30>tracks[0].p00->frames() ? (float)tracks[0].p00->frames() : info->f30;
        float opacity;
        if (frame<info->f2c) opacity=info->b34?0.0f:1.0f;
        else if (frame>end) opacity=info->b34?1.0f:0.0f;
        else {
            float ratio=(frame-info->f2c)/(end-info->f2c);
            opacity=info->b34?ratio:1.0f-ratio;
        }
        if (opacity>0.0f) { ((BfmeThing923B*)p08)->bfmeGo923B(1); p34->hidden(0); }
        else { ((BfmeThing923B*)p08)->bfmeGo923B(0); p34->hidden(1); }
        p34->opacity(opacity);
    }
    finish();
}

// Retail 0x00765FB0 (2190 B), reached through ILT 0x00001CA8 from update
// (0x00766A70), select (0x0076B800) and advanceAnimation above. The BFME
// expansion of Zero Hour's W3DModelDraw::adjustAnimation: an optional Lua
// selection script, the idle-anim choice, the handle fallback and the
// start-frame/speed setup. It lives here because complete0075B980 is this
// file's static helper.
void Rva0076C080::rva00765FB0(State00765FB0 *prev, float prevFraction, bool keepFrame, bool useFraction, bool restart)
{
    if (!p14 || !p10) return;
    Object00765FB0 *object = ((Drawable00765FB0 *)p08)->m_fc;
    Data00765FB0 *data = (Data00765FB0 *)p04;
    State00765FB0 *state = (State00765FB0 *)p14;
    bool hasScript = !state->m_48.isEmpty();
    int prevIndex = i28;
    if (restart) {
        prevIndex = -1;
        prev = 0;
        i6c = 0;
    }
    int numAnims = state->m_animations.size();
    if (numAnims <= 0 && !hasScript) {
        if (p34) {
            ((BfmeHostYB *)this)->bfmeResetYB(0);
            ((BfmeHostYB *)this)->bfmeResetYB(1);
            p34->slotB4();
        }
        i28 = -1;
        return;
    }
    if (!keepFrame) {
        if (p34 && numAnims == 0) {
            ((BfmeHostYB *)this)->bfmeResetYB(0);
            ((BfmeHostYB *)this)->bfmeResetYB(1);
            p34->slotB4();
        }
        i28 = -1;
        if (hasScript) {
            Gen_00762E10 context(p08);
            if (prev) {
                if (prevIndex >= 0 && prevIndex < numAnims)
                    context.m_08.set(prev->m_animations.m_begin[prevIndex].m_04);
                if (prev != (State00765FB0 *)p14)
                    context.m_00.set(prev->m_name);
            }
            context.m_10 = prevFraction;
            State00765FB0 *cur = (State00765FB0 *)p14;
            AsciiString result = g_bfmeOwnerBR->run(cur->m_48.str(), cur->m_48.getLength(), (Rva002E4470Context *)&context);
            if (b173 && context.m_04.isNotEmpty()) {
                b173 = false;
                u174 = 0;
            }
            if (context.m_04.isNotEmpty() && !b173) {
                for (Entry00765FB0 *entry = data->m_begin; entry != data->m_end; ++entry) {
                    if (entry->m_name.compareNoCase(context.m_04) == 0) {
                        u174 = (U32)p14;
                        b173 = true;
                        b230 = false;
                        ((Select0076B800 *)this)->select((State0076B800 *)entry, false, 0);
                        return;
                    }
                }
            }
            Track0076C080 *track = tracks[1].p00 ? &tracks[1] : &tracks[0];
            if (prev && context.m_14) {
                bool done = complete0075B980(p34, *track, false);
                if (!done) {
                    b173 = true;
                    u174 = (U32)p14;
                    track->b18 = done;
                    p14 = (State0076C080 *)prev;
                    i28 = 0;
                    return;
                }
            }
            if (!result.isEmpty()) {
                int found = -1;
                for (int i = 0; i < numAnims; ++i) {
                    if (((State00765FB0 *)p14)->m_animations.m_begin[i].m_name.compareNoCase(result) == 0) {
                        found = i;
                        break;
                    }
                }
                if (found == -1) i28 = 0;
                else i28 = found;
            }
        }
        if (numAnims < 1) {
            i28 = -1;
            return;
        }
        if (numAnims == 1)
            i28 = 0;
        else if (b230 && numAnims > 1)
            i28 = (prevIndex + 1) % numAnims;
        else if (i28 < 0) {
            int avoid = -1;
            if (prev == (State00765FB0 *)p14) avoid = prevIndex;
            int limit = vf8();
            if (((Rva00765AC0 *)p14)->ready()) limit = 9999;
            i28 = ((Gen_0075F090 *)p14)->rva0075F0E0(avoid, limit);
        }
    }

    State00765FB0 *cur = (State00765FB0 *)p14;
    Rva007657F0 *info = &cur->m_animations.m_begin[i28];
    if (!useFraction && !keepFrame && prev == cur && !cur->b6c && i28 == prevIndex) {
        if (((Rva0075C990 *)this)->test()) return;
        if (!complete0075B980(p34, tracks[0], false)) return;
        if (((Gen_00208330 *)((char *)p14 + 4))->bfmeAny()) return;
    }

    HAnimClass *anim;
    Owner00765FB0 *owner = (Owner00765FB0 *)p10;
    if (data->b109)
        anim = ((State00765FB0 *)p14)->m_animations.m_begin[i28].resolve(owner->m_34, true, lod0075B4A0(p08, 0));
    else if (data->b108)
        anim = ((State00765FB0 *)p14)->m_animations.m_begin[i28].resolve(owner->m_34, true,
            (p08 && (((Drawable00765FB0 *)p08)->u110 & 0x20)) ? 2 : ia0);
    else
        anim = ((State00765FB0 *)p14)->m_animations.m_begin[i28].resolve(owner->m_34, false, 0);
    if (!anim) {
        if (((State00765FB0 *)p14)->m_animations.size() > 1) {
            for (unsigned int i = 0; i < ((State00765FB0 *)p14)->m_animations.size(); ++i) {
                if (i == (unsigned int)i28) continue;
                if (data->b109)
                    anim = ((State00765FB0 *)p14)->m_animations.m_begin[i].resolve(owner->m_34, true, lod0075B4A0(p08, 0));
                else if (data->b108)
                    anim = ((State00765FB0 *)p14)->m_animations.m_begin[i].resolve(owner->m_34, true, rva0075b520((Obj0075B520 *)p08, ia0));
                else
                    anim = ((State00765FB0 *)p14)->m_animations.m_begin[i].resolve(owner->m_34, false, 0);
                if (anim) {
                    i28 = i;
                    break;
                }
            }
        }
    }
    i6c = i28;
    if (!anim) return;

    int startFrame = 0;
    int direction = 1;
    if (keepFrame) {
        startFrame = (int)tracks[0].f04;
        direction = tracks[0].i14;
    } else {
        State00765FB0 *s = (State00765FB0 *)p14;
        if ((s->m_animations.m_begin != s->m_animations.m_end && s->i4c >= 0 && s->m_animations.m_begin[s->i4c].i14 == 6)
            || ((Gen_0075F090 *)s)->bfmeValue() == 5) {
            startFrame = anim->Get_Num_Frames() - 1;
            direction = -1;
        }
        if (useFraction && prevFraction >= 0.0) {
            startFrame = (int)(anim->Get_Num_Frames() * prevFraction);
        } else {
            State00765FB0 *c = (State00765FB0 *)p14;
            if (testFlagBit0076C080(c->u38, 0)) {
                if (((Rva00765AC0 *)c)->ready() && *(int *)((char *)TheGameLODManager + 0x170c) > 0)
                    startFrame = ((Draw00765FB0 *)this)->randomFrame0075CE50(anim->Get_Num_Frames());
                else
                    startFrame = vfc(anim->Get_Num_Frames());
            } else if (testFlagBit0076C080(c->u38, 1)) {
                startFrame = 0;
            } else if (testFlagBit0076C080(c->u38, 2)) {
                startFrame = anim->Get_Num_Frames() - 1;
            } else if ((c->u38 & 0x1d0) && prev && prev != c && (prev->u38 & 0x1d0)
                    && ((prev->u38 & c->u38) & 0x1d0) && prevFraction >= 0.0) {
                startFrame = (int)(anim->Get_Num_Frames() * prevFraction);
            }
        }
    }

    float speed = 1.0f;
    if (info->f1c != 1.0f || info->f20 != 1.0f)
        speed = GetGameClientRandomValueReal(info->f1c, info->f20, g_bfmeTag1028, 3995);
    if (info->b25 && object) {
        void *weapon = ((AssistedTargetingObjectShim *)object)->find(0);
        if (weapon) {
            int duration = (int)(info->f10 * 0.005f);
            int total;
            if (((Weapon *)weapon)->bfmeComputeStatus(0) == WEAPON_STATUS_3)
                total = ((Rva001E18A0 *)weapon)->difference();
            else
                total = ((Rva001E6F10Weapon *)weapon)->delay00013818(object, 0, 0)
                    + ((BfmeThing941B *)weapon)->bfmeGo941B(object, 0);
            speed = (float)duration / (float)total;
        }
    }
    int loops = info->i18;
    int mode = info->i14;
    if (b230) {
        speed = 1.0f;
        startFrame = 0;
        loops = 0;
        if (mode == 2 && numAnims == 1) mode = 1;
    }
    float frame = (float)startFrame;
    ((Draw00765FB0 *)this)->play00760660(anim, info->b24, mode, loops, frame,
        (float)direction * -0.00001f + frame, 0, speed);
    if (--anim->NumRefs == 0)
        anim->Delete_This();
}

// Compile-time checks of the retail storage view (not semantic member names).
typedef char CheckTrackSize0076C080[sizeof(Track0076C080)==0x1c?1:-1];
typedef char CheckInfoSize0076C080[sizeof(Info0076C080)==0x38?1:-1];
typedef char CheckRender0076C080[offsetof(Rva0076C080,p34)==0x34?1:-1];
typedef char CheckTracks0076C080[offsetof(Rva0076C080,tracks)==0xdc?1:-1];
typedef char CheckFlags0076C080[offsetof(Rva0076C080,u148)==0x148?1:-1];
typedef char CheckTransition0076C080[offsetof(Rva0076C080,b173)==0x173?1:-1];
typedef char CheckSync0076C080[offsetof(Rva0076C080,b1fc)==0x1fc?1:-1];
typedef char CheckTail0076C080[offsetof(Rva0076C080,b231)==0x231?1:-1];
