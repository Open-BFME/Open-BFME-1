// Clean C++ reconstruction of the small opacity-ramp pair at 0x00458270 and
// 0x00458400.  The names remain address-derived until an owning BFME class is
// recovered independently.

class Gen00458270
{
public:
	char m_pad00[ 0x20 ];
	float m_minimum;
	float m_maximum;
	unsigned int m_duration;

	float sample( unsigned int frame );
};

float Gen00458270::sample( unsigned int frame )
{
	float value = ( m_maximum - m_minimum ) / (float)m_duration;
	value *= (float)( frame - 1 );
	value += m_minimum;
	return value > m_maximum ? m_maximum : value;
}

class Gen00458400Result
{
public:
	char m_pad00[ 0x58 ];
	float m_first;
	float m_second;
};

class Gen00458400
{
public:
	Gen00458270 *m_ramp;
	Gen00458400Result *m_result;

	void sample( unsigned int frame );
};

void Gen00458400::sample( unsigned int frame )
{
	Gen00458400Result *result = m_result;
	if( result != 0 )
	{
		Gen00458270 *ramp = m_ramp;
		if( ramp != 0 )
		{
			result->m_second = result->m_first = ramp->sample( frame );
		}
	}
}
