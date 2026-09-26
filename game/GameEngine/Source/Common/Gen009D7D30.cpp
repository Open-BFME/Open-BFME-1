// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the C-string hash-map operator[] at retail RVA 0x009D7D30.

struct BfmeHashPair
{
	void *key;
	void *value;
};

class Gen009D76F0
{
public:
	void *evaluate(void *argument);
	BfmeHashPair *bfmeInsert(const BfmeHashPair *value);
	void *bfmeAt(void **key);
};

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
