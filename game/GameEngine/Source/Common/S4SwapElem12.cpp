// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// Open-BFME5: swap of the twelve-byte char-string-int record, retail
// 0x0052E370, 152 bytes.  Same layout gen00531D80 copies; the temporary goes
// through StringBase<char>'s copy ctor at 0x00887B60 and set at 0x00887C90.

#include "string_base.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString(void) {}
	AsciiString &operator=(const AsciiString &other)
	{
		set(other);
		return *this;
	}
};

struct S4SortElem12
{
	char m_bfmeC;
	AsciiString m_bfmeName;
	int m_bfmeA;
};

void bfmeSwapElem12(S4SortElem12 &left, S4SortElem12 &right)
{
	S4SortElem12 temporary(left);
	left = right;
	right = temporary;
}
