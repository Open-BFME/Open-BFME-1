// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: OCLUpdate::getRemainingFrames, retail 0x002988F0, 13 bytes. The
// body carried only a machine byte-dump row; reverse/reloc_names.csv holds the
// name with identity=real.
//
// The target frame at +0x20 minus the current frame, which TheGameLogic keeps
// at +0x3C. TheGameLogic is the global at 0x012F0898 the ledger already names.

typedef unsigned int UnsignedInt;

class GameLogicFrameSlice
{
public:
	char m_bfmeHead[0x3C];
	UnsignedInt m_bfmeFrame;				// +0x3C
};

extern GameLogicFrameSlice *TheGameLogic;			// 0x012F0898

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/OCLUpdate.h
class OCLUpdate
{
public:
	UnsignedInt getRemainingFrames(void);

private:
	char m_bfmeHead[0x20];
	UnsignedInt m_bfmeTargetFrame;				// +0x20
};

// ?getRemainingFrames@OCLUpdate@@QAEIXZ
UnsignedInt OCLUpdate::getRemainingFrames(void)
{
	return m_bfmeTargetFrame - TheGameLogic->m_bfmeFrame;
}
