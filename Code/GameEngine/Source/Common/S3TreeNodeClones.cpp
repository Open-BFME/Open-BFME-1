// Ten 50-byte bodies with one shape: allocate 0x18 bytes, copy-construct the
// value at +0x10 out of the argument's own +0x10, zero +0x08 and +0x0C, and
// copy the byte at +0x00. Then return the block.
//
// That is a red-black tree node cloned: colour at +0x00, parent at +0x04, left
// at +0x08, right at +0x0C, value at +0x10, and 0x18 total for an eight-byte
// value. Zeroing only left and right while copying the colour and taking the
// value from the SOURCE NODE rather than from a bare value is what makes it a
// clone rather than a create.
//
// The allocator is the shared __node_alloc body, whose public spelling in the
// ledger is __new_alloc::allocate. Each _Construct is a distinct template
// instantiation and its decorated name gives the value type away -- seven
// pairs keyed by int and three by AsciiString, each with its own four-byte
// mapped struct.
//
// The colour assignment has to come FIRST in the source even though its store
// lands last in the output -- MSVC hoists the read above the two zero stores
// and sinks the store below them. Written last, the read stays put and the
// body is a byte-for-byte permutation away.
//
// ecx is never touched, so these are written __stdcall; a member that ignores
// this would produce the same bytes and the image cannot separate the two.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
	char m_bfmeBody[0x04];
};

namespace _STL
{

class __new_alloc
{
public:
	static void *allocate(unsigned int size);			// retail 0x0082E540
};

template <class T1, class T2> struct pair
{
	T1 first;
	T2 second;
};

template <class T1, class T2> void _Construct(T1 *destination, const T2 &source);

}

struct Rva000A3F30Value
{
	int m_bfmeValue;
};

typedef _STL::pair<const int, Rva000A3F30Value> Gen_000a3bc0Value;

struct Gen_000a3bc0Node
{
	char m_bfmeColour;						// +0x00
	char m_bfmePad[3];
	void *m_bfmeParent;						// +0x04
	void *m_bfmeLeft;						// +0x08
	void *m_bfmeRight;						// +0x0C
	Gen_000a3bc0Value m_bfmeValue;					// +0x10
};

typedef _STL::pair<const int, unsigned int> Gen_000aaaf0Value;

struct Gen_000aaaf0Node
{
	char m_bfmeColour;						// +0x00
	char m_bfmePad[3];
	void *m_bfmeParent;						// +0x04
	void *m_bfmeLeft;						// +0x08
	void *m_bfmeRight;						// +0x0C
	Gen_000aaaf0Value m_bfmeValue;					// +0x10
};

struct Rva000E1970Value
{
	int m_bfmeValue;
};

typedef _STL::pair<const int, Rva000E1970Value> Gen_000d15f0Value;

struct Gen_000d15f0Node
{
	char m_bfmeColour;						// +0x00
	char m_bfmePad[3];
	void *m_bfmeParent;						// +0x04
	void *m_bfmeLeft;						// +0x08
	void *m_bfmeRight;						// +0x0C
	Gen_000d15f0Value m_bfmeValue;					// +0x10
};

struct Rva000E1B10Value
{
	int m_bfmeValue;
};

typedef _STL::pair<const int, Rva000E1B10Value> Gen_000d1640Value;

struct Gen_000d1640Node
{
	char m_bfmeColour;						// +0x00
	char m_bfmePad[3];
	void *m_bfmeParent;						// +0x04
	void *m_bfmeLeft;						// +0x08
	void *m_bfmeRight;						// +0x0C
	Gen_000d1640Value m_bfmeValue;					// +0x10
};

struct Rva001363B0Value
{
	int m_bfmeValue;
};

typedef _STL::pair<const int, Rva001363B0Value> Gen_001358a0Value;

struct Gen_001358a0Node
{
	char m_bfmeColour;						// +0x00
	char m_bfmePad[3];
	void *m_bfmeParent;						// +0x04
	void *m_bfmeLeft;						// +0x08
	void *m_bfmeRight;						// +0x0C
	Gen_001358a0Value m_bfmeValue;					// +0x10
};

struct Rva00136490Value
{
	int m_bfmeValue;
};

typedef _STL::pair<const int, Rva00136490Value> Gen_001358e0Value;

struct Gen_001358e0Node
{
	char m_bfmeColour;						// +0x00
	char m_bfmePad[3];
	void *m_bfmeParent;						// +0x04
	void *m_bfmeLeft;						// +0x08
	void *m_bfmeRight;						// +0x0C
	Gen_001358e0Value m_bfmeValue;					// +0x10
};

struct Rva00140DE0Value
{
	int m_bfmeValue;
};

typedef _STL::pair<const int, Rva00140DE0Value> Gen_00135920Value;

struct Gen_00135920Node
{
	char m_bfmeColour;						// +0x00
	char m_bfmePad[3];
	void *m_bfmeParent;						// +0x04
	void *m_bfmeLeft;						// +0x08
	void *m_bfmeRight;						// +0x0C
	Gen_00135920Value m_bfmeValue;					// +0x10
};

struct Rva00142EE0Value
{
	int m_bfmeValue;
};

typedef _STL::pair<const AsciiString, Rva00142EE0Value> Gen_001367c0Value;

struct Gen_001367c0Node
{
	char m_bfmeColour;						// +0x00
	char m_bfmePad[3];
	void *m_bfmeParent;						// +0x04
	void *m_bfmeLeft;						// +0x08
	void *m_bfmeRight;						// +0x0C
	Gen_001367c0Value m_bfmeValue;					// +0x10
};

struct Rva00424520Value
{
	int m_bfmeValue;
};

typedef _STL::pair<const AsciiString, Rva00424520Value> Gen_00424070Value;

struct Gen_00424070Node
{
	char m_bfmeColour;						// +0x00
	char m_bfmePad[3];
	void *m_bfmeParent;						// +0x04
	void *m_bfmeLeft;						// +0x08
	void *m_bfmeRight;						// +0x0C
	Gen_00424070Value m_bfmeValue;					// +0x10
};

struct Rva0007D900Value
{
	int m_bfmeValue;
};

typedef _STL::pair<const AsciiString, Rva0007D900Value> Gen_005671a0Value;

struct Gen_005671a0Node
{
	char m_bfmeColour;						// +0x00
	char m_bfmePad[3];
	void *m_bfmeParent;						// +0x04
	void *m_bfmeLeft;						// +0x08
	void *m_bfmeRight;						// +0x0C
	Gen_005671a0Value m_bfmeValue;					// +0x10
};

Gen_000a3bc0Node *__stdcall Gen_000a3bc0(const Gen_000a3bc0Node *source)
{
	Gen_000a3bc0Node *node = (Gen_000a3bc0Node *)_STL::__new_alloc::allocate(0x18);

	_STL::_Construct(&node->m_bfmeValue, source->m_bfmeValue);

	node->m_bfmeColour = source->m_bfmeColour;
	node->m_bfmeLeft = 0;
	node->m_bfmeRight = 0;

	return node;
}

Gen_000aaaf0Node *__stdcall Gen_000aaaf0(const Gen_000aaaf0Node *source)
{
	Gen_000aaaf0Node *node = (Gen_000aaaf0Node *)_STL::__new_alloc::allocate(0x18);

	_STL::_Construct(&node->m_bfmeValue, source->m_bfmeValue);

	node->m_bfmeColour = source->m_bfmeColour;
	node->m_bfmeLeft = 0;
	node->m_bfmeRight = 0;

	return node;
}

Gen_000d15f0Node *__stdcall Gen_000d15f0(const Gen_000d15f0Node *source)
{
	Gen_000d15f0Node *node = (Gen_000d15f0Node *)_STL::__new_alloc::allocate(0x18);

	_STL::_Construct(&node->m_bfmeValue, source->m_bfmeValue);

	node->m_bfmeColour = source->m_bfmeColour;
	node->m_bfmeLeft = 0;
	node->m_bfmeRight = 0;

	return node;
}

Gen_000d1640Node *__stdcall Gen_000d1640(const Gen_000d1640Node *source)
{
	Gen_000d1640Node *node = (Gen_000d1640Node *)_STL::__new_alloc::allocate(0x18);

	_STL::_Construct(&node->m_bfmeValue, source->m_bfmeValue);

	node->m_bfmeColour = source->m_bfmeColour;
	node->m_bfmeLeft = 0;
	node->m_bfmeRight = 0;

	return node;
}

Gen_001358a0Node *__stdcall Gen_001358a0(const Gen_001358a0Node *source)
{
	Gen_001358a0Node *node = (Gen_001358a0Node *)_STL::__new_alloc::allocate(0x18);

	_STL::_Construct(&node->m_bfmeValue, source->m_bfmeValue);

	node->m_bfmeColour = source->m_bfmeColour;
	node->m_bfmeLeft = 0;
	node->m_bfmeRight = 0;

	return node;
}

Gen_001358e0Node *__stdcall Gen_001358e0(const Gen_001358e0Node *source)
{
	Gen_001358e0Node *node = (Gen_001358e0Node *)_STL::__new_alloc::allocate(0x18);

	_STL::_Construct(&node->m_bfmeValue, source->m_bfmeValue);

	node->m_bfmeColour = source->m_bfmeColour;
	node->m_bfmeLeft = 0;
	node->m_bfmeRight = 0;

	return node;
}

Gen_00135920Node *__stdcall Gen_00135920(const Gen_00135920Node *source)
{
	Gen_00135920Node *node = (Gen_00135920Node *)_STL::__new_alloc::allocate(0x18);

	_STL::_Construct(&node->m_bfmeValue, source->m_bfmeValue);

	node->m_bfmeColour = source->m_bfmeColour;
	node->m_bfmeLeft = 0;
	node->m_bfmeRight = 0;

	return node;
}

Gen_001367c0Node *__stdcall Gen_001367c0(const Gen_001367c0Node *source)
{
	Gen_001367c0Node *node = (Gen_001367c0Node *)_STL::__new_alloc::allocate(0x18);

	_STL::_Construct(&node->m_bfmeValue, source->m_bfmeValue);

	node->m_bfmeColour = source->m_bfmeColour;
	node->m_bfmeLeft = 0;
	node->m_bfmeRight = 0;

	return node;
}

Gen_00424070Node *__stdcall Gen_00424070(const Gen_00424070Node *source)
{
	Gen_00424070Node *node = (Gen_00424070Node *)_STL::__new_alloc::allocate(0x18);

	_STL::_Construct(&node->m_bfmeValue, source->m_bfmeValue);

	node->m_bfmeColour = source->m_bfmeColour;
	node->m_bfmeLeft = 0;
	node->m_bfmeRight = 0;

	return node;
}

Gen_005671a0Node *__stdcall Gen_005671a0(const Gen_005671a0Node *source)
{
	Gen_005671a0Node *node = (Gen_005671a0Node *)_STL::__new_alloc::allocate(0x18);

	_STL::_Construct(&node->m_bfmeValue, source->m_bfmeValue);

	node->m_bfmeColour = source->m_bfmeColour;
	node->m_bfmeLeft = 0;
	node->m_bfmeRight = 0;

	return node;
}
