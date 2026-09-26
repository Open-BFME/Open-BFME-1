namespace _STL
{

class __new_alloc
{
public:
	static void *allocate(unsigned int n);
};

template <int A, int B>
class __node_alloc
{
public:
	static void _M_deallocate(void *p, unsigned int n);
};

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

			_STL::__node_alloc<1, 0>::_M_deallocate(p, 12);
			break;
		}

		p = p->m_bfmeF0JS;
	}

	BfmeNodeJS *e = m_bfme10JS;
	BfmeNodeJS *n = (BfmeNodeJS *)_STL::__new_alloc::allocate(12);
	void **q = &n->m_bfmeValJS;

	if (q != 0)
		*q = v;

	BfmeNodeJS *nx2 = e->m_bfmeF4JS;

	n->m_bfmeF0JS = e;
	n->m_bfmeF4JS = nx2;
	nx2->m_bfmeF0JS = n;
	e->m_bfmeF4JS = n;
}
