// cl: /GX- /GS

struct Rva00800A40Input
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
};

struct Rva00800A40Target
{
	virtual void send(int code, int value);
};

struct Rva00800A40Diag
{
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void fail(const char *expression, const char *file, int line);
};

struct Rva007EB810Diag;
extern Rva007EB810Diag *Rva007EB810Get();

struct Rva00800A40Slot
{
	int m_00;
	int m_04;
	unsigned char m_08;
	unsigned char m_pad09[3];
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
};

class Rva00800920Owner
{
	char m_pad00[0x0c];
	Rva00800A40Target *m_0c;
	char m_pad10[4];
	unsigned char m_14;
	unsigned char m_pad15[3];
	int m_18;
	char m_pad1c[0xb8];
	Rva00800A40Slot m_slots[8];
	int m_1f4;						// mNumProbes, per the 0x00800B30 assert

public:
	int rva00800a40(void *input, unsigned char flag, int value);
	void rva00800b30(Rva00800A40Slot *slot);
};

int Rva00800920Owner::rva00800a40(
	void *input, unsigned char flag, volatile int value)
{
	if (m_14)
	{
		m_0c->send(0, value);
		return 0;
	}

	Rva00800A40Input &record = *(Rva00800A40Input *)input;
	if (record.m_04 != 0)
		reinterpret_cast<Rva00800A40Diag *>(Rva007EB810Get())->fail(
			"addr->GetType() == AddressInternet",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowserdemangler.cpp",
			0x4d);

	int index;
	for (index = 0; index < 8; ++index)
	{
		if (m_slots[index].m_00 == 0)
			goto found_slot;
	}
	goto no_slot;

	Rva00800A40Slot *slot = 0;
	found_slot:
	slot = &m_slots[index];
	goto check_slot;

	no_slot:
	slot = 0;
	check_slot:
	if (slot == 0)
	{
		reinterpret_cast<Rva00800A40Diag *>(Rva007EB810Get())->fail(
			"false",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowserdemangler.cpp",
			0x54);
		m_0c->send(-0x65, value);
	}
	slot->m_00 = m_18;
	++m_18;
	slot->m_04 = 0;
	slot->m_0c = value;
	slot->m_14 = record.m_04;
	slot->m_18 = record.m_08;
	slot->m_1c = record.m_0c;
	slot->m_20 = 0;
	slot->m_08 = flag;
	++m_1f4;
	return 0;
}

// ?rva00800b30@Rva00800920Owner@@QAEXPAURva00800A40Slot@@@Z
// 0x00800B30 (58 B), the release side of rva00800a40: it clears the fields
// that body fills (id, +0x04, value, +0x20 and the flag byte) and drops the
// probe count, asserting "mNumProbes >= 0" at gamebrowserdemangler.cpp:0x147.
void Rva00800920Owner::rva00800b30(Rva00800A40Slot *slot)
{
	slot->m_00 = 0;
	slot->m_04 = 0;
	slot->m_0c = 0;
	slot->m_20 = 0;
	slot->m_08 = 0;
	--m_1f4;
	if (m_1f4 < 0)
		reinterpret_cast<Rva00800A40Diag *>(Rva007EB810Get())->fail(
			"mNumProbes >= 0",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\gamebrowser\\gamebrowserdemangler.cpp",
			0x147);
}
