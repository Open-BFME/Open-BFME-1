// ?d_002417e0@@YAXXZ
// partial score=0.2767552828902522 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc /G7 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// Complete retail control-flow reconstruction: RVA 002417E0, 1467 bytes.
// See ANALYSIS.md. Names with an address/offset are deliberately opaque.
// Entry: ECX=receiver, (Object*, const Coord3D*, float), ret 12, no EH.
// Retail frame: sub esp,64h; saves EBX EBP ESI EDI. No artificial padding.
// Partial: 1465/1467 B, 1057 masked positional differences, score
// 0.2767552828902522. /G7 and the two zero-code barrier kinds are measured
// shape hypotheses, not claims about the original source or compiler flags.
// Every call/branch is represented; instruction order/local slot allocation
// remain non-exact. See build/hub_002417e0/ANALYSIS.md and PROGRESS.md.
#include "Lib/BaseType.h"
extern "C" void _WriteBarrier();
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_WriteBarrier, _ReadWriteBarrier)
class Rva002417E0Call {};
template<class T> __forceinline T rva002417E0Method(void (*raw)()) {
    union { void (*raw)(); T method; } u;
    u.raw=raw; return u.method;
}
#define CALL(T,p,j) (((Rva002417E0Call*)(p))->*rva002417E0Method<T>(j))
typedef void (Rva002417E0Call::*Void0)();
typedef bool (Rva002417E0Call::*Bool0)();
typedef int (Rva002417E0Call::*Int0)();
typedef float (Rva002417E0Call::*Float0)();
typedef float (Rva002417E0Call::*FloatPtr)(void*);
typedef void (Rva002417E0Call::*VoidPtr)(const void*);
typedef void (Rva002417E0Call::*VoidFloat)(float);
typedef void (Rva002417E0Call::*VoidInt)(int);
typedef bool (Rva002417E0Call::*BoolInt)(int);
typedef bool (Rva002417E0Call::*BoolPtr)(void*);
typedef int (Rva002417E0Call::*IntInt)(int);
typedef void (Rva002417E0Call::*VoidII)(int,int);
struct Rva003FD7D0Point36 {
    float value00;
    Coord3D point04;
    Coord3D point10;
    int word1C;
    int word20;
};
typedef void (Rva002417E0Call::*PathQuery)(void*,void*,Rva003FD7D0Point36*,bool);
typedef bool (Rva002417E0Call::*Valid)(const Coord3D*,int,unsigned,void*);
typedef bool (Rva002417E0Call::*Adjust)(void*,const void*,Coord3D*,const Coord3D*);
typedef void (Rva002417E0Call::*Update)(void*,const Coord3D*,int,const char*,int);
typedef unsigned char (__stdcall *Guard)(void*);
extern void j_00004a11(); extern void j_00008a9e();
extern void j_0000ebab(); extern void j_00012486(); extern void j_000131a6();
extern void j_0001336d(); extern void j_00015d02(); extern void j_0002191d();
extern void j_000230ab(); extern void j_00024d70(); extern void j_00024f7d();
extern void j_00027ffc(); extern void j_0002910e(); extern void j_000294e2();
extern void j_0002ecad(); extern void j_0002ed16();
extern void j_0003251f(); extern void j_0003611a(); extern void j_000399A5();
extern void j_0003a1a7(); extern void j_0003a391(); extern void j_0003b359();
extern void j_00044774(); extern void j_00046164();
extern void j_0002fe0f();
extern float normalizeAngle(float);

class Thing {
public:
    virtual void slot000();
    virtual void slot004();
    virtual void slot008();
    virtual void slot00C();
    virtual void slot010();
    virtual void slot014();
    virtual void slot018();
    virtual void slot01C();
    virtual void slot020();
    virtual void slot024();
    virtual void slot028();
    virtual void slot02C();
    virtual void slot030();
    virtual void slot034();
    virtual void slot038();
    virtual void slot03C();
    virtual void slot040();
    virtual void slot044();
    virtual void slot048();
    virtual void slot04C();
    virtual void slot050();
    virtual void slot054();
    virtual void slot058();
    virtual void slot05C();
    virtual void slot060();
    virtual void slot064();
    virtual void slot068();
    virtual void slot06C();
    virtual void slot070();
    virtual void slot074();
    virtual void slot078();
    virtual void slot07C();
    virtual void slot080();
    virtual void slot084();
    virtual void slot088();
    virtual void slot08C();
    virtual void slot090();
    virtual void slot094();
    virtual void slot098();
    virtual void slot09C();
    virtual void slot0A0();
    virtual void slot0A4();
    virtual void slot0A8();
    virtual void slot0AC();
    virtual void slot0B0();
    virtual void slot0B4();
    virtual void slot0B8();
    virtual void slot0BC();
    virtual void slot0C0();
    virtual void slot0C4();
    virtual void slot0C8();
    virtual void slot0CC();
    virtual void slot0D0();
    virtual void slot0D4();
    virtual void slot0D8();
    virtual void slot0DC();
    virtual void slot0E0();
    virtual void slot0E4();
    virtual void slot0E8();
    virtual void slot0EC();
    virtual void slot0F0();
    virtual void slot0F4();
    virtual void slot0F8();
    virtual void slot0FC();
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
    virtual bool slot180();
    virtual bool slot184();
    virtual void slot188();
    virtual bool slot18C();
    virtual void slot190();
    virtual void slot194();
    virtual void slot198();
    virtual void slot19C();
    virtual void slot1A0();
    virtual void slot1A4();
    virtual void slot1A8();
    virtual void slot1AC();
    virtual void slot1B0();
    virtual void slot1B4();
    virtual void slot1B8();
    virtual void slot1BC();
    virtual void slot1C0();
    virtual void slot1C4();
    virtual void slot1C8();
    virtual void slot1CC();
    virtual void slot1D0();
    virtual void slot1D4();
    virtual void slot1D8(const Coord3D*);
    virtual void slot1DC(const Coord3D*);
    virtual void slot1E0();
    virtual void slot1E4(float);
    virtual void slot1E8();
    virtual void slot1EC();
    virtual void slot1F0();
    virtual void slot1F4(const Coord3D*);

    char pad004[0x140-4]; void *path140;
    char pad144[0x1A8-0x144]; char set1A8[0x10];
    unsigned word1B8;
    char pad1BC[0x1CC-0x1BC]; void *locomotor1CC;
};
struct Rva002417E0Object {
    char pad000[0x38]; Coord3D position; float orientation;
    char pad048[0x74-0x48]; int id;
    char pad078[0x9C-0x78]; int word09C,word0A0,word0A4,word0A8;
    char pad0AC[0x114-0xAC]; unsigned word114;
    char pad118[0x204-0x118]; Thing *ai204;
    __forceinline void clear114() {
        if (word114 & 0x10000000) {
            word114 &= ~0x10000000;
            CALL(Void0,this,j_0002191d)();
        }
    }
};
struct Rva002417E0Record {
    int word00; char pad004[0x14-4]; unsigned word14; unsigned word18;
};
struct Rva002417E0AIService { char pad000[12]; void *pathfinder; };
struct Rva002417E0Clock { char pad000[0x3C]; unsigned frame; };
class Rva002417E0Terrain {
public:
    virtual void slot000(); virtual void slot004(); virtual void slot008();
    virtual void slot00C(); virtual void slot010(); virtual void slot014();
    virtual void slot018();
    virtual float slot01C(float,float,int,void*,bool);
};
// Address-derived symbols are mapped to the independently read image VAs.
// No new ledger pin is claimed by this analysis-only reconstruction.
extern Rva002417E0AIService *rva012EF214;
extern Rva002417E0Terrain *rva012EF4CC;
extern Rva002417E0Clock *rva012F0898;
class Rva002417E0 {
public:
    char pad000[8]; Rva002417E0Object *object08;
    char pad00C[0xE8-12]; bool flag0E8;
    char pad0E9[0x1AC-0xE9]; unsigned word1AC;
    char pad1B0[0x1D8-0x1B0]; Rva002417E0Record *records1D8;
    char pad1DC[0x1FC-0x1DC]; bool flag1FC;
    char pad1FD[0x204-0x1FD]; bool flag204;
    void body(Rva002417E0Object*,const Coord3D*,float);
};

// ?body@Rva002417E0@@QAEXPAURva002417E0Object@@PBUCoord3D@@M@Z
void Rva002417E0::body(Rva002417E0Object *member,const Coord3D *destination,float orientation)
{
    Coord3D delta;
    Thing *memberAI=member->ai204;
    const Coord3D *memberPosition=&member->position;
    Rva002417E0Object *owner=object08;
    Coord3D oldPosition=*memberPosition;
    Thing *ownerAI=owner->ai204;
    if (!ownerAI || !memberAI) return;
    Coord3D dest;
    dest=*destination;
    void *ownerLocomotor=ownerAI->locomotor1CC;
    void *memberLocomotor=memberAI->locomotor1CC;
    if (!memberLocomotor || !ownerLocomotor) return;
    if (((Guard)j_000131a6)(member)) {
        if (member->word114 & 0x10000000) {
            member->word114 &= ~0x10000000;
            CALL(Void0,member,j_0002191d)();
            _WriteBarrier();
            return;
        }
        _ReadWriteBarrier();
        return;
    }
    if (!CALL(Bool0,ownerAI,j_00044774)() && word1AC==0) {
        ICoord2D pair0A4;
        pair0A4.x=member->word0A4;
        pair0A4.y=member->word0A8;
        if (member->word09C>=0 && member->word09C==pair0A4.x && member->word0A0==pair0A4.y)
            dest=member->position;
    }
    delta.x=dest.x-oldPosition.x;
    delta.y=dest.y-oldPosition.y;
    delta.z=0.0f;
    float distance=CALL(Float0,&delta,j_0002fe0f)();
    float adjustedDistance=distance;
    if (ownerAI->path140) {
        Rva003FD7D0Point36 point;
        CALL(PathQuery,ownerAI->path140,j_00008a9e)(owner,ownerAI->locomotor1CC,&point,false);
        // Retail +016B fsubr, +016F fadd; Ghidra drops this adjustment.
        adjustedDistance=point.value00-CALL(Float0,ownerLocomotor,j_0002ecad)()+distance;
    }
    if (!flag1FC) {
        if ((!memberAI->slot184() || !ownerAI->slot184()) &&
            (CALL(Bool0,ownerAI,j_00044774)() || memberAI->slot180()) && !memberAI->slot18C())
            CALL(VoidII,(char*)memberAI+0x20,j_0001336d)(0,2);
    } else {
        if (!memberAI->slot180() && !memberAI->slot184())
            CALL(VoidInt,(char*)memberAI+0x20,j_00024d70)(2);
    }
    float threshold=CALL(FloatPtr,memberLocomotor,j_00024f7d)(member);
    float speedLimit=CALL(FloatPtr,memberLocomotor,j_000230ab)(member)*0.2f;
    if (threshold>speedLimit) threshold=speedLimit;
    if (distance<threshold) {
        Coord3D nearPosition;
        nearPosition=dest;
        if (CALL(Int0,memberLocomotor,j_0002910e)()!=8) {
            nearPosition.z=oldPosition.z;
            void *pathfinder=rva012EF214->pathfinder;
            if (CALL(Valid,pathfinder,j_0003b359)(&nearPosition,
                    CALL(Int0,member,j_0003a391)(),memberAI->word1B8,object08))
                nearPosition.z=rva012EF4CC->slot01C(nearPosition.x,nearPosition.y,
                    CALL(Int0,member,j_0003a391)(),0,true);
        }
        CALL(VoidPtr,member,j_0003a1a7)(&nearPosition);
        CALL(VoidPtr,member,j_0002ed16)(&nearPosition);
        // Retail +02FA stores before the cdecl pop: angle replaces distance
        // in steady ESP+10. The per-record thresholds below also use angle.
        float angle=(float)fabs(normalizeAngle(orientation-member->orientation));
        bool turn=angle>0.1745329350233078f;
        if (flag1FC) {
            int index=CALL(IntInt,this,j_00046164)(member->id);
            Rva002417E0Record *record=&records1D8[index];
            turn=false;
            if (record->word00==1) {
                turn=angle>1.5707963705062866f;
                if (record->word14>rva012F0898->frame) turn=true;
            }
            if (record->word00==2 && angle>0.1745329350233078f) turn=true;
            if (turn) record->word00=2;
        }
        if (turn) {
            if (CALL(BoolInt,member,j_0003251f)(14)) {
                CALL(VoidFloat,member,j_000399A5)(orientation);
                memberAI->slot1E8();
            } else {
                memberAI->slot1E4(orientation);
                CALL(Void0,memberAI,j_0003611a)();
            }
            flag0E8=true;
            return;
        }
        if (CALL(Bool0,memberAI,j_00044774)()) CALL(Void0,memberAI,j_00012486)();
        member->clear114();
        memberAI->slot1E8();
        if (flag1FC) {
            int index=CALL(IntInt,this,j_00046164)(member->id);
            Rva002417E0Record *record=&records1D8[index];
            if (record->word00==1 || record->word00==2) record->word00=3;
        }
        if (!CALL(Bool0,ownerAI,j_00044774)()) {
            if (!CALL(BoolPtr,this,j_00004a11)(member)) {
                if (!CALL(Adjust,rva012EF214->pathfinder,j_00027ffc)(member,memberAI->set1A8,&nearPosition,0))
                    return;
                memberAI->slot1F4(&nearPosition);
                void *pathfinder=rva012EF214->pathfinder;
                CALL(Update,pathfinder,j_000294e2)(member,&nearPosition,
                    CALL(Int0,member,j_0003a391)(),
                    "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeContain.cpp",2021);
            } else {
                void *pathfinder=rva012EF214->pathfinder;
                CALL(Update,pathfinder,j_000294e2)(member,&member->position,
                    CALL(Int0,member,j_0003a391)(),
                    "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeContain.cpp",2025);
                return;
            }
        }
        flag0E8=true;
    } else {
        flag0E8=true;
        if (!flag1FC && CALL(Bool0,ownerAI,j_00044774)())
            CALL(VoidPtr,rva012EF214->pathfinder,j_00015d02)(member);
        delta=dest;
        if (flag204) memberAI->slot1D8(&delta);
        else memberAI->slot1DC(&delta);
        CALL(VoidFloat,memberAI,j_0000ebab)(adjustedDistance);
        if (!(member->word114&0x10000000)) {
            member->word114|=0x10000000;
            CALL(Void0,member,j_0002191d)();
        }
    }
    _ReadWriteBarrier();
}
