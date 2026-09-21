// ?bfmeGo008939C0@@YAPAXPAPAXHH@Z
// partial score=0.15 date=2026-09-21
// cl: /DNDEBUG /MD /EHs-c-
//
// Address-derived: no this-pointer field is ever read (ecx is unused), so
// this is a free helper, not a method. It grows/replaces a BfmeElemCU[]
// buffer allocated through the custom allocator at 0x01337828 and freed
// through g_bfmeFreeDWF (0x0133782c) -- both already-pinned globals used by
// the landed Rva00893960ListClear.cpp neighbour. The two decrement/increment
// callees resolve to the already-matched refcount helpers documented in
// S3ChildTeardown.cpp (bfmeCheckA @ 0x00894D90 -- decrement-and-test; the
// paired increment @ 0x00894D80 is pinned as bfmeIncVGO). Element ctor/dtor
// are the pinned BfmeElemCU special members (0x00892B80 / thunk 0x000463AD).
// Exact parameter semantics are NOT proven (literal straight-line
// transliteration of the disassembly; register names kept as such where the
// true meaning is unproven), per docs/naming_evidence.md.

#include <new>

typedef unsigned int UnsignedInt;

extern "C" void *(__cdecl *g_bfmeAllocDWF)(unsigned int bytes);	// 0x01337828
extern "C" void (__cdecl *g_bfmeFreeDWF)(void *ptr);			// 0x0133782c

int bfmeCheckA(void *p);				// 0x00894D90, decrement-and-return
int bfmeIncVGO(int *p);				// 0x00894D80, increment-and-return
extern void bfmeDropA(void *p);			// 0x00895320 (S3ChildTeardown.cpp)

class BfmeElemCU
{
public:
	BfmeElemCU();					// 0x00892B80
	~BfmeElemCU();					// thunk 0x000463AD

private:
	void *m_ptr;
};

// this-unused free helper; ebx=p1 (nullable source array), [esp+0x24]-arg=p2
// (existing/old count), [esp+0x28]-arg=p3 (new element count).
void *bfmeGo008939C0(void **p1, int p2, int p3)
{
	void **ebx = p1;
	int ebp = 0;
	void *buf;
	int newCount;
	void **esi;
	void **edi;

	if (ebx != 0)
		goto SecondBranch;

	// ---- first branch: p1 == NULL ----
	{
		int count = p3;
		buf = g_bfmeAllocDWF(count * 4 + 4);
		newCount = 0;
		if (buf == 0)
			return 0;

		*(int *)buf = count;
		esi = (void **)((char *)buf + 4);
		for (int i = 0; i < count; ++i)
			new (&((BfmeElemCU *)esi)[i]) BfmeElemCU();
		return esi;
	}

SecondBranch:
	{
		int count = p3;
		buf = 0;
		if (count == 0)
			goto OldBufferCheck;

		void *newBuf = g_bfmeAllocDWF(count * 4 + 4);
		buf = newBuf;
		newCount = 1;
		if (newBuf == 0)
		{
			edi = 0;
			goto Merge;
		}

		*(int *)newBuf = count;
		edi = (void **)((char *)newBuf + 4);
		for (int i = 0; i < count; ++i)
			new (&((BfmeElemCU *)edi)[i]) BfmeElemCU();
		goto AfterConstruct;
	}

Merge:
AfterConstruct:
	{
		int oldCount = p2;
		newCount = (p3 >= oldCount) ? -1 : newCount;
		buf = edi;
		if (p3 < oldCount)
			goto SkipLoop;

		esi = (void **)(UnsignedInt)oldCount;
		if (oldCount == 0)
			goto OldBufferCheck;

		ebp = oldCount;
		edi = 0;
		for (;;)
		{
			esi = edi;
			edi = (void **)((char *)edi + 4);
			if (ebx == esi)
				break;

			void *elem = *(void **)esi;
			if (elem != 0)
			{
				if (bfmeCheckA(elem) == 0)
					bfmeDropA(elem);
			}

			void *repl = *ebx;
			*(void **)esi = repl;
			if (repl != 0)
				bfmeIncVGO((int *)repl);

			ebx = (void **)((char *)ebx + 4);
			if (--ebp == 0)
				break;
		}
	}

SkipLoop:
OldBufferCheck:
	if (ebx != 0)
	{
		void *old = *((char **)ebx - 1);
		void **oldData = (void **)((char *)ebx - 4);
		((BfmeElemCU *)oldData)->~BfmeElemCU();
		g_bfmeFreeDWF(oldData);
	}

	return buf;
}
