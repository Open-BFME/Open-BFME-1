// ?storeTwoRecords@@YAXPBURva00784030Pair@@@Z
// partial score=0.9 date=2026-09-06
struct Rva00784030Rec { int m_id; float x; float y; float z; };
struct Rva00784030Pair { Rva00784030Rec m_first; Rva00784030Rec m_second; };
extern Rva00784030Rec Rva00784030First;
extern Rva00784030Rec Rva00784030Second;
void storeTwoRecords(const Rva00784030Pair* pair)
{
	const Rva00784030Rec& a = pair->m_first;
	const Rva00784030Rec& b = pair->m_second;
	Rva00784030First = a;
	Rva00784030Second = b;
}
