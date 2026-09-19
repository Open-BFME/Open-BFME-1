// ?aptKeyCode@@YAPAVAptValue@@XZ
// Open-BFME7: Apt key-code callback (41 B): maps the last key through the
// special-key table when the modifier bits are set and the code is small.
// cl: /DNDEBUG /MD /EHsc
class AptValue;
class AptInteger { public: static AptValue* Create(int value); };
extern unsigned int Rva008A5250LastKey;
extern const int Rva008A5250KeyTable[0x14];
AptValue* aptKeyCode()
{
	unsigned int key = Rva008A5250LastKey;
	int code = key >> 17;
	if ((key & 0x3fc) && code < 0x14)
		code = Rva008A5250KeyTable[code];
	return AptInteger::Create(code);
}
