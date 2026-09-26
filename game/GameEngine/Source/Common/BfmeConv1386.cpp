// cl: /GS
// Open-BFME5 conversions.

class BfmeMsgVJI
{
public:
	BfmeMsgVJI(char *buf, int n) throw();
	~BfmeMsgVJI() throw();
	void bfmeSetVJI(const char *k, const char *v) throw();
	void bfmeSet3VJI(const char *k, int v) throw();
	int bfmeGetVJI(const char *k, int d) throw();
	char bfmeGetStrVJI(const char *k, char *b, int n) throw();
	char m_bfmePad[0x1c];
	int m_bfme1c;
	char m_bfmePad2[0x14];
};

class BfmeSubVJI
{
public:
	void bfmeNoteVJI(const char *name) throw();
};

class BfmeThingVJI
{
public:
	void bfmeGoVJI(BfmeMsgVJI *src);
	void bfmeSendVJI(BfmeMsgVJI *m) throw();
	char m_bfmePad[0x18];
	BfmeSubVJI *m_bfme18;
};

void BfmeThingVJI::bfmeGoVJI(BfmeMsgVJI *src)
{
	char buf[0x40];
	char name[0x20];
	BfmeMsgVJI msg(buf, 0x40);
	msg.m_bfme1c = 0x55534552;
	src->bfmeGetStrVJI("NAME", name, 0x20);
	msg.bfmeSetVJI("NAME", name);
	int tid = src->bfmeGetVJI("TID", -1);
	if (tid != -1)
		msg.bfmeSet3VJI("TID", tid);
	m_bfme18->bfmeNoteVJI(name);
	bfmeSendVJI(&msg);
}
