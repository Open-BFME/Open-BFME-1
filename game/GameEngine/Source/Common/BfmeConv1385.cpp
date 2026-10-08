// cl: /GS
// Open-BFME5 conversions.

// 0x007E86C0 is the shared FESL base cleanup (ledger:
// ?m@Gen_007e86c0@@QAEXXZ); it is the end-of-scope teardown of the message.
class Gen_007e86c0
{
public:
	void m();
};

// Matched callee rows (callees.py, direct calls): BfmeC994 ctor 0x007E8850 and addString 0x007E8A10,
// BfmeThingCIB::bfmeGoCIB 0x007E88D0, Rva008038F0Sender::send 0x008038F0.
class BfmeThingCIB
{
public:
	void bfmeGoCIB(void *k, void *v) throw();
};

class Rva008038F0Sender
{
public:
	void send(class BfmeC994 *m) throw();
};

class BfmeC994
{
public:
	BfmeC994(char *buf, int n) throw();
	void addString(const char *k, const char *v) throw();
	char m_bfmePad[0x1c];
	int m_bfme1c;
	char m_bfmePad2[0x14];
};

class BfmeThingVJH
{
public:
	void bfmeGoVJH(int a);
};

void BfmeThingVJH::bfmeGoVJH(int a)
{
	char buf[0x40];
	BfmeC994 msg(buf, 0x40);
	msg.m_bfme1c = 0x4c444154;
	((BfmeThingCIB *)&msg)->bfmeGoCIB("TID", (void *)a);
	((BfmeThingCIB *)&msg)->bfmeGoCIB("LID", (void *)-2);
	msg.addString("NAME", "LAN");
	((Rva008038F0Sender *)this)->send(&msg);
	((Gen_007e86c0 *)&msg)->m();
}
