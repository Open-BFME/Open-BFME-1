// cl: -GX
// stlport
// Open-BFME5: near-twin of R5VectorDtorEHFramed.cpp -- an EH-framed
// std::vector<T> destructor (three-word push fs:[0] frame, unwind states 0
// across the element-destroy loop and -1 once only the outer buffer is
// left). This element is 0x20 bytes wide and owns one nested raw byte
// buffer at +0x04 (start) / +0x0c (end), freed through the same
// operator-delete-vs-node_alloc dispatch at the 0x80-byte threshold that the
// twin's BfmeDtorMemberBElement uses. The rest of the 0x20-byte element
// (offsets 0x00, 0x08, 0x10-0x1f) is never touched by this destructor, so it
// is trivially destructible padding here.
//
// IDENTITY IS NOT RECOVERED. Element named for its stride; `char m_pad*`
// carries width and nothing else.

#include <vector>

struct Rva007715B0Element
{
	char m_pad0[4];
	char *m_begin;
	char m_pad8[4];
	char *m_end;
	char m_padTail[0x10];

	Rva007715B0Element();
	Rva007715B0Element(const Rva007715B0Element &);
	~Rva007715B0Element();
	Rva007715B0Element &operator=(const Rva007715B0Element &);
};

Rva007715B0Element::~Rva007715B0Element()
{
	const unsigned int allocation_size = m_end - m_begin;
	if (m_begin != 0)
	{
		_STL::allocator<char>().deallocate(m_begin, allocation_size);
	}
}

template class _STL::vector<Rva007715B0Element>;
