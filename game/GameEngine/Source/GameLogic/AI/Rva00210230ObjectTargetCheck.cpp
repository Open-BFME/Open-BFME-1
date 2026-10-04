// cl: /DNDEBUG /MD /EHsc
// Retail 0x00210230: BFME object-target eligibility predicate.
//
// The owning retail name is not recovered.  The two arguments are the source
// object and candidate target.  A target is accepted only when it is neutral
// to the source, within the BFME AI distance, and the source belongs to a
// computer player; the status and active-command checks are BFME additions.

typedef unsigned char Bool;
typedef float Real;
typedef int Int;

enum Relationship
{
	NEUTRAL = 0
};

class Player
{
public:
	char m_bfmeHead[0x2C];
	void *m_bfme2c;
};

class BfmeObjectAI
{
public:
	char m_bfmeHead[0x34];
	void *m_field34;
};

class Object
{
public:
	Relationship getRelationship(const Object *other) const;
	Real getDistanceSquared(const Object *other) const;
	Player *getControllingPlayer() const;

	char m_bfmeHead[0x90];
	unsigned char m_status;
	char m_bfmeHead91[0x07];
	unsigned char m_status98;
	char m_bfmeHead99[0x16B];
	BfmeObjectAI *m_ai;
};

class BfmeAIData
{
public:
	char m_bfmeHead[0xC4];
	Real m_bfmeC4;
};

// 0x012EF214 is retail's TheAI singleton. The old stand-in was C-linkage, so it
// emitted an unmangled TheAIParseDefinitionAI; retail's own bytes name the
// global ?TheAI@@3PAVAI@@A, so the C++ spelling with the real class name is
// the one to bind. This TU has no AI.h in its include closure, so the class is
// renamed in place rather than pulled in.
class AI
{
public:
	char m_bfmeHead[0x14];
	BfmeAIData *m_aiData;
};

extern AI *TheAI;

// The retail separation-squared body is reached through this incremental-link
// thunk (0x00043CED, pinned ?getDistanceSquared@Object@@QBEMPBV1@@Z), so the
// call binds the thunk directly instead of through a stand-in name.
extern void j_00043ced();

class Rva00210230
{
public:
	static Bool check(Object *source, Object *target);
};

// ?check@Rva00210230@@SAEPAVObject@@0@Z
Bool Rva00210230::check(Object *source, Object *target)
{
	if (!target)
		goto failure;
	if (!source)
		goto failure;
	if (source->m_status98 & 0x20)
		goto failure;

	BfmeObjectAI *ai = source->m_ai;
	if (ai && ai->m_field34)
		goto failure;
	if (target->m_status & 0x40)
		goto failure;
	if (target->getRelationship(source) != NEUTRAL)
		goto failure;

	Real distanceLimit = TheAI->m_aiData->m_bfmeC4;
	typedef Real (Object::*DistanceSquared)(const Object *) const;
	union { void (*fn)(); DistanceSquared call; } distanceSquared = { j_00043ced };
    if (!((source->*distanceSquared.call)(target) > distanceLimit * distanceLimit))
        return source->getControllingPlayer()->m_bfme2c == 0;

failure:
	return false;
}
