// cl: /DNDEBUG /MD /EHsc
// BFME AIUpdateInterface::hasHigherPathPriority, RVA 0x00274410, 435 bytes.
// Source: GameLogic/Object/Update/AIUpdate.cpp. Retail adds the signed
// crushable-level comparison and uses BFME kind ordinals 8, 9 and 14.
// Preserve the authentic Override.h conversion/dereference/recursive layers;
// the helper they emit independently matches Overridable::getFinalOverride.

struct Coord3D { float x,y,z; };
struct Coord2D { float x,y; };
typedef bool Bool;
enum ObjectID { INVALID_ID=0 };
enum KindOfType { KINDOF_INFANTRY=8,KINDOF_VEHICLE=9,KINDOF_DOZER=14 };
class Overridable {
public:
 virtual ~Overridable();
 const Overridable *getFinalOverride() const {
  if(next) return next->getFinalOverride();
  return this;
 }
 Overridable *next;
};
class ThingTemplate : public Overridable {
public:
 bool hasKindMask(unsigned mask) const { return (flags & mask)!=0; }
 char pad08[0xc0]; unsigned flags;
};
template<class T> class OVERRIDE {
 const T *value;
public:
 const T *operator*() const { if(!value) return 0; return (T*)value->getFinalOverride(); }
 operator const T*() const { return operator*(); }
};
class Thing {
public:
 virtual ~Thing();
 const ThingTemplate *getTemplate() const {return m_template;}
 const Coord3D *getUnitDirectionVector2D() const;
 bool isKindOf(KindOfType) const;
 const Coord3D *getPosition() const { return &position; }
 OVERRIDE<ThingTemplate> m_template;
 char pad08[0x30]; Coord3D position;
 char pad44[0x30];
};
class Object : public Thing {
public:
 ObjectID id; // Object +0x74
 unsigned char getCrushableLevel() const;
 ObjectID getID() const {return id;}
};
class AIUpdateInterface {
public:
 Bool hasHigherPathPriority(AIUpdateInterface *) const;
 Object *getObject() const {return object;}
 char prefix[8]; Object *object;
};
Bool AIUpdateInterface::hasHigherPathPriority(AIUpdateInterface *otherAI) const
{
 const Object *other = otherAI->getObject();
 const Object *self = getObject();
 unsigned mask=0x4000;
 if (self->getTemplate()->hasKindMask(mask) && !other->getTemplate()->hasKindMask(mask)) return true;
 if (!self->getTemplate()->hasKindMask(mask) && other->getTemplate()->hasKindMask(mask)) return false;
 if (static_cast<char>(self->getCrushableLevel()) > static_cast<char>(other->getCrushableLevel())) return true;
 self = getObject();
 if (self->isKindOf(KINDOF_VEHICLE) && other->isKindOf(KINDOF_INFANTRY)) return true;
 if (self->isKindOf(KINDOF_INFANTRY) && other->isKindOf(KINDOF_VEHICLE)) return false;
 const Coord3D *ourDirection = self->getUnitDirectionVector2D();
 Coord3D ourDir;
 ourDir.x = ourDirection->x; ourDir.y = ourDirection->y;
 const Coord3D *otherDirection = other->getUnitDirectionVector2D();
 Coord3D otherDir;
 otherDir.x = otherDirection->x; otherDir.y = otherDirection->y;
 // Materialize comparisons as a byte: retail returns AL without clearing EAX.
 // Omitting the cast adds two XORs and changes both ID-load schedules.
 if (ourDir.x*otherDir.x + ourDir.y*otherDir.y <= 0) return (unsigned char)(getObject()->getID() < other->getID());
 Coord2D combinedDir;
 combinedDir.x = ourDir.x + otherDir.x;
 combinedDir.y = ourDir.y + otherDir.y;
 Coord2D vectorToOther;
 vectorToOther.x = other->getPosition()->x - getObject()->getPosition()->x;
 vectorToOther.y = other->getPosition()->y - getObject()->getPosition()->y;
 float dotProduct = combinedDir.x*vectorToOther.x + combinedDir.y*vectorToOther.y;
 if(dotProduct>0) return false;
 if(dotProduct<0) return true;
 return (unsigned char)(getObject()->getID() < other->getID());
}
