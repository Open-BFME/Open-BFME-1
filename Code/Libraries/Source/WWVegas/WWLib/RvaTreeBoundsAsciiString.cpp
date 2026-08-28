// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: STLport _Rb_tree<AsciiString, V>::_M_lower_bound and
// _M_upper_bound, 22 bodies of 145 bytes.  All of them carried only a machine
// byte-dump row.  The pair already converted in
// Code/GameEngine/Source/Common/AsciiStringSetBounds.cpp is the same shape.
//
// Each is one descent: lower_bound takes the right child while the node's key
// compares below the sought key and keeps the node otherwise, upper_bound does
// the mirror of that.  There is not a single call in either -- the comparison
// inlines all the way down, which is what makes 145 bytes of it.  The two
// lengths are read as halfwords at +4, a null pointer stands in for the empty
// string at 0x0107388B, `repe cmpsb` runs over the shorter side and the length
// difference breaks the tie: StringBase<char>::compare, spelled out.  That is
// AsciiString, and it is the only thing the bodies name.
//
// There is no allocation here, so the mapped type has no width the bytes can be
// asked for.  Each tree is therefore spelled with its own key-of-value functor
// over a value that begins with the AsciiString -- what the descent proves and
// no more -- and named for the address of its lower_bound.  Three trees own
// both halves: their two bodies sit adjacent in .text, which is what the linker
// does with two members of one instantiation.

#define _STLP_NO_EXCEPTIONS 1
#include <map>

typedef int Int;
typedef bool Bool;

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	int compare(const AsciiString &str) const
	{
		const int len = str.m_data ? str.m_data->length : 0;
		const char *data = str.m_data ? &str.m_data->data[0] : "";
		const int myLen = m_data ? m_data->length : 0;
		const char *myData = m_data ? &m_data->data[0] : "";
		int result = memcmp(myData, data, myLen < len ? myLen : len);
		if (result == 0) {
			result = myLen - len;
		}
		return result;
	}

private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};

	Header *m_data;
};

inline bool operator<(const AsciiString &left, const AsciiString &right)
{
	return left.compare(right) < 0;
}

struct Rva00062FC0Value
{
	AsciiString m_key;
};

struct Rva00062FC0KeyOfValue
{
	const AsciiString &operator()( const Rva00062FC0Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva00062FC0Value, Rva00062FC0KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva00062FC0Value> > Rva00062FC0Tree;

// lower_bound and upper_bound are public; the _M_ helpers they call are not,
// so reaching them through the public pair is what emits them.
Bool BfmeTreeBoundsAnchor00062FC0( const Rva00062FC0Tree &tree, const AsciiString &key )
{
	return tree.lower_bound( key ) != tree.upper_bound( key );
}

struct Rva0007D780Value
{
	AsciiString m_key;
};

struct Rva0007D780KeyOfValue
{
	const AsciiString &operator()( const Rva0007D780Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva0007D780Value, Rva0007D780KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva0007D780Value> > Rva0007D780Tree;

// lower_bound and upper_bound are public; the _M_ helpers they call are not,
// so reaching them through the public pair is what emits them.
Bool BfmeTreeBoundsAnchor0007D780( const Rva0007D780Tree &tree, const AsciiString &key )
{
	return tree.lower_bound( key ) != tree.upper_bound( key );
}

struct Rva00080410Value
{
	AsciiString m_key;
};

struct Rva00080410KeyOfValue
{
	const AsciiString &operator()( const Rva00080410Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva00080410Value, Rva00080410KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva00080410Value> > Rva00080410Tree;

// lower_bound and upper_bound are public; the _M_ helpers they call are not,
// so reaching them through the public pair is what emits them.
Bool BfmeTreeBoundsAnchor00080410( const Rva00080410Tree &tree, const AsciiString &key )
{
	return tree.lower_bound( key ) != tree.upper_bound( key );
}

struct Rva000BF610Value
{
	AsciiString m_key;
};

struct Rva000BF610KeyOfValue
{
	const AsciiString &operator()( const Rva000BF610Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva000BF610Value, Rva000BF610KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva000BF610Value> > Rva000BF610Tree;

// lower_bound and upper_bound are public; the _M_ helpers they call are not,
// so reaching them through the public pair is what emits them.
Bool BfmeTreeBoundsAnchor000BF610( const Rva000BF610Tree &tree, const AsciiString &key )
{
	return tree.lower_bound( key ) != tree.upper_bound( key );
}

struct Rva000BF6D0Value
{
	AsciiString m_key;
};

struct Rva000BF6D0KeyOfValue
{
	const AsciiString &operator()( const Rva000BF6D0Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva000BF6D0Value, Rva000BF6D0KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva000BF6D0Value> > Rva000BF6D0Tree;

// lower_bound and upper_bound are public; the _M_ helpers they call are not,
// so reaching them through the public pair is what emits them.
Bool BfmeTreeBoundsAnchor000BF6D0( const Rva000BF6D0Tree &tree, const AsciiString &key )
{
	return tree.lower_bound( key ) != tree.upper_bound( key );
}

struct Rva0033F2E0Value
{
	AsciiString m_key;
};

struct Rva0033F2E0KeyOfValue
{
	const AsciiString &operator()( const Rva0033F2E0Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva0033F2E0Value, Rva0033F2E0KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva0033F2E0Value> > Rva0033F2E0Tree;

// lower_bound and upper_bound are public; the _M_ helpers they call are not,
// so reaching them through the public pair is what emits them.
Bool BfmeTreeBoundsAnchor0033F2E0( const Rva0033F2E0Tree &tree, const AsciiString &key )
{
	return tree.lower_bound( key ) != tree.upper_bound( key );
}

struct Rva003B9A10Value
{
	AsciiString m_key;
};

struct Rva003B9A10KeyOfValue
{
	const AsciiString &operator()( const Rva003B9A10Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva003B9A10Value, Rva003B9A10KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva003B9A10Value> > Rva003B9A10Tree;

// lower_bound and upper_bound are public; the _M_ helpers they call are not,
// so reaching them through the public pair is what emits them.
Bool BfmeTreeBoundsAnchor003B9A10( const Rva003B9A10Tree &tree, const AsciiString &key )
{
	return tree.lower_bound( key ) != tree.upper_bound( key );
}

struct Rva00448AD0Value
{
	AsciiString m_key;
};

struct Rva00448AD0KeyOfValue
{
	const AsciiString &operator()( const Rva00448AD0Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva00448AD0Value, Rva00448AD0KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva00448AD0Value> > Rva00448AD0Tree;

// lower_bound and upper_bound are public; the _M_ helpers they call are not,
// so reaching them through the public pair is what emits them.
Bool BfmeTreeBoundsAnchor00448AD0( const Rva00448AD0Tree &tree, const AsciiString &key )
{
	return tree.lower_bound( key ) != tree.upper_bound( key );
}

struct Rva00448B90Value
{
	AsciiString m_key;
};

struct Rva00448B90KeyOfValue
{
	const AsciiString &operator()( const Rva00448B90Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva00448B90Value, Rva00448B90KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva00448B90Value> > Rva00448B90Tree;

// lower_bound and upper_bound are public; the _M_ helpers they call are not,
// so reaching them through the public pair is what emits them.
Bool BfmeTreeBoundsAnchor00448B90( const Rva00448B90Tree &tree, const AsciiString &key )
{
	return tree.lower_bound( key ) != tree.upper_bound( key );
}

struct Rva00452E60Value
{
	AsciiString m_key;
};

struct Rva00452E60KeyOfValue
{
	const AsciiString &operator()( const Rva00452E60Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva00452E60Value, Rva00452E60KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva00452E60Value> > Rva00452E60Tree;

// lower_bound and upper_bound are public; the _M_ helpers they call are not,
// so reaching them through the public pair is what emits them.
Bool BfmeTreeBoundsAnchor00452E60( const Rva00452E60Tree &tree, const AsciiString &key )
{
	return tree.lower_bound( key ) != tree.upper_bound( key );
}

struct Rva00460F80Value
{
	AsciiString m_key;
};

struct Rva00460F80KeyOfValue
{
	const AsciiString &operator()( const Rva00460F80Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva00460F80Value, Rva00460F80KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva00460F80Value> > Rva00460F80Tree;

// lower_bound and upper_bound are public; the _M_ helpers they call are not,
// so reaching them through the public pair is what emits them.
Bool BfmeTreeBoundsAnchor00460F80( const Rva00460F80Tree &tree, const AsciiString &key )
{
	return tree.lower_bound( key ) != tree.upper_bound( key );
}

struct Rva00474C10Value
{
	AsciiString m_key;
};

struct Rva00474C10KeyOfValue
{
	const AsciiString &operator()( const Rva00474C10Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva00474C10Value, Rva00474C10KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva00474C10Value> > Rva00474C10Tree;

// lower_bound and upper_bound are public; the _M_ helpers they call are not,
// so reaching them through the public pair is what emits them.
Bool BfmeTreeBoundsAnchor00474C10( const Rva00474C10Tree &tree, const AsciiString &key )
{
	return tree.lower_bound( key ) != tree.upper_bound( key );
}

struct Rva00474CD0Value
{
	AsciiString m_key;
};

struct Rva00474CD0KeyOfValue
{
	const AsciiString &operator()( const Rva00474CD0Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva00474CD0Value, Rva00474CD0KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva00474CD0Value> > Rva00474CD0Tree;

// lower_bound and upper_bound are public; the _M_ helpers they call are not,
// so reaching them through the public pair is what emits them.
Bool BfmeTreeBoundsAnchor00474CD0( const Rva00474CD0Tree &tree, const AsciiString &key )
{
	return tree.lower_bound( key ) != tree.upper_bound( key );
}

struct Rva005B2E30Value
{
	AsciiString m_key;
};

struct Rva005B2E30KeyOfValue
{
	const AsciiString &operator()( const Rva005B2E30Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva005B2E30Value, Rva005B2E30KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva005B2E30Value> > Rva005B2E30Tree;

// lower_bound and upper_bound are public; the _M_ helpers they call are not,
// so reaching them through the public pair is what emits them.
Bool BfmeTreeBoundsAnchor005B2E30( const Rva005B2E30Tree &tree, const AsciiString &key )
{
	return tree.lower_bound( key ) != tree.upper_bound( key );
}

struct Rva006A7740Value
{
	AsciiString m_key;
};

struct Rva006A7740KeyOfValue
{
	const AsciiString &operator()( const Rva006A7740Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva006A7740Value, Rva006A7740KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva006A7740Value> > Rva006A7740Tree;

// lower_bound and upper_bound are public; the _M_ helpers they call are not,
// so reaching them through the public pair is what emits them.
Bool BfmeTreeBoundsAnchor006A7740( const Rva006A7740Tree &tree, const AsciiString &key )
{
	return tree.lower_bound( key ) != tree.upper_bound( key );
}

struct Rva009C9CE0Value
{
	AsciiString m_key;
};

struct Rva009C9CE0KeyOfValue
{
	const AsciiString &operator()( const Rva009C9CE0Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva009C9CE0Value, Rva009C9CE0KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva009C9CE0Value> > Rva009C9CE0Tree;

// lower_bound and upper_bound are public; the _M_ helpers they call are not,
// so reaching them through the public pair is what emits them.
Bool BfmeTreeBoundsAnchor009C9CE0( const Rva009C9CE0Tree &tree, const AsciiString &key )
{
	return tree.lower_bound( key ) != tree.upper_bound( key );
}

struct Rva009CFBE0Value
{
	AsciiString m_key;
};

struct Rva009CFBE0KeyOfValue
{
	const AsciiString &operator()( const Rva009CFBE0Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva009CFBE0Value, Rva009CFBE0KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva009CFBE0Value> > Rva009CFBE0Tree;

// lower_bound and upper_bound are public; the _M_ helpers they call are not,
// so reaching them through the public pair is what emits them.
Bool BfmeTreeBoundsAnchor009CFBE0( const Rva009CFBE0Tree &tree, const AsciiString &key )
{
	return tree.lower_bound( key ) != tree.upper_bound( key );
}

struct Rva009CFC80Value
{
	AsciiString m_key;
};

struct Rva009CFC80KeyOfValue
{
	const AsciiString &operator()( const Rva009CFC80Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva009CFC80Value, Rva009CFC80KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva009CFC80Value> > Rva009CFC80Tree;

// lower_bound and upper_bound are public; the _M_ helpers they call are not,
// so reaching them through the public pair is what emits them.
Bool BfmeTreeBoundsAnchor009CFC80( const Rva009CFC80Tree &tree, const AsciiString &key )
{
	return tree.lower_bound( key ) != tree.upper_bound( key );
}

struct Rva006339C0Value
{
	AsciiString m_key;
};

struct Rva006339C0KeyOfValue
{
	const AsciiString &operator()( const Rva006339C0Value &x ) const { return x.m_key; }
};

typedef _STL::_Rb_tree<AsciiString, Rva006339C0Value, Rva006339C0KeyOfValue,
	_STL::less<AsciiString>, _STL::allocator<Rva006339C0Value> > Rva006339C0Tree;

// lower_bound and upper_bound are public; the _M_ helpers they call are not,
// so reaching them through the public pair is what emits them.
Bool BfmeTreeBoundsAnchor006339C0( const Rva006339C0Tree &tree, const AsciiString &key )
{
	return tree.lower_bound( key ) != tree.upper_bound( key );
}

