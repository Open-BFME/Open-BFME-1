// Open-BFME5 conversions.

class BfmeMgrTJA
{
public:
	char *bfmeFindTJA(int key);
};

// The DIR32 at 0x012F086C is retail's `CaveSystem *TheCaveSystem`
// (?TheCaveSystem@@3PAVCaveSystem@@A). CaveSystem is declared by
// game/GameEngine/Source/Common/System/game_engine_subsystems.h, so it is only
// forward-declared here and this TU's own view of it, BfmeMgrTJA, is reached
// through a cast rather than a second CaveSystem definition in this TU.
class CaveSystem;

extern CaveSystem *TheCaveSystem;

class BfmeThingTJA
{
public:
	char *bfmeGoTJA();
	char m_bfmePad[0xbc];
	int m_bfmeKey;
};

char *BfmeThingTJA::bfmeGoTJA()
{
	return ((BfmeMgrTJA *)TheCaveSystem)->bfmeFindTJA(m_bfmeKey) + 8;
}
