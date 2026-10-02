// The dword-sized string member at +0x0C is an AsciiString: retail assigns it
// with `StringBase<char>::set(const StringBase<char> &)` (0x00887C90), reached
// through the wrapper's inline forwarder so the call target is the header's.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class Rva0036CA00Str
{
public:
	void set(const Rva0036CA00Str &other) { m_str.set(other.m_str); }

private:
	AsciiString m_str;
};

class Rva000EB280
{
	char m_00[0x0C];
	Rva0036CA00Str m_0C;
	int m_10;

public:
	void set(const Rva0036CA00Str &s, int v);
};

void Rva000EB280::set(const Rva0036CA00Str &s, int v)
{
	m_0C.set(s);
	m_10 = v;
}