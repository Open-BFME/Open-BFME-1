// cl: /DNDEBUG /MD /G6 /EHsc
//
// Retail 0x00943550 is a signed +0x94 guard that tail-jumps to the unlink
// helper at 0x00943430: a negative field returns immediately, otherwise the
// receiver is forwarded into unlink. The direct-thiscall spelling is what
// emits retail's `mov eax,[esp+4] / mov edx,[eax+0x94] / test edx,edx /
// jl +9 / mov [esp+4],eax / jmp 0x00943430 / ret 4` form; the member-pointer
// route, storeless stdcall, local-copy, address-first and slot-reuse
// spellings all mirror ecx/edx or add spills (see build/probe_small03e/
// unlink*.cpp). The callee resolves through the existing
// ?unlink@Gen_00943CF0@@AAEXPAX@Z pin at 0x00943430, so no new pin is
// needed. IDENTITY IS NOT RECOVERED: the owner keeps the address token of
// the Gen_00943CF0 node-grid family it guards.
class Gen_00943CF0
{
	void unlink(void *value);
public:
	void Rva00943550Release(void *value);
	int m_pad[0x25];
	int m_addr;
};

void Gen_00943CF0::Rva00943550Release(void *value)
{
	int addr = *(int *)((char *)value + 0x94);
	if (addr < 0)
		return;
	unlink(value);
}
