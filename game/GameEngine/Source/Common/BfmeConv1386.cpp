// cl: /GS
// Open-BFME5 conversions.

// 0x007E86C0 is the shared FESL base cleanup (ledger:
// ?m@Gen_007e86c0@@QAEXXZ); it is the end-of-scope teardown of the message.
class Gen_007e86c0
{
public:
	void m();
};

// Matched callee rows (callees.py): BfmeC994 ctor 0x007E8850 and addString
// 0x007E8A10, BfmeThingCIB::bfmeGoCIB 0x007E88D0, BfmeThingRF::bfmeGoRF 0x007E8900,
// BfmeThingUPB::bfmeGoUPB 0x007E8A80, BfmeThingBLF::bfmeGoBLF 0x00808BF0,
// Rva008038F0Sender::send 0x008038F0.
class BfmeC994
{
public:
	BfmeC994(char *buf, int n) throw();
	void addString(const char *k, const char *v) throw();
	char m_bfmePad[0x1c];
	int m_bfme1c;
	char m_bfmePad2[0x14];
};

class BfmeThingCIB
{
public:
	void bfmeGoCIB(void *k, void *v) throw();
};

class BfmeThingRF
{
public:
	void *bfmeGoRF(void *k, void *d) throw();
};

class BfmeThingUPB
{
public:
	char bfmeGoUPB(void *k, char *b, void *n) throw();
};

class BfmeThingBLF
{
public:
	void bfmeGoBLF(void *name) throw();
};

class Rva008038F0Sender
{
public:
	void send(BfmeC994 *m) throw();
};

class BfmeMsgVJI;

class BfmeSubVJI;

class BfmeThingVJI
{
public:
	void bfmeGoVJI(BfmeMsgVJI *src);
	char m_bfmePad[0x18];
	BfmeSubVJI *m_bfme18;
};

void BfmeThingVJI::bfmeGoVJI(BfmeMsgVJI *src)
{
	char buf[0x40];
	char name[0x20];
	BfmeC994 msg(buf, 0x40);
	msg.m_bfme1c = 0x55534552;
	((BfmeThingUPB *)src)->bfmeGoUPB("NAME", name, (void *)0x20);
	msg.addString("NAME", name);
	int tid = (int)((BfmeThingRF *)src)->bfmeGoRF("TID", (void *)-1);
	if (tid != -1)
		((BfmeThingCIB *)&msg)->bfmeGoCIB("TID", (void *)tid);
	((BfmeThingBLF *)m_bfme18)->bfmeGoBLF(name);
	((Rva008038F0Sender *)this)->send(&msg);
	((Gen_007e86c0 *)&msg)->m();
}
