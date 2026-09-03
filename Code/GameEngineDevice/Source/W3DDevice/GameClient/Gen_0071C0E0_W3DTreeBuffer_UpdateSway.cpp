// cl: /O2 /DNDEBUG /MD
// readable body of ?updateSway@W3DTreeBuffer@@IAEXABUBreezeInfo@@@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeBuffer.cpp
// BFME W3DTreeBuffer::updateSway.  The retail tree records use a 0xa4-byte
// stride and the BFME buffer keeps the sway arrays at the offsets below.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef short Short;
typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
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
	char m_pad00[0x7c];
	Int m_swayType;
	char m_pad80[0x24];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DTreeBuffer.h
class W3DTreeBuffer
{
protected:
	void updateSway(const BreezeInfo& info);

private:
	char m_pad00[0x1548];
	BfmeTree m_trees[12000];
	Int m_numTrees;
};

void W3DTreeBuffer::updateSway(const BreezeInfo& info)
{
	Int i = 0;
	char *sway = (char *)this + 0x1e33e8;
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
	if (*(Int *)((char *)this + 0x1e1cc8) > 0) {
		for (; j < m_numTrees; j++) {
			m_trees[j].m_swayType = 1 + GetGameClientRandomValue(
				0, 9, (char *)0x01120d60, 0xf9);
		}
	}

	Real high = *(Real *)0x01075334 + delta;
	Real low = *(Real *)0x01075334 - delta;
	char *step = (char *)this + 0x1e38c0;
	for (i = 0; i < 10; i++) {
		*(Real *)step = *(Real *)0x0107fac4 /
			((Real)info.m_breezePeriod * *(Real *)((char *)this + 0x1e3910));
		*(Real *)step *= GetGameClientRandomValueReal(
				low, high, (char *)0x01120d60, 0xfd);
		if (*(Real *)step < *(Real *)0x01075350)
			*(Real *)step = 0.0f;
		*(Real *)(step - 0x28) = 0;
		*(Real *)(step + 0x28) = GetGameClientRandomValueReal(
				low, high, (char *)0x01120d60, 0x102);
		step += 4;
	}
	*(Int *)((char *)this + 0x1e3894) = (Int)info.m_breezeVersion;
}
