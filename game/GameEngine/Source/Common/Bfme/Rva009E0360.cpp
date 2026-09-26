// cl: /DNDEBUG /MD /EHsc

class Rva009E0360
{
public:
	void m009E0360();

private:
	unsigned char m_gap00[0x0C];
	short m_width;
	short m_height;
	signed char m_bits;
	unsigned char m_gap11[0x0F];
	unsigned char *m_data;
};

void Rva009E0360::m009E0360()
{
	unsigned char *ptr;
	unsigned char *ptr1;
	long x;
	long y;
	unsigned char value;
	unsigned char value1;
	signed char depth;

	depth = (signed char)((m_bits + 7) >> 3);
	for (y = 0; y < (m_height >> 1); ++y)
	{
		ptr = (m_data + ((m_width * y) * depth));
		ptr1 = (m_data + ((m_width * (m_height - 1)) * depth));
		ptr1 -= ((m_width * y) * depth);

		for (x = 0; x < (m_width * depth); ++x)
		{
			value = *ptr;
			value1 = *ptr1;
			*ptr = value1;
			*ptr1 = value;
			++ptr;
			++ptr1;
		}
	}
}
