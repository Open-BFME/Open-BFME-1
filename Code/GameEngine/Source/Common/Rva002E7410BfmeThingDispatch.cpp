// cl: /DNDEBUG /MD /EHsc /O2
//
// Address-derived reconstruction of retail RVA 0x002E7410, 225 bytes.
// The matched BfmeThingVKQ test at 0x002E0380 proves the 0x54-byte record
// type and the two BfmeBlockVKQ filter arguments.  Retail walks the range
// at this+0x98 .. this+0x9c and sends qualifying records to the existing
// three-argument event-dispatch thunk at ILT 0x0003D4E7.  The temporary list
// shape is independently established by the DelayedLuaEventList constructor
// and destructor bodies at 0x000EDBB0 and 0x000EDC40.

class Object;

class BfmeBlockVKQ
{
};

class BfmeThingVKQ
{
public:
	char bfmeTestVKQ(BfmeBlockVKQ &filter); // 0x002E0380

private:
	char m_bfmeBody[0x54];
};

class BfmeDelayedLuaEvent
{
public:
	BfmeDelayedLuaEvent(void);             // ILT 0x0003A1C5
	~BfmeDelayedLuaEvent(void);            // ILT 0x00041362

private:
	char m_bfmeBody[0x18];
};

class BfmeBaseVUQ
{
public:
	virtual ~BfmeBaseVUQ(void) {}
};

class DelayedLuaEventList : public BfmeBaseVUQ
{
public:
	BfmeDelayedLuaEvent m_bfmeEvents[3];
};

// This local view uses the ABI already pinned independently at 0x0003D4E7.
// Its name does not assign an identity to this address-derived owner.
struct BfmeDelayedLuaEventList;

struct BfmeObjectEventDispatch
{
	void invoke(void *record, void *object, BfmeDelayedLuaEventList *events);
};

class Rva002E7410
{
public:
	void dispatch(BfmeBlockVKQ *first, BfmeBlockVKQ *second,
		Object *object);

private:
	char m_bfmePad[0x98];
	BfmeThingVKQ *m_bfmeBegin; // +0x98
	BfmeThingVKQ *m_bfmeEnd;   // +0x9c
};

void Rva002E7410::dispatch(BfmeBlockVKQ *first,
	BfmeBlockVKQ *second, Object *object)
{
	for (BfmeThingVKQ *it = m_bfmeBegin; it != m_bfmeEnd; ++it)
	{
		if (it->bfmeTestVKQ(*first) && !it->bfmeTestVKQ(*second))
		{
			DelayedLuaEventList events;
			reinterpret_cast<BfmeObjectEventDispatch *>(this)->invoke(
				it, object,
				reinterpret_cast<BfmeDelayedLuaEventList *>(&events));
		}
	}
}
