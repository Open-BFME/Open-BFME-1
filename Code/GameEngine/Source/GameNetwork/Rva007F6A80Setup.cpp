// cl: /O2 /Ob0
// Converted from Code/gen_asm/d_007f2a50.asm (?d_007f6a80@@YAXXZ).
// Void thiscall: zeros +8..+18, append empty literal onto +0x1C, then +24/+28/+6C.
// Not a constructor -- retail has no mov eax,esi.

class Rva00800290Buffer
{
public:
	void append(const char *text);
	char *m_ptr;
	int m_size;
};

extern const char g_Rva0107301CEmptyString[];

class Rva007F6A80Host
{
public:
	void setup();

	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	char m_14;
	char m_pad15[3];
	int m_18;
	Rva00800290Buffer m_buf;
	int m_24;
	int m_28;
	char m_pad2C[0x6C - 0x2C];
	char m_6C;
};

void Rva007F6A80Host::setup()
{
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_buf.append(g_Rva0107301CEmptyString);
	m_24 = 0;
	m_28 = 0;
	m_6C = 0;
}
