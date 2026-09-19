// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

class Rva0019C520Member
{
public:
	int lookup(AsciiString *name, int extra);
};

class Rva0019C520Owner
{
public:
	int forward(AsciiString name, int extra);

private:
	char m_head[0x630];
	Rva0019C520Member m_member;
};

int Rva0019C520Owner::forward(AsciiString name, int extra)
{
	return m_member.lookup(&name, extra);
}
