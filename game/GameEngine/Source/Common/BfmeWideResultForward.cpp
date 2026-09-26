// cl: /O2 /Ob0

struct BfmeWideResult
{
	void *m_value;
	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &that);
	~BfmeWideResult();
};

class BfmeWideResultSource
{
public:
	BfmeWideResult bfmeMakeWideResult(int a, int b, int c, int d, int e, int f);
};

class BfmeWideForwardA
{
	char m_pad[0x0C];
	BfmeWideResultSource *m_source;

public:
	BfmeWideResult bfmeForwardWideA(int a, int b, int c, int d);
};

class BfmeWideForwardB
{
	char m_pad[0x0C];
	BfmeWideResultSource *m_source;

public:
	BfmeWideResult bfmeForwardWideB(int a, int b, int c, int d);
};

class BfmeWideForwardC
{
	char m_pad[0x0C];
	BfmeWideResultSource *m_source;

public:
	BfmeWideResult bfmeForwardWideC(int a, int b, int c, int d, int e);
};

BfmeWideResult BfmeWideForwardA::bfmeForwardWideA(int a, int b, int c, int d)
{
	return m_source->bfmeMakeWideResult(a, b, 0, c, 0, d);
}

BfmeWideResult BfmeWideForwardB::bfmeForwardWideB(int a, int b, int c, int d)
{
	return m_source->bfmeMakeWideResult(0, 0, a, b, c, d);
}

BfmeWideResult BfmeWideForwardC::bfmeForwardWideC(int a, int b, int c, int d, int e)
{
	return m_source->bfmeMakeWideResult(a, b, 0, c, d, e);
}
