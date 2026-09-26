// cl: /O2

extern "C" __declspec(dllimport) void __cdecl free(void *block);

void __stdcall rva007e8530_bar(void *self, void *g);

void *g_rva007e8530;

class Rva007E8600
{
public:
	void run();

private:
	char m_pad[0x20];
	void *m_20;
	int m_24;
	int m_28;
};

void Rva007E8600::run()
{
	rva007e8530_bar(this, g_rva007e8530);
	int z = 0;
	if (m_20 != 0)
	{
		free(m_20);
		m_20 = (void *)z;
	}
	m_24 = z;
	m_28 = z;
}
