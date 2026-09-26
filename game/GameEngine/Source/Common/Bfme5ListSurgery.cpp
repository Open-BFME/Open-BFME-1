// Open-BFME5 conversions: circular list insert, erase and clear.

namespace _STL {

class __new_alloc
{
public:
	static void *allocate(unsigned int n);
};

}

void __cdecl operator delete(void *p);

struct Bfme5RegItem;

struct Bfme5RegLink
{
	Bfme5RegLink *m_bfmeNext;
	Bfme5RegLink *m_bfmePrev;
	Bfme5RegItem *m_bfmeValue;
};

struct Bfme5RegItem
{
	char m_bfmePad[0x54];
	char m_bfmeFlag;
};

class Bfme5Registry
{
public:
	void bfmeRegister(Bfme5RegItem *it);

	char m_bfmePad0[0x528];
	char m_bfmeFlag;
	char m_bfmePad1[0xf];
	Bfme5RegLink *m_bfmeNode;
};

void Bfme5Registry::bfmeRegister(Bfme5RegItem *it)
{
	it->m_bfmeFlag = m_bfmeFlag;

	Bfme5RegLink *pos = m_bfmeNode;
	Bfme5RegLink *n = (Bfme5RegLink *)_STL::__new_alloc::allocate(0x0c);
	Bfme5RegItem **p = &n->m_bfmeValue;

	if (p)
		*p = it;

	Bfme5RegLink *prev = pos->m_bfmePrev;

	n->m_bfmeNext = pos;
	n->m_bfmePrev = prev;
	prev->m_bfmeNext = n;
	pos->m_bfmePrev = n;
}

class Bfme5OwnedValue
{
public:
	virtual ~Bfme5OwnedValue();

	int m_bfme04;
};

struct Bfme5OwnerLink
{
	Bfme5OwnerLink *m_bfmeNext;
	Bfme5OwnerLink *m_bfmePrev;
	Bfme5OwnedValue m_bfmeValue;
};

class Bfme5OwnerList
{
public:
	void bfmeClear(void);

	Bfme5OwnerLink *m_bfmeNode;
};

void Bfme5OwnerList::bfmeClear(void)
{
	Bfme5OwnerLink *h = m_bfmeNode;
	Bfme5OwnerLink *n = h->m_bfmeNext;

	while (n != h) {
		Bfme5OwnerLink *cur = n;

		n = n->m_bfmeNext;
		cur->m_bfmeValue.~Bfme5OwnedValue();
		operator delete(cur);
		h = m_bfmeNode;
	}

	m_bfmeNode->m_bfmeNext = m_bfmeNode;
	m_bfmeNode->m_bfmePrev = m_bfmeNode;
}

struct Bfme5OwnerIter
{
	Bfme5OwnerLink *m_bfmeNode;

	Bfme5OwnerIter(void) {}
};

Bfme5OwnerIter __stdcall bfme5EraseOwnerLink(Bfme5OwnerLink *n)
{
	Bfme5OwnerLink *prev = n->m_bfmePrev;
	Bfme5OwnerLink *next = n->m_bfmeNext;

	prev->m_bfmeNext = next;
	next->m_bfmePrev = prev;
	n->m_bfmeValue.~Bfme5OwnedValue();
	operator delete(n);

	Bfme5OwnerIter r;

	r.m_bfmeNode = next;
	return r;
}
