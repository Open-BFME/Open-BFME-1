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

// Retail 0x00588890 (50 B): file-static percentage of the value behind owner+0x200,
// scaled and rounded, clamped to 0..100 and 100 when absent. The owner arrives in EAX
// through MSVC's private static convention; owner and value types are address-named.
// Retail percentage helper +0x0f multiplies by VA 0x0107FAC4, whose
// four bytes 00 00 C8 42 establish 100.0f. Own the existing global once.
// BFME 2 aa505f34 has no matching provider spelling; no donor datum used.
float g_bfmeScaleBC = 100.0f;
extern const float g_rva0107533C;

class Rva00588890Value
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual float slot14();
};

class Rva00588890Owner
{
public:
	unsigned char m_unmodelled000[0x200];
	Rva00588890Value *m_value200;
};

static int rva00588890(const Rva00588890Owner *owner)
{
	Rva00588890Value *value = owner->m_value200;
	if (value)
	{
		int percent = (int)(value->slot14() * g_bfmeScaleBC + g_rva0107533C);
		if (percent > 100)
			percent = 100;
		else if (percent < 0)
			percent = 0;
		return percent;
	}
	return 100;
}

// absent-from-retail: TU-local caller that keeps the static above alive.
int rva00588890Caller(const Rva00588890Owner *owner)
{
	return rva00588890(owner);
}
