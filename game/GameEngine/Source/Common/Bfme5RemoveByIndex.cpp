// A remove that finds its value by index and erases the slot it landed on.
//
// The search returns an index, so the erase recomputes the position from the
// start pointer instead of reusing the cursor the search walked; the guard
// against the not-found index survives only on the path where the index came
// out of the loop, because on the other one MSVC knows it is minus one.
//
// The span is recomputed on every pass, which makes it the condition of the
// loop rather than a hoisted local, and the compares are unsigned.

extern "C" __declspec(dllimport) void * __cdecl memmove(void *destination, const void *source, unsigned int bytes);

class BfmeVecAI
{
public:
	unsigned int bfmeSize(void) const
	{
		return (unsigned int)(m_bfmeFinish - m_bfmeStart);
	}

	void bfmeEraseAt(unsigned int index)
	{
		int *position = m_bfmeStart + index;
		int *next = position + 1;

		if (m_bfmeFinish != next)
			memmove(position, next, (char *)m_bfmeFinish - (char *)next);

		--m_bfmeFinish;
	}

	int *m_bfmeStart;					// +0x00
	int *m_bfmeFinish;					// +0x04
	int *m_bfmeEnd;						// +0x08
};

inline unsigned int bfmeFindIndex(const BfmeVecAI *vector, int value)
{
	unsigned int index = 0;

	while (index < vector->bfmeSize())
	{
		if (value == vector->m_bfmeStart[index])
			return index;

		++index;
	}

	return (unsigned int)-1;
}

// ?bfmeRemoveValue@@YGXPAVBfmeVecAI@@H@Z
void __stdcall bfmeRemoveValue(BfmeVecAI *vector, int value)
{
	unsigned int index = bfmeFindIndex(vector, value);

	if (index != (unsigned int)-1)
		vector->bfmeEraseAt(index);
}
