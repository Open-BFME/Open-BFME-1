class Rva00478C90Object
{
public:
	int store(unsigned int value);

private:
	unsigned char m_prefix[0x34];
	unsigned int m_value;
};

int Rva00478C90Object::store(unsigned int value)
{
	m_value = value;
	return 0;
}
