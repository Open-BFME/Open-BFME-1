// Open-BFME5 conversions: bodies whose callees are already named.

class TextureClass
{
public:
	void Release_Ref(void);

	int m_bfme00;
	unsigned short m_bfmeRefCount;
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

class SubsystemInterface
{
public:
	SubsystemInterface(void);
	virtual ~SubsystemInterface();

	int m_bfmeSubsystem04;
};

class Bfme5TripleSubsystem : public SubsystemInterface
{
public:
	Bfme5TripleSubsystem(int a, int b, int c);
	virtual ~Bfme5TripleSubsystem();

	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
};

Bfme5TripleSubsystem::Bfme5TripleSubsystem(int a, int b, int c)
{
	m_bfme08 = a;
	m_bfme0c = b;
	m_bfme10 = c;
}

struct Coord3D;

enum CellShroudStatus
{
	BFME5_CELLSHROUD_ZERO
};

class PartitionManager
{
public:
	CellShroudStatus getShroudStatusForPlayer(int player, const Coord3D *pos) const;
};

extern PartitionManager *ThePartitionManager;

class Bfme5ShroudedThing
{
public:
	char bfmeIsShrouded(int player);

	char m_bfmePad[0x48];
	int m_bfmePos;
};

char Bfme5ShroudedThing::bfmeIsShrouded(int player)
{
	if (ThePartitionManager &&
	    ThePartitionManager->getShroudStatusForPlayer(player, (const Coord3D *)&m_bfmePos) >= 1)
		return 1;

	return 0;
}

struct Bfme5Link
{
	Bfme5Link *m_bfmeNext;
	Bfme5Link *m_bfmePrev;
	void *m_bfmeValue;
};

struct Bfme5LinkHead
{
	Bfme5Link *m_bfmeNode;
};

class Bfme5LinkPusher
{
public:
	void bfmePushBack(void *x);

	char m_bfmePad[0x10];
	Bfme5LinkHead *m_bfmeList;
};

void Bfme5LinkPusher::bfmePushBack(void *x)
{
	Bfme5Link *pos = m_bfmeList->m_bfmeNode;
	Bfme5Link *n = (Bfme5Link *)_STL::__new_alloc::allocate(0x0c);
	void **p = &n->m_bfmeValue;

	if (p)
		*p = x;

	Bfme5Link *prev = pos->m_bfmePrev;

	n->m_bfmeNext = pos;
	n->m_bfmePrev = prev;
	prev->m_bfmeNext = n;
	pos->m_bfmePrev = n;
}

struct Bfme5Pair8
{
	Bfme5Pair8(void);
	~Bfme5Pair8();

	int m_bfme00;
	int m_bfme04;
};

class Bfme5PairArray
{
public:
	Bfme5PairArray(void);

	int m_bfme00;
	int m_bfme04;
	Bfme5Pair8 *m_bfme08;
	Bfme5Pair8 m_bfmeArray[2];
};

Bfme5PairArray::Bfme5PairArray(void)
	: m_bfme00(0), m_bfme04(0), m_bfme08(m_bfmeArray)
{
}

extern TextureClass *g_bfme5TextureSlots[];

void __cdecl bfme5SetTextureSlot(int i, TextureClass **src)
{
	TextureClass **slot = &g_bfme5TextureSlots[i];
	TextureClass *t = *src;

	if (t)
		++t->m_bfmeRefCount;

	TextureClass *old = *slot;

	if (old)
		old->Release_Ref();

	*slot = *src;
}

void __cdecl operator delete(void *p);

extern void *g_bfme5DetachVtable;

struct Bfme5DetachSink
{
	char m_bfmePad[0x1dc];
	int m_bfme1dc;
};

class Bfme5Detachable
{
public:
	void *bfmeDestroy(int flags);

	void *m_bfmeVptr;
	int m_bfme04;
	Bfme5DetachSink *m_bfmeSink;
};

void *Bfme5Detachable::bfmeDestroy(int flags)
{
	m_bfmeVptr = &g_bfme5DetachVtable;

	Bfme5DetachSink *o = m_bfmeSink;

	if (o) {
		o->m_bfme1dc = m_bfme04;
		m_bfmeSink = 0;
	}

	if (flags & 1)
		operator delete(this);

	return this;
}

class Bfme5TextureArray
{
public:
	void bfmeSetSlot(int i, TextureClass **src);

	char m_bfmePad[0x24];
	TextureClass **m_bfmeSlots;
};

void Bfme5TextureArray::bfmeSetSlot(int i, TextureClass **src)
{
	TextureClass **slot = &m_bfmeSlots[i];
	TextureClass *t = *src;

	if (t)
		++t->m_bfmeRefCount;

	TextureClass *old = *slot;

	if (old)
		old->Release_Ref();

	*slot = *src;
}
