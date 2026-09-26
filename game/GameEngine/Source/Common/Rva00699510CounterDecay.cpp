class Rva00699510
{
public:
	void decayCounters();

private:
	char m_head[ 0x188 ];
	signed char m_counters[ 6 ][ 8 ];
};

void Rva00699510::decayCounters()
{
	signed char *counter = &m_counters[ 0 ][ 2 ];
	int row = 6;

	do
	{
		int group = 2;

		do
		{
			if ( counter[ -2 ] > 0 )
				--counter[ -2 ];
			if ( counter[ -1 ] > 0 )
				--counter[ -1 ];
			if ( counter[ 0 ] > 0 )
				--counter[ 0 ];
			if ( counter[ 1 ] > 0 )
				--counter[ 1 ];

			counter += 4;
		}
		while ( --group != 0 );
	}
	while ( --row != 0 );
}
