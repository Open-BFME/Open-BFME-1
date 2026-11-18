// ?slot14@Rva002BAA40@@UAEXXZ
// cl: /DNDEBUG /MD /EHsc /Igame/GameEngine/Source /Igame/Libraries/Include /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include
// stlport
#include <bitset>

#include "../../../../../Include/Common/ScalarTypes.h"



#include <Lib/Coord3D.h>

class Overridable
{
public:
    // recursively ask if there is a next override, and if not, return this.
    const Overridable *getFinalOverride() const
    {
        if (m_nextOverride)
            return m_nextOverride->getFinalOverride();
        return this;
    }
    void *m_vptr;
    Overridable *m_nextOverride;
};

#define _OVERRIDABLE_H_
#include <Common/Override.h>

// The retail radius is at +0x14; the shared GeometryInfo header has a different layout.
class GeometryInfo
{
public:
    Real getBoundingSphereRadius() const { return m_boundingSphereRadius; }
    unsigned char m_pad[0x14];
    Real m_boundingSphereRadius;
};

class ThingTemplate : public Overridable
{
public:
    const GeometryInfo &getTemplateGeometryInfo() const { return m_geometryInfo; }
    unsigned char m_pad[0x58];
    GeometryInfo m_geometryInfo;
};

class Matrix3D
{
public:
    Real Get_Z_Rotation() const;
    Real m_values[12];
};

enum KindOfType { KINDOF_003F = 63, KINDOF_0098 = 152 };

#define MATRIX3D_H
#define BFME_HAVE_COORD3D
#define THING_TU_MEMBERS \
    Bool isKindOf(KindOfType kind) const; \
    const ThingTemplate *getTemplate() const \
    { \
        OVERRIDE<ThingTemplate> tmpl(m_template); \
        return tmpl; \
    } \
    const Coord3D *getPosition() const { return &m_cachedPos; } \
    Real getOrientation() const { return m_transform.Get_Z_Rotation(); }
#define OBJECT_TU_MEMBERS \
    unsigned int getID() const { return m_id; } \
    void setProducer(const Object *producer);
#include "GameLogic/Object/object.h"

template<int NUMBITS> class BitFlags
{
public:
    enum BogusInitType { kInit = 0 };
    BitFlags(BogusInitType, Int index) { m_bits.set(index); }
    _STL::bitset<NUMBITS> m_bits;
};
// This inherited copy view covers six words without asserting the retail mask bit count.
typedef BitFlags<192> KindOfMaskType;
extern const KindOfMaskType KINDOFMASK_NONE;

class PartitionFilter
{
public:
    PartitionFilter() : m_next(0) {}
    virtual ~PartitionFilter() {}
    virtual Bool allow(Object *object) = 0;
    virtual Int getPlayerMask();
    PartitionFilter *link(PartitionFilter *next);
    PartitionFilter *m_next;
};

class PartitionFilterWouldCollide : public PartitionFilter
{
public:
    PartitionFilterWouldCollide(const Coord3D &position, const GeometryInfo &geometry, Real angle, Bool desired)
    {
        m_position.x = position.x;
        m_position.y = position.y;
        m_position.z = position.z;
        m_geometry = &geometry;
        m_angle = angle;
        m_desired = desired;
    }
    virtual Bool allow(Object *object);
    Coord3D m_position;
    const GeometryInfo *m_geometry;
    Real m_angle;
    Bool m_desired;
};

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
    __declspec(noinline) PartitionFilterAcceptByKindOf(const KindOfMaskType &mustBeSet, const KindOfMaskType &mustBeClear)
        : m_mustBeSet(mustBeSet), m_mustBeClear(mustBeClear) {}
    virtual Bool allow(Object *object);
    KindOfMaskType m_mustBeSet, m_mustBeClear;
};

class PartitionManager
{
public:
    Object *getClosestObject(const Coord3D *position, Real radius, Int distanceType, PartitionFilter *filters);
};
extern PartitionManager *ThePartitionManager;

class Gen002BA240
{
public:
    void handle(unsigned int id);
};

class Rva002BAA40
{
public:
    virtual void slot14();
    unsigned char m_pad[4];
    Object *m_object;
    unsigned char m_pad2[0x88];
    unsigned int m_lastId;
};

// ?slot14@Rva002BAA40@@UAEXXZ
void Rva002BAA40::slot14()
{
    if (m_lastId != 0)
        return;
    Object *owner = m_object;
    const GeometryInfo &geometry = owner->getTemplate()->getTemplateGeometryInfo();
    Object *found = ThePartitionManager->getClosestObject(owner->getPosition(), geometry.getBoundingSphereRadius() * 1.1f, 1,
        PartitionFilterAcceptByKindOf(KindOfMaskType(KindOfMaskType::kInit, 104), KINDOFMASK_NONE).link(
            &PartitionFilterWouldCollide(*owner->getPosition(), geometry, owner->getOrientation(), true)));
    if (found == 0)
        return;
    Bool kind = found->isKindOf(KINDOF_003F);
    if (owner->isKindOf(KINDOF_0098) == kind)
    {
        reinterpret_cast<Gen002BA240 *>(this)->handle(found->getID());
        found->setProducer(owner);
    }
}
