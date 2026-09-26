class Rva005FC2B0
{
public:
	void *set();

private:
	char m_value;
};

void *Rva005FC2B0::set()
{
	m_value = 1;
	return this;
}
