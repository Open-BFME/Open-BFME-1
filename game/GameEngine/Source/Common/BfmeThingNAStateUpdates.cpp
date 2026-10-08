// cl: /DNDEBUG /MD /EHsc

class Coord2D;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
class Region2D
{
public:
	bool isInside(const Coord2D &point) const;

private:
	unsigned char m_data[0x14];
};

class LivingWorldSound { public: void Rva0061C060(void); };	// 0x0061C060 via ILT 0x00002C2A
class BfmeThingJZ { public: void bfmeGoJZ(void); };		// 0x0061BB50 via ILT 0x0003AFE4
#define bfmeOneNA() ((LivingWorldSound *)this)->Rva0061C060()
#define bfmeTwoNA() ((BfmeThingJZ *)this)->bfmeGoJZ()

class BfmeThingNA
{
public:
	void bfmeApplyNA(void);
	void bfmeUpdateBNA(void);
	void bfmeUpdateDNA(void);
	void bfmeResetStateNA(void);
	void bfmeUpdateBFromPointNA(const Coord2D &point);
	void bfmeUpdateBFromPointGuardedNA(const Coord2D &point);

private:
	char m_bfmePad[0x18];
	unsigned int m_bfmeBits;
	Region2D m_bfmeRegion;
	unsigned char m_bfmeC;
	unsigned char m_bfmeB;
	unsigned char m_bfmeD;
};

void BfmeThingNA::bfmeUpdateBFromPointGuardedNA(const Coord2D &point)
{
	unsigned int bits = m_bfmeBits;

	if (bits & 2)
		m_bfmeB = 0;
	else if (!(bits & 5))
		m_bfmeB = 1;
	else
	{
		m_bfmeB = m_bfmeRegion.isInside(point);
		if (m_bfmeB && (bits & 4))
			return;
	}

	if (m_bfmeB)
	{
		if (m_bfmeD)
		{
			if (bits & 0x10)
				if (m_bfmeC)
					return;

			bfmeOneNA();
			return;
		}
	}

	if (!(bits & 0x20))
		bfmeTwoNA();
}

void BfmeThingNA::bfmeUpdateBFromPointNA(const Coord2D &point)
{
	unsigned int bits = m_bfmeBits;

	if (bits & 2)
		m_bfmeB = 0;
	else if (!(bits & 5))
		m_bfmeB = 1;
	else
		m_bfmeB = m_bfmeRegion.isInside(point);

	if (m_bfmeB)
	{
		if (m_bfmeD)
		{
			if (bits & 0x10)
				if (m_bfmeC)
					return;

			bfmeOneNA();
			return;
		}
	}

	if (!(bits & 0x20))
		bfmeTwoNA();
}

void BfmeThingNA::bfmeResetStateNA(void)
{
	unsigned int bits = m_bfmeBits;
	unsigned char zero = 0;
	m_bfmeC = zero;

	if (!(bits & 5))
		m_bfmeB = 1;
	else
		m_bfmeB = zero;

	if (bits & 8)
		m_bfmeD = zero;
	else
		m_bfmeD = 1;

	if (m_bfmeB && m_bfmeD)
	{
		bfmeOneNA();
		return;
	}

	if (!(bits & 0x20))
		bfmeTwoNA();
}

void BfmeThingNA::bfmeUpdateBNA(void)
{
	unsigned int bits = m_bfmeBits;
	if (!(bits & 5))
		m_bfmeB = 1;
	else
		m_bfmeB = 0;

	if (m_bfmeB)
	{
		if (m_bfmeD)
		{
			if (bits & 0x10)
				if (m_bfmeC)
					return;

			bfmeOneNA();
			return;
		}
	}

	if (!(bits & 0x20))
		bfmeTwoNA();
}

void BfmeThingNA::bfmeUpdateDNA(void)
{
	unsigned int bits = m_bfmeBits;
	if (bits & 8)
		m_bfmeD = 0;
	else
		m_bfmeD = 1;

	if (m_bfmeB)
	{
		if (m_bfmeD)
		{
			if (bits & 0x10)
				if (m_bfmeC)
					return;

			bfmeOneNA();
			return;
		}
	}

	if (!(bits & 0x20))
		bfmeTwoNA();
}

void BfmeThingNA::bfmeApplyNA(void)
{
	if (m_bfmeB)
	{
		if (m_bfmeD)
		{
			if (m_bfmeBits & 0x10)
				if (m_bfmeC)
					return;

			bfmeOneNA();
			return;
		}
	}

	if (!(m_bfmeBits & 0x20))
		bfmeTwoNA();
}
