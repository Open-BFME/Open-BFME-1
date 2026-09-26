// cl: /DNDEBUG /MD /EHsc

class Rva000C8C80
{
public:
	int combinedValue() const;

private:
	unsigned char m_padding[0x64];
	int m_base;
	int m_first;
	int m_second;
};

int Rva000C8C80::combinedValue() const
{
	return m_first + m_second + m_base;
}
