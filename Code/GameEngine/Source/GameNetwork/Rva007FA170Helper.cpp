// cl: /O2
// 0x007FA170: slot helper. Block timeout sets error on the +8 message;
// nonblock timeout builds a stack message, fires the +0xC callback, and
// tears the slot down; otherwise the timeout is ignored.

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void log(int level, const char *format, ...);
	virtual void fail(const char *expr, const char *file, int line);
};

extern Rva007EB810Diag *Rva007EB810Get();

class Rva007E8810Message
{
public:
	Rva007E8810Message() throw();
	~Rva007E8810Message() throw();
	void setError(int code);
};

struct Rva007FA170Slot
{
	void *m_00;
	int m_04;
	Rva007E8810Message *m_08;
	void (__cdecl *m_0C)(Rva007E8810Message *msg, void *arg);
	void *m_10;
};

class Rva007FA2C0
{
public:
	void helper(void *slot, int line) throw();
	void clearSlot(void *slot);
};

void Rva007FA2C0::helper(void *slot, int line) throw()
{
	char buf[0x34];
	Rva007FA170Slot *s = (Rva007FA170Slot *)slot;
	if (s)
	{
		if (s->m_08)
		{
			Rva007EB810Get()->log(0, "--- timeout of Block request\n");
			s->m_08->setError(line);
			s->m_04 = 2;
			return;
		}
		if (s->m_0C)
		{
			Rva007EB810Get()->log(0, "--- timeout of Nonblock request\n");
			Rva007E8810Message *msg = (Rva007E8810Message *)buf;
			msg->Rva007E8810Message::Rva007E8810Message();
			msg->setError(line);
			s->m_0C(msg, s->m_10);
			clearSlot(s);
			msg->Rva007E8810Message::~Rva007E8810Message();
			return;
		}
		Rva007EB810Get()->log(0, "--- ignored timeout\n");
	}
}
