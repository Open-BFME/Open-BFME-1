// Open-BFME5 conversions.

struct BfmeC1104;

struct BfmeVt1104
{
	char m_bfmePad[0x114];
	void (__stdcall *m_bfme114)(BfmeC1104 *self, int a, int b, int c);
};

struct BfmeC1104
{
	BfmeVt1104 *m_bfmeVt;
};

struct IDirect3DDevice8;

class DX8Wrapper
{
	friend void __cdecl bfmeGo1104A(int);

protected:
	static IDirect3DDevice8 *D3DDevice;
	static unsigned int texture_stage_state_changes;
};

extern unsigned int number_of_DX8_calls;
#define g_bfmeC1104 reinterpret_cast<BfmeC1104 *>(DX8Wrapper::D3DDevice)
#define g_bfmeA1104 DX8Wrapper::texture_stage_state_changes

void __cdecl bfmeGo1104A(int a)
{
	g_bfmeC1104->m_bfmeVt->m_bfme114(g_bfmeC1104, a, 6, 2);
	number_of_DX8_calls++;
	g_bfmeA1104++;
	g_bfmeC1104->m_bfmeVt->m_bfme114(g_bfmeC1104, a, 5, 2);
	number_of_DX8_calls++;
	g_bfmeA1104++;
	g_bfmeC1104->m_bfmeVt->m_bfme114(g_bfmeC1104, a, 0xa, 0);
	number_of_DX8_calls++;
	g_bfmeA1104++;
	g_bfmeC1104->m_bfmeVt->m_bfme114(g_bfmeC1104, a, 7, 1);
	number_of_DX8_calls++;
	g_bfmeA1104++;
}
