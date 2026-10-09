// cl: /DNDEBUG /MD /O2
// Each address below starts immediately after retail INT3 padding and ends
// at RET followed by INT3. Address-derived identities do not assert a class.
// Evidence: build/astra_seat/disassembly.txt (retail-1.03-unpacked).
int Rva00783360() { return 0; }
void Rva00783370() {}
void Rva00783380() {}
void Rva00783390() {}
// Retail .rdata holds these independently verified 4-byte constants.
extern const float Rva01126AB0 = 1024.0f;
extern const float Rva01126AB4 = 768.0f;
float Rva007833A0() { return Rva01126AB0; }
float Rva007833B0() { return Rva01126AB4; }
void Rva007833C0() {}
void Rva007833D0() {}

void Rva008C57C0() {}
void Rva008C57D0() {}
void Rva008C57E0() {}
void Rva008C57F0() {}
void Rva008C5800() {}
void Rva008C5810() {}
void Rva008C5820(void *, unsigned char *value) { value[0x14] = 1; }
void Rva008C5830() {}

void Rva00C70A50() {}
void Rva00C70A60() {}
void Rva00C70A70() {}

struct Rva0084A550 { char offset00[0x24]; int offset24; int body(); };
int Rva0084A550::body() { return offset24; }
struct Rva0084A560 { char offset00[8]; char offset08; void *body(); };
void *Rva0084A560::body() { return &offset08; }
struct Rva0084A570 { char offset00[0x38]; bool offset38; int body(); };
int Rva0084A570::body() { return offset38 != 0; }
struct Rva0084A580 { char offset00[4]; char offset04; void *body(); };
void *Rva0084A580::body() { return &offset04; }
struct Rva0084A590 { char offset00[0x34]; bool offset34; int body(); };
int Rva0084A590::body() { return offset34 != 0; }
struct Rva0084A5A0 { char offset00[0xC]; char offset0C; void *body(); };
void *Rva0084A5A0::body() { return &offset0C; }
struct Rva0084A5B0 { char offset00[0x3C]; bool offset3C; int body(); };
int Rva0084A5B0::body() { return offset3C != 0; }

struct Rva008C4530 { char offset00[12]; unsigned char bit0:1; int body(); };
int Rva008C4530::body() { return bit0; }
struct Rva008C4540 { char offset00[12]; unsigned char bit0:1; unsigned char bit1:1; int body(); };
int Rva008C4540::body() { return bit1; }
struct Rva008C4550 { char offset00[12]; unsigned char bits01:2; unsigned char bit2:1; int body(); };
int Rva008C4550::body() { return bit2; }
struct Rva008C4560 { char offset00[20]; char offset14; void *body(); };
void *Rva008C4560::body() { return &offset14; }
struct Rva008C4570 { unsigned offset00; char *body(); };
char *Rva008C4570::body() { return (char *)this + offset00 + 20; }
struct Rva008C4580 { unsigned offset00, offset04; char *body(); };
char *Rva008C4580::body() { return (char *)this + (offset04 + offset00) + 20; }
struct Rva008C4590 { char offset00[0x7C]; int offset7C; int body(); };
int Rva008C4590::body() { return offset7C != 0; }

struct Rva007F5680 { char offset00[0x1C]; int offset1C; int body(); };
int Rva007F5680::body() { return offset1C; }
struct Rva007F5690 { char offset00[0x64]; int offset64; int body(); };
int Rva007F5690::body() { return offset64; }
struct Rva007F56A0 { char offset00[0x6C]; char offset6C; void *body(); };
void *Rva007F56A0::body() { return &offset6C; }
struct Rva007F56B0 { char offset00[0x68]; int offset68; int body(); };
int Rva007F56B0::body() { return offset68; }

struct Rva0097E510 { char offset00[4]; int offset04; int body(); };
int Rva0097E510::body() { return offset04; }
struct Rva0097E520 { char offset00[0x1C0]; int offset1C0; int body(); };
int Rva0097E520::body() { return offset1C0; }
struct Rva0097E530 { char offset00[0x1C4]; int offset1C4; int body(); };
int Rva0097E530::body() { return offset1C4; }
struct Rva0097E540 { char offset00[0x18]; char offset18; void *body(); };
void *Rva0097E540::body() { return &offset18; }
struct Rva0097E550 { char offset00[0x124]; float offset124; float body(); };
float Rva0097E550::body() { return offset124; }
struct Rva0097E560 { char offset00[0x128]; float offset128; float body(); };
float Rva0097E560::body() { return offset128; }
struct Rva0097E570 { char offset00[0x12C]; float offset12C; float body(); };
float Rva0097E570::body() { return offset12C; }

struct Rva009F4A30 { int offset00, offset04; void body(); };
void Rva009F4A30::body() { offset04 -= 24; }
