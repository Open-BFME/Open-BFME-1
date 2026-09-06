// cl: /DNDEBUG /MD /EHsc
// Fuzzy-twin (r0.940) of ?doShroudReveal@PartitionManager@@QAEXPBUCoord3D@@MI@Z
// / ?undoShroudReveal@PartitionManager@@... in
// Code/GameEngine/Source/Common/RTS/ShroudManagerImpl008FBA40.cpp: same
// cellX/cellY/cellRadius conversion from a Coord3D position + radius via
// ceil/floor and PartitionManager's m_impl (offset 0xC), but this variant
// forwards two extra passthrough int args and calls
// ShroudManagerImpl008FBA40::revealVariant (still a dump at 0x008FA070,
// pinned as Rva008F77E0ShroudImpl::revealVariant) with 6 args instead of
// PartitionManager's doShroudReveal/undoShroudReveal wrappers.
// IDENTITY IS NOT RECOVERED: class/method names are address-derived; field
// layout (mode@0, region@4, defaultCellSize@0x1C, inverseCellSize@0x20,
// m_impl@0xC) matches ShroudManagerImpl008FBA40/PartitionManager exactly
// per reverse/symbols.csv note on 0x008FA070.

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Region3D
{
	Coord3D lo;
	Coord3D hi;
};

// ?revealVariant@Rva008F77E0ShroudImpl@@QAEXHHHHHI@Z (still a dump at
// 0x008FA070; declared here only to reproduce the call's mangled name)
class Rva008F77E0ShroudImpl
{
public:
	Int mode;
	Region3D region;
	Real defaultCellSize;
	Real inverseCellSize;

	void revealVariant(Int cellX, Int cellY, Int cellRadius, Int a4, Int a5,
		UnsignedInt playerMask);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
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

// ?d_008f77e0@@YAXXZ
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

	m_impl->revealVariant(cellX, cellY, cellRadius, a4, a5, playerMask);
}
