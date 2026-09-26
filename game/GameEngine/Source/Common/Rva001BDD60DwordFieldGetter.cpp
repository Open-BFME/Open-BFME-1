class Rva001BDD60DwordField
{
public:
	int get() const;

private:
	char m_lead[ 0x1C ];
	int m_value;
};

int Rva001BDD60DwordField::get() const
{
	return m_value;
}
