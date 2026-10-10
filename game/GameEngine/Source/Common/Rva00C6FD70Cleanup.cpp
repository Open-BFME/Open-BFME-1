// cl: /O2 /Ob0
// Ten independently int3-bounded entries. DATA xrefs from startup code
// register these function addresses; their original names remain unknown.
// Callee ABI is witnessed at each final body: mov [ecx],01073744h; ret.
// Existing opaque ledger names are reused, without inventing class identity.
// ILT routes: 2F04->1BDCB0;12634->1BDC30;15140->1BDC10;
// 28BF5->1BDC70;1DC37->1BDC50;1EF6A->1BDC90;1E182->1C0D00.
struct Gen_001bdcb0 { void m(); };
struct Gen_001bdc30 { void m(); };
struct Gen_001bdc10 { void m(); };
struct Gen_001bdc70 { void m(); };
struct Gen_001bdc50 { void m(); };
struct Gen_001bdc90 { void m(); };
struct Gen_001c0d00 { void m(); };

unsigned g_Va012EF5E0 = 0;
unsigned g_Va012EF5F0 = 0;
unsigned g_Va012EF600 = 0;
unsigned g_Va012EF610 = 0;
unsigned g_Va012EF620 = 0;
unsigned g_Va012EF630 = 0;
unsigned g_Va012EF5D0 = 0;

void rva00C6FD70() { reinterpret_cast<Gen_001bdcb0 *>(&g_Va012EF5E0)->m(); }
void rva00C6FD80() { reinterpret_cast<Gen_001bdc30 *>(&g_Va012EF5F0)->m(); }
void rva00C6FD90() { reinterpret_cast<Gen_001bdc10 *>(&g_Va012EF600)->m(); }
void rva00C6FDA0() { reinterpret_cast<Gen_001bdc70 *>(&g_Va012EF610)->m(); }
void rva00C6FDB0() { reinterpret_cast<Gen_001bdc50 *>(&g_Va012EF620)->m(); }
void rva00C6FDC0() { reinterpret_cast<Gen_001bdc90 *>(&g_Va012EF630)->m(); }
void rva00C6FDD0() { reinterpret_cast<Gen_001c0d00 *>(&g_Va012EF5D0)->m(); }
void rva00C6FDE0() {}
void rva00C6FDF0() {}
void rva00C6FE00() {}
