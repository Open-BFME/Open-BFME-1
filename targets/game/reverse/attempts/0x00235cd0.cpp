// ?d_00235cd0@@YAXXZ
// partial score=0.78 date=2026-08-30
// cl: /DNDEBUG /MD /EHsc

#include <string.h>

typedef unsigned int UnsignedInt;

struct BfmeRecord16
{
	UnsignedInt m_words[4];

};

struct BfmeRecord20
{
	UnsignedInt m_first;
	BfmeRecord16 m_rest;
};

void bfmeCopyOptional20(BfmeRecord20 *destination, const BfmeRecord20 *source)
{
	if (destination != 0)
	{
		destination->m_first = source->m_first;
		memcpy(&destination->m_rest, &source->m_rest, sizeof(destination->m_rest));
	}
}
