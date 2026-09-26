// The three-byte body reads the first integer from its receiver.
struct Rva00756D40
{
	int m_value;

	int getValue() const;
};

int Rva00756D40::getValue() const
{
	return m_value;
}
