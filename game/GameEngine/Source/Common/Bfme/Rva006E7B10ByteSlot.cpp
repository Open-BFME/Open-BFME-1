// cl: /DNDEBUG /MD /EHsc
// Retail stores one byte at this+0x128 and cleans one stack argument. The
// carved body has no owner evidence, so the class name keeps its address.

class Rva006E7B10ByteSlot
{
private:
	char m_data[0x128];
	unsigned char m_value;

public:
	void set(unsigned char value);
};

void Rva006E7B10ByteSlot::set(unsigned char value)
{
	m_value = value;
}
