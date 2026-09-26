#include <string.h>

struct Rva00980B60Definition
{
	char m_reserved[0x18];
	unsigned int m_count18;
	char m_reserved1c[0x3c];
	const char *m_name58;

	unsigned int encodedLength() const;
};

unsigned int Rva00980B60Definition::encodedLength() const
{
	unsigned int header = 92;
	if (m_name58)
		header += (unsigned int)strlen(m_name58) + 1;
	return header + m_count18 * 64;
}
