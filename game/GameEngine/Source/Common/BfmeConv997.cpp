// Open-BFME5 conversions.

class BfmeClock997
{
public:
	virtual void bfmeV0997();
	virtual void bfmeV1997();
	virtual void bfmeV2997();
	virtual void bfmeV3997();
	virtual void bfmeV4997();
	virtual void bfmeV5997();
	virtual void bfmeV6997();
	virtual void bfmeV7997();
	virtual void bfmeV8997();
	virtual void bfmeV9997();
	virtual void bfmeV10997();
	virtual void bfmeV11997();
	virtual void bfmeV12997();
	virtual void bfmeV13997();
	virtual void bfmeV14997();
	virtual void bfmeV15997();
	virtual void bfmeV16997();
	virtual void bfmeV17997();
	virtual void bfmeV18997();
	virtual void bfmeV19997();
	virtual void bfmeV20997();
	virtual void bfmeV21997();
	virtual void bfmeV22997();
	virtual void bfmeV23997();
	virtual void bfmeV24997();
	virtual void bfmeV25997();
	virtual int bfmeNow997();
};

// The global is declared by its defining spelling so the object references
// ?TheGameClient@@3PAVGameClient@@A (dir32 0x012F1464, the same pointer
// BfmeClock997 above is a local slot view of).  BfmeClock997 stays as the
// vtable view the three bfmeNow997() calls need.
class GameClient;
extern GameClient *TheGameClient;

// retail reaches 0x00411CD0 through ILT 0x200D1
extern void j_000200d1();

class BfmeA997
{
public:
	void bfmeGo997A(int a);
	void bfmeGo997B(int a);
	void bfmeGo997C(int a, int b);

	char m_bfmePad[0x124];
	int m_bfmeMode;
	int m_bfmeZero;
	int m_bfmeArgA;
	int m_bfmeArgB;
	char m_bfmePad2[0x1d4];
	int m_bfmeStamp;
	char m_bfmePad3[0xa1];
	char m_bfmeOn;
};

void BfmeA997::bfmeGo997A(int a)
{
	if (m_bfmeOn) {
		m_bfmeOn = 0;
		union { void (*fn)(); void (BfmeA997::*call)(); } toggle = { j_000200d1 };
		(this->*toggle.call)();
	}

	m_bfmeMode = 4;
	m_bfmeArgA = a;
	m_bfmeZero = 0;
	m_bfmeStamp = reinterpret_cast<BfmeClock997 *>(TheGameClient)->bfmeNow997();
}

void BfmeA997::bfmeGo997B(int a)
{
	if (m_bfmeOn != 1) {
		m_bfmeOn = 1;
		union { void (*fn)(); void (BfmeA997::*call)(); } toggle = { j_000200d1 };
		(this->*toggle.call)();
	}

	m_bfmeMode = 3;
	m_bfmeArgA = a;
	m_bfmeZero = 0;
	m_bfmeStamp = reinterpret_cast<BfmeClock997 *>(TheGameClient)->bfmeNow997();
}

void BfmeA997::bfmeGo997C(int a, int b)
{
	if (m_bfmeOn != 1) {
		m_bfmeOn = 1;
		union { void (*fn)(); void (BfmeA997::*call)(); } toggle = { j_000200d1 };
		(this->*toggle.call)();
	}

	m_bfmeMode = 5;
	m_bfmeArgA = a;
	m_bfmeArgB = b;
	m_bfmeZero = 0;
	m_bfmeStamp = reinterpret_cast<BfmeClock997 *>(TheGameClient)->bfmeNow997();
}
