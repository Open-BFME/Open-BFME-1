// Open-BFME5 conversions.

struct BfmeOwner955
{
	char m_bfmePad[0x2bc];
	int *m_bfmeBegin;
	int *m_bfmeEnd;
};

class BfmeIter955
{
public:
	virtual void bfmeV0955();
	virtual void bfmeV1955();
	virtual void bfmeV2955();
	virtual void bfmeV3955();
	virtual void bfmeV4955();
	virtual void bfmeV5955();
	virtual void bfmeV6955();
	virtual void bfmeV7955();
	virtual void bfmeV8955();
	virtual void bfmeV9955();
	virtual void bfmeV10955();
	virtual void bfmeV11955();
	virtual void bfmeV12955();
	virtual void bfmeV13955();
	virtual void bfmeV14955();
	virtual void bfmeV15955();
	virtual void bfmeV16955();
	virtual void bfmeV17955();
	virtual void bfmeV18955();
	virtual void bfmeV19955();
	virtual void bfmeV20955();
	virtual void bfmeV21955();
	virtual void bfmeV22955();
	virtual void bfmeV23955();
	virtual void bfmeV24955();
	virtual void bfmeV25955();
	virtual void bfmeV26955();
	virtual void bfmeV27955();
	virtual void bfmeV28955();
	virtual void bfmeV29955();
	virtual void bfmeV30955();
	virtual void bfmeV31955();
	virtual void bfmeV32955();
	virtual void bfmeV33955();
	virtual void bfmeV34955();
	virtual void bfmeV35955();
	virtual void bfmeV36955();
	virtual void bfmeV37955();
	virtual void bfmeV38955();
	virtual void bfmeV39955();
	virtual void bfmeV40955();
	virtual void bfmeV41955();
	virtual void bfmeV42955();
	virtual void bfmeV43955();
	virtual void bfmeV44955();
	virtual void bfmeV45955();
	virtual void bfmeV46955();
	virtual void bfmeV47955();
	virtual void bfmeV48955();
	virtual void bfmeV49955();
	virtual void bfmeV50955();
	virtual void bfmeV51955();
	virtual void bfmeV52955();
	virtual void bfmeV53955();
	virtual void bfmeV54955();
	virtual void bfmeV55955();
	virtual void bfmeV56955();
	virtual void bfmeV57955();
	virtual void bfmeV58955();
	virtual void bfmeV59955();
	virtual void bfmeV60955();
	virtual void bfmeV61955();
	virtual void bfmeV62955();
	virtual void bfmeV63955();
	virtual void bfmeV64955();
	virtual void bfmeV65955();
	virtual void bfmeV66955();
	virtual void bfmeV67955();
	virtual void bfmeV68955();
	virtual void bfmeV69955();
	virtual void bfmeV70955();
	virtual void bfmeV71955();
	virtual void bfmeV72955();
	virtual void bfmeV73955();
	virtual void bfmeV74955();
	virtual void bfmeV75955();
	virtual void bfmeV76955();
	virtual void bfmeV77955();
	virtual void bfmeV78955();
	virtual void bfmeV79955();
	virtual void bfmeV80955();
	virtual void bfmeV81955();
	virtual void bfmeV82955();
	virtual void bfmeV83955();
	virtual void bfmeV84955();
	virtual void bfmeV85955();
	virtual void bfmeV86955();
	virtual void bfmeV87955();
	virtual void bfmeV88955();
	virtual void bfmeV89955();
	virtual void bfmeV90955();
	virtual void bfmeV91955();
	virtual void bfmeV92955();
	virtual void bfmeV93955();
	virtual void bfmeV94955();
	virtual void bfmeV95955();
	virtual void bfmeV96955();
	virtual void bfmeV97955();
	virtual void bfmeV98955();
	virtual void bfmeV99955();
	virtual void bfmeV100955();
	virtual void bfmeV101955();
	virtual void bfmeV102955();
	virtual void bfmeV103955();
	virtual void bfmeV104955();
	virtual void bfmeV105955();
	virtual void bfmeV106955();
	virtual void bfmeV107955();
	virtual void bfmeVA955(int *it, int a, int b);
	virtual void bfmeVB955(int *it, int a);

	void bfmeGoA955();
	void bfmeGoB955();
};

void BfmeIter955::bfmeGoA955()
{
	BfmeOwner955 *o = *(BfmeOwner955 **)((char *)this - 0xe0);
	if (!o)
		return;

	for (int *it = o->m_bfmeBegin; it != o->m_bfmeEnd; ++it)
		bfmeVA955(it, 0, -1);
}

void BfmeIter955::bfmeGoB955()
{
	BfmeOwner955 *o = *(BfmeOwner955 **)((char *)this - 0xe0);
	if (!o)
		return;

	for (int *it = o->m_bfmeBegin; it != o->m_bfmeEnd; ++it)
		bfmeVB955(it, 0);
}

class BfmeSink955
{
public:
	void bfmeAdd955(int *it, int a);
};

class BfmeHost955
{
public:
	void bfmeGoC955(BfmeSink955 *sink);
	char m_bfmePad[4];
	BfmeOwner955 *m_bfmeOwner;
};

void BfmeHost955::bfmeGoC955(BfmeSink955 *sink)
{
	if (!sink)
		return;

	BfmeOwner955 *o = m_bfmeOwner;
	if (!o)
		return;

	for (int *it = o->m_bfmeBegin; it != o->m_bfmeEnd; ++it)
		sink->bfmeAdd955(it, -1);
}
