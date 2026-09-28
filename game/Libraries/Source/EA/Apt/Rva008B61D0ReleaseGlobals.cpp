// cl: /O2 /DNDEBUG /MD

// Open-BFME7: RVA 0x008B61D0 (782 bytes). Release the 37 lazily created Apt
// property singletons at 0x013383A4 through 0x01338434 through virtual slot +4
// and clear each slot. The same globals are created one per switch case by
// rva008B73B0 (Rva008B73B0Properties.cpp), so this TU shares its symbols;
// called from rva00891E00ReleaseChain. Address-derived identity.

class Rva00899FC0;

class Rva008B61D0Slot
{
public:
	virtual void slot00();
	virtual void release();
};

extern Rva00899FC0 *Va013383A4;
extern Rva00899FC0 *Va013383A8;
extern Rva00899FC0 *Va013383AC;
extern Rva00899FC0 *Va013383B0;
extern Rva00899FC0 *Va013383B4;
extern Rva00899FC0 *Va013383B8;
extern Rva00899FC0 *Va013383BC;
extern Rva00899FC0 *Va013383C0;
extern Rva00899FC0 *Va013383C4;
extern Rva00899FC0 *Va013383C8;
extern Rva00899FC0 *Va013383CC;
extern Rva00899FC0 *Va013383D0;
extern Rva00899FC0 *Va013383D4;
extern Rva00899FC0 *Va013383D8;
extern Rva00899FC0 *Va013383DC;
extern Rva00899FC0 *Va013383E0;
extern Rva00899FC0 *Va013383E4;
extern Rva00899FC0 *Va013383E8;
extern Rva00899FC0 *Va013383EC;
extern Rva00899FC0 *Va013383F0;
extern Rva00899FC0 *Va013383F4;
extern Rva00899FC0 *Va013383F8;
extern Rva00899FC0 *Va013383FC;
extern Rva00899FC0 *Va01338400;
extern Rva00899FC0 *Va01338404;
extern Rva00899FC0 *Va01338408;
extern Rva00899FC0 *Va0133840C;
extern Rva00899FC0 *Va01338410;
extern Rva00899FC0 *Va01338414;
extern Rva00899FC0 *Va01338418;
extern Rva00899FC0 *Va0133841C;
extern Rva00899FC0 *Va01338420;
extern Rva00899FC0 *Va01338424;
extern Rva00899FC0 *Va01338428;
extern Rva00899FC0 *Va0133842C;
extern Rva00899FC0 *Va01338430;
extern Rva00899FC0 *Va01338434;

void rva008B61D0ReleaseGlobals()
{
	Rva00899FC0 *z = 0;
	if (Va013383A4 != z)
	{
		((Rva008B61D0Slot *)Va013383A4)->release();
		Va013383A4 = z;
	}
	if (Va013383A8 != z)
	{
		((Rva008B61D0Slot *)Va013383A8)->release();
		Va013383A8 = z;
	}
	if (Va013383AC != z)
	{
		((Rva008B61D0Slot *)Va013383AC)->release();
		Va013383AC = z;
	}
	if (Va013383B0 != z)
	{
		((Rva008B61D0Slot *)Va013383B0)->release();
		Va013383B0 = z;
	}
	if (Va013383B4 != z)
	{
		((Rva008B61D0Slot *)Va013383B4)->release();
		Va013383B4 = z;
	}
	if (Va013383B8 != z)
	{
		((Rva008B61D0Slot *)Va013383B8)->release();
		Va013383B8 = z;
	}
	if (Va013383BC != z)
	{
		((Rva008B61D0Slot *)Va013383BC)->release();
		Va013383BC = z;
	}
	if (Va013383C0 != z)
	{
		((Rva008B61D0Slot *)Va013383C0)->release();
		Va013383C0 = z;
	}
	if (Va013383C4 != z)
	{
		((Rva008B61D0Slot *)Va013383C4)->release();
		Va013383C4 = z;
	}
	if (Va013383C8 != z)
	{
		((Rva008B61D0Slot *)Va013383C8)->release();
		Va013383C8 = z;
	}
	if (Va013383CC != z)
	{
		((Rva008B61D0Slot *)Va013383CC)->release();
		Va013383CC = z;
	}
	if (Va013383D0 != z)
	{
		((Rva008B61D0Slot *)Va013383D0)->release();
		Va013383D0 = z;
	}
	if (Va013383D4 != z)
	{
		((Rva008B61D0Slot *)Va013383D4)->release();
		Va013383D4 = z;
	}
	if (Va013383D8 != z)
	{
		((Rva008B61D0Slot *)Va013383D8)->release();
		Va013383D8 = z;
	}
	if (Va013383DC != z)
	{
		((Rva008B61D0Slot *)Va013383DC)->release();
		Va013383DC = z;
	}
	if (Va013383E0 != z)
	{
		((Rva008B61D0Slot *)Va013383E0)->release();
		Va013383E0 = z;
	}
	if (Va013383E4 != z)
	{
		((Rva008B61D0Slot *)Va013383E4)->release();
		Va013383E4 = z;
	}
	if (Va013383E8 != z)
	{
		((Rva008B61D0Slot *)Va013383E8)->release();
		Va013383E8 = z;
	}
	if (Va013383EC != z)
	{
		((Rva008B61D0Slot *)Va013383EC)->release();
		Va013383EC = z;
	}
	if (Va013383F0 != z)
	{
		((Rva008B61D0Slot *)Va013383F0)->release();
		Va013383F0 = z;
	}
	if (Va013383F4 != z)
	{
		((Rva008B61D0Slot *)Va013383F4)->release();
		Va013383F4 = z;
	}
	if (Va013383F8 != z)
	{
		((Rva008B61D0Slot *)Va013383F8)->release();
		Va013383F8 = z;
	}
	if (Va013383FC != z)
	{
		((Rva008B61D0Slot *)Va013383FC)->release();
		Va013383FC = z;
	}
	if (Va01338400 != z)
	{
		((Rva008B61D0Slot *)Va01338400)->release();
		Va01338400 = z;
	}
	if (Va01338404 != z)
	{
		((Rva008B61D0Slot *)Va01338404)->release();
		Va01338404 = z;
	}
	if (Va01338408 != z)
	{
		((Rva008B61D0Slot *)Va01338408)->release();
		Va01338408 = z;
	}
	if (Va0133840C != z)
	{
		((Rva008B61D0Slot *)Va0133840C)->release();
		Va0133840C = z;
	}
	if (Va01338410 != z)
	{
		((Rva008B61D0Slot *)Va01338410)->release();
		Va01338410 = z;
	}
	if (Va01338414 != z)
	{
		((Rva008B61D0Slot *)Va01338414)->release();
		Va01338414 = z;
	}
	if (Va01338418 != z)
	{
		((Rva008B61D0Slot *)Va01338418)->release();
		Va01338418 = z;
	}
	if (Va0133841C != z)
	{
		((Rva008B61D0Slot *)Va0133841C)->release();
		Va0133841C = z;
	}
	if (Va01338420 != z)
	{
		((Rva008B61D0Slot *)Va01338420)->release();
		Va01338420 = z;
	}
	if (Va01338424 != z)
	{
		((Rva008B61D0Slot *)Va01338424)->release();
		Va01338424 = z;
	}
	if (Va01338428 != z)
	{
		((Rva008B61D0Slot *)Va01338428)->release();
		Va01338428 = z;
	}
	if (Va0133842C != z)
	{
		((Rva008B61D0Slot *)Va0133842C)->release();
		Va0133842C = z;
	}
	if (Va01338430 != z)
	{
		((Rva008B61D0Slot *)Va01338430)->release();
		Va01338430 = z;
	}
	if (Va01338434 != z)
	{
		((Rva008B61D0Slot *)Va01338434)->release();
		Va01338434 = z;
	}
}
