// ?d_0076c080@@YAXXZ
// partial score=0.952 date=2026-09-27
// cl: /O2 /Ob2 /DNDEBUG /MD /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
// BANK NOTES (2026-09-27): whole body, all retail branches/calls reconstructed.
// probe --shape=0.952; 2144 compiled / 2132 retail; raw masked byte fraction
// 0.7798507463. Not a match; no production row or new pin is claimed.
// First structural residue +03AA; loop delta/last stack slots are swapped;
// three dual x87 stores are reversed. The volatile comparison reads below are
// explicit float-rounding experiments, NOT evidence of volatile retail members.
// Native WWMath::Sqrt reproduces the witnessed fsqrt/store/reload sequence.
// Static complete0075B980 is EXACT in probe for 132 B including jump table;
// the separate ledger's 104 B excludes that table. It is not landed here.
//
// Remaining address-derived external declarations require normal pin review
// only if this caller reaches exact. Independently decoded retail operands:
// TheView0076C080 -> VA 012F1600 (existing TheTacticalView global)
// TheLOD0076C080 -> VA 012ED5AC (existing TheGameLODManager global)
// Sync0076C080 / PrevSync0076C080 -> VA 0133F420 / 0133F424
// apply(State*,float,bool,bool,bool) -> ILT RVA 00001CA8 -> body 00765FB0;
//   ECX=this; five stack slots; values are state,-1.0f,0,0,0.
// finish() -> tail ILT RVA 000363AE -> body 00762900; ECX=this, no stack args.
// Other external calls retain established ledger declarations and names.
// No guessed semantic identity for this owner or its opaque field views.
// Intended production home if exact: game/GameEngineDevice/Source/W3DDevice/
// GameClient/Drawable/Draw/Rva0076C080AdvanceAnimation.cpp
// Candidate RVA 0076C080, retail extent 2132 incl six-entry switch table.
// Complete reconstruction; opaque views preserve witnessed retail offsets.
// 0075B980 is a TU-local helper with compiler-private ECX/ESI/stack ABI.
#include "wwmath.h"
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
class BFMERopeDrawable { public: const Coord3D* getPosition() const; };
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
extern View0076C080* TheView0076C080;
extern unsigned char* TheLOD0076C080;
extern int g_Va012F8064;
extern U32 Sync0076C080,PrevSync0076C080;
float minf(float,float);
float maxf(float,float);
class Rva0076C080 {
public:
    void advanceAnimation();
    void apply(State0076C080*,float,bool,bool,bool);
    void finish();
    unsigned char pad00[4]; Data0076C080* p04; void* p08;
    Interface0076C080 secondary;
    unsigned char pad10[4]; State0076C080* p14;
    unsigned char pad18[0x10]; int i28;
    unsigned char pad2c[8]; Render0076C080* p34;
    unsigned char pad38[0x74-0x38]; float f74,f78,f7c,f80;
    unsigned char pad84[0x9c-0x84]; U32 u9c;
    unsigned char pada0[0xdc-0xa0]; Track0076C080 tracks[3];
    unsigned char pad130[0x148-0x130]; U32 u148[4];
    unsigned char pad158[0x173-0x158]; bool b173; U32 u174;
    unsigned char pad178[0x1fc-0x178]; bool b1fc;
    unsigned char pad1fd[0x230-0x1fd]; bool b230,b231;
};
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
void Rva0076C080::advanceAnimation()
{
    if (!p34 || !p14) return;
    const Data0076C080* d=p04;
    *((bool*)p34+0xc4)=false;
    if (b231 && d->f120 < 1.0f) {
        Coord0076C080 camera;
        const Coord0076C080* cameraPtr=TheView0076C080->position();
        camera.x=cameraPtr->x; camera.y=cameraPtr->y;
        float cx=camera.x, cy=camera.y;
        const Coord0076C080* pos=(const Coord0076C080*)((BFMERopeDrawable*)p08)->getPosition();
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
            if (TheLOD0076C080 && *(int*)(TheLOD0076C080+0x16c4)<=1) {
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
        elapsed=Sync0076C080-PrevSync0076C080;
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
            case 1: {
                t.f04=t.f04+delta; delta=t.f04;
                if (*(volatile float*)&delta>last) { int loops=(int)(delta/last); t.f04=delta-loops*last; t.b18=true; }
                break;
            }
            case 2:
                t.f04+=delta;
                if (t.f04>last) { t.f04=last; t.b18=true; }
                break;
            case 3: {
                t.f04=t.f04+t.i14*delta; delta=t.f04;
                if (t.i14==1) {
                    if (*(volatile float*)&delta>last) { int loops=(int)(delta/last); float wrapped=loops*last; t.i14=-1; t.f04=(last+wrapped)-delta; t.b18=true; }
                } else if (*(volatile float*)&delta<0.0f) {
                    int loops=(int)(fabs(delta)/last);
                    if (loops>0) t.f04=loops*last+delta;
                    t.i14=1; t.f04=-t.f04; t.b18=true;
                }
                break;
            }
            case 5: {
                t.f04=t.f04-delta; delta=t.f04;
                if (*(volatile float*)&delta<0.0f) { int loops=(int)(fabs(delta)/last); float wrapped=loops*last; t.f04=last+wrapped+delta; t.b18=true; }
                break;
            }
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
                u174=0;
                if (next) {
                    b230=false;
                    ((BfmeRecordHook6BE90*)this)->bfmeSelect6BE90((BfmeRecord6BE90*)next,0,0);
                    if (!u174) b173=false;
                    return;
                }
                b173=false;
            }
            if (!((Gen_00208330*)((char*)state+4))->bfmeAny() || ((state->u38>>5)&1))
                apply((State0076C080*)state,-1.0f,false,false,false);
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
            opacity=(frame-info->f2c)/(end-info->f2c);
            if (!info->b34) opacity=1.0f-opacity;
        }
        if (opacity>0.0f) { ((BfmeThing923B*)p08)->bfmeGo923B(1); p34->hidden(0); }
        else { ((BfmeThing923B*)p08)->bfmeGo923B(0); p34->hidden(1); }
        p34->opacity(opacity);
    }
    finish();
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
