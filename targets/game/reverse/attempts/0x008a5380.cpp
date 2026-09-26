// ?aptRegisterFlagged008A5380@@YAPAVAptValue@@PAXH@Z
// partial score=0.85 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: two Apt script callbacks (71 B) that register the last stack
// value in a pointer table inside the global holder when its flag word has
// bit 15 set.
class AptValue { public: int toInteger(); };
class BfmeRef008A4B20;
class Rva008A4BD0 { public: unsigned char has(int value); };
class BfmePtrTable64_008A4B20 { public: void add(BfmeRef008A4B20* value); };
struct Rva008A5380Value { int m_0; int m_flags; };
extern AptValue* g_bfmeFallbackDB;
extern AptValue** g_bfmeArr1233;
extern int g_bfmeCount1233;
extern char* Rva008A5380Holder;

AptValue* aptRegisterFlagged008A5380(void* self, int argc)
{
	if (argc == 1) {
		Rva008A5380Value* v = (Rva008A5380Value*)g_bfmeArr1233[g_bfmeCount1233 - 1];
		int flags = v->m_flags;
		if (flags & 0x8000) {
			char* table = Rva008A5380Holder + 0x820;
			if (!((Rva008A4BD0*)table)->has((int)v))
				((BfmePtrTable64_008A4B20*)table)->add((BfmeRef008A4B20*)v);
		}
	}
	return g_bfmeFallbackDB;
}

// ?aptRegisterFlagged008A5440@@YAPAVAptValue@@PAXH@Z
AptValue* aptRegisterFlagged008A5440(void* self, int argc)
{
	if (argc == 1) {
		Rva008A5380Value* v = (Rva008A5380Value*)g_bfmeArr1233[g_bfmeCount1233 - 1];
		int flags = v->m_flags;
		if (flags & 0x8000) {
			char* table = Rva008A5380Holder + 0x924;
			if (!((Rva008A4BD0*)table)->has((int)v))
				((BfmePtrTable64_008A4B20*)table)->add((BfmeRef008A4B20*)v);
		}
	}
	return g_bfmeFallbackDB;
}
