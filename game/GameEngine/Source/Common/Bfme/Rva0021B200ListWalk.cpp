// Retail 0x0021B200, complete boundary 144 bytes.
//
// No named caller or constructor/vtable route has been recovered for this
// body.  The view is therefore address-derived: retail proves a circular
// doubly-linked node at this+0x99C and a three-argument continuation call.

typedef void (__cdecl *Rva0021B200Callback)(void *, void *);

struct Rva0021B200Node
{
	Rva0021B200Node *m_next;
	Rva0021B200Node *m_previous;
	void *m_value;
};

class Rva0021B200ListOwner
{
public:
	void visit(Rva0021B200Callback callback, void *context, unsigned flags);
	void call_002234A0(Rva0021B200Callback callback, void *context,
		unsigned flags);

private:
	unsigned char m_unreconstructed_000[0x99C];
	Rva0021B200Node *m_sentinel;
};

void Rva0021B200ListOwner::visit(Rva0021B200Callback callback, void *context,
	unsigned flags)
{
	if ((flags & 2) != 0 && (flags & 8) != 0)
	{
		Rva0021B200Node *node = m_sentinel;
		if (node != node->m_next)
		{
			do
			{
				node = node->m_previous;
				callback(node->m_value, context);
			} while (node != m_sentinel->m_next);
		}
	}

	call_002234A0(callback, context, flags);

	if ((flags & 2) != 0 && (flags & 8) == 0)
	{
		Rva0021B200Node *sentinel = m_sentinel;
		Rva0021B200Node *node = sentinel->m_next;
		if (node != sentinel)
		{
			do
			{
				void *value = node->m_value;
				node = node->m_next;
				callback(value, context);
			} while (node != m_sentinel);
		}
	}
}
