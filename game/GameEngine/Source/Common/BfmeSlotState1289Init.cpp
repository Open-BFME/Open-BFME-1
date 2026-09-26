// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

#include <math.h>

#pragma intrinsic(atan2, sin, cos)

extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int bytes);

#define BfmeTwoPi (*(const double *)0x01126CE8)
#define BfmeAngleUpper (*(const float *)0x01097114)
#define BfmeAngleLower (*(const float *)0x01097108)
#define BfmeAngleSpan (*(const float *)0x01136850)
#define BfmeAngleScale (*(const float *)0x0107533C)
#define BfmeKTHE (*(const float *)0x0109ECC0)
#define BfmeAxisScale (*(const float *)0x0107FAC4)
#define BfmeAxisScaleY (*(const float *)0x01081810)
#define BfmeOutputScale (*(const float *)0x01084068)
#define BfmeAxisLimit (*(const float *)0x01136948)
#define BfmeAxisLimitOther (*(const float *)0x0109BF40)
#define BfmeUnit (*(const float *)0x01075334)

extern "C" void *__cdecl memset(void *dst, int value, unsigned int count);
#pragma intrinsic(memset)

static inline float wrapBfmeAngle1289(float angle)
{
	angle = (float)fmod((double)angle, BfmeTwoPi);
	if (angle >= BfmeAngleUpper)
		angle -= BfmeAngleSpan;
	if (angle < BfmeAngleLower)
		angle += BfmeAngleSpan;
	return angle;
}

class BfmeSlotState1289
{
public:
	void rva008AC790();

private:
	char m_padding00[0x10];
	float m_output10[14];
	float *m_values;
};

// ?rva008AC790@BfmeSlotState1289@@QAEXXZ
void BfmeSlotState1289::rva008AC790()
{
	if (m_values != 0)
		return;

	float *values = (float *)Rva008C5D70Alloc(0x30);
	float *initialized = 0;
	if (values != 0)
	{
		memset(values, 0, 0x30);
		initialized = values;
	}
	m_values = initialized;

	m_values[0] = m_output10[4];
	m_values[1] = m_output10[5];

	float first = wrapBfmeAngle1289((float)atan2(m_output10[1], m_output10[0]));
	float second = wrapBfmeAngle1289((float)atan2(-m_output10[2], m_output10[3]));
	float delta = wrapBfmeAngle1289(first - second);
	delta *= BfmeAngleScale;
	float combined = delta + second;
	m_values[6] = combined * BfmeKTHE;

	float c = cosf(combined);
	float s = sinf(combined);
	if (c > BfmeAxisLimit && c < BfmeAxisLimitOther)
	{
		if (s > BfmeAxisLimit && s < BfmeAxisLimitOther)
		{
			m_values[2] = 100.0f;
			m_values[3] = 100.0f;
		}
		else
		{
			float reciprocal = BfmeUnit / s;
			m_values[2] = (m_output10[1] * reciprocal) * BfmeAxisScale;
			m_values[3] = (m_output10[2] * reciprocal) * BfmeAxisScaleY;
		}
	}
	else
	{
		float reciprocal = BfmeUnit / c;
		m_values[2] = (m_output10[0] * reciprocal) * BfmeAxisScale;
		m_values[3] = (m_output10[3] * reciprocal) * BfmeAxisScale;
	}

	m_values[7] = m_output10[6] * BfmeAxisScale;
	m_values[8] = m_output10[11] * BfmeOutputScale;
	m_values[9] = m_output10[12] * BfmeOutputScale;
	m_values[10] = m_output10[13] * BfmeOutputScale;
	m_values[11] = 1.0f;
}
