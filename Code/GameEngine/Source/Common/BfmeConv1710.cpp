class BfmeItemGB;

class BfmeSubGB
{
public:
	void bfmeInsertGB(BfmeItemGB *item, int mode);

	unsigned char m_bfmeSubDataGB[4];
};

class BfmeListGB
{
public:
	char bfmeContainsGB(BfmeItemGB *item);

	unsigned char m_bfmeHeadGB[0x20];
	BfmeSubGB m_bfmeSubGB;
};

class BfmeCtxGB
{
public:
	unsigned char m_bfmeHeadGB[0x204];
	BfmeListGB *m_bfmeListGB;
};

class BfmeOwnerGB
{
public:
	void bfmeAddGB(BfmeCtxGB *ctx, int unused);

	unsigned char m_bfmeHeadGB[0xc];
	BfmeItemGB *m_bfmeItemGB;
};

void BfmeOwnerGB::bfmeAddGB(BfmeCtxGB *ctx, int unused)
{
	BfmeItemGB *item = m_bfmeItemGB;
	if (item == 0)
		return;

	if (ctx == 0)
		return;

	BfmeListGB *list = ctx->m_bfmeListGB;
	if (list == 0)
		return;

	if (list->bfmeContainsGB(item))
		return;

	list->m_bfmeSubGB.bfmeInsertGB(item, 2);
}
