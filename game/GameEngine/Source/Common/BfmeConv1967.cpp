struct BfmeEntryESC
{
	unsigned char m_bfmeHeadESC[0xdc];
	int m_bfmeDCESC;
	int m_bfmeE0ESC;
	int m_bfmeE4ESC;
	int m_bfmeE8ESC;
	int m_bfmeECESC;
	int m_bfmeF0ESC;
	unsigned char m_bfmeF4ESC;
	unsigned char m_bfmeF5ESC;
};

class BfmeHostESC
{
public:
	void bfmeSendESC(void *ctx, int index);
	void bfmeCallESC(void *ctx, int a, unsigned char b, int c, int d, int e, int f, unsigned char g, int h);
	void bfmeDoneESC(int index);

	unsigned char m_bfmeBodyESC[4];
};

void BfmeHostESC::bfmeSendESC(void *ctx, int index)
{
	BfmeEntryESC *entry = (BfmeEntryESC *)((char *)this + index * 0x1c);

	bfmeCallESC(ctx, entry->m_bfmeDCESC, entry->m_bfmeF5ESC, entry->m_bfmeECESC,
		entry->m_bfmeE8ESC, *(int *)((char *)this + (index + 8) * 0x1c),
		entry->m_bfmeE4ESC, entry->m_bfmeF4ESC, entry->m_bfmeF0ESC);

	bfmeDoneESC(index);
}
