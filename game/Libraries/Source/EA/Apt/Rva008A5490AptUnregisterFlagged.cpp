// ?aptUnregisterFlagged008A5490@@YAPAVAptValue@@PAXH@Z
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: Apt script callback (100 B): with exactly one argument whose
// flag word has bit 15 set remove it from the pointer table inside the global
// holder and return true; otherwise false.
class AptValue;
class BfmeRef008A4B20;
class Rva008A4BD0 { public: unsigned char has(int value); };
class BfmePtrTable64_008A4B20 { public: int remove(BfmeRef008A4B20* value); };
struct Rva008A5380Value { int m_0; int m_flags; };
struct Rva008AE770Stack
{
	int field00;
	int m_rva0133874C;
	AptValue** m_rva01338750;
};
extern Rva008AE770Stack Rva008AE770TheStack;
struct BfmePickWorld1284;
extern BfmePickWorld1284* g_bfmeHolderBU;
// 0x008996B0 is DEFINED in the ledger as
// ?Create@AptBoolean@@SAPAV1@_N@Z, so the true/false results below come
// from AptBoolean::Create instead of a TU-local factory. AptValue is only
// forward-declared here, so the cast bridges the two pointer views.
class AptBoolean { public: static AptBoolean *Create(bool); };
AptValue* aptUnregisterFlagged008A5490(void* self, int argc)
{
	if (argc != 1)
		return (AptValue*)AptBoolean::Create(false);
	Rva008AE770Stack& stk = Rva008AE770TheStack;
	AptValue** args = stk.m_rva01338750;
	Rva008A5380Value* v = (Rva008A5380Value*)args[stk.field00 - 1];
	int flags = v->m_flags;
	if (flags & 0x8000) {
		char* table = (char*)g_bfmeHolderBU + 0x924;
		if (((Rva008A4BD0*)table)->has((int)v)) {
			((BfmePtrTable64_008A4B20*)table)->remove((BfmeRef008A4B20*)v);
			return (AptValue*)AptBoolean::Create(true);
		}
	}
	return (AptValue*)AptBoolean::Create(false);
}
