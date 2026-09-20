// The four byte-identical 43-byte indexed list walkers at 0x003517B0,
// 0x003517F0, 0x00351890 and 0x003518D0 -- four bodies in one drawer.  Retail:
//
//     mov eax,[esp+4] / mov ecx,[ecx+0xC] / mov edx,[esp+8]
//     lea eax,[eax+eax*4] / lea ecx,[ecx+eax*4]
//     movsx eax,word ptr [ecx+0xE] / cmp eax,edx / mov ecx,[ecx+0x10]
//     jle done / sub eax,edx / npad 2
//     loop: dec eax / mov ecx,[ecx] / jne loop
//     done: lea eax,[ecx+4] / ret 8
//
// WHAT THE BYTES SHOW.  `this` in ecx, two stack arguments, `ret 8`: a
// __thiscall member function of two arguments returning an address.
//
// `lea eax,[eax+eax*4]` followed by a scale-4 `lea` is a MULTIPLY BY TWENTY --
// the classic strength-reduced `index * 20` -- so `this` holds a pointer at
// +0xC to an array of 20-byte entries and the first argument is the index into
// it.  Within the entry, `movsx word ptr [+0xE]` is a SIGNED 16-BIT count (an
// unsigned one would be `movzx`, and an `int` would be a plain `mov`), and
// +0x10 is a pointer.  `mov ecx,[ecx]` walks it, so it is a singly linked list
// whose `next` is its first member; the result `lea eax,[ecx+4]` is the address
// of the member just past that `next`.
//
// THE LOOP IS A COUNTDOWN THE COMPILER INVENTED.  The source compares the
// entry's count against the second argument -- `cmp eax,edx` / `jle` is a
// SIGNED comparison, matching the signed 16-bit count -- and the body advances
// one link per step.  MSVC 7.1 then replaces the comparison with a trip count
// (`sub eax,edx`) and counts down to zero, which is why the loop body is three
// bytes and tests nothing.  Writing the trip count in the SOURCE instead --
// `int i = count - which; while (i-- > 0)` -- does not produce these bytes: it
// emits `sub`/`test` before the branch rather than `cmp`, and a hand-written
// do/while emits a two-byte `mov edi,edi` differently and runs two bytes long.
// The `npad 2` inside is the compiler's own loop alignment.
//
// THE ORDER OF THE TWO ENTRY LOADS IS SOURCE EVIDENCE.  Retail reads the COUNT
// first and the list HEAD second (`movsx` before `mov ecx,[ecx+0x10]`), and it
// keeps the entry address in ecx throughout.  Reading the head first -- the
// natural way to write it, `Node *n = e->head;` ahead of the loop -- swaps the
// register assignment and the two loads (`lea eax,[ecx+eax*4]` / `mov ecx,
// [eax+0x10]` / `movsx eax,[eax+0xE]`): same 43 bytes, five of them different.
// So the source names the count before it names the head.
//
// SEPARATE FUNCTIONS, NOT ALIASES.  Four addresses, four instantiations over
// four entry/node pairs that share these offsets.
//
// IDENTITY IS NOT RECOVERED.  Nothing in the image names the holder, the entry,
// the node or the accessor, so the names are address-derived and disclaim
// identity.

#define BFME_INDEXED_LIST_TAIL_WALKER( NAME )                                 \
	struct NAME##Node                                                         \
	{                                                                         \
		NAME##Node *m_next;                                                   \
		int m_value;                                                          \
	};                                                                        \
	struct NAME##Entry                                                        \
	{                                                                         \
		char m_leading[ 0xE ];                                                \
		short m_count;                                                        \
		NAME##Node *m_head;                                                   \
	};                                                                        \
	class NAME##Holder                                                        \
	{                                                                         \
	public:                                                                   \
		char m_leading[ 0xC ];                                                \
		NAME##Entry *m_entries;                                               \
		int *valueAt( int index, int which );                                 \
	};                                                                        \
	int *NAME##Holder::valueAt( int index, int which )                        \
	{                                                                         \
		NAME##Entry *entry = &m_entries[ index ];                             \
		int remaining = entry->m_count;                                       \
		NAME##Node *node = entry->m_head;                                     \
		for ( ; remaining > which; --remaining )                              \
		{                                                                     \
			node = node->m_next;                                              \
		}                                                                     \
		return &node->m_value;                                                \
	}

BFME_INDEXED_LIST_TAIL_WALKER( Rva003517B0 )
BFME_INDEXED_LIST_TAIL_WALKER( Rva003517F0 )
BFME_INDEXED_LIST_TAIL_WALKER( Rva00351890 )
BFME_INDEXED_LIST_TAIL_WALKER( Rva003518D0 )

// The 20-byte records at +0x0C form an indexed linked list.  The landed
// neighbours establish the record stride and the chain index at +0x1C.
class Rva00351830Holder
{
public:
	void Rva00351830IndexedListMark();

private:
	char m_padding00[ 0x0C ];
	unsigned char *m_records;
	char m_padding10[ 0x0C ];
	int m_index;
};

// ?Rva00351830IndexedListMark@Rva00351830Holder@@QAEXXZ
void Rva00351830Holder::Rva00351830IndexedListMark()
{
	unsigned char mark = 1;
	int index = m_index;
	if (index != -1)
	{
		unsigned int p = (unsigned int)m_records;
		do
		{
			unsigned int i = (unsigned int)index * 20;
			*(unsigned char *)(i + p + 0x0C) = mark;
			p = (unsigned int)m_records;
			index = *(int *)(i + p);
		}
		while (index != -1);
	}
}

struct Rva00351860Owner
{
	char m_padding00[ 0x0c ];
	unsigned int m_entries;
	char m_padding10[ 0x0c ];
	int m_index;

	void rva00351860();
};

static __forceinline void rva00351860Clear(unsigned int offset,
	unsigned int pointer)
{
	*(unsigned char *)(offset + pointer) = 0;
}

static __forceinline int rva00351860Read(unsigned int offset,
	unsigned int pointer)
{
	return *(int *)(offset + pointer);
}

// ?rva00351860@Rva00351860Owner@@QAEXXZ
void Rva00351860Owner::rva00351860()
{
	int index = m_index;
	if (index != -1)
	{
		do
		{
			rva00351860Clear((unsigned int)(index * 20 + 0x0c),
				m_entries);
			index = rva00351860Read((unsigned int)(index * 20), m_entries);
		}
		while (index != -1);
	}
}
