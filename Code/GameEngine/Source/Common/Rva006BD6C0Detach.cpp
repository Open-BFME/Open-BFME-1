// cl: /DNDEBUG /MD /EHsc
// Open-BFME: 22-byte adjustor unregister at 0x006BD6C0, address-derived name.
// Converted out of Code/gen_asm/d_0069c4f0.asm.
//
// IDENTITY IS NOT ASSERTED. The bytes say: a __thiscall member sitting at a
// +0x04 secondary base subobject that, when the global pointer at 0x012EF4FC
// is non-null, calls Rva006BDB00::handleNode with the primary base pointer
// (this - 4). That global is observed elsewhere as TheGhostObjectManager;
// the callee is the landed handleNode at 0x006BD1A0. No named caller or
// vtable slot proves the receiver's class.

class Rva006BDB00Node;

class Rva006BDB00
{
public:
	void handleNode(Rva006BDB00Node *node);
};

extern Rva006BDB00 *g_012EF4FC;

class Rva006BD6C0
{
public:
	void detach(void);
};

void Rva006BD6C0::detach(void)
{
	if (g_012EF4FC != 0)
		g_012EF4FC->handleNode((Rva006BDB00Node *)((char *)this - 4));
}
