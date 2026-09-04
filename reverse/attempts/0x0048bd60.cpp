// ?bfmeParse_0048BD60@@YAXPAVBfmeIni@@PAUBfmeParsedHolder@@@Z
// partial score=0.9 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /MD /EHsc

#include <new>

class BfmeIni
{
public:
	void initFromINI(void *object, const void *fieldTable);
};

struct BfmeParsed0048BD60
{
	BfmeParsed0048BD60()
	{
		field0 = 0;
		field4 = 0;
		field14 = 0;
		field8 = 0;
		fieldC = 0;
		field10 = 0;
	}
	unsigned int field0;
	unsigned int field4;
	unsigned int field8;
	unsigned int fieldC;
	unsigned int field10;
	unsigned int field14;
};

struct BfmeParsedNode0048BD60
{
	BfmeParsedNode0048BD60 *previous;
	BfmeParsedNode0048BD60 *next;
	BfmeParsed0048BD60 *value;
};

struct BfmeParsedList0048BD60
{
	BfmeParsedNode0048BD60 *head;
};

struct BfmeParsedHolder
{
	unsigned int unused;
	BfmeParsedList0048BD60 list;
};

struct BfmeParsedValue0048BD60
{
	explicit BfmeParsedValue0048BD60(BfmeParsed0048BD60 *parsed) : value(parsed) {}
	BfmeParsed0048BD60 *value;
};

extern const unsigned char Rva0048BD60FieldTable[];
void *bfmeNodeAllocate0048BD60(unsigned int bytes);

static __forceinline void bfmeAppend0048BD60(
	BfmeParsed0048BD60 *parsed,
	BfmeParsedNode0048BD60 *position)
{
	BfmeParsedNode0048BD60 *node =
		static_cast<BfmeParsedNode0048BD60 *>(bfmeNodeAllocate0048BD60(12));
	new (&node->value) BfmeParsedValue0048BD60(parsed);
	BfmeParsedNode0048BD60 *next = position->next;
	node->previous = position;
	node->next = next;
	next->previous = node;
	position->next = node;
}

void bfmeParse_0048BD60(BfmeIni *ini, BfmeParsedHolder *holder)
{
	BfmeParsedNode0048BD60 *position = holder->list.head;
	BfmeParsed0048BD60 *parsed = new BfmeParsed0048BD60;
	ini->initFromINI(parsed, Rva0048BD60FieldTable);
	if (parsed)
		bfmeAppend0048BD60(parsed, position);
}
