// ?insert_unique@?$_Rb_tree@UGen_p12pod@@U?$pair@$$CBUGen_p12pod@@H@_STL@@U?$_Select1st@U?$pair@$$CBUGen_p12pod@@H@_STL@@@3@U?$less@UGen_p12pod@@@3@V?$allocator@U?$pair@$$CBUGen_p12pod@@H@_STL@@@3@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBUGen_p12pod@@H@_STL@@U?$_Nonconst_traits@U?$pair@$$CBUGen_p12pod@@H@_STL@@@2@@2@U32@ABU?$pair@$$CBUGen_p12pod@@H@2@@Z
// Open-BFME: STLport hinted _Rb_tree::insert_unique for Gen_p12pod, retail
// RVA 0x009282C0, 718 bytes. Identity is independently pinned by the
// Gen_p12pod map operator[] caller at 0x00928690 and the insertion callee
// symbol above. The redundant bool assignment is intentional: it reproduces
// the retail adjacent materialization order in MSVC 7.1 without a byte lift.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

struct Gen_p12pod
{
	int a[3];
};

inline bool compare_tail(const Gen_p12pod &a, const Gen_p12pod &b)
{
	const int a1 = a.a[1];
	return b.a[1] > a1
		|| (!(b.a[1] < a1) && a.a[2] < b.a[2]);
}

inline bool operator<(const Gen_p12pod &a, const Gen_p12pod &b)
{
	const int a0 = a.a[0];
	return b.a[0] > a0 || (!(b.a[0] < a0) && compare_tail(a, b));
}

typedef _STL::pair<const Gen_p12pod, int> GenP12Pair;
typedef _STL::_Rb_tree<Gen_p12pod, GenP12Pair,
	_STL::_Select1st<GenP12Pair>, _STL::less<Gen_p12pod>,
	_STL::allocator<GenP12Pair> > GenP12Tree;

template <>
GenP12Tree::iterator GenP12Tree::insert_unique(
	GenP12Tree::iterator __position, const GenP12Pair &__v)
{
	if (__position._M_node == this->_M_header._M_data->_M_left) {
		if (size() <= 0)
			return insert_unique(__v).first;

		if (_M_key_compare(_STL::_Select1st<GenP12Pair>()(__v),
			_S_key(__position._M_node)))
			return _M_insert(__position._M_node, __position._M_node, __v);
		else {
			bool __comp_pos_v = _M_key_compare(
				_S_key(__position._M_node), _STL::_Select1st<GenP12Pair>()(__v));
			if (__comp_pos_v == false)
				return __position;
			iterator __after = __position;
			++__after;
			if (__after._M_node == this->_M_header._M_data)
				return _M_insert(0, __position._M_node, __v, __position._M_node);
			if (_M_key_compare(_STL::_Select1st<GenP12Pair>()(__v),
				_S_key(__after._M_node))) {
				if (_S_right(__position._M_node) == 0)
					return _M_insert(0, __position._M_node, __v, __position._M_node);
				else
					return _M_insert(__after._M_node, __after._M_node, __v);
			} else
				return insert_unique(__v).first;
		}
	} else if (__position._M_node == this->_M_header._M_data) {
		if (_M_key_compare(_S_key(_M_rightmost()),
			_STL::_Select1st<GenP12Pair>()(__v)))
			return _M_insert(0, _M_rightmost(), __v, __position._M_node);
		else
			return insert_unique(__v).first;
	} else {
		iterator __before = __position;
		--__before;
		bool __comp_pos_v = false;
		bool __comp_v_pos = _M_key_compare(
			_STL::_Select1st<GenP12Pair>()(__v), _S_key(__position._M_node));
		if (__comp_v_pos
			&& _M_key_compare(_S_key(__before._M_node),
				_STL::_Select1st<GenP12Pair>()(__v))) {
			if (_S_right(__before._M_node) == 0)
				return _M_insert(0, __before._M_node, __v, __before._M_node);
			else
				return _M_insert(__position._M_node, __position._M_node, __v);
		} else {
			iterator __after = __position;
			++__after;
			__comp_pos_v = __comp_v_pos;
			__comp_pos_v = !__comp_pos_v;
			if (!__comp_v_pos)
				__comp_pos_v = _M_key_compare(
					_S_key(__position._M_node),
					_STL::_Select1st<GenP12Pair>()(__v));
			if (!__comp_v_pos && __comp_pos_v
				&& (__after._M_node == this->_M_header._M_data
					|| _M_key_compare(_STL::_Select1st<GenP12Pair>()(__v),
						_S_key(__after._M_node)))) {
				if (_S_right(__position._M_node) == 0)
					return _M_insert(0, __position._M_node, __v, __position._M_node);
				else
					return _M_insert(__after._M_node, __after._M_node, __v);
			} else {
				if (__comp_v_pos == __comp_pos_v)
					return __position;
				else
					return insert_unique(__v).first;
			}
		}
	}
}

template GenP12Tree::iterator
GenP12Tree::insert_unique(GenP12Tree::iterator, const GenP12Pair &);
