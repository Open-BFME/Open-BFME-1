// Three more: a point setter that reports whether anything moved, a value that
// refuses to go below zero, and a list comparison item by item.

class Gen_0093D200
{
public:
	bool bfmeSetPoint(float x, float y);
private:
	int m_bfmeGap[47];							// +0x00
	float m_bfmeX;								// +0xbc
	float m_bfmeY;								// +0xc0
};

bool Gen_0093D200::bfmeSetPoint(float x, float y)
{
	if (m_bfmeX == x && m_bfmeY == y)
		return false;

	m_bfmeX = x;
	m_bfmeY = y;
	return true;
}

class Gen_00955B70
{
public:
	void bfmeSetValue(float value);
private:
	int m_bfmeGap[4];							// +0x00
	int m_bfmeFlags;							// +0x10
	int m_bfmeGap2[55];							// +0x14
	float m_bfmeValue;							// +0xf0
};

void Gen_00955B70::bfmeSetValue(float value)
{
	m_bfmeValue = (value > 0.0f) ? value : 0.0f;
	m_bfmeFlags &= ~0x20000;
}

class BfmeItemKA
{
public:
	int m_bfmeId;								// +0x00
	int m_bfmeGap[2];							// +0x04
};

class Gen_009375A0
{
public:
	bool bfmeSameList(const Gen_009375A0 *other) const;
private:
	int m_bfmeGap;								// +0x00
	BfmeItemKA *m_bfmeItems;					// +0x04
	int m_bfmeCount;							// +0x08
};

bool Gen_009375A0::bfmeSameList(const Gen_009375A0 *other) const
{
	int count = m_bfmeCount;
	if (count == other->m_bfmeCount)
	{
		for (int index = 0; index < count; ++index)
		{
			if (m_bfmeItems[index].m_bfmeId != other->m_bfmeItems[index].m_bfmeId)
				return false;
		}
		return true;
	}
	return false;
}
