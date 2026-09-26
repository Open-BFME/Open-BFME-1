// cl: /DNDEBUG /MD /EHsc

struct Rva000834F0FillOnes
{
	float m_values[132];

	Rva000834F0FillOnes *fill();
};

Rva000834F0FillOnes *Rva000834F0FillOnes::fill()
{
	for (unsigned int i = 0; i != 132; ++i)
		m_values[i] = 1.0f;
	return this;
}
