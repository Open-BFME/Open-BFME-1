// Retail 0x00367E90 reads the first dword of an unknown object and returns it.

class Rva00367E90
{
public:
	int getValue();

private:
	int m_value;
};

int Rva00367E90::getValue()
{
	return m_value;
}
