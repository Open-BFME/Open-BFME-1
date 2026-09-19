// cl: /DNDEBUG /MD /EHsc

struct VictoryXferVersion
{
	VictoryXferVersion(unsigned char value) : current(value), minimum(value) {}

	unsigned char current;
	unsigned char minimum;
};

class Xfer
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void xferVersion(VictoryXferVersion *version) = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void xferScore(unsigned int *score) = 0;
	virtual void slot28() = 0;
	virtual void xferCounter(unsigned int *counter) = 0;
};

class VictoryScoreData
{
public:
	void xfer(Xfer *xfer);

private:
	unsigned int m_unitScores[16];
	unsigned int m_buildingScores[16];
	unsigned int m_unitsLost;
	unsigned int m_buildingsLost;
};

void VictoryScoreData::xfer(Xfer *xfer)
{
	VictoryXferVersion version(1);
	xfer->xferVersion(&version);

	for (int index = 0; index < 16; ++index)
	{
		xfer->xferScore(&m_unitScores[index]);
		xfer->xferScore(&m_buildingScores[index]);
	}

	xfer->xferCounter(&m_unitsLost);
	xfer->xferCounter(&m_buildingsLost);
}
