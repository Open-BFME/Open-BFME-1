// cl: /O2
// 0x007FA790 is the FESL record callback operation adjacent to the matched
// 0x007FA6C0 opener.  Its one-argument thiscall ABI, +0x08 DirtySock record,
// and handler slots are fixed by the complete retail body.  The record pump,
// block reader and delivery wrapper are the independently matched Y2 module
// functions.  The original semantic method name is not recoverable, so this
// member remains address-derived.

struct Rva00806580Record;

void Rva00806B10(Rva00806580Record *record);
int Rva008076E0(Rva00806580Record *record, unsigned *first,
	unsigned *second, char **text);
int Rva00807820(Rva00806580Record *record, unsigned *first,
	unsigned *second, void *destination, int destinationSize);

struct Rva7F4CC0Child
{
	Rva7F4CC0Child();

	volatile unsigned table;
	volatile unsigned first;
	volatile unsigned second;
	volatile unsigned third;
};

struct Rva7F4CC0Primary
{
	unsigned first;
	unsigned second;
	unsigned third;
	unsigned fourth;
	bool enabled;
};

struct Rva7F4CC0ConstructorThunk : Rva7F4CC0Primary, Rva7F4CC0Child
{
	Rva7F4CC0ConstructorThunk();
};

class Rva00800780Addr
{
public:
	~Rva00800780Addr();
};

class Rva007FA790Handler
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2(int code);
	virtual void v3(void *packet);
};

class Rva007FA6C0
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	int rva007FA790(unsigned now);

private:
	Rva007FA790Handler *m_handler;
	Rva00806580Record *m_record;
	int m_lastTick;
	unsigned char m_active;
};

int Rva007FA6C0::rva007FA790(unsigned now)
{
	if (!m_record)
		return -202;

	Rva00806B10(m_record);
	Rva7F4CC0ConstructorThunk packet;
	char *text;
	int result = Rva008076E0(m_record,
		&packet.Rva7F4CC0Primary::first,
		&packet.Rva7F4CC0Primary::second, &text);
	if (result >= 0)
	{
		m_lastTick = 0;
		if (packet.Rva7F4CC0Primary::first == (unsigned)-1)
		{
			if (packet.Rva7F4CC0Primary::second == (unsigned)-1)
			{
				if (!m_active)
				{
					m_active = 1;
					m_handler->v0();
				}
			}
			else if (packet.Rva7F4CC0Primary::second == 0xFEFEFEFEu)
			{
				if (m_active)
				{
					m_handler->v1();
					m_active = 0;
				}
			}
		}
		else if (m_active)
		{
			packet.Rva7F4CC0Primary::third = (unsigned)text;
			packet.Rva7F4CC0Primary::fourth = (unsigned)result;
			m_handler->v3(&packet);
		}

		Rva00807820(m_record, &packet.Rva7F4CC0Primary::first,
			&packet.Rva7F4CC0Primary::second, 0, 0);
	}
	if (m_lastTick != 0 && now - (unsigned)m_lastTick > 0x3E80u)
	{
		m_handler->v2(-201);
		v5();
	}
	((Rva00800780Addr *)((char *)&packet + 0x14))->~Rva00800780Addr();
	return 0;
}
