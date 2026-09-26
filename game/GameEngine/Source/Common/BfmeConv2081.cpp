namespace _STL
{

template <int A, int B>
class __node_alloc
{
public:
	static void _M_deallocate(void *p, unsigned int n);
};

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
		_STL::__node_alloc<1, 0>::_M_deallocate(q, 12);
	}

	m_bfmeListXY->m_bfmeNextXY = m_bfmeListXY;
	m_bfmeListXY->m_bfmePrevXY = m_bfmeListXY;
	m_bfmeChainXY = 0;
}
