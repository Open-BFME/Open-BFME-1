// cl: /DNDEBUG /MD
// Retail 0x00887020 (14 B narrow toupper) and 0x00887030 (13 B wide
// towupper): file-static single-character case wrappers. File-static
// scope is what keeps the narrow argument as (movsx eax,al / push
// eax) instead of loading it from the stack.

extern "C" __declspec(dllimport) int __cdecl toupper(int value);
extern "C" __declspec(dllimport) unsigned short __cdecl towupper(unsigned short value);

static int Rva00887020Narrow(char value)
{
	return toupper(value);
}

static int Rva00887030Wide(unsigned short value)
{
	return towupper(value);
}

// Visible call sites so both statics are emitted; not claimed.
void Rva00887020Keep(char value, unsigned short wide)
{
	Rva00887020Narrow(value);
	Rva00887030Wide(wide);
}
