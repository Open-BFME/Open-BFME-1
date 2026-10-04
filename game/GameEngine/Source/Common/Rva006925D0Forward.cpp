// ?forward@Rva006925D0Wrapper@@QAEPAXPAX@Z
// The carved boundary proves a thiscall wrapper with one pointer argument.
// The wrapper calls the adjacent callee and returns that same pointer.
// No caller proves a semantic owner, so the class name preserves the address.
// cl: /O2 /Oy /DNDEBUG /MD

typedef void *Pointer;

// Retail calls this slot through the ILT thunk at 0x006922E0, whose real
// body is ?dup_006922e0@@YAXXZ; reference that body directly instead of
// spelling an unresolvable member on it.
extern void dup_006922e0();

class Rva006925D0Wrapper
{
public:
	Pointer forward(Pointer output);
};

Pointer Rva006925D0Wrapper::forward(Pointer output)
{
	typedef void (Rva006925D0Wrapper::*Begin)(Pointer);
	union { void (*fn)(); Begin call; } begin = { dup_006922e0 };
	(this->*begin.call)(output);
	return output;
}
