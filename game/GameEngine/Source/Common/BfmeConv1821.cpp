struct BfmeElemQV
{
	unsigned char m_bfmeRawQV[4];
};

class BfmeVecQV
{
public:
	void bfmeGrowQV(BfmeElemQV *where, BfmeElemQV *value, void **holder, int first, int second);

	BfmeElemQV *m_bfmeBeginQV;
	BfmeElemQV *m_bfmeEndQV;
	BfmeElemQV *m_bfmeCapQV;
};

void __cdecl bfmeConstructQV(BfmeElemQV *where, BfmeElemQV *value);

class BfmeOwnerQV
{
public:
	void bfmePushQV(void *item);

	unsigned char m_bfmeHeadQV[0x2dc];
	BfmeVecQV m_bfmeVecQV;
};

void BfmeOwnerQV::bfmePushQV(void *item)
{
	BfmeElemQV *value = (BfmeElemQV *)((char *)item + 0x20);
	BfmeVecQV *vec = &m_bfmeVecQV;

	if (vec->m_bfmeEndQV != vec->m_bfmeCapQV)
	{
		bfmeConstructQV(vec->m_bfmeEndQV, value);

		vec->m_bfmeEndQV = vec->m_bfmeEndQV + 1;
	}
	else
		vec->bfmeGrowQV(vec->m_bfmeEndQV, value, &item, 1, 1);
}
