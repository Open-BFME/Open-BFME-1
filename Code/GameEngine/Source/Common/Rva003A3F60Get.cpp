// cl: /O2 /MD /EHsc

struct Rva003A3F60
{
	void *m_value;
	void *get(void) const;
};

void *Rva003A3F60::get(void) const
{
	return m_value;
}
