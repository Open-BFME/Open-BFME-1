// cl: /O2 /Ob1 /EHsc

class Rva006F9FB0DwordField
{
public:
	int get(void) const;

private:
	int m_unmodelled_00[3];
	int m_value;
};

// ?get@Rva006F9FB0DwordField@@QBEHXZ
int Rva006F9FB0DwordField::get(void) const
{
	return m_value;
}
