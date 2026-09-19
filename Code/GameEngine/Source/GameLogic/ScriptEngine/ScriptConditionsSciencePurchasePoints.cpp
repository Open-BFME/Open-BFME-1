// readable body of ?evaluateSciencePurchasePoints@ScriptConditions@@IAE_NPAVParameter@@0@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// Open-BFME5 conversions.

struct BfmeT1089
{
	char m_bfmePad[8];
	int m_bfme08;
};

class BfmeR1089
{
public:
	char bfmeChk1089(void);
	int bfmeVal1089(void);
	char m_bfmePad[0x264];
	int m_bfme264;
};

class BfmeD1089
{
public:
	BfmeR1089 *bfmeLook1089(short *h);
};

class BfmeP1089
{
public:
	int bfmeNext1089(int a);
};

extern BfmeD1089 *g_bfmeD1089;
extern BfmeP1089 *g_bfmeP1089;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	int getInt() const { return m_int; }

private:
	char m_unreconstructed00[8];
	int m_int;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptConditions.h
class ScriptConditions
{
protected:
	bool evaluateSciencePurchasePoints(Parameter *playerParm, Parameter *pointsParm);
};

// ?evaluateSciencePurchasePoints@ScriptConditions@@IAE_NPAVParameter@@0@Z
bool ScriptConditions::evaluateSciencePurchasePoints(
	Parameter *playerParm, Parameter *pointsParm)
{
	int n = pointsParm->getInt();

	pointsParm = reinterpret_cast<Parameter *>(
		g_bfmeP1089->bfmeNext1089(reinterpret_cast<int>(playerParm)));
	while ((short)reinterpret_cast<int>(pointsParm)) {
		BfmeR1089 *r = g_bfmeD1089->bfmeLook1089(
			reinterpret_cast<short *>(&pointsParm));

		if (r && r->m_bfme264 >= n)
			return true;
	}
	return false;
}

char __stdcall bfmeGo1089B(int a)
{
	a = g_bfmeP1089->bfmeNext1089(a);
	while ((short)a) {
		BfmeR1089 *r = g_bfmeD1089->bfmeLook1089((short *)&a);

		if (r && r->bfmeChk1089())
			return 1;
	}
	return 0;
}

char __stdcall bfmeGo1089C(BfmeT1089 *t, int a)
{
	int n;

	a = g_bfmeP1089->bfmeNext1089(a);
	n = 0;
	while ((short)a) {
		BfmeR1089 *r = g_bfmeD1089->bfmeLook1089((short *)&a);

		if (r)
			n += r->bfmeVal1089();
	}
	return t->m_bfme08 >= n;
}
