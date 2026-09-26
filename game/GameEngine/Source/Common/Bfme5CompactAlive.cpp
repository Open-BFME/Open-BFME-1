// A compaction that drops the entries whose owner says they are done and
// hands the vector back to the caller.
//
// Two things settle the shape of an erase-in-loop. The pointer one past the
// cursor is not a source variable: the erase takes only the position and
// computes it, and MSVC turns that into a second induction variable advanced
// with the cursor -- writing it out at this level costs the register rotation
// and the wrong shrink-wrap. And the erase has to be the body of the if, not
// the else, so that it is what falls through.

extern "C" __declspec(dllimport) void * __cdecl memmove(void *destination, const void *source, unsigned int bytes);

class BfmeItemAK
{
public:
	bool bfmeIsAlive(void);					// retail thunk 0x00001C03 -> 0x00401C03
};

class BfmeVecAK
{
public:
	BfmeItemAK **bfmeBegin(void) const
	{
		return m_bfmeStart;
	}

	BfmeItemAK **bfmeEnd(void) const
	{
		return m_bfmeFinish;
	}

	void bfmeErase(BfmeItemAK **position)
	{
		BfmeItemAK **next = position + 1;

		if (next != m_bfmeFinish)
			memmove(position, next, (char *)m_bfmeFinish - (char *)next);

		--m_bfmeFinish;
	}

	BfmeItemAK **m_bfmeStart;				// +0x00
	BfmeItemAK **m_bfmeFinish;				// +0x04
	BfmeItemAK **m_bfmeEnd;					// +0x08
};

class Gen_0018BC70
{
public:
	BfmeVecAK *bfmeCompact(bool restart);

private:
	void bfmeRestart(void);					// retail thunk 0x0003F1FC -> 0x0043F1FC
	void bfmeResume(void);					// retail thunk 0x0000764E -> 0x0040764E

	int m_bfmeHead[4];					// +0x00
	BfmeVecAK m_bfmeVector;					// +0x10
};

// ?bfmeCompact@Gen_0018BC70@@QAEPAVBfmeVecAK@@_N@Z
BfmeVecAK *Gen_0018BC70::bfmeCompact(bool restart)
{
	if (restart)
		bfmeRestart();
	else
		bfmeResume();

	BfmeItemAK **it = m_bfmeVector.bfmeBegin();

	while (it != m_bfmeVector.bfmeEnd())
	{
		if (!(*it)->bfmeIsAlive())
			m_bfmeVector.bfmeErase(it);
		else
			++it;
	}

	return &m_bfmeVector;
}
