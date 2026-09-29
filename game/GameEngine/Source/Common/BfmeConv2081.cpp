namespace _STL
{

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

__declspec(dllimport) void __cdecl bfmeFree1035(void *p);

class BfmeThingEC
{
public:
	int bfmeTakeEC(int *n);
};

class BfmeNodeXY
{
public:
	BfmeNodeXY *m_bfmeNextXY;
	BfmeNodeXY *m_bfmePrevXY;
	BfmeThingEC *m_bfmeValXY;
};

class BfmeChainXY
{
public:
	unsigned char m_bfmeHeadXY[0x14];
	BfmeChainXY *m_bfmeNextXY;
};

class BfmeHostXY
{
public:
	void bfmeClearXY();

	unsigned char m_bfmeHeadXY[0x44];
	BfmeChainXY *m_bfmeChainXY;
	BfmeNodeXY *m_bfmeCurXY;
	BfmeNodeXY *m_bfmeListXY;
};

void BfmeHostXY::bfmeClearXY()
{
	int n;

	while (m_bfmeChainXY)
	{
		BfmeChainXY *nx = m_bfmeChainXY->m_bfmeNextXY;

		delete m_bfmeChainXY;
		m_bfmeChainXY = nx;
	}

	m_bfmeCurXY = m_bfmeListXY->m_bfmeNextXY;

	while (m_bfmeCurXY != m_bfmeListXY)
	{
		if (m_bfmeCurXY->m_bfmeValXY)
			bfmeFree1035((void *)m_bfmeCurXY->m_bfmeValXY->bfmeTakeEC(&n));

		m_bfmeCurXY = m_bfmeCurXY->m_bfmeNextXY;
	}

	BfmeNodeXY *p = m_bfmeListXY->m_bfmeNextXY;

	while (p != m_bfmeListXY)
	{
		BfmeNodeXY *q = p;

		p = p->m_bfmeNextXY;
		_STL::nodePoolDeallocate(q, 12);
	}

	m_bfmeListXY->m_bfmeNextXY = m_bfmeListXY;
	m_bfmeListXY->m_bfmePrevXY = m_bfmeListXY;
	m_bfmeChainXY = 0;
}
