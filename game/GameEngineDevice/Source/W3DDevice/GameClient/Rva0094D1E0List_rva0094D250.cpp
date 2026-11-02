// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Rva0094D1E0List::rva0094D250, retail 0x0094D250 (253 bytes, ret 4): adds a
// texture handle to the list's texture-keyed tree (this+8) when it is not
// already present, then resets the cursor at +0x14 to the leftmost node and
// sets the changed flag at +0x1C.  W3DShrubBuffer::updateTexture (0x0071DAF0)
// and W3DTreeBuffer::updateTexture (0x007348A0) call it directly under this
// pinned name; the constructor (0x0094D1E0) and clear (0x0094CE50) live beside
// this file.
//
// The key is a reference-counted texture pointer: the pair construction at
// 0x0094C650 bumps the 16-bit count at +4 and the temporaries release through
// TextureClass::Release_Ref (0x009EB7A0).  The tree, its insert_unique
// (0x0094CCF0) and _M_insert (0x0094C9E0) keep the unsigned-key spelling of
// RvaTreeInsertUniqueUnsigned.cpp / RvaTreeMInsertPair.cpp; the pair view below
// only gives `first` the handle's copy and release.
//
// Codegen: the insert chain (insert_unique, _M_insert, _Construct) and the
// pair maker 0x0094C5A0 must be visible bodies.  With any of them opaque VC7.1
// reloads the inserted key after the call instead of keeping it in ESI, and an
// opaque maker keeps the zeroed mapped value alive across the insert so it
// cannot share the insert result's slot (frame 0x40 instead of 0x38).  The
// retail STLport configuration (no exceptions, as in Rva0094D370TextureMap.cpp)
// lets _M_insert inline its node allocation; every COMDAT this TU emits under a
// ledger name is byte-identical to its retail row.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define _STLP_NO_EXCEPTIONS
#define __PLACEMENT_VEC_NEW_INLINE
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include <map>

class TextureClass
{
public:
	void Release_Ref();
};

class BFMEWaterTrackTextureHandle
{
public:
	TextureClass *m_texture;
};

class Rva0094C5A0Handle
{
public:
	Rva0094C5A0Handle(const Rva0094C5A0Handle &other) : value(other.value)
	{
		if (value)
			++*(unsigned short *)((char *)value + 4);
	}
	operator const unsigned int &() const
	{
		return *(const unsigned int *)&value;
	}
	~Rva0094C5A0Handle()
	{
		if (value)
			value->Release_Ref();
	}
	TextureClass *value;
};

struct Rva0094C5A0Value
{
	unsigned value[4];
};

struct Rva0094C5A0Pair
{
	Rva0094C5A0Pair(const Rva0094C5A0Handle &first, const Rva0094C5A0Value &second) : m_first(first), m_second(second) {}
	Rva0094C5A0Handle m_first;
	Rva0094C5A0Value m_second;
};

// ?rva0094C5A0MakePair@@YA?AURva0094C5A0Pair@@PBVRva0094C5A0Handle@@PBURva0094C5A0Value@@@Z
// Retail 0x0094C5A0 (61 bytes): make_pair of handle and mapped value.
inline __declspec(noinline) Rva0094C5A0Pair __cdecl rva0094C5A0MakePair(const Rva0094C5A0Handle *first, const Rva0094C5A0Value *second)
{
	return Rva0094C5A0Pair(*first, *second);
}

struct Rva0094CCF0Value
{
	char m_body[16];
};

namespace _STL
{
template <> struct pair<const unsigned int, ::Rva0094CCF0Value>
{
	typedef const unsigned int first_type;
	typedef ::Rva0094CCF0Value second_type;
	pair(const ::Rva0094C5A0Pair &other) : first(other.m_first), second(*(const ::Rva0094CCF0Value *)&other.m_second) {}
	pair(const pair &other) : first(other.first), second(other.second) {}
	const ::Rva0094C5A0Handle first;
	::Rva0094CCF0Value second;
};
}

typedef _STL::pair<const unsigned int, Rva0094CCF0Value> Rva0094CCF0Pair;

typedef _STL::_Rb_tree<unsigned int,
	Rva0094CCF0Pair,
	_STL::_Select1st<Rva0094CCF0Pair>,
	_STL::less<unsigned int>,
	_STL::allocator<Rva0094CCF0Pair> > Rva0094CCF0Tree;


struct Rva0094D250Node
{
	int m_color;
	Rva0094D250Node *m_parent;
	Rva0094D250Node *m_left;
	Rva0094D250Node *m_right;
};

struct Rva0094C5E0Iterator
{
	Rva0094C5E0Iterator() {}
	Rva0094C5E0Iterator(Rva0094D250Node *x) : node(x) {}
	Rva0094D250Node *node;
};

struct Rva0094C5E0Tree
{
	Rva0094D250Node *head;
	unsigned count;
	Rva0094C5E0Iterator find(const unsigned &key);	// retail 0x0094C5E0
};

static __forceinline const Rva0094C5A0Value *addressOf(const Rva0094C5A0Value &value)
{
	return &value;
}

class Rva0094D1E0List
{
public:
	void rva0094D250(const BFMEWaterTrackTextureHandle &texture);

private:
	int m_capacity;
	int m_extra;
	Rva0094C5E0Tree m_tree;
	int m_compare;
	Rva0094C5E0Iterator m_cursor;
	int m_index;
	bool m_changed;
	bool m_reset;
};

// ?rva0094D250@Rva0094D1E0List@@QAEXABVBFMEWaterTrackTextureHandle@@@Z
void Rva0094D1E0List::rva0094D250(const BFMEWaterTrackTextureHandle &texture)
{
	if (texture.m_texture == 0)
		return;
	Rva0094D250Node *head = m_tree.head;
	Rva0094C5E0Iterator it = m_tree.find(*(const unsigned *)&texture);
	if (it.node != head)
		return;
	((Rva0094CCF0Tree *)&m_tree)->insert_unique(
		rva0094C5A0MakePair((const Rva0094C5A0Handle *)&texture, addressOf(Rva0094C5A0Value())));
	m_cursor = Rva0094C5E0Iterator(m_tree.head->m_left);
	m_changed = true;
}
