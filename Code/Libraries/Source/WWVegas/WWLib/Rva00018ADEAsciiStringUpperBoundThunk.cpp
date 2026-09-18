// cl: /DNDEBUG /MD /EHsc
// The three callers use this incremental-link thunk for the set<AsciiString>
// upper-bound specialization already matched at retail 0x000804D0.

class AsciiString
{
};

namespace _STL
{
	template <class Value>
	struct _Rb_tree_node
	{
	};

	class AsciiStringTreeUpperBoundShim
	{
	public:
		_Rb_tree_node<AsciiString> *upper_bound(const AsciiString &) const;
	};
}

class Rva00018ADEThunk
{
public:
	_STL::_Rb_tree_node<AsciiString> *forward(const AsciiString &key) const;
};

_STL::_Rb_tree_node<AsciiString> *Rva00018ADEThunk::forward(
	const AsciiString &key) const
{
	return ((const _STL::AsciiStringTreeUpperBoundShim *)this)->upper_bound(key);
}
