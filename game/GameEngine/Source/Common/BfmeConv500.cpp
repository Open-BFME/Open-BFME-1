// Retail's +0x07 call target at 0x0082B8E0 is the matched STLport 4.5.3
// _STL::_Rb_global<bool>::_M_decrement
// (game/Libraries/Source/WWVegas/WWLib/STLRbGlobalBoolDecrementThunk.cpp), a
// static member taking and returning a _Rb_tree_node_base*, so the placeholder
// free function bfmeMakeBOA is respelled as that member.

namespace _STL
{
	struct _Rb_tree_node_base;

	template <class _Dummy>
	class _Rb_global
	{
	public:
		static _Rb_tree_node_base *__cdecl _M_decrement(_Rb_tree_node_base *);
	};
}

class BfmeThingBOA
{
public:
	void bfmeGoBOA(void **out, void *spare);
	void *m_bfmeWhat;
};

void BfmeThingBOA::bfmeGoBOA(void **out, void *spare)
{
	void *old = m_bfmeWhat;
	m_bfmeWhat = _STL::_Rb_global<bool>::_M_decrement((_STL::_Rb_tree_node_base *)old);
	*out = old;
}