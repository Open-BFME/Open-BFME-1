// cl: /O2

// The carved body only proves an integer read at receiver offset 0x0c.  No
// caller or table provides a semantic identity for that field.
class Rva006E7070IntGetter
{
public:
	int get() const;

private:
	unsigned char m_padding[0x0c];
	int m_value;
};

int Rva006E7070IntGetter::get() const
{
	return m_value;
}
