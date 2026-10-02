// Open-BFME5 conversions.

class BfmeResetA961
{
public:
	void bfmeReset961();
};

class BfmeGate961
{
public:
	char bfmeCheck961();
	void bfmeFinish961();
};

struct BfmeFlag961
{
	char m_bfmePad[8];
	char m_bfmeFlag;
};

// Retail 0x012F1028 is EA's `LivingWorldLogic *TheLivingWorldLogic`, defined
// once in game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldLogic.cpp.
// BfmeResetA961 above is this TU's own view of that address, so the call casts.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
extern BfmeGate961 *g_bfmeGate961;
extern BfmeFlag961 *g_bfmeFlag961;

class BfmeHost961
{
public:
	void bfmeGo961();
	void bfmeFallback961(int a, int b);
};

void BfmeHost961::bfmeGo961()
{
	((BfmeResetA961 *)TheLivingWorldLogic)->bfmeReset961();

	if (g_bfmeGate961->bfmeCheck961() && !g_bfmeFlag961->m_bfmeFlag) {
		g_bfmeGate961->bfmeFinish961();
		return;
	}

	bfmeFallback961(0, 0);
}
