// ?test@Rva002DF120@@QAEEPAX0@Z
// partial score=0.95 date=2026-09-12
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// Shared two-argument object-match predicate, retail 0x002DF120.
// Neighbor wrappers Rva002DF100Test / Rva002DF4C0Test and Rva002DCDA0Test
// call this as unsigned char test(void *, void *).  The filter lives on
// this at +0x50 (lea ecx,[ebp+50h]); the first argument is only the
// lookup context (object at +4, id at +8).

extern "C" float fabs(float);
#pragma intrinsic(fabs)
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Rva002DF100
{
public:
	unsigned char testOne(void *value);
};

enum KindOfType
{
	KINDOF_INVALID = 0
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL,
	ALLIES
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

class Player;

class Object
{
public:
	Player *getControllingPlayer() const;
	Relationship getRelationship(const Object *that) const;
	bool isSignificantlyAboveTerrain() const;

	char m_pad00[0x40];
	float m_positionZ;
	char m_pad44[0x74 - 0x44];
	int m_id;
	int m_producerID;
	char m_pad7c[0x343 - 0x7c];
	unsigned char m_scriptStatus;
	char m_pad344[0x4d8 - 0x344];
	int m_flags4d8;
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

	char m_pad00[0x50];
	Rva2225E0Filter m_filter;
};

struct Rva002DF120MatchContext
{
	char m_pad00[4];
	Object *m_object;
	int m_id;
};

unsigned char Rva002DF120::test(void *first, void *second)
{
	Object *other = (Object *)second;
	if (other == 0)
		return 0;
	if (!testOne(first))
		return 0;

	Object *found = TheBfmeGameLogic->findObjectByID(
		((Rva002DF120MatchContext *)first)->m_id);
	if (found == 0)
		return testOne(first);

	int flags = ((Rva002DF120MatchContext *)first)->m_object->m_flags4d8;
	if ((flags & 1) == 0)
	{
		if (found == other || found->m_producerID == other->m_id)
			return 0;
	}

	if ((flags & 0x20) != 0)
	{
		if (((Thing *)found)->getTemplate()->isEquivalentTo(
			((Thing *)other)->getTemplate()) &&
			found->getRelationship(other) == ALLIES)
			return 0;
	}

	if (((Thing *)other)->isKindOf((KindOfType)0x19) && (signed char)flags >= 0)
		return 0;
	if ((flags & 0x40) != 0 && other->isSignificantlyAboveTerrain())
		return 0;

	if ((flags & 0x100) != 0)
	{
		if (fabs(other->m_positionZ - found->m_positionZ) > g_bfmeDirectionWeight1285)
			return 0;
	}

	if ((flags & 0x200) != 0 && ((Thing *)other)->isKindOf((KindOfType)0x36))
		goto accept;

	if ((other->m_scriptStatus & 0x10) == 0)
	{
		int relationship = found->getRelationship(other);
		if (relationship == ALLIES)
		{
			_ReadWriteBarrier();
			goto accept;
		}
		int required = relationship != ENEMIES ? 8 : 4;
		if ((flags & required) == 0)
			return 0;
	}

accept:
	return m_filter.accepts(other, found->getControllingPlayer()) != 0;
}
