typedef float Real;

extern const Real BfmeZeroRange;

class BfmeRangeEQI
{
public:
	virtual void bfmeSlot0EQI(void);
	virtual void bfmeSlot1EQI(void);
	virtual void bfmeSlot2EQI(void);
	virtual void bfmeSlot3EQI(void);
	virtual void bfmeSlot4EQI(void);
	virtual void bfmeSlot5EQI(void);
	virtual char bfmeReadyEQI(void);
	Real bfmeRatioEQI(void);

	char m_bfmeHeadEQI[8];
	unsigned int m_bfmeNumEQI;
	char m_bfmeMidEQI[4];
	unsigned int m_bfmeDenEQI;
};

Real BfmeRangeEQI::bfmeRatioEQI(void)
{
	if (bfmeReadyEQI())
		return (Real)m_bfmeNumEQI / (Real)m_bfmeDenEQI;
	return BfmeZeroRange;
}

class BfmeSpanEQJ
{
public:
	virtual void bfmeSlot0EQJ(void);
	virtual void bfmeSlot1EQJ(void);
	virtual void bfmeSlot2EQJ(void);
	virtual void bfmeSlot3EQJ(void);
	virtual void bfmeSlot4EQJ(void);
	virtual void bfmeSlot5EQJ(void);
	virtual char bfmeReadyEQJ(void);
	Real bfmeRatioEQJ(void);

	char m_bfmeHeadEQJ[0xc];
	unsigned int m_bfmeNumEQJ;
	char m_bfmeMidEQJ[4];
	unsigned int m_bfmeDenEQJ;
};

Real BfmeSpanEQJ::bfmeRatioEQJ(void)
{
	if (bfmeReadyEQJ())
		return (Real)m_bfmeNumEQJ / (Real)m_bfmeDenEQJ;
	return BfmeZeroRange;
}
