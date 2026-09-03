// ?isAfter@Rva00064770Tree@@QBE_NI@Z
// partial score=0.95 date=2026-09-02
// cl: /DNDEBUG /MD /EHs-c-
// Near-miss for 0x00064880. Sibling of isBefore@Rva00064770Tree. Exact 39-byte
// shape except the key load uses ecx instead of eax (ModRM 48 vs 40).

typedef int Int;
typedef unsigned int UnsignedInt;

struct Rva00064770Node
{
	Int m_colour;
	Rva00064770Node *m_parent;
	Rva00064770Node *m_left;
	Rva00064770Node *m_right;
	unsigned char m_unreconstructed_10[0x18];
	UnsignedInt m_key;
};

extern "C" Rva00064770Node *__cdecl _W3RbDecrement(Rva00064770Node *node);

class Rva00064770Tree
{
public:
	bool isAfter(UnsignedInt key) const;

private:
	Rva00064770Node *m_header;
	Int m_count;
};

bool Rva00064770Tree::isAfter(UnsignedInt key) const
{
	if (m_count == 0)
	{
		return true;
	}

	return _W3RbDecrement(m_header)->m_key < key;
}
