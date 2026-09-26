// cl: /O2 /Ob0
//
// RVA-derived name: identity not recovered. Two symbols.csv pins name the
// ILT 0x00037349 (which thunks to this body) as WeaponTemplate and
// BfmeRelationTest relationship testers; those are pinharvest candidates.
// The body walks the owner+0x538 circular list used by BfmeThing404/LO.

class Rva001E4090;

class Rva002DF100
{
public:
	unsigned char testOne(void *value);
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual unsigned char slot7();
	virtual void slot8();
	virtual void slot9();
	virtual class Holder001E4090 *slot10();
	virtual Rva001E4090 *slot11();
};

class Holder001E4090
{
public:
	char m_pad[0x70];
	void *m_70;
};

struct Node001E4090
{
	Node001E4090 *next;
	Node001E4090 *prev;
	Rva002DF100 *item;
};

class Rva001E4090
{
public:
	bool allows(void *first, void *second);

private:
	char m_pad0[0x4C];
	void *m_4C;
	char m_pad50[0x538 - 0x50];
	Node001E4090 *m_head;
};

bool Rva001E4090::allows(void *first, void *second)
{
	if (m_4C == first)
		return true;
	if (!second)
		return false;

	Node001E4090 *head = m_head;
	for (Node001E4090 *at = head->next; at != m_head; at = at->next)
	{
		Rva002DF100 *item = at->item;
		if (!item->testOne(second))
			continue;
		if (item->slot7())
		{
			Holder001E4090 *held = item->slot10();
			if (held && held->m_70 == first)
				return true;
		}
		Rva001E4090 *other = item->slot11();
		if (other && other->allows(first, second))
			return true;
	}
	return false;
}
