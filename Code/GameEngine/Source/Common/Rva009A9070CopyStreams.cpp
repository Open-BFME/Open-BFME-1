extern "C" void * __cdecl memcpy(void *destination, const void *source, unsigned int bytes);
#pragma intrinsic(memcpy)

struct Rva009A9070Source
{
	unsigned int m_size0;
	int m_rows0;
	unsigned int m_sourceStep0;
	unsigned int m_size1;
	int m_rows1;
	unsigned int m_sourceStep1;
	unsigned char *m_source0;
	unsigned char *m_source1;
	unsigned char *m_source2;
};

struct Rva009A9070Context
{
	unsigned char m_pad0[0x78];
	unsigned char *m_destination0;
	unsigned char *m_destination1;
	unsigned char *m_destination2;
	unsigned char m_pad1[0x98 - 0x84];
	unsigned int m_destinationStep0;
	unsigned int m_destinationStep1;
};

	void __cdecl d_009a8c50(void);

void __cdecl Rva009A9070CopyStreams(
	Rva009A9070Context *self,
	Rva009A9070Source *source,
	int offset)
{
	unsigned char *input = source->m_source0;
	unsigned char *destination = self->m_destination0 + offset;
	int row = 0;
	while (row < source->m_rows0)
	{
		memcpy(destination, input, source->m_size0);
		input += source->m_sourceStep0;
		destination += self->m_destinationStep0;
		++row;
	}

	{
		register unsigned char *destination1 = self->m_destination1;
		register int offset1 = offset;
		register unsigned char *input1 = source->m_source1;
		register int row1 = 0;
		destination1 += offset1;
		while (row1 < source->m_rows1)
		{
			memcpy(destination1, input1, source->m_size1);
			input1 += source->m_sourceStep1;
			destination1 += self->m_destinationStep1;
			++row1;
		}
	}

	{
		register unsigned char *destination2 = self->m_destination2;
		register int offset2 = offset;
		register unsigned char *input2 = source->m_source2;
		register int row2 = 0;
		destination2 += offset2;
		while (row2 < source->m_rows1)
		{
			memcpy(destination2, input2, source->m_size1);
			input2 += source->m_sourceStep1;
			destination2 += self->m_destinationStep1;
			++row2;
		}
	}

	((void (__cdecl *)(Rva009A9070Context *, int))d_009a8c50)(self, offset);
}
