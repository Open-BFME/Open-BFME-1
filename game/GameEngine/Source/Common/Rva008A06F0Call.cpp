// cl: /O2 /Ob0

// Retail calls 0x008BDD70 directly: the matched
// bfmeReset1046@BfmeD1046@@QAEXH@Z row in Rva008BDD70ResetList.cpp.
class BfmeD1046
{
public:
	void bfmeReset1046(int n);
};

typedef BfmeD1046 Rva008A06F0Inner;

class Rva008A06F0
{
	char m_lead[0x24];
	Rva008A06F0Inner m_inner;

public:
	void run();
};

void Rva008A06F0::run()
{
	m_inner.bfmeReset1046(0);
}
