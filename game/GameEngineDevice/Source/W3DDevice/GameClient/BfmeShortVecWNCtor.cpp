// cl: /O2 /Oi
// stlport
#include <vector>
struct Gen_t_0074cbe0_p2pod { short a; };
namespace _STL { template<> _Vector_base<Gen_t_0074cbe0_p2pod, allocator<Gen_t_0074cbe0_p2pod> >::_Vector_base(unsigned, const allocator<Gen_t_0074cbe0_p2pod>&); }

class BfmeShortVecWN
{
public:
	BfmeShortVecWN(unsigned n);

	unsigned short *m_start;
	unsigned short *m_finish;
};

template <class Output, class Size, class Value>
static inline Output bfmeFillN(Output first, Size count, const Value &value)
{
	for (; count > 0; --count, ++first)
		*first = value;
	return first;
}

template <class Forward, class Size, class Value>
static inline Forward bfmeUninitializedFillN(
	Forward first, Size count, const Value &value)
{
	return bfmeFillN(first, count, value);
}

BfmeShortVecWN::BfmeShortVecWN(unsigned n)
{
	unsigned count = n;
	reinterpret_cast<_STL::_Vector_base<Gen_t_0074cbe0_p2pod, _STL::allocator<Gen_t_0074cbe0_p2pod> > *>(this)->_STL::_Vector_base<Gen_t_0074cbe0_p2pod, _STL::allocator<Gen_t_0074cbe0_p2pod> >::_Vector_base(count, *reinterpret_cast<const _STL::allocator<Gen_t_0074cbe0_p2pod> *>(&n));
	unsigned short *p = m_start;
	if (count > 0)
		m_finish = bfmeUninitializedFillN(p, count, unsigned short());
	else
		m_finish = p;
}
