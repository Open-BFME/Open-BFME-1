// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: OCLUpdate::getRemainingFrames, retail 0x002988F0, 13 bytes. The
// body carried only a machine byte-dump row; targets/game/reverse/reloc_names.csv holds the
// name with identity=real.
//
// The target frame at +0x20 minus the current frame, which TheGameLogic keeps
// at +0x3C. TheGameLogic is the global at 0x012F0898 the ledger already names.

typedef unsigned int UnsignedInt;

// The global at 0x012F0898 is EA's `GameLogic *TheGameLogic`
// (?TheGameLogic@@3PAVGameLogic@@A, defined in GameLogic.cpp); only that
// spelling links.  The real header declares GameLogic with getFrame() only,
// so the +0x3C frame slot is read through this TU-local view.
class GameLogic;
class GameLogicFrameSlice
{
public:
	char m_bfmeHead[0x3C];
	UnsignedInt m_bfmeFrame;				// +0x3C
};

extern GameLogic *TheGameLogic;				// 0x012F0898

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/OCLUpdate.h
class OCLUpdate
{
public:
	UnsignedInt getRemainingFrames(void);

private:
	char m_bfmeHead[0x20];
	UnsignedInt m_nextCreationFrame;				// +0x20
};

// ?getRemainingFrames@OCLUpdate@@QAEIXZ
UnsignedInt OCLUpdate::getRemainingFrames(void)
{
	return m_nextCreationFrame - ((GameLogicFrameSlice *)TheGameLogic)->m_bfmeFrame;
}
