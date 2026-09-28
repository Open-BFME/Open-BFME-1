// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// The 0x009F2A20 and 0x009F2A40 forwarders name this result maker.  The
// 0x009F39F0 constructor, 0x009F3C00 append method, and 0x009F2A70 predicate
// identify its result payload and linked-node filtering behavior.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

class BfmeThingEQ
{
public:
	unsigned char bfmeAskEQ(void *what);
};

class BfmeResultNodeItem
{
public:
	virtual void bfmeSpare000(void) = 0;
	virtual void bfmeSpare001(void) = 0;
	virtual void bfmeSpare002(void) = 0;
	virtual void *bfmeGetResultThing(void) = 0;
};

struct BfmeResultNode
{
	void *m_bfmeUnused;
	BfmeResultNodeItem *m_bfmeItem;
	void *m_bfmeUnused2;
	BfmeResultNode *m_bfmeNext;
};

class OCLSpecialPowerModuleData
{
public:
	struct Upgrades
	{
		int m_bfmeFirst;
		int m_bfmeSecond;
	};
};

struct Rva009F39F0Payload
{
	_STL::vector<OCLSpecialPowerModuleData::Upgrades> m_items;
	void *m_cursor;
	int m_refCount;
};

struct Rva009F39F0Result
{
	Rva009F39F0Payload *m_value;

	Rva009F39F0Result();
	void append(int first, int second);
};

typedef Rva009F39F0Payload BfmeResultPayload;

struct BfmeResultA : private Rva009F39F0Result
{
	BfmeResultA()
		: Rva009F39F0Result()
	{
	}
	__forceinline BfmeResultA(const BfmeResultA &that)
		: Rva009F39F0Result(*(const Rva009F39F0Result *)&that)
	{
		m_value = that.m_value;
		++m_value->m_refCount;
	}

	__forceinline ~BfmeResultA()
	{
		--m_value->m_refCount;
		if (m_value->m_refCount == 0)
		{
			BfmeResultPayload *payload = m_value;
			payload->m_items.~vector();
			::operator delete(payload);
		}
	}
};

class BfmeResultSourceA
{
	unsigned char m_bfmePadding[0xE4];
	BfmeResultNode *m_bfmeHead;

public:
	BfmeResultA bfmeMakeResultA(int value);
};

BfmeResultA BfmeResultSourceA::bfmeMakeResultA(int value)
{
	BfmeResultA result;
	BfmeResultNode *node = m_bfmeHead;

	while (node != 0)
	{
		void *thing = node->m_bfmeItem->bfmeGetResultThing();

		if (thing != 0 && (value == 0 || ((BfmeThingEQ *)value)->bfmeAskEQ(thing) != 0))
			((Rva009F39F0Result *)&result)->append((int)thing, 0);

		node = node->m_bfmeNext;
	}

	return result;
}
