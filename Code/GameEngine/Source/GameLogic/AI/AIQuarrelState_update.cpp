// cl: /DNDEBUG /MD /EHsc
//
// AIQuarrelState::update — retail 0x0016B6B0 (36B).
//
// Constructor-owned vtable 0x00C98470 slot 6 -> ILT 0x00004E30 -> this body.
// Slot 2 is the literal name getter for "AIQuarrelState".

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef UnsignedInt ObjectID;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

class Object
{
public:
	Bool bfmeGetRecentDamageSource(ObjectID *sourceID, UnsignedInt seconds) const;
};

class StateMachine
{
public:
	unsigned char m_pad[0x10];
	Object *m_owner;
};

class AIQuarrelState
{
public:
	virtual StateReturnType update();

private:
	unsigned char m_pad[0x18];
	StateMachine *m_machine;
};

StateReturnType AIQuarrelState::update()
{
	ObjectID sourceID;
	Object *obj = m_machine->m_owner;
	if (!obj)
		return STATE_FAILURE;
	return obj->bfmeGetRecentDamageSource(&sourceID, 4) ? STATE_SUCCESS : STATE_CONTINUE;
}
