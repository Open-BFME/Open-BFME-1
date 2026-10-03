// Open-BFME5 conversions.

// The release the sink teardown calls is the record teardown at 0x008068B0,
// whose body is Libraries/Source/DirtySock/Y2Rva00806580Module.cpp.  Retail
// passes the item pointer and ignores the returned count.
struct Rva00806580Record;
int Rva008068B0(Rva00806580Record *record);

// The four-int box setter retail reaches through the ILT thunk 0x000297C6 is
// Rva00494380::set (0x00494380), whose body is Common/Rva00494380Set.cpp; the
// class is declared there exactly as here, with only the member left undefined.
class Rva00494380
{
	char m_pad[0x0C];
	int m_0C;
	int m_10;
	int m_14;
	int m_18;

public:
	void set(int a, int b, int c, int d);
};

struct BfmeVecTMA
{
	float m_bfmeX;
	float m_bfmeY;
	float m_bfmeZ;
};

class BfmeSubTMA
{
public:
	virtual void bfmeV0TMA() = 0;
	virtual void bfmeV1TMA() = 0;
	virtual void bfmeV2TMA() = 0;
	virtual void bfmeV3TMA() = 0;
	virtual void bfmeV4TMA() = 0;
	virtual void bfmeV5TMA() = 0;
	virtual void bfmeV6TMA() = 0;
	virtual void bfmeV7TMA() = 0;
	virtual void bfmeV8TMA() = 0;
	virtual void bfmeV9TMA() = 0;
	virtual void bfmeV10TMA() = 0;
	virtual void bfmeV11TMA() = 0;
	virtual void bfmeV12TMA() = 0;
	virtual void bfmeV13TMA() = 0;
	virtual void bfmeV14TMA() = 0;
	virtual void bfmeV15TMA() = 0;
	virtual void bfmeV16TMA() = 0;
	virtual void bfmeV17TMA() = 0;
	virtual void bfmeV18TMA() = 0;
	virtual void bfmeV19TMA() = 0;
	virtual void bfmeUpdateTMA() = 0;
	char m_bfmePad[0x20];
	float m_bfmeX;
	char m_bfmePad2[0xc];
	float m_bfmeY;
	char m_bfmePad3[0xc];
	float m_bfmeZ;
};

class BfmeThingTMA
{
public:
	void bfmeGoTMA(BfmeVecTMA *out);
	char m_bfmePad[8];
	BfmeSubTMA *m_bfmeSub;
};

void BfmeThingTMA::bfmeGoTMA(BfmeVecTMA *out)
{
	BfmeSubTMA *s = m_bfmeSub;
	if (s) {
		s->bfmeUpdateTMA();
		float x = *(volatile float *)&s->m_bfmeX;
		float y = s->m_bfmeY;
		float z = s->m_bfmeZ;
		out->m_bfmeX = x;
		out->m_bfmeY = y;
		out->m_bfmeZ = z;
	}
}

class BfmeSinkTMB
{
public:
	virtual void bfmeV0TMB() = 0;
	virtual void bfmeStopTMB() = 0;
};

class BfmeThingTMB
{
public:
	void bfmeGoTMB();
	char m_bfmePad[4];
	BfmeSinkTMB *m_bfmeSink;
	void *m_bfmeItem;
	int m_bfmeCount;
	char m_bfmeFlag;
};

void BfmeThingTMB::bfmeGoTMB()
{
	char f = m_bfmeFlag;
	m_bfmeCount = 0;
	if (f) {
		m_bfmeFlag = 0;
		m_bfmeSink->bfmeStopTMB();
	}
	Rva008068B0(reinterpret_cast<Rva00806580Record *>(m_bfmeItem));
}

class BfmeBoxTMC
{
public:
	virtual void bfmeV0TMC();
	virtual void bfmeV1TMC();
	virtual void bfmeV2TMC();
	virtual void bfmeV3TMC();
	virtual void bfmeV4TMC();
	virtual void bfmeV5TMC();
	virtual void bfmeV6TMC();
	virtual void bfmeApplyTMC();
};

class BfmeThingTMC
{
public:
	int bfmeGoTMC(int unused);
	char m_bfmePad[0x14];
	int m_bfmeLeft;
	int m_bfmeTop;
	int m_bfmeRight;
	int m_bfmeBottom;
	char m_bfmePad2[0x1f4];
	BfmeBoxTMC m_bfmeBox;
};

int BfmeThingTMC::bfmeGoTMC(int unused)
{
	reinterpret_cast<Rva00494380 *>(&m_bfmeBox)->set(m_bfmeLeft, m_bfmeTop, m_bfmeRight, m_bfmeBottom);
	m_bfmeBox.bfmeApplyTMC();
	return 1;
}

class BfmeThingTMD
{
public:
	void bfmeGoTMD(int x, int y, int w, int h);
	char m_bfmePad[0x10];
	BfmeBoxTMC *m_bfmeBox;
};

void BfmeThingTMD::bfmeGoTMD(int x, int y, int w, int h)
{
	reinterpret_cast<Rva00494380 *>(m_bfmeBox)->set(x, y, x + w, y + h);
	m_bfmeBox->bfmeApplyTMC();
}
