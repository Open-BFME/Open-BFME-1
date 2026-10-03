// Open-BFME5 conversions.

class BfmeSink992
{
public:
	virtual void bfmeVS0992();
	virtual void bfmeVS1992();
	virtual void bfmeVS2992();
	virtual void bfmeVS3992();
	virtual void bfmeVS4992();
	virtual void bfmeVS5992();
	virtual void bfmeVS6992();
	virtual void bfmeVS7992();
	virtual void bfmeVS8992();
	virtual void bfmeVS9992();
	virtual void bfmeVS10992();
	virtual void bfmeVS11992();
	virtual void bfmeVS12992();
	virtual void bfmeVS13992();
	virtual void bfmeVS14992();
	virtual void bfmeVS15992();
	virtual void bfmeVS16992();
	virtual void bfmeVS17992();
	virtual void bfmeSend992C(int v);
};

class BfmeAsk992;

class W3DVideoBuffer
{
public:
	virtual bool valid(void);
};

class Gen_007e88b0
{
public:
	int m();
};

class BfmeC992
{
public:
	void bfmeGo992C(BfmeAsk992 *a);

	char m_bfmePad[0x1c];
	BfmeSink992 *m_bfmeSink;
};

void BfmeC992::bfmeGo992C(BfmeAsk992 *a)
{
	if (((W3DVideoBuffer *)a)->W3DVideoBuffer::valid()) {
		int v = ((Gen_007e88b0 *)a)->m();

		m_bfmeSink->bfmeSend992C(v);
	} else {
		m_bfmeSink->bfmeSend992C(0);
	}
}
