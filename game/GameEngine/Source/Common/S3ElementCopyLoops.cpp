// Four 67-byte copy loops over eight-byte elements: a four-byte string-like
// first member and a four-byte word second.
//
// The call in the loop is NOT a construction. Its target is the StringBase set
// member -- the same body the ledger also holds as AudioEventRTS::operator= --
// and the loop has no null test in front of it. Placement new always emits one
// (with or without exception handling, and with or without a throw()
// specification on the placement operator), so an uninitialized copy is ruled
// out: these assign into elements that already exist.
//
// Two shaping points beyond that:
//
//   - The count must be computed INSIDE the if, not before it. Hoisted into a
//     variable ahead of the test, the compiler keeps it in a callee-saved
//     register from the start and saves that register in the prologue; written
//     inside, the difference stays in eax and only the source pointer is saved
//     before the branch, which is what retail does.
//
//   - The empty case returns the destination parameter unadvanced and the loop
//     case returns the walked pointer, so the two exits are separate.

template <class T> class StringBase
{
public:
	void set(const StringBase &other);
};

struct Gen_000b0290Elem
{
	StringBase<char> m_bfmeKey;					// +0x00
	int m_bfmeValue;						// +0x04
};

struct Gen_00125130Elem
{
	StringBase<char> m_bfmeKey;					// +0x00
	int m_bfmeValue;						// +0x04
};

struct Gen_0029c560Elem
{
	StringBase<char> m_bfmeKey;					// +0x00
	int m_bfmeValue;						// +0x04
};

struct Gen_00434d20Elem
{
	StringBase<unsigned short> m_bfmeKey;					// +0x00
	int m_bfmeValue;						// +0x04
};

// ?Gen_000b0290@@YAPAUGen_000b0290Elem@@PBU1@0PAU1@@Z
Gen_000b0290Elem *Gen_000b0290(const Gen_000b0290Elem *first, const Gen_000b0290Elem *last, Gen_000b0290Elem *destination)
{
	if (last - first > 0)
	{
		int count = last - first;

		do
		{
			destination->m_bfmeKey.set(first->m_bfmeKey);
			destination->m_bfmeValue = first->m_bfmeValue;

			first++;
			destination++;
		}
		while (--count);
	}

	return destination;
}

// ?Gen_00125130@@YAPAUGen_00125130Elem@@PBU1@0PAU1@@Z
Gen_00125130Elem *Gen_00125130(const Gen_00125130Elem *first, const Gen_00125130Elem *last, Gen_00125130Elem *destination)
{
	if (last - first > 0)
	{
		int count = last - first;

		do
		{
			destination->m_bfmeKey.set(first->m_bfmeKey);
			destination->m_bfmeValue = first->m_bfmeValue;

			first++;
			destination++;
		}
		while (--count);
	}

	return destination;
}

// ?Gen_0029c560@@YAPAUGen_0029c560Elem@@PBU1@0PAU1@@Z
Gen_0029c560Elem *Gen_0029c560(const Gen_0029c560Elem *first, const Gen_0029c560Elem *last, Gen_0029c560Elem *destination)
{
	if (last - first > 0)
	{
		int count = last - first;

		do
		{
			destination->m_bfmeKey.set(first->m_bfmeKey);
			destination->m_bfmeValue = first->m_bfmeValue;

			first++;
			destination++;
		}
		while (--count);
	}

	return destination;
}

// ?Gen_00434d20@@YAPAUGen_00434d20Elem@@PBU1@0PAU1@@Z
Gen_00434d20Elem *Gen_00434d20(const Gen_00434d20Elem *first, const Gen_00434d20Elem *last, Gen_00434d20Elem *destination)
{
	if (last - first > 0)
	{
		int count = last - first;

		do
		{
			destination->m_bfmeKey.set(first->m_bfmeKey);
			destination->m_bfmeValue = first->m_bfmeValue;

			first++;
			destination++;
		}
		while (--count);
	}

	return destination;
}
