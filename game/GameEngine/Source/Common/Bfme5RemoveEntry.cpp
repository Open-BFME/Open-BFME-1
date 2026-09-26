// A remove that tells the singleton first and then takes the entry out of its
// vector wherever it appears.
//
// The loop does not stop at the first match: the span is recomputed on every
// pass and the erase only moves the tail down, so the walk carries on with the
// same index. The copier is hoisted into a register because the call sits
// inside a loop.

extern "C" __declspec(dllimport) void * __cdecl memmove(void *destination, const void *source, unsigned int bytes);

class BfmeItemAM
{
public:
	int m_bfmePad[2];					// +0x00
	int m_bfmeHandle;					// +0x08
};

class BfmeSinkAM
{
public:
	void bfmeDrop(int handle);				// retail thunk 0x00010FFA -> 0x003C6D40
};

extern BfmeSinkAM *g_bfmeSinkAM;				// retail 0x012F706C

class BfmeVecAM
{
public:
	unsigned int bfmeSize(void) const
	{
		return (unsigned int)(m_bfmeFinish - m_bfmeStart);
	}

	BfmeItemAM **bfmeBegin(void) const
	{
		return m_bfmeStart;
	}

	void bfmeErase(BfmeItemAM **position)
	{
		BfmeItemAM **next = position + 1;

		if (m_bfmeFinish != next)
			memmove(position, next, (char *)m_bfmeFinish - (char *)next);

		--m_bfmeFinish;
	}

	BfmeItemAM **m_bfmeStart;				// +0x00
	BfmeItemAM **m_bfmeFinish;				// +0x04
	BfmeItemAM **m_bfmeEnd;					// +0x08
};

class Gen_003BEBA0
{
public:
	void bfmeRemove(BfmeItemAM *entry);

private:
	int m_bfmeHead[14];					// +0x00
	BfmeVecAM m_bfmeVector;					// +0x38
};

// ?bfmeRemove@Gen_003BEBA0@@QAEXPAVBfmeItemAM@@@Z
void Gen_003BEBA0::bfmeRemove(BfmeItemAM *entry)
{
	if (!entry)
		return;

	g_bfmeSinkAM->bfmeDrop(entry->m_bfmeHandle);

	for (unsigned int index = 0; index < m_bfmeVector.bfmeSize(); ++index)
	{
		BfmeItemAM **position = m_bfmeVector.bfmeBegin() + index;

		if (*position == entry)
			m_bfmeVector.bfmeErase(position);
	}
}
