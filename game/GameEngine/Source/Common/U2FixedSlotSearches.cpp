// Five bodies that walk a small array held by their owner.  Four of them are
// leaves that call nothing, and only the first carries a relocation, so the
// shapes are what the bytes prove.
//
// 0x0081C5C0 -- the only one that is not a member: two file-scope pointers are
// loaded from adjacent addresses, subtracted, and the difference divided by 28
// through the signed magic 0x92492493 / sar 4 / sign fixup.  Signed division is
// what says the expression is a POINTER DIFFERENCE (ptrdiff_t) and not a
// container's size(), which would be unsigned; the divisor gives the element
// width exactly, 0x1C.  The two globals are DIR32 the patcher fills.
//
// 0x00806400 -- an eight-slot array of pointer pairs at +8..+0x48 walked with a
// pointer, comparing the first word of each pair against the argument and
// zeroing BOTH words of the first match before returning.  The compiler emitted
// the entry guard (`lea/add/cmp/jae`) even though both bounds are constant
// offsets off ecx, which is MSVC 7.1 declining to fold a comparison of two
// leas; the loop is therefore a plain `while (p < end)`, not a do-while.
//
// 0x00808C80 and 0x00808E60 -- the same search over an array of POINTERS, each
// slot null-checked before its +0x10 word is compared, returning the slot on a
// hit and null on exhaustion.  They differ in exactly one thing: the first
// walks sixteen slots stored inline at +0x18, the second walks a count at +4 of
// slots held out of line at +8.  A fixed sixteen and a stored count are two
// different owners, so they are written as two classes.
//
// Identity is not recovered; every name is derived from an address.

struct Rva0081C5C0Element
{
	char m_body[28];
};

extern Rva0081C5C0Element *g_Rva0081C5C0Begin;
extern Rva0081C5C0Element *g_Rva0081C5C0End;

int Rva0081C5C0Count()
{
	return g_Rva0081C5C0End - g_Rva0081C5C0Begin;
}

// 0x00806370 -- the second member of the same class, and what says the first
// word of each pair is an OBJECT: it walks the identical +8..+0x48 range and
// calls the FIRST virtual of every non-null slot, passing the new value, the
// slot's second word, and its own second argument.  The whole loop is guarded
// by `value != m_value` (the argument on the left -- the reversed operand order
// is in the bytes) and the store of the new value happens before the walk, so
// the slots are a fixed-size listener table and this member is its notifier.
struct Rva00806400Listener
{
	virtual void notify(int value, void *arg, void *context);
};

struct Rva00806400Pair
{
	Rva00806400Listener *m_listener;
	void *m_arg;
};

class Rva00806400Owner
{
public:
	void release(void *key);
	void setValue(int value, void *context);

	int m_pad;
	int m_value;
	Rva00806400Pair m_pairs[8];
};

void Rva00806400Owner::release(void *key)
{
	Rva00806400Pair *p = m_pairs;
	Rva00806400Pair *end = m_pairs + 8;
	while (p < end)
	{
		if ((void *)p->m_listener == key)
		{
			p->m_listener = 0;
			p->m_arg = 0;
			return;
		}
		++p;
	}
}

void Rva00806400Owner::setValue(int value, void *context)
{
	if (value != m_value)
	{
		m_value = value;
		Rva00806400Pair *p = m_pairs;
		Rva00806400Pair *end = m_pairs + 8;
		while (p < end)
		{
			if (p->m_listener != 0)
				p->m_listener->notify(value, p->m_arg, context);
			++p;
		}
	}
}

struct Rva00808C80Item
{
	char m_head[0x10];
	int m_id;
};

class Rva00808C80Owner
{
public:
	Rva00808C80Item *find(int id);

	char m_head[0x18];
	Rva00808C80Item *m_slots[16];
};

Rva00808C80Item *Rva00808C80Owner::find(int id)
{
	for (int i = 0; i < 16; ++i)
	{
		Rva00808C80Item *p = m_slots[i];
		if (p != 0 && p->m_id == id)
			return p;
	}
	return 0;
}

class Rva00808E60Owner
{
public:
	Rva00808C80Item *find(int id);

	char m_head[4];
	int m_count;
	Rva00808C80Item **m_slots;
};

Rva00808C80Item *Rva00808E60Owner::find(int id)
{
	for (int i = 0; i < m_count; ++i)
	{
		Rva00808C80Item *p = m_slots[i];
		if (p != 0 && p->m_id == id)
			return p;
	}
	return 0;
}
