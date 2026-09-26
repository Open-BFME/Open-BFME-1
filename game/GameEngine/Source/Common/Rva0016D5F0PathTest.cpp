// cl: /DNDEBUG /MD /EHsc
// Retail 0x0016D5F0: the second entry of the three-entry table installed by
// Rva0016D590VptrZeroObject.  The adjacent 0x0016D5C0 entry is the already
// recovered BfmeThingESCb-shaped sibling, but the debug string embedded in
// this body names AIAttackFireDuringApproachState::computePath.  Keep the
// owner address-derived until those two identity clues are reconciled.

typedef bool Bool;

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

class BfmeCheckerNW
{
public:
	char bfmeBusyNW();
};

class Object
{
public:
	Relationship getRelationship(const Object *other) const;

	char m_pad00[0x38];
	Coord3D m_position;
	char m_pad44[0x1C0];
	void *m_ai;
	BfmeCheckerNW *m_checker;
	char m_pad20C[0x138];
	unsigned char m_flags;
};

class GameLogic
{
public:
	char m_pad00[0x1A0];
	int m_desyncLogFrameCount;
};

class AI
{
public:
	char m_pad00[0x0C];
	void *m_pathfinder;
};

class CRCParameterCheck
{
};

extern GameLogic *TheBfmeGameLogic;
extern AI *TheAI;
extern CRCParameterCheck *TheCRCParameterCheck;
extern void j_0003a17a(void);
extern void j_000296b8(void);

class Rva0016D5F0Pathfinder;

typedef void (__cdecl *BfmeCritterDesyncLog)(
	void *, const char *, ...);

typedef Bool (Rva0016D5F0Pathfinder::*FindMeleeEngagementLocation)(
	Object *, void *, void *, Coord3D *, Object *);

class Rva0016D5F0Pathfinder
{
};

class Rva0016D5F0PathTest
{
public:
	Bool run(Object *target);

	char m_pad00[8];
	Object *m_source;
	void *m_meleeContext;
};

Bool Rva0016D5F0PathTest::run(Object *target)
{
	register Rva0016D5F0PathTest *self = this;
	register Object *targetObject = target;
	register unsigned char targetFlags = targetObject->m_flags;
	if ((targetFlags & 1) != 0)
		return false;

	if (((self->m_source->m_flags ^ targetFlags) & 8) != 0)
		return false;

	if (self->m_source->getRelationship(targetObject) != ENEMIES)
		return false;

	BfmeCheckerNW *checker = targetObject->m_checker;
	if (checker != 0 && checker->bfmeBusyNW())
		return false;

	Coord3D position;
	position.x = targetObject->m_position.x;
	position.y = targetObject->m_position.y;
	position.z = targetObject->m_position.z;

	if (TheBfmeGameLogic->m_desyncLogFrameCount > 0 && TheCRCParameterCheck != 0)
	{
		((BfmeCritterDesyncLog)j_0003a17a)(
			TheCRCParameterCheck,
			(const char *)0x01097758,
			(double)position.x,
			(double)position.y);
	}

	void *sourceAI = self->m_source->m_ai;
	Rva0016D5F0Pathfinder *pathfinder =
		(Rva0016D5F0Pathfinder *)TheAI->m_pathfinder;
	union
	{
		void (*raw)(void);
		FindMeleeEngagementLocation member;
	} fn;
	fn.raw = j_000296b8;

	return (pathfinder->*fn.member)(
		self->m_source,
		self->m_meleeContext,
		(char *)sourceAI + 0x1A8,
		&position,
		targetObject);
}
