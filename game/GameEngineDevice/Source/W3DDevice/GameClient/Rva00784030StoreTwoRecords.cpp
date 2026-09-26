// cl: /DNDEBUG /MD
// BFME 0x00784030 copies two records into adjacent graphics state globals.
// No caller supplies an original method name; retain the address in the symbol.
struct Rva00784030Rec { int m_id; float x; float y; float z; };
struct Rva00784030Pair { Rva00784030Rec m_first; Rva00784030Rec m_second; };
extern Rva00784030Rec Rva00784030First;
extern Rva00784030Rec Rva00784030Second;
void storeTwoRecordsRva00784030(const Rva00784030Pair* pair)
{
	const Rva00784030Rec &a = pair->m_first;
	float z = a.z, y = a.y, x = a.x;
	Rva00784030First.m_id = a.m_id;
	Rva00784030First.x = x;
	Rva00784030First.y = y;
	Rva00784030First.z = z;
	const Rva00784030Rec &b = pair->m_second;
	float z2 = b.z, y2 = b.y, x2 = b.x;
	Rva00784030Second.m_id = b.m_id;
	Rva00784030Second.x = x2;
	Rva00784030Second.y = y2;
	Rva00784030Second.z = z2;
}
