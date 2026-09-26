// BfmeQuery1279::bfmeQuery1279, retail RVA 0x008BD0F0 (185 bytes).
// The second argument is the address of a string-data handle when nonzero.

extern "C" int __cdecl memcmp(const void *left, const void *right, unsigned int count);
#pragma intrinsic(memcmp)

struct BfmeStringData1279
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned int m_capacity;
	char m_text[1];
};

// Keep the length as a promoted unsigned value.  The retail body loads both
// 16-bit lengths into full registers before comparing and passing the first
// one to memcmp.
static __forceinline unsigned int bfmeLength1279(const BfmeStringData1279 *data)
{
	return *(const unsigned short *)((const char *)data + 2);
}

struct BfmeQueryNode1279
{
	void *m_vtable;
	unsigned int m_flags;
	int m_key;
	BfmeStringData1279 *m_name;
	char m_padding10[0x58 - 0x10];
	BfmeQueryNode1279 *m_next;
};

class BfmeQuery1279
{
public:
	void bfmeQuery1279(void *key, int name, void **previousResult, void **nodeResult);

private:
	BfmeQueryNode1279 *m_root;
};

void BfmeQuery1279::bfmeQuery1279(void *key, int name, void **previousResult, void **nodeResult)
{
	BfmeQuery1279 *self = this;
	BfmeQueryNode1279 *node = self->m_root->m_next;
	BfmeQueryNode1279 *namePrevious = self->m_root;

	if (name != 0 && node != 0) {
		do {
			if (((unsigned char)(~(node->m_flags >> 15)) & 1) != 0) {
				BfmeStringData1279 *wanted = *(BfmeStringData1279 **)name;
				unsigned int wantedLength = bfmeLength1279(wanted);
				unsigned int nodeLength = bfmeLength1279(node->m_name);
				if (wantedLength == nodeLength &&
					(wanted == node->m_name || memcmp(wanted->m_text, node->m_name->m_text, wantedLength) == 0)) {
					*nodeResult = node;
					*previousResult = namePrevious;
					return;
				}
			}
			namePrevious = node;
			node = node->m_next;
		} while (node != 0);
	}

	node = self->m_root->m_next;
	BfmeQueryNode1279 *keyPrevious = self->m_root;
	while (node != 0 && node->m_key < (int)key) {
		keyPrevious = node;
		node = node->m_next;
	}
	if (node != 0 && node->m_key == (int)key)
		*nodeResult = node;
	else
		*nodeResult = 0;
	*previousResult = keyPrevious;
}

// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
