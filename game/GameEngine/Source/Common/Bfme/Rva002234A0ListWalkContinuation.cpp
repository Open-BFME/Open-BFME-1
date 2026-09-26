// Retail 0x002234A0, complete boundary 106 bytes.
//
// This is the shared middle-list continuation called by the verified list
// walkers at 0x0021B200 and 0x0022B720. Retail proves the circular list at
// this+0x18, flags bit 0 ownership, and bit 3 traversal direction.

typedef void (__cdecl *Rva0021B200Callback)(void *, void *);

struct Rva002234A0Node
{
	Rva002234A0Node *m_next;
	Rva002234A0Node *m_previous;
	void *m_value;
};

class Rva0021B200ListOwner
{
public:
	void call_002234A0(Rva0021B200Callback callback, void *context,
		unsigned flags);

private:
	unsigned char m_unreconstructed_000[0x18];
	Rva002234A0Node *m_sentinel;
};

void Rva0021B200ListOwner::call_002234A0(
	Rva0021B200Callback callback, void *context, unsigned flags)
{
	if ((flags & 1) == 0)
		return;

	if ((flags & 8) != 0)
	{
		Rva002234A0Node *node = m_sentinel;
		if (node != node->m_next)
		{
			do
			{
				node = node->m_previous;
				callback(node->m_value, context);
			} while (node != m_sentinel->m_next);
		}
	}
	else
	{
		Rva002234A0Node *sentinel = m_sentinel;
		Rva002234A0Node *node = sentinel->m_next;
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
