// stlport
// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
// RVA 0075F810: thiscall with no stack arguments. See docs/analysis/0x0077b3f0.md.
// Port of ZH W3DModelDraw::handleClientRecoil with BFME's four slots and layouts.
// Owner identity remains opaque. Offsets and virtual slots are retail witnesses.
#include <new>
#define _OPERATOR_NEW_DEFINED_
#include "matrix3d.h"
#include <math.h>
#include <vector>
#include <stddef.h>
extern "C" void _WriteBarrier();
#pragma intrinsic(_WriteBarrier)

class RecoilRender0075F810 {
public:
    virtual void slot00();
#define SLOT(n) virtual void slot##n();
    SLOT(04) SLOT(08) SLOT(0C) SLOT(10) SLOT(14) SLOT(18) SLOT(1C)
    SLOT(20) SLOT(24) SLOT(28) SLOT(2C) SLOT(30) SLOT(34) SLOT(38) SLOT(3C)
    SLOT(40) SLOT(44) SLOT(48) SLOT(4C) SLOT(50) SLOT(54) SLOT(58) SLOT(5C)
    SLOT(60) SLOT(64) SLOT(68) SLOT(6C) SLOT(70) SLOT(74) SLOT(78) SLOT(7C) SLOT(80)
    virtual RecoilRender0075F810 *slot84(int, int) const;
    SLOT(88) SLOT(8C) SLOT(90) SLOT(94) SLOT(98) SLOT(9C) SLOT(A0) SLOT(A4)
    SLOT(A8) SLOT(AC) SLOT(B0) SLOT(B4) SLOT(B8) SLOT(BC) SLOT(C0) SLOT(C4)
    SLOT(C8) SLOT(CC) SLOT(D0)
    virtual void slotD4(int);
    SLOT(D8) SLOT(DC)
    virtual void slotE0(int, const Matrix3D &, bool);
    SLOT(E4) SLOT(E8) SLOT(EC) SLOT(F0) SLOT(F4) SLOT(F8) SLOT(FC)
    SLOT(100) SLOT(104) SLOT(108) SLOT(10C) SLOT(110) SLOT(114) SLOT(118) SLOT(11C)
    SLOT(120) SLOT(124) SLOT(128) SLOT(12C) SLOT(130) SLOT(134) SLOT(138) SLOT(13C)
    SLOT(140) SLOT(144) SLOT(148) SLOT(14C) SLOT(150) SLOT(154) SLOT(158) SLOT(15C)
    SLOT(160) SLOT(164) SLOT(168) SLOT(16C) SLOT(170) SLOT(174) SLOT(178) SLOT(17C)
    SLOT(180) SLOT(184) SLOT(188) SLOT(18C)
    virtual void slot190(int);
#undef SLOT
    int refs04;
    void release() { if (--refs04 == 0) slot00(); }
};

struct BarrelRecord0075F810 {
    int recoilBone00;
    int unknown04;
    int muzzleFlashBone08;
    char unknown0C[0x3C-0x0C];
    void setHidden(RecoilRender0075F810 *render, bool hidden) const {
        // Retail +CD..+D0 tests hidden and branches to the next instruction.
        // The intrinsic retains that witnessed branch without an emitted call.
        if (!hidden) _WriteBarrier();
        if (render) {
            RecoilRender0075F810 *child = render->slot84(0, muzzleFlashBone08);
            if (child) {
                child->slot190(hidden);
                child->release();
            }
        }
    }
};
struct RecoilEntry0075F810 { enum State { Idle, Start, Recoil, Settle }; int state; float shift, rate; };
// Native STLport accessors are needed: a three-pointer replacement changes
// address lifetimes and register allocation starting at retail +A6.
#define RecoilVector0075F810 std::vector
struct RecoilState0075F810 {
    char unknown00[0x7C];
    RecoilVector0075F810<BarrelRecord0075F810> barrels7C[4];
    unsigned validAC;
};
struct RecoilFlags0075F810 { char unknown00[0x120]; bool active120[4]; };
struct RecoilData0075F810 {
    char unknown00[0x54];
    float InitialRecoilSpeed, MaxRecoilDistance, RecoilDamping, RecoilSettleSpeed;
};
class RecoilDraw0075F810 {
public:
    void update();
    char unknown00[4];
    const RecoilData0075F810 *data04;
    char unknown08[8];
    RecoilFlags0075F810 *flags10;
    RecoilState0075F810 *m_curState;
    char unknown18[0x34-0x18];
    RecoilRender0075F810 *m_renderObject;
    char unknown38[0xAC-0x38];
    RecoilVector0075F810<RecoilEntry0075F810> recoilsAC[4];
};
typedef char RecoilEntrySize0075F810[sizeof(RecoilEntry0075F810) == 12 ? 1 : -1];
typedef char BarrelRecordSize0075F810[sizeof(BarrelRecord0075F810) == 0x3C ? 1 : -1];
typedef char RecoilArrayOffset0075F810[offsetof(RecoilDraw0075F810, recoilsAC) == 0xAC ? 1 : -1];
typedef char RecoilStateFlagsOffset0075F810[offsetof(RecoilState0075F810, validAC) == 0xAC ? 1 : -1];

void RecoilDraw0075F810::update() {
    if (!m_curState) return;
    const RecoilData0075F810 *d = data04;
    if (!(m_curState->validAC & 8)) return;
    for (int wslot = 0; wslot < 4; ++wslot) {
        if (!flags10->active120[wslot]) continue;
        const RecoilVector0075F810<BarrelRecord0075F810> &barrels = m_curState->barrels7C[wslot];
        RecoilVector0075F810<RecoilEntry0075F810> &recoils = recoilsAC[wslot];
        int count = barrels.size();
        int recoilCount = recoils.size();
        count = count > recoilCount ? recoilCount : count;
        for (int i = 0; i < count; ++i) {
            if (barrels[i].muzzleFlashBone08 != 0) {
                bool hidden = recoils[i].state != 1;
                barrels[i].setHidden(m_renderObject, hidden);
            }
            if (barrels[i].recoilBone00 != 0) {
                switch (recoils[i].state) {
                case 0: break;
                case 1: case 2:
                    recoils[i].shift += recoils[i].rate;
                    recoils[i].rate *= d->RecoilDamping;
                    if (recoils[i].shift >= d->MaxRecoilDistance) {
                        recoils[i].shift = d->MaxRecoilDistance;
                        recoils[i].state = RecoilEntry0075F810::Settle;
                    } else if (fabs(recoils[i].rate) < 0.01f) {
                        recoils[i].state = RecoilEntry0075F810::Settle;
                    }
                    break;
                case 3:
                    recoils[i].shift -= d->RecoilSettleSpeed;
                    if (recoils[i].shift <= 0.0f) {
                        recoils[i].shift = 0.0f;
                        recoils[i].state = RecoilEntry0075F810::Idle;
                    }
                    break;
                }
                Matrix3D gunXfrm;
                gunXfrm.Make_Identity();
                gunXfrm.Translate_X(-recoils[i].shift);
                if (m_renderObject) {
                    m_renderObject->slotD4(barrels[i].recoilBone00);
                    m_renderObject->slotE0(barrels[i].recoilBone00, gunXfrm, false);
                }
            } else {
                recoils[i].state = RecoilEntry0075F810::Idle;
            }
        }
    }
}
