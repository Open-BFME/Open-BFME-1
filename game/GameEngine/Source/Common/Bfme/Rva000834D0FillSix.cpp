// cl: /DNDEBUG /MD /EHsc

struct Rva000834D0FillSix
{
	float m_values[6];

	Rva000834D0FillSix *initialize();
};

Rva000834D0FillSix *Rva000834D0FillSix::initialize()
{
	m_values[0] = 1.0f;
	m_values[1] = 1.0f;
	m_values[2] = 1.0f;
	m_values[3] = 1.0f;
	m_values[4] = 1.0f;
	m_values[5] = 1.0f;
	return this;
}
