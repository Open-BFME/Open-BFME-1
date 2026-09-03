// ?bfmeFind@Gen_0021AD10@@QAEPAXPAX@Z
// partial score=0.8 date=2026-09-03
// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: 0x0021AD10. List search with predicate, 110 bytes: a
// non-null find result returns at once; otherwise walk the circular node
// list at this+0x9BC, running the check per payload -- a non-null check
// result goes through virtual slot 6 with arg1, and a true virtual
// answer returns that payload, else the null find result. The two direct
// callees are pinned at their thunks.

struct BfmeNodeAD10
{
	BfmeNodeAD10 *m_next;			// +0x00
	char m_pad[4];				// +0x04
	void *m_payload;				// +0x08
};

class BfmeCheckAD10
{
public:
	virtual void bfmeV00(); virtual void bfmeV01(); virtual void bfmeV02();
	virtual void bfmeV03(); virtual void bfmeV04(); virtual void bfmeV05();
	virtual bool bfmeV06(void *a);
};

class Gen_0021AD10
{
public:
	void *bfmeFind(void *a);

private:
	void *bfmeFindRaw(void *a);
	void *bfmeAskRaw(void *o);
};

// ?bfmeFind@Gen_0021AD10@@QAEPAXPAX@Z
void *Gen_0021AD10::bfmeFind(void *a)
{
	void *found = bfmeFindRaw(a);

	if (found)
		return found;

	BfmeNodeAD10 *head = *(BfmeNodeAD10 **)((char *)this + 0x9BC);
	BfmeNodeAD10 *n = head->m_next;

	if (n == head)
		return found;

	do {
		void *obj = n->m_payload;
		n = n->m_next;
		void *chk = bfmeAskRaw(obj);

		if (chk) {
			BfmeCheckAD10 *c = (BfmeCheckAD10 *)chk;
			if (c->bfmeV06(a))
				return chk;
		}
	} while (n != head);

	return found;
}
