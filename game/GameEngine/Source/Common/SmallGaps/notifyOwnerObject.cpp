// ?notifyOwnerObject@@YGXH@Z
class Object;
class GameLogic { public: Object* findObjectByID(int id); };
extern GameLogic* TheGameLogic;
struct Rva002B7240Source { virtual void s0(); virtual int getOwnerID(); };
struct Rva002B7240Module { virtual void s0(); virtual void s1(); virtual void onOwnerFound(); };
class BridgeTowerBehaviorInterface;
class BridgeBehaviorInterface;
// retail ILT 0x00042424 -> 0x001F66D0 and ILT 0x00010424 -> 0x001F1F30 are
// the matched static interface lookups; 0x1F253 -> 0x0009A510 is the matched
// GameLogic::findObjectByID
class BridgeTowerBehavior { public: static BridgeTowerBehaviorInterface* getBridgeTowerBehaviorInterfaceFromObject(Object* obj); };
class BridgeBehavior { public: static BridgeBehaviorInterface* getBridgeBehaviorInterfaceFromObject(Object* obj); };
void __stdcall notifyOwnerObject(int id)
{
	if (!id)
		return;
	Rva002B7240Source* src = (Rva002B7240Source*)BridgeTowerBehavior::getBridgeTowerBehaviorInterfaceFromObject((Object*)id);
	if (!src)
		return;
	Object* owner = TheGameLogic->findObjectByID(src->getOwnerID());
	if (!owner)
		return;
	Rva002B7240Module* m = (Rva002B7240Module*)BridgeBehavior::getBridgeBehaviorInterfaceFromObject(owner);
	if (!m)
		return;
	m->onOwnerFound();
}
