// cl: /O2

// The carved body only proves an integer read at receiver offset 4.  No
// caller or table provides a semantic identity for that field.
class Rva003C4C10IntGetter
{
public:
	int get() const;

private:
	int m_padding;
	int m_value;
};

int Rva003C4C10IntGetter::get() const
{
	return m_value;
}
