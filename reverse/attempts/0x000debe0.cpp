// ?_M_fill_insert@?$vector@UBfmeItemERE@@V?$allocator@UBfmeItemERE@@@_STL@@@_STL@@QAEXPAUBfmeItemERE@@IABU3@@Z
// partial score=0.9 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <vector>

class BfmeStrERE
{
public:
	BfmeStrERE();
	BfmeStrERE(const BfmeStrERE &);
	~BfmeStrERE();

	void *m_data;
};

class BfmeSubERE
{
public:
	BfmeSubERE();
	BfmeSubERE(const BfmeSubERE &);
	~BfmeSubERE();

	unsigned char m_body[12];
};

struct BfmeItemERE
{
	BfmeStrERE m_name;
	BfmeSubERE m_sub;

	BfmeItemERE();
	BfmeItemERE(const BfmeItemERE &);
	~BfmeItemERE();
};

template class _STL::vector<BfmeItemERE>;
