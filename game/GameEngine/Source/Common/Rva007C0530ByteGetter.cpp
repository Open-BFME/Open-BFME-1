// cl: /O2 /MD

class Rva007C0530ByteGetter
{
public:
	unsigned char get() const;

private:
	char m_padding[5];
	unsigned char m_value;
};

unsigned char Rva007C0530ByteGetter::get() const
{
	return m_value;
}
