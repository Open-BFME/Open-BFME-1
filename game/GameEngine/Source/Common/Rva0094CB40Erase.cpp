// ?erase@Rva0094CB40@@QAEXABI@Z
// Retail returns with ret 4 at RVA 0x0094CBA3 after removing a keyed tree node.
// No caller or string identifies the owner, so the class keeps the body address.
// The volatile iterator node read preserves retail's order before the tree-head read.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
namespace _STL {
struct _Rb_tree_node_base { int color; _Rb_tree_node_base *parent,*left,*right; };
template<class T> struct _Rb_global { static _Rb_tree_node_base *_Rebalance_for_erase(_Rb_tree_node_base *,_Rb_tree_node_base *&,_Rb_tree_node_base *&,_Rb_tree_node_base *&); };
template<bool T,int N> class __node_alloc { public: static void _M_deallocate(void *,unsigned int); };
}
struct Rva0094BFD0 { void *m_reference; unsigned char m_04[16]; ~Rva0094BFD0(); };
struct Rva0094CB40Node : _STL::_Rb_tree_node_base { Rva0094BFD0 payload; };
struct Rva0094C5E0Iterator { Rva0094CB40Node *volatile node; Rva0094C5E0Iterator() {} };
struct Rva0094C5E0Tree { Rva0094CB40Node *head; unsigned count; Rva0094C5E0Iterator find(const unsigned&); };
class Rva0094CB40 {
 unsigned m_0[2]; Rva0094C5E0Tree m_tree; unsigned m_10; Rva0094CB40Node *m_14; unsigned m_18; bool m_1c;
public: void erase(const unsigned &key);
};
void Rva0094CB40::erase(const unsigned &key) {
 Rva0094C5E0Tree *tree=&m_tree;
 Rva0094C5E0Iterator it = tree->find(key);
 Rva0094CB40Node *found = it.node;
 if(found == tree->head) return;
 Rva0094CB40Node *node=static_cast<Rva0094CB40Node*>(_STL::_Rb_global<bool>::_Rebalance_for_erase(found,tree->head->parent,tree->head->left,tree->head->right));
 node->payload.~Rva0094BFD0();
 if(node) _STL::__node_alloc<false,0>::_M_deallocate(node,0x24);
 --tree->count;
 m_14=static_cast<Rva0094CB40Node*>(tree->head->left);
 m_1c=true;
}

// Retail 0x0094C6C0: hidden-result forwarding to the tree find at 0x0094C5E0.
// The wrapper's owner is not established; its address identifies the ABI view.
class Rva0094C6C0
{
    Rva0094C5E0Tree m_tree;
public:
    Rva0094C5E0Iterator find(const unsigned &key);
};

Rva0094C5E0Iterator Rva0094C6C0::find(const unsigned &key)
{
    return m_tree.find(key);
}
