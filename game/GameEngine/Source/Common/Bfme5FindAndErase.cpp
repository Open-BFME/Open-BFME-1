// Two bodies that look a value up in their vector and erase the first match.
//
// The search is written out at the call site -- the value goes into a register
// before the loop and the bound stays in another. The bound has to come from
// an accessor on the vector: read as a member here, MSVC shares it with the
// read the erase makes and the reload inside the erase disappears.
//
// The erase itself is the move-down: copy the tail over the hole unless the
// hole is the last element, then step the finish pointer back by one.

extern "C" __declspec(dllimport) void * __cdecl memmove(void *destination, const void *source, unsigned int bytes);

class BfmeVecAG
{
public:
	void bfmeErase(int *position)
	{
		int *next = position + 1;

		if (m_bfmeFinish != next)
			memmove(position, next, (char *)m_bfmeFinish - (char *)next);

		--m_bfmeFinish;
	}

	int *bfmeBegin(void) const
	{
		return m_bfmeStart;
	}

	int *bfmeEnd(void) const
	{
		return m_bfmeFinish;
	}

	int *m_bfmeStart;					// +0x00
	int *m_bfmeFinish;					// +0x04
	int *m_bfmeEnd;						// +0x08
};

class Gen_0039BE00
{
public:
	void bfmeRemove(int value);

private:
	int m_bfmeHead[2];					// +0x00
	BfmeVecAG m_bfmeVector;					// +0x08
};

// ?bfmeRemove@Gen_0039BE00@@QAEXH@Z
void Gen_0039BE00::bfmeRemove(int value)
{
	int *it = m_bfmeVector.bfmeBegin();
	int *last = m_bfmeVector.bfmeEnd();

	while (it != last)
	{
		if (*it == value)
		{
			m_bfmeVector.bfmeErase(it);

			return;
		}

		++it;
	}
}

class Gen_00430440
{
public:
	void bfmeRemove(int value);

private:
	int m_bfmeHead[57];					// +0x000
	BfmeVecAG m_bfmeVector;					// +0x0E4
};

// ?bfmeRemove@Gen_00430440@@QAEXH@Z
void Gen_00430440::bfmeRemove(int value)
{
	int *it = m_bfmeVector.bfmeBegin();
	int *last = m_bfmeVector.bfmeEnd();

	while (it != last)
	{
		if (*it == value)
		{
			m_bfmeVector.bfmeErase(it);

			return;
		}

		++it;
	}
}
