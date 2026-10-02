// Open-BFME5 conversions.

void bfmeReset1050(int n);

class BfmeA1050
{
public:
	void bfmeGo1050A(void);

	char m_bfmePad[8];
	int m_bfme08;
	char m_bfmePad2[0x55];
	char m_bfmeFlag;
	char m_bfmePad3[0xc6];
	int m_bfme128;
};

void BfmeA1050::bfmeGo1050A(void)
{
	m_bfmeFlag = 0;
	bfmeReset1050(0);
	m_bfme08 = 0;
	m_bfme128 = 0;
}

extern "C" void *bfmeVft1050B[];

class BfmeB1050
{
public:
	BfmeB1050 *bfmeGo1050B(void);
	void bfmeBase1050(void);

	void *m_bfmeVfptr;
	char m_bfmePad[0x54];
	int m_bfme58;
	int m_bfme5c;
	float m_bfme60;
	char m_bfme64;
};

BfmeB1050 *BfmeB1050::bfmeGo1050B(void)
{
	bfmeBase1050();

	int z = 0;

	m_bfme58 = z;
	m_bfme5c = z;
	m_bfme64 = (char)z;
	m_bfme60 = 20.0f;
	m_bfmeVfptr = bfmeVft1050B;
	return this;
}

class BfmeP1050
{
public:
	void *bfmeFwd1050(int a, int b, int c, int d, int e);
};

class BfmeC1050
{
public:
	void *bfmeGo1050C(int a, int b, int c, int d, int e);
	void *bfmeGo1050D(int a, int b, int c, int d);
	void bfmeGo009F26D0(int a, int b, int c, int d);
	void *bfmeGo009F2680(int a, int b, int c);

	char m_bfmePad[0xc];
	BfmeP1050 *m_bfmeP;
};

// retail 0x009F2700, 36 bytes, five stack args and ret 0x14.  Same shape as
// 0x009F26A0: five pushes, call 0x009F5C00, then ret with nothing in between
// writing EAX, and the inner epilogue loads the accepted candidate into EAX at
// 0x009F63B7, so the query's pointer reaches the caller in EAX.
// ?bfmeGo1050C@BfmeC1050@@QAEPAXHHHHH@Z
// The only direct retail call site is 0x0014DEE1 in the matched body
// 0x0014DAB0, and it consumes EAX twice: 0x0014DEE6 cmp eax,edi and
// 0x0014DEED mov ecx,eax before the Object call at 0x0014DEEF, with
// 0x0014DEF6 xor eax,eax on the null path.
void *BfmeC1050::bfmeGo1050C(int a, int b, int c, int d, int e)
{
	return m_bfmeP->bfmeFwd1050(a, c, b, d, e);
}

// retail 0x009F26A0: same inner at +0xC, same callee 0x009F5C00, four args
// with an explicit 0 in the third slot.  ?bfmeGo1050D@BfmeC1050@@QAEPAXHHHH@Z
// The 0x009F5C00 body leaves the accepted candidate in EAX before its
// ret 0x14 and this wrapper touches no register after the call, so the
// query's pointer reaches the caller in EAX.  The demonstrated readers are in
// body 0x003DCBA0: 0x003DCC0C stores EAX, 0x003DCC0E and 0x003DCC9F test it
// and 0x003DCCAB compares it.  0x009F26A0 has 91 direct retail call sites and
// no claim is made here about the ones not read individually.
void *BfmeC1050::bfmeGo1050D(int a, int b, int c, int d)
{
	return m_bfmeP->bfmeFwd1050(a, b, 0, c, d);
}

void BfmeC1050::bfmeGo009F26D0(int a, int b, int c, int d)
{
	m_bfmeP->bfmeFwd1050(a, c, b, d, 0);
}

// retail 0x009F2680 (30 bytes), directly before 0x009F26A0 and unclaimed until
// now: three stack args and ret 0xC, the same inner at +0xC and callee
// 0x009F5C00 with zeros in the third and fifth slots; EAX is untouched after
// the call.  16-aligned after int3 padding, int3 after the ret, no callers.
void *BfmeC1050::bfmeGo009F2680(int a, int b, int c)
{
	return m_bfmeP->bfmeFwd1050(a, b, 0, c, 0);
}

extern "C" void *bfmeVft1050F[];

class BfmeF1050
{
public:
	BfmeF1050 *bfmeGo1050F(int a, int b, int c);
	void bfmeBaseF1050(int a, int b, int c);

	void *m_bfmeVfptr;
};

BfmeF1050 *BfmeF1050::bfmeGo1050F(int a, int b, int c)
{
	bfmeBaseF1050(a, b, c);
	m_bfmeVfptr = bfmeVft1050F;
	return this;
}

