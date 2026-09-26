// ?find@Rva009A3250Table@@QAEPAURva009A3250Node@@PAURva009A3250Key@@@Z
// Address-derived hash-bucket lookup: hash = ((key->m_8 << 16) + key->m_c) %
// 0x2B7B, walk the chain at bucket[hash] via m_30, matching on (m_8, m_c).
struct Rva009A3250Node
{
	unsigned char m_pad0[8];
	unsigned m_8;
	unsigned m_c;
	unsigned char m_pad10[0x30 - 0x10];
	Rva009A3250Node* m_30;
};

struct Rva009A3250Key
{
	unsigned char m_pad0[8];
	unsigned m_8;
	unsigned m_c;
};

struct Rva009A3250Table
{
	Rva009A3250Node* m_buckets[0x2b7b];

	Rva009A3250Node* find(Rva009A3250Key* key);
};

Rva009A3250Node* Rva009A3250Table::find(Rva009A3250Key* key)
{
	unsigned h = ((key->m_8 << 16) + key->m_c) % 0x2b7b;

	Rva009A3250Node* node = m_buckets[h];
	while (node)
	{
		if (node->m_8 == key->m_8 && node->m_c == key->m_c)
			return node;
		node = node->m_30;
	}
	return 0;
}
