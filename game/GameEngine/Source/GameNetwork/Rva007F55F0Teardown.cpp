// cl: /O2 /GX-
// Converted from game/gen_asm/d_007f2a50.asm (?d_007f55f0@@YAXXZ).
// Same teardown as BfmeThingTWB::bfmeDelTWB without the scalar-delete tail.

// 0x0112B5C4 is the vftable Rva007F6D60ChildConstructor.cpp emits (ledger
// dir32 row ??_7Rva007F6D60Child@@6B@); g_bfmeVftATWB was a stand-in spelling.
extern "C" void *__identifier("??_7Rva007F6D60Child@@6B@")[];
extern void *g_bfmeVftBTWB[];

// 0x007E86C0 is the matched shim ?m@Gen_007e86c0@@QAEXXZ (game/gen_small/fun_005.cpp):
// the shared base cleanup that reinstalls vtable 0x01129358.
class Gen_007e86c0
{
public:
	void m();
};

class BfmeStrTWB
{
public:
	char m_bfmePad[0x10];
};

class BfmeListTWB
{
public:
	void bfmeDropTWB();
	char m_bfmePad[0x10];
};

class Rva007F55F0Host
{
public:
	void teardown();

	void *m_vft;
	char m_pad04[4];
	int m_08;
	char m_pad0C[0x10];
	BfmeListTWB m_list;
	BfmeStrTWB m_b;
	BfmeStrTWB m_a;
};

void Rva007F55F0Host::teardown()
{
	m_vft = __identifier("??_7Rva007F6D60Child@@6B@");
	m_08 = 0;
	((Gen_007e86c0 *)&m_a)->m();
	((Gen_007e86c0 *)&m_b)->m();
	m_list.bfmeDropTWB();
	m_vft = g_bfmeVftBTWB;
}
