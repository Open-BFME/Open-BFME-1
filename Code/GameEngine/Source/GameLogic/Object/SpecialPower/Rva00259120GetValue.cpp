// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

class Rva00259120
{
public:
	int getValue(void) const;

private:
	char m_pad00[4];
	int m_value;
};

// ?getValue@Rva00259120@@QBEHXZ
int Rva00259120::getValue(void) const
{
	return m_value;
}
