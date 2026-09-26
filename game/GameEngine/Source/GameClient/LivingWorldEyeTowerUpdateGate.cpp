// cl: /DNDEBUG /MD /GX- /O2 /Ob2

class WWMath
{
public:
	static float Random_Float();
};

class Gen0060BE20
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();

	void updateGate();

private:
	void refresh();
	void onRandomGate();
	void onLimitPassed();

	char m_pad04[0x04];
	void *m_object;
	char m_gap0c[0x18];
	unsigned int m_mode;
	void *m_target;
	unsigned int m_phase;
	unsigned int m_value;
	unsigned int m_start;
	unsigned int m_lower;
	unsigned int m_upper;
	unsigned int m_limit;
	unsigned int m_state;
	char m_gap48[0x44];
	float m_scale;
	float m_result;
	float m_red;
	float m_green;
	float m_blue;
};

extern volatile float g_bfmeUint32Scale;
void Rva00739900Forward( void *object, float value );
void __cdecl bfmeReportGN( void *object, void *red, void *green, void *blue );

void Gen0060BE20::refresh()
{
	if( m_mode != 0 )
	{
		float value = 0.0f;

		if( m_mode == 1 || m_mode == 2 )
		{
			if( m_value == 0 )
				slot20();

			unsigned int numerator;
			if( m_mode == 1 )
				numerator = m_value;
			else
				numerator = m_phase - m_value;
			unsigned int denominator = m_phase;
			value = (float)numerator / (float)denominator;

			++m_value;
			if( m_value > denominator )
				slot24();
		}
		else if( m_mode == 3 )
		{
			unsigned int next = ++m_value;
			m_state = 0;
			if( next > m_limit )
				slot24();
			else if( next > m_upper )
			{
				unsigned int numerator = m_limit - next;
				unsigned int denominator = m_limit - m_upper;
				value = (float)numerator / (float)denominator;
				m_state = 2;
			}
			else if( next > m_lower )
			{
				value = 1.0f;
			}
			else if( next >= m_start )
			{
				unsigned int numerator = next - m_start;
				unsigned int denominator = m_lower - m_start;
				value = (float)numerator / (float)denominator;
				m_state = 1;
				if( next == m_start )
					slot20();
			}
		}

		value *= m_scale;
		m_result = value;

		if( m_target == 0 )
		{
			Rva00739900Forward( m_object, value );
			goto finish;
		}
		if( m_target == reinterpret_cast<void *>( 1 ) )
		{
			reinterpret_cast<void (__cdecl *)( void *, float, float, float )>( bfmeReportGN )(
				m_object, value * m_red, value * m_green, value * m_blue );
		}
	}

finish:
	slot10();
	slot18();
	slot14();
}

void Gen0060BE20::updateGate()
{
	refresh();

	if (m_value > m_lower && m_value < m_upper && WWMath::Random_Float() > 0.7f)
		onRandomGate();

	if (m_value > m_limit)
		onLimitPassed();
}
