// A body that empties its vector and refills it from another object's, then
// marks a singleton dirty if it was asked to.
//
// The append is the usual inlined vector push: the fast path constructs in
// place, which is where the null test on the finish pointer comes from, and
// the full path calls the out-of-line insert with the value by address. Here
// the value is the element being copied, so its address is the loop cursor
// itself.
//
// The third argument of that insert is the caller's own flag by address: it
// lands on the parameter slot the flag arrives in, which is the slot read
// again after the loop. A one-byte temporary of the caller's own would sit in
// the other parameter slot instead.

extern "C" __declspec(dllimport) void * __cdecl memmove(void *destination, const void *source, unsigned int bytes);

inline int *bfmeCopyRange(int *destination, const int *first, const int *last)
{
	if (first == last)
		return destination;

	int bytes = (const char *)last - (const char *)first;

	return (int *)((char *)memmove(destination, first, bytes) + bytes);
}

class BfmeVecAE
{
public:
	void bfmeErase(int *first, int *last)
	{
		m_bfmeFinish = bfmeCopyRange(first, last, m_bfmeFinish);
	}

	void bfmeClear(void)
	{
		bfmeErase(m_bfmeStart, m_bfmeFinish);
	}

	void bfmeAppend(const int &value, bool *flag)
	{
		if (m_bfmeFinish != m_bfmeEnd)
		{
			if (m_bfmeFinish)
				*m_bfmeFinish = value;

			++m_bfmeFinish;
		}
		else
		{
			bfmeInsertOverflow(m_bfmeFinish, &value, flag, 1, 1);
		}
	}

	void bfmeInsertOverflow(int *position, const int *value, bool *flag, int count, int atEnd);
								// retail thunk 0x0000A240 -> 0x0040A240

	int *m_bfmeStart;					// +0x00
	int *m_bfmeFinish;					// +0x04
	int *m_bfmeEnd;						// +0x08
};

class BfmeDirtyAE
{
public:
	int m_bfmeHead[9];					// +0x00
	bool m_bfmeDirty;					// +0x24
};

extern BfmeDirtyAE *g_bfmeDirtyAE;				// retail 0x012F33F8

class Gen_0049C4B0
{
public:
	void bfmeCopyFrom(Gen_0049C4B0 *source, bool notify);

private:
	int m_bfmeHead[78];					// +0x000
	BfmeVecAE m_bfmeVector;					// +0x138
};

// ?bfmeCopyFrom@Gen_0049C4B0@@QAEXPAV1@_N@Z
void Gen_0049C4B0::bfmeCopyFrom(Gen_0049C4B0 *source, bool notify)
{
	m_bfmeVector.bfmeClear();

	for (int *it = source->m_bfmeVector.m_bfmeStart; it < source->m_bfmeVector.m_bfmeFinish; ++it)
		m_bfmeVector.bfmeAppend(*it, &notify);

	if (notify)
		g_bfmeDirtyAE->m_bfmeDirty = true;
}
