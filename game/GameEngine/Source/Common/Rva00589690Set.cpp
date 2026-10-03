// cl: /O2 /Ob0

// Retail's code at 0x0003643A is the ILT thunk `?j_0003643a@@YAXXZ`
// (ledger row `?j_0003643a@@YAXXZ` at 0x0003643A, 5 bytes,
// game/gen_small/thunks_026.cpp) into the notify body at 0x00964700. It is
// cdecl with an empty prototype because it is a thunk, and this call site
// needs no this adjustment: `set` already holds its own `this` in ecx.
extern "C" void __identifier("?j_0003643a@@YAXXZ")();

class Rva00589690
{
	char m_pad[0x4B];
	unsigned char m_flag;

public:
	void set(unsigned char v);
};

void Rva00589690::set(unsigned char v)
{
	m_flag = v;
	__identifier("?j_0003643a@@YAXXZ")();
}
