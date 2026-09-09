// ?findByNameB@BfmeNamedContainer0033c340@@QAEPAVBfmeNamedItem0033c340@@ABVAsciiString@@@Z
// partial score=0.99 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc
// The ILT at 0x0000A592 and the lookup caller at 0x0033C450 identify this
// method as BfmeNamedContainer0033c340::findByNameB.

class AsciiString
{
};

class BfmeSubERY
{
public:
	int bfmeCheckERY(void *key);
};

struct BfmeBucketERY
{
	char m_head[8];
	BfmeSubERY m_sub;
	char m_padding[7];
	void *m_item;
};

class BfmeNamedContainer0033c340;

class Rva00359530StringRecordTable
{
private:
	friend class BfmeNamedContainer0033c340;
	int findNameIndex(AsciiString *name);

	int *m_first;
	int *m_last;
	char m_padding[4];
	BfmeBucketERY *m_entries;
};

class BfmeNamedItem0033c340
{
};

class BfmeNamedContainer0033c340
{
public:
	BfmeNamedItem0033c340 *findByNameB(const AsciiString &name);

private:
	char m_prefix[0x2c];
	Rva00359530StringRecordTable m_table;
};

// ?findByNameB@BfmeNamedContainer0033c340@@QAEPAVBfmeNamedItem0033c340@@ABVAsciiString@@@Z
BfmeNamedItem0033c340 *BfmeNamedContainer0033c340::findByNameB(
	const AsciiString &name)
{
	Rva00359530StringRecordTable *table = &m_table;
	unsigned int index = table->findNameIndex((AsciiString *)&name);

	if (index < (unsigned int)(table->m_last - table->m_first))
	{
		int id = table->m_first[index];
		BfmeSubERY *sub = &table->m_entries[id].m_sub;
		if (sub->bfmeCheckERY((void *)&name) == 0 && id != -1)
			return (BfmeNamedItem0033c340 *)
				((char *)m_table.m_entries[id].m_item + 4);
	}

	return 0;
}
