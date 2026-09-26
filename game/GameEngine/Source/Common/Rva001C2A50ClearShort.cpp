class Rva001C2A50Object
{
public:
	void clearShort();

private:
	unsigned char m_prefix[0x26];
	unsigned short m_value;
};

void Rva001C2A50Object::clearShort()
{
	m_value = 0;
}
