// A destructor that copies an empty range over itself.
//
// The "cmp eax,eax" and the subtraction of a register from itself are not dead
// code the compiler invented: they are a copy helper called with the same
// member for both ends of its range. The two parameters arrive in one register
// after inlining, and MSVC keeps the comparison and the difference it was
// asked for. Any hand-written self-comparison folds instead; only the two
// parameters reproduce it.
//
// The two zeroed fields are written with immediates rather than through a
// shared zero register because one of them is set before the copy and the
// other after. Putting both after lets MSVC share an xor and loses six bytes.

void __cdecl bfmeFreeScalar(void *block);			// retail 0x00881EB0
void __cdecl bfmeDeallocate(void *block, unsigned int bytes);	// retail 0x0082E5F0

extern void * (__cdecl *bfmeMemCopy)(void *destination, const void *source, unsigned int bytes);

inline void bfmeRelease(void *block, unsigned int bytes)
{
	if (bytes > 0x80)
		bfmeFreeScalar(block);
	else
		bfmeDeallocate(block, bytes);
}

inline int *bfmeCopyRange(int *destination, const int *first, const int *last)
{
	if (first == last)
		return destination;

	int bytes = (const char *)last - (const char *)first;

	return (int *)((char *)bfmeMemCopy(destination, first, bytes) + bytes);
}

class Gen_001DB2C0
{
public:
	~Gen_001DB2C0(void);

private:
	int *m_bfmeStart;					// +0x00
	int *m_bfmeFinish;					// +0x04
	int *m_bfmeEnd;						// +0x08
	int m_bfmeGap;						// +0x0C
	int m_bfmeCount;					// +0x10
};

// ??1Gen_001DB2C0@@QAE@XZ
Gen_001DB2C0::~Gen_001DB2C0(void)
{
	m_bfmeGap = 0;

	m_bfmeFinish = bfmeCopyRange(m_bfmeStart, m_bfmeFinish, m_bfmeFinish);

	m_bfmeCount = 0;

	int *start = m_bfmeStart;

	if (start)
		bfmeRelease(start, sizeof(int) * (m_bfmeEnd - start));
}
