// ?rva002E9590ParseScriptedEvent@LuaScriptEngine@@QAEXPAVBfmeLexEAN@@@Z
// partial score=0.5914 date=2026-09-28
// ?rva002E9590ParseScriptedEvent@LuaScriptEngine@@QAEXPAVBfmeLexEAN@@@Z present-unmatched
// Retail 0x002E9590, 186 bytes. The matched 0x002EA5D0 caller proves the
// LuaScriptEngine/BfmeLexEAN ABI; the parser argument slot is reused for the
// temporary BfmeThing adapters, and the vector begins at LuaScriptEngine+0x7c.
//
// cl: /DNDEBUG /MD /O2 /Ob0
#include <string.h>
#pragma intrinsic(memcmp)

typedef int Int;

extern void j_00038fc8();
extern void j_0003a5fd();
extern void j_00027a7a();
extern void j_00025e1e();
extern void j_00022bf6();
extern void j_00017c38();
extern void j_00049ae4();

class XmlNameSlotList
{
public:
	__forceinline Int count()
	{
		typedef Int (XmlNameSlotList::*CountThunk)();
		union
		{
			void (*function)();
			CountThunk member;
		} thunk;
		thunk.function = j_00038fc8;
		return (this->*thunk.member)();
	}

	__forceinline const char *tagAt(Int index)
	{
		typedef const char *(XmlNameSlotList::*GetThunk)(Int);
		union
		{
			void (*function)();
			GetThunk member;
		} thunk;
		thunk.function = j_0003a5fd;
		return (this->*thunk.member)(index);
	}

	__forceinline const char *nameAt(Int index)
	{
		typedef const char *(XmlNameSlotList::*GetThunk)(Int);
		union
		{
			void (*function)();
			GetThunk member;
		} thunk;
		thunk.function = j_00027a7a;
		return (this->*thunk.member)(index);
	}

	__forceinline Int finish()
	{
		typedef Int (XmlNameSlotList::*FinishThunk)();
		union
		{
			void (*function)();
			FinishThunk member;
		} thunk;
		thunk.function = j_00049ae4;
		return (this->*thunk.member)();
	}
};
class BfmeLexEAN;


class BfmeThingVKT
{
public:
	__forceinline void bfmeBaseVKT()
	{
		typedef void (BfmeThingVKT::*BaseThunk)();
		union
		{
			void (*function)();
			BaseThunk member;
		} thunk;
		thunk.function = j_00025e1e;
		(this->*thunk.member)();
	}
};

class BfmeThingBLC
{
public:
	__forceinline void bfmeGoBLC(void *what)
	{
		typedef void (BfmeThingBLC::*GoThunk)(void *);
		union
		{
			void (*function)();
			GoThunk member;
		} thunk;
		thunk.function = j_00022bf6;
		(this->*thunk.member)(what);
	}

	void *m_bfmeGot;
};

class Rva002E9590Vector
{
public:
	void **m_start;
	void **m_cur;
	void **m_end;

	__forceinline void insertHelper(void **position,
		void *const *source, void *temporary, Int one1, Int one2)
	{
		typedef void (Rva002E9590Vector::*InsertThunk)(
			void **, void *const *, void *, Int, Int);
		union
		{
			void (*function)();
			InsertThunk member;
		} thunk;
		thunk.function = j_00017c38;
		(this->*thunk.member)(position, source, temporary, one1, one2);
	}
};

class __declspec(novtable) SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	void *m_name;
};

class __declspec(novtable) LuaScriptEngine : public SubsystemInterface
{
public:
	void rva002E9590ParseScriptedEvent(BfmeLexEAN *parser);

private:
	char m_pad08To7c[0x74];
	Rva002E9590Vector m_eventCapacity;
};

void LuaScriptEngine::rva002E9590ParseScriptedEvent(BfmeLexEAN *parser)
{
	LuaScriptEngine * volatile owner = this;
	XmlNameSlotList &xml = *(XmlNameSlotList *)parser;
	Int i = 0;
	if (xml.count() > 0)
	{
		do
		{
			int diff = memcmp(xml.tagAt(i), "Name", 5);
			if (diff == 0)
			{
				const char *value = xml.nameAt(i);
				((BfmeThingVKT *)&parser)->bfmeBaseVKT();
				((BfmeThingBLC *)&parser)->bfmeGoBLC((void *)value);

				LuaScriptEngine *ownerValue = owner;
				void **current = ownerValue->m_eventCapacity.m_cur;
				void **end = ownerValue->m_eventCapacity.m_end;
				Rva002E9590Vector *vector = &ownerValue->m_eventCapacity;
				if (current != end)
				{
					if (current)
						*current = ((BfmeThingBLC *)&parser)->m_bfmeGot;
					vector->m_cur++;
				}
				else
				{
					vector->insertHelper(current,
						(void *const *)&((BfmeThingBLC *)&parser)->m_bfmeGot,
						(void *)&parser, 1, 1);
				}
			}
			++i;
		} while (i < xml.count());
	}
	xml.finish();
}
