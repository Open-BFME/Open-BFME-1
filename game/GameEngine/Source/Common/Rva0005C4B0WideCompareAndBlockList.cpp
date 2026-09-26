// cl: /DNDEBUG /MD /EHs-c-
// Counted wide-character comparison and the related overflow-block release
// loop recovered from the retail image. Both identities are address-derived.

#include <stdlib.h>

typedef unsigned short WCHAR;

// ?Rva0005C4B0CompareWide@@YGHPBG0H@Z
int __stdcall Rva0005C4B0CompareWide(const WCHAR *a, const WCHAR *b, int count)
{
	while (count > 0) {
		if (*a != *b) {
			return (int)(unsigned int)*a - (int)(unsigned int)*b;
		}

		++a;
		++b;
		--count;
	}

	return 0;
}

struct Rva0005C660Block
{
	Rva0005C660Block *m_next;
};

class Rva0005C660BlockList
{
public:
	void releaseAll(void);

private:
	Rva0005C660Block *m_head;
};

// ?releaseAll@Rva0005C660BlockList@@QAEXXZ
void Rva0005C660BlockList::releaseAll(void)
{
	while (m_head != 0) {
		Rva0005C660Block *block = m_head;
		m_head = block->m_next;
		free(block);
	}
}
