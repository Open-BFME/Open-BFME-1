// cl: /DNDEBUG /MD /EHsc
// RVA 0x009CA440: public tree lower_bound wrapper around the matched 0x009C9CE0
// _M_lower_bound specialization. The address-derived callable is pinned to that
// proven target. The tree owner remains unproven, so the ledger identity keeps this address.

class AsciiString;
class Rva009CA440Owner;
class ArchivedDirectoryInfo;
struct Rva009C9CE0Value;
struct Rva009C9CE0KeyOfValue;
namespace _STL {
 template<class A, class B> struct pair;
 template<class T> struct _Select1st;
 template<class T> struct less;
 template<class T> class allocator;
 template<class T> struct _Rb_tree_node;
 template<class K,class V,class E,class C,class A> class _Rb_tree {
  template<class Q> _Rb_tree_node<V> *_M_find(const Q &) const;
  _Rb_tree_node<V> *_M_lower_bound(const K &) const;
  friend class ::Rva009CA440Owner;
 };
}

struct Rva009CA440Result
{
    void *m_node;
    explicit Rva009CA440Result(void *node) : m_node(node) {}
};

class Rva009CA440Owner
{
public:
    Rva009CA440Result lower_bound(const AsciiString &key) const;
};

Rva009CA440Result Rva009CA440Owner::lower_bound(const AsciiString &key) const
{
    return Rva009CA440Result(reinterpret_cast<const _STL::_Rb_tree<AsciiString, Rva009C9CE0Value, Rva009C9CE0KeyOfValue, _STL::less<AsciiString>, _STL::allocator<Rva009C9CE0Value> > *>(this)->_M_lower_bound(key));
}
