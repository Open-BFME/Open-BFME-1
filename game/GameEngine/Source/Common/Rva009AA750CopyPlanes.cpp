// Open-BFME5 conversion of the codec's three-plane row copier.

extern "C" void * __cdecl memcpy(void *destination, const void *source, unsigned int bytes);
#pragma intrinsic(memcpy)

struct Rva009AA750Context
{
	unsigned char m_pad0[0x40];
	unsigned int m_bytes;
	unsigned int m_rows;
	unsigned char m_pad1[0x78 - 0x48];
	unsigned char *m_source0;
	unsigned char *m_source1;
	unsigned char *m_source2;
	unsigned char m_pad2[0x98 - 0x84];
	unsigned int m_sourceStep0;
	unsigned int m_sourceStep1;
};

struct Rva009AA750Block
{
	unsigned int m_width;
	unsigned int m_height;
	unsigned char m_pad0[0x0c - 0x08];
	unsigned int m_planeStep;
	unsigned char m_pad1[0x18 - 0x10];
	unsigned char *m_destination0;
	unsigned char *m_destination1;
	unsigned char *m_destination2;
};

void Rva009AA750CopyPlanes(
	Rva009AA750Context *self, int offset, Rva009AA750Block *block)
{
	int width = (unsigned int)(block->m_height - self->m_rows) >> 1;
	unsigned char *destination0 = block->m_destination0 + block->m_width * width;
	int x = (unsigned int)(block->m_width - self->m_bytes) >> 1;
	unsigned char *source0 = self->m_source0 + offset;
	destination0 += x;

	unsigned int index = 0;
	while (index < self->m_rows)
	{
		memcpy(destination0, source0, self->m_bytes);
		destination0 += block->m_width;
		source0 += self->m_sourceStep0;
		++index;
	}

	unsigned char *source1 = self->m_source1 + offset;
	int halfWidth = width / 2;
	int halfX = x / 2;
	unsigned char *destination1 = block->m_destination1 + block->m_planeStep * halfWidth + halfX;

	index = 0;
	while (index < self->m_rows / 2)
	{
		memcpy(destination1, source1, self->m_bytes / 2);
		destination1 += block->m_planeStep;
		source1 += self->m_sourceStep1;
		++index;
	}

	source1 = self->m_source2 + offset;
	unsigned char *destination2 = block->m_destination2 + block->m_planeStep * halfWidth + halfX;

	index = 0;
	while (index < self->m_rows / 2)
	{
		memcpy(destination2, source1, self->m_bytes / 2);
		destination2 += block->m_planeStep;
		source1 += self->m_sourceStep1;
		++index;
	}
}
