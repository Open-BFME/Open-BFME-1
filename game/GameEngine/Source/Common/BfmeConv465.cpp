struct BfmeGotBHF
{
	unsigned char m_bfmeHead[0x48];
	int m_bfmeValue;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
// Declaration only: the spelling of the reference this call site makes. The
// definition is GameWindow.cpp's body at 0x00478C70, which this TU does not
// include; retail encodes the call through its ILT thunk 0x00046538.
class GameWindow
{
public:
	void *winGetUserData();
};

// Opaque: the receiver is a GameWindow, but this function's own ledger row
// (?bfmeGoBHF@@YAHPAVBfmeSubBHF@@@Z) carries the parameter type in its mangled
// name, so the stand-in stays and the call casts.
class BfmeSubBHF
{
};

int bfmeGoBHF(BfmeSubBHF *sub)
{
	if (sub == 0)
		return -1;
	return ((BfmeGotBHF *)reinterpret_cast<GameWindow *>(sub)
		->winGetUserData())->m_bfmeValue;
}