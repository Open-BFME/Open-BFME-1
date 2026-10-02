// cl: /D_STLP_USE_STATIC_LIB /Iinputs/vendor/stlport
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *addend);
#include <stl/_alloc.h>

class BfmeRefEU
{
public:
	virtual ~BfmeRefEU();

	void bfmeReleaseEU(void)
	{
		if (InterlockedDecrement(&m_bfmeCountEU) <= 0)
			delete this;
	}

	long m_bfmeCountEU;
};

class BfmeNodeEU
{
public:
	BfmeNodeEU *m_bfmeNextEU;
	BfmeNodeEU *m_bfmePrevEU;
	BfmeRefEU *m_bfmeValueEU;
};

class BfmeHolderEU
{
public:
	BfmeNodeEU *m_bfmeNodeEU;
};

class BfmeListEU
{
public:
	void bfmeEraseEU(void);

	BfmeHolderEU *m_bfmeImplEU;
};

void BfmeListEU::bfmeEraseEU(void)
{
	BfmeNodeEU *node = m_bfmeImplEU->m_bfmeNodeEU;
	BfmeNodeEU *next = node->m_bfmeNextEU;
	BfmeNodeEU *prev = node->m_bfmePrevEU;
	prev->m_bfmeNextEU = next;
	next->m_bfmePrevEU = prev;
	if (node->m_bfmeValueEU != 0)
		node->m_bfmeValueEU->bfmeReleaseEU();
	_STL::__node_alloc<true, 0>::deallocate(node, 12);
}
