// ?aptRegisterFlagged008A5380@@YAPAVAptValue@@PAXH@Z
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
struct Rva008AE770Stack
{
	int field00;
	int m_rva0133874C;
	AptValue** m_rva01338750;
};
extern Rva008AE770Stack Rva008AE770TheStack;
struct BfmePickWorld1284;
extern BfmePickWorld1284* g_bfmeHolderBU;

AptValue* aptRegisterFlagged008A5380(void* self, int argc)
{
	if (argc != 1)
		goto done;
	{
		Rva008AE770Stack& stk = Rva008AE770TheStack;
		AptValue** args = stk.m_rva01338750;
		Rva008A5380Value* v = (Rva008A5380Value*)args[stk.field00 - 1];
		int flags = v->m_flags;
		if (!(flags & 0x8000))
			goto done;
		char* table = (char*)g_bfmeHolderBU + 0x820;
		if (!((Rva008A4BD0*)table)->has((int)v))
			((BfmePtrTable64_008A4B20*)table)->add((BfmeRef008A4B20*)v);
	}
	done:
	return g_bfmeFallbackDB;
}

// RVA 0x008A5440: the adjacent callback uses the holder table at +0x924.
AptValue* aptRegisterFlagged008A5440(void* self, int argc)
{
	if (argc != 1)
		goto done;
	{
		Rva008AE770Stack& stk = Rva008AE770TheStack;
		AptValue** args = stk.m_rva01338750;
		Rva008A5380Value* v = (Rva008A5380Value*)args[stk.field00 - 1];
		int flags = v->m_flags;
		if (!(flags & 0x8000))
			goto done;
		char* table = (char*)g_bfmeHolderBU + 0x924;
		if (!((Rva008A4BD0*)table)->has((int)v))
			((BfmePtrTable64_008A4B20*)table)->add((BfmeRef008A4B20*)v);
	}
	done:
	return g_bfmeFallbackDB;
}
