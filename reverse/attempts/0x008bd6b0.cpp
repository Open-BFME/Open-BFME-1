// ?d_008bd6b0@@YAXXZ
// partial score=0.86 date=2026-08-30
extern char g_bfmeNode1281Vtable;
extern unsigned short g_bfmeEmptyString1281;
extern unsigned char g_bfmeFlag1281;

class BfmeNode1281
{
public:
	BfmeNode1281();

private:
	void *m_vtable;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	unsigned char m_bfme14;
	char m_padding15[3];
	void *m_bfme18;
	void *m_bfme1c;
	int m_bfme20;
	int m_bfme24;
	int m_bfme28;
	int m_bfme2c;
	int m_bfme30;
	unsigned int m_bfme34;
	int m_bfme38;
	int m_bfme3c;
	int m_bfme40;
	int m_bfme44;
	int m_bfme48;
	int m_bfme4c;
	int m_bfme50;
	int m_bfme54;
	int m_bfme58;
	int m_bfme5c;
	int m_bfme60;
	int m_bfme64;
	int m_bfme68;
	int m_bfme6c;
	int m_bfme70;
	union {
		unsigned int m_flags;
		struct {
			unsigned int m_lowBits : 3;
			unsigned int m_globalBit : 1;
			unsigned int m_remainingBits : 28;
		};
	};
};

BfmeNode1281::BfmeNode1281()
{
	m_bfme04 = -1;
	m_bfme08 = 0;
	m_bfme0c = 0;
	m_bfme10 = 0;
	m_bfme14 = 0;
	m_vtable = &g_bfmeNode1281Vtable;
	m_bfme18 = &g_bfmeEmptyString1281;
	++g_bfmeEmptyString1281;
	m_bfme1c = &g_bfmeEmptyString1281;
	++g_bfmeEmptyString1281;
	m_bfme24 = -1;
	m_bfme30 = -1;
	m_bfme38 = 3;
	m_bfme3c = 3;
	unsigned int flags = m_flags;
	m_bfme28 = 1;
	m_bfme2c = 1;
	m_flags = flags & ~7u;
	m_bfme20 = 0;
	m_bfme34 = 0xff000000;
	m_bfme40 = 0;
	m_bfme44 = 0;
	m_bfme48 = 0;
	m_bfme4c = 0;
	m_bfme60 = 0;
	m_bfme64 = 0;
	m_bfme68 = 0;
	m_bfme6c = 0;
	m_bfme70 = 0;
	m_globalBit = g_bfmeFlag1281;
	m_bfme50 = 0;
	m_bfme54 = 0;
	m_bfme58 = 0;
	m_bfme5c = 0;
}
