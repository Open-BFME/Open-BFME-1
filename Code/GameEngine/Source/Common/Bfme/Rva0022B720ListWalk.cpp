// Retail 0x0022B720, complete boundary 144 bytes.
//
// Retail proves a circular doubly-linked list at this+0xC4, a cdecl callback
// taking the node value and context, and the continuation at 0x002234A0.

typedef void (__cdecl *Rva0022B720Callback)(void *, void *);

struct Rva0022B720Node
{
	Rva0022B720Node *m_next;
	Rva0022B720Node *m_previous;
	void *m_value;
};

struct Rva0022B720List
{
	Rva0022B720Node *m_sentinel;
};

class Rva0021B200ListOwner
{
public:
	void call_002234A0(Rva0022B720Callback callback, void *context,
		unsigned flags);
};

class Rva0022B720ListOwner
{
public:
	void visit(Rva0022B720Callback callback, void *context, unsigned flags);

private:
	unsigned char m_unreconstructed_000[0xC4];
	Rva0022B720List m_members;
};

void Rva0022B720ListOwner::visit(Rva0022B720Callback callback, void *context,
	unsigned flags)
{
	if ((flags & 4) != 0 && (flags & 8) != 0)
	{
		Rva0022B720Node *node = m_members.m_sentinel;
		if (node != node->m_next)
		{
			do
			{
				node = node->m_previous;
				callback(node->m_value, context);
			} while (node != m_members.m_sentinel->m_next);
		}
	}

	((Rva0021B200ListOwner *)this)->call_002234A0(callback, context, flags);

	if ((flags & 4) != 0 && (flags & 8) == 0)
	{
		Rva0022B720Node *node = m_members.m_sentinel->m_next;
		if (node != m_members.m_sentinel)
		{
			do
			{
				void *value = node->m_value;
				node = node->m_next;
				callback(value, context);
			} while (node != m_members.m_sentinel);
		}
	}
}
