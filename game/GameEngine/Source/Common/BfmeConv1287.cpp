// Open-BFME5 conversions.
// The complete getter at 0x007E8900 is BfmeThingRF::bfmeGoRF (see
// BfmeConv908.cpp) and returns a signed decimal integer, and this matched
// caller requests the TID and PID fields before forwarding both to the
// 0x00809100 sink.  Retail's own mangled names for bfmeGoSA/bfmeGoSB take a
// BfmeThingSA* and a BfmeThingSB*, so those parameter spellings stay and the
// field lookups go through BfmeThingRF, exactly as the sibling GameNetwork
// conversions do.

class BfmeThingRF
{
public:
	void *bfmeGoRF(void *key, void *defaultValue);
};

class BfmeThingSA;

class BfmeSinkSA
{
public:
	void bfmeUseSA(int tid, int pid);
};

class BfmeHostSA
{
public:
	void bfmeGoSA(BfmeThingSA *r);
	char m_bfmePad[0x18];
	BfmeSinkSA *m_bfmeSink;
};

void BfmeHostSA::bfmeGoSA(BfmeThingSA *r)
{
	int tid = (int)(long)reinterpret_cast< BfmeThingRF * >( r )->bfmeGoRF( (void *)"TID", 0 );
	int pid = (int)(long)reinterpret_cast< BfmeThingRF * >( r )->bfmeGoRF( (void *)"PID", 0 );
	m_bfmeSink->bfmeUseSA(tid, pid);
}

class BfmeThingSB;

class BfmeSinkSB
{
public:
	void bfmeUseSB(void *a, void *b);
};

class BfmeHostSB
{
public:
	void bfmeGoSB(BfmeThingSB *r);
	char m_bfmePad[0x18];
	BfmeSinkSB *m_bfmeSink;
};

void BfmeHostSB::bfmeGoSB(BfmeThingSB *r)
{
	void *a = reinterpret_cast< BfmeThingRF * >( r )->bfmeGoRF( (void *)"TID", 0 );
	void *b = reinterpret_cast< BfmeThingRF * >( r )->bfmeGoRF( (void *)"PID", 0 );
	m_bfmeSink->bfmeUseSB(a, b);
}
