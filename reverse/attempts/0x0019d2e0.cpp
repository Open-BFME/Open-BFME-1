// ??0BfmeTmpACH@@QAE@PAX@Z
// partial score=0.82 date=2026-09-19
// cl: /EHsc

namespace _STL
{
class __new_alloc
{
public:
	static void *__cdecl allocate(unsigned int size);
};

struct _Rb_tree_node_base
{
	int m_color;
	_Rb_tree_node_base *m_parent;
	_Rb_tree_node_base *m_left;
	_Rb_tree_node_base *m_right;
};

template <class First, class Second>
struct pair
{
	First first;
	Second second;
};

template <class Value>
struct _Nonconst_traits
{
};

template <bool Threaded>
class _Rb_global
{
public:
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *node);
};

template <class Value, class Traits>
struct _Rb_tree_iterator
{
	_Rb_tree_node_base *m_node;

	_Rb_tree_iterator(_Rb_tree_node_base *node = 0) : m_node(node) {}

	Value &operator*() const
	{
		return *(Value *)((char *)m_node + 0x10);
	}

	_Rb_tree_iterator &operator++()
	{
		m_node = _Rb_global<false>::_M_increment(m_node);
		return *this;
	}
};
}

struct Rva0019BC70Key
{
	unsigned char m_data[8];
};

struct Rva0019BC70Value
{
	unsigned char m_data[4];
};

typedef _STL::pair<const Rva0019BC70Key, Rva0019BC70Value>
	Rva0019BC70Pair;

class Rva0019BC70Tree
{
public:
	typedef _STL::_Rb_tree_iterator<Rva0019BC70Pair,
		_STL::_Nonconst_traits<Rva0019BC70Pair> > iterator;

	struct Header
	{
		unsigned char m_color;
		unsigned char m_padding[3];
		_STL::_Rb_tree_node_base *m_parent;
		_STL::_Rb_tree_node_base *m_left;
		_STL::_Rb_tree_node_base *m_right;
	};

	Rva0019BC70Tree() throw();
	iterator insert_unique(iterator position, const Rva0019BC70Pair &value);

	Header *m_header;
	int m_count;
	int m_allocator;
};

Rva0019BC70Tree::Rva0019BC70Tree() throw()
	: m_header(0), m_count(0)
{
	m_header = (Header *)_STL::__new_alloc::allocate(0x1c);
	m_header->m_color = 0;
	m_header->m_parent = 0;
	m_header->m_left = (_STL::_Rb_tree_node_base *)m_header;
	m_header->m_right = (_STL::_Rb_tree_node_base *)m_header;
}

struct BfmeRefRecord
{
	short m_word0;
	short m_word2;
	short m_word4;
	short m_word6;
	int m_word8;
	short *m_reference;
};

class BfmeRefRecordVector
{
public:
	BfmeRefRecordVector(const BfmeRefRecordVector &source);

	BfmeRefRecord *m_begin;
	BfmeRefRecord *m_end;
	int m_allocator;
};

class BfmeBaseCH
{
public:
	~BfmeBaseCH();

	Rva0019BC70Tree m_bfmeHeadCH;
};

class BfmeMemCH
{
public:
	BfmeMemCH(const void *source)
		: m_vector(*(BfmeRefRecordVector *)((char *)source + 0xc)),
		  m_word18(*(short *)((char *)source + 0x18)),
		  m_word1a(*(short *)((char *)source + 0x1a))
	{
	}

	~BfmeMemCH();

	BfmeRefRecordVector m_vector;
	short m_word18;
	short m_word1a;
};

class BfmeTmpACH : public BfmeBaseCH
{
public:
	BfmeTmpACH(void *value);
	~BfmeTmpACH() {}

	BfmeMemCH m_bfmeMemCH;
};

struct BfmeInputCH
{
	Rva0019BC70Tree m_bfmeHeadCH;
	BfmeMemCH m_bfmeMemCH;
};

BfmeTmpACH::BfmeTmpACH(void *value)
	: BfmeBaseCH(),
	  m_bfmeMemCH(value)
{
	const BfmeInputCH *source;
	source = (const BfmeInputCH *)value;
	Rva0019BC70Tree::iterator current(source->m_bfmeHeadCH.m_header->m_left);
	volatile Rva0019BC70Tree::iterator end(
		(_STL::_Rb_tree_node_base *)source->m_bfmeHeadCH.m_header);
	while (current.m_node != end.m_node)
	{
		Rva0019BC70Tree::iterator hint(m_bfmeHeadCH.m_header->m_left);
		Rva0019BC70Tree::iterator inserted =
			m_bfmeHeadCH.insert_unique(hint, *current);
		Rva0019BC70Pair *valueCopy =
			(Rva0019BC70Pair *)((char *)inserted.m_node + 0x10);
		if (valueCopy->second.m_data[0] != 0)
		{
			BfmeRefRecord *record;
			do
			{
				record = m_bfmeMemCH.m_vector.m_begin +
					valueCopy->second.m_data[0];
				record->m_word8 = (int)inserted.m_node;
			} while (record->m_word4 != 0);
		}
		++current;
	}
}
