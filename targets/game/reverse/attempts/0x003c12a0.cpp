// ?tail003C12A0@Transfer003C3D90@@QAEXPAVXfer@@@Z
// partial score=0.4808 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// The caller load003C4160 in Load003C4160.cpp passes its Xfer pointer to this
// method. The symbols.csv row at 0x003C12A0 names it tail003C12A0 on
// Transfer003C3D90. This method belongs in Load003C4160.cpp, which declares
// Transfer003C3D90 and calls it.
//
// The list at this+0xC0 has 12-byte elements. The sized-list constructor at
// 0x003C15C0 shows the same wide string and two integer fields, with the last
// field initialized to 3. The virtual declarations in xfer.h map slots 1, 9,
// 25, and 30 to IsLoading, XferRawBytes, operator==(UnicodeString&), and
// operator==(int&).
//
// The trial emits 444 bytes, one more than retail's 443, and differs at 228
// non-relocation bytes. Its frame matches retail's 0x28 bytes, but register
// and stack slot choices still differ.

#include "../../../../game/Libraries/Source/WWVegas/WWLib/string_base.h"
#include "../../../../game/GameEngine/Source/Common/System/xfer.h"
#include <new>

namespace _STL
{

class __new_alloc
{
public:
	static void *allocate(unsigned int bytes);
};

template <class T>
class allocator
{
};

template <class T>
struct _Nonconst_traits
{
};

struct _List_node_base
{
	_List_node_base *_M_next;
	_List_node_base *_M_prev;
};

template <class T>
struct _List_node : public _List_node_base
{
	T _M_data;
};

template <class T, class Traits>
struct _List_iterator
{
	_List_iterator(_List_node_base *node) : _M_node(node) {}
	bool operator!=(const _List_iterator &that) const { return _M_node != that._M_node; }
	_List_iterator &operator++() { _M_node = _M_node->_M_next; return *this; }
	T &operator*() const { return ((_List_node<T> *)_M_node)->_M_data; }
	_List_node_base *_M_node;
};

template <class T, class Alloc>
class _List_base
{
public:
	typedef _List_node<T> _Node;
	_Node *_M_node;
	void clear();
};

template <class T, class Alloc = allocator<T> >
class list : public _List_base<T, Alloc>
{
public:
	typedef _List_node<T> _Node;
	typedef _List_iterator<T, _Nonconst_traits<T> > iterator;

	int size() const
	{
		int count = 0;
		_List_node_base *end = this->_M_node;
		_List_node_base *node = end->_M_next;
		while (node != end)
		{
			node = node->_M_next;
			++count;
		}
		return count;
	}

	iterator begin() { return iterator(this->_M_node->_M_next); }
	iterator end() { return iterator(this->_M_node); }

	iterator insert(iterator position, const T &value)
	{
		_Node *node = _M_create_node(value);
		_List_node_base *at = position._M_node;
		_List_node_base *before = at->_M_prev;
		node->_M_next = at;
		node->_M_prev = before;
		before->_M_next = node;
		at->_M_prev = node;
		return iterator(node);
	}

	void push_back(const T &value)
	{
		insert(iterator(this->_M_node), value);
	}

private:
	__forceinline _Node *_M_create_node(const T &value)
	{
		_Node *node = (_Node *)__new_alloc::allocate(sizeof(_Node));
		new (&node->_M_data) T(value);
		return node;
	}
};

template <class Iterator>
int distance(Iterator first, Iterator last)
{
	int count = 0;
	while (first != last)
	{
		++first;
		++count;
	}
	return count;
}

}

class UnicodeString
{
public:
	UnicodeString() : m_text(0) {}
	UnicodeString(const UnicodeString &that)
	{
		((StringBase<wchar_t> *)this)->StringBase<wchar_t>::StringBase(
			*(const StringBase<wchar_t> *)&that);
	}
	~UnicodeString()
	{
		((StringBase<wchar_t> *)this)->releaseBuffer();
	}

private:
	void *m_text;
};

struct Rva003C12A0Element
{
	UnicodeString m_text;
	int m_word4;
	int m_word8;

	Rva003C12A0Element()
		: m_text()
		, m_word4(0)
		, m_word8(3)
	{
	}

	~Rva003C12A0Element() {}
};

bool operator==(const Rva003C12A0Element &, const Rva003C12A0Element &);
bool operator<(const Rva003C12A0Element &, const Rva003C12A0Element &);

class Transfer003C3D90
{
public:
	void tail003C12A0(Xfer *xfer);

private:
	unsigned char m_unmodelled00[0xC0];
	_STL::list<Rva003C12A0Element> m_list;
};

// ?tail003C12A0@Transfer003C3D90@@QAEXPAVXfer@@@Z
void Transfer003C3D90::tail003C12A0(Xfer *xfer)
{
	int count = _STL::distance(m_list.begin(), m_list.end());
	*xfer == count;
	bool proceed = xfer->IsLoading();

	if (proceed)
	{
		m_list.clear();
		int i;
		i = 0;
		for (; i < count; ++i)
		{
			Rva003C12A0Element tmp;
			*xfer == tmp.m_text;
			*xfer == tmp.m_word4;
			xfer->XferRawBytes(&tmp.m_word8, 4);
			m_list.push_back(tmp);
		}
		return;
	}

	_STL::list<Rva003C12A0Element>::iterator it = m_list.begin();
	_STL::list<Rva003C12A0Element>::iterator end = m_list.end();
	for (; it != end; ++it)
	{
		Rva003C12A0Element tmp2(*it);
		*xfer == tmp2.m_text;
		*xfer == tmp2.m_word4;
		xfer->XferRawBytes(&tmp2.m_word8, 4);
	}
}
