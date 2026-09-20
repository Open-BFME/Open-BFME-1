// ?forward@Rva006925D0Wrapper@@QAEPAXPAX@Z
// The carved boundary proves a thiscall wrapper with one pointer argument.
// The wrapper calls the adjacent callee and returns that same pointer.
// No caller proves a semantic owner, so the class name preserves the address.
// cl: /O2 /Oy /DNDEBUG /MD

typedef void *Pointer;

class Rva006925D0Wrapper
{
public:
	void begin(Pointer output);
	Pointer forward(Pointer output);
};

#pragma comment(linker, "/alternatename:?begin@Rva006925D0Wrapper@@QAEXPAX@Z=?dup_006922e0@@YAXXZ")

Pointer Rva006925D0Wrapper::forward(Pointer output)
{
	begin(output);
	return output;
}
