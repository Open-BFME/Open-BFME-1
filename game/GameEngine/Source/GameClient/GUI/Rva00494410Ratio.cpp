// Neutral layout view of retail 0x00494410/103. The body returns an x87
// float and takes no stack arguments. The guard uses owner+0x20 bit 0 and
// owner+0x08; integer virtual results are converted for the ratio. Retail
// loads 0.0f (bytes 00 00 00 00) from VA 0x01075350 on the fallback path.
// cl: /DNDEBUG /DWIN32 /MD /EHsc

extern const float BfmeZeroRange;

class Rva00494410MetricSource
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual int getStart();
	virtual int getEnd();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual bool suppressRatio();
	virtual void slot14();
	virtual void slot15();
	virtual int getTotal();
};

class Rva00494410RatioOwner
{
public:
	float getRatio();

private:
	unsigned char m_padding0[0x08];
	Rva00494410MetricSource *m_source;
	unsigned char m_padding0C[0x14];
	unsigned char m_state;
};

float Rva00494410RatioOwner::getRatio()
{
	if ((m_state & 1) != 0 && m_source != 0 && !m_source->suppressRatio()) {
		int range = m_source->getEnd() - m_source->getStart();
		return (float)range / (float)m_source->getTotal();
	}

	return BfmeZeroRange;
}
