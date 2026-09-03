// cl: /DNDEBUG /MD /O2 /EHsc
// Open-BFME5: VNE-family ctor with inlined 0x2c rb-header at +0xC.
// Retail 0x003BC360, 162 bytes. Base virtual dtor pulls the EH frame.

void *bfmeAllocNode(unsigned int bytes);

class BfmeBaseVNI
{
public:
	BfmeBaseVNI(unsigned w, char f);
	virtual ~BfmeBaseVNI();
	virtual void handle();

	unsigned m_bfme04;
	char m_bfme08;
};

BfmeBaseVNI::BfmeBaseVNI(unsigned w, char f)
{
	m_bfme08 = f;
	m_bfme04 = (int)((float)w * 0.03f);
	if (m_bfme04 < 1)
		m_bfme04 = 1;
}

BfmeBaseVNI::~BfmeBaseVNI()
{
}

struct BfmeVNINode
{
	char color;
	int *parent;
	BfmeVNINode *left;
	BfmeVNINode *right;
};

struct BfmeVNITree
{
	BfmeVNINode *header;
	int count;
	BfmeVNITree();
};

BfmeVNITree::BfmeVNITree()
{
	header = 0;
	header = (BfmeVNINode *)bfmeAllocNode(0x2c);
	count = 0;
	header->color = 0;
	header->parent = 0;
	header->left = header;
	header->right = header;
}

class BfmeRectVNI : public BfmeBaseVNI
{
public:
	BfmeRectVNI(unsigned w, char f);

	BfmeVNITree m_tree;
	int m_at14;
	int m_at18;
};

// ??0BfmeRectVNI@@QAE@ID@Z
BfmeRectVNI::BfmeRectVNI(unsigned w, char f)
	: BfmeBaseVNI(w, f)
	, m_at18(0)
{
}
