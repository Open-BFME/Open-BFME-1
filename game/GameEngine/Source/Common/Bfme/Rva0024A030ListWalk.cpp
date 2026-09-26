// Retail 0x0024A030, complete boundary 144 bytes.
//
// This is the address-derived sibling of the already matched list-walk body
// at 0x0021B200.  Retail proves a circular doubly-linked list at this+0xCC,
// a cdecl callback taking the node value and context, and the same continuation
// body reached through the 0x003D0D7 ILT (0x002234A0).

typedef void (__cdecl *Rva0024A030Callback)(void *, void *);

struct Rva0024A030Node
{
	Rva0024A030Node *m_next;
	Rva0024A030Node *m_previous;
	void *m_value;
};

struct Rva0024A030List
{
	Rva0024A030Node *m_sentinel;
};

// The retail continuation is the same neutral body already proven at
// 0x002234A0.  Reuse its established symbol so the ILT candidate (0x003D0D7)
// is resolved by the existing ledger pin.
class Rva0021B200ListOwner
{
public:
	void call_002234A0(Rva0024A030Callback callback, void *context,
		unsigned flags);
};

class Rva0024A030ListOwner
{
public:
	void visit(Rva0024A030Callback callback, void *context, unsigned flags);

private:
	unsigned char m_unreconstructed_000[0xCC];
	Rva0024A030List m_members;
};

void Rva0024A030ListOwner::visit(Rva0024A030Callback callback, void *context,
	unsigned flags)
{
	if ((flags & 4) != 0 && (flags & 8) != 0)
	{
		Rva0024A030Node *node = m_members.m_sentinel;
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
		Rva0024A030Node *node = m_members.m_sentinel->m_next;
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
