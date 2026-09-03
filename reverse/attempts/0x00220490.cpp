// ?d_00220490@@YAXXZ
// partial score=0.98 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: 0x00220490. Walk the circular list at this+0x28; on a one-result
// predicate, override-walk the payload and call two virtuals at this+0x20.

struct BfmeNode490
{
	BfmeNode490 *next;
	BfmeNode490 *prev;
	void *value;
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_next;
};

class BfmePred490
{
public:
	char bfmeCheck(void *obj, void *ctx);
};

class BfmeVirt490
{
public:
	virtual void slot00() = 0;
	virtual int virt04(void *ovr, void *obj) = 0;
	virtual void virt08(void *obj, int handle) = 0;
};

class Gen_00220490
{
public:
	void bfmePrep();
	int bfmeWalk();
};

// ?bfmeWalk@Gen_00220490@@QAEHXZ
int Gen_00220490::bfmeWalk()
{
	bfmePrep();
	void *ctx = *(void **)((char *)this - 0xC);
	BfmeNode490 *sent = *(BfmeNode490 **)((char *)this + 0x28);
	BfmeNode490 *n = sent->next;
	if (n != sent)
	{
		do
		{
			void *extra = *(void **)((char *)ctx + 0x168);
			void *obj = n->value;
			n = n->next;
			if (((BfmePred490 *)((char *)this - 0x10))->bfmeCheck(obj, extra) == 1)
			{
				void *arg = *(void **)((char *)obj + 4);
				if (arg != 0)
				{
					Overridable *next = *(Overridable **)((char *)arg + 4);
					if (next != 0)
						arg = (void *)next->getFinalOverride();
				}
				BfmeVirt490 *v = (BfmeVirt490 *)((char *)this + 0x20);
				int handle = v->virt04(arg, obj);
				if (handle != -1)
					v->virt08(obj, handle);
			}
		} while (n != *(BfmeNode490 **)((char *)this + 0x28));
	}
	return 1;
}
