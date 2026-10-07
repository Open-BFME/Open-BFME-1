// Retail 0x00198120: the call at +0x1E goes through ILT 0x0000C815 to the
// matched STLport vector copy constructor at 0x00195C40 (callees.py), so the
// second member is constructed by that body from the argument.

class Gen_00193D50;

namespace _STL
{
	template <typename T> class allocator;
	template <typename T, typename Alloc = allocator<T> > class vector
	{
	public:
		vector(const vector &other);
	};
}

typedef _STL::vector<Gen_00193D50> BfmeVecDOD;

struct BfmeOutDOD
{
	int m_bfmeA;
	char m_bfmeSub[12];
};

BfmeOutDOD *bfmeGoDOD(BfmeOutDOD *out, int *src, void *arg)
{
	volatile int tmp = 0;
	out->m_bfmeA = *src;
	((BfmeVecDOD *)out->m_bfmeSub)->BfmeVecDOD::vector(*(const BfmeVecDOD *)arg);
	return out;
}
