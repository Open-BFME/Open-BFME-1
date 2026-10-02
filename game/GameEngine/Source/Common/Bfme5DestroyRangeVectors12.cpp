// Two more destroy-range vector destroys, over twelve-byte elements.
//
// Same source as the four-byte pair: hand start, finish and the address of an
// uninitialised char to a destroy helper, then free the block by size. The
// width shows in the magic divide and the multiply back rather than a shift
// pair, and it costs the extra callee-saved register the four-byte version
// does not need.

void __cdecl bfmeFreeScalar(void *block);			// retail 0x00881EB0
void __cdecl bfmeDeallocate(void *block, unsigned int bytes);	// retail 0x0082E5F0

inline void bfmeRelease(void *block, unsigned int bytes)
{
	if (bytes > 0x80)
		bfmeFreeScalar(block);
	else
		bfmeDeallocate(block, bytes);
}

struct BfmeElem12 { int m_bfmeWords[3]; };

class AsciiString;

namespace _STL
{
struct __false_type;

template <class T>
void __destroy_aux(T first, T last, const __false_type &tag);
}

class Gen_006FA4E0
{
public:
	void bfmeDestroy(void);

private:
	BfmeElem12 *m_bfmeStart;				// +0x00
	BfmeElem12 *m_bfmeFinish;				// +0x04
	BfmeElem12 *m_bfmeEnd;					// +0x08
};

class Gen_006FA5B0
{
public:
	void bfmeDestroy(void);

private:
	BfmeElem12 *m_bfmeStart;				// +0x00
	BfmeElem12 *m_bfmeFinish;				// +0x04
	BfmeElem12 *m_bfmeEnd;					// +0x08
};

// ?bfmeDestroy@Gen_006FA4E0@@QAEXXZ
void Gen_006FA4E0::bfmeDestroy(void)
{
	char tag;

	_STL::__destroy_aux((AsciiString *)m_bfmeStart,
		(AsciiString *)m_bfmeFinish, (const _STL::__false_type &)tag);

	BfmeElem12 *start = m_bfmeStart;

	if (start)
		bfmeRelease(start, sizeof(BfmeElem12) * (m_bfmeEnd - start));
}

// ?bfmeDestroy@Gen_006FA5B0@@QAEXXZ
void Gen_006FA5B0::bfmeDestroy(void)
{
	char tag;

	_STL::__destroy_aux((AsciiString *)m_bfmeStart,
		(AsciiString *)m_bfmeFinish, (const _STL::__false_type &)tag);

	BfmeElem12 *start = m_bfmeStart;

	if (start)
		bfmeRelease(start, sizeof(BfmeElem12) * (m_bfmeEnd - start));
}
