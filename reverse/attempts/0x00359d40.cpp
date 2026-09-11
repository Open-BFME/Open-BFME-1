// ?findByNameA@BfmeNamedContainer0033c340@@QAEPAVBfmeNamedItem0033c340@@ABVAsciiString@@@Z
// partial score=0.99 date=2026-09-10
class AsciiString
{
public:
	int compare(const AsciiString &other) const;

private:
	void *m_data;
};

class BfmeNamedItem0033c340
{
};

struct BfmeStoredItem00359d40
{
	unsigned char m_head[4];
	BfmeNamedItem0033c340 m_item;
};

struct BfmeBucket00359d40
{
	unsigned char m_head[8];
	AsciiString m_name;
	unsigned char m_pad[4];
	BfmeStoredItem00359d40 *m_storedItem;
};

class BfmeMap00359d40
{
public:
	unsigned int findNameIndex(const AsciiString &name);

	int *m_first;
	int *m_last;
	unsigned char m_mid[4];
	BfmeBucket00359d40 *m_entries;
};

class BfmeNamedContainer0033c340
{
public:
	BfmeNamedItem0033c340 *findByNameA(const AsciiString &name);

private:
	unsigned char m_head[0xc];
	BfmeMap00359d40 m_map;
};

BfmeNamedItem0033c340 *BfmeNamedContainer0033c340::findByNameA(
	const AsciiString &name)
{
	BfmeMap00359d40 *map = &m_map;
	unsigned int i = map->findNameIndex(name);

	if (i < (unsigned int)(map->m_last - map->m_first))
	{
		int id = map->m_first[i];
		AsciiString *entryName = &map->m_entries[id].m_name;
		if (entryName->compare(name) == 0 && id != -1)
			return &m_map.m_entries[id].m_storedItem->m_item;
	}

	return 0;
}
