// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

// This wrapper asks the same owner to compare its argument with the payload
// beginning eight bytes into the object.  Keeping the worker as a member is
// material: retail preserves the incoming this pointer in ecx for the call.
//
// The only definition of RVA 0x00028AF6 is the 5-byte ILT thunk
// ?j_00028af6@@YAXXZ (game/gen_small/thunks_019.cpp), a void(void) __cdecl
// symbol, so its own name cannot carry this two-pointer callee-cleanup thiscall
// ABI.  Entering it through a union of its raw function pointer and a
// member-function pointer carrying retail's ABI keeps the live ecx that forms
// `lea edx,[ecx+8]` - the shape ModelConditionInfoDestructorThunk.cpp uses for
// this same kind of ILT call.
extern void j_00028af6();

struct Rva0039C7D0Payload
{
	unsigned char m_storage;
};

class Rva0039C7D0Owner
{
public:
	bool equals(const Rva0039C7D0Payload &other) const;

private:
	unsigned char m_prefix[8];
	Rva0039C7D0Payload m_payload;
};

bool Rva0039C7D0Owner::equals(const Rva0039C7D0Payload &other) const
{
	union {
		void (*raw)();
		bool (Rva0039C7D0Owner::*compare)(const Rva0039C7D0Payload *,
			const Rva0039C7D0Payload *) const;
	} callee;
	callee.raw = j_00028af6;
	return (this->*callee.compare)(&m_payload, &other);
}