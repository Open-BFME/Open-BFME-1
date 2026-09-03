// ?d_0021cd60@@YAXXZ
// partial score=0.58 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: 0x0021CD60. Six-arg continuation, then count the circular list
// at +0x99C and tally payloads whose override has bit 0x100 at +0xC8.

struct BfmeNodeD60
{
	BfmeNodeD60 *next;
	BfmeNodeD60 *prev;
	void *value;
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_next;
};

class Gen_0021CD60
{
public:
	bool bfmeInner(void *a, void *b, void *c, void *d, int *count, int *bits);
	bool bfmeCount(void *a, void *b, void *c, void **copy, int *count, int *bits);

	char m_pad[0x99C];
	BfmeNodeD60 *m_list;
};

// ?bfmeCount@Gen_0021CD60@@QAE_NPAX00PAPAXPAH2@Z
bool Gen_0021CD60::bfmeCount(void *a, void *b, void *c, void **copy, int *count, int *bits)
{
	void *a1 = a;
	int *cnt = count;
	void **cp = copy;
	int *bt = bits;
	bool ok = bfmeInner(a1, b, c, cp, cnt, bt);
	if (!ok)
		return ok;

	BfmeNodeD60 *sent = m_list;
	int n = 0;
	BfmeNodeD60 *p;
	for (p = sent->next; p != sent; p = p->next)
		++n;
	*cnt = n;
	*cp = *(void **)a1;
	*bt = 0;

	p = m_list->next;
	if (p != m_list)
	{
		unsigned mask = 0x100;
		do
		{
			char *payload = (char *)p->value;
			unsigned addr = (unsigned)payload + 4;
			Overridable *ovr = *(Overridable **)addr;
			if (ovr != 0)
			{
				Overridable *next = ovr->m_next;
				if (next != 0)
					ovr = (Overridable *)next->getFinalOverride();
			}
			if ((*(unsigned *)((char *)ovr + 0xC8) & mask) != 0)
				++*bt;
			p = p->next;
		} while (p != m_list);
	}
	return ok;
}
