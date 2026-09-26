// A vector clear that destroys its elements through an out-of-line helper
// taking the vector by address, then copies the empty range over itself.

extern "C" __declspec(dllimport) void * __cdecl memmove(void *destination, const void *source, unsigned int bytes);

class BfmeVecAW;

void __cdecl bfmeDestroyRange(BfmeVecAW *vector);		// retail thunk 0x00034DC9 -> 0x00434DC9

inline int *bfmeCopyRange(int *destination, const int *first, const int *last)
{
	if (first == last)
		return destination;

	int bytes = (const char *)last - (const char *)first;

	return (int *)((char *)memmove(destination, first, bytes) + bytes);
}

class BfmeVecAW
{
public:
	void bfmeClear(void);

	void bfmeErase(int *first, int *last)
	{
		m_bfmeFinish = bfmeCopyRange(first, last, m_bfmeFinish);
	}

	int *m_bfmeStart;					// +0x00
	int *m_bfmeFinish;					// +0x04
	int *m_bfmeEnd;						// +0x08
};

// ?bfmeClear@BfmeVecAW@@QAEXXZ
void BfmeVecAW::bfmeClear(void)
{
	bfmeDestroyRange(this);

	bfmeErase(m_bfmeStart, m_bfmeFinish);
}
