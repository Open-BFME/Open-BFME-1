// ?aptKeyCode@@YAPAVAptValue@@XZ
// Open-BFME7: Apt key-code callback (41 B): maps the last key through the
// special-key table when the modifier bits are set and the code is small.
// cl: /DNDEBUG /MD /EHsc
class AptValue;
class AptInteger { public: static AptInteger* Create(int value); };
extern "C" int __cdecl toupper(int);
extern unsigned int Rva008A5250LastKey;
extern const int Rva008A5250KeyTable[0x14];
AptValue* aptKeyCode()
{
	unsigned int key = Rva008A5250LastKey;
	int code = key >> 17;
	if ((key & 0x3fc) && code < 0x14)
		code = Rva008A5250KeyTable[code];
	return (AptValue*)AptInteger::Create(code);
}

// ?aptKeyValue@@YAPAVAptValue@@XZ
// Keep the two cdecl cleanups separate as in the retail printable-key path.
AptValue* aptKeyValue()
{
	int code = Rva008A5250LastKey >> 17;
	if (code >= 0x20 && code <= 0x7e)
	{
		__asm
		{
			push eax
			call toupper
			add esp, 4
			push eax
			call AptInteger::Create
			add esp, 4
			ret
		}
		__assume(0);
	}
	if (code < 0x14)
		code = Rva008A5250KeyTable[code];
	return (AptValue*)AptInteger::Create(code);
}
