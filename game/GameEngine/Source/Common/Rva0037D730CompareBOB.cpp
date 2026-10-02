// cl: /MD /O2 /EHsc- /GR- /DNDEBUG /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include

#include "Common/GameMemory.h"
#include "Common/Overridable.h"

// Retail keeps the recursive override walk as a call.
#pragma inline_depth(0)

struct BfmeGotBOB
{
public:
	int m_vtable;
	Overridable *m_bob;
	int m_pad[2];
	int m_order;
};

class BfmeCompareBOB
{
public:
	bool lessThan(BfmeCompareBOB *other);
	bool greaterThan(BfmeCompareBOB *other);

private:
	int m_vtable;
	BfmeGotBOB *m_item;
	int m_pad[2];
	int m_order;
};

// ?lessThan@BfmeCompareBOB@@QAE_NPAV1@@Z
bool BfmeCompareBOB::lessThan(BfmeCompareBOB *other)
{
	BfmeGotBOB *item = m_item;
	BfmeGotBOB *left;
	if (item != 0)
	{
	Overridable *bob = item->m_bob;
		if (bob != 0)
			left = (BfmeGotBOB *)bob->friend_getFinalOverride();
		else
			left = item;
	}
	else
		left = (BfmeGotBOB *)this;

	item = other->m_item;
	BfmeGotBOB *right;
	if (item != 0)
	{
		Overridable *bob = item->m_bob;
		if (bob != 0)
			right = (BfmeGotBOB *)bob->friend_getFinalOverride();
		else
			right = item;
	}
	else
		right = (BfmeGotBOB *)other;

	if (left == 0 || right == 0)
		return false;

	return left->m_order < right->m_order;
}

// ?greaterThan@BfmeCompareBOB@@QAE_NPAV1@@Z
bool BfmeCompareBOB::greaterThan(BfmeCompareBOB *other)
{
	BfmeGotBOB *item = m_item;
	BfmeGotBOB *left;
	if (item != 0)
	{
		Overridable *bob = item->m_bob;
		if (bob != 0)
			left = (BfmeGotBOB *)bob->friend_getFinalOverride();
		else
			left = item;
	}
	else
		left = (BfmeGotBOB *)this;

	item = other->m_item;
	BfmeGotBOB *right;
	if (item != 0)
	{
		Overridable *bob = item->m_bob;
		if (bob != 0)
			right = (BfmeGotBOB *)bob->friend_getFinalOverride();
		else
			right = item;
	}
	else
		right = (BfmeGotBOB *)other;

	if (left == 0 || right == 0)
		return false;

	return left->m_order > right->m_order;
}
