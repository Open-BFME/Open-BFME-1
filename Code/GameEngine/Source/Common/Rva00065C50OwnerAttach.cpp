// cl: /DNDEBUG /MD /EHs-c-
// ?attach@Rva00065C50Owner@@AAEXPAX@Z
//
// Copy-assign a (char*, dword) pair: self-assignment guard, operator delete[]
// the old buffer, operator new[] + byte copy when the source buffer is live,
// otherwise store null, then copy the dword at +4.

#include <string.h>

void *__cdecl operator new[](unsigned int n);
void __cdecl operator delete[](void *block);

class Rva00065C50Owner
{
public:
	Rva00065C50Owner(void *source);

private:
	Rva00065C50Owner *attach(void *source);

	char *m_str;
	int m_value;
};

Rva00065C50Owner *Rva00065C50Owner::attach(void *source)
{
	Rva00065C50Owner *src = (Rva00065C50Owner *)source;

	if (this != src)
	{
		::operator delete[](m_str);
		if (src->m_str)
		{
			char *d = (char *)::operator new[](strlen(src->m_str) + 1);
			m_str = d;
			strcpy(d, src->m_str);
		}
		else
			m_str = 0;

		m_value = src->m_value;
	}

	return this;
}
