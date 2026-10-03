// cl: /DNDEBUG /MD /O2 /EHsc /G6
// Open-BFME5: VNE-family ctor with inlined 0x2c rb-header at +0xC.
// Retail 0x003BC360, 162 bytes. Base virtual dtor pulls the EH frame.
//
// /G6: retail calls _STL::__new_alloc::allocate (0x0082E540, ret 4) from this
// body, so the allocator declaration has to mangle
// ?allocate@__new_alloc@_STL@@SAPAXI@Z (the /G6 convention, as in
// game/Libraries/Source/WWVegas/WWLib/Small03hStlAlloc.cpp) rather than a
// TU-local wrapper name. Every member body here is __thiscall, so the flag
// does not move their bytes.

// (body owned by game/Libraries/Source/WWVegas/WWLib/STL_new_alloc_allocateThunk.cpp)
namespace _STL
{

class __new_alloc
{
public:
	static void *allocate(unsigned int n);
};

}

class BfmeBaseVNI
{
public:
	BfmeBaseVNI(unsigned w, char f);
	virtual ~BfmeBaseVNI();
	// Retail's vtable for this class (0x010ED8D4) carries the purecall body
	// 0x0088C500 in this slot, so the slot is pure here too; BfmeRectVNI's
	// own table (0x010EDA08) overrides it through 0x0042C656.
	virtual int handle() = 0;

	unsigned m_bfme04;
	char m_bfme08;
};

// ?BfmeBaseVNI::BfmeBaseVNI present-unmatched
BfmeBaseVNI::BfmeBaseVNI(unsigned w, char f)
{
	m_bfme08 = f;
	m_bfme04 = (int)((float)w * 0.03f);
	if (m_bfme04 < 1)
		m_bfme04 = 1;
}

// ?BfmeBaseVNI::~BfmeBaseVNI present-unmatched
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

// ?BfmeVNITree::BfmeVNITree present-unmatched
BfmeVNITree::BfmeVNITree()
{
	header = 0;
	header = (BfmeVNINode *)_STL::__new_alloc::allocate(0x2c);
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
