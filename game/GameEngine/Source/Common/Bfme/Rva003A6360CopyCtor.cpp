// Retail 0x003A6360 copies a 12-byte polymorphic record and installs vtable
// 0x010EC760. No evidence proves the semantic class name, so the type keeps the address.

extern int R2Data010EC760;

class Rva003A6360Record
{
public:
	Rva003A6360Record(const Rva003A6360Record &other);

	int m_vtable;
	int m_word04;
	unsigned char m_byte08;
	int m_word0C;
};

Rva003A6360Record::Rva003A6360Record(const Rva003A6360Record &other)
{
	m_vtable = (int)&R2Data010EC760;
	m_word04 = other.m_word04;
	m_byte08 = other.m_byte08;
	m_word0C = other.m_word0C;
}
