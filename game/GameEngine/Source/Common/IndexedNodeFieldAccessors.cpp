// The four byte-identical 20-byte accessors at 0x0033B330, 0x00354420,
// 0x00354440 and 0x003544C0.
//
//     mov eax,[esp+4] / mov ecx,[ecx+0xC] / lea eax,[eax+eax*4]
//     mov eax,[ecx+eax*4+0x10] / add eax,4 / ret 4
//
// WHAT THE BYTES SHOW.  `this` in ecx, one dword argument, `ret 4`: __thiscall
// taking an index.  The class's member at +0xC is a pointer to an array, and the
// index is scaled by five and then by four -- `lea eax,[eax+eax*4]` followed by
// an `*4` scale factor is MSVC's factorisation of a multiply by TWENTY, so the
// array's element type is twenty bytes wide.  Within the element, displacement
// +0x10 is loaded as a POINTER (it is produced by a load, then only added to,
// never used as a base for a second load), and the constant 4 is added to it.
//
// Adding a constant to a loaded pointer and returning it, with no null check
// anywhere, is the signature of taking the address of a field: the compiler
// folded the member offset into the address computation because taking an
// address cannot fault.  A null check would have been mandatory for a
// dereference and is absent, which is what distinguishes this from a load of the
// field itself.  So the body returns the address of a field four bytes into the
// node the indexed entry holds.
//
// Note `add eax,4` rather than `lea eax,[eax+4]`, both three bytes: the compiler
// chose the arithmetic form because the value is no longer live as an address at
// that point.  Nothing in the source controls that choice, and the spelling
// below reproduces it.
//
// SEPARATE FUNCTIONS, NOT ALIASES.  Four distinct addresses, three of them
// (0x00354420, 0x00354440, 0x003544C0) in one drawer at a small stride, the
// fourth well away.  Nothing defeats inlining here, so there is no
// per-translation-unit COMDAT reading to justify asserting they are one.
//
// IDENTITY IS NOT RECOVERED.  Nothing in the image names the table, the element
// or the field, so the names are address-derived.

struct IndexedNode
{
	void *m_link;
	int m_field;
};

struct IndexedEntry
{
	int m_pad0;
	int m_pad1;
	int m_pad2;
	int m_pad3;
	IndexedNode *m_node;
};

#define BFME_INDEXED_NODE_FIELD( NAME )                                       \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		int *at( int index );                                                 \
                                                                              \
		int m_pad0;                                                           \
		int m_pad1;                                                           \
		int m_pad2;                                                           \
		IndexedEntry *m_table;                                                \
	};                                                                        \
	int *NAME::at( int index )                                                \
	{                                                                         \
		return &m_table[index].m_node->m_field;                               \
	}

BFME_INDEXED_NODE_FIELD( Rva0033B330Table )
BFME_INDEXED_NODE_FIELD( Rva00354420Table )
BFME_INDEXED_NODE_FIELD( Rva00354440Table )
BFME_INDEXED_NODE_FIELD( Rva003544C0Table )
