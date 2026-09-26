// ?aptUnregisterFlagged008A53D0@@YAPAVAptValue@@PAXH@Z
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: Apt script callback (100 B): with exactly one argument whose
// flag word has bit 15 set remove it from the pointer table inside the global
// holder and return true; otherwise false.
class AptValue;
class BfmeRef008A4B20;
class Rva008A4BD0 { public: unsigned char has(int value); };
class BfmePtrTable64_008A4B20 { public: int remove(BfmeRef008A4B20* value); };
struct Rva008A5380Value { int m_0; int m_flags; };
extern AptValue** g_bfmeArr1233;
extern int g_bfmeCount1233;
extern char* Rva008A5380Holder;
AptValue* __cdecl Rva008A53D0MakeBool(int value);
AptValue* aptUnregisterFlagged008A53D0(void* self, int argc)
{
	if (argc != 1)
		return Rva008A53D0MakeBool(0);
	Rva008A5380Value* v = (Rva008A5380Value*)g_bfmeArr1233[g_bfmeCount1233 - 1];
	int flags = v->m_flags;
	if (flags & 0x8000) {
		char* table = Rva008A5380Holder + 0x820;
		if (((Rva008A4BD0*)table)->has((int)v)) {
			((BfmePtrTable64_008A4B20*)table)->remove((BfmeRef008A4B20*)v);
			return Rva008A53D0MakeBool(1);
		}
	}
	return Rva008A53D0MakeBool(0);
}
