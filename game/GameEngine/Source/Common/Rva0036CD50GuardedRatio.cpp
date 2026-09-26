typedef float Real;

extern const Real BfmeZeroRange;

class Rva0036CD50Values
{
public:
	char m_unreconstructed[ 0x2C ];
	Real m_divisor;
};

class Rva0036CD50Owner
{
public:
	char m_unreconstructed04[ 4 ];
	Rva0036CD50Values *m_values;
	char m_unreconstructed08[ 0x94 ];
	void *m_guard;
	char m_unreconstructedA0[ 8 ];
	Real m_amount;

	Real ratio(void) const;
};

Real Rva0036CD50Owner::ratio(void) const
{
	if( !m_guard )
		return 1.0f - m_amount / m_values->m_divisor;
	return BfmeZeroRange;
}

// @?ratio@Rva0036CD50Owner@@QBEMXZ 0x0036CD50
