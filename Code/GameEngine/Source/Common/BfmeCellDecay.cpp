// Byte-matched BFME cell-channel decay helper.

typedef unsigned int UnsignedInt;
typedef float Real;

class BfmeCell
{
public:
	void bfmeDecay(Real scale, Real subtract);

private:
	Real m_first[16];
	Real m_second[16];
	UnsignedInt m_firstMask;
	UnsignedInt m_secondMask;
};

void BfmeCell::bfmeDecay(Real scale, Real subtract)
{
	if (m_firstMask == 0 && m_secondMask == 0)
		return;

	if (m_firstMask == 0)
	{
		for (UnsignedInt playerIndex = 0; playerIndex < 16; ++playerIndex)
		{
			UnsignedInt playerMask = 1U << playerIndex;
			if ((m_secondMask & playerMask) != 0)
			{
				m_second[playerIndex] =
					scale * m_second[playerIndex] - subtract;
				if (m_second[playerIndex] <= 0.0f)
				{
					m_second[playerIndex] = 0.0f;
					m_secondMask &= ~playerMask;
				}
			}
		}
		return;
	}

	if (m_secondMask == 0)
	{
		for (UnsignedInt playerIndex = 0; playerIndex < 16; ++playerIndex)
		{
			UnsignedInt playerMask = 1U << playerIndex;
			if ((m_firstMask & playerMask) != 0)
			{
				m_first[playerIndex] =
					scale * m_first[playerIndex] - subtract;
				if (m_first[playerIndex] <= 0.0f)
				{
					m_first[playerIndex] = 0.0f;
					m_firstMask &= ~playerMask;
				}
			}
		}
		return;
	}

	for (UnsignedInt playerIndex = 0; playerIndex < 16; ++playerIndex)
	{
		UnsignedInt playerMask = 1U << playerIndex;
		if ((m_firstMask & playerMask) != 0)
		{
			m_first[playerIndex] = scale * m_first[playerIndex] - subtract;
			if (m_first[playerIndex] <= 0.0f)
			{
				m_first[playerIndex] = 0.0f;
				m_firstMask &= ~playerMask;
			}
		}

		if ((m_secondMask & playerMask) != 0)
		{
			m_second[playerIndex] = scale * m_second[playerIndex] - subtract;
			if (m_second[playerIndex] <= 0.0f)
			{
				m_second[playerIndex] = 0.0f;
				m_secondMask &= ~playerMask;
			}
		}
	}
}
