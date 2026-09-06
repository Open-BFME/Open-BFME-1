// ?bfmeGoFL@BfmeFinderFL@@QAEXPAX0@Z (identity unknown)
// partial score=0.97 date=2026-09-06
// 30/30, exact size; two instructions differ only in which register carries the
// intermediate node: retail mov ecx,[eax] / mov ecx,[ecx+8], MSVC mov eax,[eax] /
// mov ecx,[eax+8]. Pin: ?bfmeLookupFL@BfmeItemFL@@QAEPAVBfmeResultFL@@XZ 0x0000B3E3
class BfmeResultFL
{
public:
	virtual void bfmeApplyFL(void *first, void *second);
};

class BfmeItemFL
{
public:
	BfmeResultFL *bfmeLookupFL(void);
};

class BfmeNodeFL
{
public:
	BfmeNodeFL *volatile m_bfmeNextFL;
	unsigned char m_bfmeMidFL[4];
	BfmeItemFL *m_bfmeItemFL;
};

class BfmeFinderFL
{
public:
	void bfmeGoFL(void *first, void *second);

	unsigned char m_bfmeHeadFL[4];
	BfmeNodeFL *m_bfmeListFL;
};

void BfmeFinderFL::bfmeGoFL(void *first, void *second)
{
	BfmeNodeFL *list = m_bfmeListFL;
	if (list->m_bfmeNextFL == list)
		return;

	BfmeResultFL *result = list->m_bfmeNextFL->m_bfmeItemFL->bfmeLookupFL();
	if (result == 0)
		return;

	result->bfmeApplyFL(first, second);
}
