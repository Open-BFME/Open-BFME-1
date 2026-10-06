struct BfmeNodeSD
{
	unsigned char m_bfmeHead[4];
	unsigned short m_bfmeTag;
};

struct BfmeKeySD
{
	BfmeNodeSD *m_bfmeNode;
};

struct BfmeSlotSD
{
	unsigned char m_bfmeHead[0x14];
	void *m_bfmeWhat;
};

// Retail calls the STLport _Rb_tree<AsciiString, ...>::_M_find<AsciiString>
// body at 0x00142FD0 (ILT 0x00020E7D), matched in
// WWLib/RvaTreeFindAsciiString.cpp.  Only the declaration that body's name
// needs is spelled here; the key is the AsciiString the caller passes.
class AsciiString;
struct Rva00142FD0Value;
struct Rva00142FD0KeyOfValue;

namespace _STL
{
template <class T> struct less;
template <class T> class allocator;
template <class V> struct _Rb_tree_node;

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
public:
	template <class KT> _Rb_tree_node<Value> *find(const KT &key) const
	{
		return _M_find(key);
	}

private:
	template <class KT> _Rb_tree_node<Value> *_M_find(const KT &key) const;
};
}

typedef _STL::_Rb_tree<AsciiString, Rva00142FD0Value, Rva00142FD0KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva00142FD0Value> > Rva00142FD0Tree;

class BfmeMapSD
{
public:
	BfmeSlotSD *bfmeFindSD(BfmeKeySD *key) const
	{
		return reinterpret_cast<BfmeSlotSD *>(
			reinterpret_cast<const Rva00142FD0Tree *>(this)->find(
				*reinterpret_cast<const AsciiString *>(key)));
	}
	BfmeSlotSD *m_bfmeFirst;
};

class BfmeThingSD
{
public:
	void ** bfmeLookSD(BfmeKeySD *key);
	unsigned char m_bfmeHead[0x328];
	BfmeMapSD m_bfmeMap;
};

void ** BfmeThingSD::bfmeLookSD(BfmeKeySD *key)
{
	BfmeNodeSD *node = key->m_bfmeNode;
	if (node == 0)
		return 0;
	if (node->m_bfmeTag == 0)
		return 0;
	BfmeSlotSD *at = m_bfmeMap.bfmeFindSD(key);
	if (at == m_bfmeMap.m_bfmeFirst)
		return 0;
	return &at->m_bfmeWhat;
}
