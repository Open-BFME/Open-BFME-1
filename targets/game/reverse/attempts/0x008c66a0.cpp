// ?dup_008c66a0@@YAPAVAptValue@@XZ
// partial score=0.4651 date=2026-09-30
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Address-owned Apt callback. Its registered name and semantic identity are unknown.

class AptValue
{
public:
	int toInteger() const;
	bool isUndefined() const { return ((m_valueBits >> 15) & 1) == 0; }

private:
	void *m_vtable;
	unsigned int m_valueBits;
};

class Rva008A0FF0Value
{
public:
	virtual void slot00();
	virtual void release();
};

class Rva008A0FF0ValueStack
{
public:
	void releaseAll();
	Rva008A0FF0Value *m_field00;
	Rva008A0FF0Value *m_field04;
	int m_field08;
	int m_field0c;
	int m_field10;
	int m_count;
	int m_capacity;
	Rva008A0FF0Value **m_values;
};

struct Rva008AE770Stack
{
	int m_count;
};

extern AptValue **g_bfmeArr1233;
extern AptValue *g_bfmeFallbackDB;
extern char * volatile Rva008A5380Holder;
extern Rva008AE770Stack Rva008AE770TheStack;

AptValue *__cdecl dup_008c66a0()
{
	AptValue *value = g_bfmeArr1233[Rva008AE770TheStack.m_count - 1];
	if (value->isUndefined())
		return g_bfmeFallbackDB;

	int index = value->toInteger();
	char *holder = Rva008A5380Holder;
	char *entries = *(char **)(holder + 0x1230);
	int offset = index << 5;
	if (*(void **)(offset + (unsigned int)entries))
	{
		((Rva008A0FF0ValueStack *)(offset + (unsigned int)entries))->m_field04->release();
		((Rva008A0FF0ValueStack *)(offset + (int)*(char **)(Rva008A5380Holder + 0x1230)))->m_field00 = 0;
		((Rva008A0FF0ValueStack *)(offset + (int)*(char **)(Rva008A5380Holder + 0x1230)))->releaseAll();
		--*(int *)(Rva008A5380Holder + 0x1234);
	}
	return g_bfmeFallbackDB;
}
