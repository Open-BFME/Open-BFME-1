// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::_Rb_tree<AsciiString, pair<const AsciiString,
// ArchivedDirectoryInfo> >::~_Rb_tree, retail 0x009C9570, 83 bytes. The body
// carried only a machine byte-dump row; reverse/reloc_names.csv holds the name
// with identity=real.
//
// STLport's own destructor is just clear(). Everything after the call is the
// base destructor folded in: _Rb_tree_base releases the header node through
// the allocator, which null-checks and then hands the node to the node
// allocator's static deallocate. The unwind state around clear() is there so
// that base destructor still runs if clear() throws.
//
// The size argument fixes the value type: 0x30 for the node, less the 16-byte
// node base, leaves 0x20 for pair<const AsciiString, ArchivedDirectoryInfo>.
// AsciiString is one pointer, so ArchivedDirectoryInfo is the remaining 28.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
	char *m_bfmeData;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ArchiveFileSystem.h
class ArchivedDirectoryInfo
{
	char m_bfmeBody[28];
};

namespace _STL
{

template <bool threads, int inst>
class __node_alloc
{
public:
	static void _M_deallocate(void *p, unsigned int n);	// retail 0x0082E5F0
};

template <class T>
class allocator
{
public:
	void deallocate(T *p, unsigned int n)
	{
		if (p != 0)
			__node_alloc<true, 0>::_M_deallocate(p, n * sizeof(T));
	}
};

// pair, less and _Select1st are structs, not classes: the retail name spells
// them U while allocator stays V.
template <class T1, class T2>
struct pair
{
	T1 first;
	T2 second;
};

template <class T>
struct less {};

template <class T>
struct _Select1st {};

struct _Rb_tree_node_base
{
	int _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};

template <class T>
struct _Rb_tree_node : public _Rb_tree_node_base
{
	T _M_value_field;
};

template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
	Pointer _M_data;					// +0x00
};

template <class T, class Alloc>
struct _Rb_tree_base
{
	typedef _Rb_tree_node<T> _Node;

	~_Rb_tree_base(void)
	{
		_M_header.deallocate(_M_header._M_data, 1);
	}

	_STLP_alloc_proxy<_Node *, _Node, allocator<_Node> > _M_header;
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree : public _Rb_tree_base<Value, Alloc>
{
public:
	~_Rb_tree(void) { clear(); }

	void clear(void);					// retail 0x009CAC00
};

}

typedef _STL::pair<const AsciiString, ArchivedDirectoryInfo> BfmeArchivedDirEntry;

typedef _STL::_Rb_tree<AsciiString, BfmeArchivedDirEntry,
	_STL::_Select1st<BfmeArchivedDirEntry>, _STL::less<AsciiString>,
	_STL::allocator<BfmeArchivedDirEntry> > BfmeArchivedDirTree;

// The destructor is only emitted if something reaches it, and a pseudo-
// destructor call on its own gets inlined into the caller instead.
namespace _STL
{
template class _Rb_tree<AsciiString, BfmeArchivedDirEntry,
	_Select1st<BfmeArchivedDirEntry>, less<AsciiString>,
	allocator<BfmeArchivedDirEntry> >;
}
