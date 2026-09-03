// ?bfmeSetAxis1289@BfmeSlotState1289@@QAEXHMH@Z
// partial score=0.45 date=2026-09-03
// Open-BFME5 conversion.
// cl: /I Code/Libraries/Source/WWVegas/WWLib /I Code/Libraries/Source/WWVegas/WWMath

#include "../../../Libraries/Source/WWVegas/WWMath/wwmath.h"

void d_008ac790(void);

extern float g_bfmeAngleScale008AC9F0;
extern float g_bfmeAxisScale008AC9F0;
extern float g_bfmeExtentScale008AC9F0;

class BfmeSlotState1289
{
public:
	void bfmeSetAxis1289(int axis, float value, int enabled);

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
	d_008ac790();
	m_values[axis] = value;

	float angle = m_values[6] * g_bfmeAngleScale008AC9F0;
	float c = WWMath::Cos(angle);
	float s = WWMath::Sin(angle);
	float x = m_values[2] * g_bfmeAxisScale008AC9F0;
	float y = m_values[3] * g_bfmeAxisScale008AC9F0;

	m_output10[0] = x * c;
	m_output10[1] = x * s;
	m_output10[2] = -y * c;
	m_output10[3] = y * s;
	m_output10[4] = m_values[0];
	m_output10[5] = m_values[1];
	m_output10[6] = m_values[7] * g_bfmeAxisScale008AC9F0;
	m_output10[11] = m_values[8] * g_bfmeExtentScale008AC9F0;
	m_output10[12] = m_values[9] * g_bfmeExtentScale008AC9F0;
	m_output10[13] = m_values[10] * g_bfmeExtentScale008AC9F0;

	m_enabled = enabled != 0;
}
