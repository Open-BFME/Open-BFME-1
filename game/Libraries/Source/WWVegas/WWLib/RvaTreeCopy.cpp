// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: STLport _Rb_tree<K,V>::_M_copy, 15 bodies of 171 bytes.  Every
// one carried only a machine byte-dump row; the same shape is already converted
// at 0x000AAC70 and 0x005671E0.
//
// _M_copy rebuilds a subtree: clone the node it is given, recurse down the
// right spine iteratively and the left recursively, and hand back the root of
// the copy.  The node is 0x18 bytes -- sixteen of header and eight of value --
// and each clone's value goes through an out-of-line _Construct, pinned here
// from the body's own displacement.  So the key and the mapped type are four
// bytes each; what the mapped type IS the copy never reveals.
//
// Nothing here compares, so nothing here says whether the key is signed; it is
// spelled Int because that is the narrower claim of the two and the bytes are
// the same either way.  The mapped type is a four-byte POD named for the
// address of the body.
//
// Seven more landed later at other node sizes -- 0x1c, 0x20, 0x24 twice, 0x2c
// and 0x30 twice.  Node minus sixteen is the value and node minus twenty the
// mapped type.  One further body, 0x000BF790, allocates 0x14: four bytes of
// value leave no room for a pair, so its tree is a set -- but a set spelled
// here does not reproduce it, and it is left as a dump rather than forced.

#define _STLP_NO_EXCEPTIONS 1
#include <map>

typedef int Int;

struct Rva000A3E50Value
{
	int m_body;
};

typedef _STL::map<Int, Rva000A3E50Value> Rva000A3E50Map;

// retail 0x000A3E50
void BfmeTreeCopyAnchor000A3E50( Rva000A3E50Map &out, const Rva000A3E50Map &in )
{
	out = in;
}

struct Rva000D3810Value
{
	int m_body;
};

typedef _STL::map<Int, Rva000D3810Value> Rva000D3810Map;

// retail 0x000D3810
void BfmeTreeCopyAnchor000D3810( Rva000D3810Map &out, const Rva000D3810Map &in )
{
	out = in;
}

struct Rva000D3B00Value
{
	int m_body;
};

typedef _STL::map<Int, Rva000D3B00Value> Rva000D3B00Map;

// retail 0x000D3B00
void BfmeTreeCopyAnchor000D3B00( Rva000D3B00Map &out, const Rva000D3B00Map &in )
{
	out = in;
}

struct Rva001363B0Value
{
	int m_body;
};

typedef _STL::map<Int, Rva001363B0Value> Rva001363B0Map;

// retail 0x001363B0
void BfmeTreeCopyAnchor001363B0( Rva001363B0Map &out, const Rva001363B0Map &in )
{
	out = in;
}

struct Rva00136490Value
{
	int m_body;
};

typedef _STL::map<Int, Rva00136490Value> Rva00136490Map;

// retail 0x00136490
void BfmeTreeCopyAnchor00136490( Rva00136490Map &out, const Rva00136490Map &in )
{
	out = in;
}

struct Rva001365C0Value
{
	int m_body;
};

typedef _STL::map<Int, Rva001365C0Value> Rva001365C0Map;

// retail 0x001365C0
void BfmeTreeCopyAnchor001365C0( Rva001365C0Map &out, const Rva001365C0Map &in )
{
	out = in;
}

struct Rva001374C0Value
{
	int m_body;
};

typedef _STL::map<Int, Rva001374C0Value> Rva001374C0Map;

// retail 0x001374C0
void BfmeTreeCopyAnchor001374C0( Rva001374C0Map &out, const Rva001374C0Map &in )
{
	out = in;
}

struct Rva00424610Value
{
	int m_body;
};

typedef _STL::map<Int, Rva00424610Value> Rva00424610Map;

// retail 0x00424610
void BfmeTreeCopyAnchor00424610( Rva00424610Map &out, const Rva00424610Map &in )
{
	out = in;
}

struct Rva00064B10Value
{
	char m_body[ 24 ];
};

typedef _STL::map<Int, Rva00064B10Value> Rva00064B10Map;

// retail 0x00064B10, a 0x2c-byte node
void BfmeTreeCopyAnchor00064B10( Rva00064B10Map &out, const Rva00064B10Map &in )
{
	out = in;
}

struct Rva000F1D00Value
{
	char m_body[ 8 ];
};

typedef _STL::map<Int, Rva000F1D00Value> Rva000F1D00Map;

// retail 0x000F1D00, a 0x1c-byte node
void BfmeTreeCopyAnchor000F1D00( Rva000F1D00Map &out, const Rva000F1D00Map &in )
{
	out = in;
}

struct Rva00138720Value
{
	char m_body[ 12 ];
};

typedef _STL::map<Int, Rva00138720Value> Rva00138720Map;

// retail 0x00138720, a 0x20-byte node
void BfmeTreeCopyAnchor00138720( Rva00138720Map &out, const Rva00138720Map &in )
{
	out = in;
}

struct Rva004D56E0Value
{
	char m_body[ 16 ];
};

typedef _STL::map<Int, Rva004D56E0Value> Rva004D56E0Map;

// retail 0x004D56E0, a 0x24-byte node
void BfmeTreeCopyAnchor004D56E0( Rva004D56E0Map &out, const Rva004D56E0Map &in )
{
	out = in;
}

struct Rva009C9650Value
{
	char m_body[ 28 ];
};

typedef _STL::map<Int, Rva009C9650Value> Rva009C9650Map;

// retail 0x009C9650, a 0x30-byte node
void BfmeTreeCopyAnchor009C9650( Rva009C9650Map &out, const Rva009C9650Map &in )
{
	out = in;
}

struct Rva009CF2C0Value
{
	char m_body[ 28 ];
};

typedef _STL::map<Int, Rva009CF2C0Value> Rva009CF2C0Map;

// retail 0x009CF2C0, a 0x30-byte node
void BfmeTreeCopyAnchor009CF2C0( Rva009CF2C0Map &out, const Rva009CF2C0Map &in )
{
	out = in;
}

struct Rva009D0680Value
{
	char m_body[ 16 ];
};

typedef _STL::map<Int, Rva009D0680Value> Rva009D0680Map;

// retail 0x009D0680, a 0x24-byte node
void BfmeTreeCopyAnchor009D0680( Rva009D0680Map &out, const Rva009D0680Map &in )
{
	out = in;
}

