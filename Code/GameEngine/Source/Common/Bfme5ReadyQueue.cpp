// Open-BFME5 conversions: bodies whose callees are already named.

class TextureClass
{
public:
	void Release_Ref(void);
};

static void bfme5ReleaseTexture(TextureClass **pp)
{
	TextureClass *t = *pp;

	if (!t)
		return;

	t->Release_Ref();
	*pp = 0;
}

class Bfme5TextureHolderA
{
public:
	void bfmeDropTexture(void);

	char m_bfmePad[0x1c];
	TextureClass *m_bfmeTexture;
};

void Bfme5TextureHolderA::bfmeDropTexture(void)
{
	if (m_bfmeTexture)
		bfme5ReleaseTexture(&m_bfmeTexture);
}

class Bfme5TextureHolderB
{
public:
	void bfmeDropTexture(void);

	char m_bfmePad[0x1c];
	TextureClass *m_bfmeTexture;
};

void Bfme5TextureHolderB::bfmeDropTexture(void)
{
	if (m_bfmeTexture)
		bfme5ReleaseTexture(&m_bfmeTexture);
}

namespace _STL {

class __new_alloc
{
public:
	static void *allocate(unsigned int n);
};

}

struct Bfme5IntNode
{
	Bfme5IntNode *m_bfmeNext;
	int m_bfmeValue;
};

Bfme5IntNode * __stdcall bfme5MakeIntNode(const int *v)
{
	Bfme5IntNode *n = (Bfme5IntNode *)_STL::__new_alloc::allocate(8);
	int *p = &n->m_bfmeValue;

	n->m_bfmeNext = 0;

	if (p)
		*p = *v;

	return n;
}
