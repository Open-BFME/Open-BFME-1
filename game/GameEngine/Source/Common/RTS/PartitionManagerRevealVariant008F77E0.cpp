// cl: /DNDEBUG /MD /EHsc
// Fuzzy-twin (r0.940) of ?doShroudReveal@PartitionManager@@QAEXPBUCoord3D@@MI@Z
// / ?undoShroudReveal@PartitionManager@@... in
// game/GameEngine/Source/Common/RTS/ShroudManagerImpl008FBA40.cpp: same
// cellX/cellY/cellRadius conversion from a Coord3D position + radius via
// ceil/floor and PartitionManager's m_impl (offset 0xC), but this variant
// forwards two extra passthrough int args to BfmeOwnerXO::bfmeSendXO at
// 0x008FA070 with 6 args instead of PartitionManager's doShroudReveal/
// undoShroudReveal wrappers.
// IDENTITY OF THIS PARTITION MANAGER METHOD IS NOT RECOVERED: its local
// manager and implementation views remain address-derived. Their field
// layout (mode@0, region@4, defaultCellSize@0x1C, inverseCellSize@0x20,
// m_impl@0xC) matches ShroudManagerImpl/PartitionManager exactly;
// the retail call target is ledger-matched as BfmeOwnerXO::bfmeSendXO.

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

extern "C" __declspec(dllimport) double __cdecl ceil(double value);
extern "C" __declspec(dllimport) double __cdecl floor(double value);

__forceinline Int shroudFloatToLong(Real value)
{
	long result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
#include "../../../../Libraries/Include/Lib/Coord3D.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Region3D
{
	Coord3D lo;
	Coord3D hi;
};

// Layout view of the implementation fields read by this caller.
class Rva008F77E0ShroudImpl
{
public:
	Int mode;
	Region3D region;
	Real defaultCellSize;
	Real inverseCellSize;
};

class BfmeOwnerXO
{
public:
	void bfmeSendXO(void *a1, void *a2, Int a3, Int a4, void *a5,
		UnsignedInt a6);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class Rva008F77E0PartitionManager
{
public:
	__declspec(noinline) void revealVariantFromPosition(
		const Coord3D *position, Real radius, Int a4, Int a5,
		UnsignedInt playerMask);

private:
	char m_unmodelled_00[0x0C];
	Rva008F77E0ShroudImpl *m_impl;
};

// ?revealVariantFromPosition@Rva008F77E0PartitionManager@@QAEXPBUCoord3D@@MHHI@Z
void Rva008F77E0PartitionManager::revealVariantFromPosition(
	const Coord3D *position, Real radius, Int a4, Int a5,
	UnsignedInt playerMask)
{
	Real radiusInCells = (Real)ceil(radius * m_impl->inverseCellSize);
	Int cellRadius = shroudFloatToLong(radiusInCells);
	Real yInCells = (Real)floor((position->y - m_impl->region.lo.y) *
		m_impl->inverseCellSize);
	Int cellY = shroudFloatToLong(yInCells);
	Real xInCells = (Real)floor((position->x - m_impl->region.lo.x) *
		m_impl->inverseCellSize);
	Int cellX = shroudFloatToLong(xInCells);

	reinterpret_cast<BfmeOwnerXO *>(m_impl)->bfmeSendXO(
		reinterpret_cast<void *>(cellX), reinterpret_cast<void *>(cellY),
		cellRadius, a4, reinterpret_cast<void *>(a5), playerMask);
}
