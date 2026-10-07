// cl: /O2 /Ob0 /Igame

// Both retail calls are StringBase<char>::set at 0x00887C90; the opaque
// member type keeps the ledgered name and is only that string base.
#include "Libraries/Source/WWVegas/WWLib/string_base.h"

class Rva0036CA00Str : public StringBase<char>
{
};

class Rva000DF920
{
	Rva0036CA00Str *m_00;
	Rva0036CA00Str *m_04;

public:
	Rva000DF920 &operator=(const Rva0036CA00Str *pair);
};

Rva000DF920 &Rva000DF920::operator=(const Rva0036CA00Str *pair)
{
	m_00->set(pair[0]);
	m_04->set(pair[1]);
	return *this;
}
