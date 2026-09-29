// ?clear@Rva008A18C0Holder@@QAEXXZ
// partial score=0.7578 date=2026-09-29
// Retail 0x008A18C0 (128 bytes, thiscall): empties an Apt value holder.  For
// every held value it first winds down the live display nodes -- a type-0x0E
// value whose +0x50 record has no +0x1C link gets state 1
// (BfmeNode1285::bfmeSetState1285), a type-0x0D value whose record still has
// the -1 frame marker at +0x18 is activated (BfmeNode1236::bfmeActivate1236)
// -- then releases the value and finally zeroes the count.  The Apt dispatch
// reaches it only through generated code, so the holder keeps the address.

struct Info
{
	char m_pad00[0x18];
	int m_frame;
	void *m_link;
};

class AptValue
{
public:
	virtual void AddRef();
	virtual void Release();

	bool isLive(char type) const
	{
		unsigned int bits = m_valueBits;
		return (char)(bits & 0x3f) == type && !((unsigned char)~(bits >> 15) & 1);
	}

	bool isUndefined() const
	{
		return (m_valueBits >> 15 & 1) == 0;
	}

	unsigned int m_valueBits;
	char m_pad08[0x48];
	Info *m_record;
};

class BfmeNode1285
{
public:
	void bfmeSetState1285(int state);
};

class BfmeNode1236
{
public:
	void bfmeActivate1236();
};

class Rva008A18C0Holder
{
public:
	void clear();

	char m_pad00[0x0c];
	AptValue **m_values;
	int m_count;
};

void Rva008A18C0Holder::clear()
{
	for (int i = 0; i < m_count; ++i)
	{
		AptValue *value = m_values[i];
		if (value->isLive(0x0e))
		{
			if (value->m_record->m_link == 0)
				((BfmeNode1285 *)value)->bfmeSetState1285(1);
		}
		else if (value->isLive(0x0d))
		{
			if (value->m_record->m_frame == -1)
				((BfmeNode1236 *)value)->bfmeActivate1236();
		}
		m_values[i]->Release();
	}
	m_count = 0;
}
