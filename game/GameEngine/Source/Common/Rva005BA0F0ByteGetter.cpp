// cl: /O2

class Rva005BA0F0ByteGetter
{
public:
	unsigned char get() const;

private:
	unsigned char m_padding[0x18];
	unsigned char m_value;
};

unsigned char Rva005BA0F0ByteGetter::get() const
{
	return m_value;
}
