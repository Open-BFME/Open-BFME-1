// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: PathfindLayer::isUsed, retail 0x003FBB90, 23 bytes. The body
// carried only a machine byte-dump row; reverse/reloc_names.csv holds the name
// with identity=real.
//
// Two pointers, at +0x38 and +0x3C; the layer counts as used if either is set.
// The answer is materialised in the whole of eax rather than just al, which is
// what an or of two pointer tests gives.

typedef bool Bool;

class Bridge;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindLayer
{
public:
	Bool isUsed(void);

private:
	char m_bfmeHead[0x38];
	Bridge *m_bfmeA;					// +0x38
	Bridge *m_bfmeB;					// +0x3C
};

// ?isUsed@PathfindLayer@@QAE_NXZ
Bool PathfindLayer::isUsed(void)
{
	return m_bfmeA != 0 || m_bfmeB != 0;
}
