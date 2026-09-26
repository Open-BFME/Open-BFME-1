// ?callback@Rva003DE940@@QAEHPAVRva003DE940Cell@@0HH@Z
// partial score=0.33 date=2026-09-16
// Scratch reconstruction only; do not promote this file to Code/.
//
// Retail 0x003DE940: 284 bytes, complete boundary
// 0x003DE940..0x003DEA5B (exclusive 0x003DEA5C), RET 0x10.
// The member receiver is an address-derived four-field callback payload:
//   +0x00 -> receiver used by 0x003DC810, 0x003DB900 and 0x003D6400
//   +0x08 -> second cell passed to 0x003DB900
//   +0x0c -> diameter compared after 0x003DC810
// The semantic owner is intentionally not claimed.
//
// Resolved retail calls, in body order:
//   ILT 0x00048D29 -> 0x003DC810 (six-Int thiscall clear test)
//   ILT 0x0003A828 -> 0x003DB900 (two-cell thiscall cost calculation)
//   ILT 0x00040313 -> 0x003F69A0 (to.setParentCellHierarchical(from))
//   ILT 0x00024EF1 -> 0x003D6400 (one-cell thiscall indexed update)
//   ILT 0x0003D1A9 -> 0x003F6AD0 (cdecl pool initialization)
//   ILT 0x00021DA0 -> 0x003D7DB0 (cdecl free-list acquire)
// The callee declarations below are ABI declarations only; unresolved calls
// remain relocations for the scratch probe.
//
// The cell is the observed BFME 16-byte object: m_info at +0x00 and the
// packed dword at +0x0c.  The byte at +0x0f is used exactly as observed by
// retail; its semantic bit name is deliberately left address-derived.
// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

struct Rva003DE940Coord
{
	Int x;
	Int y;
};

struct Rva003DE940Info
{
	char m_pad00[0x0c];
	Rva003DE940Info *m_prevOpen;       // observed +0x0c reset
	UnsignedShort m_totalCost;         // observed +0x10
	UnsignedShort m_costSoFar;         // observed +0x12
	char m_pad14[0x10];
	long m_state0:1;                    // observed state dword +0x24, bit 0
	long m_state1:1;
	long m_state2:1;
	long m_state3:1;                    // tested as the first list-state bit
	long m_state4:1;                    // tested as the second list-state bit
	long m_stateRest:27;
};

class Rva003DE940Cell
{
public:
	Rva003DE940Info *m_info;            // observed +0x00
	char m_pad04[0x08];
	UnsignedInt m_packed;               // observed +0x0c; object is 16 bytes

	Int getLayer(void) const
	{
		return (m_packed >> 6) & 0x3f;
	}

	bool getState3(void) const { return m_info->m_state3; }
	bool getState4(void) const { return m_info->m_state4; }

	void setParentCellHierarchical(Rva003DE940Cell *parent);
};

class Rva003DE940Pathfinder
{
public:
	Int clearCellForDiameter(Int crusher, Int cellX, Int cellY,
		Int layer, Int diameter, Int attackerOnWall);
	Int rva003DB900Cost(Rva003DE940Cell *cell,
		Rva003DE940Cell *goal);
	void rva003D6400CopyIndexed(Rva003DE940Cell *cell);
};

extern Rva003DE940Info *g_rva003DE940FreeList;
extern void __cdecl rva003DE940AllocateCellInfos(void);
extern Rva003DE940Info *__cdecl rva003DE940AcquireCellInfo(
	Rva003DE940Info **freeList, Rva003DE940Cell *cell,
	const Rva003DE940Coord *pos);

class Rva003DE940
{
public:
	Int callback(Rva003DE940Cell *from, Rva003DE940Cell *to,
		Int to_x, Int to_y);

	Rva003DE940Pathfinder *m_pathfinder; // +0x00
	Int m_pad04;                         // +0x04
	Rva003DE940Cell *m_goalCell;          // +0x08
	Int m_diameter;                      // +0x0c
};

Int Rva003DE940::callback(Rva003DE940Cell *from, Rva003DE940Cell *to,
	Int to_x, Int to_y)
{
	if (from == 0)
		return 0;

	if (to->m_info != 0) {
		if (to->getState3() || to->getState4())
			return 1;
	}

	Int clearDiameter = m_pathfinder->clearCellForDiameter(
		0, to_x, to_y, to->getLayer(), m_diameter, 1);
	if (clearDiameter != m_diameter)
		return 1;

	Rva003DE940Coord newCellCoord;
	newCellCoord.x = to_x;
	newCellCoord.y = to_y;
	if (to->m_info == 0) {
		if (g_rva003DE940FreeList == 0)
			rva003DE940AllocateCellInfos();
		to->m_info = rva003DE940AcquireCellInfo(
			&g_rva003DE940FreeList, to, &newCellCoord);
	} else {
		to->m_info->m_prevOpen = 0;
	}

	to->m_info->m_state0 = 0;
	Int costRemaining = m_pathfinder->rva003DB900Cost(to, m_goalCell);
	bool state24 = ((to->m_packed >> 24) & 1) != 0;
	Int stepCost = state24 ? 2 : 5;
	to->m_info->m_costSoFar =
		(UnsignedShort)(from->m_info->m_costSoFar + stepCost);
	to->setParentCellHierarchical(from);
	to->m_info->m_totalCost =
		(UnsignedShort)(to->m_info->m_costSoFar + costRemaining);
	m_pathfinder->rva003D6400CopyIndexed(to);
	return 0;
}

