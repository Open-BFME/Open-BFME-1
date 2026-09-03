// ?bfmeInsert@Gen009D76F0@@QAEPAUBfmeHashPair@@PBU2@@Z
// partial score=0.88 date=2026-09-02
// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the C-string hash-map insert at retail RVA 0x009D7AF0.

void __cdecl gen009D73D0(void *dest, void *src);

struct BfmeHashPair
{
	void *key;
	void *value;
};

struct BfmeHashNode
{
	BfmeHashNode *next;
	BfmeHashPair pair;
};

class Gen009D76F0
{
public:
	void *evaluate(void *argument);
	BfmeHashPair *bfmeInsert(const BfmeHashPair *value);
	void *bfmeAt(void **key);

private:
	void bfmeResize(unsigned int newCount);

	unsigned char m_pad[4];
	BfmeHashNode **m_begin;
	BfmeHashNode **m_end;
	unsigned char m_gap[4];
	unsigned int m_count;
};

BfmeHashPair *Gen009D76F0::bfmeInsert(const BfmeHashPair *value)
{
	BfmeHashPair *result = 0;
	bfmeResize(m_count + 1);

	unsigned int hash = 0;
	const char *text = static_cast<const char *>(value->key);
	char ch = *text;
	if (ch != 0)
	{
		do
		{
			hash = hash * 5 + static_cast<signed char>(ch);
			ch = *++text;
		}
		while (ch != 0);
	}

	unsigned int n = static_cast<unsigned int>(m_end - m_begin);
	unsigned int bucket = hash % n;
	BfmeHashNode *head = m_begin[bucket];
	BfmeHashNode *node = static_cast<BfmeHashNode *>(::operator new(sizeof(BfmeHashNode)));
	node->next = 0;
	gen009D73D0(&node->pair, const_cast<BfmeHashPair *>(value));
	node->next = head;
	m_begin[bucket] = node;
	++m_count;
	result = &node->pair;
	return result;
}

void *Gen009D76F0::bfmeAt(void **key)
{
	void *found = evaluate(key);
	if (found == 0)
	{
		BfmeHashPair tmp;
		tmp.key = *key;
		tmp.value = 0;
		return reinterpret_cast<char *>(bfmeInsert(&tmp)) + 4;
	}
	return static_cast<char *>(found) + 8;
}
