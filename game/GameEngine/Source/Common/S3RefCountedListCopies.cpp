// Ten bodies in two shapes, all copy-constructing the same four-byte base and
// then taking a reference on a pointer at +0x04.
//
// The base call lands on 0x00887B60, which the ledger already holds twice:
// once as StringBase<char>'s PRIVATE copy constructor and once, by
// identical-code folding, as list<FXNugget *>'s public one. A derived class
// cannot reach a private base constructor, so the public spelling is the one
// used here; the bytes cannot say which of the two the compiler actually saw.
//
// After it, both shapes do the same thing: read a pointer, store it at +0x04,
// and bump the word at its own +0x04 unless it was null. Load, test, store,
// branch, increment -- an ordinary refcount acquire.
//
// The five 34-byte bodies are copy constructors: one argument, the same type,
// and it feeds both the base and the pointer. The five 35-byte ones take two
// arguments -- the base by reference and the pointer by reference, the second
// dereferenced once before the test.

namespace _STL
{

template <class T> class allocator
{
};

template <class T, class A> class list
{
public:
	list(const list &other);					// retail 0x00887B60

	void *m_bfmeNode;
};

}

class FXNugget;

typedef _STL::list<FXNugget *, _STL::allocator<FXNugget *> > BfmeNuggetList;

class BfmeRefCounted
{
public:
	char m_bfmeHead[0x04];
	int m_bfmeRefCount;						// +0x04
};

class Gen_0045f830 : public BfmeNuggetList
{
public:
	Gen_0045f830(Gen_0045f830 const &other);

	BfmeRefCounted *m_bfmeHeld;					// +0x04
};

class Gen_00467e00 : public BfmeNuggetList
{
public:
	Gen_00467e00(Gen_00467e00 const &other);

	BfmeRefCounted *m_bfmeHeld;					// +0x04
};

class Gen_00469950 : public BfmeNuggetList
{
public:
	Gen_00469950(Gen_00469950 const &other);

	BfmeRefCounted *m_bfmeHeld;					// +0x04
};

class Gen_004699c0 : public BfmeNuggetList
{
public:
	Gen_004699c0(Gen_004699c0 const &other);

	BfmeRefCounted *m_bfmeHeld;					// +0x04
};

class Gen_00473b60 : public BfmeNuggetList
{
public:
	Gen_00473b60(Gen_00473b60 const &other);

	BfmeRefCounted *m_bfmeHeld;					// +0x04
};

class Gen_0045f9d0 : public BfmeNuggetList
{
public:
	Gen_0045f9d0(BfmeNuggetList const &nuggets, BfmeRefCounted *const &held);

	BfmeRefCounted *m_bfmeHeld;					// +0x04
};

class Gen_00468440 : public BfmeNuggetList
{
public:
	Gen_00468440(BfmeNuggetList const &nuggets, BfmeRefCounted *const &held);

	BfmeRefCounted *m_bfmeHeld;					// +0x04
};

class Gen_00468470 : public BfmeNuggetList
{
public:
	Gen_00468470(BfmeNuggetList const &nuggets, BfmeRefCounted *const &held);

	BfmeRefCounted *m_bfmeHeld;					// +0x04
};

class Gen_004684a0 : public BfmeNuggetList
{
public:
	Gen_004684a0(BfmeNuggetList const &nuggets, BfmeRefCounted *const &held);

	BfmeRefCounted *m_bfmeHeld;					// +0x04
};

class Gen_00473870 : public BfmeNuggetList
{
public:
	Gen_00473870(BfmeNuggetList const &nuggets, BfmeRefCounted *const &held);

	BfmeRefCounted *m_bfmeHeld;					// +0x04
};

Gen_0045f830::Gen_0045f830(Gen_0045f830 const &other)
	: BfmeNuggetList(other)
{
	m_bfmeHeld = other.m_bfmeHeld;

	if (m_bfmeHeld)
		++m_bfmeHeld->m_bfmeRefCount;
}

Gen_00467e00::Gen_00467e00(Gen_00467e00 const &other)
	: BfmeNuggetList(other)
{
	m_bfmeHeld = other.m_bfmeHeld;

	if (m_bfmeHeld)
		++m_bfmeHeld->m_bfmeRefCount;
}

Gen_00469950::Gen_00469950(Gen_00469950 const &other)
	: BfmeNuggetList(other)
{
	m_bfmeHeld = other.m_bfmeHeld;

	if (m_bfmeHeld)
		++m_bfmeHeld->m_bfmeRefCount;
}

Gen_004699c0::Gen_004699c0(Gen_004699c0 const &other)
	: BfmeNuggetList(other)
{
	m_bfmeHeld = other.m_bfmeHeld;

	if (m_bfmeHeld)
		++m_bfmeHeld->m_bfmeRefCount;
}

Gen_00473b60::Gen_00473b60(Gen_00473b60 const &other)
	: BfmeNuggetList(other)
{
	m_bfmeHeld = other.m_bfmeHeld;

	if (m_bfmeHeld)
		++m_bfmeHeld->m_bfmeRefCount;
}

Gen_0045f9d0::Gen_0045f9d0(BfmeNuggetList const &nuggets, BfmeRefCounted *const &held)
	: BfmeNuggetList(nuggets)
{
	m_bfmeHeld = held;

	if (m_bfmeHeld)
		++m_bfmeHeld->m_bfmeRefCount;
}

Gen_00468440::Gen_00468440(BfmeNuggetList const &nuggets, BfmeRefCounted *const &held)
	: BfmeNuggetList(nuggets)
{
	m_bfmeHeld = held;

	if (m_bfmeHeld)
		++m_bfmeHeld->m_bfmeRefCount;
}

Gen_00468470::Gen_00468470(BfmeNuggetList const &nuggets, BfmeRefCounted *const &held)
	: BfmeNuggetList(nuggets)
{
	m_bfmeHeld = held;

	if (m_bfmeHeld)
		++m_bfmeHeld->m_bfmeRefCount;
}

Gen_004684a0::Gen_004684a0(BfmeNuggetList const &nuggets, BfmeRefCounted *const &held)
	: BfmeNuggetList(nuggets)
{
	m_bfmeHeld = held;

	if (m_bfmeHeld)
		++m_bfmeHeld->m_bfmeRefCount;
}

Gen_00473870::Gen_00473870(BfmeNuggetList const &nuggets, BfmeRefCounted *const &held)
	: BfmeNuggetList(nuggets)
{
	m_bfmeHeld = held;

	if (m_bfmeHeld)
		++m_bfmeHeld->m_bfmeRefCount;
}
