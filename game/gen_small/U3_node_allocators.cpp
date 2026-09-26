// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME-1: four allocation helpers out of d_0005b6c0.asm.
//
// 0x00066920 and 0x00066960 are an allocate/deallocate pair over ONE element
// size: both multiply the count by 0x408 and both split on the same 0x80
// threshold, above it going to the plain operator new / operator delete bodies
// at 0x00881F30 / 0x00881EB0 and below it to the STLport node pool at
// 0x0082E540 / 0x0082E5F0. That split IS STLport's __node_alloc contract --
// _MAX_BYTES is 128 -- so these are the allocator members of a container whose
// element is 1032 bytes. The second parameter of each is dead in the body but
// still cleaned by `ret 8`.
//
// 0x00066D90 is a node factory: allocate a fixed-size 0x408 node,
// copy-construct the payload through an out-of-line helper, zero the link field
// and return the node. Its helper at 0x00066A40
// the ledger already names -- it is the STLport
// _Construct<pair<const NameKeyType, DamageFX> > instantiation -- which fixes
// the container as a map keyed by NameKeyType; the local declaration here is a
// plain two-pointer spelling of it pinned by address, because writing the
// template-id out would need DamageFX complete for no gain.
//
// Identity is otherwise address-derived.

typedef unsigned int UnsignedInt;

namespace _STL
{

class __new_alloc
{
public:
	static void *allocate(UnsignedInt size);
};

template<bool threads, int inst>
class __node_alloc
{
public:
	static void _M_deallocate(void *p, UnsignedInt size);
};

}

extern "C++"
{
	void *BFMENetworkAllocate(UnsignedInt size);
	void Rva00066A40Construct(void *destination, const void *source);
}

void *operator new(UnsignedInt size);
void operator delete(void *p);

// ?Rva00066920Allocate@@YGPAXII@Z
void *__stdcall Rva00066920Allocate(UnsignedInt count, UnsignedInt hint)
{
	if (count != 0)
	{
		UnsignedInt bytes = count * 0x408;

		if (bytes > 0x80)
		{
			return BFMENetworkAllocate(bytes);
		}

		return _STL::__new_alloc::allocate(bytes);
	}

	return 0;
}

// ?Rva00066960Deallocate@@YGXPAXI@Z
void __stdcall Rva00066960Deallocate(void *p, UnsignedInt count)
{
	if (p == 0)
	{
		return;
	}

	UnsignedInt bytes = count * 0x408;

	if (bytes > 0x80)
	{
		operator delete(p);
		return;
	}

	_STL::__node_alloc<true, 0>::_M_deallocate(p, bytes);
}

// ---------------------------------------------------------------------------

struct Rva00066D90Node
{
	Rva00066D90Node *m_next;							///< node+0x00
	unsigned char m_value[0x404];						///< node+0x04
};

// ?Rva00066D90CreateNode@@YGPAURva00066D90Node@@PBX@Z
Rva00066D90Node *__stdcall Rva00066D90CreateNode(const void *value)
{
	Rva00066D90Node *node = (Rva00066D90Node *)BFMENetworkAllocate(0x408);

	node->m_next = 0;
	Rva00066A40Construct(node->m_value, value);

	return node;
}
