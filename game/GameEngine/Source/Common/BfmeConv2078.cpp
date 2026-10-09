namespace _STL
{
static __forceinline void *vectorSmallAllocate(unsigned int bytes);



// The node allocator's pool entry points are private STLport members
// (_STL::__node_alloc<true, 0>::_M_allocate at 0x0082E540, _M_deallocate at
// 0x0082E5F0); these TU-local helpers reach them under their real names.
template <bool __threads, int __inst> class __node_alloc;
static void nodePoolDeallocate(void *block, unsigned int bytes);
template <bool __threads, int __inst>
class __node_alloc
{
	friend void *vectorSmallAllocate(unsigned int bytes);
	friend void nodePoolDeallocate(void *, unsigned int);
	static void *__cdecl _M_allocate(unsigned int __n);
	static void __cdecl _M_deallocate(void *__p, unsigned int __n);
};
static __forceinline void *vectorSmallAllocate(unsigned int bytes)
{
	return __node_alloc<true, 0>::_M_allocate(bytes);
}
static inline void nodePoolDeallocate(void *block, unsigned int bytes) { __node_alloc<true, 0>::_M_deallocate(block, bytes); }

}

class BfmeNodeJS
{
public:
	BfmeNodeJS *m_bfmeF0JS;
	BfmeNodeJS *m_bfmeF4JS;
	void *m_bfmeValJS;
};

class BfmeListJS
{
public:
	void bfmeSetJS(void *v);

	unsigned char m_bfmeHeadJS[0x10];
	BfmeNodeJS *m_bfme10JS;
};

void BfmeListJS::bfmeSetJS(void *v)
{
	BfmeNodeJS *h = m_bfme10JS;
	BfmeNodeJS *p = h->m_bfmeF0JS;

	while (p != h)
	{
		if (p->m_bfmeValJS == v)
		{
			BfmeNodeJS *nx = p->m_bfmeF0JS;
			BfmeNodeJS *pv = p->m_bfmeF4JS;

			pv->m_bfmeF0JS = nx;
			nx->m_bfmeF4JS = pv;

			_STL::nodePoolDeallocate(p, 12);
			break;
		}

		p = p->m_bfmeF0JS;
	}

	BfmeNodeJS *e = m_bfme10JS;
	BfmeNodeJS *n = (BfmeNodeJS *)_STL::vectorSmallAllocate(12);
	void **q = &n->m_bfmeValJS;

	if (q != 0)
		*q = v;

	BfmeNodeJS *nx2 = e->m_bfmeF4JS;

	n->m_bfmeF0JS = e;
	n->m_bfmeF4JS = nx2;
	nx2->m_bfmeF0JS = n;
	e->m_bfmeF4JS = n;
}
