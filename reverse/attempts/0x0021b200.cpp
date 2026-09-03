// ?d_0021b200@@YAXXZ
// partial score=0.85 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: 0x0021B200. Sibling of 0x0022B720: flags bit 1 selects a
// reverse or forward walk of the circular list at +0x99C.

struct BfmeNodeB200
{
	BfmeNodeB200 *next;
	BfmeNodeB200 *prev;
	void *value;
};

class Gen_0021B200
{
public:
	void bfmeWalk(void (__cdecl *cb)(void *, void *), void *user, unsigned flags);
	void bfmeInner(void (__cdecl *cb)(void *, void *), void *user, unsigned flags);

	char m_pad[0x99C];
	BfmeNodeB200 *m_list;
};

// ?bfmeWalk@Gen_0021B200@@QAEXP6AXPAX0@Z0I@Z
void Gen_0021B200::bfmeWalk(void (__cdecl *cb)(void *, void *), void *user, unsigned flags)
{
	unsigned saved = flags;
	saved &= 2;
	if (saved != 0 && (flags & 8) != 0)
	{
		BfmeNodeB200 *n = m_list;
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
		BfmeNodeB200 *sent = m_list;
		BfmeNodeB200 *n = sent->next;
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
