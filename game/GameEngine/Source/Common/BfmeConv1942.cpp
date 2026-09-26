class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);

	~BFMERetailAsciiString() { releaseBuffer(); }

	void *m_bfmeBufDO;

private:
	void releaseBuffer();
};

class BfmeSubDO
{
public:
	void bfmeSetDO(int first, int second, int third, int fourth);
};

class BfmeEntryDO
{
public:
	unsigned char m_bfmeHeadDO[8];
	BfmeSubDO m_bfmeSubDO;
};

class BfmeMapDO
{
public:
	BfmeEntryDO *bfmeFindDO(const BFMERetailAsciiString &name);
};

class BfmeHostDO
{
public:
	void bfmeApplyDO(const char *name, int first, int second, int third, int fourth);

	unsigned char m_bfmeHeadDO[0x30];
	BfmeMapDO m_bfmeMapDO;
};

void BfmeHostDO::bfmeApplyDO(const char *name, int first, int second, int third, int fourth)
{
	if (name == 0)
		return;

	BfmeEntryDO *entry;

	{
		const BFMERetailAsciiString &text = BFMERetailAsciiString(name);

		BfmeMapDO *map = &m_bfmeMapDO;

		entry = map->bfmeFindDO(text);
	}

	if (entry == 0)
		return;

	entry->m_bfmeSubDO.bfmeSetDO(first, second, third, fourth);
}
