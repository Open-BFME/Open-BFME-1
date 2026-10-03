// cl: /DNDEBUG /MD /EHsc

class BfmeCondition
{
public:
	// isActive() is not declared here: it is reached through the ILT thunk below.
};

struct BfmeConditionOwnerPart
{
	unsigned char m_pad00[0x140];
	BfmeCondition *m_condition;
};

struct BfmeConditionOwner
{
	unsigned char m_pad00[0x204];
	BfmeConditionOwnerPart *m_part;
};

struct BfmeConditionNode
{
	BfmeConditionNode *m_next;
	BfmeConditionNode *m_previous;
	BfmeConditionOwner *m_value;
};

class BfmeConditionListView
{
public:
	bool bfmeAnyLinkedConditionActive();
};

// Retail's isActive call goes through the five-byte ILT thunk at 0x0002760B,
// which is defined as ?j_0002760b@@YAXXZ in game/gen_small/thunks_018.cpp
// (target FUN_007fd030) and pinned for the 0x00235320 scan. The thunk takes
// no argument of its own: it jumps with the thiscall `this` in ECX, so the
// reference is spelled through a thiscall member pointer of the same shape.
extern void j_0002760b();

typedef bool (BfmeCondition::*bfmeIsActiveThunk)();

union BfmeConditionThunkCast
{
	void (__cdecl *freeFunction)();
	bfmeIsActiveThunk memberFunction;
};

bool BfmeConditionListView::bfmeAnyLinkedConditionActive()
{
	BfmeConditionListView *self = this;
	BfmeConditionThunkCast cast;
	cast.freeFunction = ::j_0002760b;
	BfmeConditionNode *node = (*reinterpret_cast<BfmeConditionNode **>(
		reinterpret_cast<unsigned char *>(self) - 0xac))->m_next;
	while (node != *reinterpret_cast<BfmeConditionNode **>(
		reinterpret_cast<unsigned char *>(self) - 0xac))
	{
		BfmeConditionOwner *owner = node->m_value;
		if (owner != 0)
		{
			BfmeCondition *condition = owner->m_part->m_condition;
			if (condition != 0 && (condition->*cast.memberFunction)())
				return true;
		}
		node = node->m_next;
	}
	return false;
}
