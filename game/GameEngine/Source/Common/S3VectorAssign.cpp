// Four vector assignments, 0x00095A50, 0x000B54C0, 0x002F8980 and 0x003A9560.
//
// The first call is entered with the source as this and the ADDRESS OF THE
// PARAMETER SLOT as its argument -- there is no sub esp, so that address can
// only be the parameter itself. That is a reference-to-pointer parameter on
// the callee, not a local.
//
// The element count is (finish - start) >> 3, so the elements are eight bytes
// wide, and the bounds are re-read from the source after the reserve call.
// The copy walks two independent pointers rather than recomputing the
// destination, and the null test in front of each element is placement-new
// codegen. The finish pointer is written from the cursor at the end and this
// is handed back.

inline void *operator new(unsigned int, void *place)
{
	return place;
}

struct BfmePair
{
	BfmePair(const BfmePair &other)
	{
		m_bfmeFirst = other.m_bfmeFirst;
		m_bfmeSecond = other.m_bfmeSecond;
	}

	int m_bfmeFirst;
	int m_bfmeSecond;
};

struct BfmeVectorRange
{
	BfmePair *m_bfmeStart;					// +0x00
	BfmePair *m_bfmeFinish;					// +0x04
};


class BfmeSourceA
{
public:
	void *bfmeGrab(void **slot);			// ILT 0x00019876
};

class Gen_00095A50
{
public:
	Gen_00095A50 *bfmeAssign(BfmeVectorRange *source);

private:
	void bfmeReserve(int count, void *grabbed);		// ILT 0x000472DA

	BfmePair *m_bfmeStart;					// +0x00
	BfmePair *m_bfmeFinish;					// +0x04
};

class BfmeSourceB
{
public:
	void *bfmeGrab(void **slot);			// ILT 0x000314E9
};

class Gen_000B54C0
{
public:
	Gen_000B54C0 *bfmeAssign(BfmeVectorRange *source);

private:
	void bfmeReserve(int count, void *grabbed);		// ILT 0x00043E37

	BfmePair *m_bfmeStart;					// +0x00
	BfmePair *m_bfmeFinish;					// +0x04
};

class BfmeSourceC
{
public:
	void *bfmeGrab(void **slot);			// ILT 0x0002EBC2
};

class Gen_002F8980
{
public:
	Gen_002F8980 *bfmeAssign(BfmeVectorRange *source);

private:
	void bfmeReserve(int count, void *grabbed);		// ILT 0x00015ABE

	BfmePair *m_bfmeStart;					// +0x00
	BfmePair *m_bfmeFinish;					// +0x04
};

class BfmeSourceD
{
public:
	void *bfmeGrab(void **slot);			// ILT 0x00018697
};

class Gen_003A9560
{
public:
	Gen_003A9560 *bfmeAssign(BfmeVectorRange *source);

private:
	void bfmeReserve(int count, void *grabbed);		// ILT 0x00027098

	BfmePair *m_bfmeStart;					// +0x00
	BfmePair *m_bfmeFinish;					// +0x04
};

// ?bfmeAssign@Gen_00095A50@@QAEPAV1@PAUBfmeVectorRange@@@Z
Gen_00095A50 *Gen_00095A50::bfmeAssign(BfmeVectorRange *source)
{
	void *slot;
	void *grabbed = ((BfmeSourceA *)source)->bfmeGrab(&slot);

	bfmeReserve(source->m_bfmeFinish - source->m_bfmeStart, grabbed);

	const BfmePair *last = source->m_bfmeFinish;
	const BfmePair *element = source->m_bfmeStart;
	BfmePair *cursor = m_bfmeStart;

	while (element != last)
	{
		new (cursor) BfmePair(*element);
		++element;
		++cursor;
	}

	m_bfmeFinish = cursor;

	return this;
}

// ?bfmeAssign@Gen_000B54C0@@QAEPAV1@PAUBfmeVectorRange@@@Z
Gen_000B54C0 *Gen_000B54C0::bfmeAssign(BfmeVectorRange *source)
{
	void *slot;
	void *grabbed = ((BfmeSourceB *)source)->bfmeGrab(&slot);

	bfmeReserve(source->m_bfmeFinish - source->m_bfmeStart, grabbed);

	const BfmePair *last = source->m_bfmeFinish;
	const BfmePair *element = source->m_bfmeStart;
	BfmePair *cursor = m_bfmeStart;

	while (element != last)
	{
		new (cursor) BfmePair(*element);
		++element;
		++cursor;
	}

	m_bfmeFinish = cursor;

	return this;
}

// ?bfmeAssign@Gen_002F8980@@QAEPAV1@PAUBfmeVectorRange@@@Z
Gen_002F8980 *Gen_002F8980::bfmeAssign(BfmeVectorRange *source)
{
	void *slot;
	void *grabbed = ((BfmeSourceC *)source)->bfmeGrab(&slot);

	bfmeReserve(source->m_bfmeFinish - source->m_bfmeStart, grabbed);

	const BfmePair *last = source->m_bfmeFinish;
	const BfmePair *element = source->m_bfmeStart;
	BfmePair *cursor = m_bfmeStart;

	while (element != last)
	{
		new (cursor) BfmePair(*element);
		++element;
		++cursor;
	}

	m_bfmeFinish = cursor;

	return this;
}

// ?bfmeAssign@Gen_003A9560@@QAEPAV1@PAUBfmeVectorRange@@@Z
Gen_003A9560 *Gen_003A9560::bfmeAssign(BfmeVectorRange *source)
{
	void *slot;
	void *grabbed = ((BfmeSourceD *)source)->bfmeGrab(&slot);

	bfmeReserve(source->m_bfmeFinish - source->m_bfmeStart, grabbed);

	const BfmePair *last = source->m_bfmeFinish;
	const BfmePair *element = source->m_bfmeStart;
	BfmePair *cursor = m_bfmeStart;

	while (element != last)
	{
		new (cursor) BfmePair(*element);
		++element;
		++cursor;
	}

	m_bfmeFinish = cursor;

	return this;
}
