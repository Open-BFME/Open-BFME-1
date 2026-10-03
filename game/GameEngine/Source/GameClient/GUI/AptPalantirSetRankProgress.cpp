extern const float g_rva01075350;

class Rva00563E60
{
public:
	static void go();
};

class Rva00563E90
{
public:
	static void go();
};

extern void bfmeGo1070B( float value );

class AptPalantir
{
public:
	void setRankProgress( float value );

private:
	unsigned char m_unmodelled00[ 0x10 ];
	float m_rankProgress;
};

void AptPalantir::setRankProgress( float value )
{
	unsigned char wasVisible = m_rankProgress >= g_rva01075350;

	if( value >= g_rva01075350 )
	{
		if( !wasVisible )
			Rva00563E60::go();
		bfmeGo1070B( value );
		m_rankProgress = value;
	}
	else
	{
		if( wasVisible )
		{
			Rva00563E90::go();
			m_rankProgress = value;
			return;
		}
		m_rankProgress = value;
	}
}
