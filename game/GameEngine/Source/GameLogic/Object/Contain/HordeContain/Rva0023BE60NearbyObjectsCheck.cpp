// cl: /DNDEBUG /MD /EHs-c-
// Retail 0x0023BE60 (189 bytes, thiscall, ret 4). Reached through ILT 0x00004A11
// from the HordeContain.cpp member bodies 0x00245420 and 0x0024E310 (and 0x002417E0),
// which pass their own receiver in ECX plus one Object*. Owner class and method
// name are not proven, so both keep the address token. AI+0x0C is ZH m_pathfinder;
// the pathfinder query at 0x003E4680 (ILT 0x00027AB6, ret 12) is address-derived.

struct Coord3D { float x, y, z; };
typedef unsigned int ObjectID;

class Overridable {
public:
	const Overridable *getFinalOverride() const;
	char pad000[4];
	Overridable *next;
	char pad008[0xC8 - 8];
	unsigned flagsC8;
	char padCC[8];
	unsigned flagsD4;
};

class Object {
public:
	char pad000[4];
	Overridable *m_template;
	char pad008[0x38 - 8];
	Coord3D position;
	char pad044[0x74 - 0x44];
	ObjectID id;
	char pad078[0x214 - 0x78];
	Object *m_containedBy;
};

class Rva003E4680Pathfinder {
public:
	int rva003E4680(Object *, const Coord3D *, ObjectID *);
};

class AI {
public:
	char pad000[0xC];
	Rva003E4680Pathfinder *pathfinder;
};

class GameLogic {
public:
	Object *findObjectByID(int);
};

extern AI *TheAI;
extern GameLogic *TheBfmeGameLogic;

class Rva0023BE60Receiver {
public:
	char pad000[8];
	Object *objectAt8;
	bool rva0023BE60(Object *target);
};

bool Rva0023BE60Receiver::rva0023BE60(Object *target)
{
	const Overridable *targetData = target->m_template;
	if (targetData && targetData->next)
		targetData = targetData->next->getFinalOverride();
	if (targetData->flagsC8 & 0x800)
		return true;

	ObjectID nearby[16];
	Rva003E4680Pathfinder *pathfinder = TheAI->pathfinder;
	Object *owner = objectAt8;
	int count = pathfinder->rva003E4680(target, &target->position, nearby);
	int i = 0;
	if (count > 0) {
		ObjectID ownerId = owner->id;
		GameLogic *logic = TheBfmeGameLogic;
		do {
			ObjectID id = nearby[i];
			if (id == ownerId)
				continue;
			Object *candidate = logic->findObjectByID(id);
			if (!candidate)
				return false;
			if (candidate->m_containedBy == owner)
				continue;
			const Overridable *candidateData = candidate->m_template;
			if (candidateData && candidateData->next)
				candidateData = candidateData->next->getFinalOverride();
			if (candidateData->flagsD4 & 0x1000)
				continue;
			return false;
		} while (++i < count);
	}
	return true;
}
