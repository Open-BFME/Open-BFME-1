// ?rva007F97B0@Rva007FA2C0@@QAEXPAVRva007E8810Message@@PAURva007F97B0State@@@Z
// partial score=0.76 date=2026-09-25
// ?rva007F97B0@Rva007FA2C0@@QAEXPAVRva007E8810Message@@PAURva007F97B0State@@@Z
// Candidate built from the landed FESL message and transactor layouts.
// cl: /O2 /GX- /GS

typedef unsigned char Byte;

extern int vftable_011296B0;

class Rva007E86B0Base
{
public:
	Rva007E86B0Base();
	virtual ~Rva007E86B0Base();
	int m_field04;
};

struct Rva007F93E0Prefix
{
	Rva007F93E0Prefix()
	{
		m_00 = 0;
		m_04 = 0;
		m_08 = 0;
		m_0c = 0;
		m_10 = 0;
	}

	int m_00;
	int m_04;
	char *m_08;
	int m_0c;
	Byte m_10;
};

class Rva007F93E0Tail : public Rva007E86B0Base
{
};

struct Rva007F93E0Envelope
{
	Rva007F93E0Prefix m_prefix;
	Rva007F93E0Tail m_tail;
	volatile int m_1c;
	volatile int m_20;
};

class Rva007E8810Message
{
public:
	bool getString(const char *key, char *out, int size);

	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	char *m_10;
	int m_14;
	int m_18;
	unsigned int m_1c;
	int m_20;
	int m_24;
	int m_28;
	int m_2c;
	char m_30;
	char m_pad31[3];
};

extern "C" unsigned int __cdecl strlen(const char *text);
#pragma intrinsic(strlen)

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void log(int level, const char *format, ...);
	virtual void fail(const char *expr, const char *file, int line);
};

extern Rva007EB810Diag *Rva007EB810Get();
int rva007FF250Decode(int length, const char *source,
	unsigned char *destination);

class Gen007F0130
{
public:
	static void *operator new(unsigned int size);
};

class Rva007EFFC0Allocator
{
public:
	virtual void v0();
	virtual void v1();
	virtual char *allocate(int size, int flags);
	virtual void release(void *block, int flags);
};

extern Rva007EFFC0Allocator *Rva007EFFC0Get();

class Rva007FA2C0Hub
{
public:
	virtual void v0(void *a, void *b);
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void *v5(void *a, int first, int second);
	virtual void v6();
	virtual void v7();
	virtual int v8(Rva007E8810Message *message);
	virtual bool v9(void *a);
};

class Rva007FA2C0Transport
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void send(Rva007F93E0Envelope *envelope);
};

struct Rva007F97B0Record
{
	static void *operator new(unsigned int size)
	{
		return Gen007F0130::operator new(size);
	}

	Rva007F97B0Record()
	{
		m_04 = 0;
		m_00 = 0;
		m_08 = (char *)0;
	}

	int m_00;
	unsigned int m_04;
	char *m_08;
};

struct Rva007F97B0State
{
	char m_pad00[0x18];
	Rva007F97B0Record *m_18;
};

class Rva007FA2C0
{
public:
	void rva007F97B0(Rva007E8810Message *message,
		register Rva007F97B0State *state);

private:
	char m_pad00[0x1c];
	void *m_1c;
	char m_pad20[4];
	Rva007FA2C0Hub *m_24;
};

void Rva007FA2C0::rva007F97B0(Rva007E8810Message *message,
	register Rva007F97B0State *state)
{
	Rva007F97B0Record *record = state->m_18;
	if (!record)
	{
		{
			Rva007F97B0Record *fresh = new Rva007F97B0Record;
			state->m_18 = (Rva007F97B0Record *)fresh;
			record = (Rva007F97B0Record *)fresh;
		}
		record->m_00 = m_24->v8(message);
		record->m_08 = (char *)Rva007EFFC0Get()->allocate(
			record->m_00 + 4, 1);
	}
	char *text = (char *)Rva007EFFC0Get()->allocate(message->m_14, 0);
	int messageSize = message->m_14;
	message->getString((const char *)0x0112BAC4, text, messageSize);
	unsigned int length = strlen(text);
	if ((length & 3) != 0)
	{
		Rva007EB810Diag *diag = Rva007EB810Get();
		diag->fail((const char *)0x0112BAB0,
			(const char *)0x0112BA50, 0x13b);
	}
	unsigned int decodedSize = (length >> 2) * 3;
	if (!rva007FF250Decode((int)length, text,
		(unsigned char *)(record->m_04 + (unsigned int)record->m_08)))
	{
		Rva007EB810Diag *diag = Rva007EB810Get();
		diag->fail((const char *)0x0112BAA8,
			(const char *)0x0112BA50, 0x13e);
	}
	record->m_04 += decodedSize;
	Rva007EFFC0Get()->release(text, 0);
	if (record->m_04 >= record->m_00)
	{
		Rva007F93E0Envelope envelope;
		int message20 = message->m_20;
		int message04 = message->m_04;
		envelope.m_prefix.m_00 = message->m_1c;
		*(volatile int *)&envelope.m_tail = (int)&vftable_011296B0;
		envelope.m_1c = 0;
		envelope.m_20 = 0;
		envelope.m_tail.m_field04 = message04;
		envelope.m_prefix.m_04 = message20 & 0xdfffffff;
		envelope.m_prefix.m_08 = record->m_08;
		int recordTotal = record->m_00;
		envelope.m_prefix.m_0c = recordTotal;
		envelope.m_prefix.m_10 = 0;
		envelope.m_1c = message->m_08;
		envelope.m_20 = message->m_0c;
	((Rva007FA2C0Transport *)((char *)this + 4))->send(&envelope);
	}
}
