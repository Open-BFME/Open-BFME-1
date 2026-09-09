// ?test@Rva002DF120@@QAEEPAX0@Z
// partial score=0.9 date=2026-09-07
// Open-BFME: shared two-argument object match predicate, retail 0x002DF120.

#include <math.h>

class Rva002DF100
{
public:
	unsigned char testOne(void *value);
};

enum KindOfType
{
	KindOfTypeValue
};

enum Relationship
{
	RelationshipValue
};

class ThingTemplate
{
public:
	bool isEquivalentTo(const ThingTemplate *that) const;
};

class Thing
{
public:
	const ThingTemplate *getTemplate() const;
	bool isKindOf(KindOfType kind) const;
};

class BfmeThingAIA
{
public:
	bool bfmeAskAIA(int kind);
};

class Player;

class Object
{
public:
	Player *getControllingPlayer() const;
	Relationship getRelationship(const Object *that) const;
	bool isSignificantlyAboveTerrain() const;

	char m_pad00[0x40];
	float m_position40;
	char m_pad44[0x74 - 0x44];
	int m_field74;
	int m_field78;
	char m_pad80[0x4d8 - 0x7c];
	int m_flags4d8;
};

class BfmeObjectCall
{
public:
	Player *getControllingPlayer() const;
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

class Rva2225E0Filter
{
public:
	bool accepts(Object *object, Player *player);
};

extern GameLogic *TheBfmeGameLogic;
extern const float g_bfmeDirectionWeight1285;

class Rva002DF120 : public Rva002DF100
{
public:
	unsigned char test(void *first, void *second);
};

struct Rva002DF120MatchContext
{
	char m_pad00[4];
	Object *m_object;
	int m_id;
	char m_pad0c[0x50 - 0x0c];
	Rva2225E0Filter m_filter;
};

unsigned char Rva002DF120::test(void *first, void *second)
{
	if (second == 0)
		return 0;
	if (!testOne(first))
		return 0;
	Object *other = (Object *)second;

	Object *found = TheBfmeGameLogic->findObjectByID(
		((Rva002DF120MatchContext *)first)->m_id);
	if (found == 0)
		return testOne(first);

	int flags = ((Rva002DF120MatchContext *)first)->m_object->m_flags4d8;
	if ((flags & 1) == 0)
	{
		if (found == other || found->m_field78 == other->m_field74)
			return 0;
	}

	if ((flags & 0x20) != 0)
	{
		if (((Thing *)found)->getTemplate()->isEquivalentTo(
			((Thing *)other)->getTemplate()) &&
			found->getRelationship(other) == (Relationship)2)
			return 0;
	}

	if (((BfmeThingAIA *)other)->bfmeAskAIA(0x19) && (flags & 0x80) == 0)
		return 0;
	if ((flags & 0x40) != 0 && found->isSignificantlyAboveTerrain())
		return 0;

	if ((flags & 0x100) != 0)
	{
		if (fabs(other->m_position40 - found->m_position40) > g_bfmeDirectionWeight1285)
			return 0;
	}

	if ((flags & 0x200) != 0 && ((BfmeThingAIA *)other)->bfmeAskAIA(0x36))
		goto accept;

	if ((*(unsigned char *)((char *)other + 0x343) & 0x10) == 0)
	{
		int relationship = found->getRelationship(other);
		int required = relationship;
		if (required != (Relationship)2)
			required = required != (Relationship)0 ? 8 : 4;
		if ((flags & required) == 0)
			return 0;
	}

	accept:
	return ((Rva002DF120MatchContext *)first)->m_filter.accepts(other,
		((const BfmeObjectCall *)found)->getControllingPlayer()) != 0;
}
