// Retail 0x006BE000 returns the four-byte field at this plus eight.

class Rva006BE000Object
{
public:
	int getValue();

private:
	char m_padding00[8];
	int m_value;
};

int Rva006BE000Object::getValue()
{
	return m_value;
}
