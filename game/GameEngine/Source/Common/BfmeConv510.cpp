struct BfmeSubBPF
{
	unsigned char m_bfmeHead[4];
};

// Retail reaches the three-argument dispatch through the ILT thunk 0x00022AB6,
// five bytes of `jmp 0x004559A0`. The body there is the ledger's matched
// updateMapStartSpots
// (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/UpdateMapStartSpotsBFME.cpp,
// 838 bytes at 0x004559A0), but it is a __cdecl free function whose third
// parameter is `bool`: spelling this call with it makes the compiler normalise
// the raw pointer in the third slot to 0/1, which moves bytes. The only symbol
// defined at 0x00022AB6 itself is the generated zero-argument thunk
// ?j_00022ab6@@YAXXZ (game/gen_small/thunks_016.cpp), so the reference carries
// that name and the three-argument __cdecl shape is recovered by re-casting it.
// A member-function union pun (BfmeConv1850.cpp,
// game/GameEngine/Source/Common/INI/INIWindowTransition.cpp) is not needed for a
// __cdecl free function.
extern void j_00022ab6();

typedef void (*BfmeDoBPFDispatch)(void *, void *, void *);

class BfmeThingBPF
{
public:
	void bfmeGoBPF(void *one, void *two);
	unsigned char m_bfmeHead[0x14];
	BfmeSubBPF m_bfmeSub;
};

void BfmeThingBPF::bfmeGoBPF(void *one, void *two)
{
	if (one != 0)
		// __cdecl on both sides, so the cast is a pure re-spelling of the thunk's
		// address; MSVC folds it back into retail's direct three-argument call.
		reinterpret_cast<BfmeDoBPFDispatch>(j_00022ab6)(one, &m_bfmeSub, two);
}