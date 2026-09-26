// cl: /DNDEBUG /MD /EHs-c-
//
// Retail 0x007243A0, 365 bytes: the three-state blend step of the object
// whose reset body is BfmeThingTBA::bfmeTwoTBA (0x00723D80, tail-called here
// through the 0x00024780 link thunk).  The matched caller
// W3DSnowManager::extraAfterFmod (0x00725620) reaches it through the
// 0x00027435 link thunk.  Owner and method names stay address-derived.
//
// Retail loads the 0x012F15F8 override root once and walks it three times,
// keeping the root and its m_nextOverride in callee-saved registers across
// the out-of-line getFinalOverride calls.  MSVC only does that when it has
// seen getFinalOverride's body in this TU and knows it writes no memory, so
// the walk is upstream's inline recursive definition
// (inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/
// Common/Overridable.h); with only a declaration the root and its next
// pointer land in a rotated register set (EDI/EBX/EBP for EBX/EBP/EDI).

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	void *m_vtable;
	const Overridable *m_nextOverride;
};

class BfmeOverride1137 : public Overridable
{
public:
	char m_unmodelled08[0x58 - 8];
	char m_flag58;
	char m_unmodelled59[3];
	int m_5c;
};

extern BfmeOverride1137 *g_bfmeGlo012F15F8;

// One inlined level of upstream OVERRIDE<T>::operator->.
static inline const BfmeOverride1137 *finalOverride1137(const BfmeOverride1137 *root)
{
	if (!root)
		return 0;
	return (const BfmeOverride1137 *)root->getFinalOverride();
}

class BfmeThingTBA
{
public:
	void rva007243A0(void);
	void bfmeTwoTBA(void);

private:
	char m_unmodelled00[0x10];
	float m_10;
	char m_unmodelled14[0x38 - 0x14];
	float m_38;
	char m_unmodelled3c[0x4c - 0x3c];
	int m_4c;
	float m_50;
	float m_54;
	float m_58;
	float m_5c;
	float m_60;
	float m_64;
	char m_unmodelled68[0x98 - 0x68];
	int m_98;
};

void BfmeThingTBA::rva007243A0(void)
{
	if (!finalOverride1137(g_bfmeGlo012F15F8)->m_flag58 || m_98 == 0)
		return;

	float fraction = (float)(finalOverride1137(g_bfmeGlo012F15F8)->m_5c - m_4c) /
		(float)finalOverride1137(g_bfmeGlo012F15F8)->m_5c;
	if (fraction > 1.0f)
	{
		bfmeTwoTBA();
	}
	else if (fraction > m_54)
	{
		m_98 = 3;
		float blend = (fraction - m_54) / (1.0f - m_54);
		m_38 = m_5c - (m_5c - m_58) * blend;
		m_10 = m_64 - (m_64 - m_60) * blend;
	}
	else if (fraction > m_50)
	{
		m_98 = 2;
		m_38 = m_5c;
		m_10 = m_64;
	}
	else if (fraction > 0.0f)
	{
		m_98 = 1;
		float blend = m_50 > 0.00001f ? fraction / m_50 : 1.0f;
		m_38 = m_58 + (m_5c - m_58) * blend;
		m_10 = m_60 + (m_64 - m_60) * blend;
	}
	else
	{
		bfmeTwoTBA();
	}
}
