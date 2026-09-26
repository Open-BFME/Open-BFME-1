// cl: /DNDEBUG /MD /EHsc

struct Rva0026FA40StoreAndClear
{
	unsigned char m_unmodelled_000[0x1FC];
	unsigned int m_value;
	unsigned char m_unmodelled_200[0x12A];
	unsigned char m_ready;

	void storeAndClear(unsigned int value);
};

void Rva0026FA40StoreAndClear::storeAndClear(unsigned int value)
{
	m_value = value;
	m_ready = 0;
}
