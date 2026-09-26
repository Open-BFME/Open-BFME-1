// cl: /DNDEBUG /MD /EHsc

struct Rva001B3FB0
{
	unsigned int m_value;

	void decrement();
};

void Rva001B3FB0::decrement()
{
	if (m_value != 0)
		--m_value;
}
