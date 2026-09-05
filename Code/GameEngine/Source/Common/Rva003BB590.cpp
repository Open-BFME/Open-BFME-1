// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <vector>
//
// Owner contains vector<20-byte element> at +0x14. Local is constructed by
// the Rva003B9610 ctor (ILT 0x00019B28), AsciiString::set writes the first field, then
// inlined 20-byte push_back. Copy ctor is Rva003B9AD0 (ILT 0x00048923).
// Dtors: rb_tree at +8 (0x00032FD3) then AsciiString releaseBuffer.

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	~StringBase();
	void set(const StringBase<T> &other);
	int *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	~AsciiString() {}
	void set(const AsciiString &other) { StringBase<char>::set(other); }
};


struct Rva003BB590Tree
{
	Rva003BB590Tree();
	~Rva003BB590Tree();
	int m_header;
	int m_count;
	char m_unreconstructed08[4];
};

struct Rva003BB540Element
{
	Rva003BB540Element();
	Rva003BB540Element( const Rva003BB540Element &other );
	AsciiString m_name;
	int m_at04;
	Rva003BB590Tree m_tree;
};

class Rva003BB590
{
public:
	void add( const AsciiString &name );

	char m_pad00[ 0x14 ];
	_STL::vector<Rva003BB540Element, _STL::allocator<Rva003BB540Element> > m_items;
};

void Rva003BB590::add( const AsciiString &name )
{
	Rva003BB540Element tmp;
	tmp.m_name.set(name);
	m_items.push_back(tmp);
}
