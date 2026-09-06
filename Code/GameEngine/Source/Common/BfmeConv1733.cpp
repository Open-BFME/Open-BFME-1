class BfmeTagZB
{
public:
	BfmeTagZB() { m_bfmeTagZB = 0; }
	BfmeTagZB(const BfmeTagZB &other) throw() { m_bfmeTagZB = other.m_bfmeTagZB; }
	~BfmeTagZB();

	int m_bfmeTagZB;
};

void __cdecl bfmeSendZB(void *first, void *second, void *third, BfmeTagZB tag);

void __cdecl bfmeMakeZB(void *first, void *second, void *third)
{
	bfmeSendZB(first, second, third, BfmeTagZB());
}
