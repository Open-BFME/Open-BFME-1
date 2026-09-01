// The insertion sort itself: for every element after the first, hand it to the
// linear insert with the range that is already in order.
//
// The distance from the cursor back to the first element is kept as a base
// held in a callee-saved register -- four minus the first pointer -- so the
// byte count for the move-up is one lea per pass.
//
// The other two are linear inserts whose comparator is inlined: an entry with
// nothing attached sorts ahead of one that has something, and otherwise the
// names decide. The "exactly one of them" test is written with a bitwise xor
// of the two flags -- an inequality of the two comparisons compiles to a cmp
// and loses the xor retail has.

extern "C" __declspec(dllimport) void * __cdecl memmove(void *destination, const void *source, unsigned int bytes);
extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *left, const void *right, unsigned int count);

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

__forceinline void bfmeLinearInsert(int *first, int *last, int value)
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

// ?bfmeInsertionSort@@YAXPAH0@Z
void __cdecl bfmeInsertionSort(int *first, int *last)
{
	if (first == last)
		return;

	for (int *cursor = first + 1; cursor != last; ++cursor)
		bfmeLinearInsert(first, cursor, *cursor);
}

class BfmeNameAU
{
public:
	inline int bfmeCompare(const BfmeNameAU *other) const
	{
		int otherLength = other->m_bfmeData ? other->m_bfmeData->m_length : 0;
		const char *otherData = other->m_bfmeData ? other->m_bfmeData->m_data : "";
		int length = m_bfmeData ? m_bfmeData->m_length : 0;
		const char *data = m_bfmeData ? m_bfmeData->m_data : "";
		int count = length < otherLength ? length : otherLength;
		int order = _memicmp(data, otherData, count);

		if (order != 0)
			return order;

		return length - otherLength;
	}

private:
	struct Header
	{
		int m_references;
		unsigned short m_length;
		unsigned short m_capacity;
		char m_data[1];
	};

	Header *m_bfmeData;					// +0x00
	int m_bfmeUnused08;
	int m_bfmeUnused0C;
};

class BfmeRecAU
{
public:
	int m_bfmeTag;						// +0x00
	BfmeNameAU m_bfmeName;					// +0x04
	void *m_bfmeThing;					// +0x10
};

class BfmeCompAU
{
public:
	bool operator()(const BfmeRecAU *left, const BfmeRecAU *right) const
	{
		if ((left->m_bfmeThing == 0) ^ (right->m_bfmeThing == 0))
			return right->m_bfmeThing == 0;

		return left->m_bfmeName.bfmeCompare(&right->m_bfmeName) < 0;
	}

	int m_bfmeState;					// +0x00
};

inline BfmeRecAU **bfmeCopyBackwardAU(BfmeRecAU **first, BfmeRecAU **last, BfmeRecAU **result)
{
	int bytes = (char *)last - (char *)first;

	if (bytes > 0)
		memmove((char *)result - bytes, first, bytes);

	return (BfmeRecAU **)((char *)result - bytes);
}

// ?bfmeUnguardedInsertAU@@YAXPAPAVBfmeRecAU@@PAV1@VBfmeCompAU@@@Z
void __cdecl bfmeUnguardedInsertAU(BfmeRecAU **last, BfmeRecAU *value, BfmeCompAU comp)
{
	BfmeRecAU **next = last - 1;

	while (comp(value, *next))
	{
		*last = *next;
		last = next;
		--next;
	}

	*last = value;
}

// ?bfmeLinearInsertAU@@YAXPAPAVBfmeRecAU@@0PAV1@VBfmeCompAU@@@Z
void __cdecl bfmeLinearInsertAU(BfmeRecAU **first, BfmeRecAU **last, BfmeRecAU *value, BfmeCompAU comp)
{
	if (comp(value, *first))
	{
		bfmeCopyBackwardAU(first, last, last + 1);

		*first = value;
	}
	else
	{
		bfmeUnguardedInsertAU(last, value, comp);
	}
}

void __cdecl bfmeUnguardedInsertAV(BfmeRecAU **last, BfmeRecAU *value, BfmeCompAU comp);
								// retail thunk 0x000044EE -> 0x004044EE

// ?bfmeLinearInsertAV@@YAXPAPAVBfmeRecAU@@0PAV1@VBfmeCompAU@@@Z
void __cdecl bfmeLinearInsertAV(BfmeRecAU **first, BfmeRecAU **last, BfmeRecAU *value, BfmeCompAU comp)
{
	if (comp(value, *first))
	{
		bfmeCopyBackwardAU(first, last, last + 1);

		*first = value;
	}
	else
	{
		bfmeUnguardedInsertAV(last, value, comp);
	}
}
