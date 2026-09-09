// ?repairStructure@AIPlayer@@UAEXW4ObjectID@@@Z
// partial score=0.75 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc
// Open-BFME: AIPlayer::repairStructure, retail 0x00165070, 101 bytes.
//
// Queues a damaged structure into the dozer repair queue, skipping a
// structure already queued and one queued once MAX_STRUCTURES_TO_REPAIR deep.
// The Zero Hour twin also inlines GameLogic::findObjectByID (the ZH header's
// flat-vector body) and tests isKindOf(KINDOF_BRIDGE) with an empty body.
// Retail here still calls the out-of-line ILT thunk at 0x0001F253 and has no
// isKindOf check, matching the hash_map-era BFME1 GameLogic that
// GameLogicFindObjectByID.cpp already recovered, so this TU keeps GameLogic
// declaration-only to avoid the header's inline vector lookup and drops the
// bridge check the retail bytes do not have.
//
// probe.py: 24 non-relocation byte diffs out of 101 (ours compiles to 102
// bytes). Every early-exit guard (findObjectByID call, null obj, null
// getBodyModule(), getDamageState()==0) is byte-exact through +0x2b. The
// repair-queue loop and tail also match in shape and callee-saved register
// SET (ebx and ebp both used, matching retail's push/pop pattern), but
// retail assigns the queue-count value to ebx and the queued id to edx while
// this compile mirrors them (edx for count, ebx for id) -- shape_levers.md's
// register-mirror lever (declare locals in retail's materialization order)
// was already applied and did not flip the assignment. Tried and rejected:
// caching the array base pointer in a local (produces indexed [esi+eax*4]
// addressing instead of retail's pointer-walk), computing the queued id
// before the count>0 guard (loses the ebp reload), and replacing the tail
// `structuresInQueue() = n + 1` with `++structuresInQueue()` (compiles to
// retail's direct `inc dword ptr [esi+0x60]` but then drops ebp entirely,
// a worse match at 50 diff bytes). This 24-byte version is the best found.

class Object;
enum ObjectID { OBJECTID_INVALID = 0 };

class BodyModuleInterface
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0C();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1C();
	virtual int getDamageState() const;		// +0x20; BODY_PRISTINE == 0
};

class Object
{
public:
	ObjectID getID() const
	{
		return *reinterpret_cast<const ObjectID *>(
			reinterpret_cast<const char *>(this) + 0x74);
	}
	BodyModuleInterface *getBodyModule() const
	{
		return *reinterpret_cast<BodyModuleInterface *const *>(
			reinterpret_cast<const char *>(this) + 0x200);
	}
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};
extern GameLogic *TheGameLogic;

enum { MAX_STRUCTURES_TO_REPAIR = 2 };

class AIPlayer
{
public:
	virtual void repairStructure(ObjectID structure);

private:
	ObjectID *structuresToRepair()
	{
		return reinterpret_cast<ObjectID *>(reinterpret_cast<char *>(this) + 0x48);
	}
	int &structuresInQueue()
	{
		return *reinterpret_cast<int *>(reinterpret_cast<char *>(this) + 0x60);
	}
};

// ?repairStructure@AIPlayer@@UAEXW4ObjectID@@@Z
void AIPlayer::repairStructure(ObjectID structure)
{
	Object *structureObj = TheGameLogic->findObjectByID(structure);
	if (structureObj == 0)
		return;

	BodyModuleInterface *body = structureObj->getBodyModule();
	if (body == 0)
		return;

	if (body->getDamageState() == 0)
		return;

	int n = structuresInQueue();

	int i;
	for (i = 0; i < structuresInQueue(); i++)
	{
		if (structuresToRepair()[i] == structureObj->getID())
			return;
	}

	if (n == MAX_STRUCTURES_TO_REPAIR)
		return;

	structuresToRepair()[n] = structureObj->getID();
	structuresInQueue() = n + 1;
}
