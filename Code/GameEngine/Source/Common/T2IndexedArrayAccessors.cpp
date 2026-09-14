// Bounds-checked element accessors and linear searches over a pointer/count
// pair held in the owner.  Three element strides appear -- 0x30, 0x38 and 0x80
// -- and each is spelled by the multiply the compiler chose: lea+shl 4 for
// 0x30, imul for 0x38, shl 7 for 0x80.  The searches compare a dword at offset
// 8 of the element, which is the only element field the bytes name.
struct T2ElemA { char m_head[8]; int m_id; char m_tail[0x30 - 0xC]; };
struct GetterWord { int m_value; };
struct T2ElemB
{
	virtual ~T2ElemB();
	virtual void v1();
	virtual GetterWord get() const;
	char m_body[0x38 - 4];
};
struct T2ArrB
{
	T2ElemB *m_a;
	int m_n;
	__forceinline T2ElemB *at(int index)
	{
		if (index >= m_n)
			return 0;
		return m_a + index;
	}
};
struct T2ElemC { char m_head[8]; int m_id; char m_tail[0x80 - 0xC]; };

struct T2OwnerA
{
	char m_head[0x3C];
	T2ElemA *m_base;
	int m_count;

	T2ElemA *at(int index);
	T2ElemA *find(int id);
};

T2ElemA *T2OwnerA::at(int index)
{
	if (index >= m_count)
		return 0;
	return m_base + index;
}

T2ElemA *T2OwnerA::find(int id)
{
	T2ElemA *p = m_base;
	T2ElemA *end = m_base + m_count;
	while (p < end)
	{
		if (p->m_id == id)
			return p;
		++p;
	}
	return 0;
}

struct T2OwnerB
{
	char m_head[0x20];
	T2ArrB m_20;

	T2ElemB *at(int index);
	T2ElemB *find(int id);
};

T2ElemB *T2OwnerB::at(int index)
{
	if (index >= m_20.m_n)
		return 0;
	return m_20.m_a + index;
}

T2ElemB *T2OwnerB::find(int id)
{
	for (int i = 0; i < m_20.m_n; ++i)
	{
		T2ElemB *slot = m_20.at(i);
		GetterWord key;
		key = slot->get();
		if (key.m_value == id)
			return slot;
	}
	return 0;
}

struct T2OwnerC
{
	char m_head[0x1C];
	T2ElemC *m_base;
	int m_count;

	T2ElemC *at(int index);
	T2ElemC *find(int id);
};

T2ElemC *T2OwnerC::at(int index)
{
	if (index >= m_count)
		return 0;
	return m_base + index;
}

T2ElemC *T2OwnerC::find(int id)
{
	T2ElemC *p = m_base;
	T2ElemC *end = m_base + m_count;
	while (p < end)
	{
		if (p->m_id == id)
			return p;
		++p;
	}
	return 0;
}

// A free function that indexes a pointer table at offset 0x88 of its first
// argument; __cdecl, so the object arrives on the stack rather than in ecx.
struct T2TableOwner
{
	char m_head[0x88];
	void *m_slots[1];
};

void *t2_table_slot(T2TableOwner *owner, int index)
{
	return owner->m_slots[index];
}
