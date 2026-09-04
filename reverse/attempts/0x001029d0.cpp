// ?bfmeFlushFS@BfmeThingFS@@QAEXXZ
// partial score=0.9 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
// Open-BFME: waiting-list flush on a Thing-like owner, retail 0x001029D0.
//
// this+0 is an owner pointer (not a vtable).  When the head entry's amount is
// positive the owner is queried and then updated with query+amount, after
// which every entry has that amount subtracted.  The head is then unlinked
// and destroyed.

struct BfmeThingFSOwner;

struct BfmeThingFSOwnerVT
{
	void *slot0;
	int (__fastcall *query)(BfmeThingFSOwner *self);
	void (__fastcall *apply)(BfmeThingFSOwner *self, int amountKeep, int value);
};

struct BfmeThingFSOwner
{
	BfmeThingFSOwnerVT *vt;
};

class BfmeThingFSEntry
{
public:
	virtual ~BfmeThingFSEntry(void);

	BfmeThingFSEntry *next;
	char pad[0x10];
	int amount;
};

class BfmeThingFS
{
	BfmeThingFSOwner *m_owner;
	char pad[0x18];
	BfmeThingFSEntry *m_list;

public:
	void bfmeFlushFS(void);
};

// ?bfmeFlushFS@BfmeThingFS@@QAEXXZ
void BfmeThingFS::bfmeFlushFS(void)
{
	BfmeThingFSEntry *e = m_list;
	if (e == 0)
		return;

	if (e->amount > 0)
	{
		BfmeThingFSOwner *o = m_owner;
		BfmeThingFSOwnerVT *vt = o->vt;
		int v = vt->query(o);
		o = m_owner;
		e = m_list;
		int amt = e->amount;
		vt->apply(o, amt, v + amt);
		e = m_list;
		if (e == 0)
			goto afterWalk;
		{
			int take = e->amount;
			do
			{
				e->amount -= take;
				e = e->next;
			} while (e != 0);
		}
	afterWalk:;
	}

	e = m_list;
	if (e != 0)
	{
		m_list = e->next;
		delete e;
	}
}
