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
struct Rva008AE770Stack { int field00; };
extern Rva008AE770Stack Rva008AE770TheStack;
extern char* Rva008A5380Holder;
// 0x008996B0 is DEFINED in the ledger as
// ?Create@AptBoolean@@SAPAV1@_N@Z, so the true/false return values below are
// built by AptBoolean::Create rather than by a TU-local factory. The bool
// argument and the pointer return match the old local spelling exactly.
// AptValue is only forward-declared here, so AptBoolean cannot derive from it;
// the cast at the return sites bridges the two pointer views.
class AptBoolean { public: static AptBoolean *Create(bool); };
AptValue* aptUnregisterFlagged008A53D0(void* self, int argc)
{
	if (argc != 1)
		return (AptValue*)AptBoolean::Create(false);
	Rva008A5380Value* v = (Rva008A5380Value*)g_bfmeArr1233[Rva008AE770TheStack.field00 - 1];
	int flags = v->m_flags;
	if (flags & 0x8000) {
		char* table = Rva008A5380Holder + 0x820;
		if (((Rva008A4BD0*)table)->has((int)v)) {
			((BfmePtrTable64_008A4B20*)table)->remove((BfmeRef008A4B20*)v);
			return (AptValue*)AptBoolean::Create(true);
		}
	}
	return (AptValue*)AptBoolean::Create(false);
}
