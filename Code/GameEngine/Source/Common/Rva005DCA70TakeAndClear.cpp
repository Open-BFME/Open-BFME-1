class Rva005DCA70Value
{
public:
	unsigned int takeAndClear();

private:
	unsigned int m_value;
};

unsigned int Rva005DCA70Value::takeAndClear()
{
	unsigned int old = m_value;
	m_value = 0;
	return old;
}
