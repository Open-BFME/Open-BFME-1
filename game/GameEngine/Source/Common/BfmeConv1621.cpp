// Open-BFME5 conversions.

class BfmeStrVTM
{
public:
	BfmeStrVTM(const BfmeStrVTM &other);
	char *m_bfme00;
};

struct BfmeNodeVTM
{
	BfmeNodeVTM *m_bfme00;
	int m_bfme04;
	BfmeStrVTM m_bfme08;
};

class BfmeHostVTM
{
public:
	char m_bfmePad000[0x174];
	BfmeNodeVTM *volatile m_bfme174;
};

extern BfmeStrVTM g_bfmeDefaultVTM;

class BfmeOwnVTM
{
public:
	BfmeStrVTM bfmeNameVTM();
};

BfmeStrVTM BfmeOwnVTM::bfmeNameVTM()
{
	BfmeHostVTM *host = *(BfmeHostVTM **)((char *)this - 0xe0);
	BfmeNodeVTM *head = host->m_bfme174;
	BfmeNodeVTM *node;
	int count = 0;
	volatile int scratch = 0;
	const BfmeStrVTM *source;

	for (node = head->m_bfme00; node != head; node = node->m_bfme00)
		++count;

	if (count == 1)
		source = &host->m_bfme174->m_bfme00->m_bfme08;
	else
		source = &g_bfmeDefaultVTM;

	return *source;
}
