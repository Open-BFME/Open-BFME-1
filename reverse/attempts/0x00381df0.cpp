// ?d_00381df0@@YAXXZ
// partial score=0.85 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc

// Open-BFME: fuzzy-twin of ??0?$list@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@ABV01@@Z
// (retail 0x00080840, 111B, Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLLoginMenu.cpp,
// difflib ratio 0.942 against retail @ 0x00381DF0). Same shape: a list<T,allocator<T>>
// copy-constructor from a "const list &". The element here is 216 bytes (node size
// 0xe0), which crosses STLport's small-object-pool threshold (128 bytes), so the
// header/sentinel node is allocated with a direct ::operator new(0xe0) call (no pool
// wrapper -- confirmed by tools/dis_retail.py on both this body and its element-copy
// helper at retail 0x00381D10, already a landed thunk: thunks_033.cpp j_000448f0 ->
// b_00381d10). This ctor allocates its own sentinel node then delegates the whole
// range-copy loop to that helper in one call, matching retail's single CALL instruction
// (no inline loop in this body).

struct _List_node_base
{
	_List_node_base *_M_next;				// +0x00
	_List_node_base *_M_prev;				// +0x04
};

struct Rva00381DF0Element
{
	char m_body[216];
};

template <class T>
struct _List_node : public _List_node_base
{
	T _M_data;						// +0x08
};

template <class T>
struct _List_iterator
{
	_List_iterator(_List_node_base *node) : _M_node(node) {}

	_List_node_base *_M_node;
};

// RAII base: holds the sentinel node and frees it if the derived list's own
// constructor body throws mid-copy -- the automatic base-subobject destructor
// call is what lets retail use its lightweight esp-based EH frame here instead
// of an explicit try/catch (which forces a heavier ebp-based frame).
template <class T>
class _List_base
{
public:
	typedef _List_node<T> _Node;

	_List_base()
	{
		_M_node = 0;
		_Node *node = (_Node *)::operator new(sizeof(_Node));
		node->_M_next = node;
		node->_M_prev = node;
		_M_node = node;
	}

	~_List_base()
	{
		::operator delete(_M_node);
	}

	_Node *_M_node;
};

template <class T>
class Rva00381DF0List : public _List_base<T>
{
public:
	typedef _List_node<T> _Node;
	typedef _List_iterator<T> iterator;

	Rva00381DF0List(const Rva00381DF0List *that);

private:
	// out-of-line range-copy helper; retail body at 0x00381D10 (thunks_033.cpp
	// j_000448f0 -> b_00381d10); pinned by address-derived name in symbols.csv.
	// The 4th argument (address of the incoming "that" parameter's own stack
	// slot -- a bare "lea", not a load) is passed on the stack alongside the
	// three iterators, matching retail's exact 4-word argument block (proven
	// by tools/dis_retail.py on 0x00381DF0). That shape is only produced when
	// "that" is a POINTER parameter (not a reference): its exact source-level
	// meaning is not resolved, only its instruction shape.
	void bfmeRangeInsert00381D10(iterator position, iterator first, iterator last, const void *thatAddr);
};

template <class T>
Rva00381DF0List<T>::Rva00381DF0List(const Rva00381DF0List *that)
{
	bfmeRangeInsert00381D10(iterator(this->_M_node->_M_next), iterator(that->_M_node->_M_next), iterator(that->_M_node), &that);
}

// retail 0x00381DF0, a 224-byte node
template class Rva00381DF0List<Rva00381DF0Element>;
