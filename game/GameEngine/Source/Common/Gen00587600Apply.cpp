// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Open-BFME5: the two-argument generator member at retail 0x00587600 (88B).
// The retail object is a STLport hash table whose mapped value is a compact
// generated POD, followed by a vector of the corresponding compact value.
#include <vector>

struct Gen_t_005863d0_m12pod { int a[3]; };
struct Gen_t_00587480_m4pod { int a[1]; };

struct BfmeApplyNode
{
	char m_bfmeFields[0x24];
	_STL::vector<Gen_t_00587480_m4pod> m_bfmeValues;
};

namespace _STL
{
	template <class T> struct pair<T, T>
	{
		T first;
		pair() {}
		pair(const pair &other) : first(other.first) {}
	};

	template <class T> struct hash {};
	template <class Pair> struct _Select1st {};
	template <class T> struct equal_to {};
	template <class Value, class Traits, class Key, class Hash, class Extract,
		class Equal, class Alloc>
	struct _Ht_iterator
	{
		_Ht_iterator() {}
		_Ht_iterator(const _Ht_iterator &other) : _M_cur(other._M_cur) {}

		void * _M_cur;
	};

	template <class Value, class Key, class Hash, class Extract, class Equal,
		class Alloc>
	class hashtable
	{
	public:
		typedef _Ht_iterator<Value, _Nonconst_traits<Value>, Key, Hash, Extract,
			Equal, Alloc> iterator;
		typedef _STL::pair<iterator, iterator> result_type;

		result_type equal_range(const Key &key);

		BfmeApplyNode *m_bfmeHead;
	};
}

typedef _STL::pair<const int, Gen_t_005863d0_m12pod> BfmeApplyPair;
typedef _STL::hashtable<BfmeApplyPair, int, _STL::hash<int>,
	_STL::_Select1st<BfmeApplyPair>, _STL::equal_to<int>,
	_STL::allocator<BfmeApplyPair> > BfmeApplyTable;

class BfmeApplyTree
{
public:
	BfmeApplyTable m_bfmeMap;
};

class Gen00587600
{
public:
	void apply(int value, int which);

private:
	char m_bfmeFields[0x24];
	BfmeApplyTree m_bfmeTree;
};

// ?apply@Gen00587600@@QAEXHH@Z
void Gen00587600::apply(int value, int which)
{
	BfmeApplyTable::result_type range = m_bfmeTree.m_bfmeMap.equal_range(value);
	if (range.first._M_cur != m_bfmeTree.m_bfmeMap.m_bfmeHead)
		reinterpret_cast<BfmeApplyNode *>(range.first._M_cur)->m_bfmeValues.push_back(
			reinterpret_cast<const Gen_t_00587480_m4pod &>(which));
}
