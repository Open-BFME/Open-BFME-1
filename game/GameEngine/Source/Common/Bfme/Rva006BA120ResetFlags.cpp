// cl: /DNDEBUG /MD /EHsc

struct Rva006BA120ResetFlags
{
	unsigned char m_unmodelled_000[0x41];
	unsigned char m_first;
	unsigned char m_second;

	void reset();
};

void Rva006BA120ResetFlags::reset()
{
	m_first = 0;
	m_second = 1;
}
