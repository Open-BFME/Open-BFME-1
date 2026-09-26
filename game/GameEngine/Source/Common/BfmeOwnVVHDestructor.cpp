// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// BfmeOwnVVH::~BfmeOwnVVH, retail RVA 0x009035E0.
// Retail releases the counted handles at +0x04, +0x260, +0x264, and +0x268.
// The eight four-byte elements at +0x08 then run through the vector dtor.

class BfmeRefVVH
{
public:
	virtual void release();

	int m_referenceCount;
};

class BfmeElementA
{
public:
	~BfmeElementA(); // retail ILT 0x00030652

private:
	char m_body[4];
};

class BfmeOwnVVH
{
public:
	~BfmeOwnVVH();

private:
	char m_head[4];
	BfmeRefVVH *m_first;
	BfmeElementA m_elements[8];
	char m_gap[0x238];
	BfmeRefVVH *m_middle[2];
	BfmeRefVVH *m_last;
};

// ??1BfmeOwnVVH@@QAE@XZ
BfmeOwnVVH::~BfmeOwnVVH()
{
	BfmeRefVVH *first = m_first;
	if (first)
	{
		if (--first->m_referenceCount == 0)
			first->release();
		m_first = 0;
	}

	BfmeRefVVH **slot = m_middle;
	int count = 2;
	do
	{
		BfmeRefVVH *value = *slot;
		if (value)
		{
			if (--value->m_referenceCount == 0)
				value->release();
			*slot = 0;
		}
		++slot;
	}
	while (--count != 0);

	BfmeRefVVH *last = m_last;
	if (last)
	{
		if (--last->m_referenceCount == 0)
			last->release();
		m_last = 0;
	}
}
