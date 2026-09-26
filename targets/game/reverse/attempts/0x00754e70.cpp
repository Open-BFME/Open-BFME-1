// ?d_00754e70@@YAXXZ
// partial score=0.36 date=2026-09-24
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ivendor/stlport
// Bounded 0x00754E70/128 bank, not a verified conversion. Retail creates a
// default-empty 12-byte vector, allocates a 20-byte node, copy-constructs its
// payload through ILT 0x000494AE, and links it before the supplied position.
// This native new-expression emits the same Form-A SEH family, but compiles to
// 125 bytes with 81 non-relocation differences and three wrong relocation
// sites. It calls a local node constructor instead of the retail vector copy.
// Do not land until the constructor route and frame/dataflow match strictly.
#include <list>

struct BfmeVecAY
{
    BfmeVecAY() : m_start(0), m_finish(0), m_end(0) {}
    BfmeVecAY(const BfmeVecAY &other);
    int *m_start;
    int *m_finish;
    int *m_end;
};

class Rva00754E70List
{
public:
    _STL::list<BfmeVecAY>::iterator rva00754E70(_STL::list<BfmeVecAY>::iterator where);
private:
    _STL::list<BfmeVecAY> m_values;
};

struct Rva00754E70Node : _STL::_List_node_base
{
    BfmeVecAY m_data;
    Rva00754E70Node(const BfmeVecAY &value) : m_data(value) {}
    static void *operator new(unsigned n) { return _STL::__new_alloc::allocate(n); }
    static void operator delete(void *p) { _STL::__new_alloc::deallocate(p, sizeof(Rva00754E70Node)); }
};

_STL::list<BfmeVecAY>::iterator Rva00754E70List::rva00754E70(_STL::list<BfmeVecAY>::iterator where)
{
    BfmeVecAY empty;
    Rva00754E70Node *node = new Rva00754E70Node(empty);
    _STL::_List_node_base *position = where._M_node;
    _STL::_List_node_base *before = position->_M_prev;
    node->_M_next = position;
    node->_M_prev = before;
    before->_M_next = node;
    position->_M_prev = node;
    return (_STL::_List_node<BfmeVecAY> *)node;
}
