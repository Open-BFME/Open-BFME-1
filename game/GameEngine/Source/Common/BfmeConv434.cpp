namespace _STL
{
struct _Rb_tree_node_base;
template <class Threading>
struct _Rb_global
{
	static _Rb_tree_node_base *__cdecl _M_decrement(_Rb_tree_node_base *);
};
}

class BfmeThingBBB
{
public:
	void *bfmeGetBBB();
	void *m_bfmeSub;
};

void *BfmeThingBBB::bfmeGetBBB()
{
	_STL::_Rb_tree_node_base *sub = reinterpret_cast<_STL::_Rb_tree_node_base *>(m_bfmeSub);
	return reinterpret_cast<unsigned char *>(_STL::_Rb_global<bool>::_M_decrement(sub)) + 0x10;
}
