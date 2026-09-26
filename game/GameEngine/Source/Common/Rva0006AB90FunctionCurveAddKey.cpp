// ?addKey@Rva0006AB90FunctionCurve@@QAEXMMPBM0@Z
// Function-curve key accumulator at retail RVA 0x0006AB90.
// The curve setter at 0x0006AB10 and the Function-curve field strings identify
// the address-derived owner; this body preserves the retail tangent flags and
// its MSVC 7.1 register schedule.
// cl: /Iinputs/reference/shims/iniexception /DNDEBUG /DWIN32 /MD /EHsc

typedef int Int;

#include "Common/INIException.h"

// Retail calls this curve helper through the thunk at RVA 0x00032E9D.
class Rva0006AB10Curve
{
public:
	void set(float time, float value, Int inTangent, Int outTangent);
};

class Rva0006AB90FunctionCurve
{
public:
	void addKey(float time, float value, const float *inTangent,
		const float *outTangent);

private:
	Rva0006AB10Curve *m_curve;
	bool m_firstKey;
	float m_lastTime;
	float m_lastValue;
	union Tangent
	{
		float value;
		Int bits;
	} m_inTangent, m_outTangent;
	bool m_haveInTangent;
	bool m_haveOutTangent;
};

void Rva0006AB90FunctionCurve::addKey(float time, float value,
	const float *inTangent, const float *outTangent)
{
	if (m_firstKey) {
		m_lastTime = time;
		m_lastValue = value;
		m_firstKey = false;
		m_haveInTangent = inTangent != 0;
		if (m_haveInTangent)
			m_inTangent.bits = *(const Int *)inTangent;
		m_haveOutTangent = outTangent != 0;
		if (m_haveOutTangent)
			m_outTangent.bits = *(const Int *)outTangent;
		return;
	}

	if (time <= m_lastTime)
		throw INIException(3, "Function curve time must be increasing");

	if (!m_haveOutTangent)
		m_outTangent.value = (value - m_lastValue) / (time - m_lastTime);
	if (!m_haveInTangent)
		m_inTangent.value = m_outTangent.value;
	m_curve->set(m_lastTime, m_lastValue, m_inTangent.bits, m_outTangent.bits);
	if (!inTangent)
		m_inTangent.value = (value - m_lastValue) / (time - m_lastTime);
	else
		m_inTangent.bits = *(const Int *)inTangent;
	m_haveInTangent = true;
	m_haveOutTangent = outTangent != 0;
	if (m_haveOutTangent)
		m_outTangent.bits = *(const Int *)outTangent;
	m_lastTime = time;
	m_lastValue = value;
}
