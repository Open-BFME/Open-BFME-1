// cl: /DNDEBUG /MD
// Retail 0x00886FC0 (narrow) and 0x00886FE0 (wide): file-static
// single-character whitespace predicates. File-static scope is what
// keeps the argument in EAX (push eax / movsx eax,al) instead of
// loading it from the stack.

extern "C" __declspec(dllimport) int __cdecl isspace(int value);
extern "C" __declspec(dllimport) int __cdecl iswspace(unsigned short value);

static bool Rva00886FC0(char value)
{
	return isspace(value) != 0;
}

static bool Rva00886FE0(unsigned short value)
{
	return iswspace(value) != 0;
}

// Visible call sites so both statics are emitted; not claimed.
void Rva00886FC0Keep(char value, unsigned short wide)
{
	Rva00886FC0(value);
	Rva00886FE0(wide);
}
