// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GameLODManager::findDynamicLODLevel, retail 0x0007C440.
//
// The Zero Hour body unchanged. Three things about it differ from what
// GameLOD.cpp can produce, and the retail bytes state all three outright:
//
//   the loop runs 4 down to 0 inclusive (`mov eax,4` ... `test eax,eax; jge`)
//     and the fall-through returns 0 (`xor eax,eax`), so the level enum bases
//     DYNAMIC_GAME_LOD_LOW at 0 and DYNAMIC_GAME_LOD_VERY_HIGH at 4 -- five
//     levels where ZH's GameLOD.h has four, and where this tree's header bases
//     LOW at 1 (it compiles the same source to `cmp eax,1` and `mov eax,1`)
//
//   the walk steps 0x10 (`sub ecx,0x10`), so DynamicGameLODInfo is four dwords,
//     not the six ZH declares
//
//   the walk is seeded at this+0x160 (`lea ecx,[esi+0x160]`) and steps DOWN,
//     so that is element 4 and the array itself starts at this+0x120
//
// Kept out of GameLOD.cpp because the first two are header changes that gate
// the tree, and the enum rebase would move every one of that file's 16 matched
// rows that mentions a level.

// Only the two bounds are proven by this body. ZH names four levels; BFME has
// five, and nothing here says where in the order the extra one sits, so it is
// not invented.
enum DynamicGameLODLevel
{
	DYNAMIC_GAME_LOD_UNKNOWN = -1,
	DYNAMIC_GAME_LOD_LOW = 0,
	DYNAMIC_GAME_LOD_VERY_HIGH = 4,
	DYNAMIC_GAME_LOD_COUNT = 5
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameLOD.h
struct DynamicGameLODInfo
{
	int m_minFPS;									///< first dword of the entry
	int m_unreconstructed_04[3];					///< entry is 0x10 bytes
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameLOD.h
class GameLODManager
{
public:
	DynamicGameLODLevel findDynamicLODLevel(float averageFPS);

private:
	char m_unreconstructed_00[0x120];
	DynamicGameLODInfo m_dynamicGameLODInfo[DYNAMIC_GAME_LOD_COUNT];	///< retail this+0x120
};

// ?findDynamicLODLevel@GameLODManager@@QAE?AW4DynamicGameLODLevel@@M@Z
DynamicGameLODLevel GameLODManager::findDynamicLODLevel(float averageFPS)
{
	int ifps=(int)(averageFPS);	//convert to integer.

	for (int i=DYNAMIC_GAME_LOD_VERY_HIGH; i>=DYNAMIC_GAME_LOD_LOW; i--)
	{	//check which of the LOD levels matches our fps
		if (m_dynamicGameLODInfo[i].m_minFPS < ifps)
			return (DynamicGameLODLevel)i;
	}
	return DYNAMIC_GAME_LOD_LOW;	//none of the low levels were slow enough so pick the lowest.
}
