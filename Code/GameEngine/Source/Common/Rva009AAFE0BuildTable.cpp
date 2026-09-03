// Open-BFME5 conversion of the 16-value codec table builder.

struct Rva009AAFE0Context
{
	unsigned char m_pad0[0x19C];
	unsigned char m_mode;
	unsigned char m_pad1[0x5BC - 0x19D];
	unsigned char m_table[0x400];
};

void __cdecl Rva009AAFE0BuildTable(register Rva009AAFE0Context *self,
	register const unsigned char *source)
{
	int next = 1;
    unsigned int value;

	self->m_table[0] = 0;

	for (value = 0; value < 16; ++value) {
        unsigned int position;

		for (position = 1; position < 64; ++position) {
			if (source[position] == value) {
				self->m_table[next] = (unsigned char)position;
				++next;
			}
		}

	}

	{
		unsigned int maximum = 0;
		unsigned char *output = self->m_table + 0x40;
		int group = 16;

		do {
			unsigned int candidate = self->m_table[output - (self->m_table + 0x40)];
			if (candidate > maximum)
				maximum = candidate;
			*output = (unsigned char)maximum;
			if (self->m_mode > 6)
				*output = (unsigned char)(maximum + 1);

			candidate = self->m_table[output - (self->m_table + 0x40) + 1];
			if (candidate > maximum)
				maximum = candidate;
			output[1] = (unsigned char)maximum;
			if (self->m_mode > 6)
				output[1] = (unsigned char)(maximum + 1);

			candidate = self->m_table[output - (self->m_table + 0x40) + 2];
			if (candidate > maximum)
				maximum = candidate;
			output[2] = (unsigned char)maximum;
			if (self->m_mode > 6)
				output[2] = (unsigned char)(maximum + 1);

			candidate = self->m_table[output - (self->m_table + 0x40) + 3];
			if (candidate > maximum)
				maximum = candidate;
			output[3] = (unsigned char)maximum;
			if (self->m_mode > 6)
				output[3] = (unsigned char)(maximum + 1);

			output += 4;
		} while (--group != 0);
	}
}
