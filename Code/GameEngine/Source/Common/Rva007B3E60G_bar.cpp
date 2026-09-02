// Open-BFME: Rva007B3E60G::bar, retail 0x007B3BD0, 118 bytes.
//
// Walk the list at +0x14 looking for the argument node. On a hit, unlink it
// from that list, push it onto the list at +0x18, and drop the two refcounted
// pointers hanging off the node at +0x58 and +0x5C (inner slot +0x68). The
// walk continues with the node's (now updated) successor.

class RefCountClass
{
public:
	void Release_Ref(void)
	{
		NumRefs--;
		if (NumRefs == 0)
			Delete_This();
	}

protected:
	virtual void Delete_This(void);
	int NumRefs;
};

struct Rva007B3BD0Holder
{
	unsigned char m_pad[0x68];
	RefCountClass *m_ref;
};

struct Rva007B3BD0Node
{
	unsigned char m_pad0[0x58];
	Rva007B3BD0Holder *m_first;
	Rva007B3BD0Holder *m_second;
	unsigned char m_pad1[4];
	Rva007B3BD0Node *m_next;
};

class Rva007B3E60G
{
public:
	void bar(Rva007B3BD0Node *target);

private:
	unsigned char m_pad[0x14];
	Rva007B3BD0Node *m_list;
	Rva007B3BD0Node *m_other;
};

void Rva007B3E60G::bar(Rva007B3BD0Node *target)
{
	Rva007B3BD0Node *prev = 0;
	Rva007B3BD0Node *node = m_list;

	while (node)
	{
		if (node == target)
		{
			if (prev)
				prev->m_next = target->m_next;
			else
				m_list = target->m_next;

			target->m_next = m_other;
			m_other = target;

			Rva007B3BD0Holder *first = target->m_first;
			RefCountClass *ref = first->m_ref;
			if (ref)
			{
				ref->Release_Ref();
				first->m_ref = 0;
			}

			Rva007B3BD0Holder *second = target->m_second;
			ref = second->m_ref;
			if (ref)
			{
				ref->Release_Ref();
				second->m_ref = 0;
			}
		}

		prev = node;
		node = node->m_next;
	}
}
