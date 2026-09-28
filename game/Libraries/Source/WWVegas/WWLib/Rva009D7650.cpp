struct Rva009D7650Text
{
	const char *m_first;
	const char *m_last;
};

unsigned int __stdcall Rva009D7650(const Rva009D7650Text &text)
{
	unsigned int value = 0;
	const char *first = text.m_first;
	unsigned int length = static_cast<unsigned int>(text.m_last - first);
	for (unsigned int index = 0; index < length; ++index)
		value = value * 5 + static_cast<signed char>(first[index]);
	return value;
}
