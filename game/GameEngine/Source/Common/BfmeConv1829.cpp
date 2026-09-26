int __cdecl bfmeComputeQW(void *item);

class BfmeSinkQW
{
public:
	virtual void bfmeV0QW(void);
	virtual void bfmeV1QW(void);
	virtual void bfmeV2QW(void);
	virtual void bfmeV3QW(void);
	virtual void bfmeV4QW(void);
	virtual void bfmeV5QW(void);
	virtual void bfmeV6QW(void);
	virtual void bfmeV7QW(void);
	virtual void bfmeV8QW(void);
	virtual void bfmeV9QW(void);
	virtual void bfmeV10QW(void);
	virtual void bfmeV11QW(void);
	virtual void bfmeV12QW(void);
	virtual void bfmeV13QW(void);
	virtual void bfmeV14QW(void);
	virtual void bfmeV15QW(void);
	virtual void bfmeV16QW(void);
	virtual void bfmeV17QW(void);
	virtual void bfmeV18QW(void);
	virtual void bfmeV19QW(void);
	virtual void bfmeV20QW(void);
	virtual void bfmeV21QW(void);
	virtual void bfmeV22QW(void);
	virtual void bfmeV23QW(void);
	virtual void bfmeV24QW(void);
	virtual void bfmeV25QW(void);
	virtual void bfmeV26QW(void);
	virtual void bfmeV27QW(void);
	virtual void bfmeV28QW(void);
	virtual void bfmeV29QW(void);
	virtual void bfmeV30QW(void);
	virtual void bfmeV31QW(void);
	virtual void bfmeV32QW(void);
	virtual void bfmeV33QW(void);
	virtual void bfmeV34QW(void);
	virtual void bfmeV35QW(void);
	virtual void bfmeV36QW(void);
	virtual void bfmeV37QW(void);
	virtual void bfmeV38QW(void);
	virtual void bfmeV39QW(void);
	virtual void bfmeV40QW(void);
	virtual void bfmeV41QW(void);
	virtual void bfmeV42QW(void);
	virtual void bfmeV43QW(void);
	virtual void bfmeApplyQW(void *token, float amount, int value);
};

class BfmeOwnerQW
{
public:
	void bfmeUpdateQW(int amount, void *item);

	unsigned char m_bfmeHeadQW[0x20];
	BfmeSinkQW *m_bfmeSinkQW;
	void *m_bfmeTokenQW;
	int m_bfmeValueQW;
	int m_bfmeLastQW;
};

void BfmeOwnerQW::bfmeUpdateQW(int amount, void *item)
{
	int value = bfmeComputeQW(item);
	BfmeSinkQW *sink = m_bfmeSinkQW;

	if (sink == 0)
		return;

	void *token = m_bfmeTokenQW;

	if (token == 0)
		return;

	if (m_bfmeLastQW == amount && m_bfmeValueQW == value)
		return;

	m_bfmeValueQW = value;
	m_bfmeLastQW = amount;

	sink->bfmeApplyQW(token, (float)amount, value);
}
