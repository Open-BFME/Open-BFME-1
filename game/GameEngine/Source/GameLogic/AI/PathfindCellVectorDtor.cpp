// cl: /DNDEBUG /MD /EHsc

// PathfindCell's vector deleting destructor, retail 0x003D5710 (84 bytes).
// It passes the destructor's ILT 0x00036AB1 and stride 0x10 to the eh vector
// destructor iterator, and calls the destructor (0x003F6EA0) directly for the
// scalar case. ilt_oracle confirms ??_EPathfindCell@@QAEPAXI@Z here; see
// targets/game/reverse/identity_evidence/003f6ea0-PathfindCell-dtor.md.

// Retail frees the array through operator delete[] (??_V@YAXPAX@Z,
// 0x00881EF0); without this declaration cl uses scalar operator delete.
void __cdecl operator delete[](void *block);

class PathfindCellInfo;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCell
{
public:
	~PathfindCell();

private:
	PathfindCellInfo *m_info;
	unsigned char m_bfmeTail[0x0C];
};

// The delete[] expression below makes cl emit the out-of-line
// ??_EPathfindCell@@QAEPAXI@Z COMDAT.
// ?bfmeEmitPathfindCellVectorDtor@@YAXPAVPathfindCell@@@Z absent-from-retail
void bfmeEmitPathfindCellVectorDtor(PathfindCell *cells)
{
	delete[] cells;
}
