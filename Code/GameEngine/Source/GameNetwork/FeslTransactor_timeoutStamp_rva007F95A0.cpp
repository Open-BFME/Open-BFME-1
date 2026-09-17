// cl: /O2 /GX- /GS-
// Retail 0x007F95A0 is the FESL request-slot timeout stamp helper.  The
// direct call from the fresh 0x007FA4D0 body supplies a slot and timeout;
// 0x007FA170 and 0x007FA240 establish the same slot stride and watermark
// fields.  The original owner/member name is not recoverable from the
// callers, so the method remains address-derived.

struct Rva007E9B70Obj
{
public:
	virtual void v0();
	virtual void v1();
	virtual int v2();
};

Rva007E9B70Obj *Rva007E9B70Get();

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Rva007FA170Slot
{
	char m_pad00[0x14];
	unsigned m_expiry;
};

class Rva007FA2C0
{
public:
	void rva007F95A0(Rva007FA170Slot *slot, unsigned timeout);

private:
	char m_pad00[0x18];
	unsigned m_watermark;
};

void Rva007FA2C0::rva007F95A0(Rva007FA170Slot *slot, unsigned timeout)
{
	unsigned now = (unsigned)Rva007E9B70Get()->v2();
	unsigned delay = timeout;
	Rva007FA170Slot *target = slot;
	_ReadWriteBarrier();
	unsigned expiry = now + delay;
	target->m_expiry = expiry;
	if (m_watermark == 0 || expiry < m_watermark)
		m_watermark = expiry;
}
