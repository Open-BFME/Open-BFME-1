// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x008C66A0 (129 bytes, RET at +0x7A and +0x80). Address-owned Apt
// callback: it reads the integer on the Apt stack top, and when that slot of
// the holder's 32-byte value-stack table is live, releases its +4 value,
// clears it, releases the whole stack and drops the live-slot count at
// holder+0x1234. Its registered name and semantic identity are unknown.

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

	void *m_value00;
	Rva008A0FF0Value *m_value04;
	int m_value08;
	int m_value0C;
	int m_value10;
	int m_count;
	int m_capacity;
	Rva008A0FF0Value **m_values;
};

struct Rva008AE770Stack
{
	int m_count;
	int m_rva0133874C;
	AptValue **m_rva01338750;
};

extern Rva008AE770Stack Rva008AE770TheStack;
extern AptValue *g_bfmeFallbackDB;
// retail 0x013377D8; its one definition is ?g_bfmeHolderBU@@3PAUBfmePickWorld1284@@A
struct BfmePickWorld1284;
extern BfmePickWorld1284 *g_bfmeHolderBU;

AptValue *__cdecl dup_008c66a0()
{
	// Native 0x008C66A0 loads VA 0x01338750: the existing stack's +8 field.
	// One volatile pointer read retains VC7.1's native array-before-count order.
	AptValue **values = *reinterpret_cast<AptValue ** volatile *>(&Rva008AE770TheStack.m_rva01338750);
	AptValue *arg = values[Rva008AE770TheStack.m_count - 1];
	if (!arg->isUndefined())
	{
		int index = arg->toInteger();
		char *holder = ((char *)g_bfmeHolderBU);
		if (((Rva008A0FF0ValueStack *)*(char **)(holder + 0x1230))[index].m_value00)
		{
			((Rva008A0FF0ValueStack *)*(char **)(holder + 0x1230))[index].m_value04->release();
			((Rva008A0FF0ValueStack *)*(char **)(((char *)g_bfmeHolderBU) + 0x1230))[index].m_value00 = 0;
			((Rva008A0FF0ValueStack *)*(char **)(((char *)g_bfmeHolderBU) + 0x1230))[index].releaseAll();
			--*(int *)(((char *)g_bfmeHolderBU) + 0x1234);
		}
	}
	return g_bfmeFallbackDB;
}
