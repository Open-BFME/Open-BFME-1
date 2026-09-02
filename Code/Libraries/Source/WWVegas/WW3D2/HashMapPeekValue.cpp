// cl: /DNDEBUG /MD /EHsc
// Retail 0x008FF850: hash_map find wrapper returning mapped pointer or null.

struct HashNode008FF850
{
	char pad[0x14];
	void *value;
};

struct HashIter008FF850
{
	HashNode008FF850 *node;
	HashIter008FF850(HashNode008FF850 *n = 0) : node(n) {}
};

class HashMap008FF850
{
public:
	HashNode008FF850 *end_node;
	HashIter008FF850 find(const int &key);
};

extern HashMap008FF850 g_map008FF850;

void *PeekHashMapValue008FF850(int key)
{
	HashIter008FF850 it = g_map008FF850.find(key);
	if (it.node == g_map008FF850.end_node)
		return 0;
	return it.node->value;
}
