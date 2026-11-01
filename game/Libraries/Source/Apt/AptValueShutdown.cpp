// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// AptValueShutdown(int), retail 0x00899AF0 (297 bytes): Apt value-system
// teardown. The matched Apt shutdown dup_00894A90 calls it right after its
// three pool deletes and forwards its own int argument, which this body never
// reads. It resets the Apt stack, closes and frees the lazily built table at
// 0x01337A28, releases the value singletons Rva0089BBF0InitGlobals created
// (virtual slot 2), frees the 0x3C0-byte block at 0x01337A04 and clears the
// last eight singleton pointers.
//
// Identity: targets/game/reverse/identity_evidence/00899af0-aptvalueshutdown.md
// (Open BFME 2 donor Code/Libraries/Source/Apt/AptValueShutdownBFME2.cpp at
// 45afcff3, whose name comes from an original MAP file).
//
// The table pointer is read once: the receiver of the close call is the
// global itself, the delete operand a copy taken first. Spelling both through
// one local keeps it in EDI from the entry block and saves EDI at entry;
// retail tests the global in ECX and saves EDI only inside the if block.

class Gen_008C6BC0 { public: void bfmeReset(); };
struct Rva008AE770Stack;
extern Rva008AE770Stack Rva008AE770TheStack;

class Gen0089C880 { public: void handle(); };
extern void (__cdecl *TheBfmeFree)(void *, unsigned int);
// The destructor route 8976E0 -> 89CC70 -> 89C900 ends at the matched
// Q3EhMember0089C900 cleanup; the first jump body owns this call target,
// as in BfmeSubB1035Destroy.cpp.
extern void j_008976e0();
class BfmeChildA
{
public:
	static void operator delete(void *p, unsigned int n) { TheBfmeFree(p, n); }
private:
	char m_bytes[16];
};
extern void *g_Rva01337A28Index;

// Each singleton is released through its third virtual slot.
struct Rva00899AF0View { virtual void slot00(); virtual void slot04(); virtual void release(); };
class Rva89A2C0Derived; extern Rva89A2C0Derived *g_Va013379B4;
class BfmeThingVDW; extern BfmeThingVDW *g_Va013379FC;
class Rva89A540Derived; extern Rva89A540Derived *g_Va013379AC;
struct Rva00899C20Registry; extern Rva00899C20Registry *g_Va013387D8;
struct BfmeMap1024; extern BfmeMap1024 *g_bfmeMap1024;
class Rva89AA20Derived; extern Rva89AA20Derived *g_Va01337A00;
class Rva008A9B00; extern Rva008A9B00 *g_Va013379F0;
extern int g_bfmeB1038;
class BfmeA1029;
extern BfmeA1029 *g_Va013379EC;
extern BfmeA1029 *g_Va013379C4;
extern BfmeA1029 *g_Va013379C8;
extern BfmeA1029 *g_Va013379F8;
extern BfmeA1029 *g_Va013379B8;
extern BfmeA1029 *g_Va013379B0;
extern BfmeA1029 *g_Va01337A2C;
extern int g_bfmeRegisterClass1015;

#define RELEASE(p) ((Rva00899AF0View *)(p))->release()

// ?AptValueShutdown@@YAXH@Z
void AptValueShutdown(int)
{
	((Gen_008C6BC0 *)&Rva008AE770TheStack)->bfmeReset();
	if (g_Rva01337A28Index)
	{
		BfmeChildA *table = (BfmeChildA *)g_Rva01337A28Index;
		((Gen0089C880 *)g_Rva01337A28Index)->handle();
		if (table)
		{
			((void (__fastcall *)(BfmeChildA *))j_008976e0)(table);
			BfmeChildA::operator delete(table, sizeof(BfmeChildA));
		}
		g_Rva01337A28Index = 0;
	}
	RELEASE(g_Va013379B4);
	RELEASE(g_Va013379FC);
	RELEASE(g_Va013379AC);
	RELEASE(g_Va013387D8);
	RELEASE(g_bfmeMap1024);
	RELEASE(g_Va01337A00);
	RELEASE(g_Va013379F0);
	TheBfmeFree((void *)g_bfmeB1038, 0x3c0);
	RELEASE(g_Va013379EC); g_Va013379EC = 0;
	RELEASE(g_Va013379C4); g_Va013379C4 = 0;
	RELEASE(g_Va013379C8); g_Va013379C8 = 0;
	RELEASE(g_Va013379F8); g_Va013379F8 = 0;
	RELEASE(g_Va013379B8); g_Va013379B8 = 0;
	RELEASE(g_Va013379B0); g_Va013379B0 = 0;
	RELEASE(g_Va01337A2C); g_Va01337A2C = 0;
	RELEASE(g_bfmeRegisterClass1015); g_bfmeRegisterClass1015 = 0;
}
