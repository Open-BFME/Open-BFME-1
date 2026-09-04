// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x006ABC60 is the non-virtual destructor for an owner containing a
// six-element 12-byte vector, an AsciiString tree, and a trailing helper.
// The member extents are taken from the three destructor calls and the
// eh-vector arguments in the retail body.

class AsciiString
{
};

namespace _STL
{
template <class Type> class allocator
{
};

template <class Type> struct _Identity
{
};

template <class Type> struct less
{
};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree
{
public:
	_Rb_tree();
	~_Rb_tree();

private:
	void *m_header;
	unsigned int m_count;
	char m_pad08[0x0c];
};
}

class Rva006ABC60TrailingMember
{
public:
	~Rva006ABC60TrailingMember();
};

class Rva006ABC60VectorElement
{
public:
	~Rva006ABC60VectorElement();

private:
	char m_body[0x0c];
};

typedef _STL::_Rb_tree<AsciiString, AsciiString, _STL::_Identity<AsciiString>,
	_STL::less<AsciiString>, _STL::allocator<AsciiString> > Rva006ABC60Tree;

class Rva006ABC60
{
public:
	~Rva006ABC60();

private:
	char m_pad4c[0x4c];
	Rva006ABC60VectorElement m_elements[6];
	char m_pad94[0x0c];
	Rva006ABC60Tree m_tree;
	char m_padb4[0x104];
	Rva006ABC60TrailingMember m_trailing;
};

Rva006ABC60::~Rva006ABC60()
{
}
