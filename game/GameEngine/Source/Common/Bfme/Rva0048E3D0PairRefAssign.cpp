// cl: /DNDEBUG /MD /EHsc

struct Rva0048E3D0Source
{
	unsigned char m_unmodelled_000[0x0c];
	int m_delta;
	unsigned int m_first;
	unsigned int m_second;
};

struct Rva0048E3D0PairRefAssign
{
	unsigned int m_first;
	unsigned int m_second;

	void assign(Rva0048E3D0Source *source);
};

void Rva0048E3D0PairRefAssign::assign(Rva0048E3D0Source *source)
{
	source->m_first = m_first;
	source->m_second = m_second;
	m_first += source->m_delta;
}
