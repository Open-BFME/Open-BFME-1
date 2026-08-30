// ?bfmeQuery1279@BfmeQuery1279@@QAEXPAXHPAPAX1@Z
// partial score=0.82 date=2026-08-30
extern "C" int __cdecl memcmp(const void *left, const void *right, unsigned int count);
#pragma intrinsic(memcmp)

struct BfmeStringData1279
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned int m_capacity;
	char m_text[1];
};

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
	BfmeQueryNode1279 *previous = m_root;
	BfmeQueryNode1279 *node = previous->m_next;
	BfmeStringData1279 *wanted = (BfmeStringData1279 *)name;

	if (wanted != 0 && node != 0) {
		do {
			if (((~(node->m_flags >> 15)) & 1) != 0 &&
				wanted->m_length == node->m_name->m_length &&
				(wanted == node->m_name || memcmp(wanted->m_text, node->m_name->m_text, wanted->m_length) == 0)) {
				*nodeResult = node;
				*previousResult = previous;
				return;
			}
			previous = node;
			node = node->m_next;
		} while (node != 0);
	}

	previous = m_root;
	node = previous->m_next;
	while (node != 0 && node->m_key < (int)key) {
		previous = node;
		node = node->m_next;
	}
	*nodeResult = node != 0 && node->m_key == (int)key ? node : 0;
	*previousResult = previous;
}
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
