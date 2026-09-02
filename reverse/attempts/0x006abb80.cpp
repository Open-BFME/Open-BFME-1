// ?reset@Rva006ABB80@@QAEXXZ
// partial score=0.85 date=2026-09-02
// cl: /DNDEBUG /MD
//
// Retail 0x006ABB80: if the tree count at +0xA4 is nonzero, optionally fill
// 48 bytes at +0x188 with 0x02 when +0x9C is not 1.0f, then _M_erase the
// tree at +0xA0 and reset its header sentinels.
//
// 87/102: only the inlined memset stosd setup order differs (lea edi first
// in retail, mov ecx/eax first here).

#include <cstring>

struct Rva006ABB80Node
{
	int color;
	Rva006ABB80Node *parent;
	Rva006ABB80Node *left;
	Rva006ABB80Node *right;
};

struct Rva006ABB80Tree
{
	void erase(Rva006ABB80Node *node);
	Rva006ABB80Node *header;
	int count;
};

class Rva006ABB80
{
public:
	void reset();

	char m_pad[0x9C];
	unsigned m_scaleBits;
	Rva006ABB80Tree m_tree;
	char m_padA8[0x188 - 0xA8];
	unsigned char m_buf[48];
};

void Rva006ABB80::reset()
{
	if (m_tree.count == 0)
		return;
	if (m_scaleBits != 0x3F800000)
		memset(m_buf, 2, 48);
	Rva006ABB80Tree *tree = &m_tree;
	if (m_tree.count != 0)
	{
		tree->erase(tree->header->parent);
		tree->header->left = tree->header;
		tree->header->parent = 0;
		tree->header->right = tree->header;
		tree->count = 0;
	}
}
