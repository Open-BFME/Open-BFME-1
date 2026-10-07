// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	char gap[0x94];
	unsigned char status;
};

struct Rva21C8E0Context
{
	char gap[8];
	int objectId;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(int id);
};

extern GameLogic *TheGameLogic;

// Retail calls ILT 0x37A1F -> 0x00248B40, matched as
// BfmeThingAMA::conditionalForward (HordeContainConditionalForward.cpp).
struct Rva00248B40Object;
struct BfmeStateAMA;
class BfmeThingAMA
{
public:
	void conditionalForward(Rva00248B40Object *target, void *action, BfmeStateAMA *state);
};

class Rva21C8E0ConditionalDispatch
{
public:
	void dispatch(Object *object, void *action, Rva21C8E0Context *context);
	__forceinline void handle(Object *object, void *action, Rva21C8E0Context *context)
	{
		reinterpret_cast<BfmeThingAMA *>(this)->conditionalForward(
			reinterpret_cast<Rva00248B40Object *>(object), action,
			reinterpret_cast<BfmeStateAMA *>(context));
	}
};

void Rva21C8E0ConditionalDispatch::dispatch(
	Object *object,
	void *action,
	Rva21C8E0Context *context)
{
	if ((object->status & 0x10) != 0) {
		Object *other = TheGameLogic->findObjectByID(context->objectId);
		if (other != 0 && (other->status & 0x10) != 0)
			return;
	}

	handle(object, action, context);
}
