class BfmeNodeNY;

class BfmeTableNY
{
public:
	void bfmeFindNY(BfmeNodeNY **found, void **key);

	BfmeNodeNY *m_bfmeEndNY;
};

class BfmeItemNY
{
public:
	unsigned char m_bfmeHeadNY[0x74];
	void *m_bfmeKeyNY;
	unsigned char m_bfmeGapNY[0x19c];
	int m_bfmeKindNY;
};

class BfmeOwnerNY
{
public:
	char bfmeCheckNY(void *item);

	unsigned char m_bfmeHeadNY[0x30];
	BfmeTableNY m_bfmeTableNY;
};

char BfmeOwnerNY::bfmeCheckNY(void *item)
{
	if (((BfmeItemNY *)item)->m_bfmeKindNY == *(int *)((char *)this - 0xdc))
		return 1;

	item = ((BfmeItemNY *)item)->m_bfmeKeyNY;

	BfmeNodeNY *found;

	m_bfmeTableNY.bfmeFindNY(&found, &item);

	return found != m_bfmeTableNY.m_bfmeEndNY;
}
