// ?rva005BE700Insert@Rva005BE700Owner@@QAEXPAVRva005BE700Item@@H@Z
// Address-derived: append obj to the tail of a per-index intrusive doubly
// linked list (head array at +0xc, tail array at +0x44, both indexed by the
// bucket argument), unless obj is already flagged (+0x7a). Bumps a count at
// +0x84.
class Rva005BE700Item
{
public:
	unsigned char m_pad0[0x44];
	Rva005BE700Item *m_next;
	Rva005BE700Item *m_prev;
	unsigned char m_pad1[0x7a - 0x4c];
	unsigned char m_flag;
};

class Rva005BE700Owner
{
public:
	void rva005BE700Insert(Rva005BE700Item *obj, int index);

private:
	unsigned char m_pad0[0xc];
};

void Rva005BE700Owner::rva005BE700Insert(Rva005BE700Item *obj, int index)
{
	if (obj->m_flag)
		return;

	Rva005BE700Item **headSlot = (Rva005BE700Item **)(index * 4 + (char *)this + 0xc);
	Rva005BE700Item **tailSlot = (Rva005BE700Item **)(index * 4 + (char *)this + 0x44);

	if (*headSlot == 0)
		*headSlot = obj;

	Rva005BE700Item *tail = *tailSlot;
	if (tail != 0)
	{
		tail->m_next = obj;
		tail = *tailSlot;
		obj->m_prev = tail;
	}
	else
	{
		obj->m_prev = 0;
	}

	*tailSlot = obj;
	obj->m_next = 0;
	obj->m_flag = 1;
	++*(int *)((char *)this + 0x84);
}
