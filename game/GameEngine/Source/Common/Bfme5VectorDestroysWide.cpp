// Six more vector destroys, over widths the release has to divide out.
//
// Same shape as the power-of-two ones: run the destructor over every live
// element, then free the block by size. Here the width does not fold into a
// shift pair, so the byte span is divided by a magic multiply and multiplied
// straight back, which is what the source "sizeof(T) * (end - start)" gives.
//
// Four of the elements have a virtual destructor, so the walk calls slot zero
// with a zero flag; two have an ordinary one and the walk calls it directly.
// That is also why the two ordinary ones have no vptr to leave room for.
//
// The end of the walk is declared before its start. The declaration order of
// the two locals is what decides which member is loaded first, and it comes
// out in source order, so start-then-end loads the wrong one.

void __cdecl operator delete(void *block);
static __forceinline void bfmeRelease(void *block, unsigned int bytes);

namespace _STL
{
template <bool Threads, int Instance>
class __node_alloc
{
    static void _M_deallocate(void *block, unsigned int bytes);
    friend void ::bfmeRelease(void *block, unsigned int bytes);
};
}

class WorkerAIUpdateModuleData
{
public:
    virtual ~WorkerAIUpdateModuleData();
};

class Rva000FD010 { public: void invoke(); };

static __forceinline void bfmeRelease(void *block, unsigned int bytes)
{
	if (bytes > 0x80)
		::operator delete(block);
	else
		_STL::__node_alloc<true, 0>::_M_deallocate(block, bytes);
}

class BfmeVecElem_000FAFF0
{
public:

private:
	char m_bfmePad[0x60];
};

class Gen_000FAFF0
{
public:
	void bfmeDestroy(void);

private:
	BfmeVecElem_000FAFF0 *m_bfmeStart;			// +0x00
	BfmeVecElem_000FAFF0 *m_bfmeFinish;			// +0x04
	BfmeVecElem_000FAFF0 *m_bfmeEnd;			// +0x08
};

class BfmeVecElem_000FEAF0
{
public:

private:
	char m_bfmePad[0x24];
};

class Gen_000FEAF0
{
public:
	void bfmeDestroy(void);

private:
	BfmeVecElem_000FEAF0 *m_bfmeStart;			// +0x00
	BfmeVecElem_000FEAF0 *m_bfmeFinish;			// +0x04
	BfmeVecElem_000FEAF0 *m_bfmeEnd;			// +0x08
};

class BfmeVecElem_003639E0
{
public:
	virtual ~BfmeVecElem_003639E0(void);

private:
	char m_bfmePad[0x54];
};

class Gen_003639E0
{
public:
	void bfmeDestroy(void);

private:
	BfmeVecElem_003639E0 *m_bfmeStart;			// +0x00
	BfmeVecElem_003639E0 *m_bfmeFinish;			// +0x04
	BfmeVecElem_003639E0 *m_bfmeEnd;			// +0x08
};

class BfmeVecElem_003AFAB0
{
public:
	virtual ~BfmeVecElem_003AFAB0(void);

private:
	char m_bfmePad[0x24];
};

class Gen_003AFAB0
{
public:
	void bfmeDestroy(void);

private:
	BfmeVecElem_003AFAB0 *m_bfmeStart;			// +0x00
	BfmeVecElem_003AFAB0 *m_bfmeFinish;			// +0x04
	BfmeVecElem_003AFAB0 *m_bfmeEnd;			// +0x08
};

class BfmeVecElem_003AFB30
{
public:
	virtual ~BfmeVecElem_003AFB30(void);

private:
	char m_bfmePad[0x2C];
};

class Gen_003AFB30
{
public:
	void bfmeDestroy(void);

private:
	BfmeVecElem_003AFB30 *m_bfmeStart;			// +0x00
	BfmeVecElem_003AFB30 *m_bfmeFinish;			// +0x04
	BfmeVecElem_003AFB30 *m_bfmeEnd;			// +0x08
};

class BfmeVecElem_003AFC20
{
public:
	virtual ~BfmeVecElem_003AFC20(void);

private:
	char m_bfmePad[0x8];
};

class Gen_003AFC20
{
public:
	void bfmeDestroy(void);

private:
	BfmeVecElem_003AFC20 *m_bfmeStart;			// +0x00
	BfmeVecElem_003AFC20 *m_bfmeFinish;			// +0x04
	BfmeVecElem_003AFC20 *m_bfmeEnd;			// +0x08
};

// ?bfmeDestroy@Gen_000FAFF0@@QAEXXZ
void Gen_000FAFF0::bfmeDestroy(void)
{
	BfmeVecElem_000FAFF0 *last = m_bfmeFinish;
	BfmeVecElem_000FAFF0 *first = m_bfmeStart;

	for (; first != last; ++first)
		((WorkerAIUpdateModuleData *)first)->WorkerAIUpdateModuleData::~WorkerAIUpdateModuleData();

	BfmeVecElem_000FAFF0 *start = m_bfmeStart;

	if (start)
		bfmeRelease(start, sizeof(BfmeVecElem_000FAFF0) * (m_bfmeEnd - start));
}

// ?bfmeDestroy@Gen_000FEAF0@@QAEXXZ
void Gen_000FEAF0::bfmeDestroy(void)
{
	BfmeVecElem_000FEAF0 *last = m_bfmeFinish;
	BfmeVecElem_000FEAF0 *first = m_bfmeStart;

	for (; first != last; ++first)
		((Rva000FD010 *)first)->invoke();

	BfmeVecElem_000FEAF0 *start = m_bfmeStart;

	if (start)
		bfmeRelease(start, sizeof(BfmeVecElem_000FEAF0) * (m_bfmeEnd - start));
}

// ?bfmeDestroy@Gen_003639E0@@QAEXXZ
void Gen_003639E0::bfmeDestroy(void)
{
	BfmeVecElem_003639E0 *last = m_bfmeFinish;
	BfmeVecElem_003639E0 *first = m_bfmeStart;

	for (; first != last; ++first)
		first->~BfmeVecElem_003639E0();

	BfmeVecElem_003639E0 *start = m_bfmeStart;

	if (start)
		bfmeRelease(start, sizeof(BfmeVecElem_003639E0) * (m_bfmeEnd - start));
}

// ?bfmeDestroy@Gen_003AFAB0@@QAEXXZ
void Gen_003AFAB0::bfmeDestroy(void)
{
	BfmeVecElem_003AFAB0 *last = m_bfmeFinish;
	BfmeVecElem_003AFAB0 *first = m_bfmeStart;

	for (; first != last; ++first)
		first->~BfmeVecElem_003AFAB0();

	BfmeVecElem_003AFAB0 *start = m_bfmeStart;

	if (start)
		bfmeRelease(start, sizeof(BfmeVecElem_003AFAB0) * (m_bfmeEnd - start));
}

// ?bfmeDestroy@Gen_003AFB30@@QAEXXZ
void Gen_003AFB30::bfmeDestroy(void)
{
	BfmeVecElem_003AFB30 *last = m_bfmeFinish;
	BfmeVecElem_003AFB30 *first = m_bfmeStart;

	for (; first != last; ++first)
		first->~BfmeVecElem_003AFB30();

	BfmeVecElem_003AFB30 *start = m_bfmeStart;

	if (start)
		bfmeRelease(start, sizeof(BfmeVecElem_003AFB30) * (m_bfmeEnd - start));
}

// ?bfmeDestroy@Gen_003AFC20@@QAEXXZ
void Gen_003AFC20::bfmeDestroy(void)
{
	BfmeVecElem_003AFC20 *last = m_bfmeFinish;
	BfmeVecElem_003AFC20 *first = m_bfmeStart;

	for (; first != last; ++first)
		first->~BfmeVecElem_003AFC20();

	BfmeVecElem_003AFC20 *start = m_bfmeStart;

	if (start)
		bfmeRelease(start, sizeof(BfmeVecElem_003AFC20) * (m_bfmeEnd - start));
}
