// cl: /O2 /Ob0

struct BfmeResultA
{
	void *m_value;
	BfmeResultA();
	BfmeResultA(const BfmeResultA &that);
	~BfmeResultA();
};

class BfmeResultSourceA
{
public:
	BfmeResultA bfmeMakeResultA(int value);
};

class BfmeResultForwardA
{
	char m_pad[0x0C];
	BfmeResultSourceA *m_source;

public:
	BfmeResultA bfmeForwardResultA();
};

class BfmeResultForwardB
{
	char m_pad[0x0C];
	BfmeResultSourceA *m_source;

public:
	BfmeResultA bfmeForwardResultB(int value);
};

BfmeResultA BfmeResultForwardA::bfmeForwardResultA()
{
	return m_source->bfmeMakeResultA(0);
}

BfmeResultA BfmeResultForwardB::bfmeForwardResultB(int value)
{
	return m_source->bfmeMakeResultA(value);
}
