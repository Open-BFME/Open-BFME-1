// _Rva008921B0Atof
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2

// Retail calls the CRT atof through the incremental-link thunk
// ?ji_009f6fac@@YAXXZ, which is declared with no parameters in
// imports_000.cpp.  Call it through a __cdecl signature that carries the
// argument retail leaves on the stack.
extern void __cdecl ji_009f6fac();

typedef double (__cdecl *AtofFn)(const char *text);

class EmptyGuard
{
public:
	~EmptyGuard() {}
};

extern "C" double Rva008921B0Atof(const char *text)
{
	EmptyGuard guard;
	return ((AtofFn)(void *)ji_009f6fac)(text);
}