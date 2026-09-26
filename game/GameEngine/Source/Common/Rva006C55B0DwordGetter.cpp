// cl: /DNDEBUG /MD

class Rva006C55B0DwordField
{
public:
	int get(void) const;

private:
	char m_padding[4];
	int m_value;
};

int Rva006C55B0DwordField::get(void) const
{
	return m_value;
}
