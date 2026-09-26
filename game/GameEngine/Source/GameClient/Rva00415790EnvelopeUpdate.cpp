// ?update@Rva00415790@@QAEXXZ
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/sweep
// Envelope layout: constructor 00412140 and matched TintEnvelope rate setters
// 00412270/00412320 witness vectors +04/+10/+1c/+28; state +38 and affect +39.
// Keep the bank's address-qualified owner until a named caller establishes it.
// No stack arguments: caller 0041BE60 invokes ILT 0002CE76 with ECX receiver.
// Code ends at +1ef (ret); +1f0..+1ff is a four-entry switch table.
// Independently resolved table destinations: +17/+fb/+29/+1d9 for states 0..3.
#include "vector3.h"

const float FADE_RATE_EPSILON = (0.001f);

class Rva00415790
{
public:
	void update();

private:
	void *m_vtable;
	Vector3 m_attackRate;
	Vector3 m_decayRate;
	Vector3 m_peakColor;
	Vector3 m_currentColor;
	unsigned int m_sustainCounter;
	signed char m_envState;
	bool m_affect;
};

void Rva00415790::update()
{
	switch (m_envState)
	{
	case 0:
		m_currentColor.Set(0, 0, 0);
		m_affect = false;
		break;

	case 2:
		if (m_decayRate.Length() > m_currentColor.Length() ||
			m_currentColor.Length() <= FADE_RATE_EPSILON)
		{
			m_envState = 0;
			m_affect = false;
		}
		else
		{
			Vector3::Add(m_decayRate, m_currentColor, &m_currentColor);
			m_affect = true;
		}
		break;

	case 1:
		{
			Vector3 delta;
			Vector3::Subtract(m_currentColor, m_peakColor, &delta);

			if (m_attackRate.Length() > delta.Length() ||
				delta.Length() <= FADE_RATE_EPSILON)
			{
				if (m_sustainCounter)
					m_envState = 3;
				else
					m_envState = 2;
			}
			else
			{
				Vector3::Add(m_attackRate, m_currentColor, &m_currentColor);
				m_affect = true;
			}
			break;
		}

	case 3:
		if (m_sustainCounter > 0)
			--m_sustainCounter;
		else
			m_envState = 2;
		break;
	}
}
