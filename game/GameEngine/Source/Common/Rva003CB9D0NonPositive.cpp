class Rva003CB9D0
{
public:
	bool isNonPositive();

private:
	char m_pad[0x38];
	char m_flag;
};

bool Rva003CB9D0::isNonPositive()
{
	return m_flag > 0;
}
