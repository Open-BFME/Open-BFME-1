// Copies a vector of 16-byte records whose final pointer owns a 16-bit
// reference count.

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
	BfmeRefRecordAllocator bfmeAllocator(void) const;
	void bfmeAllocate(int count, const BfmeRefRecordAllocator &allocator);

private:
	BfmeRefRecord *m_begin;
	BfmeRefRecord *m_end;
};

// ??0BfmeRefRecordVector@@QAE@ABV0@@Z
BfmeRefRecordVector::BfmeRefRecordVector(
	const BfmeRefRecordVector &source)
{
	bfmeAllocate((source.m_end - source.m_begin), source.bfmeAllocator());

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
