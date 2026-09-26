struct Rva009A4E30Source
{
	char m_reserved[0x1a0];
	int m_value1a0;
};

void __cdecl rva009A4E30ConditionalOutput(const Rva009A4E30Source *source,
	unsigned int suppress, int *output)
{
	if (suppress == 0)
		*output = source->m_value1a0;
}
