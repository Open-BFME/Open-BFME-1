// The insertion step of a sort: if the value belongs in front of the whole
// range, move the range up by one and drop it at the front, otherwise walk
// back from the end shifting elements up until it fits.
//
// The move-up is a copy backward, and for a trivially copyable element that is
// one memmove whose destination is computed from the far end -- last minus the
// byte count plus one element -- which is why the addition comes after the
// subtraction.
//
// Three of the four take a comparator by value and hand their unguarded arm to
// an out-of-line copy of itself; the comparator object is four bytes, passed
// on by value and called through its own address in the argument slot.

extern "C" __declspec(dllimport) void * __cdecl memmove(void *destination, const void *source, unsigned int bytes);

inline int *bfmeCopyBackward(int *first, int *last, int *result)
{
	int bytes = (char *)last - (char *)first;

	if (bytes > 0)
		memmove((char *)result - bytes, first, bytes);

	return (int *)((char *)result - bytes);
}

inline void bfmeUnguardedLinearInsert(int *last, int value)
{
	int *next = last - 1;

	while (value < *next)
	{
		*last = *next;

		last = next;

		--next;
	}

	*last = value;
}

// ?bfmeLinearInsert@@YAXPAH0H@Z
void __cdecl bfmeLinearInsert(int *first, int *last, int value)
{
	if (value < *first)
	{
		bfmeCopyBackward(first, last, last + 1);

		*first = value;
	}
	else
	{
		bfmeUnguardedLinearInsert(last, value);
	}
}

class BfmeCompAO
{
public:
	bool operator()(int left, int right);			// retail thunk 0x00024055 -> 0x00424055

	int m_bfmeState;					// +0x00
};

void __cdecl bfmeUnguardedInsertAO(int *last, int value, BfmeCompAO comp);
								// retail thunk 0x0001A424 -> 0x0041A424

// ?bfmeLinearInsertAO@@YAXPAH0HVBfmeCompAO@@@Z
void __cdecl bfmeLinearInsertAO(int *first, int *last, int value, BfmeCompAO comp)
{
	if (comp(value, *first))
	{
		bfmeCopyBackward(first, last, last + 1);

		*first = value;
	}
	else
	{
		bfmeUnguardedInsertAO(last, value, comp);
	}
}

class BfmeCompAP
{
public:
	bool operator()(int left, int right);			// retail thunk 0x00039CB1 -> 0x00439CB1

	int m_bfmeState;					// +0x00
};

void __cdecl bfmeUnguardedInsertAP(int *last, int value, BfmeCompAP comp);
								// retail thunk 0x000389B5 -> 0x004389B5

// ?bfmeLinearInsertAP@@YAXPAH0HVBfmeCompAP@@@Z
void __cdecl bfmeLinearInsertAP(int *first, int *last, int value, BfmeCompAP comp)
{
	if (comp(value, *first))
	{
		bfmeCopyBackward(first, last, last + 1);

		*first = value;
	}
	else
	{
		bfmeUnguardedInsertAP(last, value, comp);
	}
}

class BfmeCompAQ
{
public:
	bool operator()(int left, int right);			// retail thunk 0x00024B81 -> 0x00424B81

	int m_bfmeState;					// +0x00
};

void __cdecl bfmeUnguardedInsertAQ(int *last, int value, BfmeCompAQ comp);
								// retail thunk 0x000018C0 -> 0x004018C0

// ?bfmeLinearInsertAQ@@YAXPAH0HVBfmeCompAQ@@@Z
void __cdecl bfmeLinearInsertAQ(int *first, int *last, int value, BfmeCompAQ comp)
{
	if (comp(value, *first))
	{
		bfmeCopyBackward(first, last, last + 1);

		*first = value;
	}
	else
	{
		bfmeUnguardedInsertAQ(last, value, comp);
	}
}

class BfmeCompAR
{
public:
	bool operator()(int left, int right);			// retail thunk 0x0002952D -> 0x0042952D

	int m_bfmeState;					// +0x00
};

void __cdecl bfmeUnguardedInsertAR(int *last, int value, BfmeCompAR comp);
								// retail thunk 0x0003EDB0 -> 0x0043EDB0

// ?bfmeLinearInsertAR@@YAXPAH0HVBfmeCompAR@@@Z
void __cdecl bfmeLinearInsertAR(int *first, int *last, int value, BfmeCompAR comp)
{
	if (comp(value, *first))
	{
		bfmeCopyBackward(first, last, last + 1);

		*first = value;
	}
	else
	{
		bfmeUnguardedInsertAR(last, value, comp);
	}
}

typedef bool (__cdecl *BfmeCompareAS)(int left, int right);

void __cdecl bfmeUnguardedInsertAS(int *last, int value, BfmeCompareAS compare)

{
	int *next = last - 1;

	while (compare(value, *next))
	{
		*last = *next;

		last = next;

		--next;
	}

	*last = value;
}
								// retail thunk 0x0004727B -> 0x0044727B

// ?bfmeLinearInsertAS@@YAXPAH0HP6A_NHH@Z@Z
void __cdecl bfmeLinearInsertAS(int *first, int *last, int value, BfmeCompareAS compare)
{
	if (compare(value, *first))
	{
		bfmeCopyBackward(first, last, last + 1);

		*first = value;
	}
	else
	{
		bfmeUnguardedInsertAS(last, value, compare);
	}
}
