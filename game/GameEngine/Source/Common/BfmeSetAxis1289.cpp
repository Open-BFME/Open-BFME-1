// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
#include <math.h>

extern const float g_01075954;
extern const float g_01076C24;
extern const float g_0107C64C;

class BfmeSlotState1289
{
public:
	void bfmeSetAxis1289(int axis, float value, int enabled);
	void rva008AC790();

private:
	char m_padding00[0x10];
	float m_output10[14];
	float *m_values;
	char m_padding4c[0x14];
	unsigned m_unused : 16;
	unsigned m_enabled : 1;
	unsigned m_rest : 15;
};

void BfmeSlotState1289::bfmeSetAxis1289(int axis, float value, int enabled)
{
	rva008AC790();
	m_values[axis] = value;

	float *v = m_values;
	float angle = *(volatile float *)(v + 6) * g_01075954;
	float c = cosf(angle);
	float s = sinf(angle);
	float x = *(volatile float *)(v + 2) * g_01076C24;
	float y = *(volatile float *)(v + 3) * g_01076C24;

	m_output10[0] = x * c;
	m_output10[1] = x * s;
	m_output10[2] = -(y * s);
	m_output10[3] = y * c;
	m_output10[4] = v[0];
	m_output10[5] = v[1];
	m_output10[6] = *(volatile float *)(v + 7) * g_01076C24;
	m_output10[11] = *(volatile float *)(v + 8) * g_0107C64C;
	m_output10[12] = *(volatile float *)(v + 9) * g_0107C64C;
	m_output10[13] = *(volatile float *)(v + 10) * g_0107C64C;

	m_enabled = (unsigned char)enabled != 0;
}
