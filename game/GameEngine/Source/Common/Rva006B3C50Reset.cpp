// Clean reconstruction of the retail reset helper at RVA 0x006B3C50.

// The helper reached at RVA 0x006B3C58 with the local buffer is the ILT thunk
// at 0x0004AC82 (`?j_0004ac82@@YAXXZ`, game/gen_small/thunks_036.cpp), which
// stdcall-forwards its argument, so the callee is named by that thunk.

extern void j_0004ac82();

class Rva006B3C50Owner
{
public:
	void reset();

	char padding[0x44];
	int state;
};

void Rva006B3C50Owner::reset()
{
	typedef void (__stdcall *Init)(void *buffer);
	union { void (*raw)(); Init init; } call;

	char buffer[8];
	state = 0;
	call.raw = j_0004ac82;
	call.init(buffer);
}
