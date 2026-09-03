// ?d_0022b720@@YAXXZ
// partial score=0.85 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: 0x0022B720. If flags bit 2 is set, walk the circular list at
// +0xC4 (reverse when bit 3 is set, forward otherwise) and always run the
// three-arg continuation.

struct BfmeNodeB720
{
	BfmeNodeB720 *next;
	BfmeNodeB720 *prev;
	void *value;
};

class Gen_0022B720
{
public:
	void bfmeWalk(void (__cdecl *cb)(void *, void *), void *user, unsigned flags);
	void bfmeInner(void (__cdecl *cb)(void *, void *), void *user, unsigned flags);

	char m_pad[0xC4];
	BfmeNodeB720 *m_list;
};

// ?bfmeWalk@Gen_0022B720@@QAEXP6AXPAX0@Z0I@Z
void Gen_0022B720::bfmeWalk(void (__cdecl *cb)(void *, void *), void *user, unsigned flags)
{
	unsigned saved = flags;
	saved &= 4;
	if (saved != 0 && (flags & 8) != 0)
	{
		BfmeNodeB720 *n = m_list;
		if (n != n->next)
		{
			do
			{
				n = n->prev;
				cb(n->value, user);
			} while (n != m_list->next);
		}
	}
	bfmeInner(cb, user, flags);
	if (saved != 0 && (flags & 8) == 0)
	{
		BfmeNodeB720 *sent = m_list;
		BfmeNodeB720 *n = sent->next;
		if (n != sent)
		{
			do
			{
				void *value = n->value;
				n = n->next;
				cb(value, user);
			} while (n != m_list);
		}
	}
}
