// cl: /DNDEBUG /MD

class Rva000B2100DwordField
{
public:
	int get() const;

private:
	char m_padding[0x28];
	int m_value;
};

int Rva000B2100DwordField::get() const
{
	return m_value;
}
