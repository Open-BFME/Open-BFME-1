// cl: /O2 /MD

class Rva0079E3C0ByteGetter
{
public:
	unsigned char get() const;

private:
	char m_padding[4];
	unsigned char m_value;
};

unsigned char Rva0079E3C0ByteGetter::get() const
{
	return m_value;
}
