// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME-1: the three red-black-tree lookups out of d_0005b6c0.asm, plus a
// small struct copy. Not one byte of any of them is a relocation.
//
// 0x00064770 and 0x000648B0 are the same walk twice: start at the header, take
// the root from header+4, and descend keeping the last node whose key did NOT
// compare less than the sought key -- `cmp [node+0x28],key / jb right`, then
// left at node+8 and right at node+0x0C. That is lower_bound, and the node
// layout it fixes is the STLport _Rb_tree_node one: colour at +0, parent at +4,
// left at +8, right at +0x0C, value at +0x10, with the key 0x18 into the value
// at +0x28. The comparison is UNSIGNED (jb, and sbb/neg in the sibling), so the
// key is an unsigned quantity, not an int.
//
// The two differ only in how they hand the answer back: 0x00064770 returns the
// node pointer in eax, 0x000648B0 writes it through a hidden return pointer and
// cleans eight bytes, which is what a one-word iterator WITH a constructor
// looks like -- a plain 4-byte POD would come back in eax like the first one.
//
// 0x00064850 is the emptiness-and-front test built on the same object: the
// count at +4 short-circuits to true and otherwise the leftmost node
// (header+8) supplies the key to compare against.
//
// Identity is address-derived; nothing in the image names them and the
// instantiation's value type is not recoverable from these bodies.

typedef int Int;
typedef unsigned int UnsignedInt;

struct Rva00064770Key
{
	unsigned char m_unreconstructed_00[0x18];
	UnsignedInt m_key;									///< key+0x18
};

struct Rva00064770Node
{
	Int m_colour;										///< node+0x00
	Rva00064770Node *m_parent;							///< node+0x04
	Rva00064770Node *m_left;							///< node+0x08
	Rva00064770Node *m_right;							///< node+0x0C
	unsigned char m_unreconstructed_10[0x18];
	UnsignedInt m_key;									///< node+0x28
};

struct Rva000648B0Iterator
{
	Rva000648B0Iterator(void) {}
	Rva000648B0Iterator(Rva00064770Node *node) : m_node(node) {}

	Rva00064770Node *m_node;
};

class Rva00064770Tree
{
public:
	Rva00064770Node *lowerBoundNode(const Rva00064770Key *key) const;
	Rva000648B0Iterator lowerBound(const Rva00064770Key *key) const;
	bool isBefore(UnsignedInt key) const;

private:
	Rva00064770Node *m_header;							///< retail this+0x00
	Int m_count;										///< retail this+0x04
};

// ?lowerBoundNode@Rva00064770Tree@@QBEPAURva00064770Node@@PBURva00064770Key@@@Z
Rva00064770Node *Rva00064770Tree::lowerBoundNode(const Rva00064770Key *key) const
{
	Rva00064770Node *result = m_header;
	Rva00064770Node *node = m_header->m_parent;

	while (node != 0)
	{
		if (!(node->m_key < key->m_key))
		{
			result = node;
			node = node->m_left;
		}
		else
		{
			node = node->m_right;
		}
	}

	return result;
}

// ?lowerBound@Rva00064770Tree@@QBE?AURva000648B0Iterator@@PBURva00064770Key@@@Z
Rva000648B0Iterator Rva00064770Tree::lowerBound(const Rva00064770Key *key) const
{
	Rva00064770Node *result = m_header;
	Rva00064770Node *node = m_header->m_parent;

	while (node != 0)
	{
		if (!(node->m_key < key->m_key))
		{
			result = node;
			node = node->m_left;
		}
		else
		{
			node = node->m_right;
		}
	}

	return Rva000648B0Iterator(result);
}

// ?isBefore@Rva00064770Tree@@QBE_NI@Z
bool Rva00064770Tree::isBefore(UnsignedInt key) const
{
	if (m_count == 0)
	{
		return true;
	}

	return key < m_header->m_left->m_key;
}

// ---------------------------------------------------------------------------

struct Rva00069940Vector
{
	Int m_x;
	Int m_y;
	Int m_z;
};

struct Rva00069940Value
{
	Int m_kind;											///< value+0x00
	Rva00069940Vector m_vector;							///< value+0x04
};

// ?Rva00069940Assign@@YAPAURva00069940Value@@PAU1@PBU1@PBURva00069940Vector@@@Z
//
// It RETURNS the destination, and that return is what the bytes prove: nothing
// reads eax afterwards, yet retail keeps the destination in eax and pays for a
// `lea edx,[eax+4]` plus an esi temp to copy the vector without clobbering it.
// Written as a void function the same source compiles to 34 bytes that reuse
// eax as the cursor.
Rva00069940Value *Rva00069940Assign(Rva00069940Value *destination,
	const Rva00069940Value *source, const Rva00069940Vector *vector)
{
	destination->m_kind = source->m_kind;
	destination->m_vector = *vector;
	return destination;
}
