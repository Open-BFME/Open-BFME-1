// Open-BFME5 conversions.

// Reference the ledger-owned ILT entries at the original call sites. These
// five-byte jumps preserve ECX and the stack arguments; the member-pointer
// views below keep each existing thiscall ABI without defining another body.
void j_0000ddd7(); // W3DTreeBuffer::clearAllTrees, body 0x00732E70
void j_00045d72(); // W3DShrubBuffer::clearAllTrees, body 0x0071C7E0
void j_0002addd(); // W3DPropBuffer::updatePropPosition, body 0x007026E0
void j_00025cca(); // AsciiString tree _M_find, body 0x005C7770
void j_00021c1f(); // two-stack-argument thiscall body 0x006ADAE0

class BfmeObjPA
{
public:
	virtual void bfmeSlotPA00();
	virtual void bfmeSlotPA01();
	virtual void bfmeSlotPA02();
	virtual void bfmeSlotPA03();
	virtual void bfmeSlotPA04();
	virtual void bfmeSlotPA05();
	virtual void bfmeSlotPA06();
	virtual void bfmeSlotPA07();
	virtual void bfmeSlotPA08();
	virtual void bfmeSlotPA09();
	virtual void bfmeSlotPA10();
	virtual void bfmeSlotPA11();
	virtual void bfmeSlotPA12();
	virtual void bfmeSlotPA13();
	virtual void bfmeSlotPA14();
	virtual void bfmeSlotPA15();
	virtual void bfmeVirtPA();
};

struct BfmeNodePA
{
	int m_bfmePad;
	BfmeObjPA *m_bfmeObj;
	BfmeNodePA *m_bfmeNext;
};

class BfmeThingPA
{
public:
	void bfmeGoPA(int i);
	char m_bfmePad[0x80];
	BfmeNodePA *m_bfmeHeads[1];
};

void BfmeThingPA::bfmeGoPA(int i)
{
	BfmeNodePA *n = m_bfmeHeads[i];
	while (n) {
		n->m_bfmeObj->bfmeVirtPA();
		n = n->m_bfmeNext;
	}
}

struct BfmeNodePB
{
	int m_bfmePad;
	void *m_bfmeObj;
	BfmeNodePB *m_bfmeNext;
};

// retail global: RTS3DScene *W3DDisplay::m_3DScene (0x012F8058),
// mangled ?m_3DScene@W3DDisplay@@2PAVRTS3DScene@@A.
class RTS3DScene
{
public:
	virtual void bfmeSlotPB00();
	virtual void bfmeSlotPB01();
	virtual void bfmeVirtPB(void *o);
};

class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;
};

class BfmeThingPB
{
public:
	void bfmeGoPB(int i);
	char m_bfmePad[0x80];
	BfmeNodePB *m_bfmeHeads[1];
};

void BfmeThingPB::bfmeGoPB(int i)
{
	BfmeNodePB *n = m_bfmeHeads[i];
	while (n) {
		W3DDisplay::m_3DScene->bfmeVirtPB(n->m_bfmeObj);
		n = n->m_bfmeNext;
	}
}

class BfmeSubPC
{
};

class BfmeThingPC
{
public:
	void bfmeGoPC();
	char m_bfmePad[0x3094];
	BfmeSubPC *m_bfmeA;
	BfmeSubPC *m_bfmeB;
};

void BfmeThingPC::bfmeGoPC()
{
	union { void (*entry)(); void (BfmeSubPC::*member)(); }
		one = { j_0000ddd7 }, two = { j_00045d72 };
	if (m_bfmeA)
		(m_bfmeA->*one.member)();
	if (m_bfmeB)
		(m_bfmeB->*two.member)();
}

struct BfmeVecPD
{
	int m_bfmeX;
	int m_bfmeY;
	int m_bfmeZ;
};

class BfmeSubPD
{
};

class BfmeThingPD
{
public:
	char bfmeGoPD(int a, BfmeVecPD v, int e, int f);
	char m_bfmePad[0x309c];
	BfmeSubPD *m_bfmeSub;
};

char BfmeThingPD::bfmeGoPD(int a, BfmeVecPD v, int e, int f)
{
	union { void (*entry)(); char (BfmeSubPD::*member)(int, BfmeVecPD *, int, int); }
		call = { j_0002addd };
	BfmeSubPD *s = m_bfmeSub;
	if (s)
		return (s->*call.member)(a, &v, e, f);
	return 0;
}

struct BfmeSubPE
{
	int *m_bfmeFirst;
};

class BfmeThingPE
{
public:
	char *bfmeGoPE(int k);
	char m_bfmePad[0x1b8];
	BfmeSubPE m_bfmeSub;
};

char *BfmeThingPE::bfmeGoPE(int k)
{
	union { void (*entry)(); int *(BfmeSubPE::*member)(int); }
		call = { j_00025cca };
	int *r = (m_bfmeSub.*call.member)(k);
	if (r == m_bfmeSub.m_bfmeFirst)
		return 0;
	return (char *)r + 0x14;
}

class BfmeThingPG
{
public:
	void bfmeGoPG(int v, int i, void *c);
	char m_bfmePad[0xac4];
	int m_bfmeArr[1];
};

void BfmeThingPG::bfmeGoPG(int v, int i, void *c)
{
	union { void (*entry)(); void (BfmeThingPG::*member)(int, void *); }
		call = { j_00021c1f };
	(this->*call.member)(i, c);
	m_bfmeArr[i] = v;
}
