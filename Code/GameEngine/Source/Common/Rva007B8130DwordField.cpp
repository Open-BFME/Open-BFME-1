// ?get@Rva007B8130DwordField@@QBEHXZ
// cl: /O2 /MD /EHsc-

class Rva007B8130DwordField
{
public:
	int get() const;

	char m_lead[0x18];
	int m_value;
};

int Rva007B8130DwordField::get() const
{
	return m_value;
}
