class BfmeNodeNY;

class BfmeTableNY
{
public:
	// bfmeFindNY() is reached through the ILT thunk below, not declared here.

	BfmeNodeNY *m_bfmeEndNY;
};

// The table lookup goes through the five-byte ILT thunk at 0x00016C70, defined
// as ?j_00016c70@@YAXXZ in game/gen_small/thunks_010.cpp (target FUN_004eef40)
// and pinned for ?bfmeFindNY@BfmeTableNY@@. The thunk declares no argument of
// its own: it jumps with the thiscall `this` in ECX, so the call is spelled
// through a thiscall member pointer of the same shape.
extern void j_00016c70();

typedef void (BfmeTableNY::*bfmeFindNYThunk)(BfmeNodeNY **found, void **key);

union BfmeFindNYThunkCast
{
	void (__cdecl *freeFunction)(BfmeNodeNY **found, void **key);
	bfmeFindNYThunk memberFunction;
};

class BfmeItemNY
{
public:
	unsigned char m_bfmeHeadNY[0x74];
	void *m_bfmeKeyNY;
	unsigned char m_bfmeGapNY[0x19c];
	int m_bfmeKindNY;
};

class BfmeOwnerNY
{
public:
	char bfmeCheckNY(void *item);

	unsigned char m_bfmeHeadNY[0x30];
	BfmeTableNY m_bfmeTableNY;
};

char BfmeOwnerNY::bfmeCheckNY(void *item)
{
	if (((BfmeItemNY *)item)->m_bfmeKindNY == *(int *)((char *)this - 0xdc))
		return 1;

	item = ((BfmeItemNY *)item)->m_bfmeKeyNY;

	BfmeNodeNY *found;

	BfmeFindNYThunkCast cast;
	cast.freeFunction = reinterpret_cast<void (__cdecl *)(BfmeNodeNY **, void **)>(&::j_00016c70);
	(m_bfmeTableNY.*cast.memberFunction)(&found, &item);

	return found != m_bfmeTableNY.m_bfmeEndNY;
}
