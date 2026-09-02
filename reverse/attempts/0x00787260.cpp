// ?bfmeIterate00787260@@YAP6AXPAI@ZPAURva00787260Node@@PAURva00787260Table@@1P6AX0@Z@Z
// partial score=0.95 date=2026-09-02
// cl: /O2 /Ob0

struct Rva00787260Node
{
	Rva00787260Node *m_next;
	unsigned int m_key;
};

struct Rva00787260Table
{
	void *m_pad00;
	Rva00787260Node **m_bucketBegin;
	Rva00787260Node **m_bucketEnd;
};

typedef void (__cdecl *Rva00787260Visitor)(unsigned int *key);

// @?bfmeIterate00787260@@YAP6AXPAI@ZPAURva00787260Node@@PAURva00787260Table@@0P6AX0@Z@Z 0x00787260
Rva00787260Visitor __cdecl bfmeIterate00787260(
	Rva00787260Node *node,
	Rva00787260Table *table,
	Rva00787260Node *end,
	Rva00787260Visitor visitor)
{
	Rva00787260Table *buckets = table;
	Rva00787260Node *current = node;
	if (current != end) {
		Rva00787260Visitor callback = visitor;
		do {
			unsigned int *key = &current->m_key;
			callback(key);
			current = current->m_next;

			if (current == 0) {
				unsigned int bucketCount = (unsigned int)(buckets->m_bucketEnd - buckets->m_bucketBegin);
				unsigned int bucket = *key % bucketCount;
				unsigned int limit = (unsigned int)(buckets->m_bucketEnd - buckets->m_bucketBegin);
				while (++bucket < limit) {
					current = buckets->m_bucketBegin[bucket];
					if (current != 0)
						break;
				}
			}
		} while (current != end);
		return callback;
	}
	return visitor;
}
