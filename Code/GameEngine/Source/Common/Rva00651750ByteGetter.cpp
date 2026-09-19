// cl: /O2

// The carved body only proves a byte read at receiver offset 0x58.  No caller
// or table provides a semantic identity for that field.
class Rva00651750ByteGetter
{
public:
	unsigned char get() const;

private:
	unsigned char m_padding[0x58];
	unsigned char m_value;
};

unsigned char Rva00651750ByteGetter::get() const
{
	return m_value;
}
