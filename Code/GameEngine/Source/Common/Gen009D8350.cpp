// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the character-range hash insert at retail RVA 0x009D8350.

struct BfmeCharRange
{
	const char *begin;
	const char *end;
};

void __cdecl gen009D8190(void *dest, const void *src);

struct BfmeRangeNode
{
	BfmeRangeNode *next;
	unsigned char pair[0x10];
};

class Gen009D7B80
{
public:
	unsigned int bfmeBucket(const BfmeCharRange *key) const;
	unsigned char *bfmeInsert(const BfmeCharRange *value);

private:
	void bfmeResize(unsigned int newCount);

	unsigned char m_pad[4];
	BfmeRangeNode **m_begin;
	BfmeRangeNode **m_end;
	unsigned char m_gap[4];
	unsigned int m_count;
};

unsigned char *Gen009D7B80::bfmeInsert(const BfmeCharRange *value)
{
	bfmeResize(m_count + 1);
	unsigned int bucket = bfmeBucket(value);
	BfmeRangeNode *head = m_begin[bucket];
	BfmeRangeNode *node = static_cast<BfmeRangeNode *>(::operator new(sizeof(BfmeRangeNode)));
	node->next = 0;
	gen009D8190(node->pair, value);
	node->next = head;
	m_begin[bucket] = node;
	++m_count;
	return node->pair;
}
