// cl: /DNDEBUG /MD /EHsc

class Object;

struct BfmeObjectIdValue
{
	int m_id;
};

struct BfmeObjectIdSlot
{
	BfmeObjectIdValue *m_value;
};

class BfmeObjectReference
{
public:
	BfmeObjectIdSlot *getObjectIdSlot();
	Object *resolve();
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

extern GameLogic *TheGameLogic;

Object *BfmeObjectReference::resolve()
{
	if (this != 0) {
		BfmeObjectIdSlot *slot = getObjectIdSlot();
		return TheGameLogic->findObjectByID(slot->m_value->m_id);
	}
	return 0;
}
