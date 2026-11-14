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
// Retail 0x012F706C: use the existing data owner; retain the local pointee view.
extern class LivingWorldManager *TheLivingWorldManager;
// Retail 0x012F7048: use the existing data owner; retain the local pointee view.
extern class Rva006092D0State *g_rva012F7048LivingWorld;

class BfmeHost961
{
public:
	void bfmeGo961();
	void bfmeFallback961(int a, int b);
};

void BfmeHost961::bfmeGo961()
{
	((BfmeResetA961 *)TheLivingWorldLogic)->bfmeReset961();

	if (reinterpret_cast<BfmeGate961 *>(TheLivingWorldManager)->bfmeCheck961() && !reinterpret_cast<BfmeFlag961 *>(g_rva012F7048LivingWorld)->m_bfmeFlag) {
		reinterpret_cast<BfmeGate961 *>(TheLivingWorldManager)->bfmeFinish961();
		return;
	}

	bfmeFallback961(0, 0);
}
