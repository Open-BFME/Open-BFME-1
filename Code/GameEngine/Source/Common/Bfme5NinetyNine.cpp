// Three siblings: the same reach, refused three different ways when the offset
// runs past the tolerance.

extern "C" double fabs(double value);
#pragma intrinsic(fabs)

extern float g_bfmeBiasMC;

class BfmeThingMC
{
public:
	int m_bfmeGap[2];							// +0x00
	float m_bfmeSpeed;							// +0x08
};

class BfmePointMD
{
public:
	int m_bfmeGap[16];							// +0x00
	float m_bfmeZ;								// +0x40
};

class Gen_001E1480
{
public:
	float bfmeReach(const BfmeThingMC *thing, float offset) const;
	float bfmeReachDelta(const BfmeThingMC *thing, const BfmePointMD *a, const BfmePointMD *b) const;
	float bfmeReachNeg(const BfmeThingMC *thing, const BfmeThingMC *other) const;
private:
	int m_bfmeGap[5];							// +0x000
	float m_bfmeScale;							// +0x014
	int m_bfmeGap2[325];						// +0x018
	float m_bfmeTol;							// +0x52c
};

float Gen_001E1480::bfmeReach(const BfmeThingMC *thing, float offset) const
{
	float reach = thing->m_bfmeSpeed * m_bfmeScale - g_bfmeBiasMC;

	if (m_bfmeTol > 0.0f && (float)fabs(offset) > m_bfmeTol)
		return 0.0f;
	if (reach < 0.0f)
		return 0.0f;
	return reach;
}

float Gen_001E1480::bfmeReachDelta(const BfmeThingMC *thing, const BfmePointMD *a, const BfmePointMD *b) const
{
	float reach = thing->m_bfmeSpeed * m_bfmeScale - g_bfmeBiasMC;

	if (m_bfmeTol > 0.0f && (float)fabs(b->m_bfmeZ - a->m_bfmeZ) > m_bfmeTol)
		return 0.0f;
	if (reach < 0.0f)
		return 0.0f;
	return reach;
}

float Gen_001E1480::bfmeReachNeg(const BfmeThingMC *thing, const BfmeThingMC *other) const
{
	float reach = thing->m_bfmeSpeed * m_bfmeScale - g_bfmeBiasMC;

	if (m_bfmeTol > 0.0f && (float)fabs(-other->m_bfmeSpeed) > m_bfmeTol)
		return 0.0f;
	if (reach < 0.0f)
		return 0.0f;
	return reach;
}
