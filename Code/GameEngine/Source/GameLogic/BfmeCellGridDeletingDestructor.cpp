// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: BfmeCellGrid scalar-deleting destructor at retail RVA
// 0x001DE390 (30 bytes). The wrapper calls the exact BfmeCellGrid destructor
// through ILT 0x000046E2, whose target thunk 0x001B1AC0 clears the grid
// allocations. The exact constructor at 0x001B1830 recovers the 0x1C-byte
// grid layout, and the landed grid method family independently establishes
// the class identity.

class BfmeCellGrid
{
public:
	~BfmeCellGrid();
};

void forceBfmeCellGridDeletingDestructor(BfmeCellGrid *value)
{
	delete value;
}
