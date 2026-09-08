// cl: /O2 /DNDEBUG /MD
// Readable body of ?updateSway@W3DTreeBuffer@@IAEXABUBreezeInfo@@@Z.
// Retail stores the BFME tree buffer fields at the offsets below.

typedef int Int;
typedef short Short;
typedef float Real;

struct BreezeInfo
{
	Real m_direction;
	Real m_directionVecX;
	Real m_directionVecY;
	Real m_intensity;
	Real m_lean;
	Real m_randomness;
	Short m_breezePeriod;
	Short m_breezeVersion;
};

extern Real bfmeCosVNB(Real);
extern Real bfmeSinVNB(Real);
extern Int GetGameClientRandomValue(Int, Int, char *, Int);
extern Real GetGameClientRandomValueReal(Real, Real, char *, Int);

struct BfmeTree
{
	Int m_swayType;
	char m_pad04[0xe4];
};

class W3DTreeBuffer
{
protected:
	void updateSway(const BreezeInfo& info);

private:
	char m_pad00[0x210];
	BfmeTree m_trees[11999];
	char m_padAfterTrees[0x88];
	Int m_numTrees;
	char m_padBeforeSway[0x1bc8];
	Int m_curSwayVersion;
	Real m_curSwayOffset[10];
	Real m_curSwayStep[10];
	Real m_curSwayFactor[10];
};

void W3DTreeBuffer::updateSway(const BreezeInfo& info)
{
	Int i = 0;
	char *sway = (char *)this + 0x2a93d0;
	for (; i < 100; ) {
		Real factor = bfmeCosVNB((Real)i * *(Real *)0x01120dbc);
		Real angle = info.m_lean + (info.m_intensity * factor);
		Real S = bfmeSinVNB(angle);
		Real C = bfmeCosVNB(angle);

		*(Real *)(sway - 0x04) = info.m_directionVecX * S;
		*(Real *)sway = info.m_directionVecY * S;
		*(Real *)(sway + 0x04) = C - *(Real *)0x01075334;
		++i;
		sway += 0xc;
	}

	Real delta = info.m_randomness * *(Real *)0x0107533c;
	register Int j = 0;
	if (m_numTrees > 0) {
		for (; j < m_numTrees; j++) {
			m_trees[j].m_swayType = 1 + GetGameClientRandomValue(
				0, 9, (char *)0x01121410, 0xe6);
		}
	}

	Real high = *(Real *)0x01075334 + delta;
	Real low = *(Real *)0x01075334 - delta;
	for (i = 0; i < 10; i++) {
		m_curSwayStep[i] = *(Real *)0x0107fac4 /
			((Real)info.m_breezePeriod * *(Real *)((char *)this + 0x2a98f8));
		m_curSwayStep[i] *= GetGameClientRandomValueReal(
				low, high, (char *)0x01121410, 0xea);
		if (m_curSwayStep[i] < *(Real *)0x01075350)
			m_curSwayStep[i] = 0.0f;
		m_curSwayOffset[i] = 0;
		m_curSwayFactor[i] = GetGameClientRandomValueReal(
				low, high, (char *)0x01121410, 0xef);
	}
	m_curSwayVersion = (Int)info.m_breezeVersion;
}
