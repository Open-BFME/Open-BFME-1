// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// 0x0094C5A0 (rva0094C5A0MakePair) now lives in
// game/GameEngineDevice/Source/W3DDevice/GameClient/Rva0094D1E0List_rva0094D250.cpp,
// whose caller 0x0094D250 needs its body visible.

// 0x0094C450 (15 bytes), unreferenced: copies the node pointer held at +0,
// steps it back with _Rb_global<bool>::_M_decrement and returns the address
// of the node's value field (+0x10) -- the shape of a reverse iterator's
// operator* over some red-black tree.  The tree's value type is unknown, so
// the name stays address-derived.
namespace _STL
{
struct _Rb_tree_node_base;
template <class _Dummy> struct _Rb_global
{
	static _Rb_tree_node_base *_M_decrement(_Rb_tree_node_base *);
};
}

struct Rva0094C450TreeIterator
{
	_STL::_Rb_tree_node_base *_M_node;
	void _M_decrement() { _M_node = _STL::_Rb_global<bool>::_M_decrement(_M_node); }
};

class Rva0094C450ReverseIterator
{
public:
	char &deref() const;
	Rva0094C450TreeIterator m_current;
};

char &Rva0094C450ReverseIterator::deref() const
{
	Rva0094C450TreeIterator tmp = m_current;
	tmp._M_decrement();
	return *((char *)tmp._M_node + 0x10);
}
