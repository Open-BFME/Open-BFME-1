// ?addKey@Rva0006AB90FunctionCurve@@QAEXMMPBM0@Z
// partial score=0.95 date=2026-09-06
// cl: /Ireference/shims/iniexception /DNDEBUG /DWIN32 /MD /EHsc

typedef int Int;

#include "Common/INIException.h"

// Retail calls this curve helper through the thunk at RVA 0x00032E9D.
class Rva0006AB10Curve
{
public:
	void set(float time, float value, Int inTangent, Int outTangent);
};

// The Function curve strings and the callback at RVA 0x0006ADC0 identify this
// address-derived owner. The first key is held until the next key supplies a
// segment, then the helper curve receives the previous key and its tangents.
class Rva0006AB90FunctionCurve
{
public:
	void addKey(float time, volatile float value, const float *inTangent, const float *outTangent);

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

// ?addKey@Rva0006AB90FunctionCurve@@QAEXMMPBM0@Z
void Rva0006AB90FunctionCurve::addKey(float time, volatile float value,
	const float *inTangent, const float *outTangent)
{
	if (m_firstKey) {
		m_lastValue = value;
		m_lastTime = time;
		m_haveInTangent = inTangent != 0;
		m_firstKey = false;
		m_haveOutTangent = outTangent != 0;
		if (inTangent != 0)
			m_inTangent.bits = *(const Int *)inTangent;
		if (outTangent != 0)
			m_outTangent.bits = *(const Int *)outTangent;
		return;
	}

	if (!(time > m_lastTime))
		throw INIException(3, "Function curve time must be increasing");

	if (!m_haveOutTangent)
		m_outTangent.value = (value - m_lastValue) / (time - m_lastTime);
	if (!m_haveInTangent)
		m_inTangent.value = m_outTangent.value;
	m_curve->set(m_lastTime, m_lastValue, m_inTangent.bits, m_outTangent.bits);
	if (inTangent == 0)
		m_inTangent.bits = m_outTangent.bits;
	else
		m_inTangent.bits = *(const Int *)inTangent;
	m_haveInTangent = true;
	m_haveOutTangent = outTangent != 0;
	if (outTangent != 0)
		m_outTangent.bits = *(const Int *)outTangent;
	m_lastTime = time;
	m_lastValue = value;
}
