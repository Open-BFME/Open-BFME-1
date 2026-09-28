// cl: /DNDEBUG /MD /G6 /EHsc
//
// Retail 0x0092F550 is an indexed refcounting getter over the table at
// this+0x34: it fetches slot[i] into the caller's out-buffer (the hidden
// struct-return pointer), add-refs through the halfword at +4 when non-null,
// and returns the out-pointer in eax. The by-value handle spelling is what
// emits retail's `push ecx / mov eax,[ecx+0x34] / mov ecx,[esp+0xC] /
// mov ecx,[eax+ecx*4] / test ecx,ecx / mov eax,[esp+8] / mov [esp],0 /
// mov [eax],ecx / je +4 / inc word ptr [ecx+4] / pop ecx / ret 8` form: the
// non-POD handle forces the hidden-buffer first argument, and the volatile
// guard owns the `mov [esp],0` slot. The sibling 0x009291F0 getter reads its
// table at +8, so this +0x34-table body cannot share that identity.
// IDENTITY IS NOT RECOVERED: the owner keeps its address token.
struct Rva0092F550Table
{
	void *m_slots[1];
};

class Rva0092F550Target
{
public:
	int m_first;
	unsigned short m_refCount;
	unsigned short m_pad;
};

class Rva0092F550Handle
{
public:
	Rva0092F550Handle(Rva0092F550Target *target);
	Rva0092F550Target *m_target;
};
// ??0Rva0092F550Handle@@QAE@PAVRva0092F550Target@@@Z absent-from-retail
inline Rva0092F550Handle::Rva0092F550Handle(Rva0092F550Target *target) : m_target(target)
{
	if (m_target)
		++m_target->m_refCount;
}

class Rva0092F550Box
{
public:
	Rva0092F550Handle getBuf(int i);
	int m_pad[13];
	Rva0092F550Table *m_table;
};

Rva0092F550Handle Rva0092F550Box::getBuf(int i)
{
	volatile int guard = 0;
	return Rva0092F550Handle((Rva0092F550Target *)m_table->m_slots[i]);
}
