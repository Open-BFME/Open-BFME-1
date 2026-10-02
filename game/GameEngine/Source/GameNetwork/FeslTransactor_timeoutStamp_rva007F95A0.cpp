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

// Retail 0x007E9B70 is a six-byte singleton getter: `mov eax,0x0130A580; ret`.
// It never reads `this`, so its only definition is the gen-shim skeleton
// Gen_007e9b70::m (game/gen_small/fun_005.cpp:129-130), and callers must reach it
// through that __thiscall spelling to link.  The earlier stand-in
// ?Rva007E9B70Get@@YAPAURva007E9B70Obj@@XZ was declared here and defined nowhere.
// Retail's `push esi; mov esi,ecx; call 0x7E9B70` leaves this in ecx already, so
// spelling the call as a member of `this` emits no receiver load and is
// byte-exact; the cast is sound only because the body ignores its receiver, and
// m() returns the singleton address that the next vcall consumes.
// `unsigned` (not `int`) is required: the return type is part of the mangling.
struct Gen_007e9b70 { unsigned m(); };

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
	unsigned now = (unsigned)((Rva007E9B70Obj*)(unsigned)((Gen_007e9b70*)this)->m())->v2();
	unsigned delay = timeout;
	Rva007FA170Slot *target = slot;
	_ReadWriteBarrier();
	unsigned expiry = now + delay;
	target->m_expiry = expiry;
	if (m_watermark == 0 || expiry < m_watermark)
		m_watermark = expiry;
}
