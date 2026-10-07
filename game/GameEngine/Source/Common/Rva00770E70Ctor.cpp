// cl: /O2 /Ob0 /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

// The empty literal at VA 0x0107301C (retail .rdata: a zero byte, padded, ahead of
// the "Lang\\%s\\Lotr.csf" string at 0x01073020); this constructor pushes it.
extern const char g_Rva0107301CEmptyString[] = "";

class Rva00770E70
{
public:
	Rva00770E70();

private:
	AsciiString text;
	int first;
	int second;
	int third;
	int fourth;
};

Rva00770E70::Rva00770E70()
	: text(g_Rva0107301CEmptyString)
{
	first = 0;
	second = 0;
	third = 0;
	fourth = 0;
}
