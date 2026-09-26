// cl: /DNDEBUG /MD /EHsc
//
// Address-derived reconstruction of retail RVA 0x002BCEE0 (124 bytes).
// The body constructs the native three-element delayed-Lua event list,
// copies the witnessed Object ID at +0x74 into the first event, and dispatches event
// 8 through the already matched BfmeOwnerBR wrapper.  No caller or emitter
// proves a semantic owner for this body, so the owner name remains opaque.

#include "../Object/object.h"

class BfmeDelayedLuaEvent
{
public:
	BfmeDelayedLuaEvent(void);             // ILT 0x0003A1C5
	~BfmeDelayedLuaEvent(void);            // ILT 0x00041362

	char m_pad0[0x0c];
	unsigned int m_value;
	char m_pad1[0x04];
	unsigned int m_count;
};

class BfmeDelayedLuaEventListBase
{
public:
	virtual ~BfmeDelayedLuaEventListBase(void) {}
};

class __declspec(novtable) DelayedLuaEventList : public BfmeDelayedLuaEventListBase
{
public:
	DelayedLuaEventList(void);             // ILT 0x00019CF9
	__forceinline ~DelayedLuaEventList(void) {}

	BfmeDelayedLuaEvent m_events[3];
};

class BfmeOwnerBR
{
public:
	void bfmeGo939B(int, Object *, DelayedLuaEventList *);
};

extern BfmeOwnerBR *g_bfmeOwnerBR;       // VA 0x012F060C

class Rva002BCEE0
{
public:
	void dispatch(void);

private:
	char m_pad[0x08];
	Object *m_object;
};

// ?dispatch@Rva002BCEE0@@QAEXXZ
void Rva002BCEE0::dispatch(void)
{
	DelayedLuaEventList events;
	Object *object = m_object;
	events.m_events[0].m_value = object->m_id;
	events.m_events[0].m_count = 3;
	g_bfmeOwnerBR->bfmeGo939B(8, object, &events);
}
