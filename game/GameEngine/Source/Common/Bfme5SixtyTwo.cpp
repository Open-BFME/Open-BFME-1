// Four more: a masked table read, two three-dimensional distances, and a
// float range comparison.

extern int g_bfmeTableEJ[];					// retail 0x012AA068

class Gen_000D3690
{
public:
	int bfmeLookup(unsigned int index) const;

private:
	unsigned int m_bfmeWords[8];				// +0x00
};

// ?bfmeLookup@Gen_000D3690@@QBEHI@Z
int Gen_000D3690::bfmeLookup(unsigned int index) const
{
	if (m_bfmeWords[index >> 5] & (1 << (index & 31)))
		return g_bfmeTableEJ[index];

	return 0;
}

class BfmeVec3EJ
{
public:
	float m_bfmeX;						// +0x00
	float m_bfmeY;						// +0x04
	float m_bfmeZ;						// +0x08
};

class Gen_000E5A50
{
public:
	float bfmeDistanceSquared(const BfmeVec3EJ *point) const;

private:
	int m_bfmeHead[14];					// +0x00
	float m_bfmeX;						// +0x38
	float m_bfmeY;						// +0x3C
	float m_bfmeZ;						// +0x40
};

// ?bfmeDistanceSquared@Gen_000E5A50@@QBEMPBVBfmeVec3EJ@@@Z
float Gen_000E5A50::bfmeDistanceSquared(const BfmeVec3EJ *point) const
{
	float dx = m_bfmeX - point->m_bfmeX;
	float dy = m_bfmeY - point->m_bfmeY;
	float dz = m_bfmeZ - point->m_bfmeZ;

	return dx * dx + dy * dy + dz * dz;
}

class Gen_000E5A90
{
public:
	float bfmeDistanceSquared(const Gen_000E5A90 *other) const;

private:
	int m_bfmeHead[14];					// +0x00
	float m_bfmeX;						// +0x38
	float m_bfmeY;						// +0x3C
	float m_bfmeZ;						// +0x40
};

// ?bfmeDistanceSquared@Gen_000E5A90@@QBEMPBV1@@Z
float Gen_000E5A90::bfmeDistanceSquared(const Gen_000E5A90 *other) const
{
	float dx = m_bfmeX - other->m_bfmeX;
	float dy = m_bfmeY - other->m_bfmeY;
	float dz = m_bfmeZ - other->m_bfmeZ;

	return dx * dx + dy * dy + dz * dz;
}

// ?bfmeEqualFloats@@YA_NPBM00@Z
bool __cdecl bfmeEqualFloats(const float *first, const float *last, const float *other)
{
	while (first != last)
	{
		if (*first != *other)
			return false;

		++first;
		++other;
	}

	return true;
}
