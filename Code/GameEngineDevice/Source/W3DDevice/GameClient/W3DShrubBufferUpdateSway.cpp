// cl: /O2 /DNDEBUG /MD
// readable body of ?updateSway@W3DShrubBuffer@@IAEXABUBreezeInfo@@@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShrubBuffer.cpp
//
// Retail 0x0071C0E0.  The three GetGameClientRandomValue* calls below pass the
// literal at 0x01120D60 as their __FILE__ argument, and reverse/string_xrefs.tsv
// binds that literal to
//   F:\bfme\Code\gameenginedevice\Source\W3DDevice\GameClient\W3DShrubBuffer.cpp
// which names this function's translation unit outright.  So the owner is
// W3DShrubBuffer, the near-clone of W3DTreeBuffer, and not W3DTreeBuffer itself:
// that file's own literal binds to 0x00732500 and 0x00736B60, the run where
// allocateTreeBuffers and removeTree already sit.  The line numbers the three
// calls pass -- 0xF9, 0xFD, 0x102 -- are lines 249, 253 and 258 of it.
//
// The retail shrub records use a 0xa4-byte stride and the buffer keeps the sway
// arrays at the offsets below.

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

struct BfmeShrub
{
	char m_pad00[0x7c];
	Int m_swayType;
	char m_pad80[0x24];
};

// upstream layout of the tree-buffer twin this class clones:
// reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DTreeBuffer.h
class W3DShrubBuffer
{
protected:
	void updateSway(const BreezeInfo& info);

private:
	char m_pad00[0x1548];
	BfmeShrub m_shrubs[12000];
	Int m_numShrubs;
};

void W3DShrubBuffer::updateSway(const BreezeInfo& info)
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
		for (; j < m_numShrubs; j++) {
			m_shrubs[j].m_swayType = 1 + GetGameClientRandomValue(
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
