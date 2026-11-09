// Open-BFME5 conversions.

extern "C" void *bfmeVft1030A[];
extern "C" void *bfmeVft1030B[];

extern "C" __declspec(dllimport) int __stdcall CreateMutexA(int a, int b, int c);

class BfmeA1030
{
public:
	BfmeA1030 *bfmeGo1030A(void);
	void bfmeBase1030(void);

	void *m_bfmeVfptr;
	int m_mutex;
};

BfmeA1030 *BfmeA1030::bfmeGo1030A(void)
{
	bfmeBase1030();
	m_bfmeVfptr = bfmeVft1030A;
	m_mutex = CreateMutexA(0, 0, 0);
	return this;
}

class BfmeSub1030
{
public:
	void bfmeInit1030(int a, int *p);
};

class BfmeB1030
{
public:
	BfmeB1030 *bfmeGo1030B(int a);

	void *m_bfmeVfptr;
	char m_bfmePad[8];
	BfmeSub1030 m_bfmeSub;
};

BfmeB1030 *BfmeB1030::bfmeGo1030B(int a)
{
	m_bfmeVfptr = bfmeVft1030B;
	m_bfmeSub.bfmeInit1030(a, &a);
	return this;
}

// 0x008B9C60 is the out-of-line constructor of the type-22 array value whose
// vtable is 0x01136D58 (??_7Rva008B9C90HeaderedDeleting@@6B@); ConcatArray
// 0x008B9CC0 inlines the same constructor (same base call 0x00899F00(0x16, 8),
// same three zeroed fields, same vtable).
class Rva00899F00Base
{
public:
	Rva00899F00Base(unsigned, int);
	virtual ~Rva00899F00Base();
	unsigned flags;
	char field08[0x18];
};

class Rva008B9C90HeaderedDeleting : public Rva00899F00Base
{
public:
	unsigned *m_elements;
	int m_capacity, m_length;
	virtual ~Rva008B9C90HeaderedDeleting();
	Rva008B9C90HeaderedDeleting();
};

Rva008B9C90HeaderedDeleting::Rva008B9C90HeaderedDeleting() : Rva00899F00Base(0x16, 8)
{
	m_capacity = 0;
	m_elements = 0;
	m_length = 0;
}

extern "C" void bfmeCtor1030(void);
extern "C" void bfmeDtor1030(void);
void __stdcall bfmeVecCtor1030(void *o, void *s, int sz, int n, void (*c)(void), void (*d)(void));

class BfmeD1030
{
public:
	BfmeD1030 *bfmeGo1030D(void *p);
};

BfmeD1030 *BfmeD1030::bfmeGo1030D(void *p)
{
	bfmeVecCtor1030(this, p, 0x14, 8, bfmeCtor1030, bfmeDtor1030);
	return this;
}
