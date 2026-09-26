// cl: /DNDEBUG /MD /EHsc

struct Rva00117ED0Clear
{
	unsigned int m_values[109];

	Rva00117ED0Clear *clear();
};

Rva00117ED0Clear *Rva00117ED0Clear::clear()
{
	for (unsigned int i = 0; i != 109; ++i)
		m_values[i] = 0;
	return this;
}
