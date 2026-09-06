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
	unsigned char m_status90;
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

class BfmeAIRoot
{
public:
	char m_bfmeHead[0x14];
	BfmeAIData *m_aiData;
};

extern "C" BfmeAIRoot *TheAIParseDefinitionAI;

// The retail body is reached through this import thunk rather than through a
// named Object method in the current source tree.
#pragma comment(linker, "/alternatename:?getDistanceSquared@Object@@QBEMPBV1@@Z=?j_00043ced@@YAXXZ")

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
	if (target->m_status90 & 0x40)
		goto failure;
	if (target->getRelationship(source) != NEUTRAL)
		goto failure;

	Real distanceLimit = TheAIParseDefinitionAI->m_aiData->m_bfmeC4;
    if (!(source->getDistanceSquared(target) > distanceLimit * distanceLimit))
        return source->getControllingPlayer()->m_bfme2c == 0;

failure:
	return false;
}
