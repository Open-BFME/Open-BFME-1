// Open-BFME5 conversions.

// 0x007E86C0 is the shared FESL base cleanup (ledger:
// ?m@Gen_007e86c0@@QAEXXZ); it is this body's "done the message" step.
class Gen_007e86c0
{
public:
	void m();
};

// Retail's local message object is built by the constructor at 0x007E8850,
// which the ledger owns as BfmeC994's; the leading-byte store plus this call on
// `this` is its constructor, so the class carries that name and the call is
// spelled as the constructor it is.
class BfmeC994
{
public:
	BfmeC994(char *buf, int n);

	char m_bfmePad[0x34];
};

// The callback retail pushes is the cdecl function at 0x007F6870 (VA 0x00BF6870),
// owned by Rva007F6870GameLobbyCallback.cpp; only its address reaches this body.
extern "C" void __identifier("?rva007F6870GameLobbyCallback@@YAXPAVRva007E8810Message@@PAVRva007F65E0Owner@@@Z")(void *message, void *owner);

class BfmeAVJM
{
public:
	virtual void bfmeA00VJM();
	virtual void bfmeA04VJM();
	virtual void bfmeA08VJM();
	virtual void bfmeA0CVJM();
	virtual void bfmeA10VJM();
	virtual void bfmeA14VJM();
	virtual void bfmeA18VJM();
	virtual void bfmeA1CVJM();
	virtual void bfmeA20VJM(class BfmeC994 *m, int a, int b);
};

class BfmeBVJM
{
public:
	virtual void bfmeB00VJM();
	virtual void bfmeB04VJM();
	virtual void bfmeB08VJM(class BfmeC994 *m, void (__stdcall *cb)(), void *o, int n);
};

class BfmeThingVJM
{
public:
	void bfmeGoVJM(int a, int b);
	char m_bfmePad00[0x10];
	BfmeAVJM *m_bfme10;
	BfmeBVJM *m_bfme14;
	char m_bfmePad18[0x2c4];
	char m_bfmeBuf[0x400];
	int m_bfme6dc;
};

void BfmeThingVJM::bfmeGoVJM(int a, int b)
{
	BfmeC994 msg(m_bfmeBuf, 0x400);
	m_bfme10->bfmeA20VJM(&msg, a, b);
	m_bfme14->bfmeB08VJM(&msg,
		reinterpret_cast<void (__stdcall *)()>(
			&__identifier("?rva007F6870GameLobbyCallback@@YAXPAVRva007E8810Message@@PAVRva007F65E0Owner@@@Z")),
		this, m_bfme6dc);
	((Gen_007e86c0 *)&msg)->m();
}
