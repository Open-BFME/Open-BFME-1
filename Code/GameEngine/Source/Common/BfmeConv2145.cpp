class BfmeRecXZ
{
public:
	unsigned char m_bfmeHeadXZ[0x20];
	int m_bfme20XZ;
	unsigned char m_bfmeMidXZ[0x34 - 0x24];
	int m_bfme34XZ;
};

class BfmePoolXZ
{
public:
	BfmeRecXZ *bfmeTakeXZ(int a);
};

class BfmeSinkXZ
{
public:
	virtual void bfmeV00XZ();
	virtual void bfmeV04XZ();
	virtual void bfmeV08XZ();
	virtual void bfmeV0CXZ();
	virtual void bfmeV10XZ();
	virtual void bfmeBeginXZ();
	virtual void bfmeV18XZ();
	virtual void bfmeV1CXZ();
	virtual void bfmeMarkXZ(int code);
	virtual void bfmeV24XZ();
	virtual void bfmeV28XZ();
	virtual void bfmeV2CXZ();
	virtual void bfmeV30XZ();
	virtual void bfmeV34XZ();
	virtual void bfmeEmitXZ(void *item);
};

class BfmeHostXZ
{
public:
	void bfmeSendXZ(void *item, int kind);
	void bfmeFinishXZ(void *item);

	unsigned char m_bfmeHeadXZ[8];
	BfmePoolXZ *m_bfme08XZ;
	unsigned char m_bfmeMidXZ[0x30 - 0xc];
	BfmeSinkXZ *m_bfme30XZ;
	unsigned char m_bfmeTailXZ[0x48 - 0x34];
	int m_bfme48XZ;
};

void BfmeHostXZ::bfmeSendXZ(void *item, int kind)
{
	if (item == 0)
		return;

	m_bfme30XZ->bfmeBeginXZ();
	m_bfme30XZ->bfmeEmitXZ(item);

	m_bfme48XZ = kind;

	m_bfme30XZ->bfmeMarkXZ(0x2e);

	BfmeRecXZ *rec = m_bfme08XZ->bfmeTakeXZ(0);

	if (rec != 0)
	{
		rec->m_bfme34XZ = 1;
		rec->m_bfme20XZ = 0;
	}

	if (kind == 0 || kind == 1)
		bfmeFinishXZ(item);
}
