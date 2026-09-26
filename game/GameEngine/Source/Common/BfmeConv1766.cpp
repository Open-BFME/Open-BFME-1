class BfmeTmpCF
{
public:
	BfmeTmpCF(void);
	~BfmeTmpCF();

	void bfmeRunCF(void *first, void *second);

	unsigned char m_bfmeHeadCF[0x24];
};

void __cdecl bfmeMakeCF(void *first, void *second)
{
	BfmeTmpCF tmp;

	tmp.bfmeRunCF(first, second);
}
