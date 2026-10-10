// cl: /O2 /GX- /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
#include <map>

struct Gen_t_00424ac0_p12cd;

// ILT 0x000083E1 reaches the ledger-owned tree assignment at 0x00424AC0.
extern template class _STL::_Rb_tree<int,
	_STL::pair<const int, Gen_t_00424ac0_p12cd>,
	_STL::_Select1st<_STL::pair<const int, Gen_t_00424ac0_p12cd> >,
	_STL::less<int>, _STL::allocator<_STL::pair<const int, Gen_t_00424ac0_p12cd> > >;

// Open-BFME5: STLport __copy for the 28-byte Rva004262F0 element.  The first
// four dwords are inline fields; the trailing twelve-byte map member uses its
// out-of-line assignment operator through ILT 0x000083E1.

class BfmeRva004262F0Map
{
private:
	char m_raw[ 12 ];
};

struct Rva004262F0Elem
{
	int m_field0;
	int m_field4;
	int m_field8;
	int m_fieldC;
	BfmeRva004262F0Map m_map;

	Rva004262F0Elem &operator=( const Rva004262F0Elem &that )
	{
		m_field0 = that.m_field0;
		m_field4 = that.m_field4;
		m_field8 = that.m_field8;
		m_fieldC = that.m_fieldC;
		*reinterpret_cast<_STL::_Rb_tree<int,
			_STL::pair<const int, Gen_t_00424ac0_p12cd>,
			_STL::_Select1st<_STL::pair<const int, Gen_t_00424ac0_p12cd> >,
			_STL::less<int>, _STL::allocator<_STL::pair<const int, Gen_t_00424ac0_p12cd> > > *>(&m_map) =
			*reinterpret_cast<const _STL::_Rb_tree<int,
				_STL::pair<const int, Gen_t_00424ac0_p12cd>,
				_STL::_Select1st<_STL::pair<const int, Gen_t_00424ac0_p12cd> >,
				_STL::less<int>, _STL::allocator<_STL::pair<const int, Gen_t_00424ac0_p12cd> > > *>(&that.m_map);
		return *this;
	}
};

namespace _STL
{
template Rva004262F0Elem *__copy<Rva004262F0Elem *, Rva004262F0Elem *, int>(
	Rva004262F0Elem *, Rva004262F0Elem *, Rva004262F0Elem *,
	const random_access_iterator_tag &, int *);
}
