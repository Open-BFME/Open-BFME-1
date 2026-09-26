// ?aptKeyMatches@@YAPAVAptValue@@PAXH@Z
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
class AptValue { public: int toInteger(); };
extern AptValue** g_bfmeArr1233;
extern int g_bfmeCount1233;
extern unsigned int Rva008A5250LastKey;
extern const int Rva008A5250KeyTable[0x14];
int __cdecl Rva008A5250KeyChar(int code);
AptValue* __cdecl Rva008A53D0MakeBool(int value);
AptValue* aptKeyMatches(void* self, int argc)
{
	AptValue* v = g_bfmeArr1233[g_bfmeCount1233 - 1];
	unsigned int key = Rva008A5250LastKey;
	if ((key & 3) == 1) {
		int code = key >> 17;
		if (code >= 0x20 && code <= 0x7e) {
			int c = Rva008A5250KeyChar(code);
			return Rva008A53D0MakeBool(c == v->toInteger());
		}
		if (code < 0x14) {
			int m = Rva008A5250KeyTable[code];
			return Rva008A53D0MakeBool(m == v->toInteger());
		}
	}
	return Rva008A53D0MakeBool(0);
}
