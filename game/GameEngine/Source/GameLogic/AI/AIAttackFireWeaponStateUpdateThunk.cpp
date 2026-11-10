// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Include /Igame/GameEngine/Source/GameLogic/Object /Igame/GameEngine/Source/GameLogic
// readable body of ?update@AIAttackFireWeaponState@@UAE?AW4StateReturnType@@XZ: game/GameEngine/Source/GameLogic/AI/AIStates.cpp
// Handoff: targets/game/reverse/attempt_support/20261110-0017c250-fire-weapon-update.md
// Retail 0017C250, 979 bytes (RET at +0x3D2); vtable 0x01097DC0 slot 6 via
// ILT 0x00029D7A. The flag533 test reads the template through Weapon's
// inline getTemplate() accessor and the goal-object id is read directly from
// the machine: together these set MSVC's EAX/ECX/EDX round-robin phase that
// the old bank missed by one step (+00B2..+01E6). Coord3D is the canonical
// struct and the goal position is copied field by field (BFME 2 donor
// 2bac16a65 AIAttackFireWeaponState::update spelling).
#include "Lib/Coord3D.h"
#include "command_source_type.h"

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
 bool flag533()const{return m_533;}
 bool flag529()const{return m_529;}
 float getContinueAttackRange()const{return m_continueAttackRange;}
};
class Weapon {
  public:
    char pad_00[4];
    WeaponTemplate *m_04;
    WeaponStatus getStatus() const;
    const WeaponTemplate *getTemplate() const { return m_04; }
    bool flag529() const { return m_04->m_529; }
    float getContinueAttackRange() const { return m_04->m_continueAttackRange; }
};
class BFMEActionObject {public: bool testStatus(int)const;};
#define BFME_HAVE_COORD3D 1
#define THING_TU_MEMBERS bool isKindOf(KindOfType)const;
#define OBJECT_TU_MEMBERS \
 Weapon* getCurrentWeapon(WeaponSlotType*); \
 void setStatusBit(int,bool); \
 void preFireCurrentWeapon(const Object*,const Coord3D*); \
 void setFiringConditionForCurrentWeapon()const; \
 bool getWorldspaceBestContactPoint(Coord3D*,const Coord3D*,const char*,int,int,bool)const; \
 Player* getControllingPlayer()const; \
 const Coord3D* getPosition()const{return &m_cachedPos;} \
 __forceinline bool isEffectivelyDead()const{return (m_privateStatus&1)||((BFMEActionObject*)this)->testStatus(49);}
#include "object.h"
class BfmeArgETB;
class BfmeHostETB {public: void fireCurrentWeapon(BfmeArgETB *);};
class Rva001CD990FireView {public:
 virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();virtual void s7();virtual void s8();virtual void s9();virtual void s10();
 virtual void invoke(Object*,unsigned);
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
 const Coord3D* getGoalPosition()const{return &m_goalPosition;}
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
// Zero Hour's PartitionFilterPossibleToAttack shape. Its out-of-line constructor is
// retail 0x00149E60 (through ILT 0x0001960F): it stores vtable 0x010956C4, m_next = 0,
// then obj at +8, commandSource at +0xC and the attack type at +0x10, in Zero Hour's
// parameter order. ilt_oracle confirms Zero Hour's exact constructor decoration at
// 0x00149E60, but the ledger already gives that name to 0x004C12B0 (where the oracle
// contradicts it), so the class stays address-named until that row is corrected.
enum AbleToAttackType { ATTACK_NEW_TARGET = 0 };
class Rva00149E60 : public PartitionFilter {
  public:
    const Object *m_obj;
    CommandSourceType m_commandSource;
    AbleToAttackType m_attackType;
    Rva00149E60(AbleToAttackType t, const Object *obj, CommandSourceType commandSource);
    virtual bool allow(Object *);
    virtual void slot2();
};
class Rva0016A9F0FunctorValueWrapper : public PartitionFilter {
  public:
    Player *m_08;
    Rva0016A9F0FunctorValueWrapper(Player *p) : m_08(p) {}
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
 StateMachine* getMachine()const{return m_machine;}
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
    if (!weapon) return STATE_FAILURE;
    if (obj->m_privateStatus & 1) return STATE_FAILURE;
    if (obj->m_status[2] & 0x20000) return STATE_FAILURE;
    bool atPosition;
    if (weapon->getTemplate()->flag533() && !(victim && victim->isKindOf((KindOfType)2)))
        atPosition = true;
    else {
        atPosition = false;
        AIUpdateInterface *ai;
        if (victim && (ai = obj->m_ai) && ai->m_curLocomotor &&
            ai->getWhichTurretForCurWeapon() == -1) {
            Coord3D pos;
            pos.x = victim->getPosition()->x;
            pos.y = victim->getPosition()->y;
            pos.z = victim->getPosition()->z;
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
        obj->preFireCurrentWeapon(victim, m_machine->getGoalPosition());
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
        ((Rva001CD990FireView*)obj)->invoke(victim,arg20);
        obj->setStatusBit(27, false);
        float range = weapon->getContinueAttackRange();
        if (range > 0.0f && victim && ((victim->m_status[0] & 1) || victim->isEffectivelyDead())) {
            const Coord3D *original = m_att ? m_att->getOriginalVictimPos() : 0;
            if (original) {
                AIUpdateInterface *ai = obj->m_ai;
                int cmd = ai ? ai->getLastCommandSource() : 2;
                {
                    PartitionFilterSameMapStatus mapFilter(obj);
                    victim = ThePartitionManager->getClosestObject(
                        original, range, 0,
                        Rva0016A9F0FunctorValueWrapper(victim->getControllingPlayer())
                            .link(Rva00149E60(ATTACK_NEW_TARGET, obj, (CommandSourceType)cmd).link(&mapFilter)));
                }
                if (victim) {
                    m_machine->setGoalObject(victim);
                    m_att->notifyNewVictimChosen(victim);
                }
            }
        }
    } else {
        ((BfmeHostETB *)obj)->fireCurrentWeapon((BfmeArgETB *)&m_machine->m_goalPosition);
        obj->setStatusBit(27, false);
    }
    m_att->notifyFired();
    return STATE_SUCCESS;
}
