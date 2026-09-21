// ?d_00415790@@YAXXZ
// partial score=0.64 date=2026-09-17
// cl: /DNDEBUG /DWIN32 /MD /EHs-c-
// ?update@Rva00415790@@QAEXXZ present-unmatched

extern "C" double sqrt(double value);

struct Rva00415790Vector
{
	float x;
	float y;
	float z;
};

static __forceinline float rva00415790LengthInto(const float *v,
	volatile float *squared)
{
	*squared = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
	return (float)sqrt(*squared);
}

class Rva00415790
{
public:
	void update();

private:
	unsigned char m_pad00[4];
	float m_velocityX;
	float m_velocityY;
	float m_velocityZ;
	float m_inputX;
	float m_inputY;
	float m_inputZ;
	float m_targetX;
	float m_targetY;
	float m_targetZ;
	float m_accumulatedX;
	float m_accumulatedY;
	float m_accumulatedZ;
	int m_counter;
	signed char m_state;
	unsigned char m_active;
};

void Rva00415790::update()
{
	switch (m_state)
	{
	case 0:
		m_accumulatedX = 0.0f;
		m_accumulatedY = 0.0f;
		m_accumulatedZ = 0.0f;
		m_active = 0;
		return;

	case 1:
		{
			volatile float squared;
			volatile float inputLength =
				rva00415790LengthInto(&m_inputX, &squared);

			volatile float accumulatedLength =
				rva00415790LengthInto(&m_accumulatedX, &squared);
			if (inputLength > accumulatedLength)
			{
				m_state = 0;
				m_active = 0;
				return;
			}

			volatile float accumulatedLength2 =
				rva00415790LengthInto(&m_accumulatedX, &squared);
			if (accumulatedLength2 <= *(const float *)0x010F1070)
			{
				m_accumulatedX += m_inputX;
				m_accumulatedY += m_inputY;
				m_accumulatedZ += m_inputZ;
				m_active = 1;
				return;
			}

			m_state = 0;
			m_active = 0;
			return;

		}

	case 2:
		{
			volatile Rva00415790Vector delta;
			delta.x = m_accumulatedX - m_targetX;
			delta.y = m_accumulatedY - m_targetY;
			delta.z = m_accumulatedZ - m_targetZ;

			volatile float velocitySquared[2];
			velocitySquared[0] = m_velocityX * m_velocityX + m_velocityY * m_velocityY +
				m_velocityZ * m_velocityZ;
			volatile float velocityLength = (float)sqrt(velocitySquared[0]);
			volatile float deltaSquared = delta.z * delta.z + delta.y * delta.y +
				delta.x * delta.x;
			volatile float deltaLength = (float)sqrt(deltaSquared);

			if (velocityLength > deltaLength)
				goto rva00415790Case2Transition;

			if ((float)sqrt(deltaSquared) <=
				*(const float *)0x010F1070)
			{
				m_accumulatedX += m_velocityX;
				m_accumulatedY += m_velocityY;
				m_accumulatedZ += m_velocityZ;
				m_active = 1;
				return;
			}

			goto rva00415790Case2Transition;

		rva00415790Case2Transition:
			m_state = m_counter != 0 ? 3 : 2;
			return;
		}

	case 3:
		if (m_counter > 0)
		{
			--m_counter;
			return;
		}
		m_state = 2;
		return;
	}
}
