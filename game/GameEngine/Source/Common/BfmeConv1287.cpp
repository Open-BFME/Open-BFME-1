// Open-BFME5 conversions.
// The complete getter at 0x007E8900 returns a signed decimal integer, and this
// matched caller requests the TID and PID fields before forwarding both to the
// 0x00809100 sink.  The older void-pointer declarations preserved the same
// 32-bit machine ABI but did not describe the values the retail code handles.

class BfmeThingSA
{
public:
	int bfmeGetSA(const char *key, int fallback);
};

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
	int tid = r->bfmeGetSA("TID", 0);
	int pid = r->bfmeGetSA("PID", 0);
	m_bfmeSink->bfmeUseSA(tid, pid);
}

class BfmeThingSB
{
public:
	void *bfmeGetSB(void *a, void *b);
};

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
	void *a = r->bfmeGetSB((void *)"TID", 0);
	void *b = r->bfmeGetSB((void *)"PID", 0);
	m_bfmeSink->bfmeUseSB(a, b);
}
