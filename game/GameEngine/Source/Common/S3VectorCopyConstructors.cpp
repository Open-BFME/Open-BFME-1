// Four 76-byte vector copy constructors. Each asks the source for its
// allocator, hands the element count and that allocator to an allocate-and-copy
// member, and then copies the elements itself before writing the finish
// pointer.
//
// Three things are worth recording.
//
// The allocator comes back by value through a hidden return pointer, and the
// slot MSVC picks for it is the incoming argument's own stack slot -- the
// parameter is still live but its VALUE is already in a register, so the slot
// is free. That falls out on its own; nothing in the source asks for it.
//
// The allocate-and-copy result is never read. The loop reads this->start back
// out of the object instead, which is what says that member writes into this
// rather than returning the block.
//
// The copy loop DOES have a null test in front of it, so unlike the assignment
// loops at 0x000B0290 this one really is placement new -- the elements do not
// exist yet.
//
// Both the source's finish pointer and its start have to be held in locals, in
// that order. Left as member reads the compare goes against memory and the
// body comes out three bytes longer.

inline void *operator new(unsigned int, void *place)
{
	return place;
}

class BfmeAllocator
{
public:
	BfmeAllocator(const BfmeAllocator &other);

	char m_bfmeBody[0x04];
};

class Gen_000bb890
{
public:
	Gen_000bb890(const Gen_000bb890 &other);

private:
	BfmeAllocator bfmeGetAllocator(void) const;			// ILT 0x0001E2A4
	void bfmeAllocateAndCopy(int count, const BfmeAllocator &allocator);	// ILT 0x0001E579

	int *m_bfmeStart;						// +0x00
	int *m_bfmeFinish;						// +0x04
};

class Gen_000ce890
{
public:
	Gen_000ce890(const Gen_000ce890 &other);

private:
	BfmeAllocator bfmeGetAllocator(void) const;			// ILT 0x00008BED
	void bfmeAllocateAndCopy(int count, const BfmeAllocator &allocator);	// ILT 0x000067C1

	int *m_bfmeStart;						// +0x00
	int *m_bfmeFinish;						// +0x04
};

class Gen_0036e170
{
public:
	Gen_0036e170(const Gen_0036e170 &other);

private:
	BfmeAllocator bfmeGetAllocator(void) const;			// ILT 0x000441BB
	void bfmeAllocateAndCopy(int count, const BfmeAllocator &allocator);	// ILT 0x00019BF0

	int *m_bfmeStart;						// +0x00
	int *m_bfmeFinish;						// +0x04
};

class Gen_005862c0
{
public:
	Gen_005862c0(const Gen_005862c0 &other);

private:
	BfmeAllocator bfmeGetAllocator(void) const;			// ILT 0x0003FFB7
	void bfmeAllocateAndCopy(int count, const BfmeAllocator &allocator);	// ILT 0x00038122

	int *m_bfmeStart;						// +0x00
	int *m_bfmeFinish;						// +0x04
};

// ??0Gen_000bb890@@QAE@ABV0@@Z
Gen_000bb890::Gen_000bb890(const Gen_000bb890 &other)
{
	bfmeAllocateAndCopy(other.m_bfmeFinish - other.m_bfmeStart, other.bfmeGetAllocator());

	const int *last = other.m_bfmeFinish;
	const int *first = other.m_bfmeStart;
	int *destination = m_bfmeStart;

	while (first != last)
	{
		new (destination) int(*first);

		first++;
		destination++;
	}

	m_bfmeFinish = destination;
}

// ??0Gen_000ce890@@QAE@ABV0@@Z
Gen_000ce890::Gen_000ce890(const Gen_000ce890 &other)
{
	bfmeAllocateAndCopy(other.m_bfmeFinish - other.m_bfmeStart, other.bfmeGetAllocator());

	const int *last = other.m_bfmeFinish;
	const int *first = other.m_bfmeStart;
	int *destination = m_bfmeStart;

	while (first != last)
	{
		new (destination) int(*first);

		first++;
		destination++;
	}

	m_bfmeFinish = destination;
}

// ??0Gen_0036e170@@QAE@ABV0@@Z
Gen_0036e170::Gen_0036e170(const Gen_0036e170 &other)
{
	bfmeAllocateAndCopy(other.m_bfmeFinish - other.m_bfmeStart, other.bfmeGetAllocator());

	const int *last = other.m_bfmeFinish;
	const int *first = other.m_bfmeStart;
	int *destination = m_bfmeStart;

	while (first != last)
	{
		new (destination) int(*first);

		first++;
		destination++;
	}

	m_bfmeFinish = destination;
}

// ??0Gen_005862c0@@QAE@ABV0@@Z
Gen_005862c0::Gen_005862c0(const Gen_005862c0 &other)
{
	bfmeAllocateAndCopy(other.m_bfmeFinish - other.m_bfmeStart, other.bfmeGetAllocator());

	const int *last = other.m_bfmeFinish;
	const int *first = other.m_bfmeStart;
	int *destination = m_bfmeStart;

	while (first != last)
	{
		new (destination) int(*first);

		first++;
		destination++;
	}

	m_bfmeFinish = destination;
}
