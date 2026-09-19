// Retail RVA 0x005DCAD0 reads the first field, clears it, and returns.
// The carved body has no named caller, so the address-derived owner keeps its identity open.

class Rva005DCAD0
{
public:
	void *reset();

private:
	void *m_value;
};

void *Rva005DCAD0::reset()
{
	void *oldValue = m_value;
	m_value = 0;
	return oldValue;
}

class Rva005DCB60Value
{
public:
	unsigned int takeAndClear();

private:
	unsigned int m_value;
};

unsigned int Rva005DCB60Value::takeAndClear()
{
	unsigned int oldValue = m_value;
	m_value = 0;
	return oldValue;
}
