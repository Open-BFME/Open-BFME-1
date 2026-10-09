// cl: /DNDEBUG /MD /EHsc
class Coord3D;
class Object;

#define SLOT(N) virtual void slot##N() = 0

class Rva216940Facet
{
public:
	SLOT(00); SLOT(01); SLOT(02); SLOT(03); SLOT(04); SLOT(05); SLOT(06); SLOT(07);
	SLOT(08); SLOT(09); SLOT(10); SLOT(11); SLOT(12); SLOT(13); SLOT(14); SLOT(15);
	SLOT(16); SLOT(17); SLOT(18); SLOT(19); SLOT(20); SLOT(21); SLOT(22); SLOT(23);
	SLOT(24); SLOT(25); SLOT(26); SLOT(27); SLOT(28); SLOT(29); SLOT(30); SLOT(31);
	SLOT(32); SLOT(33); SLOT(34); SLOT(35); SLOT(36); SLOT(37); SLOT(38); SLOT(39);
	SLOT(40); SLOT(41); SLOT(42); SLOT(43); SLOT(44); SLOT(45); SLOT(46); SLOT(47);
	SLOT(48); SLOT(49); SLOT(50); SLOT(51); SLOT(52); SLOT(53); SLOT(54); SLOT(55);
	SLOT(56); SLOT(57); SLOT(58); SLOT(59); SLOT(60); SLOT(61); SLOT(62); SLOT(63);
	SLOT(64); SLOT(65); SLOT(66); SLOT(67); SLOT(68); SLOT(69); SLOT(70); SLOT(71);
	SLOT(72); SLOT(73); SLOT(74);
	virtual bool canAccept() = 0;              // slot 75, +0x12c
	virtual bool accepts(Object *) = 0;        // slot 76, +0x130
	virtual void add(Object *) = 0;            // slot 77, +0x134
	SLOT(78);
	virtual int getLeaderId() = 0;             // slot 79, +0x13c
};

class Rva216940FacetSource
{
public:
	SLOT(00); SLOT(01); SLOT(02); SLOT(03); SLOT(04); SLOT(05); SLOT(06); SLOT(07);
	SLOT(08); SLOT(09); SLOT(10); SLOT(11); SLOT(12); SLOT(13); SLOT(14); SLOT(15);
	SLOT(16); SLOT(17); SLOT(18); SLOT(19); SLOT(20); SLOT(21); SLOT(22); SLOT(23);
	SLOT(24); SLOT(25);
	virtual Rva216940Facet *getFacet() = 0;       // slot 26, +0x68
};

enum Relationship { RELATIONSHIP_ALLIES = 2 };
enum KindOfType { KINDOF_6C = 0x6c };

#define THING_TU_MEMBERS bool isKindOf(KindOfType) const;
#define OBJECT_TU_MEMBERS \
    int getID() const { return m_id; } \
    Object *getContainedBy() const { Object *m_related = m_containedBy; return m_related; } \
    __declspec(dllimport) __forceinline Rva216940FacetSource *getContain() const { Rva216940FacetSource *m_facetSource = (Rva216940FacetSource *)m_contain; return m_facetSource; } \
    Relationship getRelationship(const Object *) const;
#include "../object.h"
#undef OBJECT_TU_MEMBERS
#undef THING_TU_MEMBERS

class BFMEActionObject
{
public:
	bool testStatus(int) const;
};

class GameLogic
{
public:
	Object *findObjectByID(int);
};

extern GameLogic *TheBfmeGameLogic;

class HordeMemberCollide
{
public:
	virtual void onCollide(Object *other, const Coord3D *location, const Coord3D *normal);
};

// ?onCollide@HordeMemberCollide@@UAEXPAVObject@@PBVCoord3D@@1@Z
// Open BFME 2: Code/GameEngine/Source/GameLogic/Object/Collide/HordeMemberCollideOnCollide.cpp
void HordeMemberCollide::onCollide(Object *other, const Coord3D *, const Coord3D *)
{
    if (!other)
        return;
    Object *self = *(Object **)((char *)this - 8);
    Object *related = self->getContainedBy();
    if (!related)
        return;
    Rva216940FacetSource *facetSource = related->getContain();
    if (!facetSource)
        return;
    Rva216940Facet *facet = facetSource->getFacet();
    if (!facet)
        return;
    if (!facet->getLeaderId())
        return;
    if (other->getID() == facet->getLeaderId())
    {
        facet->add(other);
        return;
    }
    Object *recordObject = TheBfmeGameLogic->findObjectByID(facet->getLeaderId());
    if (facet->accepts(recordObject))
        return;
    Object *otherContainer = other->getContainedBy();
    if (otherContainer && otherContainer->getID() == facet->getLeaderId())
    {
        facet->add(other);
        return;
    }
    Object *collided = other;
    if (((BFMEActionObject *)other)->testStatus(0x25))
        collided = other->getContainedBy();
    if (!collided)
        return;
    if (!((Thing *)collided)->isKindOf(KINDOF_6C))
        return;
    if (self->getRelationship(collided) != RELATIONSHIP_ALLIES)
        return;
    Rva216940Facet *otherFacet = 0;
    if (collided->getContain())
        otherFacet = collided->getContain()->getFacet();
    if (!otherFacet->accepts(recordObject))
        return;
    if (!otherFacet->canAccept())
        return;
    facet->add(recordObject);
}
