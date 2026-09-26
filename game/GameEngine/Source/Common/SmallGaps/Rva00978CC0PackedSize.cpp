// ?packedSize@Rva00978CC0Owner@@QBEHXZ
#include <string.h>
#pragma intrinsic(strlen)
struct Rva00978CC0Owner { int m_0; int m_count; const char** m_strings; int packedSize() const; };
int Rva00978CC0Owner::packedSize() const
{
	int total = m_count * 8 + 16;
	for (int i = 0; i < m_count; ++i)
		total += strlen(m_strings[i]) + 1;
	return total;
}
