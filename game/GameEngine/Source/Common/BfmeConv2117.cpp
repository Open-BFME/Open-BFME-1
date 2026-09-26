namespace _STL
{

struct __false_type
{
};

}

class ChainVictim005C92F0;

class BfmeVecAAH
{
public:
	void _M_insert_overflow(ChainVictim005C92F0 **pos, ChainVictim005C92F0 *const &x,
		const _STL::__false_type &tag, bool fill, unsigned int n);

	ChainVictim005C92F0 **m_bfmeStartAAH;
	ChainVictim005C92F0 **m_bfmeFinishAAH;
	ChainVictim005C92F0 **m_bfmeEndAAH;
};

class BfmeHostAAH
{
public:
	void __fastcall bfmePushAAH(ChainVictim005C92F0 *v);

	unsigned char m_bfmeHeadAAH[0xc0];
	BfmeVecAAH m_bfmeVecAAH;
};

void __fastcall BfmeHostAAH::bfmePushAAH(ChainVictim005C92F0 *v)
{
	BfmeVecAAH *vec = &m_bfmeVecAAH;

	if (vec->m_bfmeFinishAAH != vec->m_bfmeEndAAH)
	{
		if (vec->m_bfmeFinishAAH != 0)
			*vec->m_bfmeFinishAAH = v;

		++vec->m_bfmeFinishAAH;
	}
	else
	{
		_STL::__false_type tag;

		vec->_M_insert_overflow(vec->m_bfmeFinishAAH, v, tag, true, 1);
	}
}
