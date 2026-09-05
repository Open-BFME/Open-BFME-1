// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ScriptConditions::evaluatePlayerHasComparisonPercentPower
// ZH twin: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp

class Gen_000C7DE0
{
public:
	float bfmeRatio(void) const;
};

struct BfmeR1087
{
	char m_pad[0xA4];
	Gen_000C7DE0 energy;
};

class BfmeD1087
{
public:
	BfmeR1087 *bfmeLook1087(unsigned short *h);
};

class Parameter;
class BfmeP1087
{
public:
	unsigned short bfmeNext1087(Parameter *a);
};

extern BfmeD1087 *g_bfmeD1087;
extern BfmeP1087 *g_bfmeP1087;

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
	bool evaluatePlayerHasComparisonPercentPower(Parameter *playerParm, Parameter *cmpParm, Parameter *pctParm);
};

// ?evaluatePlayerHasComparisonPercentPower@ScriptConditions@@IAE_NPAVParameter@@00@Z
bool ScriptConditions::evaluatePlayerHasComparisonPercentPower(
	Parameter *playerParm, Parameter *cmpParm, Parameter *pctParm)
{
	float testRatio = pctParm->getInt() * 0.01f;

	unsigned short mask = g_bfmeP1087->bfmeNext1087(playerParm);
	while (mask) {
		BfmeR1087 *r = g_bfmeD1087->bfmeLook1087(&mask);
		float ratio = r->energy.bfmeRatio();

		switch (cmpParm->getInt()) {
		case 0:
			if (ratio < testRatio)
				return true;
			break;
		case 1:
			if (ratio <= testRatio)
				return true;
			break;
		case 2:
			if (ratio == testRatio)
				return true;
			break;
		case 3:
			if (ratio >= testRatio)
				return true;
			break;
		case 4:
			if (ratio > testRatio)
				return true;
			break;
		case 5:
			if (ratio != testRatio)
				return true;
			break;
		}
	}
	return false;
}
