// ?d_00236930@@YAXXZ
// partial score=0.71 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
// stlport

#include <new>
#include <stdlib.h>

class INI
{
public:
	const char *getNextTokenOrNull(const char *text);

private:
	unsigned char m_pad00[0x414];
	const char *m_text;

	friend void bfmeParseIntList(INI *ini, struct BfmeIntList *values);
};

struct BfmeIntNode
{
	BfmeIntNode *m_next;
	BfmeIntNode *m_previous;
	int m_value;
};

struct BfmeIntList
{
	BfmeIntNode *m_header;

	void pushBack(int value);
};

void *bfmeAlloc1046(int size);

inline void BfmeIntList::pushBack(int value)
{
	BfmeIntNode *header = m_header;
	BfmeIntNode *node = static_cast<BfmeIntNode *>(bfmeAlloc1046(sizeof(BfmeIntNode)));
	new (&node->m_value) int(value);
	BfmeIntNode *previous = header->m_previous;
	node->m_previous = previous;
	node->m_next = header;
	previous->m_next = node;
	header->m_previous = node;
}

void bfmeParseIntList(INI *ini, BfmeIntList *values)
{
	INI *iniLocal = ini;
	const char *token = iniLocal->getNextTokenOrNull(iniLocal->m_text);
	if (token != 0)
	{
		BfmeIntList *valuesLocal = values;
		do
		{
			valuesLocal->pushBack(atoi(token));
			token = iniLocal->getNextTokenOrNull(iniLocal->m_text);
		} while (token != 0);
	}
}
