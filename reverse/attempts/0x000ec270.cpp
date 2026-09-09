// ?bfmeCheckEC@BfmeHostEC@@QAEHPAUBfmeNodeEC@@@Z
// partial score=1.00 date=2026-09-09
struct BfmeNodeEC
{
	unsigned char m_bfmeHeadEC[0x25c];
	void *m_bfme25CEC;
	void *m_bfme260EC;
};

class BfmeHostEC
{
public:
	int bfmeCheckEC(BfmeNodeEC *node);

	unsigned char m_bfmeHeadEC[0xc];
	BfmeNodeEC *m_bfme0CEC;
};

int BfmeHostEC::bfmeCheckEC(BfmeNodeEC *node)
{
	if (m_bfme0CEC == node || node->m_bfme25CEC != 0 || node->m_bfme260EC != 0)
		return 1;

	return 0;
}
