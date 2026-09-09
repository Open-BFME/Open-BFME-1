// ?d_0018cf10@@YAXXZ
// partial score=0.82 date=2026-09-09
// ?bfmeGoBDA@Gen_0018CF10@@QAEXPAX@Z
struct BfmeSubBDA
{
	char m_bfmeBytes[1];
};

void __stdcall bfmeDoBDA(BfmeSubBDA *sub, void *item);	// retail 0x0002CEEE

class Gen_0018CF10
{
public:
	void bfmeGoBDA(void *item);

private:
	char m_bfmeHead[0x38];
	BfmeSubBDA m_bfmeSub;
};

void Gen_0018CF10::bfmeGoBDA(void *item)
{
	bfmeDoBDA(&m_bfmeSub, item);
}
