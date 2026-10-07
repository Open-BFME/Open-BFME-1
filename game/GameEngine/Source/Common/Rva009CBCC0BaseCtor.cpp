// cl: /DNDEBUG /MD /EHsc
// RVA 0x009CBCC0: two null fields and an allocator proxy at +8.
// The 11-byte callee at 0x009CBC00 stores its second argument at the
// proxy address and returns with two stack arguments consumed.

// 0x009CBC00 is the STLport alloc proxy ctor GameAudio.cpp emits for its
// AsciiString -> AudioEventInfo* hash map element counter (callees.py).
class AsciiString;
struct AudioEventInfo;
namespace _STL
{
template <class T> class allocator;
template <class T1, class T2> struct pair;
template <class V> struct _Hashtable_node;
template <class V, class T, class A> class _STLP_alloc_proxy
{
public:
	_STLP_alloc_proxy(const A &a, V p);

	V _M_data;
};
}

typedef _STL::_Hashtable_node<_STL::pair<const AsciiString, AudioEventInfo *> > Rva009CBCC0Node;
typedef _STL::_STLP_alloc_proxy<unsigned int, Rva009CBCC0Node, _STL::allocator<Rva009CBCC0Node> > Rva009CBC00AllocatorProxy;

class Rva009CBCC0Owner
{
public:
	Rva009CBCC0Owner(const void *allocator);

private:
	void *m_start;
	void *m_finish;
	Rva009CBC00AllocatorProxy m_storage;
};

Rva009CBCC0Owner::Rva009CBCC0Owner(const void *allocator)
	: m_start(0), m_finish(0), m_storage(*(const _STL::allocator<Rva009CBCC0Node> *)allocator, 0)
{
}
