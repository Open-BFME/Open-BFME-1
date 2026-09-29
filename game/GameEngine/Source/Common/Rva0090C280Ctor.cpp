// cl: /O2 /Ob0

// Retail vtable 0x0113A56C, pinned as ?g_bfme927Vft@@3PADA
// (targets/game/reverse/symbols.csv); BfmeConv927.cpp already names it.
extern char g_bfme927Vft[];

class Rva0090C280
{
	void *m_vptr;
	char m_04;
	void *m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	int m_3C;
	int m_40;
	int m_44;

public:
	Rva0090C280();
	void releaseResource0090C2D0();
};

Rva0090C280::Rva0090C280()
{
	m_vptr = g_bfme927Vft;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
	m_20 = 0;
	m_24 = 1;
	m_28 = 1;
	m_2C = 1;
	m_30 = 1;
	m_34 = 0;
	m_38 = 0;
	m_3C = 0;
	m_40 = 2;
	m_44 = 0;
}

void Rva0090C280::releaseResource0090C2D0()
{
	m_vptr = g_bfme927Vft;
	void *resource = m_08;
	if (resource) {
		void (__stdcall *destroy)(void *) = ((void (__stdcall **)(void *))*(void **)resource)[2];
		destroy(resource);
	}
}
