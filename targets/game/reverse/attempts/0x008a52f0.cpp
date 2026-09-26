// ?aptKeyValue@@YAPAVAptValue@@XZ
// partial score=0.9 date=2026-09-06
// 59/59 B, 4 diff bytes: retail cleans the toupper call stack (add esp,4) before pushing the Create argument; ours merges into add esp,8 (or movsx with the char cast).
// cl: /DNDEBUG /MD /EHsc
extern "C" int __cdecl toupper(int);
class AptValue;
class AptInteger { public: static AptValue* Create(int value); };
extern unsigned int Rva008A5250LastKey;
extern const int Rva008A5250KeyTable[0x14];
AptValue* aptKeyValue()
{
	int code = Rva008A5250LastKey >> 17;
	if (code >= 0x20 && code <= 0x7e)
		return AptInteger::Create((char)toupper(code));
	if (code < 0x14)
		code = Rva008A5250KeyTable[code];
	return AptInteger::Create(code);
}
// ?aptKeyCode@@YAPAVAptValue@@XZ
AptValue* aptKeyCode()
{
	unsigned int key = Rva008A5250LastKey;
	int code = key >> 17;
	if ((key & 0x3fc) && code < 0x14)
		code = Rva008A5250KeyTable[code];
	return AptInteger::Create(code);
}
