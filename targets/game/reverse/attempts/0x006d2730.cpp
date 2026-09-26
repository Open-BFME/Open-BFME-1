// ?updateGrid@Rva006D2730@@QAEXPAURva006D2730Rect@@PAX1@Z
// partial score=0.2 date=2026-09-05
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?d_006d2730@@YAXXZ (Code/gen_asm/d_0069c4f0.asm), size 576.
//
// RVA-derived reconstruction, identity NOT proven. Neighbours 0x006D2660 /
// 0x006D2690 (freeMapResources) / 0x006D33B0 / 0x006D3450 are all
// HeightMapRenderObjClass, so `this` (edi) is believed to be that class;
// offsets kept relative rather than merged into the real header per FILE
// POLICY (never edit the tracked HeightMap.cpp/.h).
//
// Structural notes for the next worker:
//   Args: (ptrArg @[esp+0x1c] orig-ebx, arg2 @[esp+0x24], arg3 @[esp+0x2c]).
//   ptrArg is a rect/region-shaped object: +0x08 and +0x0c are ints, each
//   rounded up (`(v+0xe) & ~0xf`) then >>4 -- a "cells covered, tile == 16
//   units" computation, giving cols/rows.
//   this+0x2ff4 is compared against ptrArg for a `sete` flag forwarded (with
//   all 3 args and the this pointer) into still-dumped 0x0003a328 -- looks
//   like a "mark dirty region, already-current?" call.
//   this+0x30d8 is an array of 0xc4-byte records, this+0x30e0/0x30e4 the
//   cached cols/rows, this+0x30dc a stashed pointer (freed via bfmeGet-style
//   free at target 0x000225d4 then reallocated through ??_U operator
//   new[](unsigned) when the cols*rows changed).  Each record is touched
//   through two still-dumped helpers per (row,col): ctor-ish 0x0003a82d /
//   0x0003902c and a setter 0x00047668(record, ptrArg).
//   When the array is (re)grown, retail builds it via the compiler's array
//   placement-new helper (??_L, target ArrayNewHelperBodyThunk.cpp) with a
//   constructor function pointer pair (0x0002b9a4 ctor / 0x0004149d dtor),
//   record size 0xc4; this strongly suggests the record is a class with a
//   non-trivial ctor/dtor (matches the RoadSegment-family classes already
//   landed elsewhere in this session -- worth comparing 0xc4 against
//   RoadSegment's real sizeof once that class is available here).
//   this+0x30d4 gets the final `operator new[](cols*2)` byte flag array-ish
//   value; this+0x3174 is cleared to 0 at the very end.
//
// Not byte-matched: this is a compiling skeleton only, banked as partial.

extern "C" void *__cdecl operator_new_dummy_unused(); // placeholder, unused

struct Rva006D2730Rect
{
	unsigned char m_pad0[8];
	int m_width;
	int m_height;
};

extern void j_0003a328(void);
extern void j_00014c5e(void);
extern void j_0003a82d(void);
extern void j_00047668(void);
extern void j_000225d4(void);
extern void j_0003902c(void);
extern void j_0002b9a4(void);
extern void j_0004149d(void);

typedef void *(__stdcall *Rva006D2730Alloc)(unsigned int);

class Rva006D2730Owner
{
public:
	void free_(void);
};

union Rva006D2730Call5
{
	void (*free_function)(void);
	int (Rva006D2730Owner::*member_function)(void *a, void *b, void *c, void *d, int flag);
};

union Rva006D2730Call1
{
	void (*free_function)(void);
	void (Rva006D2730Owner::*member_function)(int cellCount);
};

union Rva006D2730Call2
{
	void (*free_function)(void);
	void (Rva006D2730Owner::*member_function)(void *record, void *rect);
};

union Rva006D2730Call4
{
	void (*free_function)(void);
	void (Rva006D2730Owner::*member_function)(void *record, void *rect, int row, int col);
};

class Rva006D2730
{
public:
	void updateGrid(Rva006D2730Rect *rect, void *arg2, void *arg3);

private:
	unsigned char m_pad[0x2ff4];
	void *m_dirtyRegion;
	unsigned char m_pad2ff8[0x30d4 - 0x2ff8];
	void *m_flagArray;
	void *m_records;
	void *m_recordsStash;
	int m_cols;
	int m_rows;
	unsigned char m_pad30e8[0x3174 - 0x30e8];
	char m_finalFlag;
};

void Rva006D2730::updateGrid(Rva006D2730Rect *rect, void *arg2, void *arg3)
{
	bool same = (rect == (Rva006D2730Rect *)m_dirtyRegion);

	Rva006D2730Owner *owner = (Rva006D2730Owner *)this;

	{
		Rva006D2730Call5 call;
		call.free_function = &j_0003a328;
		(owner->*call.member_function)(arg3, rect, arg2, 0, same ? 1 : 0);
	}

	int w = ((rect->m_width + 0xe) & ~0xf) >> 4;
	int h = ((rect->m_height + 0xe) & ~0xf) >> 4;
	int cellCount = w * h;

	{
		Rva006D2730Call1 call;
		call.free_function = &j_00014c5e;
		(owner->*call.member_function)(cellCount);
	}

	bool needGrow = !(m_records != 0 && m_cols == h && m_rows == w);

	if (!needGrow)
	{
		for (int col = 0; col < h; ++col)
		{
			for (int row = 0; row < w; ++row)
			{
				char *record = (char *)m_records + (h * row + col) * 0xc4;

				{
					Rva006D2730Call2 call;
					call.free_function = &j_0003a82d;
					(owner->*call.member_function)(record, rect);
				}
				{
					Rva006D2730Call2 call;
					call.free_function = &j_00047668;
					(owner->*call.member_function)(record, rect);
				}
			}
		}
		return;
	}

	{
		Rva006D2730Owner ownerAlias;
		Rva006D2730Call5 call;
		(void)call;
	}

	{
		typedef void (Rva006D2730Owner::*FreeFn)(void);
		union { void (*f)(void); FreeFn m; } u;
		u.f = &j_000225d4;
		(owner->*u.m)();
	}

	void *newRecords = (void *)new char[cellCount * 0xc4 + 4];
	if (newRecords != 0)
	{
		*(void **)newRecords = owner;
		void *payload = (char *)newRecords + 4;
		extern void ArrayNewHelper(void *, unsigned, int, void (*)(void *), void (*)(void *));
		ArrayNewHelper(payload, 0xc4, cellCount, (void (*)(void *))&j_0002b9a4, (void (*)(void *))&j_0004149d);
		m_recordsStash = payload;
	}

	m_records = 0;
	m_recordsStash = (void *)(unsigned int)cellCount;
	m_cols = h;
	m_rows = w;

	if (h > 0 && w > 0)
	{
		for (int col2 = 0; col2 < h; ++col2)
		{
			for (int row2 = 0; row2 < w; ++row2)
			{
				char *record = (char *)m_records + (h * row2 + col2) * 0xc4;

				{
					Rva006D2730Call4 call;
					call.free_function = &j_0003902c;
					(owner->*call.member_function)(record, rect, col2, row2 << 4);
				}
				{
					Rva006D2730Call2 call;
					call.free_function = &j_00047668;
					(owner->*call.member_function)(record, rect);
				}
			}
		}
	}

	m_flagArray = (void *)new char[(unsigned int)(w) * 8];
	m_finalFlag = 0;
}
