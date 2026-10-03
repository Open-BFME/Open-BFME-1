// Copies a vector of 16-byte records whose final pointer owns a 16-bit
// reference count.
//
// Neither helper is a recovered body: retail reaches the allocator accessor
// and the block allocator through the ILT thunks at 0x00046853 and
// 0x00035B07, whose only definition in the tree is the address-derived
// gen-thunk pair ?j_00046853@@YAXXZ / ?j_00035b07@@YAXXZ. Call them under
// that spelling, keeping this TU's own view of the two signatures.

extern void j_00035b07();
extern void j_00046853();

struct BfmeRefRecord
{
	short m_word0;
	short m_word2;
	short m_word4;
	short m_word6;
	int m_word8;
	short *m_reference;
};

class BfmeRefRecordAllocator
{
private:
	int m_value;
};

class BfmeRefRecordVector
{
public:
	BfmeRefRecordVector(const BfmeRefRecordVector &source);

private:
	BfmeRefRecord *m_begin;
	BfmeRefRecord *m_end;
};

// ??0BfmeRefRecordVector@@QAE@ABV0@@Z
BfmeRefRecordVector::BfmeRefRecordVector(
	const BfmeRefRecordVector &source)
{
	typedef BfmeRefRecordAllocator (BfmeRefRecordVector::*AllocatorThunk)() const;
	typedef void (BfmeRefRecordVector::*AllocateThunk)(int,
		const BfmeRefRecordAllocator &);
	union Allocator
	{
		void (*function)(void);
		AllocatorThunk member;
	} allocatorThunk;
	union Allocate
	{
		void (*function)(void);
		AllocateThunk member;
	} allocateThunk;

	allocatorThunk.function = j_00046853;
	allocateThunk.function = j_00035b07;
	(this->*allocateThunk.member)((source.m_end - source.m_begin),
		(source.*allocatorThunk.member)());

	BfmeRefRecord *sourceEnd = source.m_end;
	BfmeRefRecord *input = source.m_begin;
	BfmeRefRecord *output = m_begin;
	while (input != sourceEnd)
	{
		if (output != 0)
		{
			output->m_word0 = input->m_word0;
			output->m_word2 = input->m_word2;
			output->m_word4 = input->m_word4;
			output->m_word6 = input->m_word6;
			output->m_word8 = input->m_word8;
			output->m_reference = input->m_reference;
			if (output->m_reference != 0)
				++*output->m_reference;
		}
		++input;
		++output;
	}
	m_end = output;
}
