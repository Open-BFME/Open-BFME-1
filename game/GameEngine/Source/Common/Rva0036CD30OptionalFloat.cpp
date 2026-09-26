typedef float Real;

extern const Real BfmeZeroRange;

class Rva0036CD30Value
{
public:
	char m_unreconstructed[ 0x38 ];
	Real m_value38;
};

class Rva0036CD30Owner
{
public:
	char m_unreconstructed[ 4 ];
	Rva0036CD30Value *m_value04;

	Real value(void) const;
};

Real Rva0036CD30Owner::value(void) const
{
	Real result = BfmeZeroRange;
	if( m_value04 )
		result = m_value04->m_value38;
	return result;
}

// @?value@Rva0036CD30Owner@@QBEMXZ 0x0036CD30
