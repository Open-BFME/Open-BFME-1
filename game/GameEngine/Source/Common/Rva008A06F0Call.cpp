// cl: /O2 /Ob0

class Rva008A06F0Inner
{
	void callee(int);

	friend class Rva008A06F0;
};

class Rva008A06F0
{
	char m_lead[0x24];
	Rva008A06F0Inner m_inner;

public:
	void run();
};

void Rva008A06F0::run()
{
	m_inner.callee(0);
}
