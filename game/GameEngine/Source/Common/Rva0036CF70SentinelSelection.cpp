class Rva0036CF70Values
{
public:
	char m_unreconstructed[ 8 ];
	int m_fallbackFirst;
	int m_fallbackSecond;
	int m_selectedFirst;
	int m_selectedSecond;
};

class Rva0036CF70Selection
{
public:
	char m_unreconstructed04[ 4 ];
	Rva0036CF70Values *m_values;
	char m_unreconstructed08[ 0x1C ];
	bool m_useSelected;

	int firstValue(void) const;
	int secondValue(void) const;
};

int Rva0036CF70Selection::firstValue(void) const
{
	Rva0036CF70Values *values = m_values;
	if( m_useSelected )
	{
		int value = values->m_selectedFirst;
		if( value != -2 )
			return value;
	}

	int value = values->m_fallbackFirst;
	if( value == -2 )
		value = 1;
	return value;
}

// @?firstValue@Rva0036CF70Selection@@QBEHXZ 0x0036CF70

int Rva0036CF70Selection::secondValue(void) const
{
	Rva0036CF70Values *values = m_values;
	if( m_useSelected )
	{
		int value = values->m_selectedSecond;
		if( value != -2 )
			return value;
	}

	int value = values->m_fallbackSecond;
	if( value == -2 )
		value = 2;
	return value;
}

// @?secondValue@Rva0036CF70Selection@@QBEHXZ 0x0036CFA0
