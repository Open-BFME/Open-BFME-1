// ?update@AIAttackFireWeaponState@@UAE?AW4StateReturnType@@XZ
// partial score=0.948387 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath
// Banked reconstruction of retail 0017C250 (979 bytes), not a landed claim.
// Current emission: 1004 bytes; normalized instruction shape 0.948387.
// Same primary Thing vptr avoids an incorrect +4 Object receiver adjustment.
// Filter temporary lifetimes and the nested map-filter scope reproduce the
// retail cleanup ordering. The first 0x46 bytes match before return layout
// diverges: early failure moves to the end, early success expands inline,
// and notifyFired duplicates across the final firing arms.
// EH annotation trials, return labels/result locals, status switch, reversed
// firing arms and guard nesting did not improve this best structural score.
// The address-derived Rva00149E60 constructor emission separately matched its
// 39-byte retail body; no new pin or identity claim has been added. If the
// update becomes exact, verify its constructor/filter-vtable and Coord3D
// signature references against existing identities before landing.
#include "coord3d.h"
inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3D::Coord3D(const Coord3D &v) {
    x = v.x;
    y = v.y;
    z = v.z;
}

enum StateReturnType { STATE_CONTINUE = 0, STATE_SUCCESS = -1, STATE_FAILURE = -2 };
enum WeaponSlotType {};
enum WeaponStatus { READY_TO_FIRE = 0, PRE_ATTACK = 4 };
enum WhichTurretType {};
enum KindOfType {};
class Player;
class Object;
class BfmeD1054;
class BfmeC1054 {
  public:
    void bfmeGo1054C(BfmeD1054 *, int, int);
};
class AIUpdateInterface {
  public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void slot48();
    virtual void slot49();
    virtual void slot50();
    virtual void slot51();
    virtual void slot52();
    virtual void slot53();
    virtual void slot54();
    virtual void slot55();
    virtual void slot56();
    virtual void slot57();
    virtual void slot58();
    virtual void slot59();
    virtual void slot60();
    virtual void slot61();
    virtual void slot62();
    virtual void slot63();
    virtual void slot64();
    virtual void slot65();
    virtual void slot66();
    virtual void slot67();
    virtual void slot68();
    virtual void slot69();
    virtual void slot70();
    virtual void slot71();
    virtual void slot72();
    virtual void slot73();
    virtual void slot74();
    virtual void slot75();
    virtual void slot76();
    virtual void slot77();
    virtual void slot78();
    virtual void slot79();
    virtual void slot80();
    virtual void slot81();
    virtual void slot82();
    virtual void slot83();
    virtual void slot84();
    virtual void slot85();
    virtual void slot86();
    virtual void slot87();
    virtual void slot88();
    virtual void slot89();
    virtual void slot90();
    virtual void slot91();
    virtual void slot92();
    virtual void slot93();
    virtual void slot94();
    virtual void slot95();
    virtual void slot96();
    virtual void slot97();
    virtual void slot98();
    virtual void slot99();
    virtual void slot100();
    virtual void slot101();
    virtual void slot102();
    virtual void slot103();
    virtual void slot104();
    virtual void slot105();
    virtual void slot106();
    virtual void slot107();
    virtual void slot108();
    virtual void slot109();
    virtual void slot110();
    virtual void slot111();
    virtual void slot112();
    virtual void slot113();
    virtual void slot114();
    virtual void slot115();
    virtual void slot116();
    virtual void slot117();
    virtual void slot118();
    virtual void slot119();
    virtual void slot120();
    virtual void slot121();
    virtual void slot122();
    virtual void slot123();
    virtual void slot124();
    virtual void slot125();
    virtual void slot126();
    virtual void slot127();
    virtual int getLastCommandSource();
    char pad_04[0x1c8];
    BfmeC1054 *m_curLocomotor;
    WhichTurretType getWhichTurretForCurWeapon() const;
};
class BfmeSubEQT {
  public:
    char bfmeBEQT();
    char bfmeAEQT();
};
struct WeaponTemplate {
    char pad_00[0x510];
    float m_continueAttackRange;
    char pad_514[0x15];
    bool m_529;
    char pad_52a[9];
    bool m_533;
};
class Weapon {
  public:
    char pad_00[4];
    WeaponTemplate *m_04;
    WeaponStatus getStatus() const;
    bool flag533() const { return m_04->m_533; }
    bool flag529() const { return m_04->m_529; }
    float getContinueAttackRange() const { return m_04->m_continueAttackRange; }
};
class Thing {
  public:
    virtual void slot0();
    bool isKindOf(KindOfType) const;
};
class BFMEActionObject {
  public:
    bool testStatus(int) const;
};
class Object : public Thing {
  public:
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void fireCurrentWeapon(Object *, unsigned);
    char pad_04[0x34];
    Coord3D m_cachedPos;
    char pad_44[0x4c];
    unsigned m_status[3];
    char pad_9c[0x168];
    AIUpdateInterface *m_204;
    char pad_208[0x13c];
    unsigned char m_privateStatus;
    Weapon *getCurrentWeapon(WeaponSlotType *);
    void setStatusBit(int, bool);
    void preFireCurrentWeapon(const Object *, const Coord3D *);
    void setFiringConditionForCurrentWeapon() const;
    void fireCurrentWeapon(const Coord3D *);
    bool getWorldspaceBestContactPoint(Coord3D *, const Coord3D *, const char *, int, int,
                                       bool) const;
    Player *getControllingPlayer() const;
    __forceinline bool isEffectivelyDead() const {
        return (m_privateStatus & 1) || ((BFMEActionObject *)this)->testStatus(49);
    }
};
class StateMachine {
  public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void setGoalObject(Object *);
    char pad_04[12];
    Object *m_owner;
    char pad_14[12];
    unsigned m_20;
    Coord3D m_goalPosition;
    Object *getGoalObject();
};
class NotifyWeaponFiredInterface {
  public:
    virtual void notifyFired() = 0;
    virtual void notifyNewVictimChosen(Object *) = 0;
    virtual bool isWeaponSlotOkToFire(WeaponSlotType) const = 0;
    virtual bool isAttackingObject() const = 0;
    virtual const Coord3D *getOriginalVictimPos() const = 0;
};
class PartitionFilter {
  public:
    PartitionFilter() : m_next(0) {}
    virtual ~PartitionFilter() {}
    virtual bool allow(Object *) = 0;
    virtual void slot2() = 0;
    PartitionFilter *m_next;
    PartitionFilter *link(PartitionFilter *);
};
class PartitionFilterSameMapStatus : public PartitionFilter {
  public:
    const Object *m_object;
    PartitionFilterSameMapStatus(const Object *p) : m_object(p) {}
    virtual bool allow(Object *);
    virtual void slot2();
};
class Rva00149E60 : public PartitionFilter {
  public:
    int m_08, m_0c, m_10;
    Rva00149E60(int, int, int);
    virtual bool allow(Object *);
    virtual void slot2();
};
class Rva0016A9F0PlayerFilter : public PartitionFilter {
  public:
    Player *m_08;
    Rva0016A9F0PlayerFilter(Player *p) : m_08(p) {}
    virtual bool allow(Object *);
    virtual void slot2();
};
class PartitionManager {
  public:
    Object *getClosestObject(const Coord3D *, float, int, PartitionFilter *);
};
extern PartitionManager *ThePartitionManager;
class AIAttackFireWeaponState {
  public:
    virtual StateReturnType update();
    char pad_04[0x18];
    StateMachine *m_machine;
    char pad_20[4];
    NotifyWeaponFiredInterface *m_att;
    bool m_28;
};
StateReturnType AIAttackFireWeaponState::update() {
    Object *obj = m_machine->m_owner;
    Object *victim = m_machine->getGoalObject();
    unsigned arg20 = m_machine->m_20;
    WeaponSlotType slot;
    Weapon *weapon = obj->getCurrentWeapon(&slot);
    if (!weapon || (obj->m_privateStatus & 1) || (obj->m_status[2] & 0x20000))
        return STATE_FAILURE;
    bool atPosition;
    if (weapon->flag533() && !(victim && victim->isKindOf((KindOfType)2)))
        atPosition = true;
    else {
        atPosition = false;
        AIUpdateInterface *ai;
        if (victim && (ai = obj->m_204) && ai->m_curLocomotor &&
            ai->getWhichTurretForCurWeapon() == -1) {
            Coord3D pos = victim->m_cachedPos;
            if ((victim->isKindOf((KindOfType)59) || victim->isKindOf((KindOfType)136)) &&
                (((BfmeSubEQT *)weapon->m_04)->bfmeBEQT() ||
                 ((BfmeSubEQT *)weapon->m_04)->bfmeAEQT()))
                victim->getWorldspaceBestContactPoint(&pos, &obj->m_cachedPos, "Ram", 0, 42, false);
            BfmeC1054 *locomotor = ai->m_curLocomotor;
            locomotor->bfmeGo1054C((BfmeD1054 *)obj, (int)&pos, 0);
        }
        if (m_att && m_att->isAttackingObject() && (!victim || victim->isEffectivelyDead()) &&
            !weapon->flag529()) {
            m_machine->setGoalObject(0);
            return STATE_SUCCESS;
        }
    }
    if (m_28) {
        m_28 = false;
        obj->setStatusBit(13, true);
        obj->preFireCurrentWeapon(victim, &m_machine->m_goalPosition);
        return STATE_CONTINUE;
    }
    WeaponStatus status = weapon->getStatus();
    if (status == PRE_ATTACK)
        return STATE_CONTINUE;
    else if (status != READY_TO_FIRE)
        return STATE_FAILURE;
    if (m_att && !m_att->isWeaponSlotOkToFire(slot))
        return STATE_FAILURE;
    obj->setFiringConditionForCurrentWeapon();
    if (m_att && m_att->isAttackingObject() && !atPosition) {
        obj->fireCurrentWeapon(victim, arg20);
        obj->setStatusBit(27, false);
        float range = weapon->getContinueAttackRange();
        if (range > 0.0f && victim && ((victim->m_status[0] & 1) || victim->isEffectivelyDead())) {
            const Coord3D *original = m_att ? m_att->getOriginalVictimPos() : 0;
            if (original) {
                AIUpdateInterface *ai = obj->m_204;
                int cmd = ai ? ai->getLastCommandSource() : 2;
                {
                    PartitionFilterSameMapStatus mapFilter(obj);
                    victim = ThePartitionManager->getClosestObject(
                        original, range, 0,
                        Rva0016A9F0PlayerFilter(victim->getControllingPlayer())
                            .link(Rva00149E60(0, (int)obj, cmd).link(&mapFilter)));
                }
                if (victim) {
                    m_machine->setGoalObject(victim);
                    m_att->notifyNewVictimChosen(victim);
                }
            }
        }
    } else {
        obj->fireCurrentWeapon(&m_machine->m_goalPosition);
        obj->setStatusBit(27, false);
    }
    m_att->notifyFired();
    return STATE_SUCCESS;
}
