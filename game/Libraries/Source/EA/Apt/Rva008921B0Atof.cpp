// _Rva008921B0Atof
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2

// The import thunk is declared with no parameters in imports_000.cpp, but it
// jumps directly to the CRT atof entry point.  This declaration preserves the
// argument that retail leaves on the stack while the linker alias keeps the
// existing thunk as the call target.
extern double __cdecl ji_009f6fac(const char *text);
#pragma comment(linker, "/alternatename:?ji_009f6fac@@YANPBD@Z=?ji_009f6fac@@YAXXZ")

class EmptyGuard
{
public:
	~EmptyGuard() {}
};

extern "C" double Rva008921B0Atof(const char *text)
{
	EmptyGuard guard;
	return ji_009f6fac(text);
}
