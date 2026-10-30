// cl: /O1 /G6 /MD
// Retail 0x00C72A59..0x00C72A70 (24 B, RET at +0x17): an isolated cdecl
// byte-string length helper after the INT3 run near the end of .text. No
// direct caller or original symbol is known, so the name stays address
// derived and this is not bound to the CRT strlen. Body and flags from the
// BFME 2 donor Code/GameEngine/Source/Common/System/Rva007B9CCAStrLen.cpp
// (open-bfme-2 20a0cb6173), whose retail 0x007B9CCA has the same 24 bytes.

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

int Rva00C72A59StrLen(const char *text)
{
	const char *cursor = text;
	char current = *cursor++;

	// Compiler-only barrier: keeps the LEA before the entry TEST and emits
	// no instruction.
	_ReadWriteBarrier();
	if (current)
		goto scan;
	goto finished;

scan:
	while (current)
		current = *cursor++;

finished:
	return (int)(cursor - text - 1);
}
