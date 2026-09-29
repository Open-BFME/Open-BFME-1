// Open-BFME5 conversions: erase the first ring node whose key matches.

namespace _STL {

// The node allocator's pool entry points are private STLport members
// (_STL::__node_alloc<true, 0>::_M_allocate at 0x0082E540, _M_deallocate at
// 0x0082E5F0); these TU-local helpers reach them under their real names.
template <bool __threads, int __inst> class __node_alloc;
static void nodePoolDeallocate(void *block, unsigned int bytes);
template <bool __threads, int __inst>
class __node_alloc
{
	friend void nodePoolDeallocate(void *, unsigned int);
	static void *__cdecl _M_allocate(unsigned int __n);
	static void __cdecl _M_deallocate(void *__p, unsigned int __n);
};
static inline void nodePoolDeallocate(void *block, unsigned int bytes) { __node_alloc<true, 0>::_M_deallocate(block, bytes); }

}

struct Bfme5KeyRecord
{
	char m_bfmePad[0x74];
	void *m_bfmeKey;
};

struct Bfme5KeyNode
{
	Bfme5KeyNode *m_bfmeNext;
	Bfme5KeyNode *m_bfmePrev;
	void *m_bfmeKey;
};

class Bfme5KeyListA
{
public:
	void bfmeEraseKey(Bfme5KeyRecord *r);

	char m_bfmePad[0x1c];
	Bfme5KeyNode *m_bfmeHead;
};

void Bfme5KeyListA::bfmeEraseKey(Bfme5KeyRecord *r)
{
	Bfme5KeyNode *h = m_bfmeHead;
	Bfme5KeyNode *n = h->m_bfmeNext;

	if (n == h)
		return;

	void *k = r->m_bfmeKey;

	do {
		if (k == n->m_bfmeKey) {
			Bfme5KeyNode *nx = n->m_bfmeNext;
			Bfme5KeyNode *pv = n->m_bfmePrev;

			pv->m_bfmeNext = nx;
			nx->m_bfmePrev = pv;
			_STL::nodePoolDeallocate(n, 0x14);
			return;
		}

		n = n->m_bfmeNext;
	} while (n != h);
}

class Bfme5KeyListB
{
public:
	void bfmeEraseKey(void *k);

	char m_bfmePad[0x10];
	Bfme5KeyNode *m_bfmeHead;
};

void Bfme5KeyListB::bfmeEraseKey(void *k)
{
	Bfme5KeyNode *h = m_bfmeHead;
	Bfme5KeyNode *n = h->m_bfmeNext;

	if (n == h)
		return;

	do {
		if (n->m_bfmeKey == k) {
			Bfme5KeyNode *nx = n->m_bfmeNext;
			Bfme5KeyNode *pv = n->m_bfmePrev;

			pv->m_bfmeNext = nx;
			nx->m_bfmePrev = pv;
			_STL::nodePoolDeallocate(n, 0x0c);
			return;
		}

		n = n->m_bfmeNext;
	} while (n != h);
}
