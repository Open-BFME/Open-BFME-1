// cl: /O2 /MD /EHsc-

class Rva007B8120DwordField
{
public:
	int get() const;

	char m_lead[0x14];
	int m_value;
};

int Rva007B8120DwordField::get() const
{
	return m_value;
}
