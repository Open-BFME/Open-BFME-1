// cl: /O2
// 0x007EA5E0 is the FESL service-hub notify pass that sits between the matched
// ?add@Rva007EAServiceList@@QAEXPAVRva00803080@@@Z (0x007EA550) and
// ?remove@Rva007EAServiceList@@QAEXPAVRva00803080@@ (0x007EA590) owners in
// Y2FeslServiceList.cpp, so the receiver and the eight-slot table at +0x10 come
// from those matched rows.  It walks all eight slots of that table exactly as
// ?add/?remove do, which is what identifies the class here.
//
// Body evidence: it calls the 0x007E9B70 singleton three times and dispatches
// vtable slots +0x0C, +0x08 and +0x10, passing the +0x08 result to each live
// service's slot 0 (one stack argument, as BfmeThingTWAConstructor.cpp declares
// it).  Rva007F8C90 follows when bit 1 of the byte at +0x08 is clear.  The
// +0x08 slot is the clock several matched FESL sources already call tick()/now(),
// so the value handed to the services is a timestamp, not a context pointer.
//
// The member's original name is not recoverable, so it keeps the descriptive
// name the earlier drafts used inside an address-derived class.

class Rva00803080
{
public:
	virtual void slot0(unsigned int stamp);
};

struct Rva007E9B70Obj
{
	virtual void v0();
	virtual void v1();
	virtual unsigned int slot08();
	virtual void slot0C();
	virtual void slot10();
};

Rva007E9B70Obj *Rva007E9B70Get();
void Rva007F8C90();

class Rva007EAServiceList
{
public:
	void dispatch();

private:
	char m_pad00[8];
	unsigned char m_flags;
	char m_pad09[7];
	Rva00803080 *m_slots[8];
};

void Rva007EAServiceList::dispatch()
{
	Rva007E9B70Get()->slot0C();
	unsigned int stamp = Rva007E9B70Get()->slot08();
	for (int i = 0; i < 8; ++i)
	{
		if (m_slots[i] != 0)
			m_slots[i]->slot0(stamp);
	}
	Rva007E9B70Get()->slot10();
	if ((m_flags & 2) == 0)
		Rva007F8C90();
}
