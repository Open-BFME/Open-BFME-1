// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// Address-derived thiscall body; evidence: targets/game/reverse/identity_evidence/002c1480-passenger-release.md
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#define _OPERATOR_NEW_DEFINED_ 1
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../../../../Libraries/Source/WWVegas/WWMath/matrix3d.h"
enum ObjectStatusTypes { RVA002C1480_STATUS_59 = 59 };
#define BFME_HAVE_COORD3D 1
#define THING_TU_MEMBERS float getHeightAboveTerrain() const; void getUnitDirectionVector3D(Coord3D &) const; void setOrientation(float);
#define OBJECT_TU_MEMBERS void notifyModelConditionChanged(); void clearStatus(ObjectStatusTypes);
#include "../../object.h"
#undef OBJECT_TU_MEMBERS
#undef THING_TU_MEMBERS
#include "../../../../GameClient/FXListRetail.h"
class PhysicsBehavior {
public:
    void applyMotiveForce(const Coord3D *);
    void rva0029A6A0(bool);
    char m_prefix00[0x5f];
    bool m_flag5f;
};
class BFMEReportDamageSource { public: void report(Object *, int); };
typedef _STL::list<Object *> Rva002C1480Items;
struct Rva2225E0Filter;
class Rva002C1480Contain {
public:
#define SLOT(n) virtual void slot##n();
    SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
    SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
    SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
    SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31)
    SLOT(32) SLOT(33) SLOT(34) SLOT(35)
    virtual void remove(Object *, bool);
    SLOT(37) SLOT(38) SLOT(39) SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44)
    SLOT(45) SLOT(46) SLOT(47) SLOT(48) SLOT(49) SLOT(50) SLOT(51) SLOT(52)
    SLOT(53) SLOT(54) SLOT(55) SLOT(56) SLOT(57) SLOT(58) SLOT(59) SLOT(60)
    SLOT(61) SLOT(62) SLOT(63)
    virtual int count(Rva2225E0Filter *);
    virtual const Rva002C1480Items *items() const;
#undef SLOT
};
class Rva002C1480Machine {
public:
#define SLOT(n) virtual void slot##n();
    SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06)
    SLOT(07) SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13)
    virtual void setGoalObject(const Object *);
#undef SLOT
};
struct Rva002C1480Data {
    char m_prefix00[0x6c];
    float m_time6c;
    float m_height70;
    char m_prefix74[0x80-0x74];
    const FXList *m_fx80;
};
class Rva002C1480Owner {
public:
    void method();
    char m_prefix00[4];
    const Rva002C1480Data *m_data04;
    Object *m_object08;
    char m_prefix0c[0x30-0x0c];
    Rva002C1480Machine *m_machine30;
    char m_prefix34[0x1cc-0x34];
    void *m_locomotor1cc;
    char m_prefix1d0[0x3f0-0x1d0];
    unsigned m_flags3f0;
    float m_time3f4;
    unsigned m_value3f8;
    unsigned m_id3fc;
    char m_prefix400[0x470-0x400];
    float m_speed470;
};

// ?scaleDirection@@YAXAAUCoord3D@@M@Z absent-from-retail
static inline void scaleDirection(Coord3D &direction, float scale)
{
    direction.x *= scale;
    direction.y *= scale;
    direction.z *= scale;
}

// ?method@Rva002C1480Owner@@QAEXXZ
void Rva002C1480Owner::method()
{
    unsigned char active = (unsigned char)(m_flags3f0 >> 6);
    if (!(active & 1))
        return;
    Object *object = m_object08;
    float height = ((Thing *)object)->getHeightAboveTerrain() > 0.0f ?
        ((Thing *)object)->getHeightAboveTerrain() : 0.0f;
    Rva002C1480Contain *contain = (Rva002C1480Contain *)object->m_contain;
    if (!contain || (unsigned)contain->count(0) <= 0)
    {
        m_time3f4 = 0.0f;
        return;
    }
    m_time3f4 += 0.2f;
    const Rva002C1480Data *data = m_data04;
    if (!((data->m_time6c > 0.0f && m_time3f4 > data->m_time6c) ||
        (data->m_height70 > 0.0 && height > data->m_height70)))
        return;
    m_flags3f0 &= ~0x40u;
    const Rva002C1480Items *items = contain->items();
    Object *passenger = 0;
    for (Rva002C1480Items::const_iterator it = items->begin(); it != items->end();)
    {
        Object *current = *it;
        ++it;
        if (current->m_id == m_id3fc)
        {
            passenger = current;
            break;
        }
    }
    if (passenger)
    {
        m_id3fc = 0;
        contain->remove(passenger, false);
        ((Thing *)passenger)->setOrientation(object->m_transform.Get_Z_Rotation());
        m_machine30->setGoalObject(0);
        PhysicsBehavior *physics = passenger->m_physics;
        if (physics && m_locomotor1cc)
        {
            Coord3D direction;
            ((Thing *)object)->getUnitDirectionVector3D(direction);
            scaleDirection(direction, m_speed470 * 0.5f);
            Coord3D force;
            force.x = direction.x;
            force.y = direction.y;
            force.z = -6.0f;
            physics->applyMotiveForce(&force);
            physics->rva0029A6A0(true);
            if (data->m_fx80)
                FXList::doFXObj(data->m_fx80, passenger, object);
            unsigned char notify = (unsigned char)(m_flags3f0 >> 8);
            if (notify & 1)
            {
                ((BFMEReportDamageSource *)object)->report(passenger, 1);
                physics->m_flag5f = true;
            }
        }
        if (!(((const unsigned char *)passenger->m_modelConditionFlags)[8] & 0x80))
        {
            passenger->m_modelConditionFlags[2] |= 0x80;
            passenger->notifyModelConditionChanged();
        }
        passenger->clearStatus(RVA002C1480_STATUS_59);
        m_value3f8 = 0;
        m_time3f4 = 0.0f;
        return;
    }
}
