// cl: /DNDEBUG /MD /EHsc

typedef float Real;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ParabolicEase.h
class ParabolicEase
{
public:
	void setEaseTimes(Real easeInTime, Real easeOutTime, Real duration);

private:
	Real m_in;
	Real m_out;
};

namespace
{
	template <typename T>
	inline T clamp(T value, T minimum = T(0), T maximum = T(1))
	{
		if (value < minimum)
			return minimum;
		else if (value > maximum)
			return maximum;
		return value;
	}
}

void ParabolicEase::setEaseTimes(Real easeInTime, Real easeOutTime, Real duration)
{
	if (duration > 0.0f)
	{
		if (easeInTime > 0.0f)
			easeInTime /= duration;
		else
			easeInTime = 0.0f;

		if (easeOutTime > 0.0f)
			easeOutTime /= duration;
		else
			easeOutTime = 0.0f;
	}

	m_in = easeInTime;
	if (m_in < 0.0f || m_in > 1.0f)
		m_in = clamp(m_in);

	m_out = 1.0f - easeOutTime;
	if (m_out < 0.0f || m_out > 1.0f)
		m_out = clamp(m_out);

	if (m_in > m_out)
		m_in = m_out;
}
