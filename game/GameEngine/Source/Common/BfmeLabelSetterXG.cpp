// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the guarded label setter at retail 0x000ED960, 85 bytes.  The
// label arrives by value -- its address is taken out of the argument slot for
// set and again for the trailing release -- and the store is skipped when the
// target is absent.

// The by-value label is retail's AsciiString: its unwind funclet jumps to
// ??1AsciiString (ILT 0x0000D828 -> 0x0005EE90) and the scope exit calls
// StringBase<char>::releaseBuffer (0x00887940) inline, which is what the
// header's inline destructor gives.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class BfmeStrXG : private AsciiString
{
public:
	void bfmeSetXG(const AsciiString &other)
	{
		((StringBase<char> *)this)->set(*(const StringBase<char> *)&other);
	}
};

class BfmeTargetXG
{
public:
	char m_bfmePad000[0x270];				// +0x000
	BfmeStrXG m_bfmeLabel;					// +0x270
};

class Gen_000ED960
{
public:
	void bfmeApplyXG(AsciiString value);

	int m_bfme00;						// +0x00
	BfmeTargetXG *m_bfmeTarget;				// +0x04
};

// ?bfmeApplyXG@Gen_000ED960@@QAEXVAsciiString@@@Z
void Gen_000ED960::bfmeApplyXG(AsciiString value)
{
	if (m_bfmeTarget != 0)
		m_bfmeTarget->m_bfmeLabel.bfmeSetXG(value);
}
