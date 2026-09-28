// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x009A1C70 zeroes the two head words at this+0/+4, then forwards
// (key, 0) into the AudioEventInfo hashtable member at this+8 through the
// address-taken 0x009A1990 alias. The `lea ecx,[esi+8]` receiver is the
// tell: a plain member-pointer call on `this` emits two stores then a call
// with no lea, so the callee must be invoked on the subobject at +8.
// IDENTITY IS NOT RECOVERED: the owner and key keep their address tokens.
extern void Rva009A1990Target();

class Rva009A1C70Owner
{
public:
	typedef void (Rva009A1C70Owner::*Call)(void *key, int tag);
	Rva009A1C70Owner *initAudio(void *key);
	void *m_head[2];
	char m_sub[8];
};

Rva009A1C70Owner *Rva009A1C70Owner::initAudio(void *key)
{
	m_head[0] = 0;
	m_head[1] = 0;
	union { void (*address)(); Rva009A1C70Owner::Call member; } route = { Rva009A1990Target };
	(static_cast<Rva009A1C70Owner *>((void *)((char *)this + 8))->*route.member)(key, 0);
	return this;
}
