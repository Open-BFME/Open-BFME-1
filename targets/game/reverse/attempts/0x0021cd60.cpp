// ?d_0021cd60@@YAXXZ
// partial score=0.68 date=2026-09-11
// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: 0x0021CD60. Six-arg continuation, then count the circular list
// at +0x99C and tally payloads whose override has bit 0x100 at +0xC8.
// Folding the early "if (!ok) return ok;" into a positive "if (ok) { ... }"
// tail (one return, no duplicate epilogue) matches retail's je/fallthrough
// shape and drops diff bytes from 122/166 to 77/165. Residual wall is the
// prologue register assignment: retail keeps `this` in ebx (materialized by
// `mov ebx,ecx` right before the bfmeInner call, reused after the call for
// two m_list loads) while MSVC always keeps `this` in edi and cycles a,
// count, copy through ebp/esi/edi instead. Reordering local definitions
// (bits/b/a/count/copy/this-as-local) before the call produces byte-identical
// output to the original order -- MSVC's stack-arg-to-register assignment
// here is independent of local declaration order, ruling out the
// definition-order lever for this shape. Not attempted: forcing edi's
// mid-function reuse from `copy` to `bits` (retail reloads bits from its
// original stack slot after the call instead of keeping it live across it).

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
	if (ok)
	{
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
				Overridable **ovrp = (Overridable **)(payload + 4);
				Overridable *ovr = *ovrp;
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
	}
	return ok;
}
