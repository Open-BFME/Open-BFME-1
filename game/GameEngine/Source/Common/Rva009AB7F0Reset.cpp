// The VP6 codec caller at 0x009ABFC0 reaches this address-derived table reset.
// The volatile table pointers preserve retail's repeated field loads.

struct Rva009AB7F0Record
{
	unsigned char m_zeroByte;
	unsigned char m_pad01[3];
	int m_minusOne;
	unsigned short m_four;
	unsigned short m_zeroWord;
	unsigned char m_pad0c[4];
};

struct Rva009AB7F0Context
{
	unsigned char m_pad0[0x10c];
	Rva009AB7F0Record * volatile m_table0;
	Rva009AB7F0Record * volatile m_table1;
	Rva009AB7F0Record * volatile m_table2;
	unsigned char m_pad118[0x19c - 0x118];
	unsigned char m_mode;
	unsigned char m_pad19d[0x1f8 - 0x19d];
	unsigned int volatile m_countBias;
	unsigned char m_pad1fc[0x20];
};

void Rva009AB7F0Reset(Rva009AB7F0Context *self)
{
	int minusOne = -1;
	unsigned short four = 4;
	int zero = 0;
	int i = 0;
	i = 0;
	if (self->m_countBias + 8 != 0)
	{
		do
		{
			self->m_table0[i].m_minusOne = minusOne;
			self->m_table0[i].m_four = four;
			self->m_table0[i].m_zeroWord = zero;
			self->m_table0[i].m_zeroByte = zero;
		}
		while (++i < self->m_countBias + 8);
	}

	i = 0;
	if ((self->m_countBias >> 1) + 8 != 0)
	{
		do
		{
			self->m_table1[i].m_minusOne = minusOne;
			self->m_table1[i].m_four = four;
			self->m_table1[i].m_zeroByte = zero;
			self->m_table1[i].m_zeroWord = zero;
			self->m_table2[i].m_minusOne = minusOne;
			self->m_table2[i].m_four = four;
			self->m_table2[i].m_zeroByte = zero;
			self->m_table2[i].m_zeroWord = zero;
		}
		while (++i < (self->m_countBias >> 1) + 8);
	}

	if (self->m_mode < 6)
	{
		self->m_table1[1].m_minusOne = zero;
		self->m_table1[1].m_four = zero;
		self->m_table2[1].m_minusOne = zero;
		self->m_table2[1].m_four = zero;
	}

	*(unsigned short *)((unsigned char *)self + 0x12c) = 0x80;
	*(unsigned short *)((unsigned char *)self + 0x134) = 0x80;
	*(unsigned short *)((unsigned char *)self + 0x124) = zero;

	unsigned short *tail = (unsigned short *)((unsigned char *)self + 0x12e);
	i = 2;
	do
	{
		tail[-4] = zero;
		tail[0] = zero;
		tail[4] = zero;
		++tail;
		--i;
	}
	while (i != 0);
}
