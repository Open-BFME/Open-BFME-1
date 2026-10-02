// stlport

#include <map>
#include <vector>

// These are the defining template arguments for the three retail callees.
struct Gen_t_004247c0_p4pod { int a[1]; };
typedef _STL::pair<const int, Gen_t_004247c0_p4pod> TgPair_tree_int_p4pod_004247c0;
typedef _STL::_Rb_tree<int, TgPair_tree_int_p4pod_004247c0,
	_STL::_Select1st<TgPair_tree_int_p4pod_004247c0>, _STL::less<int>,
	_STL::allocator<TgPair_tree_int_p4pod_004247c0> > BfmeSubERF;

struct Rva004262F0Elem;
struct Rva00426C00Element;

// Use the ledger's existing definitions without instantiating new copies.
namespace _STL
{
	template <> BfmeSubERF::~_Rb_tree();
	template <> vector<Rva004262F0Elem>::iterator
		vector<Rva004262F0Elem>::erase(iterator first, iterator last);
	template <> void vector<Rva00426C00Element>::_M_fill_insert(
		iterator where, size_type count, const Rva00426C00Element &value);
}

struct BfmeItemERF
{
	unsigned char m_bfmeHeadERF[16];
	BfmeSubERF m_bfmeSubERF;
};

class BfmeVecERF
{
public:
	void bfmeResizeERF(unsigned int count, BfmeItemERF value);

	BfmeItemERF *m_bfmeFirstERF;
	BfmeItemERF *m_bfmeLastERF;
};

void BfmeVecERF::bfmeResizeERF(unsigned int count, BfmeItemERF value)
{
	if (count < (unsigned int)(m_bfmeLastERF - m_bfmeFirstERF))
		((_STL::vector<Rva004262F0Elem> *)this)->erase(
			(Rva004262F0Elem *)(m_bfmeFirstERF + count),
			(Rva004262F0Elem *)m_bfmeLastERF);
	else
	{
		unsigned int extra =
			count - (unsigned int)(m_bfmeLastERF - m_bfmeFirstERF);

		((_STL::vector<Rva00426C00Element> *)this)->_M_fill_insert(
			(Rva00426C00Element *)m_bfmeLastERF, extra,
			(const Rva00426C00Element &)value);
	}
}
