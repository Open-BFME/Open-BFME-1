// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: circular-list predicate walk at retail RVA 0x00220490.

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
	Overridable *m_nextOverride;
};

class Object;

// ILT 0x00033915 -> HealContain::doHeal at 0x002203C0.
class HealContain
{
	friend class Gen_00220490;
protected:
	bool doHeal(Object *obj, unsigned int framesForFullHeal);
};

enum UpdateSleepTime;

// The defining update body receives the secondary-interface this pointer,
// just like this caller. A qualified call keeps it non-virtual here.
class OpenContain
{
public:
	virtual UpdateSleepTime update();
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
	int bfmeWalk();
};

int Gen_00220490::bfmeWalk()
{
	((OpenContain *)this)->OpenContain::update();
	void *ctx = *(void **)((char *)this - 0xC);
	BfmeNode490 *sent = *(BfmeNode490 **)((char *)this + 0x28);
	BfmeNode490 *n = sent->next;
	if (n != sent)
	{
		do
		{
			void *obj = n->value;
			n = n->next;
			if (((HealContain *)((char *)this - 0x10))->doHeal(
				(Object *)obj, *(unsigned int *)((char *)ctx + 0x168)) == 1)
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
