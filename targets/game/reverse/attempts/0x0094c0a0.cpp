// ?d_0094c0a0@@YAXXZ
// partial score=0.95 date=2026-09-26
// cl: /O2 /Ob0

namespace _STL { struct _Rb_tree_node_base; }
extern "C" _STL::_Rb_tree_node_base *__cdecl bfme_RbGlobalBoolDecrement_82B8E0(_STL::_Rb_tree_node_base *);
class Rva0094C0A0TreePrevValue
{
	_STL::_Rb_tree_node_base *m_node;
public:
	void *value() const;
};
void *Rva0094C0A0TreePrevValue::value() const
{
	return reinterpret_cast<unsigned char *>(bfme_RbGlobalBoolDecrement_82B8E0(m_node)) + 0x10;
}
